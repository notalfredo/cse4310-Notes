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
 * @file cv_containers.cpp
 * @brief C++ example of basic image containers in OpenCV
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
    std::cout << "image width: " << imageIn.cols << std::endl;
    std::cout << "image height: " << imageIn.rows << std::endl;
    // imageIn.depth() can be used to find the depth, because gray 8bit and gray 16bit are different
    std::cout << "image channels: " << imageIn.channels() << std::endl;
    
    // get the image size using the size() member function
    std::cout << "image width: " << imageIn.size().width << std::endl;
    std::cout << "image height: " << imageIn.size().height << std::endl;

    // FIRST OP ON CV MAT below
    // display the input image
    cv::imshow("imageIn", imageIn);
    cv::waitKey();
    
    // convert the image to grayscale
    cv::Mat imageGray;

    // cvtColor(source, destination, conversion)
    // COLOR_BGR2GRAY ... many others
    //   OpenCV stores RGB as BGR.
    // 
    // Why is converting to gray scale is important?
    //      because most all OpenCV operations are usually in greyscale.
    //      80% of the time, we are more concerned with the geometry of the image.
    cv::cvtColor(imageIn, imageGray, cv::COLOR_BGR2GRAY);
    
    // display the grayscale image
    cv::imshow("imageGray", imageGray);
    cv::waitKey();
    
    // split the input image into individual channels
    // initialize an array of size 3, this is an array of cv::Mat's
    cv::Mat channels[3];
    // splits the original image's channels and puts it into each of the above cv::Mats
    cv::split(imageIn, channels);
    
    // display the image channels
    cv::imshow("channels[0] (blue)", channels[0]);
    cv::imshow("channels[1] (green)", channels[1]);
    cv::imshow("channels[2] (red)", channels[2]);
    cv::waitKey();
    
    // resize the input image to half of its original size
    cv::Mat imageResized;
    // cv::Size is an arbitrarty type that represents the sizes of containers Size(width, height)
    // Size has an option for bi-cublic sampling when sizing up an image.
    cv::resize(imageIn, imageResized, cv::Size(imageIn.cols / 2, imageIn.rows / 2));
    cv::imshow("imageResized", imageResized);
    
    // save the output image
    // Good for debugging. other optional flags, apply compression, quality levels
    cv::imwrite("OUTPUT.png", imageResized);
    cv::waitKey();
    

    // manual pixel iteration, usually avoid this because its slow.
    //
    // iterate over the resized image printing the pixel values (cv::Mat is row-major, so access is row,col)
    for(int i = 0; i < imageResized.rows; i++)
    {
        for(int j = 0; j < imageResized.cols; j++)
        {
            // imageResized.at<cv::Vec3b>
            //  remember that the value at the pixel has 3 values
            //  .at<TEMPALTE> is used to get the row column of the pixel
            //  Vec3b : depth, a vector of 3 bytes
            //      IF IT WAS A
            //      Single Channel: Vec1b
            //
            int b = imageResized.at<cv::Vec3b>(i, j)[0];
            int g = imageResized.at<cv::Vec3b>(i, j)[1];
            int r = imageResized.at<cv::Vec3b>(i, j)[2];
            std::cout << "Pixel(" << i << ", " << j << ") = " << b << " " << g << " " << r << std::endl;
        }
    }
    cv::waitKey();
}

