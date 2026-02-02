# scripts/02_create_dataset.py

import os
import pandas as pd
import numpy as np
import ast
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from tensorflow.keras.utils import to_categorical
import pickle

# Path configuration for NEW project
BASE_DIR = "C:/Users/Admin/OneDrive/Documents/FSL_AI_p2"
INPUT_CSV = os.path.join(BASE_DIR, "data", "raw_landmarks", "landmarks_data.csv")
OUTPUT_DIR = os.path.join(BASE_DIR, "data", "dataset")

# Create output directory if it doesn't exist
os.makedirs(OUTPUT_DIR, exist_ok=True)

# Expected feature dimension: 21 landmarks × 3 coordinates × 2 hands = 126
EXPECTED_FEATURES = 126

def load_and_parse_landmarks():
    """Load the raw landmarks CSV and parse the landmark data with validation"""
    print("Loading and parsing landmark data for NEW gesture set...")
    
    # Read the CSV file
    df = pd.read_csv(INPUT_CSV)
    print(f"Loaded {len(df)} videos")
    
    # DEBUG: Check what gesture IDs are actually in the CSV
    print(f"Unique gesture IDs in CSV: {df['gesture_id'].unique()}")
    print(f"Gesture ID value counts:")
    print(df['gesture_id'].value_counts().sort_index())
    
    landmark_data = []
    labels = []
    video_files = []
    problematic_videos = []
    
    for idx, row in df.iterrows():
        try:
            # Convert string representation of list to actual list
            landmarks = ast.literal_eval(row['landmark_data'])
            
            # Validate and fix each frame
            validated_frames = []
            for frame in landmarks:
                if len(frame) == EXPECTED_FEATURES:
                    validated_frames.append(frame)
                else:
                    # Fix frame by padding or truncating to expected size
                    if len(frame) < EXPECTED_FEATURES:
                        # Pad with zeros
                        padded_frame = frame + [0] * (EXPECTED_FEATURES - len(frame))
                        validated_frames.append(padded_frame)
                    else:
                        # Truncate to expected size
                        validated_frames.append(frame[:EXPECTED_FEATURES])
            
            landmark_data.append(validated_frames)
            labels.append(row['gesture_id'])
            video_files.append(row['video_file'])
            
        except Exception as e:
            print(f"Error parsing landmarks for {row['video_file']}: {e}")
            problematic_videos.append(row['video_file'])
            continue
    
    print(f"Successfully parsed {len(landmark_data)} videos")
    print(f"Labels found: {set(labels)}")
    if problematic_videos:
        print(f"Problematic videos: {len(problematic_videos)}")
    
    return landmark_data, labels, video_files

def analyze_sequence_lengths(landmark_data):
    """Analyze the sequence lengths to determine padding strategy"""
    sequence_lengths = [len(seq) for seq in landmark_data]
    
    print("\n=== Sequence Length Analysis ===")
    print(f"Total sequences: {len(sequence_lengths)}")
    print(f"Min sequence length: {min(sequence_lengths)}")
    print(f"Max sequence length: {max(sequence_lengths)}")
    print(f"Mean sequence length: {np.mean(sequence_lengths):.2f}")
    print(f"Standard deviation: {np.std(sequence_lengths):.2f}")
    
    # Let's use the 90th percentile as our target sequence length
    target_length = int(np.percentile(sequence_lengths, 90))
    print(f"Recommended target sequence length (90th percentile): {target_length}")
    
    return target_length

def preprocess_sequences(landmark_data, target_length):
    """Preprocess sequences: pad shorter ones, truncate longer ones"""
    processed_sequences = []
    
    for sequence in landmark_data:
        # Convert to numpy array - now all frames should have consistent shape
        seq_array = np.array(sequence, dtype=np.float32)
        
        # Handle sequences that are shorter than target length
        if len(seq_array) < target_length:
            # Pad with zeros
            pad_length = target_length - len(seq_array)
            padding = np.zeros((pad_length, EXPECTED_FEATURES), dtype=np.float32)
            processed_seq = np.vstack([seq_array, padding])
        # Handle sequences that are longer than target length
        elif len(seq_array) > target_length:
            # Truncate from the middle (often contains the key gesture)
            start_idx = (len(seq_array) - target_length) // 2
            processed_seq = seq_array[start_idx:start_idx + target_length]
        else:
            processed_seq = seq_array
        
        processed_sequences.append(processed_seq)
    
    return np.array(processed_sequences)

