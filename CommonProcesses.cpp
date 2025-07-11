#include "CommonProcesses.h"
#include <stdexcept>
#include <fstream>

using namespace std;
using namespace cv;



/// Constructor with an optional filePath and fileName
CommonProcesses::CommonProcesses(const string& filePath, const string& fileName, double& scale)
{	
	cout << "Constructor Created for CommonProcesses " << endl;
	setScaleFactor(scale);
	setfileName(fileName);
	readImage(filePath);
	
	
}
/// Destructor for CommonProcessor
CommonProcesses::~CommonProcesses()
{
	cout << "Destructor Called for CommonProcesses " << endl;
}

/// Get the original image
/// @return A reference to the Mat object containing the image data.
Mat& CommonProcesses::getImage(void)
{
	return image;
}

/// Get the grayscale version of the image
/// @return A constant Mat object containing the grayscale image data. 
Mat CommonProcesses::getgrayLevelImage(void) const
{
	return grayLevelImage;
}


/// Get the file name
/// @return A string containing the file name of the image.
string CommonProcesses::getfileName(void) const
{
	return fileName;
}

/// Set the file name
/// @param nameOfFile The name to set for the file.
void CommonProcesses::setfileName(string const& nameOfFile)
{
	fileName = nameOfFile;
}


/// Read an image from the specified file path
/// @param filePath The path of the image file to load.
void CommonProcesses::readImage(const string& filePath)
{
	image = imread(filePath,IMREAD_COLOR); /// IMREAD_COLOR = If set, always convert image to the 3 channel BGR color image.

	if (image.empty())
	{
		cerr << "Image could not be loaded : " << filePath << endl;

		throw runtime_error("Image could not be loaded");
	}

}

/// Convert the given image to grayscale
/// @param image A reference to the Mat object to convert.
void CommonProcesses::convertToGrayScale(Mat& image)
{	
	/// Check if the image is empty
	if (!image.empty())
	{
		cvtColor(image, image, COLOR_BGR2GRAY);
		cout << "The file image  has been converted to grayscale " << endl;
	}
	else
	{
		throw runtime_error("The image could not be converted to gray type.");
	}
	 
	
}

/// Display the given image in a window
/// @param windowName The name of the display window.
/// @param image A reference to the Mat object to display.
void CommonProcesses::showImage(const string& windowName, Mat& image) const
{
	imshow(windowName,image);
	waitKey(0);
}

/// Display the grayscale version of the image
/// @param windowName The name of the display window.
void CommonProcesses::showGrayLevelImage(const string& windowName) const
{
	if (grayLevelImage.empty())
	{
		throw runtime_error("Image was not converted to gray successfully");
	}

	imshow(windowName, grayLevelImage);
	waitKey(0);
}

/// Save the RGB values of an image to a file
/// @param image The Mat object containing the image data.
/// @param fileName The name of the file to save the RGB values
void CommonProcesses::saveRGBToFile(const Mat& image, const string& fileName)
{	
	// Creating the file for RGB values.
	ofstream outFile(fileName);
	if (!outFile.is_open()) {
		cerr << "Error: Could not open file!" << endl;
		throw runtime_error("Could not open file " + fileName);
	}

	// Taking the row and column variables.


	

	for (int y = 0; y < image.rows; y++) {   // Iterate over rows
		for (int x = 0; x < image.cols; x++) {  // Iterate over columns
			cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);  // Get the pixel value

			int blue = pixel[0];
			int green = pixel[1];
			int red = pixel[2];

			// Write RGB values to the file
			outFile << "Pixel (" << y << ", " << x << "): "
				<< "R: " << red << ", G: " << green << ", B: " << blue << "\n";
		}
	}

	outFile.close();
	cout << "RGB values " << fileName << " successfully saved to file." << endl;
}

/// Rescale the given image by a scale factor
/// @param image A reference to the Mat object to resize.
void CommonProcesses::rescaleImage(Mat& image) const
{	
	double localScaleFactor = getScaleFactor();
	if (localScaleFactor <= 0)
	{
		throw invalid_argument("Scale value cannot be less than or equal to 0.");
	}

	resize(image, image, Size(), localScaleFactor, localScaleFactor);
	cout << "Image Resized" << endl;

}

/// Apply Gaussian blur to reduce noise in the given image
/// @param image A reference to the Mat object to apply the filter.
void CommonProcesses::filterNoiseGaus(Mat& image)
{	

	if (!image.empty())
	{
		GaussianBlur(image, image, Size(3,3), 0);
		cout << "Noise in the image was cleaned using the GaussianBlur filter. " << endl;
	}
	else
	{
		throw runtime_error("image file is empty filter operation cannot be applied!");
	}

	
}

/// Apply median blur to reduce noise in the given image
/// @param image A reference to the Mat object to apply the filter.
void CommonProcesses::filterNoiseMedian(Mat& image)
{	

	if (!image.empty())
	{
		medianBlur(image, image, 11);
		cout << "Noise in the image was cleaned using the median filter. " << endl;
	}
	else
	{
		throw runtime_error("image file is empty filter operation cannot be applied!");
	}

}

/// Get the scale factor
/// @return The current scale factor.
double CommonProcesses::getScaleFactor(void) const
{
	return scaleFactor;
}

/// Set the scale factor
/// @param sf The new scale factor to set. Must be greater than 0.
void CommonProcesses::setScaleFactor(double& sf)
{
	if (sf > 0)
	{
		scaleFactor = sf;
	}
	else
	{
		throw invalid_argument("Scale factor must be greater than 0");
	}
	
}

