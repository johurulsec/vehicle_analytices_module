#include "face.h"
#include "ui_face.h"
#include "worker.h"
#include <QTimer>
#include <QEventLoop>
#include <istream>
#include <QThread>
#include <QDebug>
#include <sstream>
#include <iostream>
//#include <cairo/cairo.h>
//#include <pangolin/pangolin.h>
//#include "base64new.hpp"
//#include <cairo.h>
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


#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>

#include "HelperClasses/perspectivetransformation.h"
#include "HelperClasses/WolfBinarization.h"

using namespace rapidjson;
using namespace std;
using namespace cv;

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
    OCRed = false;
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread +++++++++++++++++++++++++++++++++++++"<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
    qDebug()<<"requestWork end";
}

void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        //qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

QString Worker::tessApi(cv::Mat im)
{
    qDebug()<<"tessapi call";

    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();

    ocr->Init(NULL, "ben", tesseract::OEM_LSTM_ONLY);
    ocr->SetPageSegMode(tesseract::PSM_AUTO);
    ocr->SetImage(im.data, im.cols, im.rows, im.channels(), im.step);

    std::string outText = string(ocr->GetUTF8Text());
    //cout << "tessApi = "<<outText;

    ocr->End();
    delete ocr;
    return QString::fromStdString(outText);

}

//void Worker::extractPlate(QPixmap picture,QString str,int indx)
//{
//    std::cout << "---------- Plate EXTRACTED---------------------" << std::endl;
//   // return plate;
//    emit valueChanged(picture, str,indx);

//}

void Worker::syncRequestFinished(QNetworkReply *rep){
    //  mutex.lock();
    //    bool abort = _abort;
    //    mutex.unlock();


    //qDebug() << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    //  QString strReply = (QString)rep->readAll();
    //qDebug()<<" Reply Test: Success\n";
    //      if (rep->error()) {
    //            //qDebug() << rep->errorString();
    //            flagship = 0;
    //            return;
    //        }
    //  mutex.lock();
    //  bool abort = _abort;
    //  mutex.unlock();
    QString answer = rep->readAll();

    //qDebug() << answer;
    // const std::string& tmp = response.str();
    //   const char* json_response = tmp.c_str();
    // +++++++++++ Parsing the JSON response

    std::cout << "---------- Pointer tree---------------------" << std::endl;
    // cutoff = true;
    //std::cout << "Raw input:        " << input << std::endl;
    std::ostringstream response;
    std::string raw= answer.toUtf8().constData();
    response << raw;

    if (response.str().length() > 32)
    {
        Document inDoc;
        inDoc.Parse(response.str());

        // Print the document
        // {
        //     rapidjson::StringBuffer buffer;
        //     rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        //     inDoc.Accept(writer);
        //     std::cout << "Original:         " << buffer.GetString() << std::endl;
        // }

        // Make the copy
        Document outDoc;
        outDoc.CopyFrom(inDoc, outDoc.GetAllocator());

        // Modify the copy
        // SetValueByPointer(outDoc, "/array/0", "locale");

        // SetValueByPointer(outDoc, "/responses/0/textAnnotations/0/locale", "en");
        //   Pointer ptr("/responses/0/");
        //  Value* text = ptr.Get(outDoc);

        // if ((*text).GetString() == "textAnnotation")
        // {

        // SetValueByPointer(outDoc, "/responses/0/textAnnotations/0/locale", "en");
        Pointer ptr("/responses/0/textAnnotations/0/description");
        Value* stars = ptr.Get(outDoc);
        //  std::string plateID;
        //rapidjson::Value* plateID;
        // memcpy(stars, "magic" , 10);
        std::cout << "--------- Pointer Value-----------" << std::endl;

        std::string plateI = (*stars).GetString();
        //  std::cout << plateI  << std::endl;
        bool success = EraseValueByPointer(outDoc, "/responses/0/textAnnotations/0/description");
        assert(success);
        std::cout << "--------- Assert Success-----------" << std::endl;

        //  //  QString plateNum = "বাংলাকে ভালোবাসি";
        plateNum = QString::fromStdString(plateI);
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        //plateNum = plateID;
        // return plateNum;
    }
    else
    {
        QString notfound = "শনাক্ত করা যায়নি";
        plateNum = notfound;
        //return notfound;

    }


    //    delete rep;
    //        flagship = 1;

    //      QByteArray buffer = rep->readAll();
    //        //qDebug() << buffer;
    //        QJsonDocument jsonDoc(QJsonDocument::fromJson(responses));
    //        QJsonObject jsonReply = jsonDoc.object();

    //        QJsonObject response = jsonReply["response"].toObject();
    //        QJsonArray  data     = jsonReply["data"].toArray();
    //        //qDebug() << data;
    //       QJsonDocument jsdoc;
    //       jsdoc = QJsonDocument::fromJson(reply->readAll());
    //       QJsonObject jsobj = jsdoc.object();
    //       QJsonArray jsarr = jsobj[“feeds”].toArray();
    //       foreach (const QJsonValue &value, jsarr) {
    //       QJsonObject jsob = value.toObject();
    //       //qDebug() << jsob[“entry_id”].toInt();
    //       //qDebug() << jsob[“field1”].toString();
    //       //qDebug() << jsob[“field2”].toString();
    //       //qDebug() << jsob[“field3”].toString();
    //       //qDebug() << jsob[“created_at”].toString();
    //       }
    rep->deleteLater();
    //      emit valueChanged(platePix, plateNum, plateIndx);
    //emit valueChangedLPR(plateNum);

    //      mutex.lock();
    //       _working = false;
    //       mutex.unlock();

    //        //qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    //        //Once 60 sec passed, the finished signal is sent
    //   emit finishedLPR();




}

