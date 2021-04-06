#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <MediaPlayer/player.h>
#include <QMainWindow>
#include <tilerdisplay.h>
//#include <deepstream_source_code.h>
//#ininclude <helperthread.h>
#include <QLabel>
#include <dialogs/footagewindow.h>
//#include <feed.h>
#include <dialogs/trackingsettingsdialog.h>
#include <mystyles.h>
#include <flowlayout.h>
#include <QGridLayout>
#include <faces.h>
#include <face.h>
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
#include <Database/config_database.h>
#include <DatabaseConnection/sqlite_connection.h>
#include <QSqlQuery>
#include <QTextCodec>
#include <QByteArray>
#include <EmployeeAttendence/employeeattendence.h>
#include <GenerateReport/reportgeneratefromtoto.h>
#include <Database/search_by_date_time.h>
#include <CaluculateTimePerObBetweenInOutTime/calculatetimeperobject.h>

#include <db_sync/db_sync.h>
#include <QTimer>
#include <db_sync/sync_checker.h>

#include <dialogs/settingsdialog.h>
#include <dialogs/progressbarloading.h>
//#include "deepstream_source_code.h"
#include <ShowFaceInTiles/showface.h>
#include <SearchByGivenImage/searchbygivenimage.h>
#include <SearchByGivenImage/searchbyimage.h>

//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
#include "mail/servicecontrollerforlpr.h"
#include <QDesktopWidget>
#include "mail/uniquefacewidget.h"
//#include <mail/lpnotif.h>
#include <mail/lpsinglewidg.h>
#include <mail/lpnotwidget.h>
#include "rectangle.h"
#include <QMap>
#include <QMapIterator>
#include <names_buf_info.h>

#include<helperthread.h>
#include<testerthread.h>
#include "overcrowdthread.h"

#include "onvif_hasan/mainwindow_onvif.h"

using namespace Buf_info;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //    GMainLoop *loop = NULL;
    //      GstElement *pipeline = NULL, *streammux = NULL, *sink = NULL, *pgie = NULL,
    //          *nvvidconv = NULL, *nvosd = NULL, *tiler = NULL, *dsExample;
    //   // #ifdef PLATFORM_TEGRA
    //      GstElement *transform = NULL;
    //  //  #endif
    //      GstBus *bus = NULL;
    //      guint bus_watch_id;
    //      GstPad *tiler_src_pad = NULL;
    //      guint i, num_sources;
    //      guint tiler_rows, tiler_columns;
    //      guint pgie_batch_size;
    //Ui::MainWindow *ui;




    //protected:
    //    void paintEvent(QPaintEvent *);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    static void dispInMainWind();
    static void dispInMainWind2();
    static int getDispWidth();
    static int getDispHeight();
    void addToDB(int Id, QPixmap m_pic, QPixmap pic, QString str, int indx, double confidence, QString, int, QString, QString, QString, int, QString, int, QString);

    static void fromDsToMain(cv::Mat pic, int n,double, std::vector< watchcam::rectangle >, int type);
