#include "WolfBinarization.h"


#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;



#define BINARIZEWOLF_VERSION	"2.4 (August 1st, 2014)"

#define uget(x,y)    at<unsigned char>(y,x)
#define uset(x,y,v)  at<unsigned char>(y,x)=v;
#define fget(x,y)    at<float>(y,x)
#define fset(x,y,v)  at<float>(y,x)=v;


WolfBinarization::WolfBinarization()
{

}

WolfBinarization::~WolfBinarization()
{

}


double WolfBinarization::calcLocalStats (Mat &im, Mat &map_m, Mat &map_s, int winx, int winy) {
    Mat im_sum, im_sum_sq;
    cv::integral(im,im_sum,im_sum_sq,CV_64F);

    double m,s,max_s,sum,sum_sq;
    int wxh	= winx/2;
    int wyh	= winy/2;
    int x_firstth= wxh;
    int y_firstth= wyh;
    int y_lastth = im.rows-wyh-1;
    double winarea = winx*winy;

    max_s = 0;
    for	(int j = y_firstth ; j<=y_lastth; j++){
        sum = sum_sq = 0;

        // for sum array iterator pointer
        double *sum_top_left = im_sum.ptr<double>(j - wyh);
        double *sum_top_right = sum_top_left + winx;
        double *sum_bottom_left = im_sum.ptr<double>(j - wyh + winy);
        double *sum_bottom_right = sum_bottom_left + winx;

        // for sum_sq array iterator pointer
        double *sum_eq_top_left = im_sum_sq.ptr<double>(j - wyh);
        double *sum_eq_top_right = sum_eq_top_left + winx;
        double *sum_eq_bottom_left = im_sum_sq.ptr<double>(j - wyh + winy);
        double *sum_eq_bottom_right = sum_eq_bottom_left + winx;

        sum = (*sum_bottom_right + *sum_top_left) - (*sum_top_right + *sum_bottom_left);
        sum_sq = (*sum_eq_bottom_right + *sum_eq_top_left) - (*sum_eq_top_right + *sum_eq_bottom_left);

        m  = sum / winarea;
        s  = sqrt ((sum_sq - m*sum)/winarea);
        if (s > max_s) max_s = s;

        float *map_m_data = map_m.ptr<float>(j) + x_firstth;
        float *map_s_data = map_s.ptr<float>(j) + x_firstth;
        *map_m_data++ = m;
        *map_s_data++ = s;

        // Shift the window, add and remove	new/old values to the histogram
        for	(int i=1 ; i <= im.cols-winx; i++) {
            sum_top_left++, sum_top_right++, sum_bottom_left++, sum_bottom_right++;

            sum_eq_top_left++, sum_eq_top_right++, sum_eq_bottom_left++, sum_eq_bottom_right++;

            sum = (*sum_bottom_right + *sum_top_left) - (*sum_top_right + *sum_bottom_left);
            sum_sq = (*sum_eq_bottom_right + *sum_eq_top_left) - (*sum_eq_top_right + *sum_eq_bottom_left);

            m  = sum / winarea;
            s  = sqrt ((sum_sq - m*sum)/winarea);
            if (s > max_s) max_s = s;

            *map_m_data++ = m;
            *map_s_data++ = s;
        }
    }

    return max_s;
}



/**********************************************************
 * The binarization routine
 **********************************************************/


