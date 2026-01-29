# File: 02_scripts/02_train_model.py
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from tensorflow import keras
from tensorflow.keras import layers
import joblib
import os

# 1. Load the processed dataset
print("Loading dataset...")
csv_path = r"C:\Users\Admin\OneDrive\Documents\camAI_FSL_alphabet02\01_data\fsl_landmarks_dataset.csv"
df = pd.read_csv(csv_path)

# 2. Prepare the data
# Separate features (landmarks) and labels (letters)
X = df.drop('label', axis=1)  # All columns except 'label'
y = df['label']               # Only the 'label' column

print(f"Dataset shape: {X.shape}")
print(f"Number of classes: {len(y.unique())}")
print(f"Classes: {sorted(y.unique())}")

# 3. Encode labels (convert letters to numbers: A=0, B=1, ...)
label_encoder = LabelEncoder()
y_encoded = label_encoder.fit_transform(y)

print(f"Label mapping: {dict(zip(label_encoder.classes_, label_encoder.transform(label_encoder.classes_)))}")

# 4. Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(
    X, y_encoded, test_size=0.2, random_state=42, stratify=y_encoded
)

print(f"Training set size: {X_train.shape[0]}")
print(f"Testing set size: {X_test.shape[0]}")

# 5. Normalize the feature data (important for neural networks)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 6. Build the neural network model
model = keras.Sequential([
    layers.Dense(128, activation='relu', input_shape=(X_train.shape[1],)),
    layers.Dropout(0.3),  # Helps prevent overfitting
    layers.Dense(64, activation='relu'),
    layers.Dropout(0.3),
    layers.Dense(32, activation='relu'),
    layers.Dense(len(label_encoder.classes_), activation='softmax')  # Output layer
])

# 7. Compile the model
model.compile(
    optimizer='adam',
    loss='sparse_categorical_crossentropy',
    metrics=['accuracy']
)

# Print model summary
print("\nModel architecture:")
model.summary()

# 8. Train the model
print("\nStarting training...")
history = model.fit(
    X_train_scaled, y_train,
    epochs=50,
    batch_size=32,
    validation_data=(X_test_scaled, y_test),
    verbose=1
)

# 9. Evaluate the model on test data
print("\nEvaluating on test data...")
test_loss, test_accuracy = model.evaluate(X_test_scaled, y_test, verbose=0)
print(f"Test Accuracy: {test_accuracy:.4f} ({test_accuracy*100:.2f}%)")

# 10. Save the trained model and preprocessing objects
print("\nSaving model and preprocessing objects...")

# Create models directory if it doesn't exist
models_dir = r"C:\Users\Admin\OneDrive\Documents\camAI_FSL_alphabet02\03_models"
os.makedirs(models_dir, exist_ok=True)

# Save the model
model.save(os.path.join(models_dir, 'fsl_classifier.h5'))

# Save the preprocessing objects (for use in real-time inference)
joblib.dump(scaler, os.path.join(models_dir, 'scaler.pkl'))
joblib.dump(label_encoder, os.path.join(models_dir, 'label_encoder.pkl'))

print("Model and preprocessing objects saved successfully!")
print(f"Files saved in: {models_dir}")

# 11. Plot training history (optional - requires matplotlib)
try:
    import matplotlib.pyplot as plt
    
    plt.figure(figsize=(12, 4))
    
    # Plot accuracy
    plt.subplot(1, 2, 1)
    plt.plot(history.history['accuracy'], label='Training Accuracy')
    plt.plot(history.history['val_accuracy'], label='Validation Accuracy')
    plt.title('Model Accuracy')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()
    
    # Plot loss
    plt.subplot(1, 2, 2)
    plt.plot(history.history['loss'], label='Training Loss')
    plt.plot(history.history['val_loss'], label='Validation Loss')
    plt.title('Model Loss')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()
    
    plt.tight_layout()
    plt.savefig(os.path.join(models_dir, 'training_history.png'))
    print("Training history plot saved!")
    
except ImportError:
    print("Matplotlib not installed. Skipping plot generation.")

print("\nTraining completed successfully!")