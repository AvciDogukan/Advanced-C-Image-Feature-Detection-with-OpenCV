#include "LineDetection.h"

/**
 * @brief Constructor for LineDetection class.
 *
 * @param filePath The file path of the input image.
 * @param fileName The name of the input image file.
 * @param scale The scaling factor for resizing the image.
 */
LineDetection::LineDetection(const string& filePath, const string& fileName, double& scale)
    : Detection(filePath, fileName, scale), lowThresHold(50) {
    logMessage("Constructor Created for LineDetection");
}

/**
 * @brief Destructor for LineDetection class.
 */
LineDetection::~LineDetection() {
    logMessage("Destructor Called for LineDetection");
}

/**
 * @brief Detects lines in the image using the Canny edge detector and the Hough Transform algorithm.
 *
 * - Applies Canny edge detection to detect edges in the image.
 * - Uses the HoughLinesP function to detect lines based on the detected edges.
 * - Stores the detected lines in the line features.
 */
void LineDetection::detectFeatures() {
    Canny(getImage(), detectedEdges, lowThresHold, lowThresHold * 3);
    vector<Vec4i> detectedLines;
    HoughLinesP(detectedEdges, detectedLines, 1, CV_PI / 180, 50, 50, 10);

    setLineFeatures(detectedLines); // Store line features
    logMessage("Lines detected and stored in lineFeatures.");
}

/**
 * @brief Processes line detection with default settings.
 *
 * - Displays the raw image.
 * - Converts the image to grayscale.
 * - Detects features (lines) in the image.
 * - Saves the detected features to a file.
 * - Displays the detected lines on the image.
 * - Creates an adjustable edge map window for visualization.
 */
void LineDetection::processLineDetection() {
    showImage("Raw Image",getImage());  // Show raw image
    convertToGrayScale(getImage());     // Convert to grayscale
    showImage("GrayScale", getImage()); // Show grayscale image

    if (getScaleFactor() != 1.0)
    {
        rescaleImage(getImage());           // Rescale the image
        showImage("Resized", getImage());   // Show resized image
    }

    detectFeatures();                   // Detect lines
    saveFeatures("Lines.txt");          // Save lines to file
    displayFeatures("Detected Lines", FeatureType::Lines); // Display detected lines
    createAdjustableEdgeMap();          // Create adjustable window for edge map
   
}

/**
 * @brief Processes line detection with optional filtering.
 *
 * - Displays the raw image.
 * - Converts the image to grayscale.
 * - Rescales the image based on the scale factor.
 * - Applies either Gaussian or Median noise filtering based on user choice.
 * - Detects features (lines) in the filtered image.
 * - Saves the detected features to a file.
 * - Displays the detected lines on the image.
 * - Creates an adjustable edge map window for visualization.
 *
 * @param filter If true, applies Gaussian filtering. Otherwise, applies Median filtering.
 */
void LineDetection::processLineDetection(bool filter) {


    showImage("Raw Image", getImage());     // Show raw image
    convertToGrayScale(getImage());         // Convert to grayscale
    showImage("GrayScale", getImage());     // Show grayscale image


    if (getScaleFactor() != 1.0)
    {
        rescaleImage(getImage());           // Rescale the image
        showImage("Resized", getImage());   // Show resized image
    }
                  
        
    
    // Apply selected filter
    if (filter)
    {
        filterNoiseGaus(getImage());
    }
    else
        filterNoiseMedian(getImage());

    showImage("Filtered", getImage());  // Show filtered image
    detectFeatures();                   // Detect lines
    saveFeatures("LinesFiltered.txt");  // Save filtered lines to file
    displayFeatures("Detected Corners", FeatureType::Lines);  // Display detected lines
    createAdjustableEdgeMap();          // Create adjustable window for edge map
  

}
