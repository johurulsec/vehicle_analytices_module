#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <dialogs/footagewindow.h>
#include <feed.h>
#include <dialogs/trackingsettingsdialog.h>
#include <mystyles.h>
#include <QTimer>
#include <flowlayout.h>
#include <QGridLayout>
#include <faces.h>
#include <face.h>
#include <QTimer>
#include <expiredialog.h>
#include <eula.h>
#include <QFile>
#include <aboutdialog.h>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QDebug>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <curl/curl.h>
#include <iostream>
#include <ctime>
#include <string.h>
#include "mail/notification.h"
#include "mail/servicecontroller.h"
#include "mail/not.h"
#include <QMenuBar>
#include <mail/not.h>
#include <mail/notwidget.h>
#include <QMouseEvent>
#include "worker.h"
#include "warker.h"
#include <QThread>
#include <QMutex>

//sudo apt install curl libcurl4-openssl-dev

using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool running;
    QVector<Feed*> feeds;

    QTimer blinkTimer;
    QMutex *darknet_mutex;
    FlowLayout *flowLayout;
    QGridLayout *gridLayout;
    int cam_count = 0;

    static GstPadProbeReturn tiler_src_pad_buffer_probe (GstPad * pad, GstPadProbeInfo * info, gpointer u_data);


    std::vector<std::string> blacklist_names;
    std::vector<dlib::matrix<float,0l,1l>> blacklist_descriptors;

    std::vector<std::string> templates_names;
    std::vector<dlib::matrix<float,0l,1l>> template_descriptors;

    // Load face detection and pose estimation models.

    dlib::frontal_face_detector face_detector;

    // We will also use a face landmarking model to align faces to a standard pose:  (see face_landmark_detection_ex.cpp for an introduction)
    dlib::shape_predictor sp;

    std::vector<dlib::matrix<dlib::rgb_pixel>> templates, blacklist_templates;

    // And finally we load the DNN responsible for face recognition.
    anet_type face_net;

    Faces *facesWindow;
    trackingSettingsDialog *trackingWindow;

    myStyles styles;

    footageWindow *footage;

    //Feed  *newFeed2, *newFeed3, *newFeed4;

   // Warker *warker;


      //  QTimer *trialTimer;
//    QString searchOn= "background-color: rgb(115, 210, 22);";
//    QString blinkOff= "border: 2px solid rgb(46, 52, 54);";
//    QString blinkOn= "border: 2px solid rgb(164, 0, 0);";

    void load_faces();

    void setSearchFaceOn();
    void setSearchFaceOff();

    void setSearchObjectOn();
    void setSearchObjectOff();

    void arrangeGrid();

    int widthCal();
    void setSizes(int);


    notWidget *nots;

    void setNotPosition();

    ServiceController *emailController;


   // QNetworkAccessManager *manager;

    QTimer *trialTimer;
    QString plateData;
    QThread *thread;
     Worker *worker;

     QThread *FRthread;
     Warker *warker;

     bool searchOn;
     bool searchFOn;
     bool searchLPRon;
     QString LPR;

    int faceNo;

private slots:



    void replyFinished(QNetworkReply*);

    void replyFinishedOnline(QNetworkReply*);

    void trialCheck();
    void on_startButton_pressed();

    void on_startButton_released();

    void on_searchFaceButton_clicked();

    void on_actionAdd_Camera_triggered();
    void resizeEvent(QResizeEvent *);

    void on_actionShow_Faces_triggered();

    void on_actionAdd_face_triggered();

    void on_actionTracking_triggered();

    //void on_actionFootage_analysis_triggered();

    void on_searchObjectButton_clicked();

    void on_searchLPRbutton_clicked();

    void on_tileButton_clicked();

    void on_actionSettings_triggered();

    void on_actionRTSS_triggered();

    void notificationSLot(bool);

    void setObjectThreshold();

    void on_actionAbout_2_triggered();

   // void emitBlink(cv::Mat);

public slots:
     void DSaddFace_triggered(cv::Mat,int);
    void addFace_triggered(cv::Mat, int);

    void addLPR_triggered(QPixmap , int);
    void addObject(QPixmap, QString, int);
    void addLP(QPixmap, QString, int);
    void addFR(QPixmap, QString, int);

    void makeNotification(QPixmap, QString, int);

    void addNotToBar(Notification* noti);

    void disagreed();

    void agreed();

    void cleanTiles();
    //void lprNotify(QPixmap, QString, int);

signals:
    void sendMail();
    void emitDSFace(cv::Mat img, int imgNo);
  //  void load_template();
private:
    Ui::MainWindow *ui;

    void mousePressEvent(QMouseEvent*);

    bool notOn;
signals:
    void requestUpdateLPR(QPixmap pic, QString str, int indx);
    void notifyLPR(QPixmap p, QString str, int indx);

    void requestUpdateFR(cv::Mat pic, QString str, int indx);
   // void load_template();
   // void load_template(std::vector<string> &names, dlib::frontal_face_detector &detector, std::vector<dlib::matrix<dlib::rgb_pixel> > &templates, dlib::shape_predictor &sp, anet_type &face_net);
    //void notifyLPR(QPixmap p, QString str, int indx);

   void emitCam(QString cam, int prior);

   void emitCam2(QString cam, int prior);

   void emitCam3(QString cam, int prior);

   void emitCam4(QString cam, int prior);

   void emitCam5(QString cam, int prior);

   void emitCam6(QString cam, int prior);

   void emitCam7(QString cam, int prior);



};

#endif // MAINWINDOW_H
