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
 * @file cv_optic_flow.cpp
 * @brief C++ example demonstrating optic flow tracking in OpenCV
 * @author Christopher D. McMurrough
 **********************************************************************************************************************/

// include necessary dependencies
#include <iostream>
#include <cstdio>
#include "opencv2/opencv.hpp"
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

// configuration parameters
#define NUM_COMNMAND_LINE_ARGUMENTS 1
#define DISPLAY_WINDOW_NAME "Video Frame"

/*******************************************************************************************************************//**
 * @brief program entry point
 * @param[in] argc number of command line arguments
 * @param[in] argv string array of command line arguments
 * @return return code (0 for normal termination)
 * @author Christoper D. McMurrough
 **********************************************************************************************************************/
int main(int argc, char **argv)
{
    // store video capture parameters
    std::string fileName;

    // validate and parse the command line arguments
    if(argc != NUM_COMNMAND_LINE_ARGUMENTS + 1)
    {
        std::cout << "USAGE:" << argv[0] << " <file_path" << std::endl;
        return 0;
    }
    else
    {
        fileName = argv[1];
    }

    // open the video file
    std::cout << fileName << std::endl;
    cv::VideoCapture capture(fileName, cv::CAP_FFMPEG);
    if(!capture.isOpened())
    {
        std::printf("Unable to open video source, terminating program! \n");
        return 0;
    }

    // get the video source parameters
    int captureWidth = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_WIDTH));
    int captureHeight = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_HEIGHT));
    int captureFPS = static_cast<int>(capture.get(cv::CAP_PROP_FPS));
    std::cout << "Video source opened successfully (width=" << captureWidth << " height=" << captureHeight << " fps=" << captureFPS << ")!" << std::endl;

    // create image window
    cv::namedWindow(DISPLAY_WINDOW_NAME, cv::WINDOW_AUTOSIZE);

    /*
    // create the tracker object
    std::string trackerTypes[9] = {"CSRT", "GOTURN", "KCF", "MIL"};
    std::string trackerType = trackerTypes[trackerSelection];
    cv::Ptr<cv::Tracker> tracker;
    if (trackerType == "CSRT")
        tracker = cv::TrackerCSRT::create();
    if (trackerType == "GOTURN")
        tracker = cv::TrackerGOTURN::create();
    if (trackerType == "KCF")
        tracker = cv::TrackerKCF::create();
    if (trackerType == "MIL")
        tracker = cv::TrackerMIL::create();
    */

    // declare variables for tracking
    //cv::Rect roi;
    //cv::Mat frame;

    // get bounding box
    //bool captureSuccess = capture.read(frame);
    //roi = cv::selectROI(DISPLAY_WINDOW_NAME, frame);
    /*
    // exit if ROI was not selected
    if(roi.width==0 || roi.height==0)
    {
        return 0;
    }

    // initialize the tracker
    tracker->init(frame,roi);
    */

    // declare variables for tracking
    cv::Mat frame;
    cv::Mat frameGray;
    cv::Mat prevGray;
    
    cv::Mat prevgray, gray, rgb;
    cv::Mat flow, flow_uv[2];
    cv::Mat mag, ang;
    cv::Mat hsv_split[3], hsv;
    char ret;

    cv::Ptr<cv::DenseOpticalFlow> algorithm = cv::DISOpticalFlow::create(cv::DISOpticalFlow::PRESET_MEDIUM);


    // perform tracking iterations on each frame
    std::cout << "Starting tracker, press 'q' to quit" << std::endl;
    bool tracking = true;
    while(tracking)
    {
        // get frame from the video
        bool captureSuccess = capture.read(frame);
        if(captureSuccess)
        {
            // convert the frame to grayscale
            cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

            // update the tracking result
            //tracker->update(frame,roi);

            // annotate and show the frame
            //cv::rectangle(frame, roi, cv::Scalar( 255, 0, 0 ), 2, 1 );
            cv::imshow(DISPLAY_WINDOW_NAME, frame);

            // check for user termination
            if(cv::waitKey(1)=='q')
            {
                tracking = false;
            }
        }
    }

    // release program resources before returning
    capture.release();
}