//    static void fromDsToMain(cv::Mat *main_obj, cv::Mat *sub_obj_of_main, watchcam::rectangle);
    static void fromDsToMain(cv::Mat main_obj, cv::Mat sub_obj_of_main, watchcam::rectangle);
    static void fromDsToMain(cv::Mat *main_obj, cv::Mat *sub_obj_of_main, Buf_info::names_buf_info*);
    static void fromDsToMain(cv::Mat pic, cv::Mat pic2);
    static void fromDsToMain(Buf_info::names_buf_info*);
    static void fromDsToMain(cv::Mat pic, watchcam::rectangle);
    static void fromDsToMainForOvercrowding(int);

    QString encodeString(QString data);

    void dataInsertIntoDb(QPixmap, QPixmap, int, QString, QString, QString, int, int);
    void dataInsertIntoDb(QPixmap, QPixmap, QPixmap, int,  float,QString, QString, int);
    void dataInsertIntoDb(QPixmap person, QPixmap face, int source, QString mask_status);

    void dataInsertIntoDbPerson(QPixmap person, int source);
    void dataInsertIntoDbFace(QPixmap face, int source, QString);

    bool running;
    //    QVector<Feed*> feeds;

    QTimer blinkTimer;
    QMutex *darknet_mutex;
    FlowLayout *flowLayout;
    QGridLayout *gridLayout;
    int cam_count = 0;



    //std::deque<cv::Mat> frameQueue;
    //    static void fromGstPadProbeReturnToDsAddFaceTriggered(cv::Mat,int, void *);

    // static gboolean create_common_elements (NvDsConfig * config, NvDsPipeline * pipeline, GstElement ** sink_elem, GstElement ** src_elem, bbox_generated_callback bbox_generated_post_analytics_cb);

    static void initialize_warker();

    std::vector<std::string> blacklist_names;
    // std::vector<dlib::matrix<float,0l,1l>> blacklist_descriptors;

    std::vector<std::string> templates_names;
    //   std::vector<dlib::matrix<float,0l,1l>> template_descriptors;

    // Load face detection and pose estimation models.

    //    dlib::frontal_face_detector face_detector;

    //    // We will also use a face landmarking model to align faces to a standard pose:  (see face_landmark_detection_ex.cpp for an introduction)
    //    dlib::shape_predictor sp;

    //    std::vector<dlib::matrix<dlib::rgb_pixel>> templates, blacklist_templates;

    //    // And finally we load the DNN responsible for face recognition.
    //    anet_type face_net;

    Faces *facesWindow;
    TilerDisplay *tilerdisplayWindow;
    trackingSettingsDialog *trackingWindow;

    myStyles styles;

    //footageWindow *footage;

    // Feed  *newFeed2;

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
    QTimer *recordDeleteTimer;
    QString plateData;
    QThread *thread;
    Worker *worker;

    QThread *FRthread;
     Warker *warker;
    //  Deepstream_source_code *dsc;

    bool searchOn;
    bool searchFOn;
    bool searchLPRon;
    QString LPR;
    int lp_id = 0;

    int faceNo;

    void NotificationManager();

    QThread *db_sync_th;
    db_sync *sync_var;
    QTimer *sy_timer;

    int getLastDBId();

    QThread *synnc_chek_T;
    sync_checker *sync_ch;

    int idc, video_srcc, statesc, rec_check;
    QString namec, date_timec, save_pathc;
    double con;
    void centerAndResize();

    uniqueFaceWidget *uniq_face_window;

    static void setNegative_left_clicked_full_disp_blink();
    static void setPositive_left_clicked_full_disp_blink();
    QString lprBanglaToEnglishTransform(QString);
    QString singleCharLprBangToEng(QString);
    void detectedLpToDb(QString, QString, QString, QString, QString);

    QThread *helpThOb;
    HelperThread *helperThread;
    QThread *testThOb;
    TesterThread *testerThread;

    QThread *overThOb;
    OvercrowdThread *overThread;
    QString encodeStringForLPRtrainData(QString data);
    Player *player_obj;

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

    void on_actionDatabase_Configuration_triggered();

    void on_actionSearch_by_date_and_time_triggered();

    void on_actionStudent_Attendece_triggered();

    void on_actionEmployee_Attendence_triggered();

    void on_actionTotal_Present_Time_For_Each_Employe_triggered();

    void on_actionTotal_Present_Time_For_Each_Employe_toggled(bool arg1);

    void on_actionSearch_By_Given_Image_triggered();

    void on_actionFace_Notification_triggered();

    void on_startButton_clicked();

    void on_actionMedia_Player_triggered();

