# File: 02_scripts/inspect_dataset.py
import os
from collections import Counter
import cv2

# 1. Path to your dataset
dataset_path = r"C:\Users\Admin\OneDrive\Documents\camAI_FSL_alphabet02\01_data\FSL_alphabet_dataset"

# 2. Let's count the number of images per class
print("Counting images per class...")
class_counts = {}
for class_name in os.listdir(dataset_path):
    class_dir = os.path.join(dataset_path, class_name)
    if os.path.isdir(class_dir):
        num_images = len([f for f in os.listdir(class_dir) if f.endswith(('.png', '.jpg', '.jpeg'))])
        class_counts[class_name] = num_images
        print(f"Class {class_name}: {num_images} images")

# 3. Let's check the image dimensions
print("\nChecking image dimensions...")
dimensions = []
for class_name in os.listdir(dataset_path):
    class_dir = os.path.join(dataset_path, class_name)
    if os.path.isdir(class_dir):
        for image_name in os.listdir(class_dir):
            if image_name.lower().endswith(('.png', '.jpg', '.jpeg')):
                image_path = os.path.join(class_dir, image_name)
                img = cv2.imread(image_path)
                if img is not None:
                    h, w, c = img.shape
                    dimensions.append((w, h)) # (width, height)

# Show some stats about dimensions
dimension_counts = Counter(dimensions)
print(f"\nFound {len(dimension_counts)} unique image dimensions.")
print("Most common dimensions:")
for dim, count in dimension_counts.most_common(5):
    print(f"  {dim}: {count} times")

# 4. Let's display a sample image from one class
print("\nLet's display a sample image. Close the image window to continue.")
sample_class = list(class_counts.keys())[0] # Get the first class
sample_class_dir = os.path.join(dataset_path, sample_class)
sample_image_name = os.listdir(sample_class_dir)[0]
sample_image_path = os.path.join(sample_class_dir, sample_image_name)

img = cv2.imread(sample_image_path)
print(f"Sample image from class '{sample_class}': {sample_image_path}")
print(f"Its dimensions are: {img.shape[1]} x {img.shape[0]}") # width x height

cv2.imshow('Sample Image', img)
cv2.waitKey(0) # Wait for a key press to close the window
cv2.destroyAllWindows()