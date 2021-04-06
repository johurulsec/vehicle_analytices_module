#include "sync_checker.h"
#include <QDebug>
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
#include <QTextCodec>

using namespace rapidjson;

sync_checker::sync_checker(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
    std::string line;
    std::ifstream myfile ("./.cfg/server_url.txt");
    if (myfile.is_open())
    {
        while ( std::getline (myfile,line) )
        {
            serverUrl = line;

        }
        myfile.close();
    }

    else { //qDebug() << "Unable to open server Url file\n";
    }
//    serverUrl = "https://www.google.com";
}

void sync_checker::requestWorkSyChT()
{
    mutex.lock();
    _working = true;
    _abort = false;
    //qDebug()<<"Request sync checker start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequestedChT();
}

void sync_checker::abortSyChT()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        //qDebug()<<"Request sync checker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void sync_checker::doWarkSyncChe(int Id, QString name, QString image_path, QString timestamp, double con, int index, int , int rec_check)
{
    //qDebug()<<"Starting sync checker process in Thread "<<thread()->currentThreadId();

    mutex.lock();
    bool abort = _abort;
    mutex.unlock();

    Document d;
    Document::AllocatorType& alloc = d.GetAllocator();

    std::string toname= name.toUtf8().constData();
    // image to base64
    QImage img;
    QString base64data;
    bool valid = img.load(image_path);
    if(valid){
        //qDebug() << "Batrre";
        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);
        img.save(&buffer, "PNG");
        base64data = buffer.data().toBase64();
    }
    std::string base_std_64 = base64data.toUtf8().constData();
    std::string toTimestp = timestamp.toUtf8().constData();

    d.SetObject();
    {
        //        Value requests(kArrayType);

        //        {
        //            Value request(kObjectType);
        //            {
        d.AddMember("face_id", std::to_string(Id), alloc);
        d.AddMember("name", toname, alloc);
        d.AddMember("time_stamp", toTimestp, alloc);
        d.AddMember("camera_id", std::to_string(index), alloc);
        d.AddMember("rec_check", std::to_string(rec_check), alloc);
        d.AddMember("pic_base_64", base_std_64, alloc);
        //            }
        //            requests.PushBack(request, alloc);
        //        }
        //       d.AddMember("face", requests, alloc);
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    //    std::cout << "Basedul islam sync db" << std::endl;
    //    std::cout << buffer.GetString() << std::endl;

    //writeIntoJSONFile(buffer.GetString());

    //    char *url = "https://f4b09b01.ngrok.io/Tracker/GetAttendanceData";
    char *url = const_cast<char*>(serverUrl.c_str());

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
    //std::cout << buffl << std::endl;
    std::cout << "-------------------------------" << std::endl;
    request.setOpt(new curlpp::options::PostFields(buffl));
    request.setOpt(new curlpp::options::PostFieldSize(buffl.length()));

    std::ostringstream response;
    request.setOpt(new curlpp::options::WriteStream(&response));

    try{
        request.perform();
    }catch(...){
        std::cout << "No Internet" << std::endl;
    }

    // return std::string(response.str());

    //    std::cout << ">>>>>>>>>>>> Retrieved Response <<<<<<<<<<< " << std::endl;
    //    std::cout << response.str() <<  std::endl;
    //    std::cout << "Response length" << response.str().length() <<  std::endl;

    if(QString::compare(QString::fromStdString(response.str()), "OK") == 0){
        //qDebug()<< "Curl Okay";
        emit updateDb(Id);
    }

    mutex.lock();
    _working = false;
    mutex.unlock();

    //qDebug()<<"sync checker process finished in Thread "<<thread()->currentThreadId();
    emit finishedSyChT();

}

