#include "db_sync.h"
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

db_sync::db_sync(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
}
void db_sync::requestWorkSyTh()
{
    mutex.lock();
    _working = true;
    _abort = false;
    //qDebug()<<"Request sync start in Thread count "<<++count<<" "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequestedSyTh();
}

void db_sync::abortSyTh()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        //qDebug()<<"Request sync aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}
QString db_sync::encodeString(QString data){
    QByteArray string = data.toUtf8();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString encodedString = codec->toUnicode(string);
    int l = encodedString.length();

//    //qDebug()<<"l = "<<l<<" encodedString = "<<encodedString;

    //    int len = d.length();
    ////qDebug()<<"string = "<<d<<" length = "<<len;
    for(int i=0;i<l;i++){
        if(encodedString[i] == "\u09e6")
        {
            encodedString[i] = '0';/*
            //qDebug()<<encodedString[i]<<" "<<"0";*/
        }


        else if(encodedString[i] == "\u09e7")
        {
            encodedString[i] = '1';
        }
        ////qDebug()<<encodedString[i]<<" "<<"1";

        else if(encodedString[i] == "\u09e8")
        {
            encodedString[i] = '2';
        }
        // //qDebug()<<encodedString[i]<<" "<<"2";

        else if(encodedString[i] == "\u09e9")
        {
            encodedString[i] = '3';
        }
        ////qDebug()<<encodedString[i]<<" "<<"3";

        else if(encodedString[i] == "\u09ea")
        {
            encodedString[i] = '4';
        }
        ////qDebug()<<encodedString[i]<<" "<<"4";

        else if(encodedString[i] == "\u09eb")
        {
            encodedString[i] = '5';
        }
        // //qDebug()<<encodedString[i]<<" "<<"5";

        else if(encodedString[i] == "\u09ec")
        {
            encodedString[i] = '6';
        }
        ////qDebug()<<encodedString[i]<<" "<<"6";

        else if(encodedString[i] == "\u09ed")
        {
            encodedString[i] = '7';
        }
        ////qDebug()<<encodedString[i]<<" "<<"7";

        else if(encodedString[i] == "\u09ee")
        {
            encodedString[i] = '8';
        }
        ////qDebug()<<encodedString[i]<<" "<<"8";

        else if(encodedString[i] == "\u09ef")
        {
            encodedString[i] = '9';
        }

    }
    return encodedString;
}

void db_sync::writeIntoJSONFile(QString json)
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
void db_sync::doWarkSync(int Id, QPixmap pic, QString name, int index, double con, QString gender)
{
    //qDebug()<<"Starting sync process in Thread counter "<<++counter<<" "<<thread()->currentThreadId();

    //   platePix = picture;
    //   plateIndx = indx;

    mutex.lock();
    bool abort = _abort;
    mutex.unlock();

    QString face_path = "./captures/faces/";
    QString obliq = "/";
    // QString format = "dd.MM.yyyy";
    //QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //date_time = encodeString(date_time);
    QString at = "<at>";
    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    QString img_path = face_path+date+obliq;
    //        QString image_name = img_path+str+at+".png";
    QString image_name = img_path+name+at+QTime::currentTime().toString()+".png";


    Document d;
    Document::AllocatorType& alloc = d.GetAllocator();


    std::string timeStampStore;
    QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    date_time = encodeString(date_time);
    timeStampStore = date_time.toStdString();
    std::string toname= name.toUtf8().constData();

    d.SetObject();
    {
        Value requests(kArrayType);

        {
            Value request(kObjectType);
            {
                request.AddMember("track_id", std::to_string(Id), alloc);
                request.AddMember("name", toname, alloc);
                request.AddMember("time_stamp", timeStampStore, alloc);
                request.AddMember("Index", std::to_string(index), alloc);
            }
            requests.PushBack(request, alloc);
        }
        d.AddMember("face", requests, alloc);
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

//    std::cout << "Basedul islam sync db" << std::endl;
    std::cout << buffer.GetString() << std::endl;

    writeIntoJSONFile(buffer.GetString());


    //char *url = "https://vision.googleapis.com/v1/images:annotate?key=AIzaSyCQC7yOnqhdeQWYEmSq7eslVPWDC7qcprU";
    char *url = "https://www.sigmind.ai/watchcam/nexgen/index.php";
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
//    std::cout << "++++++++++Sent String for" << std::to_string(LPRnum) << std::endl;
//    std::cout << buffl << std::endl;
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

    std::cout << ">>>>>>>>>>>> Retrieved Response <<<<<<<<<<< " << std::endl;
   // std::cout << response.str() <<  std::endl;
  //  std::cout << "Response length " << response.str().length() <<  std::endl;


    if(QString::compare(QString::fromStdString(response.str()), "OK") == 0){
        //qDebug()<< "Curl Okay";
        emit insertToDb(Id, pic, name, index, con, date_time, 1, date, img_path, image_name, 0, gender);
        //emit finishedSyTh();
    }else{
        //qDebug() << "Curl Not Okay";
        emit insertToDb(Id, pic, name, index, con, date_time, 0, date, img_path, image_name, 0, gender);
        //emit finishedSyTh();
    }

    mutex.lock();
    _working = false;
    mutex.unlock();

    //qDebug()<<"sync process finished in Thread "<<thread()->currentThreadId();

    //Once 60 sec passed, the finished signal is sent
    emit finishedSyTh();
}