def manual_stratified_split(X, y, labels, test_size=0.2, random_state=42):
    """Manual stratified split to ensure all classes are represented"""
    np.random.seed(random_state)
    
    # Get unique classes
    unique_classes = np.unique(labels)
    
    X_train, X_test, y_train, y_test, indices_train, indices_test = [], [], [], [], [], []
    
    for class_label in unique_classes:
        # Get indices for this class
        class_indices = np.where(np.array(labels) == class_label)[0]
        
        # Shuffle the indices
        np.random.shuffle(class_indices)
        
        # Calculate how many samples go to test
        n_test = int(len(class_indices) * test_size)
        
        # Split indices
        test_indices = class_indices[:n_test]
        train_indices = class_indices[n_test:]
        
        # Add to results
        indices_train.extend(train_indices)
        indices_test.extend(test_indices)
    
    # Sort indices to maintain order
    indices_train.sort()
    indices_test.sort()
    
    # Create splits
    X_train = X[indices_train]
    X_test = X[indices_test]
    y_train = y[indices_train]
    y_test = y[indices_test]
    
    return X_train, X_test, y_train, y_test, indices_train, indices_test

def create_dataset():
    """Main function to create the processed dataset"""
    print("=== Step 2: Creating Processed Dataset for NEW Gesture Set ===")
    
    # 1. Load and parse the raw data
    landmark_data, labels, video_files = load_and_parse_landmarks()
    
    # 2. Analyze sequence lengths
    target_length = analyze_sequence_lengths(landmark_data)
    
    # 3. Preprocess sequences (padding/truncation)
    print(f"\nPreprocessing sequences to target length: {target_length}")
    X_processed = preprocess_sequences(landmark_data, target_length)
    
    print(f"Processed data shape: {X_processed.shape}")
    
    # 4. Encode labels
    label_encoder = LabelEncoder()
    y_encoded = label_encoder.fit_transform(labels)
    y_categorical = to_categorical(y_encoded)
    
    print(f"Number of classes: {len(label_encoder.classes_)}")
    print(f"Classes: {label_encoder.classes_}")
    print(f"Encoded labels shape: {y_categorical.shape}")
    
    # 5. Use manual stratified split to ensure all classes are represented
    print("\nUsing manual stratified split...")
    X_train, X_test, y_train, y_test, train_indices, test_indices = manual_stratified_split(
        X_processed, y_categorical, labels, test_size=0.2, random_state=42
    )
    
    # Get the corresponding video files
    videos_train = [video_files[i] for i in train_indices]
    videos_test = [video_files[i] for i in test_indices]
    
    print(f"\n=== Dataset Split ===")
    print(f"Training set: {X_train.shape[0]} samples")
    print(f"Testing set: {X_test.shape[0]} samples")
    
    # DEBUG: Check the actual class distribution in train/test
    y_train_labels = np.argmax(y_train, axis=1)
    y_test_labels = np.argmax(y_test, axis=1)
    
    print("\n=== Actual Class Distribution ===")
    for i, class_id in enumerate(label_encoder.classes_):
        train_count = np.sum(y_train_labels == i)
        test_count = np.sum(y_test_labels == i)
        print(f"Class {class_id}: Train={train_count}, Test={test_count}")
    
    # 6. Save the processed dataset
    dataset = {
        'X_train': X_train,
        'X_test': X_test,
        'y_train': y_train,
        'y_test': y_test,
        'video_files_train': videos_train,
        'video_files_test': videos_test,
        'label_encoder': label_encoder,
        'target_sequence_length': target_length,
        'feature_dimension': EXPECTED_FEATURES
    }
    
    dataset_path = os.path.join(OUTPUT_DIR, 'processed_dataset.pkl')
    with open(dataset_path, 'wb') as f:
        pickle.dump(dataset, f)
    
    print(f"\nDataset saved to: {dataset_path}")
    
    # 7. Print some statistics
    print(f"\n=== Dataset Statistics ===")
    print(f"Input shape: {X_train.shape[1:]} (sequence_length, features)")
    print(f"Number of features per frame: {X_train.shape[2]}")
    print(f"Training samples: {X_train.shape[0]}")
    print(f"Test samples: {X_test.shape[0]}")
    print(f"Number of classes: {len(label_encoder.classes_)}")
    
    return dataset

if __name__ == "__main__":
    dataset = create_dataset()