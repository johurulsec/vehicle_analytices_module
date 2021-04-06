#include "face.h"
#include "ui_face.h"
#include "warker.h"
#include <QTimer>
#include <QEventLoop>
#include <istream>
#include <QThread>
#include <QDebug>
#include <sstream>
#include <iostream>
#include <QProcess>
#include <string>
#include <cstring>
#include <qpainter.h>
#include <QColor>
#include <fstream>
#include <qbuffer.h>
#include <QBuffer>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include <curl/curl.h>

#include <sstream>




//#include "faceRecognition.h"
#include <dlib/opencv.h>
#include <sstream>
#include <QDebug>
#include <opencv2/imgproc/imgproc.hpp>

using namespace dlib;
using namespace std;
int imNo;

//// ----------------------------------------------------------------------------------------

/// gender prediction start
// This block of statements defines the network as proposed for the CNN Model I.
// We however removed the "dropout" regularization on the activations of convolutional layers.
template <int N, template <typename> class BN, int stride, typename SUBNET>
using block_gender = BN<con<N, 3, 3, stride, stride, relu<BN<con<N, 3, 3, stride, stride, SUBNET>>>>>;

//template <int N, typename SUBNET> using res__gender = relu<block_gender<N, bn_con, 1, SUBNET>>;
template <int N, typename SUBNET> using ares__gender = relu<block_gender<N, affine, 1, SUBNET>>;

template <typename SUBNET> using alevel1_gender = avg_pool<2, 2, 2, 2, ares__gender<64, SUBNET>>;
template <typename SUBNET> using alevel2_gender = avg_pool<2, 2, 2, 2, ares__gender<32, SUBNET>>;

using agender_type = loss_multiclass_log<fc<2, multiply<relu<fc<16, multiply<alevel1_gender<alevel2_gender< input_rgb_image_sized<32>>>>>>>>>;

agender_type net_gender;
//// ----------------------------------------------------------------------------------------

//#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
//#define PBWIDTH 40
//void display_progressbar(float percentage)
//{
//    uint32_t val = (int)(percentage * 100);
//    uint32_t lpad = (int)(percentage * PBWIDTH);
//    uint32_t rpad = PBWIDTH - lpad;
//    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
//    fflush(stdout);
//}

// ----------------------------------------------------------------------------------------

// An helper function to load dataset for testing.
//enum label_ : uint16_t
//{
//    female_label,
//    male_label,
//};
//struct image_info
//{
//    enum label_ label_image;
//    string filename;
//};

//std::vector<image_info> get_image_listing(
//        const std::string& images_folder,
//        const enum label_& label
//        )
//{
//    std::vector<image_info> results;
//    image_info temp;
//    temp.label_image = label;

//    auto dir = directory(images_folder);
//    for (auto image_file : dir.get_files())
//    {
//        temp.filename = image_file;
//        results.push_back(temp);
//    }

//    return results;
//}
//std::vector<image_info> get_train_listing_females(const std::string& ifolder) { return get_image_listing(ifolder, female_label); }
//std::vector<image_info> get_train_listing_males(const std::string& ifolder) { return get_image_listing(ifolder, male_label); }
/// gender prediction end
///
/// age prediction
// ----------------------------------------------------------------------------------------

// This block of statements defines a Resnet-10 architecture for the age predictor.
// We will use 81 classes (0-80 years old) to predict the age of a face.
const unsigned long number_of_age_classes = 81;

// The resnet basic block.
template<
        int num_filters,
        template<typename> class BN,  // some kind of batch normalization or affine layer
        int stride,
        typename SUBNET
        >
using basicblock = BN<con<num_filters, 3, 3, 1, 1, relu<BN<con<num_filters, 3, 3, stride, stride, SUBNET>>>>>;

// A residual making use of the skip layer mechanism.
template<
        template<int, template<typename> class, int, typename> class BLOCK,  // a basic block defined before
        int num_filters,
        template<typename> class BN,  // some kind of batch normalization or affine layer
        typename SUBNET
        > // adds the block to the result of tag1 (the subnet)
using residual = add_prev1<BLOCK<num_filters, BN, 1, tag1<SUBNET>>>;

// A residual that does subsampling (we need to subsample the output of the subnet, too).
template<
        template<int, template<typename> class, int, typename> class BLOCK,  // a basic block defined before
        int num_filters,
        template<typename> class BN,
        typename SUBNET
        >
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<BLOCK<num_filters, BN, 2, tag1<SUBNET>>>>>>;

// Residual block with optional downsampling and batch normalization.
template<
        template<template<int, template<typename> class, int, typename> class, int, template<typename>class, typename> class RESIDUAL,
        template<int, template<typename> class, int, typename> class BLOCK,
        int num_filters,
        template<typename> class BN,
        typename SUBNET
        >
using residual_block = relu<RESIDUAL<BLOCK, num_filters, BN, SUBNET>>;

template<int num_filters, typename SUBNET>
using aresbasicblock_down = residual_block<residual_down, basicblock, num_filters, affine, SUBNET>;

// Some useful definitions to design the affine versions for inference.
template<typename SUBNET> using aresbasicblock256 = residual_block<residual, basicblock, 256, affine, SUBNET>;
template<typename SUBNET> using aresbasicblock128 = residual_block<residual, basicblock, 128, affine, SUBNET>;
template<typename SUBNET> using aresbasicblock64  = residual_block<residual, basicblock, 64, affine, SUBNET>;

// Common input for standard resnets.
template<typename INPUT>
using aresnet_input = max_pool<3, 3, 2, 2, relu<affine<con<64, 7, 7, 2, 2, INPUT>>>>;

// Resnet-10 architecture for estimating.
template<typename SUBNET>
using aresnet10_level1 = aresbasicblock256<aresbasicblock_down<256, SUBNET>>;
template<typename SUBNET>
using aresnet10_level2 = aresbasicblock128<aresbasicblock_down<128, SUBNET>>;
template<typename SUBNET>
using aresnet10_level3 = aresbasicblock64<SUBNET>;
// The resnet 10 backbone.
template<typename INPUT>
using aresnet10_backbone = avg_pool_everything<
aresnet10_level1<
aresnet10_level2<
aresnet10_level3<
aresnet_input<INPUT>>>>>;

using apredictor_t = loss_multiclass_log<fc<number_of_age_classes, aresnet10_backbone<input_rgb_image>>>;
// Helper function to estimage the age
uint8_t get_estimated_age(matrix<float, 1, number_of_age_classes>& p, float& confidence)
{
    float estimated_age = (0.25f * p(0));
    confidence = p(0);

    for (uint16_t i = 1; i < number_of_age_classes; i++) {
        estimated_age += (static_cast<float>(i) * p(i));
        if (p(i) > confidence) confidence = p(i);
    }

    return std::lround(estimated_age);
}

apredictor_t net_age;

// ----------------------------------------------------------------------------------------

void GetFilesInDirectory(std::vector<string> &out, const string &directory)
{
    //qDebug()<<directory.c_str()<<endl;
#ifdef WINDOWS
    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return; /* No files found */

    do {
        const string file_name = file_data.cFileName;
        const string full_file_name = directory + "/" + file_name;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (file_name[0] == '.')
            continue;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
#else
    DIR *dir;
    class dirent *ent;
    class stat st;

    dir = opendir(directory.c_str());
    while ((ent = readdir(dir)) != NULL) {
        const string file_name = ent->d_name;
        const string full_file_name = directory + "/" + file_name;

        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory)
            continue;
        std::string f = "";
        int k = file_name.size();
        for(int i=file_name.size()-1; i>=0; i--)
        {
            if(file_name[i]=='.')
            {
                k = i;
                break;
            }
        }
        for(int i=0; i<k; i++)
        {
            f += file_name[i];
        }
        out.push_back(f);
        out.push_back(full_file_name);
    }
    closedir(dir);
#endif
} // GetFilesInDirectory


cv::Mat Warker::QImage2Mat(const QImage& src) {
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat result = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0,  1,1,  2,2 };
    cv::mixChannels( &mat, 1, &result, 1, from_to, 3 );
    return result;
}