void Worker::LPRprint(QPixmap pic, QString str, int indx)
{
    // emit valueChanged(pic, plateNum, indx);
}


QString Worker::LPRcap(QString encod)
{
    //    qDebug()<<"google api call and encode str : "<<encod;

    //std::string platenum;
    //std::string plateID;

    // std::vector<uchar> array;
    // cv::imencode(".png",mat_img, array);


    // std::string encoded = Base64::encode(array);

    //std::thread apicall(googleAPI, encoded);


    //apicall.join();

    //return std::make_pair(plateID, LPRnum);
    std::string encoded = encod.toUtf8().constData();
    Document d;
    Document::AllocatorType& alloc = d.GetAllocator();

    // std::string mytext = "this is my text";

    d.SetObject();
    {

        Value requests(kArrayType);

        {
            Value request(kObjectType);
            {

                Value images(kObjectType);
                {

                    images.AddMember("content", encoded, alloc);
                    // images.PushBack(requests, alloc);
                }
                request.AddMember("image", images, alloc);
                {
                    Value features(kArrayType);

                    {
                        Value feature(kObjectType);
                        feature.AddMember("type", "TEXT_DETECTION", alloc);
                        // feature.AddMember("maxResults", 1, alloc);

                        features.PushBack(feature, alloc);
                    }

                    //   Value context(kObjectType);
                    //  {
                    //     Value lang(kArrayType);// = "bn";

                    //  context.AddMember("languageHints", lang, alloc);
                    // // images.PushBack(requests, alloc)
                    //  lang.PushBack(context, alloc);
                    //    }
                    // request.AddMember("imageContext", context, alloc);

                    request.AddMember("features", features, alloc);
                    {
                        Value context(kObjectType);
                        {
                            Value lang(kArrayType); // = "bn";
                            {
                                // Value bangla("bn"); //, alloc);
                                // std::string lang = "bn";
                                //  lang.PushBack(bangla, alloc));

                                //   Value bang(kObjectType);
                                //   {
                                //  Value bangla;
                                //   bangla.SetString("bn");
                                lang.PushBack("bn", alloc);
                            }


                            context.AddMember("languageHints", lang, alloc);

                            // images.PushBack(requests, alloc)
                            // lang.PushBack(context, alloc);
                        }
                        request.AddMember("imageContext", context, alloc);
                    }
                }

                requests.PushBack(request, alloc);
            }
            //  recipient.AddMember("maxResults", 1, alloc);
        }
        d.AddMember("requests", requests, alloc);
    }


    // {
    //   Value textPart;
    //   textPart.SetString(mytext.c_str(), alloc);
    //   d.AddMember("Text-part", textPart, alloc);
    // }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    //    qDebug()<<"after print d.accept";

    // std::cout << buffer.GetString() << std::endl;

    /// End of rapidJson

    // db sync json code
    /**

    Document d;
    Document::AllocatorType& alloc = d.GetAllocator();

    int faceIdStore = indx;
    std::string timeStampStore = timestampOfFaceId;

    d.SetObject();
    {
        Value requests(kArrayType);

        {
            Value request(kObjectType);
            {
                request.AddMember("face_id", "10", alloc);
                request.AddMember("time_stamp", "TimeStamp", alloc);
            }
             requests.PushBack(request, alloc);
        }
        d.AddMember("requests", requests, alloc);
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

     */


    //       std::stringstream jsonOUT;
    //     pt::write_json(jsonOUT, root);
    //     std::cout << jsonOUT.str() << std::endl;




    char *url = "https://vision.googleapis.com/v1/images:annotate?key=AIzaSyCtEhgAuqh7LSTR0z_K9h3rWQEUVK2zeoY";

    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    // curlpp::types::WriteFunctionFunctor functor(WriteMemoryCallback);
    // curlpp::options::WriteFunction *test = new curlpp::options::WriteFunction(functor);
    //  request.setOpt(test);

    request.setOpt(new curlpp::options::Url(url));
    request.setOpt(new curlpp::options::Verbose(true));

    std::list<std::string> header;
    header.push_back("Content-Type: application/json; charset=utf-8");
    //header.push_back("Content-Length", 1000000);
    request.setOpt(new curlpp::options::HttpHeader(header));

    //  char *buffl = jsonOUT.str();
    std::string buffl = buffer.GetString();
    //std::cout << "++++++++++Sent String for" << std::to_string(LPRnum) << std::endl;
    // std::cout << buffl << std::endl;
    std::cout << "-------------------------------" << std::endl;
    request.setOpt(new curlpp::options::PostFields(buffl));
    request.setOpt(new curlpp::options::PostFieldSize(buffl.length()));

    std::ostringstream response;
    request.setOpt(new curlpp::options::WriteStream(&response));

    try{
        request.perform();
        //        qDebug()<<"request perform successfully";

    }catch(...){
        ////qDebug() << "No Net Connection! " << response.str().length();
    }

    // return std::string(response.str());

    //    std::cout << ">>>>>>>>>>>> Retrieved Response <<<<<<<<<<< " << std::endl;
    //    std::cout << response.str() <<  std::endl;
    //    std::cout << "Response length is : " << response.str().length() <<  std::endl;

    if (response.str().length() > 33)
    {
        //        qDebug()<<"Response length is greater than 33";

        const std::string& tmp = response.str();
        const char* json_response = tmp.c_str();
        // +++++++++++ Parsing the JSON response

        //        std::cout << "---------- Pointer tree---------------------" << std::endl;
        //cutoff = true;
        //std::cout << "Raw input:        " << input << std::endl;

        Document inDoc;
        inDoc.Parse(response.str());

        // Print the document
        // {
        //     rapidjson::StringBuffer buffer;
        //     rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        //     inDoc.Accept(writer);
        //     std::cout << "Original:         " << buffer.GetString() << std::endl;
        // }

        // Make the copy
        Document outDoc;
        outDoc.CopyFrom(inDoc, outDoc.GetAllocator());

        // Modify the copy
        // SetValueByPointer(outDoc, "/array/0", "locale");

        // SetValueByPointer(outDoc, "/responses/0/textAnnotations/0/locale", "en");
        //   Pointer ptr("/responses/0/");
        //  Value* text = ptr.Get(outDoc);

        // if ((*text).GetString() == "textAnnotation")
        // {

        // SetValueByPointer(outDoc, "/responses/0/textAnnotations/0/locale", "en");
        Pointer ptr("/responses/0/textAnnotations/0/description");
        Value* stars = ptr.Get(outDoc);
        // std::string plateID;
        //rapidjson::Value* plateID;
        // memcpy(stars, "magic" , 10);
        std::cout << "--------- Pointer Value-----------" << std::endl;
        std::string plateID = (*stars).GetString();
        qDebug()<<"get plate id";
        //        std::cout <<"plateid is : "<<plateID  << std::endl;
        //        qDebug(qUtf8Printable(plateID));

        bool success = EraseValueByPointer(outDoc, "/responses/0/textAnnotations/0/description");
        qDebug()<<"before assert call and success value : "<<success;
        assert(success);
        std::cout << "--------- Assert Success-----------" << std::endl;


        //return plateID;
        //  QString plateNum = "বাংলাকে ভালোবাসি";
        QString plateNum = QString::fromStdString(plateID);
        qDebug()<<"plate number is : "<<plateNum;

        // std::this_thread::sleep_for (std::chrono::seconds(1));
        //plateNum = plateID;
        return plateNum;
    }
    else
    {
        qDebug()<<"sonakto kora jayni";

        QString notfound = "শনাক্ত করা যায়নি";
        //PlateNum = notfound;
        return notfound;
        //return platenum;
    }
    //return 0;
    // QString plateNum = "বাংলাকে ভালোবাসি";
    // return plateNum;
}

