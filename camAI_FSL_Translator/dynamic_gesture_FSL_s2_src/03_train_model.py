# scripts/03_train_model.py

import os
import pickle
import numpy as np
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, classification_report
from sklearn.model_selection import cross_val_score, GridSearchCV
import joblib

# Path configuration for NEW project
BASE_DIR = "C:/Users/Admin/OneDrive/Documents/FSL_AI_p2"  # Updated directory
DATASET_PATH = os.path.join(BASE_DIR, "data", "dataset", "processed_dataset.pkl")
MODELS_DIR = os.path.join(BASE_DIR, "models", "traditional")

# Create models directory if it doesn't exist
os.makedirs(MODELS_DIR, exist_ok=True)

def extract_features_from_sequences(X):
    """
    Extract meaningful features from the sequence data instead of using raw sequences
    """
    features = []
    
    for sequence in X:
        # Convert to numpy array
        seq_array = np.array(sequence)
        
        # Extract statistical features from the sequence
        seq_features = []
        
        # Basic statistics for each feature dimension
        for dim in range(seq_array.shape[1]):
            feature_dim = seq_array[:, dim]
            seq_features.extend([
                np.mean(feature_dim),      # Mean
                np.std(feature_dim),       # Standard deviation
                np.min(feature_dim),       # Minimum
                np.max(feature_dim),       # Maximum
                np.median(feature_dim),    # Median
            ])
        
        # Global statistics
        seq_features.extend([
            np.mean(seq_array),           # Global mean
            np.std(seq_array),            # Global std
        ])
        
        # Motion features (changes between frames)
        if len(seq_array) > 1:
            motion = np.diff(seq_array, axis=0)
            seq_features.extend([
                np.mean(motion),          # Average motion
                np.std(motion),           # Motion variability
            ])
        else:
            seq_features.extend([0, 0])
        
        features.append(seq_features)
    
    return np.array(features)

def train_traditional_models():
    """Train traditional ML models on the NEW gesture data"""
    print("=== Training Traditional ML Models for NEW Gesture Set ===")
    
    # 1. Load the processed dataset
    print("Loading processed dataset...")
    with open(DATASET_PATH, 'rb') as f:
        dataset = pickle.load(f)
    
    X_train = dataset['X_train']
    X_test = dataset['X_test']
    y_train = dataset['y_train']
    y_test = dataset['y_test']
    label_encoder = dataset['label_encoder']
    
    # Convert one-hot encoded labels back to integers
    y_train_labels = np.argmax(y_train, axis=1)
    y_test_labels = np.argmax(y_test, axis=1)
    
    print(f"Training data shape: {X_train.shape}")
    print(f"Testing data shape: {X_test.shape}")
    
    # 2. Extract features from sequences
    print("\nExtracting features from sequences...")
    X_train_features = extract_features_from_sequences(X_train)
    X_test_features = extract_features_from_sequences(X_test)
    
    print(f"Feature-extracted training data shape: {X_train_features.shape}")
    print(f"Feature-extracted testing data shape: {X_test_features.shape}")
    
    # 3. Train multiple traditional models
    models = {
        'Random Forest': RandomForestClassifier(n_estimators=100, random_state=42),
        'SVM': SVC(kernel='rbf', random_state=42),
        'Logistic Regression': LogisticRegression(random_state=42, max_iter=1000)
    }
    
    results = {}
    
    for name, model in models.items():
        print(f"\n--- Training {name} ---")
        
        # Simple training
        model.fit(X_train_features, y_train_labels)
        
        # Predictions
        y_train_pred = model.predict(X_train_features)
        y_test_pred = model.predict(X_test_features)
        
        # Calculate accuracies
        train_accuracy = accuracy_score(y_train_labels, y_train_pred)
        test_accuracy = accuracy_score(y_test_labels, y_test_pred)
        
        results[name] = {
            'model': model,
            'train_accuracy': train_accuracy,
            'test_accuracy': test_accuracy,
            'predictions': y_test_pred
        }
        
        print(f"Training Accuracy: {train_accuracy:.4f}")
        print(f"Testing Accuracy: {test_accuracy:.4f}")
        
        # Cross-validation
        cv_scores = cross_val_score(model, X_train_features, y_train_labels, cv=5)
        print(f"Cross-validation scores: {cv_scores}")
        print(f"Mean CV accuracy: {cv_scores.mean():.4f} (+/- {cv_scores.std() * 2:.4f})")
    
    # 4. Find the best model
    best_model_name = max(results.keys(), key=lambda x: results[x]['test_accuracy'])
    best_model = results[best_model_name]['model']
    best_accuracy = results[best_model_name]['test_accuracy']
    
    print(f"\n=== BEST MODEL: {best_model_name} ===")
    print(f"Best Test Accuracy: {best_accuracy:.4f}")
    
    # 5. Detailed evaluation of best model
    print(f"\n=== Detailed Classification Report for {best_model_name} ===")
    y_test_pred_best = results[best_model_name]['predictions']
    print(classification_report(y_test_labels, y_test_pred_best, 
                              target_names=[str(cls) for cls in label_encoder.classes_]))
    
    # 6. Save the best model and feature extractor info
    best_model_path = os.path.join(MODELS_DIR, f"best_traditional_model.joblib")
    joblib.dump(best_model, best_model_path)
    print(f"\nBest model saved to: {best_model_path}")
    
    # Save feature extraction info
    feature_info = {
        'label_encoder': label_encoder,
        'feature_dimension': X_train_features.shape[1],
        'models_results': results
    }
    
    feature_info_path = os.path.join(MODELS_DIR, "feature_info.pkl")
    with open(feature_info_path, 'wb') as f:
        pickle.dump(feature_info, f)
    print(f"Feature info saved to: {feature_info_path}")
    
    # 7. Print comparison
    print(f"\n=== MODEL COMPARISON ===")
    for name, result in results.items():
        print(f"{name}: Train={result['train_accuracy']:.4f}, Test={result['test_accuracy']:.4f}")
    
    return results, best_model_name

if __name__ == "__main__":
    results, best_model_name = train_traditional_models()