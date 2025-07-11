#pragma once
#include "Detection.h"
#include <fstream>
#include <vector>

using namespace std;
using namespace cv;

/// CornerDetection Class
/// Derived from the Detection class, this class provides specific functionalities for detecting and visualizing corners in an image.
class CornerDetection :public Detection
{
public:
	/// Constructor for CornerDetection
    /// @param filePath The file path of the image to process.
    /// @param fileName The name of the image file.
    /// @param scale The scale factor for resizing the image.
	CornerDetection(const string& filePath, const string& fileName, double& scale);
	
	/// Destructor for CornerDetection
	~CornerDetection(); 

	/// Detect corners in the image
	/// Uses the Harris corner detection algorithm.
	void detectFeatures(void) override;

	/// Process corner detection with default settings
	/// Applies grayscale conversion, detects features, saves features, and visualizes detected corners.
	void processCornerDetection(void);

	/// Process corner detection with an optional filter
	/// @param filter If true, applies a noise reduction filter before detecting corners.
	void processCornerDetection(bool filter);

	/// Get the quality level used for corner detection
	/// @return The quality level as an integer.
	int getQualityLevel(void) const;

	/// Set the quality level for corner detection
	/// @param q The quality level to set.
	void setQualityLevel(int q);

	/// Overload the += operator to add a detected corner to the corner list
	/// @param corner A detected corner point.
	/// @return Reference to the CornerDetection object.
	CornerDetection& operator+=(const Point& corner);



private:
	/// Quality level for corner detection
	int qualityLevel;

	/// Maximum quality level for corner detection
	const int maxQualityLevel = 100;

	/// Vector to store detected corners
	vector<Point> corners;
	


};

