#include "face.h"
#include "ui_face.h"
#include "warker.h"
#include <QTimer>
#include <QEventLoop>
#include <istream>
#include <QThread>
#include <QDebug>
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

#include <curl/curl.h>
#include "jsoncpp/include/json/json.h"
#include <sstream>
#include <cstdlib>
#include <cerrno>

#include "./curlpp/include/curlpp/cURLpp.hpp"
#include "./curlpp/include/curlpp/Easy.hpp"
#include "./curlpp/include/curlpp/Options.hpp"
#include "./curlpp/include/curlpp/Exception.hpp"

#define RAPIDJSON_HAS_STDSTRING 1
#include "./rapidjson/reader.h"
#include "./rapidjson/pointer.h"
#include "./rapidjson/document.h"     // rapidjson's DOM-style API
#include "./rapidjson/prettywriter.h" // for stringify JSON
#include "./rapidjson/stringbuffer.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonValueRef>

//#include "faceRecognition.h"
#include <dlib/opencv.h>
#include "mystyles.h"
#include <opencv2/imgproc/imgproc.hpp>

//#include <feed.h>
#include <exception>

using namespace dlib;
using namespace std;


void GetFilesInDirectory(std::vector<string> &out, const string &directory)
{
    qDebug()<<directory.c_str()<<endl;
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



//cv::Mat Warker::loadFromQrc(QString qrc, int flag = IMREAD_COLOR)
//{
//    QFile file(qrc);
//    Mat m;
//    if(file.open(QIODevice::ReadOnly))
//    {
//        qint64 sz = file.size();

//        std::vector<uchar> buf(sz);
//        file.read((char*)buf.data(), sz);
//        m = imdecode(buf, flag);
//    }
//    return m;
//}

//cv::Mat Warker::QImage2Mat( const QImage &inImage)
//{
//    bool inCloneImageData = true;
//    switch ( inImage.format() )
//    {
//    // 8-bit, 4 channel
//    case QImage::Format_RGB32:
//    {
//        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

//        return (inCloneImageData ? mat.clone() : mat);
//    }

//        // 8-bit, 3 channel
//    case QImage::Format_RGB888:
//    {
//        if ( !inCloneImageData )
//            qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";

//        QImage   swapped = inImage.rgbSwapped();

//        return cv::Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
//    }

//        // 8-bit, 1 channel
//    case QImage::Format_Indexed8:
//    {
//        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

//        return (inCloneImageData ? mat.clone() : mat);
//    }

//    default:
//        qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
//        break;
//    }

//    return cv::Mat();
//}
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
}

void Warker::requestWark()
{
    //    FRmutex.lock();
    //    _warking = true;
    //    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    //    FRmutex.unlock();

    emit warkRequested();
}


