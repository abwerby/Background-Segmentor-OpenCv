# BackGround-ForeGround-Segmentor
Motion detection based on moving average background subtraction method implemented in C++ with OpenCV library 

## Overview
This is BackGround-ForeGround-Segmentor based on moving average background subtraction method implemented in C++ with OpenCV library,
the algorithm simply model the background by taking the moving average of pixels, 
	mask = (1 - alpha) * background + alpha * frame

#### Algorithm Steps:
	1- Convert frame to gray-level image  
	2- Filter gray image with Gaussian Filter with kernal of size 7*7  
	3- Compute difference between image and background (if first frame set first frame to be background)  
	4- Apply threshold to foreground image (the difference result)  
	5- Accumulate background with equ: background = (1 - alpha) * background + alpha * frame  

## Results image
![alt text](https://github.com/abwerby/Background-Segmentor-OpenCv/blob/main/Screenshot%20(59).png)
![alt text](https://github.com/abwerby/Background-Segmentor-OpenCv/blob/main/Screenshot%20(60).png)  
![alt text](https://github.com/abwerby/Background-Segmentor-OpenCv/blob/main/Screenshot%20(61).png)
![alt text](https://github.com/abwerby/Background-Segmentor-OpenCv/blob/main/Screenshot%20(62).png)
![alt text](https://github.com/abwerby/Background-Segmentor-OpenCv/blob/main/Screenshot%20(63).png)