Warker::Warker(QObject *parent) :
    QObject(parent)
{
    _warking =false;
    _abort = false;
    OCRed = false;

    printf(">>>>>print 1<<<<<<<<<\n");
    // Load face detection and pose estimation models.
    // face_detector = dlib::get_frontal_face_detector();

    printf(">>>>>>print 2<<<<<<<<<\n");
    //template_descriptors = load_template( templates_names, face_detector, sp, face_net );

    // deserialize("./.weight/LM-5p.dat") >> sp;
    // printf(">>>>>>>>>print 2.01<<<<<<<<<<<\n");
    // deserialize("./.weight/FR-Resnetv2.dat") >> face_net;

    //printf(">>>> print 2.1<<<<<<\n");

    //...............retreiving faces moved to mainWindow.cpp..............//

    //printf("templates size: %d  template_descriptors size %d\n\n",templates.size(),template_descriptors.size());
    // printf(">>>>>>>print 3<<<<<<<<\n");
    faceRecThreshVal = new myStyles();
    faceRecThreshValStore = faceRecThreshVal->faceSensitivityValue;
    //    //qDebug()<<"myStyles::faceSensitivitySlider value constr ="<<faceRecThreshValStore;
}

void Warker::requestWark()
{
    FRmutex.lock();
    _warking = true;
    _abort = false;
    qDebug()<<"test Request warker start in Thread "<<thread()->currentThreadId();
    FRmutex.unlock();

    emit warkRequested();
}


void Warker::load_template()
{
    face_detector = get_frontal_face_detector();
    //    deserialize("./.weight/LM-68p.dat") >> sp;
    deserialize("./.weight/LM-5p.dat") >> sp;
    deserialize("./.weight/FR-Resnetv2.dat") >> face_net;
    deserialize("./.weight/shape_predictor_5_face_landmarks.dat") >> sp_gender;
    deserialize("./.weight/shape_predictor_5_face_landmarks.dat") >> sp_age;
    static const char* model_net_filename_age = "./.weight/dnn_age_predictor_v1.dat";
    deserialize(model_net_filename_age) >> net_age;
    static const char* model_net_filename_gender = "./.weight/dnn_gender_classifier_v1.dat";
    deserialize(model_net_filename_gender) >> net_gender;
    qDebug()<<"done\n";

    std::vector<dlib::matrix<dlib::rgb_pixel>> templates;
    // if(names.size()==0)
    std::ifstream TD_file("face-serial.dat");
    std::ifstream name_file("face-names-serial.dat");

    if(TD_file.good() && name_file.good()) {
        deserialize("face-serial.dat") >> template_descriptors;
        deserialize("face-names-serial.dat") >> names;
        qDebug()<<"johurul TD_file good "<<template_descriptors.size();
    }
    else {


        //if(template_descriptors.size() == 0) {
        GetFilesInDirectory(names,"./faces/temp_late");



        for(int i=0; i<names.size(); i++) cout<< names[i]<<"   "<<i<<" "<<names.size()<<endl;


        //std::vector<matrix<rgb_pixel>> templates;
        //qDebug()<<"pre-WTF?\n";
        matrix<rgb_pixel> temp;
        //qDebug()<<"WTF??\n";
        for(int i=1; i<names.size(); i+=2)
        {
            qDebug("loading  %s...\n",names[i-1].c_str());
            try{
                dlib::load_jpeg(temp, names[i]);
//                dlib::load_png(temp, names[i]);

                for (auto face : face_detector(temp))
                {
                    auto shape = sp(temp, face);
                    matrix<rgb_pixel> face_chip;
                    extract_image_chip(temp, get_face_chip_details(shape,150,0.25), face_chip);
                    templates.push_back(move(face_chip));
                }
                qDebug("%s  loaded...\n",names[i-1].c_str());
            }catch(...){

            }

        }
        //std::vector<matrix<float,0,1>>
        template_descriptors = face_net(templates);
        //    //   setup(names,template_descriptors);
        //            for(int i=0; i<names.size(); i++)
        //            {
        //                names.push_back(names[i]);
        //            }

        //            for(int i=0; i<template_descriptors.size(); i++)
        //            {
        //                template_descriptors.push_back(template_descriptors[i]);
        //            }

        serialize("face-serial.dat") << template_descriptors;
        serialize("face-names-serial.dat") << names;
    }
    //qDebug()<<"Loading Done\n";
    //  return template_descriptors;
}






void Warker::abort()
{
    FRmutex.lock();
    if (_warking) {
        _abort = true;
        ////qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    FRmutex.unlock();
}

//void Worker::extractPlate(QPixmap picture,QString str,int indx)
//{
//    std::cout << "---------- Plate EXTRACTED---------------------" << std::endl;
//   // return plate;
//    emit valueChanged(picture, str,indx);

//}



//void Warker::setup(std::vector<std::string> &names, std::vector<dlib::matrix<float,0l,1l>> &descriptors)
//{
//    for(int i=0; i<names.size(); i++)
//    {
//        names.push_back(names[i]);
//    }

//    for(int i=0; i<descriptors.size(); i++)
//    {
//        template_descriptors.push_back(descriptors[i]);
//    }
//}


std::vector<matrix<rgb_pixel>> Warker::jitter_image(const matrix<rgb_pixel>& img)
{
    // All this function does is make 100 copies of img, all slightly jittered by being
    // zoomed, rotated, and translated a little bit differently. They are also randomly
    // mirrored left to right.
    //    thread_local dlib::rand rnd;

    //    std::vector<matrix<rgb_pixel>> crops;
    //    for (int i = 0; i < 100; ++i)
    //        crops.push_back(jitter_image(img));

    //    return crops;

    thread_local random_cropper cropper;
    cropper.set_chip_dims(150,150);
    cropper.set_randomly_flip(true);
    cropper.set_max_object_size(0.99999);
    cropper.set_background_crops_fraction(0);
    //cropper.set_min_object_size(0.97);
    cropper.set_translate_amount(0.02);
    cropper.set_max_rotation_degrees(3);

    std::vector<mmod_rect> raw_boxes(1), ignored_crop_boxes;
    raw_boxes[0] = shrink_rect(get_rect(img),3);
    std::vector<matrix<rgb_pixel>> crops;

    matrix<rgb_pixel> temp;
    for (int i = 0; i < 15; ++i)
    {
        cropper(img, raw_boxes, temp, ignored_crop_boxes);
        crops.push_back(move(temp));
    }
    return crops;
}

void Warker::checkFun()
{
    //qDebug() << "Check fun" << endl;
}

bool Warker::loadImageIntoLoadTemplate(QString name_, QString newFace)
{


    //  FRmutex.lock();
    //_warking = true;
    // FRmutex.unlock();

    //    name_ = "xyz";
    //    newFace = "/home/sigmind/watchcam-testedOK/face.png";
    std::vector<dlib::matrix<dlib::rgb_pixel>> new_templates;

    std::string name = name_.toStdString();
    //    names.push_back(name); // name push into names
    //    names = {name};

    // new_templates  = templates;

    std::string face_path = newFace.toUtf8().constData();
    //    names.push_back(face_path);
    //    names = {name, face_path};
//    qDebug() << "loadImageIntoLoadTemplate method name: "<<name<<" face_path: "<<face_path;

    matrix<rgb_pixel> temp;

    try{
        qDebug() << " <<<<<<<<<<<<<<<<<<<< Inside >>>>>>>>>>>>>>>>>>>>>>>>>>>>> ";
//        dlib::load_png(temp, face_path);
        dlib::load_jpeg(temp, face_path);

        //qDebug() << "after load png of loadImageIntoLoadTemplate in warker";

        //    std::vector<rectangle> rectNew = face_detector(temp);

        //     if(rectNew.size() == 0)
        //     {
        //         //qDebug() << " ERROR !! Face not detected in image. Try another \n";
        //     }

        unsigned long previous_size = new_templates.size();

        for (auto face : face_detector(temp))
        {
            auto shape = sp(temp, face);
            matrix<rgb_pixel> face_chip;
            extract_image_chip(temp, get_face_chip_details(shape,150,0.25), face_chip);
            new_templates.push_back(move(face_chip));
        }

        //    //qDebug() << "Templat " << template_descriptors.size();

        //    //qDebug() << "Names size = " << names.size();
        //    //qDebug() << "Template descrip = " << previous_size << " " << templates.size();

        if(previous_size == new_templates.size())
        {
            qDebug() << " ERROR !! Face not detected in image. Try another \n";
            // FRmutex.unlock();
            return false;

        }
        else
        {
            qDebug() << "j Name and face push" << endl;

            //FRmutex.lock();
            // _warking = true;

            //        QEventLoop loop;
            //        QTimer::singleShot(100, &loop, SLOT(quit()));
            //        loop.exec();
            //qDebug() << "Size of template and name 1" << names.size() << " " << template_descriptors.size();
            names.push_back(name);
            names.push_back(face_path);

            std::vector<dlib::matrix<float,0l,1l>> add_descriptor = face_net(new_templates);
            template_descriptors.insert(end(template_descriptors), begin(add_descriptor), end(add_descriptor));

            //qDebug() << "Size of template and name 2" << names.size() << " " << template_descriptors.size();

            serialize("face-serial.dat") << template_descriptors;
            serialize("face-names-serial.dat") << names;
            //_abort = false;
            // FRmutex.unlock();
            //        emit finishedFR();

            return true;
        }
    }catch(...){
        qDebug() << "j Exception thrown";
        return false;
//        return true;
    }


}

void Warker::deleteFromTemplate(QString image_path, QString image_name)
{
    //qDebug() << ".......... deleteFromTemplate ..........." << endl;

    FRmutex.lock();

    std::string im_path = image_path.toUtf8().constData();
    std::string im_na = image_name.toUtf8().constData();

    std::vector<std::string>::iterator it_im_name = std::find(names.begin(), names.end(), im_na);
    //    //    std::vector<dlib::matrix<float,0l,1l>>::iterator it_im_path = std::find(template_descriptors.begin(), template_descriptors.end(), im_na);

    if (it_im_name != names.end()){
        //        std::cout << "Element Found" << std::endl;

        int index = std::distance(names.begin(), it_im_name);
        template_descriptors.erase(template_descriptors.begin() + index);

    }

    names.erase(std::remove(names.begin(), names.end(), im_na), names.end());
    names.erase(std::remove(names.begin(), names.end(), im_path), names.end());

    FRmutex.unlock();

    //qDebug() << ".......... end deleteFromTemplate ..........." << endl;

}

bool Warker::checkFaceInPerson(cv::Mat person)
{
    bool found_person = false;
    cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

    person.copyTo(facadeColor);




    std::string tempFace;
    QString faceID;


    array2d<rgb_pixel> img;
    dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));



    std::vector<matrix<rgb_pixel>> faces;

    rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    std::vector<rectangle> rects = face_detector(img);

    rects.push_back(rect);
    cout << "Rect Width : " << facadeColor.cols << endl;
    cout << "Rect Height: " << facadeColor.rows << endl;

    for (auto face : rects)
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces.push_back(move(face_chip));

    }


    //qDebug()<<"after clear rects sz ";

    //    //qDebug()<<"loop auto face "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

    //    milisecTimer.restart();
    //    nanosecTimer.restart();
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (faces.size() > 0)
    {
        found_person = true;
    }
    return found_person;
}


