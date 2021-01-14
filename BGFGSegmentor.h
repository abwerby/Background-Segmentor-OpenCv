#pragma once
#include <opencv2/opencv.hpp>

class BGFGSegmentor
{
public:
    // default constructor
    BGFGSegmentor() : threshold(25), learningRate(0.5) {}
    // constructor with arg
    BGFGSegmentor(int threshold_, double learningRate_);
    // process frame and return output of foreground 
    void process(cv::Mat& frame, cv::Mat& output);
    // set functions
    void set_threshold(int threshold_);
    void set_learningRate(double learningRate_);
private:
    // current gray-level image
    cv::Mat gray; 
    // accumulated background
    cv::Mat background; 
    // current background image
    cv::Mat backImage;
    // foreground image
    cv::Mat foreground; 
    // learning rate in background accumulation
    double learningRate;
    // threshold for foreground extraction
    int threshold; 
};