void Worker::doWork(cv::Mat obj, cv::Mat picture_, QString str, int indx, QString color, QString api_selection_value)
{



    qDebug()<<"Starting worker process in Thread ++++++++++++++++++++++++++++"<<thread()->currentThreadId();
    qDebug()<<"api valueee : "<<api_selection_value;

    //   platePix = picture;
    //   plateIndx = indx;

    mutex.lock();
    bool abort = _abort;
    mutex.unlock();
    //    for (int i = 0; i < 5; i ++) {

    //        // Checks if the process should be aborted


    //        if (abort) {
    //            //qDebug()<<"Aborting worker process in Thread "<<thread()->currentThreadId();
    //           // break;
    //        }


    //    /*/// training data creation

    if(picture_.empty() != true && obj.empty() != true){

//        QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) picture_.data, picture_.cols, picture_.rows, QImage::Format_Grayscale8));
        QPixmap ma_pict = QPixmap::fromImage(QImage((unsigned char*) obj.data, obj.cols, obj.rows, QImage::Format_RGB888));

        if(api_selection_value == "tess_api"){
            QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) picture_.data, picture_.cols, picture_.rows, QImage::Format_RGB888));

            imwrite(format("/home/sigmind/Pictures/Tests/%d_orig.png",imgCounter),picture_);

            cv::cvtColor(picture_, picture_, cv::COLOR_RGB2GRAY);
            cv::GaussianBlur( picture_, picture_, Size( 7, 7 ), 0 );

            WolfBinarization binarizer;
            binarizer.wolfBinarize(picture_,picture_);
