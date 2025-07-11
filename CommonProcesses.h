#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/* *******************************************************
 * Filename		:	CommonProcesses.h
 * Author		:	Doğukan Avcı
 * Date			:	21.12.2024
 * Description	:	OOP Final Project
 * ******************************************************/

using namespace std;
using namespace cv;

/// CommonProcesses Class
/// This class provides common image processing utilities such as image reading, grayscale conversion, resizing, noise filtering, and more.


class CommonProcesses
{

public:

	/// Constructor for CommonProcesses
	/// @param filePath The file path of the image to process.
	/// @param fileName The name of the image file.
	 /// @param scale The scale factor for resizing.
	CommonProcesses(const string& filePath, const string& fileName, double& scale ); //ok

	/// Destructor for CommonProcesses
	virtual ~CommonProcesses(); 

	/// Get the raw RGB image
	/// @return Reference to the Mat object containing the RGB image.
	Mat& getImage(void); 

	/// Get the grayscale image
	/// @return A constant Mat object containing the grayscale image.
	Mat getgrayLevelImage(void) const; 
	
	/// Get the file name of the image
	/// @return The name of the image file.
	string getfileName(void) const; 

	/// Set the file name for the image
	/// @param nameOfFile The name of the image file.
	void setfileName(string const& nameOfFile);

	/// Read an image from the local file system
	/// @param filePath The file path of the image to read.
	void readImage(const string& filePath); 

	/// Convert the RGB image to grayscale
	/// @param image Reference to the Mat object containing the image to convert.
	void convertToGrayScale(Mat& image); 

	/// Display the image in a window
	/// @param windowName The name of the window.
	/// @param image Reference to the Mat object containing the image to display.
	void showImage(const string& windowName, Mat& image) const;

	/// Display the grayscale image in a window
	/// @param windowName The name of the window.
	void showGrayLevelImage(const string& windowName) const;

	/// Save the RGB values of the image to a text file
	/// Format: Pixel(x, y): R: r_value, G: g_value, B: b_value
	/// @param image The Mat object containing the image to process.
	/// @param fileName The name of the file to save the RGB values.
	void saveRGBToFile(const Mat& image, const string& fileName);

	/// Resize the image using the resize function
	/// @param image Reference to the Mat object containing the image to resize.
	void rescaleImage(Mat& image) const; 

	/// Reduce noise in the image using a Gaussian filter
	/// @param image Reference to the Mat object containing the image to filter.
	void filterNoiseGaus(Mat& image); 

	/// Reduce noise in the image using a Median filter
	/// @param image Reference to the Mat object containing the image to filter
	void filterNoiseMedian(Mat& image);


	
	/// Get the scale factor for resizing
	/// @return The scale factor.
	double getScaleFactor(void) const; 

	/// Set the scale factor for resizing
    /// @param sf The scale factor.
	void setScaleFactor(double& sf); 

private:

		/// Storing raw RGB Values with static Mat class
		Mat image; 

		/// GrayLevelImage
		Mat grayLevelImage; 

		/// Scaling Factor
		double scaleFactor;

		/// Name of File
		string fileName;

};

