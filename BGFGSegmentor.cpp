#include "BGFGSegmentor.h"
#include <opencv2/opencv.hpp>


void BGFGSegmentor::set_threshold(int threshold_)
{
    this->threshold = threshold_;
}

void BGFGSegmentor::set_learningRate(double learningRate_)
{
    this->learningRate = learningRate_;
}

BGFGSegmentor::BGFGSegmentor(int threshold_, double learningRate_)
{
    this->threshold = threshold_;
    this->learningRate = learningRate_;
}

void BGFGSegmentor::process(cv::Mat& frame, cv::Mat& output)
{
    // convert to gray-level image
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    // Filter gray image with kernal size of 7 * 7
    cv::GaussianBlur(gray, gray, cv::Size(7, 7), 0);
    // initialize background to 1st frame
    if (background.empty())
        gray.convertTo(background, CV_32F);
    // convert background to 8U
    background.convertTo(backImage, CV_8U);
    // compute difference between image and background
    cv::absdiff(backImage, gray, foreground);
    // apply threshold to foreground image
    cv::threshold(foreground, output, threshold, 255, cv::THRESH_BINARY);
    // accumulate background
    // mask = alpha*gray + (1-alpha)*background
    cv::accumulateWeighted(gray, background,
        learningRate, // alpha
        output); //mask

    // cv::GaussianBlur(output, output, cv::Size(9, 9), 0);
}