//            imwrite(format("/home/sigmind/Pictures/Tests/%d_bin.png",imgCounter),picture_);

//             PerspectiveTransformation transformer;
//             picture_ = transformer.transform(picture_);
//             imwrite(format("/home/sigmind/Pictures/Tests/%d_m_pic.png",imgCounter),obj);

            QString full_img_lpr = tessApi(picture_);
            qDebug() <<"tess api full_img_lpr : "<<full_img_lpr;
//            pict =  QPixmap::fromImage(QImage((unsigned char*) picture_.data, picture_.cols, picture_.rows, QImage::Format_RGB888));
            QPixmap test =  QPixmap::fromImage(QImage((unsigned char*) picture_.data, picture_.cols, picture_.rows, QImage::Format_Grayscale8));

            emit valueChanged(ma_pict, test, full_img_lpr, indx, color);
        }
        else if(api_selection_value == "google_api"){
            /// convert gray scale
            cv::cvtColor(picture_, picture_, cv::COLOR_RGB2GRAY);
            QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) picture_.data, picture_.cols, picture_.rows, QImage::Format_Grayscale8));

            QPixmap full_part = pict.copy(0, 0, pict.width(), pict.height());
            QImage full_img = full_part.toImage();
            QBuffer buffer_full;
            buffer_full.open(QIODevice::WriteOnly);
            full_img.save(&buffer_full, "PNG");
            QString base64data_full_img = buffer_full.data().toBase64();
            QString full_img_lpr = LPRcap(base64data_full_img);//"| uাকা আদাজ\n২°৩২৪৪\n" or "১৩-৩৮৬১\n"

            qDebug() <<"google api full_img_lpr : "<<full_img_lpr;
            ///convert gray to rgb
            cv::cvtColor(picture_, picture_, cv::COLOR_GRAY2RGB);
            pict =  QPixmap::fromImage(QImage((unsigned char*) picture_.data, picture_.cols, picture_.rows, QImage::Format_RGB888));

            emit valueChanged(ma_pict, pict, full_img_lpr, indx, color);
        }

    }


    /// for full image in google api
    /*
    QPixmap full_part = picture.copy(0, 0, picture.width(), picture.height());
    QImage full_img = full_part.toImage();
    QBuffer buffer_full;
    buffer_full.open(QIODevice::WriteOnly);
    full_img.save(&buffer_full, "PNG");
    QString base64data_full_img = buffer_full.data().toBase64();
    QString full_img_lpr = LPRcap(base64data_full_img);//"| uাকা আদাজ\n২°৩২৪৪\n" or "১৩-৩৮৬১\n"
//        QString full_img_lpr = tessApi(picture_);//"খা\nজা\n"
    qDebug() <<"full_img_lpr : "<<full_img_lpr;
    emit valueChanged(full_part, full_img_lpr, full_part, full_img_lpr);
*/

    /// for first_half and second_half in google api
    /*
    QPixmap first_half = picture.copy(0, 0, picture.width(), picture.height()/2);
    QImage first_img = first_half.toImage();
    QBuffer buffer_first;
    buffer_first.open(QIODevice::WriteOnly);
    first_img.save(&buffer_first, "PNG");
    QString base64data_first_img = buffer_first.data().toBase64();
    QString first_img_lpr = LPRcap(base64data_first_img);
    //    QString first_img_lpr = tessApi(cropped);
    qDebug() <<"first_img_lpr : "<<first_img_lpr;


    QPixmap second_half = picture.copy(0, picture.height()/2, picture.width(), picture.height()/2);
    QImage second_img = second_half.toImage();
    QBuffer buffer_second;
    buffer_second.open(QIODevice::WriteOnly);
    second_img.save(&buffer_second, "PNG");
    QString base64data_second_img = buffer_second.data().toBase64();
    QString second_img_lpr = LPRcap(base64data_second_img);
    //    second_img_lpr = tessApi(cropped_);
    qDebug() <<"second_img_lpr : " << second_img_lpr<<"\n";

//    if(strcmp(first_img_lpr, "শনাক্ত করা যায়নি") != 0 && strcmp(second_img_lpr, "শনাক্ত করা যায়নি") != 0){
    if(first_img_lpr != "শনাক্ত করা যায়নি" && second_img_lpr != "শনাক্ত করা যায়নি"){
        qDebug() <<"valid first_img_lpr : "<<first_img_lpr<<" second_img_lpr : " << second_img_lpr;
        emit valueChanged(first_half, first_img_lpr, second_half, second_img_lpr);
    }
*/


    /// for tessApi

    /// for first_half and second_half in tess api
    /*
    cv::Rect crop_rect;
    cv::Mat cropped_first_half_cvmat;
    QString first_img_lpr;
    QPixmap cropped_first_half;

    if(picture_.rows>0 && picture_.cols>0){

        crop_rect = cv::Rect (0, 0, picture_.cols, picture_.rows/2);
        cropped_first_half_cvmat = picture_(crop_rect);
        cropped_first_half =  QPixmap::fromImage(QImage((unsigned char*) cropped_first_half_cvmat.data, cropped_first_half_cvmat.cols, cropped_first_half_cvmat.rows, QImage::Format_RGB888));

        qDebug()<<"crop first img sz : " <<cropped_first_half_cvmat.size().width<< " " <<cropped_first_half_cvmat.size().height;
        cv::imwrite("/home/sigmind/.HTPA-KK-1/captures/license_plates/tessApiData/cropImgAlphabet.jpeg" , cropped_first_half_cvmat);

        first_img_lpr = tessApi(cropped_first_half_cvmat);
        qDebug() <<"first_img_lpr : "<<first_img_lpr;
    }

    QString second_img_lpr;
    cv::Mat cropped_second_half_cvmat;
    cv::Rect crop_rect_;
    QPixmap cropped_second_half;

    if(picture_.rows>0 && picture_.cols>0){

        crop_rect_ = cv::Rect (0, picture_.rows/2, picture_.cols, picture_.rows/2);
        cropped_second_half_cvmat = picture_(crop_rect_);
        cropped_second_half =  QPixmap::fromImage(QImage((unsigned char*) cropped_second_half_cvmat.data, cropped_second_half_cvmat.cols, cropped_second_half_cvmat.rows, QImage::Format_RGB888));

        qDebug()<<"crop digit img sz : " <<cropped_second_half_cvmat.size().width<< " " <<cropped_second_half_cvmat.size().height;
        cv::imwrite("/home/sigmind/.HTPA-KK-1/captures/license_plates/tessApiData/cropImgDigit.jpeg" , cropped_second_half_cvmat);

        second_img_lpr = tessApi(cropped_second_half_cvmat);
        qDebug() <<"second_img_lpr : " << second_img_lpr<<"\n";

    }
    emit valueChanged(cropped_first_half, first_img_lpr, cropped_second_half, second_img_lpr);
*/

    //    /// end of training data creation*/


    //    QImage plateImg = picture.toImage();
    //    //QImage split_img = picture.toImage();
    //    //cv::Mat split_img_mat(split_img.rows(),split_img.cols(),CV_8UC3,split_img.scanline());

    //    //           QByteArray byteArray;

    //    //           QBuffer buff(&byteArray);

    //    //               plateImg.save(&buff, "PNG"); // writes the image in JPEG format inside the buffer

    //    //               QString base64Image = QString::fromLatin1(byteArray.toBase64().data());
    //    // QByteArray byteArray;
    //    QBuffer buffer;
    //    buffer.open(QIODevice::WriteOnly);
    //    plateImg.save(&buffer, "PNG");
    //    // auto const encoded = buffer.data().toBase64();
    //    QString base64data = buffer.data().toBase64();

    //    //       //  This will stupidly wait 1 sec doing nothing...
    //    //        QEventLoop loop;
    //    //        QTimer::singleShot(1000, &loop, SLOT(quit()));
    //    //        loop.exec();
    //    std::stringstream plateStream;
    //    QString plate = LPRcap(base64data);  // for vision api
    //    //qDebug() << "Number plate b = " << plate;
    //    qDebug(qUtf8Printable(plate));



    //    int enc = 5;

    //    //    QJsonObject emage;
    //    //    QJsonArray requests;
    //    //    QJsonObject reQuest;

    //    //    //request.push_back(QJsonValue(emages));

    //    //    //        auto emage = QJsonObject(
    //    //    //         {
    //    //    //             //qMakePair(QString("content"), base64Image)
    //    //    //                   qMakePair(QString("content"), QString("FUCK SUSU"))
    //    //    //          });

    //    //    emage.insert(QString("content"), base64data);

    //    //    reQuest.insert(QString("image"), QJsonValue(emage));

    //    //    // requests.push_back(QJsonValue(reQuest));

    //    //    QJsonArray features;
    //    //    //           auto feature = QJsonObject(
    //    //    //                {
    //    //    //                           qMakePair(QString("type"), QString("TEXT_DETECTION"))

    //    //    //                       });


    //    //    QJsonObject feature;
    //    //    feature.insert(QString("type"), QString("TEXT_DETECTION"));
    //    //    features.push_back(QJsonValue(feature));
    //    //    reQuest.insert(QString("features"), QJsonValue(features));



    //    //    QJsonObject context;
    //    //    QJsonArray lang;
    //    //    lang.push_back("bn");
    //    //    context.insert("languageHints", lang);
    //    //    reQuest.insert(QString("imageContext"), QJsonValue(context));


    //    //    requests.push_back(reQuest);

    //    //    QJsonObject finalJson;
    //    //    finalJson.insert(QString("requests"), QJsonValue(requests));
    //    //    QJsonDocument doc(finalJson);
    //    //    QString strJson(doc.toJson(QJsonDocument::Compact));
    //    //    QByteArray json_bytes = strJson.toLocal8Bit();
    //    //    //  //qDebug() << "Json Data=" << strJson;

    //    //    //qDebug()<<"SSL version use for build: "<<QSslSocket::sslLibraryBuildVersionString();
    //    //    //qDebug()<<"SSL version use for run-time: "<<QSslSocket::sslLibraryVersionNumber();
    //    //    ////qDebug()<<QCoreApplication::libraryPaths();
    //    //    // -------------  Network manager ---------
    //    //    QUrl url("https://vision.googleapis.com/v1/images:annotate?key=AIzaSyCQC7yOnqhdeQWYEmSq7eslVPWDC7qcprU");


    //    //    QNetworkAccessManager *APImanager = new QNetworkAccessManager(this);
    //    //    QNetworkRequest Request(url);

    //    //    Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //    //    Request.setRawHeader("charset", "utf-8");
    //    //    //                    connect(APImanager, SIGNAL(finishedLPR(QNetworkReply*, QPixmap, QString, int)),this,
    //    //    //                        SLOT(syncRequestFinished(QNetworkReply*, QPixmap, QString, int)));
    //    //    connect(APImanager, SIGNAL(finished(QNetworkReply*)),this,
    //    //            SLOT(syncRequestFinished(QNetworkReply*)));






    //    // APImanager->post(Request,strJson);

    //    //   APImanager->post(Request,json_bytes);  // this

    //    //       APImanager->post(request,strJson);
    //   // //qDebug() << "----------------------------------------------------------------------------- "<<plate;

    //    //   mutex.lock();
    //    //    _working = false;
    //    //    mutex.unlock();
    //    //QString plateID = QString::fromStdString(plateStream.str());;
    //    // Once we're done waiting, value is updated
    //    // QString pla = extractPlate()
    //    //  emit plateData();
    //    //  QThread::msleep(200);
    //    //   if(OCRed)
    //    //   {

    //    // QString plateVal = plate


    //      }
    // QThread::msleep(500);
    // }


    mutex.lock();
    _working = false;
    mutex.unlock();

    //qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    //Once 60 sec passed, the finished signal is sent
    emit finishedLPR();

    imgCounter++;


}

