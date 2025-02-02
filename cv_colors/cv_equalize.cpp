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
 * @file cv_equalize.cpp
 * @brief C++ example of image equalization in OpenCV
 * @author Christopher D. McMurrough
 **********************************************************************************************************************/
//Calculate the frequencies of all the values and try to spread
//them out of range. Increasing the values not represented before
//Really good when the image is super saturated.
// include necessary dependencies
#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

// configuration parameters
#define NUM_COMNMAND_LINE_ARGUMENTS 1

/*******************************************************************************************************************//**
 testing* @brief program entry point
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

    // apply the histogram equalization
    // will bin all values to try to equalize them
    cv::Mat imageEqualized;
    cv::equalizeHist(imageGray, imageEqualized);

    // display the images
    cv::imshow("imageIn", imageIn);
    cv::imshow("imageGray", imageGray);
    cv::imshow("imageEqualized", imageEqualized);
    cv::waitKey();

    return 0;
}
