# scripts/00_check_data.py

import os

BASE_DIR = "C:/Users/Admin/OneDrive/Documents/FSL_AI_p2"
CLIPS_DIR = os.path.join(BASE_DIR, "clips")

def check_clips_directory():
    """Check what gesture folders and videos exist"""
    print("=== Checking Clips Directory Structure ===")
    print(f"Directory: {CLIPS_DIR}")
    
    if not os.path.exists(CLIPS_DIR):
        print("ERROR: Clips directory doesn't exist!")
        return
    
    # Check for each gesture folder
    expected_gestures = [4, 5, 11, 14, 15]
    
    for gesture_id in expected_gestures:
        gesture_dir = os.path.join(CLIPS_DIR, str(gesture_id))
        if os.path.exists(gesture_dir):
            video_files = [f for f in os.listdir(gesture_dir) if f.endswith('.MOV')]
            print(f"Gesture {gesture_id}: {len(video_files)} videos")
            if video_files:
                print(f"  Sample files: {video_files[:3]}")  # Show first 3 files
        else:
            print(f"Gesture {gesture_id}: FOLDER NOT FOUND")
    
    # Also check for any unexpected folders
    print("\n=== All folders found ===")
    all_folders = [f for f in os.listdir(CLIPS_DIR) if os.path.isdir(os.path.join(CLIPS_DIR, f))]
    for folder in sorted(all_folders):
        if folder.isdigit():
            video_count = len([f for f in os.listdir(os.path.join(CLIPS_DIR, folder)) if f.endswith('.MOV')])
            print(f"Folder {folder}: {video_count} videos")

if __name__ == "__main__":
    check_clips_directory()