//void Worker::doWork(QPixmap picture, QString str, int indx)
//{
//    //qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();

//    //   platePix = picture;
//    //   plateIndx = indx;

//    mutex.lock();
//    bool abort = _abort;
//    mutex.unlock();
//    //    for (int i = 0; i < 5; i ++) {

//    //        // Checks if the process should be aborted


//    //        if (abort) {
//    //            //qDebug()<<"Aborting worker process in Thread "<<thread()->currentThreadId();
//    //           // break;
//    //        }

//    // To base64

//    //  QPixmap
//    QImage plateImg = picture.toImage();

//    QBuffer buffer;
//    buffer.open(QIODevice::WriteOnly);
//    plateImg.save(&buffer, "PNG");
//    // auto const encoded = buffer.data().toBase64();
//    QString base64data = buffer.data().toBase64();

//    //       //  This will stupidly wait 1 sec doing nothing...
//    //        QEventLoop loop;
//    //        QTimer::singleShot(1000, &loop, SLOT(quit()));
//    //        loop.exec();
//    //        std::stringstream plateStream;
//    //    QString plate = LPRcap(base64data);  // for vision api
//    // qDebug(qUtf8Printable(plate));



//    int enc = 5;

//    QJsonObject emage;
//    QJsonArray requests;
//    QJsonObject reQuest;