void Warker::doWark(cv::Mat m_pic, cv::Mat picture, QString str, int indx, float FRThreshold, int fpsValue, bool sus_check, QString color)
{
    //    qDebug()<<"Starting warker process in Thread "<<thread()->currentThreadId() << " sus check " << sus_check;
    //    //qDebug()<<"frthreshold of dowark "<<FRThreshold;



    im_count++;
    // QImage image = picture.toImage();
    cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

    picture.copyTo(facadeColor);




    std::string tempFace;
    QString faceID;


    array2d<rgb_pixel> img;
    dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));



    std::vector<matrix<rgb_pixel>> faces;

    rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    std::vector<rectangle> rects = face_detector(img);

    rects.push_back(rect);
    cout << "Rect Width : " << facadeColor.cols << endl;
    cout << "Rect Height: " << facadeColor.rows << endl;

    for (auto face : rects)
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces.push_back(move(face_chip));

    }


    //qDebug()<<"after clear rects sz ";

    //    //qDebug()<<"loop auto face "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

    //    milisecTimer.restart();
    //    nanosecTimer.restart();
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (faces.size() == 0)
    {

    }
    else
    {


        QString gender = /*//qDebug()<< "Male or female === " << */genderPredict(picture);

        if(!gender.isEmpty()){

            int age = agePredict(picture);
            //qDebug() << "Male or female === "<< gender << " " << age;

            std::vector<matrix<float,0,1>> face_descriptors = face_net(faces);


            //qDebug() << "face descriptors Size in dowark" <<face_descriptors.size();


            //            std::vector<matrix<float,0,1>> face_descriptors;
            //                for(int i=0; i<faces.size(); i++)
            //                {
            //                   // matrix<float,0,1> face_descriptor = mean(mat(face_net(jitter_image(faces[i]))));

            //                    face_descriptor = mean(mat(face_net(jitter_image(faces[i]))));
            //                   // matrix<float,0,1> face_descriptor = mean(mat(face_net(faces[i])));
            //                    face_descriptors.push_back( face_descriptor );
            //                }

            // In particular, one simple thing we can do is face clustering.  This next bit of code
            // creates a graph of connected faces and then uses the Chinese whispers graph clustering
            // algorithm to identify how many people there are and which faces belong to whom.
            // std::vector<sample_pair> edges;

            for (size_t i = 0; i < face_descriptors.size(); ++i)
            {

                double mn=100.0; int mtch=-1;

                //qDebug() << "Template Descriptors Size in dowark" <<template_descriptors.size();
                //qDebug() << "Names size in dowark" << names.size();

                bool authorized_or_not = false;
                double confidence = 0.0;
                QPixmap pict;
                QString str_to_float;

                for (size_t j = 0; j < template_descriptors.size(); ++j)
                {
                    // Faces are connected in the graph if they are close enough.  Here we check if
                    // the distance between two face descriptors is less than 0.6, which is the
                    // decision threshold the network was trained to use.  Although you can
                    // certainly use any other threshold you find useful.

                    //                        if(mn> length(face_descriptors[i]-template_descriptors[j]) )
                    //                        {
                    mn = length(face_descriptors[i]-template_descriptors[j]);
                    //qDebug()<<"mn value of between face des and templte des teste"<<mn;
                    //                            mtch = j;
                    //                        }
                    //}

                    //                //qDebug() << "ELSE";
                    //                time_t seconds;
                    //                time(&seconds);
                    //                std::stringstream ss;
                    //                ss << seconds;
                    //                std::string ts = ss.str();

                    //  if (length(face_descriptors[i]-template_descriptors[j]) < 0.45)// given that, 0.45 default threshold value
                    //                double confidence;
                    if (length(face_descriptors[i]-template_descriptors[j]) < FRThreshold /*&& sus_check == false*/)  // The threshold of dace match
                    {
                        //qDebug()<<"FRTheshold >>"<<FRThreshold;
                        confidence = mn*100;
                        confidence = 100-confidence;
                        tempFace = names[j+j];// + "@ Confidence =" + std::to_string(mn);
                        // win.add_overlay(dlib::image_window::overlay_rect(rects[i], rgb_pixel(0,255,0),temp));
                        //cout<< "face no: "<<i<<" similar to : " <<names[j+j]<<endl;
                        //int m=0;
                        // std::string ms = std::to_string(mn) ;
                        // string path = "./detected/" + ms + names[j + j] + ts;
                        // save_jpeg(faces[i], path);
                        //qDebug()<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"<<confidence;



                        faceID = QString::fromStdString(tempFace);




                        //                    indx = (int)confidence;
                        // //qDebug() << "InIf";
                        //                    emit valueFRChanged(picture, faceID, indx);
                        //                    QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));
                        // cv::cvtColor(facadeColor, facadeColor, cv::COLOR_GRAY2BGR);// GRAY to BGR
                        pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                        str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                        confidence = str_to_float.toFloat();

                        QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));;

                        faceID = str;
                        emit valueFRChanged(ma_pic, pict, faceID, indx, confidence, face_descriptors[i], fpsValue, 1, gender, age, color);

                        authorized_or_not = true;
                        break;// since, expected value have got
                    }

                    confidence = 0.0;
                }
                if(authorized_or_not == false && sus_check == true)
                {
                    tempFace = "SUSPECT ??";
                    faceID = QString::fromStdString(tempFace);


                    pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                    //                    //emit valueFRChanged(pict, faceID, indx, 0.50, face_descriptors[i]);

                    //                    //                    loadDetectedFace();
                    //                    //                    detected_names.push_back(tempFace);
                    //                    //                    detected_temp_descriptors.push_back(face_descriptors[i]);
                    //                    //                    serialize("detected-face-serial.dat") << detected_temp_descriptors;
                    //                    //                    serialize("detected-face-names-serial.dat") << detected_names;
                    //                    ////qDebug() << "Is lam " << detected_temp_descriptors.size() << " " << detected_names.size();

                    confidence = mn*100;
                    confidence = 100-confidence;
                    str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                    confidence = str_to_float.toFloat();
                    QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));
                    faceID = str;
                    emit valueFRChanged(ma_pic, pict, faceID, indx, confidence, face_descriptors[i], fpsValue, 0, gender, age, color);
                }

            }

            //  std::vector<matrix<float,0,1>>().swap(face_descriptors);
            //    face_descriptors.clear();
        }


    }




}

