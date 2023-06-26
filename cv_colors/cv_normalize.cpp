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
 * @file cv_normalize.cpp
 * @brief C++ example of image normalization in OpenCV
 * @author Christopher D. McMurrough
 **********************************************************************************************************************/
//We are mose focues on the shape of the picture rather than the
//colors of the image. The problem with color is with lights on 
//and lights off we get different values there. 
//Camera sensors do not give you perfect white or black colors
//Hard to get repetable results from different camers with same photo
//Normalization clean up to images

//Color image -> gray scale copy -> geometry stuff here
//Color iamge -> color stuff here

//We want to normalize before converting gray scale 
//Normalization takes min and max values in histogram and 
//stretches it out
// include necessary dependencies
#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"// Normalization, histogram, blurring, sharpaning -> low level image processing...
#include <iostream>
#include <stdio.h>

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

    // locate the minimum and maximum values in CV::MAT
    double min, max;
    cv::minMaxLoc(imageGray, &min, &max); //REQUIRES double for Min, Max
    std::cout << "Minimum value: " << min << std::endl;
    std::cout << "Maximum value: " << max << std::endl;

    // normalize the image
    cv::Mat imageNormalized; //8bit unsigned 1 channel
    cv::normalize(imageGray, imageNormalized, 0, 255, cv::NORM_MINMAX, CV_8UC1);

    // locate the minimum and maximum values
    cv::minMaxLoc(imageNormalized, &min, &max);
    std::cout << "Minimum value: " << min << std::endl;
    std::cout << "Maximum value: " << max << std::endl;

    // display the images
    cv::imshow("imageIn", imageIn);
    cv::imshow("imageGray", imageGray);
    cv::imshow("imageNormalized", imageNormalized);
    cv::waitKey();

    return 0;
}
