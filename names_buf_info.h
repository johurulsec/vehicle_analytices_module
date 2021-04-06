#ifndef NAMES_BUF_INFO_H
#define NAMES_BUF_INFO_H
#include <string>
#include <algorithm>
#include "opencv2/opencv.hpp"
namespace Buf_info {
class names_buf_info
{
public:
    names_buf_info();
    int source_id;
    std::string color;
    std::string mask_status;
    std::vector<std::pair<cv::Mat, float>> person_vec;
    cv::Mat* person;
    cv::Mat* face;
    double fps;
    double distance_between_two_person;
};
}




#endif // NAMES_BUF_INFO_H