void Warker::doWark(cv::Mat m_pic, cv::Mat picture, int indx, bool sus_check, float FRThreshold)
{
    qDebug()<<"j Starting warker process in Thread "<<thread()->currentThreadId() <<" sus ck : "<<sus_check<<" FRThreshold : "<<FRThreshold;
    im_count++;
    // QImage image = picture.toImage();
    cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

    picture.copyTo(facadeColor);
    //   cv::Mat facadeGrey;
//     cv::cvtColor(facadeColor, facadeColor, cv::COLOR_BGR2GRAY);
    //   cv::Mat facadeRGB;
   // cv::cvtColor(facadeColor, facadeColor, cv::COLOR_BGR2RGB);




    std::string tempFace;
    QString faceID;


    array2d<rgb_pixel> img;
    dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));



    std::vector<matrix<rgb_pixel>> faces;

    rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    std::vector<rectangle> rects = face_detector(img);

    rects.push_back(rect);
    cout << "Rect Width : " << facadeColor.cols << endl;
    cout << "Rect Height: " << facadeColor.rows << endl;

    for (auto face : rects)
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces.push_back(move(face_chip));

    }


    //qDebug()<<"after clear rects sz ";

    //    //qDebug()<<"loop auto face "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

    //    milisecTimer.restart();
    //    nanosecTimer.restart();
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (faces.size() == 0)
    {

    }
    else
    {


        QString gender = /*//qDebug()<< "Male or female === " << */genderPredict(picture);

        //        if(!gender.isEmpty()){

        //            int age = agePredict(picture);

        std::vector<matrix<float,(long)0,(long)1>> face_descriptors = face_net(faces);

        qDebug()<< "face_descriptor size  : "<<face_descriptors.size();
        qDebug()<< "template_descriptors : "<<template_descriptors.size();

        for (size_t i = 0; i < face_descriptors.size(); ++i)
        {

            double mn=100.0; int mtch=-1;

            bool authorized_or_not = false;
            double confidence = 0.0;
            QPixmap pict;
            QPixmap m_pict = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));
            QString str_to_float;

            for (size_t j = 0; j < template_descriptors.size(); ++j)
            {

                mn = length(face_descriptors[i]-template_descriptors[j]);
                qDebug()<<"mn val: "<<mn;

                if (length(face_descriptors[i]-template_descriptors[j]) < FRThreshold /*0.45*/)  // The threshold of dace match
                {
                    qDebug()<<"FRTheshold >> if "<<FRThreshold;
                    confidence = mn*100;
                    confidence = 100-confidence;
                    tempFace = names[j+j];// + "@ Confidence =" + std::to_string(mn);
                    faceID = QString::fromStdString(tempFace);

                    pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                    str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                    confidence = str_to_float.toFloat();


                    emit valueFRChanged(m_pict, pict, faceID, indx, confidence, face_descriptors[i], /*recog val*/1);
//                    emit valueFRChanged( pict, faceID, indx, confidence);
                    authorized_or_not = true;
                    break;// since, expected value have got
                }

                confidence = 0.0;
            }
            if(authorized_or_not == false && sus_check == true)
            {
                qDebug()<<"FRTheshold >> else";
                tempFace = "SUSPECT ??";
                faceID = QString::fromStdString(tempFace);


                pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                confidence = mn*100;
                confidence = 100-confidence;
                str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                confidence = str_to_float.toFloat();

                emit valueFRChanged(m_pict, pict, faceID, indx, confidence, face_descriptors[i], /*recog val*/0);
//                emit valueFRChanged( pict, faceID, indx, confidence);
            }

        }
        //        }

    }

    FRmutex.lock();
    _warking = false;
    FRmutex.unlock();
    emit finishedFR();

}