void Warker::load_template()
{
    face_detector = get_frontal_face_detector();
    deserialize("./.weight/LM-5p.dat") >> sp;
    deserialize("./.weight/FR-Resnetv2.dat") >> face_net;
    qDebug()<<"done\n";
    // if(names.size()==0)
    GetFilesInDirectory(names,"./faces/temp_late");

    for(int i=0; i<names.size(); i++){
        cout<< "names[] = "<<names[i]<<"   "<<i<<" "<<names.size()<<endl;
    }
    //qDebug()<<"names[0] ="<<names;
    cout<<"cout names[0] = "<<names[0];

    //std::vector<matrix<rgb_pixel>> templates;
    qDebug()<<"pre-WTF?\n";
    matrix<rgb_pixel> temp;
    qDebug()<<"WTF??\n";
    for(int i=1; i<names.size(); i+=2)
    {
        qDebug("loading  %s...\n",names[i-1].c_str());
        load_image(temp, names[i]);

        unsigned long previous_size = templates.size();

        for (auto face : face_detector(temp))
        {
            auto shape = sp(temp, face);
            matrix<rgb_pixel> face_chip;
            extract_image_chip(temp, get_face_chip_details(shape,150,0.25), face_chip);
            templates.push_back(move(face_chip));

            //            /* insert matrix of face into mysql database */
            //            if(connectionDB()){
            //                QSqlQuery query;
            //                QString create_matrix_table_for_face = "CREATE TABLE raw_matrix_face ( id INT AUTO_INCREMENT PRIMARY KEY, image BLOB NOT NULL);";
            //                if(query.exec(create_matrix_table_for_face)){
            //                    qDebug() << "Table created";
            //                }else{
            //                    qDebug() << "Table is not created";
            //                }
            //                query.prepare("insert into raw_matrix_face(image) values (?);");
            //                query.addBindValue(":image", face_chip);
            //                if(query.exec()){
            //                    qDebug() << "Image is stored";
            //                }else{
            //                    qDebug() << query.lastError();
            //                    qDebug() << "Image doesn't contained";
            //                }
            //            }

        }

        if(previous_size == templates.size()){

            QFile bf( names[i].c_str() ); // delete picture from folder
            bf.remove();

            //            qDebug() << "Names and path " << names[i-1].c_str() << " " << names[i].c_str() << endl;

            //QString name = QString::fromUtf8(names[i-1].c_str());
            //            QString name = QString::fromStdString(names[i-1].c_str());
            //QString name_path = QString::fromUtf8(names[i].c_str());
            //            QString name_path = QString::fromStdString(names[i].c_str());

            std::string name = names[i-1].c_str();
            std::string name_path =names[i].c_str();


            auto itr_name = std::find(names.begin(), names.end(),name);
            if(itr_name != names.end()){
                names.erase(itr_name);
            }

            auto itr_path = std::find(names.begin(), names.end(), name_path);
            if(itr_path != names.end()){
                names.erase(itr_path);
            }


            //            names.erase(std::remove(names.begin(), names.end(), name), names.end());
            //            names.erase(std::remove(names.begin(), names.end(), name_path), names.end());

            qDebug() << "ERROR !! Face read from temp_late" << endl;

        }else{
            template_descriptors = face_net(templates);
            qDebug("%s  loaded...\n",names[i-1].c_str());
        }

        //        template_descriptors = face_net(templates);

        //        qDebug() << "load template " << templates.size() << endl;

        //        if(templates.size() <= 10){

        //            QFile bf( names[i].c_str() ); // delete picture from folder
        //            bf.remove();

        //            names.erase(std::remove(names.begin(), names.end(), names[i-1]), names.end());
        //            names.erase(std::remove(names.begin(), names.end(), names[i]), names.end());

        //            qDebug() << "ERROR !! Face read from temp_late" << endl;
        //        }


        //        qDebug("%s  loaded...\n",names[i-1].c_str());
    }




    //std::vector<matrix<float,0,1>>
    //    template_descriptors = face_net(templates);
    //    //   setup(names,template_descriptors);
    //            for(int i=0; i<names.size(); i++)
    //            {
    //                names.push_back(names[i]);
    //            }

    //                for(int i=0; i<template_descriptors.size(); i++)
    //                {
    //                    template_descriptors.push_back(template_descriptors[i]);
    //                }

    qDebug()<<"Loading Done\n";

    qDebug() << " Loaded Template Size = " <<template_descriptors.size() << endl;

    //  return template_descriptors;
}



//QString Warker::recognize(cv::Mat &temp_img,std::vector<dlib::matrix<float,0l,1l>> &pic_templates)
//{
//QString faceString = recognition(temp_img, pic_templates, templates_names, face_detector, sp, face_net);

//return faceString;
//}

void Warker::deleteFromTemplate(QString image_path, QString image_name){
    qDebug() << ".......... deleteFromTemplate ..........." << endl;

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
    qDebug() << "Size before delete " << names.size() << " " << template_descriptors.size() << endl;
    names.erase(std::remove(names.begin(), names.end(), im_na), names.end());
    names.erase(std::remove(names.begin(), names.end(), im_path), names.end());

    qDebug() << "Size after delete " << names.size() << " " << template_descriptors.size() << endl;

    FRmutex.unlock();

    //    qDebug() << ".......... end deleteFromTemplate ..........." << endl;

}