//    //request.push_back(QJsonValue(emages));

//    //        auto emage = QJsonObject(
//    //         {
//    //             //qMakePair(QString("content"), base64Image)
//    //                   qMakePair(QString("content"), QString("FUCK SUSU"))
//    //          });

//    emage.insert(QString("content"), base64data);

//    reQuest.insert(QString("image"), QJsonValue(emage));

//    // requests.push_back(QJsonValue(reQuest));

//    QJsonArray features;
//    //           auto feature = QJsonObject(
//    //                {
//    //                           qMakePair(QString("type"), QString("TEXT_DETECTION"))

//    //                       });


//    QJsonObject feature;
//    feature.insert(QString("type"), QString("TEXT_DETECTION"));
//    features.push_back(QJsonValue(feature));
//    reQuest.insert(QString("features"), QJsonValue(features));



//    QJsonObject context;
//    QJsonArray lang;
//    lang.push_back("bn");
//    context.insert("languageHints", lang);
//    reQuest.insert(QString("imageContext"), QJsonValue(context));


//    requests.push_back(reQuest);

//    QJsonObject finalJson;
//    finalJson.insert(QString("requests"), QJsonValue(requests));
//    QJsonDocument doc(finalJson);
//    QString strJson(doc.toJson(QJsonDocument::Compact));
//    QByteArray json_bytes = strJson.toLocal8Bit();
//    //  //qDebug() << "Json Data=" << strJson;

