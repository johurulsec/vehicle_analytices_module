#ifndef WOLFBINARIZATION_H
#define WOLFBINARIZATION_H


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

namespace Ui {
class WolfBinarization;
}

class WolfBinarization
{


public:

    enum NiblackVersion
    {
        NIBLACK=0,
        SAUVOLA,
        WOLFJOLION,
    };


    explicit WolfBinarization();
    void NiblackSauvolaWolfJolion (cv::Mat im, cv::Mat output, NiblackVersion version,int winx, int winy, double k, double dR);
    double calcLocalStats (cv::Mat &im, cv::Mat &map_m, cv::Mat &map_s, int winx, int winy);
    void wolfBinarize(cv::Mat input, cv::Mat output);
    ~WolfBinarization();


};

#endif // WOLFBINARIZATION_H

