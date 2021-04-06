#ifndef WARKER_H
#define WARKER_H

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <iostream>
#include <string>
#include <QObject>
#include <QMutex>
#include <QWidget>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <iostream>
#include <string>
#include "person.h"
#include<QDebug>


#include <DatabaseConnection/sqlite_connection.h> // database connection
#include<QElapsedTimer>
#include<QTime>

// ----------------------------------------------------------------------------------------

// The next bit of code defines a ResNet network.  It's basically copied
// and pasted from the dnn_imagenet_ex.cpp example, except we replaced the loss
// layer with loss_metric and made the network somewhat smaller.  Go read the introductory
// dlib DNN examples to learn what all this stuff means.
//
// Also, the dnn_metric_learning_on_images_ex.cpp example shows how to train this network.
// The dlib_face_recognition_resnet_model_v1 model used by this example was trained using
// essentially the code shown in dnn_metric_learning_on_images_ex.cpp except the
// mini-batches were made larger (35x15 instead of 5x5), the iterations without progress
// was set to 10000, the jittering you can see below in jitter_image() was used during
// training, and the training dataset consisted of about 3 million images instead of 55.
// Also, the input layer was locked to images of size 150.
//template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
//using residual = dlib::add_prev1<block<N,BN,1,dlib::tag1<SUBNET>>>;

//template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
//using residual_down = dlib::add_prev2<dlib::avg_pool<2,2,2,2,dlib::skip1<dlib::tag2<block<N,BN,2,dlib::tag1<SUBNET>>>>>>;

//template <int N, template <typename> class BN, int stride, typename SUBNET>
//using block  = BN<dlib::con<N,3,3,1,1,dlib::relu<BN<dlib::con<N,3,3,stride,stride,SUBNET>>>>>;

//template <int N, typename SUBNET> using ares      = dlib::relu<residual<block,N,dlib::affine,SUBNET>>;
//template <int N, typename SUBNET> using ares_down = dlib::relu<residual_down<block,N,dlib::affine,SUBNET>>;

//template <typename SUBNET> using alevel0 = ares_down<256,SUBNET>;
//template <typename SUBNET> using alevel1 = ares<256,ares<256,ares_down<256,SUBNET>>>;
//template <typename SUBNET> using alevel2 = ares<128,ares<128,ares_down<128,SUBNET>>>;
//template <typename SUBNET> using alevel3 = ares<64,ares<64,ares<64,ares_down<64,SUBNET>>>>;
//template <typename SUBNET> using alevel4 = ares<32,ares<32,ares<32,SUBNET>>>;

//using anet_type = dlib::loss_metric<dlib::fc_no_bias<128,dlib::avg_pool_everything<
//                            alevel0<
//                            alevel1<
//                            alevel2<
//                            alevel3<
//                            alevel4<
//                            dlib::max_pool<3,3,2,2,dlib::relu<dlib::affine<dlib::con<32,7,7,2,2,
//                            dlib::input_rgb_image_sized<150>
//                            >>>>>>>>>>>>;

class Warker : public QObject
{
    Q_OBJECT

    template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
    using residual = dlib::add_prev1<block<N,BN,1,dlib::tag1<SUBNET>>>;

    template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
    using residual_down = dlib::add_prev2<dlib::avg_pool<2,2,2,2,dlib::skip1<dlib::tag2<block<N,BN,2,dlib::tag1<SUBNET>>>>>>;

    template <int N, template <typename> class BN, int stride, typename SUBNET>
    using block  = BN<dlib::con<N,3,3,1,1,dlib::relu<BN<dlib::con<N,3,3,stride,stride,SUBNET>>>>>;

    template <int N, typename SUBNET> using ares      = dlib::relu<residual<block,N,dlib::affine,SUBNET>>;
    template <int N, typename SUBNET> using ares_down = dlib::relu<residual_down<block,N,dlib::affine,SUBNET>>;

    template <typename SUBNET> using alevel0 = ares_down<256,SUBNET>;
    template <typename SUBNET> using alevel1 = ares<256,ares<256,ares_down<256,SUBNET>>>;
    template <typename SUBNET> using alevel2 = ares<128,ares<128,ares_down<128,SUBNET>>>;
    template <typename SUBNET> using alevel3 = ares<64,ares<64,ares<64,ares_down<64,SUBNET>>>>;
    template <typename SUBNET> using alevel4 = ares<32,ares<32,ares<32,SUBNET>>>;

    using anet_type = dlib::loss_metric<dlib::fc_no_bias<128,dlib::avg_pool_everything<
    alevel0<
    alevel1<
    alevel2<
    alevel3<
    alevel4<
    dlib::max_pool<3,3,2,2,dlib::relu<dlib::affine<dlib::con<32,7,7,2,2,
    dlib::input_rgb_image_sized<150>
    >>>>>>>>>>>>;


