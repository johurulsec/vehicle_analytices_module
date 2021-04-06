#include "perspectivetransformation.h"
#include <QApplication>
#include <QDebug>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

PerspectiveTransformation::PerspectiveTransformation()
{

}

std::vector<cv::Point> PerspectiveTransformation::order_points(std::vector<cv::Point> points)
{
    cv::Point temp;
    if(points[0].x > points[1].x)
    {
        temp = points[0];
        points[0] = points[1];
        points[1] = points[2];
        points[2] = points[3];
        points[3] = temp;
    }

    return points;
}

cv::Mat PerspectiveTransformation::transform(cv::Mat src)
{
    int largest_area = 0;
    int largest_contour_index = 0;
    cv::Rect bounding_rect;

//    Mat src = imread( "/home/sigmind/Pictures/Tests/6_orig.png" , IMREAD_COLOR );

//    Mat gray;
//    cv::cvtColor( src, gray, CV_RGB2GRAY );
//    cv::GaussianBlur( gray, gray, Size( 7, 7 ), 0 );
//    imwrite( "grayed.png", gray );

//    filter2D(gray, gray, -1, (3,3));

    Mat canny;
    cv::Canny( src, canny, 20, 20 *3, 3 );
//    imwrite( "canny_edged.png", canny);

    int morph_size = 2;
        Mat element = getStructuringElement(
            MORPH_RECT, Size(2 * morph_size + 1,
                             2 * morph_size + 1),
            Point(morph_size, morph_size));

    dilate(canny, canny, element,
                   Point(-1, -1), 1);

//    imwrite( "canny_edged_dilate.png", canny);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours( canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );

    Mat drawing = Mat::zeros( canny.size(), CV_8UC3 );
        for( size_t i = 0; i< contours.size(); i++ )
        {
            Scalar color = Scalar( 0,255,0 );
            drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
        }
//    imwrite( "test.png", drawing);


    for ( int i = 0; i < contours.size(); i++ )
    {
        double area = contourArea( contours[i],false);
        if( area > largest_area )
        {
            largest_area = area;
            largest_contour_index = i;
            bounding_rect = boundingRect(contours[i]);
        }
    }

    drawContours( src, contours,largest_contour_index, Scalar( 0, 255, 0 ), 2 );
    imwrite(format("/home/sigmind/Pictures/Tests/%d_check.png",imgCounter),src);

    vector<vector<Point>> hull( contours.size() );
    for( size_t i = 0; i < contours.size(); i++ )
    {
        convexHull( Mat(contours[i]), hull[i], false );
    }

    cv::Mat dst = Mat::zeros(src.size(), CV_8UC3);

    drawContours( dst, hull, largest_contour_index, Scalar(255, 255, 255), cv::FILLED, 8, vector<Vec4i>(), 0, Point() );
//    imwrite( "convex_hull.png", dst);

//    erode(dst, dst, getStructuringElement(MORPH_RECT, Size(3, 3)));
//    imwrite( "convex_hull_erode.png", dst);

    Mat bw;
    cvtColor(dst, bw, cv::COLOR_BGR2GRAY);
    cv::findContours(bw.clone(), contours, hierarchy,cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, Point(0, 0));

    std::vector<cv::Point> approx;

    for (size_t i = 0; i < contours.size(); i++)
    {
        double epsilon = cv::arcLength(cv::Mat(contours[i]), true) * 0.02;
        cv::approxPolyDP( cv::Mat(contours[i]), approx, epsilon, true);
    }

//    approx = order_points(approx);

//    for(size_t i = 0; i < approx.size(); i++)
//    {
//        string text = to_string(static_cast<int>(i));
//        circle(src, approx[i], 3, Scalar(0, 255, 0), CV_FILLED);
//        circle(dst, approx[i], 3, Scalar(0, 255, 0), CV_FILLED);
//        putText(src, text, approx[i], FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar( 0, 0, 255 ), 2);
//        putText(dst, text, approx[i], FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar( 0, 0, 255 ), 2);
//    }

//    imwrite( "points.png", src);

    vector<Point2f> p,q;
    p.push_back(approx[0]);
    q.push_back(Point2f(0,0));

    p.push_back(approx[3]);
    q.push_back(Point2f(300,0));

    p.push_back(approx[2]);
    q.push_back(Point2f(300,370));

    p.push_back(approx[1]);
    q.push_back(Point2f(0,370));

    Mat rotation = cv::getPerspectiveTransform(p,q);

    Mat result;
    cv::warpPerspective(src, result, rotation, Size(300,420));

//    imwrite( "transformed.png", result);

    return result;
//    drawContours( src, contours,largest_contour_index, Scalar( 0, 255, 0 ), 2 );
//    imwrite( "detected.png", src);

//    vector<vector<Point>> approx( 1 );
//    double peri = arcLength( contours[largest_contour_index], true );
//    approxPolyDP( Mat( contours[largest_contour_index] ), approx[0], 0.02 * peri, true );

//    drawContours( src, approx, -1, Scalar( 0, 255, 0 ), 2 );
//    imwrite( "detected_withPoly.png", src);

    imgCounter++;


}
