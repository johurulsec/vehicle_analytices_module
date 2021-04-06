#ifndef GETRTSP_H
#define GETRTSP_H

#include <QVector>
#include <QString>
#include <QObject>
//#include "descdevice.h"
//#include "discoveryobj.h"
//getrtsp * DiscoveryObj::theDiscovery = NULL;

class get_rtsp : public QObject{

    Q_OBJECT

public:
    get_rtsp();
   // ~getrtsp();
   // DiscoveryObj *discoveryObj = nullptr;
     std::string generate_rtsp(char szHostName[128], std::string passwd);
    //void on_pushButton_clicked();
    std::string RTSPurl = "Login to geneate";
    std::string dev_pass;


};

#endif // MAINWINDOW_H
