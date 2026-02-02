# scripts/02_debug_landmarks.py

import os
import pandas as pd
import numpy as np
import ast

# Path configuration
BASE_DIR = "C:/Users/Admin/OneDrive/Documents/FSL_AI_p2"
INPUT_CSV = os.path.join(BASE_DIR, "data", "raw_landmarks", "landmarks_data.csv")

def debug_landmark_shapes():
    """Debug the landmark data to understand shape inconsistencies"""
    print("=== Debugging Landmark Data ===")
    
    # Read the CSV file
    df = pd.read_csv(INPUT_CSV)
    print(f"Loaded {len(df)} videos")
    
    # Analyze each sequence
    shape_problems = []
    valid_sequences = 0
    
    for idx, row in df.iterrows():
        try:
            landmarks = ast.literal_eval(row['landmark_data'])
            
            # Check if all frames have the same number of features
            frame_lengths = [len(frame) for frame in landmarks]
            unique_lengths = set(frame_lengths)
            
            if len(unique_lengths) > 1:
                shape_problems.append({
                    'video': row['video_file'],
                    'gesture_id': row['gesture_id'],
                    'frame_lengths': frame_lengths,
                    'unique_lengths': unique_lengths
                })
                print(f"PROBLEM: {row['video_file']} - Inconsistent frame lengths: {unique_lengths}")
            else:
                valid_sequences += 1
                expected_features = list(unique_lengths)[0]
                
        except Exception as e:
            print(f"Error parsing {row['video_file']}: {e}")
            continue
    
    print(f"\n=== Summary ===")
    print(f"Valid sequences: {valid_sequences}")
    print(f"Sequences with shape problems: {len(shape_problems)}")
    
    if shape_problems:
        print(f"\n=== Problem Details ===")
        for problem in shape_problems[:5]:  # Show first 5 problems
            print(f"Video: {problem['video']}")
            print(f"Gesture ID: {problem['gesture_id']}")
            print(f"Frame lengths found: {problem['unique_lengths']}")
            print("---")
    
    # Check what the expected feature dimension should be
    if valid_sequences > 0:
        # Get one valid sequence to check feature dimension
        for idx, row in df.iterrows():
            try:
                landmarks = ast.literal_eval(row['landmark_data'])
                frame_lengths = [len(frame) for frame in landmarks]
                if len(set(frame_lengths)) == 1:
                    expected_features = frame_lengths[0]
                    print(f"\nExpected feature dimension: {expected_features}")
                    print(f"Number of frames in this video: {len(landmarks)}")
                    break
            except:
                continue

if __name__ == "__main__":
    debug_landmark_shapes()