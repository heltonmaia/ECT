# Image classification using SVM

## Requirements

* An OpenCV library installation (version 3.3.0 is recommended).

* A clone of the repository.

* A g++ compiler installation (others compilers can be used but the script compileAll.sh need to be altered).

# Setting the environment

Once the repository is cloned, it's necessary:

* To give execution permission and execute the compilation script:

```bash
chmod +x compileAll.sh
./compileAll.sh
```

* To create the directories where the results are going to be stored:

```bash
mkdir ymls ymls/hog ymls/edges
```

# Usage

## Usage of the HOG descriptor

```bash
# Creates the hog descriptor for each image in the dataset
./hog
# Trains the SVM with the training dataset descriptors
./train hog
# Tests the SVM with the test dataset
./test hog
```

## Usage of the Edges descriptor

```bash
# Creates the edge descriptor for each image in the dataset
./edges
# Trains the SVM with the training dataset descriptors
./train edges
# Tests the SVM with the test dataset
./test edges
```