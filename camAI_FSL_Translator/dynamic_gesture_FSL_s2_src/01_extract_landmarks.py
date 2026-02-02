# scripts/01_extract_landmarks.py

import os
import cv2
import mediapipe as mp
import csv
import numpy as np

# Initialize MediaPipe Hands model
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils

# Define the NEW gestures we want to process
SELECTED_GESTURES = [4, 5, 11, 14, 15]  # Updated gesture IDs

# Path configuration for NEW project
BASE_DIR = "C:/Users/Admin/OneDrive/Documents/FSL_AI_p2"  # Updated directory
CLIPS_DIR = os.path.join(BASE_DIR, "clips")
OUTPUT_CSV = os.path.join(BASE_DIR, "data", "raw_landmarks", "landmarks_data.csv")

# Create output directory if it doesn't exist
os.makedirs(os.path.dirname(OUTPUT_CSV), exist_ok=True)

def extract_landmarks_from_video(video_path, hands_model):
    """
    Process a single video file and extract HAND landmarks from each frame.
    """
    cap = cv2.VideoCapture(video_path)
    video_landmarks = []
    
    frame_count = 0
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break
            
        # Convert BGR to RGB (MediaPipe requires RGB)
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        rgb_frame.flags.writeable = False
        
        # Process the frame and get hand landmarks only
        results = hands_model.process(rgb_frame)
        
        frame_landmarks = []
        
        # Extract hand landmarks (same as during training)
        if results.multi_hand_landmarks:
            # We need to identify left and right hands correctly
            left_hand_data = None
            right_hand_data = None
            
            for hand_landmarks, handedness in zip(results.multi_hand_landmarks, results.multi_handedness):
                hand_label = handedness.classification[0].label
                
                if hand_label == "Left":
                    left_hand_data = hand_landmarks
                elif hand_label == "Right":
                    right_hand_data = hand_landmarks
            
            # Process left hand
            if left_hand_data:
                for landmark in left_hand_data.landmark:
                    frame_landmarks.extend([landmark.x, landmark.y, landmark.z])
            else:
                frame_landmarks.extend([0] * (21 * 3))
            
            # Process right hand
            if right_hand_data:
                for landmark in right_hand_data.landmark:
                    frame_landmarks.extend([landmark.x, landmark.y, landmark.z])
            else:
                frame_landmarks.extend([0] * (21 * 3))
        else:
            # No hands detected, fill with zeros
            frame_landmarks.extend([0] * (21 * 3 * 2))
        
        video_landmarks.append(frame_landmarks)
        frame_count += 1
    
    cap.release()
    print(f"  Processed {frame_count} frames")
    return video_landmarks

def main():
    print("Starting HAND landmark extraction for NEW gesture set...")
    print(f"Gestures to process: {SELECTED_GESTURES}")
    print(f"Project directory: {BASE_DIR}")
    
    # Count total videos for progress tracking
    total_videos = 0
    gesture_counts = {}
    
    for gesture_id in SELECTED_GESTURES:
        gesture_dir = os.path.join(CLIPS_DIR, str(gesture_id))
        if os.path.exists(gesture_dir):
            video_files = [f for f in os.listdir(gesture_dir) if f.endswith('.MOV')]
            gesture_counts[gesture_id] = len(video_files)
            total_videos += len(video_files)
            print(f"Gesture {gesture_id}: {len(video_files)} videos found")
        else:
            print(f"ERROR: Directory {gesture_dir} not found!")
            gesture_counts[gesture_id] = 0
    
    print(f"Total videos to process: {total_videos}")
    
    # Initialize CSV file and write header
    with open(OUTPUT_CSV, 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['gesture_id', 'video_file', 'landmark_data'])
    
    processed_count = 0
    
    # Process videos with MediaPipe Hands only
    with mp_hands.Hands(
        static_image_mode=False,  # False for video
        max_num_hands=2,          # Detect up to 2 hands
        min_detection_confidence=0.5,
        min_tracking_confidence=0.5) as hands:
        
        for gesture_id in SELECTED_GESTURES:
            gesture_dir = os.path.join(CLIPS_DIR, str(gesture_id))
            
            if not os.path.exists(gesture_dir):
                print(f"Warning: Directory {gesture_dir} not found. Skipping.")
                continue
            
            video_files = [f for f in os.listdir(gesture_dir) if f.endswith('.MOV')]
            print(f"\nProcessing gesture {gesture_id} ({len(video_files)} videos)...")
            
            for video_file in video_files:
                video_path = os.path.join(gesture_dir, video_file)
                
                try:
                    print(f"  Processing: {video_file}")
                    # Extract landmarks from this video
                    landmarks = extract_landmarks_from_video(video_path, hands)
                    
                    # Save to CSV
                    with open(OUTPUT_CSV, 'a', newline='') as csvfile:
                        csv_writer = csv.writer(csvfile)
                        csv_writer.writerow([gesture_id, video_file, str(landmarks)])
                    
                    processed_count += 1
                    print(f"  Completed {processed_count}/{total_videos}: {video_file}")
                    
                except Exception as e:
                    print(f"ERROR processing {video_path}: {str(e)}")
                    import traceback
                    traceback.print_exc()
                    continue
    
    print(f"\nLandmark extraction completed! Processed {processed_count}/{total_videos} videos.")
    print(f"Data saved to: {OUTPUT_CSV}")
    
    # Final summary
    print(f"\n=== PROCESSING SUMMARY ===")
    for gesture_id in SELECTED_GESTURES:
        print(f"Gesture {gesture_id}: {gesture_counts.get(gesture_id, 0)} videos")

if __name__ == "__main__":
    main()