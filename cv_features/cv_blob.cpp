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
 * @file cv_blob.cpp
 * @brief C++ example for blob detection with OpenCV
 * @author Christopher D. McMurrough
 * @notes based off of example found at https://www.learnopencv.com/blob-detection-using-opencv-python-c/
 **********************************************************************************************************************/

// include necessary dependencies
#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

// configuration parameters
#define NUM_COMNMAND_LINE_ARGUMENTS 1

/*******************************************************************************************************************//**
 * @brief program entry point
 * @param[in] argc number of command line arguments
 * @param[in] argv string array of command line arguments
 * @return return code (0 for normal termination)
 * @author Christoper D. McMurrough
 **********************************************************************************************************************/
int main(int argc, char **argv)
{
    cv::Mat imageIn;

    // validate and parse the command line arguments
    if(argc != NUM_COMNMAND_LINE_ARGUMENTS + 1)
    {
        std::printf("USAGE: %s <image_path> \n", argv[0]);
        return 0;
    }
    else
    {
        imageIn = cv::imread(argv[1], cv::IMREAD_COLOR);

        // check for file error
        if(!imageIn.data)
        {
            std::cout << "Error while opening file " << argv[1] << std::endl;
            return 0;
        }
    }

    // convert the image to grayscale
    cv::Mat imageGray;
    cv::cvtColor(imageIn, imageGray, cv::COLOR_BGR2GRAY);

    // define the blob detection parameters
    cv::SimpleBlobDetector::Params params;
    params.minThreshold = 10;
    params.maxThreshold = 250;
    params.filterByArea = true;
    params.minArea = 200;
    params.filterByCircularity = true;
    params.minCircularity = 0.1;
    params.filterByConvexity = false;
    params.minConvexity = 0.9;
    params.filterByInertia = true;
    params.minInertiaRatio = 0.1;

    // set up the blob detector with default parameters
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(imageGray, keypoints);

    // draw the keypoints
    cv::Mat imageKeypoints;
    cv::drawKeypoints(imageGray, keypoints, imageKeypoints, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // display the images
    cv::imshow("imageIn", imageIn);
    cv::imshow("imageGray", imageGray);
    cv::imshow("imageKeypoints", imageKeypoints);
    cv::waitKey();

    return 0;
}

