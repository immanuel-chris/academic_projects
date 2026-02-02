# File: 02_scripts/03_real_time_inference.py
import cv2
import mediapipe as mp
import numpy as np
import tensorflow as tf
from tensorflow import keras
import joblib
import os

# 1. Initialize MediaPipe Hands
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
)

# 2. Load the trained model and preprocessing objects
print("Loading trained model...")
models_dir = r"C:\Users\Admin\OneDrive\Documents\camAI_FSL_alphabet02\03_models"
model = keras.models.load_model(os.path.join(models_dir, 'fsl_classifier.h5'))
scaler = joblib.load(os.path.join(models_dir, 'scaler.pkl'))
label_encoder = joblib.load(os.path.join(models_dir, 'label_encoder.pkl'))

print("Model loaded successfully!")
print(f"Classes: {label_encoder.classes_}")

# 3. Initialize webcam
cap = cv2.VideoCapture(0)  # 0 for default camera

# Create a window and set it to a reasonable size
cv2.namedWindow('FSL Alphabet Recognition', cv2.WINDOW_NORMAL)
cv2.resizeWindow('FSL Alphabet Recognition', 800, 600)

print("\nReal-time FSL Alphabet Recognition Started!")
print("Press 'q' to quit")
print("Show your hand to the camera and make FSL alphabet signs!")

while True:
    # Read frame from webcam
    ret, frame = cap.read()
    if not ret:
        print("Failed to grab frame")
        break
    
    # Flip frame horizontally for mirror effect
    frame = cv2.flip(frame, 1)
    
    # Convert BGR to RGB for MediaPipe
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    
    # Process the frame with MediaPipe Hands
    results = hands.process(rgb_frame)
    
    predicted_letter = None
    confidence = 0.0
    
    # If hand landmarks are detected
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            # Draw the hand landmarks on the frame
            mp_drawing.draw_landmarks(
                frame, hand_landmarks, mp_hands.HAND_CONNECTIONS,
                mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=2, circle_radius=2),
                mp_drawing.DrawingSpec(color=(0, 0, 255), thickness=2)
            )
            
            # Extract landmarks
            landmarks = []
            for landmark in hand_landmarks.landmark:
                landmarks.extend([landmark.x, landmark.y, landmark.z])
            
            # Convert to numpy array and reshape
            landmarks_array = np.array(landmarks).reshape(1, -1)
            
            # Preprocess the landmarks (same as during training)
            landmarks_scaled = scaler.transform(landmarks_array)
            
            # Make prediction
            prediction = model.predict(landmarks_scaled, verbose=0)
            confidence = np.max(prediction)
            predicted_index = np.argmax(prediction)
            predicted_letter = label_encoder.inverse_transform([predicted_index])[0]
            
            # Draw bounding box around hand (approximate)
            h, w, _ = frame.shape
            x_coords = [landmark.x for landmark in hand_landmarks.landmark]
            y_coords = [landmark.y for landmark in hand_landmarks.landmark]
            
            x_min, x_max = int(min(x_coords) * w), int(max(x_coords) * w)
            y_min, y_max = int(min(y_coords) * h), int(max(y_coords) * h)
            
            # Draw bounding box
            cv2.rectangle(frame, (x_min, y_min), (x_max, y_max), (255, 0, 0), 2)
            
            # Only process the first detected hand
            break
    
    # Display the prediction and confidence
    if predicted_letter:
        # Create text with prediction and confidence
        text = f"Letter: {predicted_letter} ({confidence:.2%})"
        
        # Choose color based on confidence (green for high confidence, yellow for medium, red for low)
        if confidence > 0.8:
            color = (0, 255, 0)  # Green
        elif confidence > 0.6:
            color = (0, 255, 255)  # Yellow
        else:
            color = (0, 0, 255)  # Red
        
        # Put text on frame
        cv2.putText(frame, text, (50, 50), 
                   cv2.FONT_HERSHEY_SIMPLEX, 1, color, 2)
        
        # Add instruction
        cv2.putText(frame, "Show FSL alphabet signs to camera", (50, h - 30),
                   cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)
    else:
        # No hand detected
        cv2.putText(frame, "No hand detected", (50, 50),
                   cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        cv2.putText(frame, "Show your hand to the camera", (50, h - 30),
                   cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)
    
    # Display the frame
    cv2.imshow('FSL Alphabet Recognition', frame)
    
    # Break loop when 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Clean up
cap.release()
cv2.destroyAllWindows()
hands.close()
print("\nReal-time recognition stopped.")