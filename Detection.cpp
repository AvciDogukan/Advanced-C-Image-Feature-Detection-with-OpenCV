#include "Detection.h"

/**
 * @brief Constructor for Detection class.
 *
 * @param filePath The file path of the input image.
 * @param fileName The name of the input image file.
 * @param scale The scaling factor for resizing the image.
 */
Detection::Detection(const string& filePath, const string& fileName, double& scale)
    : CommonProcesses(filePath, fileName, scale), threshold(100), maxThreshold(255) {
    logMessage("Constructor Created for Detection");
}

/**
 * @brief Destructor for Detection class.
 */
Detection::~Detection() {
    logMessage("Destructor Called for Detection");
}

/**
 * @brief Logs a message to the console.
 *
 * @param message The message to be logged.
 */
void Detection::logMessage(const string& message) {
    cout << message << endl;
}

/**
 * @brief Displays detected features (corners or lines) on the image.
 *
 * @param windowName The name of the window to display the image.
 * @param type The type of feature to display (corners or lines).
 */
void Detection::displayFeatures(const string& windowName, FeatureType type) {
    Mat displayImage = getImage().clone();

    if (type == FeatureType::Corners) {
        for (const auto& feature : cornerFeatures) {
            circle(displayImage, feature, 5, Scalar(0, 255, 0), 2); // Green points
        }

        string cornerCountText = "Corners Detected: " + to_string(getCornerCount());
        putText(displayImage, cornerCountText, Point(10, displayImage.rows - 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
        logMessage(cornerCountText);
    }
    else if (type == FeatureType::Lines) {
        for (const auto& lline : lineFeatures) {
            Point pt1(lline[0], lline[1]);
            Point pt2(lline[2], lline[3]);
            line(displayImage, pt1, pt2, Scalar(255, 0, 0), 2); // Blue lines
        }
        string lineCountText = "Edges Detected: " + to_string(getLineCount());
        putText(displayImage, lineCountText, Point(10, displayImage.rows - 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
        logMessage(lineCountText);
    }

    imshow(windowName, displayImage);
    waitKey(0);
    logMessage("Features displayed in window: " + windowName);
}

/**
 * @brief Saves detected features (corners or lines) to a file.
 *
 * @param fileName The name of the file to save the features.
 */
void Detection::saveFeatures(const string& fileName) {
    ofstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open file: " + fileName);
    }

    for (const auto& feature : cornerFeatures) {
        file << "Point: (" << feature.x << ", " << feature.y << ")\n";
    }

    for (const auto& line : lineFeatures) {
        file << "Line: (" << line[0] << ", " << line[1] << ") -> ("
            << line[2] << ", " << line[3] << ")\n";
    }

    file.close();
    logMessage("Features saved to file: " + fileName);
}

/**
 * @brief Updates the edge map using the Canny edge detection algorithm.
 */
void Detection::updateEdgeMap() {
    if (getImage().empty()) {
        throw runtime_error("Gray level image is empty!");
    }

    // Generate edge map
    Canny(getImage(), edgeImage, threshold, threshold * 2);

    // Display edge map
    imshow("Edge Map", edgeImage);
    logMessage("Edge map updated with threshold: " + to_string(threshold));
}


/**
 * @brief Creates an interactive window for edge and line detection with adjustable threshold.
 */
void Detection::createAdjustableEdgeMap() {
    // Create windows for edge and line maps
    namedWindow("Edge Map", WINDOW_AUTOSIZE);
    namedWindow("Line Map", WINDOW_AUTOSIZE);

    // Create trackbar for threshold adjustment
    createTrackbar("Min Threshold:", "Edge Map", &threshold, maxThreshold, [](int, void* userdata) {
        Detection* self = static_cast<Detection*>(userdata);

        // Update edge map
        self->updateEdgeMap();

        // Clear and update line features
        self->lineFeatures.clear();
        HoughLinesP(self->edgeImage, self->lineFeatures, 1, CV_PI / 180, 50, 50, 10);

        // Update and display line map
        Mat lineImage = self->getImage().clone();
        for (const auto& lline : self->lineFeatures) {
            Point pt1(lline[0], lline[1]);
            Point pt2(lline[2], lline[3]);
            line(lineImage, pt1, pt2, Scalar(255, 0, 0), 2);
        }
        
        string lineCountText = "Lines Detected: " + to_string(self->getLineCount());
        putText(lineImage, lineCountText, Point(10, lineImage.rows - 20), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 2);
        imshow("Line Map", lineImage);
        }, this);

    // Show default maps
    updateEdgeMap();

    lineFeatures.clear();
    HoughLinesP(edgeImage, lineFeatures, 1, CV_PI / 180, 50, 50, 10);
    Mat lineImage = getImage().clone();
    for (const auto& lline : lineFeatures) {
        Point pt1(lline[0], lline[1]);
        Point pt2(lline[2], lline[3]);
        line(lineImage, pt1, pt2, Scalar(255, 0, 0), 2);
    }
    

    waitKey(0);
}
/**
 * @brief Creates an adjustable edge map with custom threshold values.
 *
 * @param initialThreshold The initial threshold value for edge detection.
 * @param maxThreshold The maximum threshold value for edge detection.
 */
void Detection::createAdjustableEdgeMap(int initialThreshold, int maxThreshold) {
    this->threshold = initialThreshold;
    this->maxThreshold = maxThreshold;

    createAdjustableEdgeMap(); // Varsayýlan fonksiyonu çaðýr
}

/**
 * @brief Sets the corner features.
 *
 * @param local A vector of corner points.
 */
void Detection::setCornerFeatures(vector<Point> local)
{
    cornerFeatures = local;
}

/**
 * @brief Sets the line features.
 *
 * @param local A vector of line features.
 */
void Detection::setLineFeatures(vector<Vec4i> local)
{
    lineFeatures = local;
}

/**
 * @brief Gets the corner features.
 *
 * @return A vector of detected corner points.
 */
vector<Point> Detection::getCornerFeatures(void) const
{
    return cornerFeatures;
}

/**
 * @brief Gets the number of detected corners.
 *
 * @return The number of detected corners.
 */
int Detection::getCornerCount(void) const
{
    return cornerFeatures.size();
}

/**
 * @brief Gets the number of detected lines.
 *
 * @return The number of detected lines.
 */
int Detection::getLineCount(void) const
{
    return lineFeatures.size();
}

/**
 * @brief Overloaded += operator to add a corner point.
 *
 * @param corner The corner point to add.
 * @return A reference to the Detection object.
 */
Detection& Detection::operator+=(const Point& corner) {
    cornerFeatures.push_back(corner);

    return *this;
}



