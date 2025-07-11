#include "CornerDetection.h"

/**
 * @brief Constructor for the CornerDetection class.
 *
 * Initializes the CornerDetection object with the specified image file path, file name, and scaling factor.
 *
 * @param filePath The file path of the image.
 * @param fileName The name of the image file.
 * @param scale The scaling factor for resizing the image.
 */
CornerDetection::CornerDetection(const string& filePath, const string& fileName, double& scale)
    : Detection(filePath, fileName, scale), qualityLevel(50) {
    logMessage("Constructor Created for CornerDetection");
}

/**
 * @brief Destructor for the CornerDetection class.
 *
 * Logs a message indicating that the object is being destroyed.
 */
CornerDetection::~CornerDetection() {
    logMessage("Destructor Called for CornerDetection");
}

/**
 * @brief Detects corners in the image using the Harris corner detection algorithm.
 *
 * Corners detected are stored in the corner features vector.
 */
void CornerDetection::detectFeatures() {
    Mat dst;
    cornerHarris(getImage(), dst, 2, 3, 0.04);
    Mat dstNormalized;
    normalize(dst, dstNormalized, 0, 255, NORM_MINMAX);

    vector<Point> localFeatures = getCornerFeatures();

    localFeatures.clear();
    for (int y = 0; y < dstNormalized.rows; y++) {
        for (int x = 0; x < dstNormalized.cols; x++) {
            if ((int)dstNormalized.at<float>(y, x) > qualityLevel) {
                localFeatures.emplace_back(Point(x, y));
                //*this += Point(x, y);

            }
        }
    }
    setCornerFeatures(localFeatures);

    logMessage("Corners detected and stored in features.");
}

/**
 * @brief Processes corner detection with default settings.
 *
 * This function converts the image to grayscale, detects corners,
 * saves the detected corners to a file, and displays the results.
 */
void CornerDetection::processCornerDetection() {
    showImage("Raw Image", getImage());
    convertToGrayScale(getImage());     // Convert to grayscale


    if (getScaleFactor() != 1.0)
    {
        rescaleImage(getImage());           // Rescale the image
        showImage("Resized", getImage());   // Show resized image
    }

    detectFeatures();                   // Detect corners
    saveFeatures("Corners.txt");        // Save corners to a file
    displayFeatures("Detected Corners", FeatureType::Corners); // Display corners
    // Ayarlamalý pencere
   
}

/**
 * @brief Processes corner detection with an optional noise reduction filter.
 *
 * Allows the user to choose between Gaussian and Median filters for noise reduction.
 *
 * @param filter If true, applies a Gaussian filter; otherwise, applies a Median filter.
 */
void CornerDetection::processCornerDetection(bool filter) {
    
    
    showImage("Raw Image", getImage());
    convertToGrayScale(getImage());
    showImage("GrayScale", getImage());
   
    // Apply the selected filter
    if (filter)
    {
        filterNoiseGaus(getImage());
    }
    else
        filterNoiseMedian(getImage());
    
    
    
    showImage("Filtered",getImage());
        
    detectFeatures();                   // Detect corners
    saveFeatures("CornersFiltered.txt");        // Save corners to a file
    displayFeatures("Detected Corners", FeatureType::Corners); // Display corners
}

/**
 * @brief Overloaded operator+= to add a corner point to the detected corner features.
 *
 * @param corner The Point object representing a detected corner.
 * @return Reference to the updated CornerDetection object.
 */
