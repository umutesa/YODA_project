/*
EEE4120F High Performance Embedded Systems
University of Cape Town

Authors: Flourish Oluwamakinde, Umutesa Munyurangabo, Anele Gunguluza
Program: Canny Edge Detection Golden Standard

This program provides the C++ implementation of the Canny Edge Detection Algorithm. There is a four-step process for extracting edges 
from an image:

    1. Noise reduction by blurring.
    2. Calculate intensity gradient of the image
    3. Suppression of false edges
    4. Hysteresis threshholding.
*/

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat img_blur = imread(./img/img/baboon.png);
Mat edges;

Canny(img_blur, edges, 100, 200, 3, false);

// Display canny edge detected image
imshow("Canny edge detection", edges);

waitKey(0);
