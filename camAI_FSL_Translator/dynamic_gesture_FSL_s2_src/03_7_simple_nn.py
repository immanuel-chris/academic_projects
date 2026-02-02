# scripts/04_real_time_inference.py

import os
import cv2
import numpy as np
import mediapipe as mp
import joblib
import pickle
from collections import deque

# Path configuration
BASE_DIR = "C:/Users/Admin/OneDrive/Documents/FSL_AI"
MODEL_PATH = os.path.join(BASE_DIR, "models", "traditional", "best_traditional_model.joblib")
FEATURE_INFO_PATH = os.path.join(BASE_DIR, "models", "traditional", "feature_info.pkl")

# Initialize MediaPipe Hands
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils

class GestureRecognizer:
    def __init__(self, model_path, feature_info_path):
        """Initialize the gesture recognizer with trained model"""
        # Load the trained model and feature info
        self.model = joblib.load(model_path)
        with open(feature_info_path, 'rb') as f:
            feature_info = pickle.load(f)
        
        self.label_encoder = feature_info['label_encoder']
        self.feature_dimension = feature_info['feature_dimension']
        
        # Buffer to store recent frames for gesture recognition
        self.frame_buffer = deque(maxlen=244)  # Same as our sequence length
        self.prediction_buffer = deque(maxlen=5)  # Smooth predictions
        
        # Gesture labels mapping (from your labels.csv)
        self.gesture_labels = {
            0: "GOOD MORNING",
            1: "GOOD AFTERNOON", 
            3: "HELLO",
            7: "THANK YOU",
            10: "UNDERSTAND",
            13: "DON'T KNOW"
        }
        
        # Recording state
        self.is_recording = False
        self.recorded_sequence = []
        self.last_prediction = None
        self.last_confidence = 0.0
        
        print("Gesture Recognizer initialized!")
        print(f"Loaded classes: {[self.gesture_labels[cls] for cls in self.label_encoder.classes_]}")
    
    def extract_landmarks_from_frame(self, frame, hands_model):
        """Extract hand landmarks from a single frame"""
        # Convert BGR to RGB
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        rgb_frame.flags.writeable = False
        
        # Process the frame
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
        
        return frame_landmarks
    
    def extract_features_from_sequence(self, sequence):
        """Extract features from a sequence (same as during training)"""
        seq_array = np.array(sequence)
        features = []
        
        # Basic statistics for each feature dimension
        for dim in range(seq_array.shape[1]):
            feature_dim = seq_array[:, dim]
            features.extend([
                np.mean(feature_dim),      # Mean
                np.std(feature_dim),       # Standard deviation
                np.min(feature_dim),       # Minimum
                np.max(feature_dim),       # Maximum
                np.median(feature_dim),    # Median
            ])
        
        # Global statistics
        features.extend([
            np.mean(seq_array),           # Global mean
            np.std(seq_array),            # Global std
        ])
        
        # Motion features (changes between frames)
        if len(seq_array) > 1:
            motion = np.diff(seq_array, axis=0)
            features.extend([
                np.mean(motion),          # Average motion
                np.std(motion),           # Motion variability
            ])
        else:
            features.extend([0, 0])
        
        return np.array(features)
    
    def start_recording(self):
        """Start recording a new gesture sequence"""
        self.is_recording = True
        self.recorded_sequence = []
        print("Started recording gesture...")
    
    def stop_recording_and_predict(self):
        """Stop recording and predict the gesture"""
        if len(self.recorded_sequence) < 244:
            print(f"Not enough frames recorded: {len(self.recorded_sequence)}/244")
            self.is_recording = False
            return
        
        self.is_recording = False
        print(f"Recording stopped. Processing {len(self.recorded_sequence)} frames...")
        
        # Extract features and predict
        sequence = np.array(self.recorded_sequence)
        features = self.extract_features_from_sequence(sequence)
        features = features.reshape(1, -1)
        
        # Predict
        prediction = self.model.predict(features)[0]
        probability = np.max(self.model.predict_proba(features))
        
        # Convert back to original label
        gesture_id = self.label_encoder.inverse_transform([prediction])[0]
        gesture_name = self.gesture_labels.get(gesture_id, "UNKNOWN")
        
        # Store the result
        self.last_prediction = gesture_name
        self.last_confidence = probability
        self.prediction_buffer.append(gesture_name)
        
        print(f"Prediction: {gesture_name} (Confidence: {probability:.2f})")
    
    def run_real_time_detection(self):
        """Run real-time gesture detection from webcam with space bar trigger"""
        print("Starting real-time gesture recognition...")
        print("=== CONTROLS ===")
        print("SPACE BAR: Start/Stop recording (4-second gesture)")
        print("'c': Clear last prediction")
        print("'q': Quit application")
        print("=================")
        
        cap = cv2.VideoCapture(0)
        
        with mp_hands.Hands(
            static_image_mode=False,
            max_num_hands=2,
            min_detection_confidence=0.5,
            min_tracking_confidence=0.5) as hands:
            
            while cap.isOpened():
                ret, frame = cap.read()
                if not ret:
                    break
                
                # Get frame dimensions
                h, w = frame.shape[:2]
                
                # Flip frame horizontally for mirror effect
                frame = cv2.flip(frame, 1)
                
                # Extract landmarks from current frame
                landmarks = self.extract_landmarks_from_frame(frame, hands)
                
                # Always maintain frame buffer for continuous display
                self.frame_buffer.append(landmarks)
                
                # If recording, add to recorded sequence
                if self.is_recording:
                    self.recorded_sequence.append(landmarks)
                
                # Draw hand landmarks on frame
                rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                results = hands.process(rgb_frame)
                if results.multi_hand_landmarks:
                    for hand_landmarks in results.multi_hand_landmarks:
                        mp_drawing.draw_landmarks(
                            frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)
                
                # Display UI elements
                buffer_percentage = min(100, len(self.frame_buffer) / 244 * 100)
                recording_percentage = min(100, len(self.recorded_sequence) / 244 * 100) if self.is_recording else 0
                
                # Display recording status
                if self.is_recording:
                    status_color = (0, 0, 255)  # Red
                    status_text = f"RECORDING: {recording_percentage:.1f}%"
                    # Draw countdown/progress bar
                    cv2.rectangle(frame, (10, h - 60), (w - 10, h - 40), (50, 50, 50), -1)
                    cv2.rectangle(frame, (10, h - 60), (10 + int((w - 20) * recording_percentage / 100), h - 40), (0, 0, 255), -1)
                else:
                    status_color = (0, 255, 0)  # Green
                    status_text = "READY - Press SPACE to record gesture"
                
                cv2.putText(frame, status_text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, status_color, 2)
                
                # Display last prediction
                if self.last_prediction:
                    confidence_color = (0, 255, 0) if self.last_confidence > 0.7 else (0, 255, 255) if self.last_confidence > 0.5 else (0, 165, 255)
                    cv2.putText(frame, f"Gesture: {self.last_prediction}", 
                              (10, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, confidence_color, 2)
                    cv2.putText(frame, f"Confidence: {self.last_confidence:.2f}", 
                              (10, 110), cv2.FONT_HERSHEY_SIMPLEX, 0.7, confidence_color, 2)
                
                # Display available gestures
                y_offset = 150
                cv2.putText(frame, "Available gestures:", (10, y_offset), 
                          cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1)
                for i, gesture in enumerate(self.gesture_labels.values()):
                    cv2.putText(frame, f"- {gesture}", (20, y_offset + 25 + i*20), 
                              cv2.FONT_HERSHEY_SIMPLEX, 0.4, (255, 255, 255), 1)
                
                # Display controls
                controls_y = h - 100
                cv2.putText(frame, "Controls: SPACE=Record, c=Clear, q=Quit", 
                          (10, controls_y), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1)
                
                # Show frame
                cv2.imshow('FSL Gesture Recognition', frame)
                
                # Handle keyboard input
                key = cv2.waitKey(1) & 0xFF
                if key == ord(' '):  # Space bar
                    if not self.is_recording:
                        # Start recording
                        self.start_recording()
                    else:
                        # Stop recording and predict
                        self.stop_recording_and_predict()
                
                elif key == ord('c'):  # Clear prediction
                    self.last_prediction = None
                    self.last_confidence = 0.0
                    self.prediction_buffer.clear()
                    print("Prediction cleared.")
                
                elif key == ord('q'):  # Quit
                    break
        
        cap.release()
        cv2.destroyAllWindows()

def main():
    try:
        # Initialize gesture recognizer
        print("Loading gesture recognizer...")
        recognizer = GestureRecognizer(MODEL_PATH, FEATURE_INFO_PATH)
        
        # Start real-time detection
        recognizer.run_real_time_detection()
    
    except Exception as e:
        print(f"Error: {e}")
        print("Make sure you have a webcam connected and the model files exist.")
        print(f"Model path: {MODEL_PATH}")
        print(f"Feature info path: {FEATURE_INFO_PATH}")

if __name__ == "__main__":
    main()