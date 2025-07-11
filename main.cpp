/**
 * @file main.cpp
 * @brief Project Synopsis
 *
 * This project is an advanced image feature detection framework implemented in C++,
 * designed to demonstrate object-oriented programming (OOP) principles.
 *
 * The project includes the following main features:
 * - **Detection Framework**: A modular architecture for detecting features in images.
 * - **Line Detection**: Utilizes OpenCV functions like `Canny` and `HoughLinesP` to detect edges and lines.
 * - **Corner Detection**: Implements Harris corner detection using OpenCV functions like `cornerHarris` and `normalize`.
 * - **Inheritance and Polymorphism**: Demonstrates OOP concepts with a base class `Detection` and derived classes `LineDetection` and `CornerDetection`.
 * - **Dynamic Feature Adjustment**: Allows real-time tuning of detection thresholds for both line and corner detection.
 *
 * Technologies used:
 * - **OpenCV**: For advanced image processing and feature detection.
 * - **C++ STL**: For efficient data management (e.g., `vector<Point>` and `vector<Vec4i>`).
 * - **Doxygen**: For generating detailed project documentation.
 *
 * The project structure is designed to be modular, allowing for easy extension with additional detection methods.
 *
 * This framework is ideal for educational purposes, showcasing image processing techniques and OOP concepts,
 * as well as for practical applications in computer vision and robotics.
 */

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "CommonProcesses.h"
#include "LineDetection.h"
#include "CornerDetection.h"

/* *******************************************************
 * Filename		:	main.cpp
 * Author		:	Doðukan Avcý
 * Date			:	21.12.2024
 * Description	:	OOP Final Project
 * ******************************************************/

using namespace cv;
using namespace std;

int main()
{   
    try {
        /// Promt Values (From User)
       string filePath = "C:/Users/doguk/OneDrive/Pictures/Ekran Görüntüleri/test2.jpg";
        //string filePath = "C:/Users/doguk/source/repos/openCV/openCV/resim.png";
        string fileName = "Plane";
        double scaleFactor = 1.0;
        
        // Starting Line Detection Process
        //LineDetection lineDetector(filePath, fileName, scaleFactor);
        //lineDetector.processLineDetection(1);
        
        /// Starting Corner Detection Process
        CornerDetection cornerDetector(filePath, fileName, scaleFactor);
        cornerDetector.processCornerDetection();
        
    }

    /// Exception Handler
    catch (const std::exception& e) {
        cerr << "Error : " << e.what() << std::endl;
    }

    return 0;


}
