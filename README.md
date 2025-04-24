# image-preprocessing-study
# Image Classification Performance: Impact of Preprocessing and Augmentation

## Goal

To investigate and quantify the impact of common image preprocessing (pixel normalization) and data augmentation techniques (specifically random horizontal flips and random rotations) on the classification accuracy of a simple Convolutional Neural Network (CNN) trained on the MNIST dataset.

## Dataset

* **Initial Dataset:** MNIST Handwritten Digits Dataset
    * **Source:** Commonly available via libraries like TensorFlow/Keras datasets, or downloadable from sources like Kaggle or Yann LeCun's website.
    * **Description:** Grayscale images of handwritten digits (0-9), size 28x28 pixels. Contains 60,000 training images and 10,000 testing images.

## Planned Steps / Methodology

1.  **Data Loading & Exploration:** Load the MNIST dataset. Explore its structure, dimensions, and visualize sample images.
2.  **Baseline Preparation:** Implement minimal preprocessing (e.g., reshaping arrays, scaling pixel values to [0, 1]). Split data into training, validation, and testing sets.
3.  **Baseline Model:** Build and train a simple Convolutional Neural Network (CNN) architecture using TensorFlow/Keras on the minimally processed training data. Evaluate its performance (accuracy, loss) on the test set.
4.  **Preprocessing/Augmentation Implementation:**
    * Implement pixel value normalization (if different from baseline).
    * Implement random horizontal flips for the training data.
    * Implement random rotations (e.g., within a small degree range like 10 degrees) for the training data.
5.  **Augmented Model Training:** Train the *exact same* CNN architecture using the training data with the specified augmentation techniques applied. Evaluate performance on the *same* test set.
6.  **Comparison & Analysis:** Compare performance metrics (accuracy, loss curves on validation/test sets) between the baseline model and the model trained with augmented data.
7.  **Documentation:** Document the process, code, results, and conclusions clearly in this repository and potentially Jupyter Notebooks.

## Technologies / Libraries Planned

* **Language:** Python 3.x
* **Core Libraries:**
    * NumPy: For numerical operations and handling image arrays.
    * Pandas: For organizing and potentially saving experiment results.
    * Matplotlib: For visualizing images and plotting results (e.g., accuracy/loss curves).
    * TensorFlow / Keras: For building, training, and evaluating the CNN model, and implementing data augmentation.
    * PIL (Pillow) / OpenCV: For basic image loading/manipulation if needed outside TensorFlow/Keras pipeline.
* **Version Control:** Git / GitHub

---

*(This README will be updated as the project progresses with Installation instructions, Usage examples, detailed Results, and Future Work sections.)*