void Warker::doWark(cv::Mat m_pic, cv::Mat picture, QString str, int indx, float FRThreshold, float fpsValue, bool sus_check, QString color, int per_list_check)
{
    qDebug()<<"Starting warker process in Thread "<<thread()->currentThreadId() << " sus check " << sus_check;

    bool face_in_per = checkFaceInPerson(m_pic);
    if(face_in_per == true && per_list_check == 1){
        im_count++;
        // QImage image = picture.toImage();
        cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

        picture.copyTo(facadeColor);
        //   cv::Mat facadeGrey;
        // cv::cvtColor(facadeColor, facadeColor, cv::COLOR_BGR2GRAY);




        std::string tempFace;
        QString faceID;

        array2d<rgb_pixel> img;
        dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));

        std::vector<matrix<rgb_pixel>> faces;

        rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

        std::vector<rectangle> rects = face_detector(img);

        rects.push_back(rect);
        cout << "Rect Width : " << facadeColor.cols << endl;
        cout << "Rect Height: " << facadeColor.rows << endl;

        for (auto face : rects)
        {
            auto shape = sp(img, face);
            matrix<rgb_pixel> face_chip;
            extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
            faces.push_back(move(face_chip));

        }


        //qDebug()<<"after clear rects sz ";

        //    //qDebug()<<"loop auto face "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

        //    milisecTimer.restart();
        //    nanosecTimer.restart();
        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        if (faces.size() == 0)
        {

        }
        else
        {
            QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));
            QPixmap se_pic = QPixmap::fromImage(QImage((unsigned char*) picture.data, picture.cols, picture.rows, QImage::Format_RGB888));

            //            emit valueFRChanged(ma_pic, se_pic, fpsValue);
        }
    }else if(per_list_check == 0){
        im_count++;
        // QImage image = picture.toImage();
        cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

        picture.copyTo(facadeColor);
        //   cv::Mat facadeGrey;
        // cv::cvtColor(facadeColor, facadeColor, cv::COLOR_BGR2GRAY);




        std::string tempFace;
        QString faceID;


        array2d<rgb_pixel> img;
        dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));



        std::vector<matrix<rgb_pixel>> faces;

        rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

        std::vector<rectangle> rects = face_detector(img);

        rects.push_back(rect);
        cout << "Rect Width : " << facadeColor.cols << endl;
        cout << "Rect Height: " << facadeColor.rows << endl;

        for (auto face : rects)
        {
            auto shape = sp(img, face);
            matrix<rgb_pixel> face_chip;
            extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
            faces.push_back(move(face_chip));

        }


        //qDebug()<<"after clear rects sz ";

        //    //qDebug()<<"loop auto face "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

        //    milisecTimer.restart();
        //    nanosecTimer.restart();
        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        if (faces.size() == 0)
        {

        }
        else
        {


            QString gender = /*//qDebug()<< "Male or female === " << */genderPredict(picture);

            if(!gender.isEmpty()){

                int age = agePredict(picture);

                std::vector<matrix<float,0,1>> face_descriptors = face_net(faces);

                for (size_t i = 0; i < face_descriptors.size(); ++i)
                {

                    double mn=100.0; int mtch=-1;

                    bool authorized_or_not = false;
                    double confidence = 0.0;
                    QPixmap pict;
                    QString str_to_float;

                    for (size_t j = 0; j < template_descriptors.size(); ++j)
                    {

                        mn = length(face_descriptors[i]-template_descriptors[j]);

                        if (length(face_descriptors[i]-template_descriptors[j]) < FRThreshold /*&& sus_check == false*/)  // The threshold of dace match
                        {
                            //qDebug()<<"FRTheshold >>"<<FRThreshold;
                            confidence = mn*100;
                            confidence = 100-confidence;
                            tempFace = names[j+j];// + "@ Confidence =" + std::to_string(mn);
                            faceID = QString::fromStdString(tempFace);

                            pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                            str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                            confidence = str_to_float.toFloat();

                            QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));;

                            faceID = str;
                            emit valueFRChanged(ma_pic, pict, faceID, indx, confidence, face_descriptors[i], fpsValue, 1, gender, age, color, per_list_check);

                            authorized_or_not = true;
                            break;// since, expected value have got
                        }

                        confidence = 0.0;
                    }
                    if(authorized_or_not == false && sus_check == true)
                    {
                        tempFace = "SUSPECT ??";
                        faceID = QString::fromStdString(tempFace);


                        pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                        confidence = mn*100;
                        confidence = 100-confidence;
                        str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                        confidence = str_to_float.toFloat();
                        QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));;
                        faceID = str;
                        emit valueFRChanged(ma_pic, pict, faceID, indx, confidence, face_descriptors[i], fpsValue, 0, gender, age, color, per_list_check);
                    }

                }
            }

        }
    }

    FRmutex.lock();
    _warking = false;
    FRmutex.unlock();
    emit finishedFR();


}
void Warker::doWark(cv::Mat m_pic, cv::Mat picture, QString str, int indx, float FRThreshold, float fpsValue, bool sus_check, QString color, int per_list_check, int s)
{
    qDebug()<<"Starting warker process based in Thread "<<thread()->currentThreadId() << " sus check " << sus_check;

    //    bool face_in_per = checkFaceInPerson(m_pic);
    /*if(face_in_per == true && per_list_check == 1){
        im_count++;
        // QImage image = picture.toImage();
        cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

        picture.copyTo(facadeColor);
        //   cv::Mat facadeGrey;
        // cv::cvtColor(facadeColor, facadeColor, cv::COLOR_BGR2GRAY);




        std::string tempFace;
        QString faceID;

        array2d<rgb_pixel> img;
        dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));

        std::vector<matrix<rgb_pixel>> faces;

        rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

        std::vector<rectangle> rects = face_detector(img);

        rects.push_back(rect);
        cout << "Rect Width : " << facadeColor.cols << endl;
        cout << "Rect Height: " << facadeColor.rows << endl;

        for (auto face : rects)
        {
            auto shape = sp(img, face);
            matrix<rgb_pixel> face_chip;
            extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
            faces.push_back(move(face_chip));

        }


        //qDebug()<<"after clear rects sz ";

        //    //qDebug()<<"loop auto face "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

        //    milisecTimer.restart();
        //    nanosecTimer.restart();
        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        if (faces.size() == 0)
        {

        }
        else
        {
            QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));
            QPixmap se_pic = QPixmap::fromImage(QImage((unsigned char*) picture.data, picture.cols, picture.rows, QImage::Format_RGB888));

            emit valueFRChanged(ma_pic, se_pic, fpsValue);
        }
    }else */
    //    if(per_list_check == 0){
    //        im_count++;
    //        // QImage image = picture.toImage();
    //        cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

    //        picture.copyTo(facadeColor);
    //        //   cv::Mat facadeGrey;
    //        // cv::cvtColor(facadeColor, facadeColor, cv::COLOR_BGR2GRAY);




    //        std::string tempFace;
    //        QString faceID;


    //        array2d<rgb_pixel> img;
    //        dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));



    //        std::vector<matrix<rgb_pixel>> faces;

    //        rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    //        std::vector<rectangle> rects = face_detector(img);

    //        rects.push_back(rect);
    //        cout << "Rect Width : " << facadeColor.cols << endl;
    //        cout << "Rect Height: " << facadeColor.rows << endl;

    //        for (auto face : rects)
    //        {
    //            auto shape = sp(img, face);
    //            matrix<rgb_pixel> face_chip;
    //            extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
    //            faces.push_back(move(face_chip));

    //        }


    //        //qDebug()<<"after clear rects sz ";

    //        //    //qDebug()<<"loop auto face "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

    //        //    milisecTimer.restart();
    //        //    nanosecTimer.restart();
    //        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //        if (faces.size() == 0)
    //        {

    //        }
    //        else
    //        {


    //            QString gender = /*//qDebug()<< "Male or female === " << */genderPredict(picture);

    //            if(!gender.isEmpty()){

    //                int age = agePredict(picture);

    //                std::vector<matrix<float,0,1>> face_descriptors = face_net(faces);

    //                for (size_t i = 0; i < face_descriptors.size(); ++i)
    //                {

    //                    double mn=100.0; int mtch=-1;

    //                    bool authorized_or_not = false;
    //                    double confidence = 0.0;
    //                    QPixmap pict;
    //                    QString str_to_float;

    //                    for (size_t j = 0; j < template_descriptors.size(); ++j)
    //                    {

    //                        mn = length(face_descriptors[i]-template_descriptors[j]);

    //                        if (length(face_descriptors[i]-template_descriptors[j]) < FRThreshold /*&& sus_check == false*/)  // The threshold of dace match
    //                        {
    //                            //qDebug()<<"FRTheshold >>"<<FRThreshold;
    //                            confidence = mn*100;
    //                            confidence = 100-confidence;
    //                            tempFace = names[j+j];// + "@ Confidence =" + std::to_string(mn);
    //                            faceID = QString::fromStdString(tempFace);

    //                            pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

    //                            str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
    //                            confidence = str_to_float.toFloat();

    //                            QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));;

    //                            faceID = str;
    //                            emit valueFRChanged(ma_pic, pict, faceID, indx, confidence, face_descriptors[i], fpsValue, 1, gender, age, color, per_list_check, s);

    //                            authorized_or_not = true;
    //                            break;// since, expected value have got
    //                        }

    //                        confidence = 0.0;
    //                    }
    //                    if(authorized_or_not == false && sus_check == true)
    //                    {
    //                        tempFace = "SUSPECT ??";
    //                        faceID = QString::fromStdString(tempFace);


    //                        pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

    //                        confidence = mn*100;
    //                        confidence = 100-confidence;
    //                        str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
    //                        confidence = str_to_float.toFloat();
    //                        QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));;
    //                        faceID = str;
    //                        emit valueFRChanged(ma_pic, pict, faceID, indx, confidence, face_descriptors[i], fpsValue, 0, gender, age, color, per_list_check, s);
    //                    }

    //                }
    //            }

    //        }
    //    }

    cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

    picture.copyTo(facadeColor);
    //   cv::Mat facadeGrey;
    // cv::cvtColor(facadeColor, facadeColor, cv::COLOR_BGR2GRAY);




    std::string tempFace;
    QString faceID;


    array2d<rgb_pixel> img;
    dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));



    std::vector<matrix<rgb_pixel>> faces;

    rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    std::vector<rectangle> rects = face_detector(img);

    rects.push_back(rect);
    cout << "Rect Width : " << facadeColor.cols << endl;
    cout << "Rect Height: " << facadeColor.rows << endl;

    for (auto face : rects)
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces.push_back(move(face_chip));

    }


    //qDebug()<<"after clear rects sz ";

    //    //qDebug()<<"loop auto face "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

    //    milisecTimer.restart();
    //    nanosecTimer.restart();
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (faces.size() == 0)
    {

    }
    else
    {


        QString gender = /*//qDebug()<< "Male or female === " << */genderPredict(picture);

        if(!gender.isEmpty()){

            int age = agePredict(picture);

            std::vector<matrix<float,0,1>> face_descriptors = face_net(faces);

            for (size_t i = 0; i < face_descriptors.size(); ++i)
            {

                double mn=100.0; int mtch=-1;

                bool authorized_or_not = false;
                double confidence = 0.0;
                QPixmap pict;
                QString str_to_float;

                for (size_t j = 0; j < template_descriptors.size(); ++j)
                {

                    mn = length(face_descriptors[i]-template_descriptors[j]);

                    if (length(face_descriptors[i]-template_descriptors[j]) < FRThreshold /*&& sus_check == false*/)  // The threshold of dace match
                    {
                        //qDebug()<<"FRTheshold >>"<<FRThreshold;
                        confidence = mn*100;
                        confidence = 100-confidence;
                        tempFace = names[j+j];// + "@ Confidence =" + std::to_string(mn);
                        faceID = QString::fromStdString(tempFace);

                        pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                        str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                        confidence = str_to_float.toFloat();

                        QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));;

                        faceID = str;
                        emit valueFRChanged(ma_pic, pict, faceID, indx, confidence, face_descriptors[i], fpsValue, 1, gender, age, color, per_list_check, s);

                        authorized_or_not = true;
                        break;// since, expected value have got
                    }

                    confidence = 0.0;
                }
                if(authorized_or_not == false && sus_check == true)
                {
                    tempFace = "SUSPECT ??";
                    faceID = QString::fromStdString(tempFace);


                    pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                    confidence = mn*100;
                    confidence = 100-confidence;
                    str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                    confidence = str_to_float.toFloat();
                    QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));;
                    faceID = str;
                    qDebug() << "Hello warker basedu islam";
                    emit valueFRChanged(ma_pic, pict, faceID, indx, confidence, face_descriptors[i], fpsValue, 0, gender, age, color, per_list_check, s);
                }

            }
        }

    }

    FRmutex.lock();
    _warking = false;
    FRmutex.unlock();
    emit finishedFR();

}