    //std::vector<dlib::matrix<float,0,1>> load_template(std::vector<std::string> &names, dlib::frontal_face_detector &detector, std::vector<dlib::matrix<dlib::rgb_pixel>> &templates, dlib::shape_predictor &sp, anet_type &face_net);

public:
    explicit Warker(QObject *parent = 0);
    /**
     * @brief Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void load_template();
    std::vector<std::string> names;
    //cv::Mat temp_img;
    std::vector<dlib::matrix<float,0l,1l>> template_descriptors;
    std::vector<dlib::matrix<dlib::rgb_pixel>> detected_faces;
    //dlib::image_window win;

    // Load face detection and pose estimation models.
    dlib::frontal_face_detector face_detector;
    // We will also use a face landmarking model to align faces to a standard pose:  (see face_landmark_detection_ex.cpp for an introduction)
    dlib::shape_predictor sp;

    // And finally we load the DNN responsible for face recognition.
    anet_type face_net;
    std::vector<dlib::matrix<dlib::rgb_pixel>> templates;
    std::vector<dlib::matrix<dlib::rgb_pixel>> new_templates;
    // void setup(std::vector<std::string> &names, std::vector<dlib::matrix<float,0l,1l>> &descriptors);
    void requestWark();
    /**
     * @brief Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     */
    // void GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory);
    void abort();
    QString plateNum;
    QPixmap platePix;
    int plateIndx;
    cv::Mat QImage2Mat(const QImage& src);
    // std::vector<dlib::matrix<float,0,1>> load_template( std::vector<std::string> &names, dlib::frontal_face_detector &detector, std::vector<dlib::matrix<dlib::rgb_pixel>> &templates, dlib::shape_predictor &sp, anet_type &face_net);

    //std::vector<dlib::matrix<float,0,1>> template_descriptors;

    // void load_template( std::vector<std::string> &names, dlib::frontal_face_detector &detector, std::vector<dlib::matrix<rgb_pixel>> &templates, dlib::shape_predictor &sp, anet_type &face_net);
    // void GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory);

    // dlib::shape_predictor sp;
    // std::vector<std::string> names;
    // anet_type face_net;

    dlib::matrix<float,0,1> face_descriptor;
    std::vector<dlib::matrix<dlib::rgb_pixel>> jitter_image(const dlib::matrix<dlib::rgb_pixel>& img);


private:
    /**
     * @brief Process is aborted when @em true
     */
    bool _abort;
    /**
     * @brief @em true when Worker is doing work
     */
    bool _warking;
    /**
     * @brief Protects access to #_abort
     */
    QMutex FRmutex;

    bool OCRed;
    int im_count=0;


signals:
    /**
     * @brief This signal is emitted when the Worker request to Work
     * @sa requestWork()
     */
    void warkRequested();
    /**
     * @brief This signal is emitted when counted value is changed (every sec)
     */
    void valueFRChanged(QPixmap , QString , int , double, dlib::matrix<float,(long)0,(long)1>);

    void faceValue(QPixmap pic, QString str, int indx, dlib::matrix<float,0,1> pic_template);
    //void valueChanged(QString plate);

    /**
     * @brief This signal is emitted when process is finished (either by counting 60 sec or being aborted)
     */
    // void finished(QNetworkReply*rep);

    void finishedFR();
    //  void plateData(QString p);

public slots:


    // load image into runtime
    bool loadImageIntoLoadTemplate(QString name_, QString path);

    // delete from template
    void deleteFromTemplate(QString image_path, QString image_name);

    /**
     * @brief Does something
     *
     * Counts 60 sec in this example.
     * Counting is interrupted if #_aborted is set to true.
     */

    void doWark(cv::Mat picture, QString str, int indx);
    // void FR_database_update();
//    QString recognition(cv::Mat &temp_img);
    //  QString recognize_face(cv::Mat faceReq);
    // cv::Mat QImage2Mat(QImage const& src);
    // QImage Mat2QImage(cv::Mat const& src);
    //  QString LPRcap(QString encod);
    //  void receive_template();
    //  void setup(std::vector<std::string> &names, std::vector<dlib::matrix<float,0l,1l>> &descriptors);
    //  QString recognize(cv::Mat &temp_img,std::vector<dlib::matrix<float,0l,1l>> &pic_templates);
    //void syncRequestFinished(QNetworkReply*rep);
    //void LPRprint(QPixmap pic, QString str, int indx);
    // void extractPlate(QPixmap picture, QString str, int indx);
};
//std::vector<dlib::matrix<float,0,1>> load_template( std::vector<std::string> &names, dlib::frontal_face_detector &detector, std::vector<dlib::matrix<dlib::rgb_pixel>> &templates, dlib::shape_predictor &sp, anet_type &face_net);
void GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory);


#endif // WARKER_H
