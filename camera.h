#ifndef CAMERA_H
#define CAMERA_H


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <string>
#include <typeinfo>
#include <iostream>
#include <QMutex>
#include <QThread>
#include <QDebug>
#include <QPixmap>
#include <vector>
#include <utility>

#include "AI_src/network.h"
#include "AI_src/region_layer.h"
#include "AI_src/cost_layer.h"
#include "AI_src/utils.h"
#include "AI_src/parser.h"
#include "AI_src/box.h"
#include "AI_src/demo.h"
#include "AI_src/option_list.h"
#include "AI_src/blas.h"

#include "AI_src/cuda.h"
#include "person.h"
#include "rectangle.h"
#include "tracking.h"
//#include <cairo/cairo.h>
#include <string.h>
#include <QtConcurrent>
#include "worker.h"

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <glib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <deque>
#include "gstnvdsmeta.h"
//#include "gstnvstreammeta.h"
//#ifndef PLATFORM_TEGRA
#include "gst-nvmessage.h"
//#endif
//#include "gst-nvmessage.h"
using namespace cv;







class Producer : public QThread
{
    //Q_OBJECT

public:

    VideoCapture *cap;
    QMutex *mutx;
    QMutex *abort_mutex;
    int number;
//    std::mutex &mutx;
    Mat &mat;
    bool _abort;

    Producer(VideoCapture *vcap, QMutex *mut, Mat &m, int no, QObject *parent = NULL) : QThread(parent), cap(vcap), mutx(mut), mat(m), number(no)
    {
        abort_mutex = new QMutex();
        _abort = false;
    }

    ~Producer(){
        delete abort_mutex;
    }

    void may_day()
    {
        abort_mutex->lock();
        _abort= true;
        abort_mutex->unlock();
    }

//    void init(VideoCapture *vcap, QMutex &mut, Mat &m)
//    {
//        cap= vcap;
//        mutex = mut;
//        mat = m;
//    }

    void run() override
    {
        printf("inside producer run loop %d\n\n",number);
        while(1)
        {

            abort_mutex->lock();
            if(_abort)
            {
                //qDebug()<<"may day! may day!  ABORT!!!\n";
                abort_mutex->unlock();
                break;
            }
            abort_mutex->unlock();

            if(cap!=NULL && cap->isOpened())
            {
//                printf("trying to lock mutex from producer  <<<<<camera no: %d >>>>>\n",number);
                mutx->lock();
//                printf("mutex locked from producer  <<<<<camera no: %d >>>>>\n",number);
                cap->read(mat);
//                printf("image read from producer  <<<<<camera no: %d >>>>>\n",number);
                mutx->unlock();
//                printf("mutex unlocked from producer  <<<<<camera no: %d >>>>>\n",number);
            }
            QThread::msleep(20);
        }
    }
};

class Camera : public QObject
{
    Q_OBJECT
    //Q_OBJECT
    // >>>>>>>>>>>>> DS Integrate










      // <<<<<<<<<<<<<<<<<<<<<<

    VideoCapture *cap = NULL;
    QMutex *mutx, *parent_mutex, *search_mutex;
    Mat matt, temp_mat;
    Producer *generator;
    int camera_index, gpu_indx;
    int cap_index;
    int prior;
    int imcount;
    char *cap_string;
    bool _abort =false;

//    cairo_surface_t* surfaceLocal = NULL;
//    cairo_t* cairoLocal = NULL;
//    cv::Mat cairoTargetLocal;

//    list *options;
//   // faceRecognition *FR;
//    char *name_list;
//    char **names;
//    image **alphabet;
//    network net;

//    float nms=.4;


  //  Camera *camer;

    // static Camera *theFoo;
   // std::vector<std::string> &face_names;
   // std::vector<dlib::matrix<float,0l,1l>> &face_descriptors;
    std::vector<int> live_tracking_id;

    std::vector<watchcam::rectangle > prev_frame;


    // GstFlowReturn new_preroll(GstAppSink *appsink, gpointer data);
    // GstFlowReturn new_sample(GstAppSink *appsink, gpointer data);


  //  Mat image_to_Mat(image img, int w, int h, int c);

