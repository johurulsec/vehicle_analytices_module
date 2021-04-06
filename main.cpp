#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QMetaType>
#include <vector>
#include <string>
#include "rectangle.h"
#include <dialogs/settingsdialog.h>
#include <QDebug>

#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>

#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>

//#include <VLCQtCore/Common.h>
#include "QtNetwork/QNetworkInterface"
#include "QString"



typedef std::vector<std::pair<watchcam::rectangle,std::string> > myType;
typedef std::vector< watchcam::rectangle > myType2;
typedef std::vector<dlib::matrix<float,(long)0,(long)1>> myType3;
typedef dlib::matrix<float,(long)0,(long)1> myType4;

Q_DECLARE_METATYPE (cv::Mat)
Q_DECLARE_METATYPE (myType)
Q_DECLARE_METATYPE (myType2)
//Q_DECLARE_METATYPE (myType3)
//Q_DECLARE_METATYPE (myType4)




QString getMacAddress()
{
    QString text;
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        text += "Interface:"+interface.hardwareAddress()+"\n";
    }
    return text;
}

int main(int argc, char *argv[])
{

    qRegisterMetaType< cv::Mat >("cv::Mat");
    qRegisterMetaType< myType >("std::vector<std::pair<watchcam::rectangle,std::string> >");
    qRegisterMetaType< myType2 >("std::vector< watchcam::rectangle >");
    qRegisterMetaType< myType3 >("std::vector<dlib::matrix<float,(long)0,(long)1>>");
    qRegisterMetaType< myType4 >("dlib::matrix<float,(long)0,(long)1>");

    QString srvr = "WATCHCAM Server MAC address::";
    qDebug(qUtf8Printable(srvr));
    qDebug(qUtf8Printable(getMacAddress()));

    std::string license_mac_sigmind = "00:04:4B:CC:25:F2";


    std::string license_mac_1 = "00:04:4B";



    //d0:50:99:c2:c5:7c
    //d0:50:99:c2:c5:79
    //d0:50:99:c2:c5:7a
    //d0:50:99:c2:c5:7b

    std::string device_mac = getMacAddress().toUtf8().constData();

    if ((device_mac.find(license_mac_sigmind) != std::string::npos) | (device_mac.find(license_mac_1) != std::string::npos)) {





    QCoreApplication::setApplicationName("watchcam");
    //printf( "%s\n", getMacAddress().toAscii().constData() );

    //qPrintable(getMacAddress());



    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

    QApplication a(argc, argv);
    //VlcCommon::setPluginPath(a.applicationDirPath() + "/plugins");


    QFile File(":/qdarkstyle/style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    //a.setStyleSheet(StyleSheet);




    QPixmap pixmap("./.rsc/sigmindLogo.png");
    QSplashScreen splash(pixmap.scaled(600, 400, Qt::KeepAspectRatio, Qt::FastTransformation));
    //QSplashScreen splash(pixmap);
    splash.showMessage("WATCHCAM Loading....... Please Wait", Qt::AlignTop, Qt::black);
    splash.showFullScreen();
    //    splash.
    a.processEvents();

    //qDebug() << "before making mainWindow";

    MainWindow w;
    w.show();

    //qDebug() << "showing making mainWindow";

    //    settingsDialog w;









    //    w.show();

    splash.finish(&w);
    splash.close();






    return a.exec();
      }
        else
        {
            QString srvr = "ERROR!! Device MAC not licensed";
            qDebug(qUtf8Printable(srvr));
    //        QPixmap pixmap("./.rsc/bike.png");
    //        QSplashScreen splash(pixmap.scaled(600, 400, Qt::KeepAspectRatio, Qt::FastTransformation));
    //        //QSplashScreen splash(pixmap);
    //        splash.showMessage("ERROR!! Device MAC not licensed", Qt::AlignTop, Qt::black);
    //        splash.showFullScreen();
            exit(1);
        }


}


//#include "mainwindow.h"
//#include <QApplication>
//#include <QSplashScreen>
//#include <QMetaType>
//#include <vector>
//#include <string>
//#include "rectangle.h"
//#include <dialogs/settingsdialog.h>
//#include <QDebug>

//#include <dlib/image_processing.h>
//#include <dlib/gui_widgets.h>
//#include <dlib/dnn.h>
//#include <dlib/clustering.h>
//#include <dlib/string.h>
//#include <dlib/image_io.h>

//#include <QtCore/QCoreApplication>
//#include <QtWidgets/QApplication>

////#include <VLCQtCore/Common.h>
//#include "QtNetwork/QNetworkInterface"
//#include "QString"



//typedef std::vector<std::pair<watchcam::rectangle,std::string> > myType;
//typedef std::vector< watchcam::rectangle > myType2;
//typedef std::vector<dlib::matrix<float,(long)0,(long)1>> myType3;
//typedef dlib::matrix<float,(long)0,(long)1> myType4;

//Q_DECLARE_METATYPE (cv::Mat)
//Q_DECLARE_METATYPE (myType)
//Q_DECLARE_METATYPE (myType2)
//Q_DECLARE_METATYPE (myType3)
//Q_DECLARE_METATYPE (myType4)




//QString getMacAddress()
//{
//    QString text;
//    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
//    {
//        text += "Interface:"+interface.hardwareAddress()+"\n";
//    }
//    return text;
//}

//int main(int argc, char *argv[])
//{

//    qRegisterMetaType< cv::Mat >("cv::Mat");
//    qRegisterMetaType< myType >("std::vector<std::pair<watchcam::rectangle,std::string> >");
//    qRegisterMetaType< myType2 >("std::vector< watchcam::rectangle >");
//    qRegisterMetaType< myType3 >("std::vector<dlib::matrix<float,(long)0,(long)1>>");
//    qRegisterMetaType< myType4 >("dlib::matrix<float,(long)0,(long)1>");

//    QString srvr = "WATCHCAM Server MAC address::";
//    qDebug(qUtf8Printable(srvr));
//    qDebug(qUtf8Printable(getMacAddress()));

////    std::string license_mac_sigmind = "2A:84:28:39:2D:F0";


////    std::string license_mac_1 = "02:44:50:B5:48:23";

//    std::string license_mac_sigmind = "02:42";


//    std::string license_mac_1 = "D0:50";

////d0:50:99:c2:c5:7c
////d0:50:99:c2:c5:79
////d0:50:99:c2:c5:7a
////d0:50:99:c2:c5:7b

//    std::string device_mac = getMacAddress().toUtf8().constData();

//    if ((device_mac.find(license_mac_sigmind) != std::string::npos) | (device_mac.find(license_mac_1) != std::string::npos)) {





//    QCoreApplication::setApplicationName("watchcam");
//    //printf( "%s\n", getMacAddress().toAscii().constData() );

//    //qPrintable(getMacAddress());



//    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

//    QApplication a(argc, argv);
//    //VlcCommon::setPluginPath(a.applicationDirPath() + "/plugins");


//    QFile File(":/qdarkstyle/style.qss");
//    File.open(QFile::ReadOnly);
//    QString StyleSheet = QLatin1String(File.readAll());

//    //a.setStyleSheet(StyleSheet);




//    QPixmap pixmap("./.rsc/sigmindLogo.png");
//    QSplashScreen splash(pixmap.scaled(600, 400, Qt::KeepAspectRatio, Qt::FastTransformation));
//    //QSplashScreen splash(pixmap);
//    splash.showMessage("WATCHCAM Loading....... Please Wait", Qt::AlignTop, Qt::black);
//    splash.showFullScreen();
////    splash.
//    a.processEvents();

//    ////qDebug() << "before making mainWindow";


//    ////qDebug() << "after making mainWindow";
//MainWindow w;
//    w.show();

//    ////qDebug() << "showing making mainWindow";

////    settingsDialog w;









////    w.show();

//    splash.finish(&w);






//      return a.exec();
//        }
//    else
//    {
//        QString srvr = "ERROR!! Device MAC not licensed";
//        qDebug(qUtf8Printable(srvr));
////        QPixmap pixmap("./.rsc/bike.png");
////        QSplashScreen splash(pixmap.scaled(600, 400, Qt::KeepAspectRatio, Qt::FastTransformation));
////        //QSplashScreen splash(pixmap);
////        splash.showMessage("ERROR!! Device MAC not licensed", Qt::AlignTop, Qt::black);
////        splash.showFullScreen();
//        exit(1);
//    }


//}