void sync_checker::doWarkSyncChe(int Id, QString person, QString face, QString timestamp, int source, QString mask_st
                                 , int status)
{
    qDebug()<<"Starting sync checker "<<face;

    mutex.lock();
    bool abort = _abort;
    mutex.unlock();

    Document d;
    Document::AllocatorType& alloc = d.GetAllocator();

    // image to base64
    QImage imgp;
    QString base64datap;
    bool validp = imgp.load(person);
    if(validp){
        //qDebug() << "Batrre";
        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);
        imgp.save(&buffer, "PNG");
        base64datap = buffer.data().toBase64();
    }
    std::string base_std_64p = base64datap.toUtf8().constData();

    QImage imgf;
    QString base64dataf;
    bool validf = imgf.load(face);
    if(validf){
        //qDebug() << "Batrre";
        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);
        imgf.save(&buffer, "PNG");
        base64dataf = buffer.data().toBase64();
    }
    std::string base_std_64f = base64dataf.toUtf8().constData();


    std::string toTimestp = timestamp.toUtf8().constData();
    std::string mask_status = mask_st.toUtf8().constData();
    std::string division = "Dhaka";
    std::string district = "Gazipur";
    d.SetArray();
    {
//        Value requests(kArrayType);
//        {
            Value request(kObjectType);
            {
                request.AddMember("person", base_std_64p, alloc);
                request.AddMember("face", base_std_64f, alloc);
                request.AddMember("camera_id", std::to_string(source), alloc);
                request.AddMember("mask_status", mask_status, alloc);
                request.AddMember("division", division, alloc);
                request.AddMember("district", district, alloc);
                request.AddMember("date_time", toTimestp, alloc);
            }
//            requests.PushBack(request, alloc);
//        }
//        d.AddMember("PersonFace", requests, alloc);
        d.PushBack(request, alloc);
    }
//    d.SetObject();
//    {
//        Value requests(kArrayType);
//        {
//            Value request(kObjectType);
//            {
//                request.AddMember("person", "base_std_64p", alloc);
//                request.AddMember("face", "base_std_64f", alloc);
//                request.AddMember("camera_id", std::to_string(source), alloc);
//                request.AddMember("mask_status", mask_status, alloc);
//                request.AddMember("division", division, alloc);
//                request.AddMember("district", district, alloc);
//                request.AddMember("time_stamp", toTimestp, alloc);
//            }
//            requests.PushBack(request, alloc);
//        }
//        d.AddMember("PersonFace", requests, alloc);
////        d.AddMember("person", base_std_64p, alloc);
////        d.AddMember("face", base_std_64f, alloc);
////        d.AddMember("camera_id", std::to_string(source), alloc);
////        d.AddMember("mask_status", mask_status, alloc);
////        d.AddMember("division", division, alloc);
////        d.AddMember("district", district, alloc);
////        d.AddMember("time_stamp", toTimestp, alloc);

//    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
        std::cout << "Basedul islam sync db" << std::endl;
        std::cout << buffer.GetString() << std::endl;

  //  writeIntoJSONFile(buffer.GetString());

    //    char *url = "https://f4b09b01.ngrok.io/Tracker/GetAttendanceData";
    char *url = const_cast<char*>(serverUrl.c_str());

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
    //std::cout << buffl << std::endl;
    std::cout << "hot url ------------------------------- "<< url << std::endl;
    request.setOpt(new curlpp::options::PostFields(buffl));
    request.setOpt(new curlpp::options::PostFieldSize(buffl.length()));

    std::ostringstream response;
    request.setOpt(new curlpp::options::WriteStream(&response));

    try{
        request.perform();
    }catch(...){
        std::cout << "No Internet" << std::endl;
    }

    // return std::string(response.str());

        std::cout << ">>>>>>>>>>>> Retrieved Response <<<<<<<<<<< " << std::endl;
        std::cout << response.str() <<  std::endl;
        std::cout << "Response length" << response.str().length() <<  std::endl;

    if(QString::compare(QString::fromStdString(response.str()), "OK") == 0){
        //qDebug()<< "Curl Okay";
        emit updateDb(Id);
    }

    mutex.lock();
    _working = false;
    mutex.unlock();

    //qDebug()<<"sync checker process finished in Thread "<<thread()->currentThreadId();
    emit finishedSyChT();

}
void sync_checker::writeIntoJSONFile(QString json)
{
    QFile json_file("./sigmind.json");
    json_file.open(QIODevice::Append | QIODevice::WriteOnly);
    if(json_file.isOpen()){
        QTextStream outStream(&json_file);
        outStream << json;
        outStream.flush();
        json_file.close();
    }
}