void Warker::doWark(cv::Mat m_pic, cv::Mat s_m_pic, cv::Mat picture, QString str, int indx, float FRThreshold, float fpsValue, bool sus_check, QString color, int per_list_check, int s)
{

    qDebug()<<"Starting warker process in Thread "<<thread()->currentThreadId()<< " Basedul islam "<< FRThreshold << " " << fpsValue;

    cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

    picture.copyTo(facadeColor);

    std::string tempFace;
    QString faceID;

    array2d<rgb_pixel> img;
    dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));

    std::vector<matrix<rgb_pixel>> faces;

    rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    std::vector<rectangle> rects = face_detector(img);

    rects.push_back(rect);
    cout << "Rect Width : " << facadeColor.cols << endl;
    cout << "Rect Height: " << facadeColor.rows << endl;

    for (auto face : rects)
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces.push_back(move(face_chip));

    }

    if (faces.size() == 0)
    {

    }
    else
    {

        QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));
        QPixmap se_pic = QPixmap::fromImage(QImage((unsigned char*) s_m_pic.data, s_m_pic.cols, s_m_pic.rows, QImage::Format_RGB888));
        QPixmap fa_pic = QPixmap::fromImage(QImage((unsigned char*) picture.data, picture.cols, picture.rows, QImage::Format_RGB888));

        //        qDebug() << "Dowarkkkkkkkkkkkkkkkkk " << str << " " << color;
        emit valueFRChanged(ma_pic, se_pic, fa_pic, fpsValue, indx, color, str, s);

    }


    FRmutex.lock();
    _warking = false;
    FRmutex.unlock();
    emit finishedFR();
}

void Warker::doWark(Buf_info::names_buf_info *infor)
{
    if(_warking == true && infor->face->clone().rows>0 && infor->face->clone().cols>0){
        qDebug()<<"Starting warker process in Thread "<<thread()->currentThreadId()<< " "<<infor->person_vec.size();

        cv::Mat facadeColor;
        infor->face->clone().copyTo(facadeColor);

        std::string tempFace;
        QString faceID;

        array2d<rgb_pixel> img;
        dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));

        std::vector<matrix<rgb_pixel>> faces;

        rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

        std::vector<rectangle> rects = face_detector(img);

        rects.push_back(rect);

        for (auto face : rects)
        {
            auto shape = sp(img, face);
            matrix<rgb_pixel> face_chip;
            extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
            faces.push_back(move(face_chip));

        }

        if (faces.size() == 0)
        {

        }
        else
        {
            //            qDebug() << "Ektukro hashite .................. " << infor->person->rows << " " << infor->person->cols;
            QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));
            //            QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) infor->person->clone().data, infor->person->clone().cols, infor->person->clone().rows, QImage::Format_RGB888));
            QPixmap se_pic = QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

            emit valueFRChanged(ma_pic, se_pic, ma_pic, 3.12, 0, "color", "str", 5);
        }


        //        for(int i = 0; i < infor->person_vec.size(); i++){
        //            infor->person_vec[i].first.deallocate();
        //            infor->person_vec[i].first.release();
        //        }
        //        infor->person.deallocate();
        //        infor->face.deallocate();
        //        infor->person.release();
        //        infor->face.release();
        //        infor->person_vec.clear();
        //        delete infor;
    }

    FRmutex.lock();
    _warking = false;
    FRmutex.unlock();
    emit finishedFR();
}

void Warker::doWark(cv::Mat person, cv::Mat face, Buf_info::names_buf_info* infor)
{
    qDebug()<<"Starting warker process in Thread "<<thread()->currentThreadId()<< " "<<infor->person_vec.size();

    cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

    face.copyTo(facadeColor);

    for(int i = 0; i < infor->person_vec.size(); i++){

        QPixmap person_pic = QPixmap::fromImage(QImage((unsigned char*) person.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));
        QPixmap sec_pic = QPixmap::fromImage(QImage((unsigned char*) infor->person_vec[i].first.data, infor->person_vec[i].first.cols, infor->person_vec[i].first.rows, QImage::Format_RGB888));
        QPixmap face_pic = QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

        emit valueFRChanged(face_pic, sec_pic, face_pic, infor->person_vec[i].second, infor->source_id, QString::fromStdString(infor->mask_status.c_str()), QString::fromStdString(infor->color.c_str()), 5);
        infor->person_vec[i].first.release();
        infor->person_vec[i].first.deallocate();
    }
    infor->person_vec.clear();


    std::string tempFace;
    QString faceID;


    array2d<rgb_pixel> img;
    dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));



    std::vector<matrix<rgb_pixel>> faces;

    rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    std::vector<rectangle> rects = face_detector(img);

    rects.push_back(rect);
    cout << "Rect Width : " << facadeColor.cols << endl;
    cout << "Rect Height: " << facadeColor.rows << endl;

    for (auto face : rects)
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces.push_back(move(face_chip));

    }
    if (faces.size() == 0)
    {

    }
    else
    {


        QString gender = /*//qDebug()<< "Male or female === " << */genderPredict(face);

        if(!gender.isEmpty()){

            int age = agePredict(face);

            std::vector<matrix<float,0,1>> face_descriptors = face_net(faces);

            for (size_t i = 0; i < face_descriptors.size(); ++i)
            {

                double mn=100.0; int mtch=-1;

                bool authorized_or_not = false;
                double confidence = 0.0;
                QPixmap pict;
                QString str_to_float;

                for (size_t j = 0; j < template_descriptors.size(); ++j)
                {

                    mn = length(face_descriptors[i]-template_descriptors[j]);

                    if (length(face_descriptors[i]-template_descriptors[j]) < 0.45 /*&& sus_check == false*/)  // The threshold of dace match
                    {
                        //qDebug()<<"FRTheshold >>"<<FRThreshold;
                        confidence = mn*100;
                        confidence = 100-confidence;
                        tempFace = names[j+j];// + "@ Confidence =" + std::to_string(mn);
                        faceID = QString::fromStdString(tempFace);

                        pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                        str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                        confidence = str_to_float.toFloat();

                        QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) person.data, person.cols, person.rows, QImage::Format_RGB888));;

                        faceID = QString::fromStdString(infor->mask_status.c_str());
                        emit valueFRChanged(ma_pic, pict, faceID, infor->source_id, confidence, face_descriptors[i], infor->fps, 1, gender, age, QString::fromStdString(infor->color.c_str()), 0, infor->person_vec.size());

                        authorized_or_not = true;
                        break;// since, expected value have got
                    }else/*(authorized_or_not == false && sus_check == true)*/
                    {
                        tempFace = "SUSPECT ??";
                        faceID = QString::fromStdString(tempFace);


                        pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                        confidence = mn*100;
                        confidence = 100-confidence;
                        str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                        confidence = str_to_float.toFloat();
                        QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) person.data, person.cols, person.rows, QImage::Format_RGB888));;
                        faceID = QString::fromStdString(infor->mask_status.c_str());
                        emit valueFRChanged(ma_pic, pict, faceID, infor->source_id, confidence, face_descriptors[i], infor->fps, 1, gender, age, QString::fromStdString(infor->color.c_str()), 0, infor->person_vec.size());
                    }
                }/*else(authorized_or_not == false && sus_check == true)*/
                //                {
                //                    tempFace = "SUSPECT ??";
                //                    faceID = QString::fromStdString(tempFace);


                //                    pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                //                    confidence = mn*100;
                //                    confidence = 100-confidence;
                //                    str_to_float = QString::number(confidence, 'f', 2);// take 2 digit after decimal point
                //                    confidence = str_to_float.toFloat();
                //                    QPixmap ma_pic = QPixmap::fromImage(QImage((unsigned char*) person.data, person.cols, person.rows, QImage::Format_RGB888));;
                //                    faceID = QString::fromStdString(infor->mask_status.c_str());
                //                    emit valueFRChanged(ma_pic, pict, faceID, infor->source_id, confidence, face_descriptors[i], infor->fps, 1, gender, age, QString::fromStdString(infor->color.c_str()), 0, infor->person_vec.size());
                //                }

            }
        }

    }




    //        for(int i = 0; i < infor->person_vec.size(); i++){
    //            infor->person_vec[i].first.deallocate();
    //            infor->person_vec[i].first.release();
    //        }
    //        infor->person.deallocate();
    //        infor->face.deallocate();
    //        infor->person.release();
    //        infor->face.release();
    //        infor->person_vec.clear();
    delete infor;
    FRmutex.lock();
    _warking = false;
    FRmutex.unlock();
    emit finishedFR();
}

void Warker::finishTh(){
    emit finishedFR();
}