void WolfBinarization::NiblackSauvolaWolfJolion (Mat im, Mat output, WolfBinarization::NiblackVersion version,
    int winx, int winy, double k, double dR) {


    double m, s, max_s;
    double th=0;
    double min_I, max_I;
    int wxh	= winx/2;
    int wyh	= winy/2;
    int x_firstth= wxh;
    int x_lastth = im.cols-wxh-1;
    int y_lastth = im.rows-wyh-1;
    int y_firstth= wyh;
    // int mx, my;

    // Create local statistics and store them in a double matrices
    Mat map_m = Mat::zeros (im.rows, im.cols, CV_32F);
    Mat map_s = Mat::zeros (im.rows, im.cols, CV_32F);
    max_s = calcLocalStats (im, map_m, map_s, winx, winy);

    minMaxLoc(im, &min_I, &max_I);

    Mat thsurf (im.rows, im.cols, CV_32F);

    // Create the threshold surface, including border processing
    // ----------------------------------------------------
    for	(int j = y_firstth ; j<=y_lastth; j++) {

        float *th_surf_data = thsurf.ptr<float>(j) + wxh;
        float *map_m_data = map_m.ptr<float>(j) + wxh;
        float *map_s_data = map_s.ptr<float>(j) + wxh;

        // NORMAL, NON-BORDER AREA IN THE MIDDLE OF THE WINDOW:
        for	(int i=0 ; i <= im.cols-winx; i++) {
            m = *map_m_data++;
            s = *map_s_data++;

            // Calculate the threshold
            switch (version) {

                case NIBLACK:
                    th = m + k*s;
                    break;

                case SAUVOLA:
                    th = m * (1 + k*(s/dR-1));
                    break;

                case WOLFJOLION:
                    th = m + k * (s/max_s-1) * (m-min_I);
                    break;

                default:
                    cerr << "Unknown threshold type in ImageThresholder::surfaceNiblackImproved()\n";
                    exit (1);
            }

            // thsurf.fset(i+wxh,j,th);
            *th_surf_data++ = th;


            if (i==0) {
                // LEFT BORDER
                float *th_surf_ptr = thsurf.ptr<float>(j);
                for (int i=0; i<=x_firstth; ++i)
                    *th_surf_ptr++ = th;

                // LEFT-UPPER CORNER
                if (j==y_firstth)
                {
                    for (int u=0; u<y_firstth; ++u)
                    {
                        float *th_surf_ptr = thsurf.ptr<float>(u);
                        for (int i=0; i<=x_firstth; ++i)
                            *th_surf_ptr++ = th;
                    }

                }

                // LEFT-LOWER CORNER
                if (j==y_lastth)
                {
                    for (int u=y_lastth+1; u<im.rows; ++u)
                    {
                        float *th_surf_ptr = thsurf.ptr<float>(u);
                        for (int i=0; i<=x_firstth; ++i)
                            *th_surf_ptr++ = th;
                    }
                }
            }

            // UPPER BORDER
            if (j==y_firstth)
                for (int u=0; u<y_firstth; ++u)
                    thsurf.fset(i+wxh,u,th);

            // LOWER BORDER
            if (j==y_lastth)
                for (int u=y_lastth+1; u<im.rows; ++u)
                    thsurf.fset(i+wxh,u,th);
        }

        // RIGHT BORDER
        float *th_surf_ptr = thsurf.ptr<float>(j) + x_lastth;
        for (int i=x_lastth; i<im.cols; ++i)
            // thsurf.fset(i,j,th);
            *th_surf_ptr++ = th;

        // RIGHT-UPPER CORNER
        if (j==y_firstth)
        {
            for (int u=0; u<y_firstth; ++u)
            {
                float *th_surf_ptr = thsurf.ptr<float>(u) + x_lastth;
                for (int i=x_lastth; i<im.cols; ++i)
                    *th_surf_ptr++ = th;
            }
        }

        // RIGHT-LOWER CORNER
        if (j==y_lastth)
        {
            for (int u=y_lastth+1; u<im.rows; ++u)
            {
                float *th_surf_ptr = thsurf.ptr<float>(u) + x_lastth;
                for (int i=x_lastth; i<im.cols; ++i)
                    *th_surf_ptr++ = th;
            }
        }
    }
    cerr << "surface created" << endl;

    for	(int y=0; y<im.rows; ++y)
    {
        unsigned char *im_data = im.ptr<unsigned char>(y);
        float *th_surf_data = thsurf.ptr<float>(y);
        unsigned char *output_data = output.ptr<unsigned char>(y);
        for	(int x=0; x<im.cols; ++x)
        {
            *output_data = *im_data >= *th_surf_data ? 255 : 0;
            im_data++;
            th_surf_data++;
            output_data++;
        }
    }
}

/**********************************************************
 * The main function
 **********************************************************/

void WolfBinarization::wolfBinarize (cv::Mat input, cv::Mat output)
{
    char version;
    int c;
    int winx=0, winy=0;
    float optK=0.5;
    bool didSpecifyK=true;
    WolfBinarization::NiblackVersion versionCode;
    char *inputname, *outputname, *versionstring=(char *) "w";

        int largest_area = 0;
    int largest_contour_index = 0;
    cv::Rect bounding_rect;


    // Determine the method
    version = versionstring[0];
    switch (version)
    {
        case 'n':
            versionCode = WolfBinarization::NiblackVersion::NIBLACK;
            break;

        case 's':
            versionCode = WolfBinarization::NiblackVersion::SAUVOLA;
            break;

        case 'w':
            versionCode = WolfBinarization::NiblackVersion::WOLFJOLION;
            break;

        default:
            cerr  << "\nInvalid version: '" << version << "'!";
    }



    // Load the image in grayscale mode
    //Mat input = imread("/home/sigmind/Downloads/local_adaptive_binarization-master/lp1.png",CV_LOAD_IMAGE_GRAYSCALE);



    // Treat the window size
    if (winx==0||winy==0) {
        winy = (int) (2.0 * input.rows-1)/3;
        winx = (int) input.cols-1 < winy ? input.cols-1 : winy;
        // if the window is too big, than we asume that the image
        // is not a single text box, but a document page: set
        // the window size to a fixed constant.
        if (winx > 100)
            winx = winy = 40;
    }

    // Threshold
//    Mat output (input.rows, input.cols, CV_8U);
    NiblackSauvolaWolfJolion (input, output, versionCode, winx, winy, optK, 128);

    //imwrite ("/home/sigmind/Downloads/local_adaptive_binarization-master/okokokokokokokokoko.png", output);

}

