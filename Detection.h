#pragma once
#include <iostream>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "CommonProcesses.h"

using namespace cv;
using namespace std;

/// Enumeration to define types of features
enum class FeatureType { Corners, Lines }; 

/// Detection class inheriting from CommonProcesses
/// Handles common detection operations for image features like corners and lines
class Detection : public CommonProcesses {
public:
    /// Constructor
    /// @param filePath The file path of the image to process.
    /// @param fileName The name of the image file.
    /// @param scale The scale factor for resizing.
    Detection(const string& filePath, const string& fileName, double& scale);

    /// Destructor
    virtual ~Detection();

    /// Pure virtual function for feature detection
    virtual void detectFeatures() = 0;

    /// Display detected features in a window
    /// @param windowName The name of the window to display.
    /// @param type The type of features to display (Corners or Lines).
    void displayFeatures(const string& windowName, FeatureType type);

    /// Save detected features to a file
    /// @param fileName The name of the file to save the features.
    void saveFeatures(const string& fileName);

    /// Log a message to the console
    /// @param message The message to log.
    void logMessage(const string& message);

    /// Create an adjustable window for edge map adjustment
    void createAdjustableEdgeMap();

    /// Create an adjustable edge map with initial values
    /// @param initialThreshold The initial threshold value for the edge map.
    /// @param maxThreshold The maximum threshold value for the edge map
    void createAdjustableEdgeMap(int initialThreshold, int maxThreshold);

    /// Update the edge map based on the current threshold values
    void updateEdgeMap();

    /// Set corner features
    /// @param local A vector of points representing corner features.
    void setCornerFeatures(vector<Point> local);

    /// Set line features
    /// @param local A vector of Vec4i representing line features.
    void setLineFeatures(vector<Vec4i> local);

    /// Overload operator+= to add corner points
    /// @param corner A point representing a detected corner.
    Detection& operator+=(const Point& corner);

    //Detection& operator+=(const Vec4i& line);

    /// Get corner features
    /// @return A vector of points representing detected corner features.
    vector<Point> getCornerFeatures(void) const;

    /// Get the count of detected corners
    /// @return The number of detected corners.
    int getCornerCount(void) const;

    /// Get the count of detected lines
    /// @return The number of detected lines.
    int getLineCount(void) const;


private:

    vector<Point> cornerFeatures;           ///< Vector to store detected corner features
    vector<Vec4i> lineFeatures;             ///< Vector to store detected line features
    Mat edgeImage;                          ///< Mat object to store edge detection image
    int threshold;                          ///< Threshold value for edge detection
    int maxThreshold;                       ///< Maximum threshold value for edge detection
};