void Warker::searchByImgToDir(QString img_path, QString img_dir)
{   //qDebug() << "searchByImgToDir";
    QStringList lis;
    std::vector<std::string> dir_img_names;
    std::vector<dlib::matrix<float,0l,1l>> dir_template_descriptors;

    const string dir_up = img_dir.toUtf8().constData();
    GetFilesInDirectory(dir_img_names, dir_up);

    std::vector<dlib::matrix<dlib::rgb_pixel>> templates_search;
    matrix<rgb_pixel> temp;
    for(int i=1; i<dir_img_names.size(); i+=2){
        try{
//            dlib::load_jpeg(temp, dir_img_names[i]);
//            dlib::load_png(temp, dir_img_names[i]);

            int pre_size = templates_search.size();
            for (auto face : face_detector(temp))
            {
                auto shape = sp(temp, face);
                matrix<rgb_pixel> face_chip;
                extract_image_chip(temp, get_face_chip_details(shape,150,0.25), face_chip);
                templates_search.push_back(move(face_chip));
            }
            if(pre_size == templates_search.size()){
                dir_img_names.erase(std::remove(dir_img_names.begin(), dir_img_names.end(), dir_img_names[i-1]), dir_img_names.end());
                dir_img_names.erase(std::remove(dir_img_names.begin(), dir_img_names.end(), dir_img_names[i]), dir_img_names.end());
            }

        }catch(...){

        }
    }
    dir_template_descriptors = face_net(templates_search);

    // load from directory done!

    // now working with single image
    //    QImage image_s;
    //    image_s.load(img_path);
    //cv::Mat mat_s(image.rows(),image.cols(),CV_8UC3,image.scanline());
    cv::Mat mats =cv::imread(img_path.toUtf8().constData());
    cv::Mat facadeColor;
    mats.copyTo(facadeColor);
    array2d<rgb_pixel> img;
    dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));
    std::vector<matrix<rgb_pixel>> faces;

    rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    std::vector<rectangle> rects = face_detector(img);
    rects.push_back(rect);
    for (auto face : rects)
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces.push_back(move(face_chip));
        // Also put some boxes on the faces so we can see that the detector is finding
        // them.
        //win.add_overlay(face);
    }
    if(faces.size() != 0){
        std::vector<matrix<float,0,1>> face_descriptors = face_net(faces);
        for (size_t i = 0; i < face_descriptors.size(); ++i){
            //            double mn=100.0; int mtch=-1;
            for (size_t j = 0; j < dir_template_descriptors.size(); ++j){
                //                mn = length(face_descriptors[i]-dir_template_descriptors[j]);
                if (length(face_descriptors[i]-dir_template_descriptors[j]) < 0.45){
                    std::string name = dir_img_names[j+j+1];
                    lis.append(QString::fromStdString(name));
                    //qDebug() << "std::string name "<< QString::fromStdString(name);
                }
            }
        }
    }
    //    if(lis.size() != 0){
    emit fromWarker(lis);
    //    }
}

void Warker::loadDetectedFace()
{
    std::ifstream TD_file("detected-face-serial.dat");
    std::ifstream name_file("detected-face-names-serial.dat");

    if(TD_file.good() && name_file.good()) {
        deserialize("detected-face-serial.dat") >> detected_temp_descriptors;
        deserialize("detected-face-names-serial.dat") >> detected_names;
    }

    //qDebug() << "Is lam " << detected_temp_descriptors.size() << " " << detected_names.size();
}

QString Warker::genderPredict(cv::Mat pic)
{
    try{
        //        frontal_face_detector detector = get_frontal_face_detector();
        //        shape_predictor sp_gender;
        //        deserialize("shape_predictor_5_face_landmarks.dat") >> sp_gender;

        //        static const char* model_net_filename = "dnn_gender_classifier_v1.dat";
        //        agender_type net_gender;
        //        deserialize(model_net_filename) >> net_gender;

        // Load the source image.
        matrix<rgb_pixel> in;
        //load_image(in, parser.option("test-image").argument(0));

        //load_image(in,"./image.jpg");
        dlib::assign_image(in, dlib::cv_image<rgb_pixel>(pic));


        // As proposed in the paper, use Softmax for the last layer.
        softmax<agender_type::subnet_type> snet;
        snet.subnet() = net_gender.subnet();

        // Evaluate the gender
        //        int32_t cur_face = 0;
        //        float confidence = 0.0f;
        //        enum label_ gender;

        for (auto face : face_detector(in))
        {
            auto shape = sp_gender(in, face);
            if (shape.num_parts())
            {
                bool male = false;
                matrix<rgb_pixel> face_chip;
                extract_image_chip(in, get_face_chip_details(shape, 32), face_chip);
                matrix<float, 1, 2> p = mat(snet(face_chip));
                if (p(0) < p(1))
                {
                    //                    gender = male_label;
                    //                    confidence = p(1);
                    male = true;
                }
                else
                {
                    //                    gender = female_label;
                    //                    confidence = p(0);
                    male = false;
                }
                return male==true ? "Male":"Female";
                //                cout << "face#" << cur_face++ << " - detected gender: " << ((gender == female_label) ? "female" : "male");
                //cout << std::fixed << std::setprecision(1) << " [" << (confidence * 100.0f) << "%]" << endl;
            }
        }
    }catch(std::exception& e)
    {
        cout << "Exception in gender prediction = " << e.what() << endl;
    }
    return "";

}

int Warker::agePredict(cv::Mat pic)
{
    try{
        //frontal_face_detector detector = get_frontal_face_detector();
        //shape_predictor sp_age;
        //        deserialize("shape_predictor_5_face_landmarks.dat") >> sp_age;

        //        static const char* model_net_filename = "dnn_age_predictor_v1.dat";
        //        apredictor_t net_age;
        //        deserialize(model_net_filename) >> net_age;

        // Load the source image.
        matrix<rgb_pixel> in;
        dlib::assign_image(in, dlib::cv_image<rgb_pixel>(pic));
        // load_image(in, "./image.jpg"/*parser.option("predict-age").argument(0)*/);

        // Usea Softmax for the last layer to estimate the age.
        softmax<apredictor_t::subnet_type> snet;
        snet.subnet() = net_age.subnet();

        // Age prediction using machine learning.
        int32_t cur_face = 0;
        for (auto face : face_detector(in))
        {
            auto shape = sp_age(in, face);
            if (shape.num_parts())
            {
                float confidence;
                matrix<rgb_pixel> face_chip;
                extract_image_chip(in, get_face_chip_details(shape, 64), face_chip);
                matrix<float, 1, number_of_age_classes> p = mat(snet(face_chip));
                return get_estimated_age(p, confidence);
                //                cout << "face#" << cur_face++ << " - age prediction: " << to_string(get_estimated_age(p, confidence)) << " years old";
                //                cout << std::fixed << std::setprecision(1) << " [" << (confidence * 100.0f) << "%]" << endl;
            }
        }
    }catch(std::exception& e){
        cout << e.what() <<" from age prediction exception "<< endl;
    }
    return -1;
}