bool Warker::loadImageIntoLoadTemplate(QString name_, QString newFace){ // load db image into runtime

    FRmutex.lock();

    std::string name = name_.toStdString();
    //    names.push_back(name); // name push into names
    //    names = {name};

    // new_templates  = templates;
    std::string face_path = newFace.toUtf8().constData();
    //    names.push_back(face_path);
    //    names = {name, face_path};

    matrix<rgb_pixel> temp;

    load_image(temp, face_path);
    qDebug() << " <<<<<<<<<<<<<< Inside >>>>>>>>>>>>> newFace that means imagepath "<<newFace;

    unsigned long previous_size = templates.size();

    for (auto face : face_detector(temp))
    {
        auto shape = sp(temp, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(temp, get_face_chip_details(shape,150,0.25), face_chip);
        templates.push_back(move(face_chip));
        qDebug() << "auto face : face_detector loop ok";
    }

    //    qDebug() << "Names size = " << names.size();
    //    qDebug() << "Template descrip = " << previous_size << " " << templates.size();

    if(previous_size == templates.size())
    {
        qDebug() << "ERROR !! Face not detected in image. Try another \n";
        //        FRmutex.lock();
        //        _warking = false;
        FRmutex.unlock();

        return false;

    }
    else
    {
        qDebug() << "Name and face push " << names.size()<< " "<< thread()->currentThreadId() << endl;

        names.push_back(name);
        names.push_back(face_path);
        template_descriptors = face_net(templates);

        qDebug() << "Names and templates size = A " << names.size() << " " << template_descriptors.size() << endl;

        FRmutex.unlock();

        return true;
    }

}

void Warker::abort()
{
    FRmutex.lock();
    if (_warking) {
        _abort = true;
        qDebug()<<"abort() of warker ThreadId "<<thread()->currentThreadId();
        //qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    FRmutex.unlock();
}




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
    for (int i = 0; i < 200; ++i)
    {
        cropper(img, raw_boxes, temp, ignored_crop_boxes);
        crops.push_back(move(temp));
    }
    return crops;
}


void Warker::doWark(cv::Mat picture, QString str, int indx)
{

    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();

    //   platePix = picture;
    //   plateIndx = indx;

    FRmutex.lock();
    bool abort = _abort;
   // _abort = false;
    // _warking = true;
    FRmutex.unlock();
    //        for (int i = 0; i < 5; i ++) {

    //    //        // Checks if the process should be aborted


    //            if (abort) {
    //                 qDebug()<<"Aborting worker process in Thread "<<thread()->currentThreadId();
    //                break;
    //            }
    //        }

    //qDebug()<<"+++++++++++++++++++++++++++++++++++++";

    //           QByteArray byteArray;
    im_count++;
    // QImage image = picture.toImage();
    cv::Mat facadeColor;// = cv::imread("/home/sigmind/mark.png");

    picture.copyTo(facadeColor);
    //   cv::Mat facadeGrey;
    cv::cvtColor(facadeColor, facadeColor, cv::COLOR_BGR2GRAY);




    std::string tempFace;
    QString faceID;
    // Grab and process frames until the main window is closed by the user.
    // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
    // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
    // long as temp is valid.  Also don't do anything to temp that would cause it
    // to reallocate the memory which stores the image as that will make cimg
    // contain dangling pointers.  This basically means you shouldn't modify temp
    // while using cimg.

    array2d<unsigned char> img;
    dlib::assign_image(img, dlib::cv_image<unsigned char>(facadeColor));

    //dlib::array2d<dlib::bgr_pixel> img;


    //dlib::assign_image(img, dlib::cv_image<dlib::bgr_pixel>(facadeColor));

    //dlib::matrix<dlib::rgb_pixel> img;

    // dlib::assign_image(img, dlib::cv_image<dlib::bgr_pixel>(facadeColor));

    //  cv_image<unsigned char> img(facadeColor);

    //qDebug()<<"dlib array2D size "<<img.size();

    // int Arows = sizeof(img)/sizeof(img[0]);
    // int Acols = sizeof(img[0])/sizeof(img[0][0]);
    //  cout<<Arows<<" rows and cols "<<Acols<<endl;
    //  matrix<rgb_pixel> img;


    // load_image(img, "/home/sigmind/mark.png");
    //    dlib::array2d<bgr_pixel> dlibFrame;
    //       dlib::assign_image(dlibFrame, dlib::cv_image<bgr_pixel>(temp));

    // assign_image(img, dlib::cv_image<bgr_pixel>(um_face));
    //  cv_image<bgr_pixel> img(facadeColor);

    //    QTime milisecTimer;
    //    milisecTimer.start();

    //    QElapsedTimer nanosecTimer;
    //    nanosecTimer.start();


    // pyramid_up(img);

    //    qDebug()<<"pyramid up "<<milisecTimer.elapsed()<<" milliSecond";
    //    qDebug()<<"pyramid up "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

    //  win.clear_overlay();
    //  win.set_image(img);



    //            Run the face detector on the image of our action heroes, and for each face extract a
    //            copy that has been normalized to 150x150 pixels in size and appropriately rotated
    //            and centered.

    //    milisecTimer.restart();
    //    nanosecTimer.restart();

    std::vector<matrix<rgb_pixel>> faces;

    rectangle rect(0, 0, facadeColor.rows, facadeColor.cols);

    std::vector<rectangle> rects;//= face_detector(img);

    rects.push_back(rect);
    cout << "Rect Width : " << facadeColor.cols << endl;
    cout << "Rect Height: " << facadeColor.rows << endl;

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

    //  faces.clear();

    rects.clear();
    img.clear();

    //    for(int i = 0; i < Arows; i++) {
    //       delete [] img[i]; }

    // img.reset();


    //qDebug()<<"before clear rects sz "<<rects.size();
    //   rects.clear();
      qDebug()<<"after clear rects sz ";

    //    qDebug()<<"loop auto face "<<nanosecTimer.nsecsElapsed()<<" nanoSecond";

    //    milisecTimer.restart();
    //    nanosecTimer.restart();
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (faces.size() == 0)
    {
        //  cout << "No faces found in image!" << endl;
        tempFace = "Not a face";
        faceID = QString::fromStdString(tempFace);

        //  faces.clear();
        // indx=0;
        //return 1;
    }
    else
    {
        // This call asks the DNN to convert each face image in faces into a 128D vector.
        // In this 128D vector space, images from the same person will be close to each other
        // but vectors from different people will be far apart.  So we can use these vectors to
        // identify if a pair of images are from the same person or from different people.


        std::vector<matrix<float,0,1>> face_descriptors = face_net(faces);


        qDebug() << "face descriptors Size in dowark" <<face_descriptors.size();


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
        int check_flag_value = 0;
        for (size_t i = 0; i < face_descriptors.size(); ++i)
        {

            double mn=100.0; int mtch=-1;

            qDebug() << "Template Descriptors Size in dowark" <<template_descriptors.size();
            qDebug() << "Names size in dowark" << names.size();

            for (size_t j = 0; j < template_descriptors.size(); ++j)
            {
                // Faces are connected in the graph if they are close enough.  Here we check if
                // the distance between two face descriptors is less than 0.6, which is the
                // decision threshold the network was trained to use.  Although you can
                // certainly use any other threshold you find useful.

                //                        if(mn> length(face_descriptors[i]-template_descriptors[j]) )
                //                        {
                mn = length(face_descriptors[i]-template_descriptors[j]);
                //                            mtch = j;
                //                        }
                //}

                //                qDebug() << "ELSE";
                time_t seconds;
                time(&seconds);
                std::stringstream ss;
                ss << seconds;
                std::string ts = ss.str();

                if (length(face_descriptors[i]-template_descriptors[j]) < 0.45)  // The threshold of dace match
                {
                    double confidence = mn*100;
                    tempFace = names[j+j];// + "@ Confidence =" + std::to_string(mn);
                    // win.add_overlay(dlib::image_window::overlay_rect(rects[i], rgb_pixel(0,255,0),temp));
                    //cout<< "face no: "<<i<<" similar to : " <<names[j+j]<<endl;
                    //int m=0;
                    std::string ms = std::to_string(mn) ;
                    // string path = "./detected/" + ms + names[j + j] + ts;
                    // save_jpeg(faces[i], path);
                    qDebug()<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"<<confidence;
                    faceID = QString::fromStdString(tempFace);
                    //                    indx = (int)confidence;
                    // qDebug() << "InIf";
                    //                    emit valueFRChanged(picture, faceID, indx);
//                    QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));
                    QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));

                    emit valueFRChanged(pict, faceID, indx, confidence, face_descriptors[i]);
                    // delete pict;
                    check_flag_value = 1;
                    break;// since, expected value have got
                }
                else
                {
                    tempFace = "SUSPECT ??";
                    faceID = QString::fromStdString(tempFace);
                    indx=0;

                    //QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) facadeColor.data, facadeColor.cols, facadeColor.rows, QImage::Format_RGB888));
                    //emit valueFRChanged(pict, faceID, indx, 0.50, face_descriptors[i]);

                    // emit valueFRChanged(picture, faceID, indx);
                }

                // emit valueFRChanged(picture, faceID, indx, conf);
            }
            //emit valueFRChanged(picture, faceID, indx, 0.50, face_descriptors[i]);

            if(check_flag_value == 1){
                qDebug()<<"break main loop ";
                break;
            }
        }

        face_descriptors.clear();

    }



    faces.clear();

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //    qDebug()<<"milliSecond ="<<milisecTimer.elapsed();
    //    qDebug()<<"nanoSecond ="<<nanosecTimer.nsecsElapsed();


    facadeColor.release();

    picture.release();

    FRmutex.lock();
    _warking = false;
    FRmutex.unlock();

    // qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    //Once 60 sec passed, the finished signal is sent
    emit finishedFR();


}