public slots:
    void emitFunction(cv::Mat foo);
    void DSaddFace_triggered(Buf_info::names_buf_info*);
    void DSaddFace_triggered(cv::Mat*, cv::Mat*, Buf_info::names_buf_info*);
    void DSaddFace_triggered(cv::Mat*, cv::Mat*, watchcam::rectangle);
    void DSaddFace_triggered(cv::Mat*, cv::Mat*, cv::Mat*, int, double, /*std::vector< *//*watchcam::rectangle*/ /*>*/int, QString, QString, int, int);
    void DSaddFace_triggered(cv::Mat*, cv::Mat*, int, double, /*std::vector< *//*watchcam::rectangle*/ /*>*/int, QString, QString, int, int);
    void DSaddFace_triggered(cv::Mat*, cv::Mat*, int, double, /*std::vector< *//*watchcam::rectangle*/ /*>*/int, QString, QString, int);
    void DSaddFace_triggered(cv::Mat*, cv::Mat*, int, double, /*std::vector< *//*watchcam::rectangle*/ /*>*/int, QString, QString);
    void DSaddFace_triggered(cv::Mat, cv::Mat, QString, int, QString);
    //----
    void DSaddFace_triggered(cv::Mat, watchcam::rectangle);
    void DSoverCrowd_triggered(int);
    void DSaddLPR_triggered(cv::Mat, cv::Mat, int, double, int, QString);

    void addFace_triggered(cv::Mat, int);

    void addLPR_triggered(QPixmap , int);
    void addObject(QPixmap, QString, int);
    void addLP(QPixmap, QPixmap, QString, int, QString);
    void addLP(QPixmap, QString, QPixmap, QString);
    //void addFR(QPixmap, QString, int, double);
    void addFR(QPixmap,QPixmap, QString, int, double, /*dlib::matrix<float,(long)0,(long)1>,*/ int, int, QString, int, QString, int);
    void addFR(QPixmap,QPixmap, QString, int, double, dlib::matrix<float,(long)0,(long)1>, int, int, QString, int, QString, int, int);
    void addFR(QPixmap,QPixmap,QPixmap,float);
    void addFR(QPixmap, QPixmap, QPixmap, float, int, QString, QString, int);

    //void makeNotification(QPixmap, QString, int);

    void makeNotification(QPixmap, QPixmap, QString, int, int, int, double, QString, int);
    void makeNotification(QPixmap, QPixmap, QString, int, int, int, double, QString, int, QString);

    void addNotToBar(Notification* noti);

    void disagreed();

    void agreed();

    void cleanTiles();
    //void lprNotify(QPixmap, QString, int);

    bool AddToLoadTemplate(QString name_, QString face_path);

    void deleteFromLoadTem(QString, QString); // delete from template

    void dowarkStarted();


    void dbSyncDowark();
    void callAddToDb(int Id, QPixmap pic, QString str, int indx, double confidence, QString date_time, int sync_states, QString, QString, QString, int, QString);
    void syncChecker();
    void syncChCallDoWark();
    void updateFeedAddFace(int);

    void addToAddFace(QString, QString);
    void batchDirMain(QString);
    void fromBatchEnr(QString, QString);
    void nlBatchNotify(QString);
    void nBatchLoadingDone(int, int);

    void getSuspectCheckStateFromSettingsDialog(bool);

    void totalSizeOfNameToProg(int);
    void fr_thresholed_value(float);
    void lpr_api_select_value(QString);

    void fromSearchByGI(QString, QString);
    void inMain(QStringList);
    void loadDetectedFace();
    void faceDesFromWark(/*std::vector<dlib::matrix<float,(long)0,(long)1>>*/);
    void fromSearchByImgtoMain(QString);
    //    void getDisFromDs(Display*);
    void make_notification_for_unique_face(QPixmap, QString, int, int, int, double, int, QString, int);
    void getDispRowsColumns(int, int);
    void blinkTimerSl();
    void blinkTimerSearchByName();
    void deleteLastOneDayFromEightDays();
    void callDoWorkFromMain();
    void addNotToBarLP(Notification *noti);
    void face_detection_work(bool);
    void lpr_detection_work(bool);
    void helperThan();

    void overThan();

    void dowark();
    void addFR(QPixmap, QPixmap, QString, int, QString);
    void addFR(QPixmap, int);
    void addFRForOvercrowd(int);

    void addFR(QPixmap, QPixmap, QString, int, double, dlib::matrix<float,(long)0,(long)1>, int);
    void addFR_2(QPixmap, QString, int, double);
    //------
    void cleanSpecificRecordVideo();
    void deleteSmartRecordVideoAfterHowManyDays(int, QString);
    void getDivisorFromSettings(std::vector<std::pair<int, double>>);

