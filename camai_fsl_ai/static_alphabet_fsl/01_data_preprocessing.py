# File: 02_scripts/01_data_preprocessing.py
import os
import cv2
import mediapipe as mp
import pandas as pd
import numpy as np

# Initialize MediaPipe Hands model
# We use 'static_image_mode=True' because we are processing a folder of static images.
# 'max_num_hands=1' because we expect one hand per image for sign language alphabet.
# 'min_detection_confidence=0.5' is a threshold for considering the hand detection as successful.
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils  # Optional, for drawing landmarks
hands = mp_hands.Hands(static_image_mode=True, max_num_hands=1, min_detection_confidence=0.5)

# 1. Define Paths
dataset_path = r"C:\Users\Admin\OneDrive\Documents\camAI_FSL_alphabet02\01_data\FSL_alphabet_dataset"
output_csv_path = r"C:\Users\Admin\OneDrive\Documents\camAI_FSL_alphabet02\01_data\fsl_landmarks_dataset.csv"

# 2. List to store our data for the CSV file
data = []

# 3. Loop through each class folder (A, B, C, ...)
for class_name in os.listdir(dataset_path):
    class_dir = os.path.join(dataset_path, class_name)
    
    # Check if it's actually a directory (like A/, B/, not a file)
    if not os.path.isdir(class_dir):
        continue
        
    print(f"Processing class: {class_name}")
    
    # Loop through each image in the class folder
    for image_name in os.listdir(class_dir):
        image_path = os.path.join(class_dir, image_name)
        
        # Check if the file is an image
        if not image_name.lower().endswith(('.png', '.jpg', '.jpeg')):
            continue
            
        # Read the image
        img = cv2.imread(image_path)
        # MediaPipe expects RGB images, but OpenCV reads as BGR. So we convert.
        img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        
        # Process the image with MediaPipe Hands
        results = hands.process(img_rgb)
        
        # Check if any hand landmarks were detected
        if results.multi_hand_landmarks:
            # We assume the first detected hand is the one we want (since max_num_hands=1)
            hand_landmarks = results.multi_hand_landmarks[0]
            
            # Extract the x, y, z coordinates of each of the 21 landmarks
            landmarks_list = []
            for landmark in hand_landmarks.landmark:
                landmarks_list.extend([landmark.x, landmark.y, landmark.z])
                # We use relative coordinates (x, y, z) which are normalized [0, 1].
                # This is better than pixel coordinates as it's size-invariant.
            
            # Append the data: first the landmarks, then the class label
            data.append(landmarks_list + [class_name])
            
        else:
            # If no landmarks are detected, we skip this image and print a warning.
            print(f"  No hand detected in: {image_path}. Skipping.")

# 4. After processing all images, close the MediaPipe model.
hands.close()

# 5. Convert the data list into a Pandas DataFrame
# First, let's create the column names: 'x1', 'y1', 'z1', ... 'x21', 'y21', 'z21', 'label'
landmark_columns = []
for i in range(1, 22): # for 21 landmarks
    landmark_columns.extend([f'x{i}', f'y{i}', f'z{i}'])
columns = landmark_columns + ['label']

df = pd.DataFrame(data, columns=columns)

# 6. Save the DataFrame to a CSV file
df.to_csv(output_csv_path, index=False)
print(f"\nProcessing complete!")
print(f"Successfully processed {len(df)} images.")
print(f"Landmarks saved to: {output_csv_path}")

# 7. Let's print a sample of the data to verify
print("\nFirst 5 rows of the generated dataset:")
print(df.head())