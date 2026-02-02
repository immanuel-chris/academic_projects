# scripts/01_extract_landmarks.py

import os
import cv2
import mediapipe as mp
import csv
import numpy as np

# Initialize MediaPipe Hands model
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils

# Define the gestures we want to process
SELECTED_GESTURES = [0, 1, 3, 7, 10, 13]

# Path configuration
BASE_DIR = "C:/Users/Admin/OneDrive/Documents/FSL_AI"
CLIPS_DIR = os.path.join(BASE_DIR, "clips")
OUTPUT_CSV = os.path.join(BASE_DIR, "data", "raw_landmarks", "landmarks_data.csv")

# Create output directory if it doesn't exist
os.makedirs(os.path.dirname(OUTPUT_CSV), exist_ok=True)

def extract_landmarks_from_video(video_path, hands_model):
    """
    Process a single video file and extract HAND landmarks from each frame.
    
    Args:
        video_path (str): Path to the video file
        hands_model: Initialized MediaPipe Hands model
    
    Returns:
        list: List of landmark data for all frames in the video
    """
    cap = cv2.VideoCapture(video_path)
    video_landmarks = []
    
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break
            
        # Convert BGR to RGB (MediaPipe requires RGB)
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        
        # To improve performance, mark the image as not writeable to pass by reference
        rgb_frame.flags.writeable = False
        
        # Process the frame and get hand landmarks only
        results = hands_model.process(rgb_frame)
        
        # Extract landmarks for each frame
        frame_landmarks = []
        
        # Extract Left Hand landmarks (21 landmarks, each with x,y,z)
        if results.multi_hand_landmarks:
            # Check which hand is which
            for hand_landmarks, handedness in zip(results.multi_hand_landmarks, results.multi_handedness):
                # handedness.classification[0].index: 0=Right, 1=Left
                hand_label = handedness.classification[0].label
                
                if hand_label == "Left":
                    for landmark in hand_landmarks.landmark:
                        frame_landmarks.extend([landmark.x, landmark.y, landmark.z])
                elif hand_label == "Right":
                    for landmark in hand_landmarks.landmark:
                        frame_landmarks.extend([landmark.x, landmark.y, landmark.z])
        
        # If we didn't get both hands, fill with zeros
        if len(frame_landmarks) < 21 * 3 * 2:  # Less than 2 hands worth of data
            # Reset and build properly
            frame_landmarks = []
            
            # Try to find left and right hands
            left_hand_found = False
            right_hand_found = False
            
            if results.multi_hand_landmarks:
                for hand_landmarks, handedness in zip(results.multi_hand_landmarks, results.multi_handedness):
                    hand_label = handedness.classification[0].label
                    
                    if hand_label == "Left" and not left_hand_found:
                        for landmark in hand_landmarks.landmark:
                            frame_landmarks.extend([landmark.x, landmark.y, landmark.z])
                        left_hand_found = True
                    elif hand_label == "Right" and not right_hand_found:
                        for landmark in hand_landmarks.landmark:
                            frame_landmarks.extend([landmark.x, landmark.y, landmark.z])
                        right_hand_found = True
            
            # Fill missing hands with zeros
            if not left_hand_found:
                frame_landmarks.extend([0] * (21 * 3))
            if not right_hand_found:
                frame_landmarks.extend([0] * (21 * 3))
        
        video_landmarks.append(frame_landmarks)
    
    cap.release()
    return video_landmarks

def main():
    print("Starting HAND landmark extraction (no face/pose)...")
    
    # Count total videos for progress tracking
    total_videos = 0
    for gesture_id in SELECTED_GESTURES:
        gesture_dir = os.path.join(CLIPS_DIR, str(gesture_id))
        if os.path.exists(gesture_dir):
            total_videos += len([f for f in os.listdir(gesture_dir) if f.endswith('.MOV')])
    
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
            
            print(f"Processing gesture {gesture_id}...")
            
            for video_file in os.listdir(gesture_dir):
                if video_file.endswith('.MOV'):
                    video_path = os.path.join(gesture_dir, video_file)
                    
                    try:
                        # Extract landmarks from this video
                        landmarks = extract_landmarks_from_video(video_path, hands)
                        
                        # Save to CSV
                        with open(OUTPUT_CSV, 'a', newline='') as csvfile:
                            csv_writer = csv.writer(csvfile)
                            csv_writer.writerow([gesture_id, video_file, str(landmarks)])
                        
                        processed_count += 1
                        print(f"Processed {processed_count}/{total_videos}: {video_file}")
                        
                    except Exception as e:
                        print(f"Error processing {video_path}: {str(e)}")
                        continue
    
    print(f"Landmark extraction completed! Processed {processed_count} videos.")
    print(f"Data saved to: {OUTPUT_CSV}")

if __name__ == "__main__":
    main()