# scripts/03_7_simple_nn.py

import os
import pickle
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
from tensorflow.keras.optimizers import Adam
import matplotlib.pyplot as plt

# Path configuration
BASE_DIR = "C:/Users/Admin/OneDrive/Documents/FSL_AI"
DATASET_PATH = os.path.join(BASE_DIR, "data", "dataset", "processed_dataset.pkl")

def create_simple_nn(input_dim, num_classes):
    """Create a very simple neural network"""
    model = Sequential([
        Dense(64, activation='relu', input_shape=(input_dim,)),
        Dropout(0.3),
        Dense(32, activation='relu'),
        Dropout(0.3),
        Dense(num_classes, activation='softmax')
    ])
    
    model.compile(
        optimizer=Adam(learning_rate=0.001),
        loss='categorical_crossentropy',
        metrics=['accuracy']
    )
    
    return model

def extract_simple_features(X):
    """Extract simple features by averaging over time"""
    return np.mean(X, axis=1)  # Average across time dimension

def train_simple_nn():
    print("=== Simple Neural Network Approach ===")
    
    # Load data
    with open(DATASET_PATH, 'rb') as f:
        dataset = pickle.load(f)
    
    X_train = dataset['X_train']
    X_test = dataset['X_test']
    y_train = dataset['y_train']
    y_test = dataset['y_test']
    
    # Extract simple features (average over time)
    X_train_simple = extract_simple_features(X_train)
    X_test_simple = extract_simple_features(X_test)
    
    print(f"Simple features shape: {X_train_simple.shape}")
    
    # Create and train simple model
    model = create_simple_nn(X_train_simple.shape[1], y_train.shape[1])
    
    history = model.fit(
        X_train_simple, y_train,
        validation_data=(X_test_simple, y_test),
        epochs=100,
        batch_size=8,
        verbose=1
    )
    
    # Evaluate
    train_loss, train_acc = model.evaluate(X_train_simple, y_train, verbose=0)
    test_loss, test_acc = model.evaluate(X_test_simple, y_test, verbose=0)
    
    print(f"Simple NN - Train Accuracy: {train_acc:.4f}, Test Accuracy: {test_acc:.4f}")
    
    return test_acc

if __name__ == "__main__":
    train_simple_nn()