signals:
    void sendMail();
    void emitDSFace(cv::Mat img, int imgNo);
    void batchDirFromMain(QString);
    void goSearchByGivenIm(QStringList);
    void goSBI(QStringList);
    //  void load_template();
    void goHelperThread(QPixmap, QPixmap, QString, int, QString);
    void goHelperThread(QPixmap, int, int);
    void goOverThread(int);
    void tester();
   void finishedTh();
   void sourceDivisorPassToDS(std::vector<std::pair<int, double>>);
   void unique_lp_to_main_window(QPixmap, QString, int, int, int, double, int, QString, int);


private:
    Ui::MainWindow *ui;

    void mousePressEvent(QMouseEvent*);

    bool notOn;

    config_database *configdb;
    bool flagOfNotificationmanager = false;
    QThread *deepstream_thread;
    int check_last_id;
    int cntt=0, cntt2 = 0, counter=0;

    settingsDialog *newSettings;
    bool suspect_state;

    ProgressBarLoading *pr;
    ShowFace *show_face;
    float FRThreshold;
    QString api_str_for_lpr;

    SearchByGivenImage *search;
    SearchByImage *sbi;

    std::vector<std::string> detected_names;
    // std::vector<dlib::matrix<float,0l,1l>> detected_temp_descriptors;

    int wid;
    int hei;
    int menubar_height;

    bool checker_not_flg = false;

    std::vector< watchcam::rectangle > rects; // display size in rectangle
    int iix = 0;
    QFrame  *frame;
    bool blink_check;
    QTimer *blink_timer;
    //bool blink_check_from_ui;
    QPair<int, int> source_and_object;

    QFrame *frame_search_by_name;
    bool blink_check_by_name;
    QTimer *blink_timer_search_by_name;
    QPair<QString, int> name_and_source;

    QTimer *delete_prev_date;

    ServiceControllerForLPR *lpr_emailController;
    LpNotWidget *lpnots;
    bool left_clicked_full_disp_blink;
    bool face_detection_check_or_uncheck;
    bool lpr_detection_check_or_uncheck;

    int distance_vio = 0;
    int unmask = 0;


    bool ppppp = false;
    bool fffff = false;

    //---------
    QSet<QString>stor_date;
    int how_may_days = 30;
    QString smart_record_video_save_directory;
    //==============

    QSet<QString>uniqLpSet;
    int uniqLpChecker = 0;

    int overcrowed_value_from_ds;
    int cker = 0;
    MainWindow_onvif *onvif_h;

signals:
    void requestUpdateLPR(cv::Mat, cv::Mat pic, QString str, int indx, QString, QString);
    //    void notifyLPR(QPixmap p, QString str, int indx);
    //    void notifyFace(QPixmap p, QString str, int indx);

    void notifyFaceNotMan(QPixmap p, QString str, int indx, int clstr, int timesofsameImg);
    void addUniqeFaceNotMan(QPixmap, QString, int/*, dlib::matrix<float,(long)0,(long)1>*/);

    //    void requestUpdateFR(cv::Mat pic, QString str, int indx);
    void requestUpdateFR(cv::Mat m_pic, cv::Mat pic, QString str, int indx, float, int, bool, QString);
    void requestUpdateFR(cv::Mat m_pic, cv::Mat pic, QString str, int indx, float, float, bool, QString, int);
    void requestUpdateFR(cv::Mat m_pic, cv::Mat pic, QString str, int indx, float, float, bool, QString, int, int);
    void requestUpdateFR(cv::Mat m_pic, cv::Mat sub_p, int, bool, float threshold_val);
    void requestUpdateFR(cv::Mat m_pic, cv::Mat, cv::Mat pic, QString str, int indx, float, float, bool, QString, int, int);
    void requestUpdateFR(Buf_info::names_buf_info*);
    void requestUpdateFR(cv::Mat, cv::Mat, Buf_info::names_buf_info*);

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

    void requestWorkDS();
    void finishedDS();

    void requestDoWark(int, QPixmap, QString, int, double, QString);
    void data_transfer_to_syncDowark(int, QString, QString, QString, double, int, int, int);
    void data_transfer_to_syncDowark(int, QString, QString, QString, int, QString, int);

    void setDifferSettings(int);
    void valueProgChange(int);
};

#endif // MAINWINDOW_H
