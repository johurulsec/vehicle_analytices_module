#ifndef WRECTANGLE_H
#define WRECTANGLE_H

#include <string>
#include <algorithm>
#include "opencv2/opencv.hpp"
namespace watchcam{
    class rectangle
    {
    public:
        rectangle();
        rectangle( int LEFT, int TOP, int RIGHT, int BOTTOM);

        bool contains_point(int x, int y);
        int intersection_with(watchcam::rectangle &a);
     // cv::Mat buFrame;
        int top, bot, left, right, width, height;
        int type, track_id;
        std::string name;
        std::string str_color;
        std::string str_label;
        bool is_face = false;
        bool is_LP =false;
        bool is_detected_by_dlib = false;
        int source_id;
        double fps;
        std::string mask_or_unmask;
        std::vector<std::pair<cv::Mat*, float>> person;

    };


}



#endif // RECTANGLE_H