//    //qDebug()<<"SSL version use for build: "<<QSslSocket::sslLibraryBuildVersionString();
//    //qDebug()<<"SSL version use for run-time: "<<QSslSocket::sslLibraryVersionNumber();
//    ////qDebug()<<QCoreApplication::libraryPaths();
//    // -------------  Network manager ---------
//    //     QUrl url("https://vision.googleapis.com/v1/images:annotate?key=AIzaSyCQC7yOnqhdeQWYEmSq7eslVPWDC7qcprU");


//    //                QNetworkAccessManager *APImanager = new QNetworkAccessManager(this);
//    //                    QNetworkRequest Request(url);

//    //                    Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    //                      Request.setRawHeader("charset", "utf-8");
//    ////                    connect(APImanager, SIGNAL(finishedLPR(QNetworkReply*, QPixmap, QString, int)),this,
//    ////                        SLOT(syncRequestFinished(QNetworkReply*, QPixmap, QString, int)));
//    //                      connect(APImanager, SIGNAL(finished(QNetworkReply*)),this,
//    //                                            SLOT(syncRequestFinished(QNetworkReply*)));






//    // APImanager->post(Request,strJson);

//    //APImanager->post(Request,json_bytes);  // this

//    //       APImanager->post(request,strJson);
//    //qDebug() << "-----------------------------------------------------------------------------";

//    //   mutex.lock();
//    //    _working = false;
//    //    mutex.unlock();
//    QString plateID = "License Plate";// QString::fromStdString(plateStream.str());;
//    // Once we're done waiting, value is updated
//    // QString pla = extractPlate()
//    //  emit plateData();
//    //  QThread::msleep(200);
//    //   if(OCRed)
//    //   {

//    // QString plateVal = plate


//    emit valueChanged(picture, plateID,indx);
//    // }
//    // QThread::msleep(500);
//    // }

//    // Set _working to false, meaning the process can't be aborted anymore.
//    mutex.lock();
//    _working = false;
//    mutex.unlock();

//    //qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

//    //Once 60 sec passed, the finished signal is sent
//    emit finishedLPR();


//}
