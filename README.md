# FinalProject Documentation

Name : Dogukan Avci
Date: 22.12.2024

## Project Overview
Welcome to the **FinalProject**, an advanced image feature detection framework implemented in **C++**. This project utilizes **OpenCV** for powerful image processing and detection capabilities, providing a modular architecture designed to demonstrate object-oriented programming (**OOP**) principles.

The framework is ideal for:
- Learning and applying modern C++ concepts such as inheritance and polymorphism.
- Exploring advanced computer vision techniques.
- Extending or integrating with other vision-based systems for research or development.

---

## Key Features
### Detection Framework
- A base class, `Detection`, serves as the foundation for feature detection with modular extensibility.
- Derived classes (`LineDetection` and `CornerDetection`) implement specialized algorithms for detecting lines and corners in images.

### Line Detection
- Implements:
  - **Canny Edge Detection**: Extracts edges in images with adjustable thresholds.
  - **HoughLinesP**: Detects lines from edges using a probabilistic Hough Transform.
- Features:
  - Dynamic threshold adjustment for real-time results.
  - Noise filtering with Gaussian and Median filters.

### Corner Detection
- Implements:
  - **Harris Corner Detection**: Identifies corners in images using the Harris algorithm.
  - **Normalization**: Scales corner intensity values for better visualization.
- Features:
  - Adjustable quality levels for corner sensitivity.
  - Detection of high-intensity corners in grayscale images.

### Modular and Extensible Design
- Easily extend the framework with additional detection algorithms.
- Designed to accommodate various image processing tasks with minimal effort.

---

## Technical Details
### Programming Concepts
- **Inheritance and Polymorphism**:
  - `Detection` is a base class with a pure virtual method `detectFeatures()` for feature detection.
  - Derived classes (`LineDetection` and `CornerDetection`) override this method to implement their specific algorithms.
- **Composition**:
  - `Detection` owns `cornerFeatures` and `lineFeatures` as `std::vector` objects to store detected features.

### OpenCV Integration
- Utilizes the following OpenCV functions:
  - `Canny`: For edge detection.
  - `HoughLinesP`: For line detection.
  - `cornerHarris`: For corner detection.
  - `normalize`: For normalizing image intensity values.

---

## Project Structure
```plaintext
src/
- Detection.h      # Base class for feature detection
- LineDetection.h  # Class for detecting lines
- CornerDetection.h# Class for detecting corners
- CommonProcesses.h# Common image processing utilities
- main.cpp         # Main program entry point



- **Key Points**:
  - **Detection** is the base class and utilizes composition for `cornerFeatures` and `lineFeatures`.
  - **LineDetection** and **CornerDetection** inherit from `Detection` and override specific behaviors.


### How Canny Edge Detection Works
- Step 1: Noise reduction using Gaussian filter.
- Step 2: Intensity gradient calculation.
- Step 3: Non-maximum suppression to retain edge pixels.
- Step 4: Double thresholding to detect strong and weak edges.
- Step 5: Edge tracking by hysteresis to finalize edges.
