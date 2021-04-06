#ifndef MAINWINDOW_ONVIF_H
#define MAINWINDOW_ONVIF_H

#include <QMainWindow>
#include "discoveryobj.h"
#include <bits/stdc++.h>
#include <string>
#include <QMediaPlayer>
#include <QTableWidget>
#include <QVideoWidget>
namespace Ui {
class MainWindow_onvif;
}

class MainWindow_onvif : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_onvif(QWidget *parent = 0);
    ~MainWindow_onvif();
    int getRTSPUrl(const char*mediaAddr,std::string&rtspUrl);
    int getProfile(const char*mediaAddr,std::string&profileToken);
    int DeviceInformation(char*szHostName,QString &pass_pass);
    int getMediaUrl(/* const char* deviceAddr,*/std::string& MediaAddr);
    int ptzContinuousMove(/*const char* deviceAddr,*/int command);
    int ptzRelativeMove(/*const char* deviceAddr,*/int command);
    int ptz();
//    void loadFromTextFile();
////    void editSourceNumber();
//    void TemplateforSourecFile();
    void addCameraBlocksToConfigFile();
    void getSourceInfosFromConfigFileData();
    QString getData(QString substring, QString subproperty, int parentfirst);
    bool islink(QString);
    struct data{
        QString  ip,port,rtsp,indx;
        data(QString  ipp="", QString  portt="", QString  rtspp="",QString indxx="" )
        {
            ip = ipp, port = portt, rtsp = rtspp ,indx = indxx;
        }
    };
    QString configFileData;
    std::vector<data>remove_data;
    QString readConfigFileData();
    int getLastSourceNumberFromConfigFile();
    int getNumberOfSources();
    int getBlockEndPositionBefore(QString pattern);
    QString generateSourceBlockAfter(int lastSourceNumber);
    void addNewBlockAt(int previousBlockEndPosition, QString newBlockData);
    void saveConfigFile();
    QString generateSinkBlockAfter(int lastSourceNumber);
    int end_indexof(QString mainString, int first, QString endString, int initial_index);
    void addSourceAfter(int lastSourceNumber);
    void addSinkAfter(int lastSourceNumber);

private slots:
    void on_btnSendProb_clicked();

    void onDiscoveredDevice(DescDevice);

    void on_display_video_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_login_clicked();

    void on_right_clicked();

    void on_left_clicked();

    void on_down_clicked();

    void on_up_clicked();

    void on_ZoomIn_clicked();

    void on_ZoomOut_clicked();

    void on_leftupper_clicked();

    void on_leftlower_clicked();

    void on_rightupper_clicked();

    void on_rightlower_clicked();

    void on_speed_clicked();

    void on_row_up_clicked();

    void on_row_down_clicked();

    void on_pushButton_write_clicked();

    void on_Undo_remove_clicked();

private:
    Ui::MainWindow_onvif *ui;
    QGraphicsVideoItem *videoItem;
    QMediaPlayer* mediaPlayer;
    QSize videoSize ;
    DiscoveryObj *discoveryObj = NULL;
    std::string port,ip_address;
    std::string m_passwd,m_username,m_deviceurl,rtsp_url,rtsp;
    QString IP_add,addrtsp,PORT,Password,Username,RTSP,Device_INFO,Table_rtsp ;
    QString srcc,ipp,portt,rtspp,srcc2,ipp2,portt2,rtspp2,indx,indx2 ;
    QVideoWidget *videoWidget;
};

#endif // MAINWINDOW_ONVIF_H
