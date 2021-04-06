#ifndef PROBING_H
#define PROBING_H
#include <QMainWindow>
#include "descdevice.h"
#include "discoveryobj.h"
#include <iostream>
#include <string>
#include <QObject>
class probing : public QObject
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = 0);

    explicit probing(QObject *parent = nullptr);
    DiscoveryObj *discoveryObj = NULL;

   // std::string generate_details(char szHostName[128], std::string passwd);
    //void on_pushButton_clicked();

    std::string dev_pass;

private slots:

    void onDiscoveredDevice(DescDevice);

    //void on_btnSendProb_clicked();

//    void on_btnGetMediaURL_clicked();

//    void on_btnGetDeviceInformation_clicked();

//    void on_btnPTZTest_clicked();

//    void on_btnReceiverTest_clicked();

//    void on_btnEventTest_clicked();

//    void on_btnAnalyticsTest_clicked();

//    void on_btnVideoAnalyticsDeviceTest_clicked();

//    void on_btnRecordingControlTest_clicked();

//    void on_btnRecordingSearchTest_clicked();

//    void on_btnReplayControlTest_clicked();

//    void on_btnDisplayTest_clicked();

};


#endif // PROBING_H
