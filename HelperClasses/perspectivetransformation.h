#ifndef PERSPECTIVETRANSFORMATION_H
#define PERSPECTIVETRANSFORMATION_H
#include <QApplication>
#include <QDebug>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

class PerspectiveTransformation
{
public:
    PerspectiveTransformation();
    Mat transform(cv::Mat src);
    std::vector<cv::Point> order_points(std::vector<cv::Point> points);
    int imgCounter = 0;
};

#endif // PERSPECTIVETRANSFORMATION_H
