//
//    Copyright 2021 Christopher D. McMurrough
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

/*******************************************************************************************************************//**
 * @file cv_annotation.cpp
 * @brief C++ example of basic image annotation and ROIs in OpenCV
 * @author Christopher D. McMurrough
 **********************************************************************************************************************/

// include necessary dependencies
#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

/*******************************************************************************************************************//**
 * @brief program entry point
 * @param[in] argc number of command line arguments
 * @param[in] argv string array of command line arguments
 * @return return code (0 for normal termination)
 * @author Christoper D. McMurrough
 **********************************************************************************************************************/
int main(int argc, char **argv)
{
    // open the input image
    std::string inputFileName = "test.png";
    cv::Mat imageIn;
    imageIn = cv::imread(inputFileName, cv::IMREAD_COLOR);

    // check for file error
    if(!imageIn.data)
    {
        std::cout << "Error while opening file " << inputFileName << std::endl;
        return 0;
    }

    // get the image size
    std::cout << "image width: " << imageIn.size().width << std::endl;
    std::cout << "image height: " << imageIn.size().height << std::endl;
    std::cout << "image channels: " << imageIn.channels() << std::endl;

    // display the input image
    cv::imshow("imageIn", imageIn);
    cv::waitKey();


    // NEW STUFF
    // REGION OF INTEREST (ROI)
    //
    // Ex: We want to draw blocks around people to avoid them. Or to count how many of something are in the scene. 
    // 
    // ROI: rectangular region of interest
    //
    // Most straightforward way is to define a ROI is using two points, x1, y1, and x2, y2
    // Other way: centroid, using center point, 0.5W, 0,5H

    // create a 200 pixel wide region of interest (ROI) on the center of the image
    cv::Point p1(imageIn.cols / 2 - 100, imageIn.rows / 2 - 100);
    cv::Point p2(imageIn.cols / 2 + 100, imageIn.rows / 2 + 100);
    // a Rect in OpenCV is just a container that stores 2 points, check their datamembers. Convenience class.
    cv::Rect region(p1, p2);

    // extract the ROI into its own image and display
    //
    // CROP
    cv::Mat imageROI = imageIn(region);
    cv::imshow("imageROI", imageROI);
    cv::waitKey();

    // draw a red rectangle around the ROI and update the display
    // rectangle(source img, ROI, Scalar( a tuple of scalars, color code BGR ), int line_thickness, ...other opts)
    cv::rectangle(imageIn, region, cv::Scalar(0, 0, 255), 3);
    cv::imshow("imageIn", imageIn);
    cv::waitKey();

    // draw a blue circle around the ROI and update the display
    cv::Point center(imageIn.cols / 2, imageIn.rows / 2);
    cv::circle(imageIn, center, 100, cv::Scalar(255, 0, 0), 3);
    cv::imshow("imageIn", imageIn);
    cv::waitKey();

    // draw black lines from corner to corner and display
    cv::Point cornerTopLeft(0, 0);
    cv::Point cornerTopRight(imageIn.cols - 1, 0);
    cv::Point cornerBottomLeft(0, imageIn.rows - 1);
    cv::Point cornerBottomRight(imageIn.cols - 1, imageIn.rows - 1);

    // draw the lines
    // line( target img, first point, second point, color, thickness )
    cv::line(imageIn, cornerTopLeft, cornerBottomRight, cv::Scalar(0, 0, 0), 3);
    cv::line(imageIn, cornerTopRight, cornerBottomLeft, cv::Scalar(0, 0, 0), 3);
    cv::imshow("imageIn", imageIn);
    cv::waitKey();
}