void Warker::batchEnrollment(QString dir)
{
    //    FRmutex.lock();
    //    _warking = true;
    //    FRmutex.unlock();
    //qDebug() << "Templates size before = " << template_descriptors.size();
    qDebug() << "Warker::batchEnrollment(QString) " << dir;

    if(dir.isEmpty()){
        QMessageBox msg_box;
        msg_box.setText("batchEnrollment directory is empty!");
        msg_box.exec();

        qDebug()<<"dir is empty so return";
        return;
    }

    const string dir_up = dir.toUtf8().constData();
    int cou = 0;
    //    if(template_descriptors_batch.size() == 0){
    GetFilesInDirectory(names_batch,dir_up);

    for(int i=0; i<names_batch.size(); i++) {
        cout<<"face path start\n";
        cout<< names_batch[i]<<"   "<<i<<" "<<names_batch.size()<<endl;
        cout<<"face path end\n\n";
    }
    emit totSizeOfNames(names_batch.size()/2);
    matrix<rgb_pixel> temp;
    qDebug()<<"WTF??\n";
    std::vector<dlib::matrix<dlib::rgb_pixel>> templates_batch;

    for(int i=1; i<names_batch.size(); i+=2)
    {
        qDebug("loading  %s...\n",names_batch[i-1].c_str());
        try{
            dlib::load_jpeg(temp, names_batch[i]);
//            dlib::load_png(temp, names_batch[i]);
            qDebug()<<"after loading testok";

            //----

//            QPixmap pic;
//            pic.load(QString::fromUtf8(names_batch[i].c_str()));
//            QString face_path = "./faces/";
//            QDir myDir;
//            QString folder_name = "temp_late2";
//            QString image_path;
//            QString image_name;
//            if(!myDir.exists(folder_name)) //if no directory so create directory
//            {
//                myDir.mkpath(face_path+folder_name);
//                //            image_name = name+".png";
////                image_name = QString::fromUtf8(names_batch[i-1].c_str()) + ".jpg";
//                image_name = QString::fromUtf8(names_batch[i-1].c_str()) + ".png";
//                image_path = face_path+folder_name+"/"+image_name;
//            }else {
//                myDir.mkpath(face_path+folder_name);
//                //            image_name = name+".png";
////                image_name = QString::fromUtf8(names_batch[i-1].c_str()) + ".jpg";
//                image_name = QString::fromUtf8(names_batch[i-1].c_str()) + ".png";
//                image_path = face_path+folder_name+"/"+image_name;
//            }
//            QFile file(face_path+folder_name+"/"+image_name);
//            file.open(QIODevice::WriteOnly);
//            pic.save(&file, "PNG");
//            pic.save(&file, "JPG");

            //---

            unsigned long previous_size = templates_batch.size();

            for (auto face : face_detector(temp))
            {
                auto shape = sp(temp, face);
                matrix<rgb_pixel> face_chip;
                extract_image_chip(temp, get_face_chip_details(shape,150,0.25), face_chip);
                templates_batch.push_back(move(face_chip));
            }
            if(previous_size == templates_batch.size()){
                emit notLoadedBatch(names_batch[i-1].c_str());
                qDebug("%s  if Not loaded...\n",names_batch[i-1].c_str());
                names_batch.erase(std::remove(names_batch.begin(), names_batch.end(), names_batch[i-1]), names_batch.end());
                names_batch.erase(std::remove(names_batch.begin(), names_batch.end(), names_batch[i]), names_batch.end());
                ++cou;
            }else{
                emit addToDbBatch(names_batch[i-1].c_str(), names_batch[i].c_str());
                //                names.push_back(names_batch[i-1].c_str());
                //                names.push_back(names_batch[i].c_str());
                qDebug("%s  loaded...\n",names_batch[i-1].c_str());
            }
        }catch(...){
            emit notLoadedBatch(names_batch[i-1].c_str());
            qDebug("%s  catch Not loaded...\n",names_batch[i-1].c_str());
            names_batch.erase(std::remove(names_batch.begin(), names_batch.end(), names_batch[i-1]), names_batch.end());
            names_batch.erase(std::remove(names_batch.begin(), names_batch.end(), names_batch[i]), names_batch.end());
            ++cou;
        }

    }
    //std::vector<matrix<float,0,1>>
    //template_descriptors_batch = face_net(templates_batch);
    names.insert(end(names), begin(names_batch), end(names_batch));
    std::vector<dlib::matrix<float,0l,1l>> add_descriptor = face_net(templates_batch);
    template_descriptors.insert(end(template_descriptors), begin(add_descriptor), end(add_descriptor));

    //    }
    //cou = (names.size()/2)-cou;
    emit batchLoadingDone(names_batch.size()/2, cou);
    qDebug()<<"Loading Done from "+dir+"\n";
    serialize("face-serial.dat") << template_descriptors;
    serialize("face-names-serial.dat") << names;
    //qDebug() << "Templates size after = " << template_descriptors.size();

    names_batch.clear();
    templates_batch.clear();
    //    FRmutex.lock();
    //    _warking = false;
    //    FRmutex.unlock();
}


//void Warker::batchEnrollment(QString dir)
//{
//    //    FRmutex.lock();
//    //    _warking = true;
//    //    FRmutex.unlock();
//    qDebug() << "Templates size before = " << template_descriptors.size();
//    qDebug() << "Warker::batchEnrollment(QString) " << dir;
//    if(dir.isEmpty()){
//        QMessageBox msg_box;
//        msg_box.setText("batchEnrollment directory is empty!");
//        msg_box.exec();

//        qDebug()<<"dir is empty so return";
//        return;
//    }
//    else{
//        const string dir_up = dir.toUtf8().constData();
//        int cou = 0;
//        //    if(template_descriptors_batch.size() == 0){
//        GetFilesInDirectory(names_batch,dir_up);

//        for(int i=0; i<names_batch.size(); i++) {
//            cout<< names_batch[i]<<"   "<<i<<" "<<names_batch.size()<<endl;
//        }
//        emit totSizeOfNames(names_batch.size()/2);
//        matrix<rgb_pixel> temp;
//        qDebug()<<"WTF??\n";
//        std::vector<dlib::matrix<dlib::rgb_pixel>> templates_batch;

//        for(int i=1; i<names_batch.size(); i+=2)
//        {
//            qDebug("loading name is %s and path %s \n",names_batch[i-1].c_str(), names_batch[i].c_str());
//            try{
//                dlib::load_jpeg(temp, names_batch[i]);
//                qDebug()<<"j after load each image of batchenrollment";
//                //----

//                QPixmap pic;
//                pic.load(QString::fromUtf8(names_batch[i].c_str()));
//                QString face_path = "./faces/";
//                QDir myDir;
//                QString folder_name = "temp_late";
//                QString image_path;
//                QString image_name;
//                if(!myDir.exists(folder_name)) //if no directory so create directory
//                {
//                    myDir.mkpath(face_path+folder_name);
//                    //            image_name = name+".png";
//                    image_name = QString::fromUtf8(names_batch[i-1].c_str()) + ".jpg";
//                    image_path = face_path+folder_name+"/"+image_name;
//                }else {
//                    myDir.mkpath(face_path+folder_name);
//                    //            image_name = name+".png";
//                    image_name = QString::fromUtf8(names_batch[i-1].c_str()) + ".jpg";
//                    image_path = face_path+folder_name+"/"+image_name;
//                }
//                QFile file(face_path+folder_name+"/"+image_name);
//                file.open(QIODevice::WriteOnly);
//                //        pic.save(&file, "PNG");
//                pic.save(&file, "JPG");

//                //---
//                unsigned long previous_size = templates_batch.size();

//                for (auto face : face_detector(temp))
//                {
//                    auto shape = sp(temp, face);
//                    matrix<rgb_pixel> face_chip;
//                    extract_image_chip(temp, get_face_chip_details(shape,150,0.25), face_chip);
//                    templates_batch.push_back(move(face_chip));
//                }
//                if(previous_size == templates_batch.size()){
//                    emit notLoadedBatch(names_batch[i-1].c_str());
//                    qDebug("%s  Not loaded...\n",names_batch[i-1].c_str());
//                    names_batch.erase(std::remove(names_batch.begin(), names_batch.end(), names_batch[i-1]), names_batch.end());
//                    names_batch.erase(std::remove(names_batch.begin(), names_batch.end(), names_batch[i]), names_batch.end());
//                    ++cou;
//                }else{
//                    emit addToDbBatch(names_batch[i-1].c_str(), names_batch[i].c_str());
//                    //                names.push_back(names_batch[i-1].c_str());
//                    //                names.push_back(names_batch[i].c_str());
//                    qDebug("%s  loaded...\n",names_batch[i-1].c_str());
//                }
//            }catch(...){
//                emit notLoadedBatch(names_batch[i-1].c_str());
//                qDebug("%s  Not loaded...\n",names_batch[i-1].c_str());
//                names_batch.erase(std::remove(names_batch.begin(), names_batch.end(), names_batch[i-1]), names_batch.end());
//                names_batch.erase(std::remove(names_batch.begin(), names_batch.end(), names_batch[i]), names_batch.end());
//                ++cou;
//            }

//        }
//        //std::vector<matrix<float,0,1>>
//        //template_descriptors_batch = face_net(templates_batch);
//        names.insert(end(names), begin(names_batch), end(names_batch));
//        std::vector<dlib::matrix<float,0l,1l>> add_descriptor = face_net(templates_batch);
//        template_descriptors.insert(end(template_descriptors), begin(add_descriptor), end(add_descriptor));

//        //    }
//        //cou = (names.size()/2)-cou;
//        emit batchLoadingDone(names_batch.size()/2, cou);
//        qDebug()<<"Loading Done from "+dir+"\n";
//        serialize("face-serial.dat") << template_descriptors;
//        serialize("face-names-serial.dat") << names;
//        qDebug() << "Templates size after = " << template_descriptors.size();

//        names_batch.clear();
//        templates_batch.clear();
//        //    FRmutex.lock();
//        //    _warking = false;
//        //    FRmutex.unlock();
//    }
//}



void Warker::detectFaceFromImage(QString img_path)
{
    cv::Mat mats =cv::imread(img_path.toUtf8().constData());
    cv::Mat facadeColor;
    mats.copyTo(facadeColor);
    array2d<rgb_pixel> img;
    dlib::assign_image(img, dlib::cv_image<rgb_pixel>(facadeColor));
    std::vector<matrix<rgb_pixel>> faces;

    rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    std::vector<rectangle> rects = face_detector(img);
    rects.push_back(rect);
    for (auto face : rects)
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces.push_back(move(face_chip));
        // Also put some boxes on the faces so we can see that the detector is finding
        // them.
        //win.add_overlay(face);
    }

    if(faces.size() != 0){
        std::vector<matrix<float,0,1>> face_descriptors = face_net(faces);
        emit faceDesToMain(face_descriptors);
    }

}
