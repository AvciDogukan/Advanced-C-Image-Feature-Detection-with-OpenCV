#pragma once
#include "Detection.h"
#include <fstream>
#include <vector>

using namespace std;
using namespace cv;

/// LineDetection Class
/// Derived from the Detection class, this class provides specific functionalities for detecting and visualizing lines in an image.
class LineDetection :  public Detection
{
	public:
		/// Constructor for LineDetection
		/// @param filePath The file path of the image to process.
		/// @param fileName The name of the image file.
		/// @param scale The scale factor for resizing the image.
		LineDetection(const string& filePath, const string& fileName, double& scale);

		/// Destructor for LineDetection
		~LineDetection();

		/// Detect lines and edges in the image
		/// Uses the Canny edge detection algorithm and Hough Line Transform.
		void detectFeatures(void) override;


		/// Process line detection with default settings
		/// Applies grayscale conversion, detects features, saves features, and visualizes detected lines.
		void processLineDetection(void);
		
		/// Process line detection with an optional filter
		/// @param filter If true, applies a noise reduction filter before detecting lines.
		void processLineDetection(bool filter);

	private:

		/// Low threshold value for edge detection
		int lowThresHold;

		/// Maximum threshold value for edge detection
		const int maxThresHold = 255;

		/// Mat object to store detected edges
		Mat detectedEdges;

};