   // image ipl_to_image(IplImage* src);

    void LPRcap(QString encod);
   // int send_to_FR(image p, std::string &label, int imleft, int imtop, int imright, int imbot, std::vector<dlib::matrix<float,0l,1l>> &pic_templates);
    void putTextCairo(cv::Mat &targetImage,
          std::string const& text,
          cv::Point2d centerPoint,
          std::string const& fontFace,
          double fontSize,
          cv::Scalar textColor,
          bool fontItalic,
          bool fontBold);
  // void LPRcap(QString encoded);
  //  int send_to_LPR(image p, std::string &label, int imleft, int imtop, int imright, int imbot, int xPos, int yPos);

  //  void draw_detections_with_FR(image im, image orig, int num, float thresh, box *boxes, float **probs, char **names, image **alphabet, int classes,
                                // std::vector<watchcam::rectangle > &rects);//, std::vector<dlib::matrix<float,0l,1l>> &pic_templates);
  //  void save_image_jpeg(image im, const char *name, int left, int top, int right, int bot);

    void init(int gpu_indx, int prior);


public:
    explicit Camera(QObject *parent = 0) ;
      //  QObject(parent), face_names(names), face_descriptors(descriptors)

//    GMainLoop *loop = NULL;
//      GstElement *pipeline = NULL, *streammux = NULL, *sink = NULL, *pgie = NULL,
//          *nvvidconv = NULL, *nvosd = NULL, *tiler = NULL;
//    // #ifdef PLATFORM_TEGRA
//      GstElement *transform = NULL;
//    // #endif

//static GstPadProbeReturn tiler_src_pad_buffer_probe (GstPad * pad, GstPadProbeInfo * info, gpointer u_data);
//static gboolean bus_call (GstBus * bus, GstMessage * msg, gpointer data);

//      GstBus *bus = NULL;
//      guint bus_watch_id;
//      GstPad *tiler_src_pad = NULL;
//      guint i, num_sources=1;
//      guint tiler_rows, tiler_columns;
//      guint pgie_batch_size;

//      GstElement *video_caps, *capsfilter;
//             GstElement *nvvidconv1 = NULL,
//                    *filter1 = NULL,
//                    *filter2 = NULL,
//                    *filter3 = NULL,
//                    *videoconvert = NULL,
//                     *videoconvert1 = NULL,
//                    *filter4 = NULL,
//                    *x264enc = NULL,
//                    *qtmux = NULL;


    Camera(int cam_indx, int index, QMutex *par, int pri, QObject *parent = NULL);


    Camera(int cam_indx, const char *file, QMutex *par, int pri, QObject *parent = NULL);

    ~Camera();

     //void sendToUI(cv::Mat mat, cv::Mat omat, std::vector< watchcam::rectangle > rects);
   // void face_database_update();

    void start();
    void end();
    void reset_object_threshold(double x);

    float thresh, hier_thresh;
    QString plateData;

//    static GstPadProbeReturn tiler_src_pad_buffer_probe (GstPad * pad, GstPadProbeInfo * info, gpointer u_data);
//    static gboolean bus_call (GstBus * bus, GstMessage * msg, gpointer data);
//    static void cb_newpad (GstElement * decodebin, GstPad * decoder_src_pad, gpointer data);
//    static void decodebin_child_added (GstChildProxy * child_proxy, GObject * object, gchar * name, gpointer user_data);
//    static GstElement * create_source_bin (guint index, gchar * uri);
private:

    QThread *thread;

    Worker *worker;
    QFuture<void> t1;
signals:

   //void ui_go(cv::Mat, cv::Mat, std::deque< watchcam::rectangle >);
    void start_requested();
    void start_producer();


public slots:
    void go();
   void sendToUI(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >);
    void inf_loop();
    //std::vector< watchcam::rectangle > rect_value(std::vector< watchcam::rectangle > rectS);

    void ui_response(QPixmap img);
    //void addNewLPR(QString enc);
signals:
    void requestUpdateLPR(QString enc);
    void ui_go(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >);
   // void send_rect_value(std::vector< watchcam::rectangle > );
};

#endif // CAMERA_H
