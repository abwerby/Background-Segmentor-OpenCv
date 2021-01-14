
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "BGFGSegmentor.h"



int main()
{
    // Read video file
    cv::VideoCapture cap("highway.mp4");
    cv::Mat frame, output, output_dilate;
    // variable to save the estimated contours from the output frame
    std::vector<std::vector<cv::Point>> contours;
    // to measure time of the process
    std::chrono::time_point<std::chrono::system_clock> start, end;
    // min area of contours to detect
    double min_area = 750;
    // color of the bounding box
    cv::Scalar color = cv::Scalar(100, 100);

    // create BGFGSegmentor objects and set paramters
    BGFGSegmentor segmntor;
    segmntor.set_learningRate(0.2);
    segmntor.set_threshold(25);

    // Check if camera opened successfully
    if (!cap.isOpened()) 
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    while (1) 
    {
        // save start time
        start = std::chrono::system_clock::now();

        // Capture frame-by-frame
        cap >> frame;
        cv::resize(frame, frame, cv::Size(), 0.5, 0.5);

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        // process current image
        segmntor.process(frame, output);

        // dilate image with kernal of size 3*3 and 1 iteration
        cv::dilate(output, output_dilate, cv::Mat(), cv::Point(-1, -1), 1);
        // find all contours in output_dilate image
        cv::findContours(output_dilate, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // loop in all contours to finad contours with area > min area
        for (auto i : contours)
        {
            if (cv::contourArea(i) > min_area)
            {
                cv::Rect boundRect = cv::boundingRect(i);
                cv::rectangle(frame, boundRect.tl(), boundRect.br(), color, 2);
            }
        }

        // Display the resulting frame
        cv::imshow("Frame", frame);
        cv::imshow("BackGround", output);
        cv::imshow("output_dilate", output_dilate);

        // save end time
        end = std::chrono::system_clock::now();
        // find the diffrence -> elapsed_seconds = end - start
        std::chrono::duration<double> elapsed_seconds = end - start;
        // print Fps
        std::cout << "elapsed time: " << 1 / elapsed_seconds.count() << " FPS\n";

        // Press  ESC on keyboard to exit
        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    cv::destroyAllWindows();

}

