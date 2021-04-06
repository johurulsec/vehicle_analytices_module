#include "rectangle.h"
#include "opencv2/opencv.hpp"

namespace watchcam{
    rectangle::rectangle()
    {
        left= top = right = bot = height = width = 0;
    }

    rectangle::rectangle(int LEFT, int TOP, int RIGHT, int BOTTOM)
    //  rectangle::rectangle(int LEFT, int TOP, int WIDTH, int HEIGHT)
    {
        left = LEFT;
        top = TOP;
        right = RIGHT;
       bot = BOTTOM;
       // buFrame = frame;
        width = right - left;
        height = bot - top;
//        width = WIDTH;
//        height = HEIGHT;

    }

    bool rectangle::contains_point(int x, int y)
    {
        return x>=left && x<=right && y>=top && y<=bot;
    }

    int rectangle::intersection_with(rectangle &a)
    {
        int l = std::max(left, a.left);
        int r = std::min(right, a.right);
        int t = std::max(top, a.top);
        int b = std::min(bot, a.bot);
       // int area = (r-l)*(b-t);
        int area = (r-l)*(b-t);
        if(area<0 || r<l) area = 0;
        return area;
    }
}
