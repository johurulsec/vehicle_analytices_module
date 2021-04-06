#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MediaPlayer/player.h"
#include <deepstream_source_code.h>

//#include <dialogs/settingsdialog.h>

#include <QDebug>
#include <QFile>
#include <QMutex>
#include "deepstream/deepstream_app.h"
#include "deepstream_config_file_parser.h"
#include "nvds_version.h"
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "deepstream/deepstream_app.h"
#include "deepstream_config_file_parser.h"
#include "nvds_version.h"
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <gst/gst.h>
#include <glib.h>
#include "gstnvdsmeta.h"
#include <ostream>
#include <iostream>
#include <math.h>
#include <stdlib.h>

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>


static MainWindow * staticO;
Deepstream_source_code *dsc;
Display* display;

void MainWindow::load_faces()
{
    ////qDebug()<<"inside load faces\n";
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    staticO = this;
    ui->setupUi(this);

    QSize availableSize = qApp->desktop()->availableGeometry().size();
    int width = availableSize.width();
    int height = availableSize.height();
    menubar_height = ui->seachLayoutWidget->geometry().height();
    //    //qDebug() << "---d=d " << ui->seachLayoutWidget->geometry().height();

    wid = width;
    hei = height;
    qDebug()<<"Mainwindow width : "<<wid<<" and height : "<<hei;
    //centerAndResize();// resize mainwindow dynamic

    /* Basedul islam */
    configdb = new config_database();
    connect(configdb, SIGNAL(AddToLoadTemplate(QString,QString)), this, SLOT(AddToLoadTemplate(QString,QString)));
    connect(configdb, SIGNAL(deleteFromLoadTem(QString, QString)), this, SLOT(deleteFromLoadTem(QString, QString)));
    // end of Basedul islam
    connect(configdb, SIGNAL(batchDir(QString)), this, SLOT(batchDirMain(QString)));

    QPixmap wcIcon("./.rsc/wc.png");
    ui->iconWC->setPixmap(wcIcon.scaledToHeight(60));
    styles.initializeValues();
    ////qDebug() << myStyles::objectSensitivityValue;
    ////qDebug() << myStyles::emailsTo;

    //      QString cam1 = "/home/imran/Downloads/deepstream_sdk_v4.0.1_jetson/samples/streams/sample_720p.mp4";

    //  //   QString cam1 = "rtsp://admin:admin123@103.113.17.146:2400/cam/realmonitor?channel=1&subtype=0";

    //      QString cam2 = "/home/imran/Downloads/deepstream_sdk_v4.0.1_jetson/samples/streams/sample_720p.mp4";

    //      QString cam3 = "/home/imran/Downloads/deepstream_sdk_v4.0.1_jetson/samples/streams/sample_720p.mp4";

    //      QString cam4 = "/home/imran/Downloads/deepstream_sdk_v4.0.1_jetson/samples/streams/sample_720p.mp4";
    // //
    //      QString cam5 = "/home/imran/Downloads/deepstream_sdk_v4.0.1_jetson/samples/streams/sample_720p.mp4";

    //      QString cam6 = "/home/imran/Downloads/deepstream_sdk_v4.0.1_jetson/samples/streams/sample_720p.mp4";

    //      QString cam7 = "/home/imran/Downloads/deepstream_sdk_v4.0.1_jetson/samples/streams/sample_720p.mp4";

    //      QString cam8 = "0";

    //      QString camList[5];

    //      QFile file("./files/cameraList.txt");
    //      if(!file.open(QIODevice::ReadOnly)) {
    //          //QMessageBox::information(0, "error", file.errorString());
    //      }

    //      QTextStream in(&file);
    //      int camListI=0;
    //      while(!in.atEnd()) {
    //         camList[camListI] = in.readLine();
    //            camListI++;
    //      }

    //QString cam5 = camList[0];
    // QString cam9 = camList[1];


    ////qDebug() << "CamList read >> " << cam5 << " and " << cam9 ;
    // running= false;
    this->setWindowTitle("WATCHCAM");
    this->setAttribute(Qt::WA_DeleteOnClose , true);
    darknet_mutex = new QMutex();

    // this->show();

    flowLayout= new FlowLayout(0,0,0);



    ui->scrollAreaWidgetContents->setLayout(flowLayout);

    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //gridLayout= new QGridLayout();
    searchOn = false;
    searchFOn = false;
    searchLPRon = false;

    //  connect(this, SIGNAL(emitDSFace(cv::Mat, int)), this, SLOT(DSaddFace_triggered(cv::Mat, int)));
    //    connect(newFeed, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
    //    connect(newFeed, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
    //    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
    //    connect(newFeed, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));





    /* for face notification */
    //connect(this, SIGNAL(notifyFace(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));

    facesWindow = new Faces(this);
    tilerdisplayWindow = new TilerDisplay(this);
    /* for face notification show right bar[ temporay now, go to on_tileButton_clicked] */
    connect(facesWindow, SIGNAL(notifyFaceFromUniqueFace(QPixmap, QPixmap, QString, int, int, int, double, QString, int)), this, SLOT(makeNotification(QPixmap, QPixmap, QString, int, int, int, double, QString, int)));
    // connect(facesWindow, SIGNAL(notifyFaceFromUniqueFace(QPixmap,QPixmap, QString, int, int, int, double, QString, int, QString)), this, SLOT(makeNotification(QPixmap,QPixmap, QString, int, int, int, double, QString, int, QString)));

    // facesWindow->deleteLater();
    // facesWindow = nullptr;
    ui->colorCombo->addItems(myStyles::colors);
    ui->objectCombo->addItems(myStyles::objects);

    QMenuBar *rightBar = new QMenuBar(ui->menuBar);

    QAction *action = new QAction("Notifications", rightBar);
    rightBar->addAction(action);

    connect(action, SIGNAL(triggered(bool)), this, SLOT(notificationSLot(bool)));

    ui->menuBar->setCornerWidget(rightBar);
    //nots= new notWidget(this);
    nots= new notWidget(this);
    lpr_emailController = new ServiceControllerForLPR(this);
    connect(lpr_emailController, SIGNAL(addANotLP(Notification*)), this, SLOT(addNotToBarLP(Notification*)));

    lpnots = new LpNotWidget(this);
    lpnots->setVisible(false);
    setNotPosition();
    nots->setVisible(false);
    notOn= false;

    emailController= new ServiceController(this);

    connect(emailController, SIGNAL(addANot(Notification*)), this, SLOT(addNotToBar(Notification*)));


    //manager = new QNetworkAccessManager(this);

    // connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    ui->startButton->setDisabled(false);  // True for Trial

    ui->menuBar->setDisabled(false);    // True for trial

    //  ui->actionFootage_analysis->setDisabled(true);
    ui->scrollArea->setDisabled(false);
    //    eula *eulaDialog = new eula;
    //    eulaDialog->setAttribute( Qt::WA_DeleteOnClose );
    //    connect(eulaDialog, SIGNAL(agree()), this, SLOT(agreed()));
    //    connect(eulaDialog, SIGNAL(disagree()), this, SLOT(disagreed()));
    //    eulaDialog->show();

    this->setWindowTitle("WATCHCAM");
    this->showMaximized();
    //    ui->pauseButton->setHidden(true);
    //    ui->playButton->setHidden(true);
    //    ui->nextButton->setHidden(true);
    // this->show();
    thread = new QThread();
    worker = new Worker();

    worker->moveToThread(thread);

    //    conconnect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), this, SLOT(
    //    conconnect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), this, SLOT(valueChanged(QPixmap,QString,int));
    //          //  connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT()
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));

    connect(thread, SIGNAL(started()), this, SLOT(callDoWorkFromMain()));
    connect(this, SIGNAL(requestUpdateLPR(cv::Mat, cv::Mat,QString,int, QString, QString)), worker, SLOT(doWork(cv::Mat, cv::Mat,QString,int, QString, QString)));
    //   //
    //   // connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT(valueChanged(QPixmap,QString,int)));
    connect(worker, SIGNAL(valueChanged(QPixmap, QPixmap,QString,int, QString)), this, SLOT(addLP(QPixmap, QPixmap,QString,int, QString)));
    connect(worker, SIGNAL(valueChanged(QPixmap,QString,QPixmap, QString)), this, SLOT(addLP(QPixmap,QString,QPixmap, QString)));
    connect(worker, SIGNAL(finishedLPR()), thread, SLOT(quit()), Qt::DirectConnection);

    FRthread = new QThread();
    warker = new Warker();
    warker->moveToThread(FRthread);
    warker->load_template();
    //    // warker->requestWark();
    //    // face_detector = dlib::get_frontal_face_detector();
    //    ////qDebug()<<"face detector initiated\n";
    //    // std::vector<string> names;
    //    //  GetFilesInDirectory(templates_names,"./faces/temp_late");

    //    //d.message = "message\n";


    //    //  warker->setup(templates_names, template_descriptors);
    //    //   warker->setup(templates_names,template_descriptors);
    //    // connect(this,SIGNAL(load_template()), warker, SLOT(receive_template()));

    connect(warker, SIGNAL(warkRequested()), FRthread, SLOT(start()));
    connect(FRthread, SIGNAL(started()), this, SLOT(dowarkStarted()));
    //    //  connect(thread, SIGNAL(started()), worker, SLOT(doWork(int)));
    //    //    connect(this, SIGNAL(requestUpdateFR(cv::Mat,QString,int)), warker, SLOT(doWark(cv::Mat,QString,int)));
    //    connect(this, SIGNAL(requestUpdateFR(cv::Mat,cv::Mat,QString,int, float, int, bool, QString)), warker, SLOT(doWark(cv::Mat, cv::Mat,QString,int, float, int, bool, QString)));
    //    connect(this, SIGNAL(requestUpdateFR(cv::Mat,cv::Mat,QString,int, float, float, bool, QString, int)), warker, SLOT(doWark(cv::Mat, cv::Mat,QString,int, float, float, bool, QString, int)));
    //    connect(this, SIGNAL(requestUpdateFR(cv::Mat,cv::Mat,QString,int, float, float, bool, QString, int, int)), warker, SLOT(doWark(cv::Mat, cv::Mat,QString,int, float, float, bool, QString, int, int)));
    connect(this, SIGNAL(requestUpdateFR(cv::Mat, cv::Mat, int, bool, float)), warker, SLOT(doWark(cv::Mat, cv::Mat, int, bool, float)));

    //connect(this, SIGNAL(requestUpdateFR(cv::Mat,cv::Mat,cv::Mat,QString,int, float, float, bool, QString, int, int)), warker, SLOT(doWark(cv::Mat,cv::Mat, cv::Mat,QString,int, float, float, bool, QString, int, int)));
    //    connect(this, SIGNAL(requestUpdateFR(Buf_info::names_buf_info*)), warker, SLOT(doWark(Buf_info::names_buf_info*)));
    //    connect(this, SIGNAL(requestUpdateFR(cv::Mat, cv::Mat, Buf_info::names_buf_info*)), warker, SLOT(doWark(cv::Mat, cv::Mat, Buf_info::names_buf_info*)));

    //    //connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), this, SLOT(valueChanged(QPixmap,QString,int));
    //    //  connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT()

    //    // connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT(valueChanged(QPixmap,QString,int)));
    //    connect(warker, SIGNAL(valueFRChanged(QPixmap, QPixmap,QString,int, double, dlib::matrix<float,(long)0,(long)1>, int, int, QString, int, QString, int)), this, SLOT(addFR(QPixmap,QPixmap,QString,int, double, dlib::matrix<float,(long)0,(long)1>, int, int, QString, int, QString, int)));
    //    connect(warker, SIGNAL(valueFRChanged(QPixmap, QPixmap,QString,int, double, dlib::matrix<float,(long)0,(long)1>, int, int, QString, int, QString, int, int)), this, SLOT(addFR(QPixmap,QPixmap,QString,int, double, dlib::matrix<float,(long)0,(long)1>, int, int, QString, int, QString, int, int)));
    connect(warker, SIGNAL(valueFRChanged(QPixmap, QPixmap, QString, int, double, dlib::matrix<float,(long)0,(long)1>, int)), this, SLOT(addFR(QPixmap, QPixmap, QString, int, double, dlib::matrix<float,(long)0,(long)1>, int)));
    connect(warker, SIGNAL(valueFRChanged(QPixmap, QString, int, double)), this, SLOT(addFR_2(QPixmap, QString, int, double)));

    //    connect(warker, SIGNAL(valueFRChanged(QPixmap,QPixmap, QPixmap, float)), this, SLOT(addFR(QPixmap,QPixmap,QPixmap, float)));
    //    connect(warker, SIGNAL(valueFRChanged(QPixmap, QPixmap, QPixmap, float, int, QString, QString, int)), this, SLOT(addFR(QPixmap, QPixmap, QPixmap, float, int, QString, QString, int)));
    connect(warker, SIGNAL(finishedFR()), FRthread, SLOT(quit()), Qt::DirectConnection);

    //    connect(this, SIGNAL(batchDirFromMain(QString)), warker, SLOT(batchEnrollment(QString)));
    //    connect(warker, SIGNAL(batchLoadingDone(int, int)), this, SLOT(nBatchLoadingDone(int, int)));
    //    connect(warker, SIGNAL(notLoadedBatch(QString)), this, SLOT(nlBatchNotify(QString)));
    connect(warker, SIGNAL(addToDbBatch(QString, QString)), this, SLOT(fromBatchEnr(QString, QString)));
    //    connect(warker, SIGNAL(totSizeOfNames(int)), this, SLOT(totalSizeOfNameToProg(int)));
    //    //  facesWindow->setAttribute( Qt::WA_DeleteOnClose , true);
    //    connect(warker, SIGNAL(faceDesToMain(std::vector<dlib::matrix<float,(long)0,(long)1>>)), this, SLOT(faceDesFromWark(std::vector<dlib::matrix<float,(long)0,(long)1>>)));

    printf("starting");

    dsc = new Deepstream_source_code(this/*, width, height*/);
    // dsc = new Deepstream_source_code();
    deepstream_thread = new QThread();
    //dsc->constructorDeepStream();
    dsc->moveToThread(deepstream_thread);
    connect(this, SIGNAL(requestWorkDS()), deepstream_thread, SLOT(start()));
    connect(deepstream_thread, SIGNAL(started()), dsc, SLOT(startDeepStream()));
    connect(this, SIGNAL(finishedDS()), deepstream_thread, SLOT(quit()), Qt::DirectConnection);
    //connect(dsc, SIGNAL(sendDisToMainFromDssc(Display*)), this, SLOT(getDisFromDs(Display*)));
    connect(dsc, SIGNAL(setDispRowColumn(int, int)), this, SLOT(getDispRowsColumns(int,int)));
    connect(this, SIGNAL(sourceDivisorPassToDS(std::vector<std::pair<int, double>>)), dsc, SLOT(gotDivisorValue(std::vector<std::pair<int, double>>)));

    left_clicked_full_disp_blink = false;
    emit requestWorkDS();



    NotificationManager();

    // //qDebug()<<"constr of mainwindow tested";

    trialTimer= new QTimer(this);
    connect(trialTimer, SIGNAL(timeout()), this, SLOT(cleanTiles()));
    trialTimer->start(3600000);// 1 minute

    /* db sync start */
    db_sync_th = new QThread();
    sync_var = new db_sync();
    sync_var->moveToThread(db_sync_th);
    connect(sync_var, SIGNAL(workRequestedSyTh()), db_sync_th, SLOT(start()));
    connect(db_sync_th, SIGNAL(started()), this, SLOT(dbSyncDowark()));
    connect(this, SIGNAL(requestDoWark(int, QPixmap, QString, int, double, QString)), sync_var, SLOT(doWarkSync(int, QPixmap, QString, int, double, QString)));
    connect(sync_var, SIGNAL(finishedSyTh()), db_sync_th, SLOT(quit()), Qt::DirectConnection);
    connect(sync_var, SIGNAL(insertToDb(int, QPixmap, QString, int, double, QString, int, QString, QString, QString, int, QString)), this, SLOT(callAddToDb(int, QPixmap, QString, int, double, QString, int, QString, QString, QString, int, QString)));


    sy_timer = new QTimer();
    connect(sy_timer, SIGNAL(timeout()), this, SLOT(syncChecker()));
    //    sy_timer->start(5000);// 5 second

    check_last_id = 0;
    getLastDBId();

    synnc_chek_T = new QThread();
    sync_ch = new sync_checker();
    sync_ch->moveToThread(synnc_chek_T);
    connect(sync_ch, SIGNAL(workRequestedChT()), synnc_chek_T, SLOT(start()));
    connect(synnc_chek_T, SIGNAL(started()), this, SLOT(syncChCallDoWark()));
    connect(this, SIGNAL(data_transfer_to_syncDowark(int, QString, QString, QString, double, int, int, int)), sync_ch, SLOT(doWarkSyncChe(int, QString, QString, QString, double, int, int, int)));
    connect(this, SIGNAL(data_transfer_to_syncDowark(int, QString, QString, QString, int, QString, int)), sync_ch, SLOT(doWarkSyncChe(int, QString, QString, QString, int, QString, int)));
    connect(sync_ch, SIGNAL(finishedSyChT()), synnc_chek_T, SLOT(quit()), Qt::DirectConnection);
    connect(sync_ch, SIGNAL(updateDb(int)), this, SLOT(updateFeedAddFace(int)));


    newSettings= new settingsDialog();
    connect(newSettings, SIGNAL(transferSuspectStateToMainWindow(bool)), this, SLOT(getSuspectCheckStateFromSettingsDialog(bool)));
    connect(newSettings, SIGNAL(checkFaceDetection(bool)), this, SLOT(face_detection_work(bool)));
    connect(newSettings, SIGNAL(checkLprDetection(bool)), this, SLOT(lpr_detection_work(bool)));
    //    connect(newSettings, SIGNAL(getSourceVecFromDs()), dsc, SLOT(getSourceVecInSettings()));
    connect(newSettings, SIGNAL(setDivisortoMain(std::vector<std::pair<int, double>>)), this, SLOT(getDivisorFromSettings(std::vector<std::pair<int, double> >)));

    pr = new ProgressBarLoading();
    //    pr->setProgressBarMaximumValue(100);
    //    pr->setProgressBarMinimumValue(0);
    pr->setMinMax(0, 100);
    connect(this, SIGNAL(setDifferSettings(int)), pr, SLOT(setDiffer(int)));
    connect(this, SIGNAL(valueProgChange(int)), pr, SLOT(progressOperation(int)));

    show_face = new ShowFace(this);
    //show_face->addFr(pic);

    //  connect(facesWindow, SIGNAL(emitPicDB_mw_signal(QPixmap)), configdb, SLOT(showFaceToConfigDB(QPixmap)));

    FRThreshold = 0.45;// default frthreshold value
    connect(newSettings, SIGNAL(fr_thresholed_value_settingdialog(float)), this ,SLOT(fr_thresholed_value(float)));

    /// API selection for lpr
    api_str_for_lpr = "tess_api";//default
    //    api_str_for_lpr = "google_api";
    connect(newSettings, SIGNAL(lpr_api_select_value_settingdialog(QString)), this ,SLOT(lpr_api_select_value(QString)));

    //int height = screenGeometry.height();
    // int width = screenGeometry.width();

    //    int x=0;//(width - w.width()) / 2.0;
    //    int y=-100;//(height - w.height()) / 2.0;
    //    facesWindow->setGeometry(x,y,600,1000);
    //    facesWindow->show();

    search = new SearchByGivenImage();
    //    connect(search, SIGNAL(goMainW(QString,QString)), this, SLOT(fromSearchByGI(QString,QString)));
    //    connect(warker, SIGNAL(fromWarker(QStringList)), this, SLOT(inMain(QStringList)));
    //    connect(this, SIGNAL(goSearchByGivenIm(QStringList)), search, SLOT(cathList(QStringList)));

    sbi = new SearchByImage();
    connect(sbi, SIGNAL(fromSearchByImg(QString)), this, SLOT(fromSearchByImgtoMain(QString)));
    connect(this, SIGNAL(goSBI(QStringList)), sbi, SLOT(fromMain_Wark(QStringList)));

    loadDetectedFace();// load detected face to descriptors
    suspect_state = true;//false silo

    //    Display* display = XOpenDisplay(NULL);

    //    XSynchronize(display, True);

    //    Window x11root = XDefaultRootWindow(display);

    //    int x = 500;
    //    int y = 500;
    //    unsigned int width = 721;
    //    unsigned int height = 461;

    //    unsigned int borderWidth = 0;
    //    long colorBlue = 0xff0000ff;

    //    Window x11w = XCreateSimpleWindow(display, x11root, x, y,
    //                                      width, height, borderWidth, 1 /*magic number*/, colorBlue);

    //    XReparentWindow(display, x11w, staticO->winId(), 310, 68);
    //    XMapWindow(display, x11w);

    uniq_face_window = new uniqueFaceWidget("strValue", this);
    connect(facesWindow, SIGNAL(unique_face_to_main_window(QPixmap, QString, int, int, int, double, int, QString, int)), this, SLOT(make_notification_for_unique_face(QPixmap, QString, int, int, int, double, int, QString, int)));
    //    connect(this, SIGNAL(unique_lp_to_main_window(QPixmap, QString, int, int, int, double, int, QString, int)), this, SLOT(make_notification_for_unique_face(QPixmap, QString, int, int, int, double, int, QString, int)));

    int y2 = ui->menuBar->geometry().y()+450;//426
    int x2= this->width()-1360;//1360
    //    //uniq_face_window->move(wid/4-8,menubar_height+4+hei/2);
    //    uniq_face_window->move(wid/4-8,menubar_height+4+hei/2);
    //    uniq_face_window->setFixedWidth((wid-(wid/4))+13);
    //    uniq_face_window->setFixedHeight(hei/3+45);

    //    uniq_face_window->move(wid/4-8,menubar_height+4+hei/2);
    uniq_face_window->move(wid/4+52,menubar_height+4+hei/2);
    //    uniq_face_window->setFixedWidth(wid/2+20);
    uniq_face_window->setFixedWidth(wid/2+270);
    uniq_face_window->setFixedHeight(hei/3+45);
    uniq_face_window->setVisible(false);

    frame = new QFrame(this);
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    frame->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowTransparentForInput | Qt::WindowDoesNotAcceptFocus | Qt::WindowStaysOnTopHint);
    frame->setObjectName("testframe");
    frame->setStyleSheet("#testframe {border: 8px solid green;}");
    frame->setWindowOpacity(0.5);
    //    frame->setAttribute(Qt::WA_TranslucentBackground);

    //    frame->setParent(this);
    blink_check = false;
    //blink_check_from_ui = false;
    blink_timer = new QTimer();
    connect(blink_timer, SIGNAL(timeout()), this, SLOT(blinkTimerSl()));
    //    blink_timer->start(1000);// 5 second

    frame_search_by_name = new QFrame(this);
    frame_search_by_name->setFrameStyle(QFrame::Box | QFrame::Plain);
    frame_search_by_name->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowTransparentForInput | Qt::WindowDoesNotAcceptFocus | Qt::WindowStaysOnTopHint);
    frame_search_by_name->setObjectName("testframeByNames");
    frame_search_by_name->setStyleSheet("#testframeByNames {border: 8px solid green;}");
    frame_search_by_name->setWindowOpacity(0.5);

    blink_check_by_name = false;
    blink_timer_search_by_name = new QTimer();
    connect(blink_timer_search_by_name, SIGNAL(timeout()), this, SLOT(blinkTimerSearchByName()));
    name_and_source.first = "";
    name_and_source.second = 0;

    delete_prev_date = new QTimer();
    connect(delete_prev_date, SIGNAL(timeout()), this, SLOT(deleteLastOneDayFromEightDays()));
    delete_prev_date->start(3600000);

    overThOb = new QThread();
    overThread = new OvercrowdThread();
    overThread->moveToThread(overThOb);

    connect(overThread, SIGNAL(requestedOverThStart()), overThOb, SLOT(start()));
    connect(overThOb, SIGNAL(started()), this, SLOT(overThan()));
    connect(this, SIGNAL(goOverThread(int)), overThread, SLOT(dowark(int)));
    connect(overThread, SIGNAL(valueFRChanged(QPixmap, int)), this, SLOT(addFR(QPixmap, int)));
    connect(overThread, SIGNAL(finishedOverTh()), overThOb, SLOT(quit()), Qt::DirectConnection);

    helpThOb = new QThread();
    helperThread = new HelperThread();
    helperThread->moveToThread(helpThOb);

    connect(helperThread, SIGNAL(requestedWorkan()), helpThOb, SLOT(start()));
    connect(helpThOb, SIGNAL(started()), this, SLOT(helperThan()));
    //    connect(helpThOb, SIGNAL(started()), helperThread, SLOT(dowark()));
    //    connect(this, SIGNAL(goHelperThread(QPixmap, QPixmap, QString, int, QString)), helperThread, SLOT(dowark(QPixmap, QPixmap, QString, int, QString)));
    connect(this, SIGNAL(goHelperThread(QPixmap, int, int)), helperThread, SLOT(dowark(QPixmap, int, int)));
    //connect(this, SIGNAL(tester()), helperThread, SLOT(dowark()));
    connect(helperThread, SIGNAL(valueFRChanged(QPixmap, QPixmap, QString, int, QString)), this, SLOT(addFR(QPixmap, QPixmap, QString, int, QString)));
    connect(helperThread, SIGNAL(valueFRChanged(QPixmap, int)), this, SLOT(addFR(QPixmap, int)));
    //    connect(helperThread, SIGNAL(valueFRChangedForOvercrowded(int)), this, SLOT(addFRForOvercrowd(int)));

    connect(helperThread, SIGNAL(finishedTh()), helpThOb, SLOT(quit()), Qt::DirectConnection);
    //connect(this, SIGNAL(finishedTh()), helpThOb, SLOT(quit()), Qt::DirectConnection);
    testThOb = new QThread();
    testerThread = new TesterThread();
    testerThread->moveToThread(testThOb);
    connect(testerThread, SIGNAL(requestedWork()), testThOb, SLOT(start()));
    connect(testThOb, SIGNAL(started()), testerThread, SLOT(dowark()));
    connect(testerThread, SIGNAL(finished()), testThOb, SLOT(quit()), Qt::DirectConnection);

    //=================
    recordDeleteTimer = new QTimer(this);
    connect(recordDeleteTimer, SIGNAL(timeout()), this, SLOT(cleanSpecificRecordVideo()));
    recordDeleteTimer->start(18000000);// check after 5 minutes

    connect(newSettings, SIGNAL(smartRecordDayCount(int, QString)), this, SLOT(deleteSmartRecordVideoAfterHowManyDays(int, QString)));

    onvif_h = new MainWindow_onvif();

}

void MainWindow::deleteSmartRecordVideoAfterHowManyDays(int days, QString smart_dir)
{
    how_may_days = days;
    smart_record_video_save_directory = smart_dir;
    qDebug()<<"how_may_days: "<<how_may_days<<" smart_record_video_save_directory: "<<smart_record_video_save_directory;

    //    cleanSpecificRecordVideo();//go to this method
}

void MainWindow::getDivisorFromSettings(std::vector<std::pair<int, double> > div)
{
    emit sourceDivisorPassToDS(div);
}

void MainWindow::face_detection_work(bool state)
{
    face_detection_check_or_uncheck = state;
}

void MainWindow::lpr_detection_work(bool state)
{
    lpr_detection_check_or_uncheck = state;
}

void MainWindow::helperThan()
{
    //    emit goHelperThread(helperThread->firstpic, helperThread->thirdpic, helperThread->mask, helperThread->index, helperThread->color);
    emit goHelperThread(helperThread->firstpic, helperThread->index, helperThread->overcrowed_val);

    //    emit tester();
}

void MainWindow::overThan()
{
    emit goOverThread(overThread->overcroweded_vl);
}
void MainWindow::dowark()
{
    //    emit finishedTh();

    // emit tester();
}

void MainWindow::addFR(QPixmap person, QPixmap face, QString mask, int source, QString clor)
{
    qDebug() << " aisa porsi .................... "<< mask;
    //    //    dataInsertIntoDb(person, face, source, mask);
    //    if(QString::compare(mask, "clear") != 0){
    //        tilerdisplayWindow->addFR(face, mask, source);

    //        //qDebug() << "after call addFR@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ "<< mask;
    //        //        QString face_path = "./captures/mask_faces";
    //        //        QString obliq = "/";
    //        //        QString date = QDate::currentDate().toString("dd.MM.yyyy");
    //        //        QString img_path = face_path+obliq+date+obliq;
    //        //        QString at = "<at>";
    //        //        QString image_name = img_path+mask+at+QTime::currentTime().toString();

    //        //        QDir myDir;
    //        //        if(!myDir.exists(date)){
    //        //            myDir.mkpath(img_path);
    //        //            person.save(image_name+"person.png");
    //        //            face.save(image_name+"face.png");
    //        //        }
    //    }
    //    else { // if(QString::compare(mask, "masked") == 0)
    //        tilerdisplayWindow->only_uniqueFace_show_inTiles(face, mask, source);

    //        //        QString face_path = "./captures/unmask_faces";
    //        //        QString obliq = "/";
    //        //        QString date = QDate::currentDate().toString("dd.MM.yyyy");
    //        //        QString img_path = face_path+obliq+date+obliq;
    //        //        QString at = "<at>";
    //        //        QString image_name = img_path+mask+at+QTime::currentTime().toString();
    //        //        QDir myDir;
    //        //        if(!myDir.exists(date)){
    //        //            myDir.mkpath(img_path);
    //        //            person.save(image_name+"person.png");
    //        //            face.save(image_name+"face.png");
    //        //        }
    //    }
}

void MainWindow::addFR(QPixmap per, int indx)
{
    Notification *newNoti= new Notification(per.scaledToHeight(140), "abc", "", QString::number(indx), per.scaledToHeight(140), "", "");
    //    facesWindow->uniqueLicencePlateShowInTiles(pic, "abc", indx, color);
    lpr_emailController->addNotLPR(newNoti);

    // dataInsertIntoDbPerson(per, indx);
}

void MainWindow::addFRForOvercrowd(int oc)
{
    //    Notification *newNoti= new Notification(per.scaledToHeight(140), "abc", "", QString::number(indx), per.scaledToHeight(140), "", "");
    //    //    facesWindow->uniqueLicencePlateShowInTiles(pic, "abc", indx, color);
    //    lpr_emailController->addNotLPR(newNoti);
}

void MainWindow::addFR(QPixmap main_pic_per, QPixmap fce, QString face_id, int ind, double con, dlib::matrix<float,(long)0,(long)1> match_fce, int rec_or_not)
{
    qDebug() << "addfr test johurul=== ";
    //tilerdisplayWindow->only_uniqueFace_show_inTiles(fce,face_id,ind);

    facesWindow->addUniqueFace(main_pic_per, fce, face_id, ind, match_fce, con, /*fpsValue*/2, rec_or_not, /*gender*/"male", /*age*/25);
    //    dataInsertIntoDbFace(fce, ind, face_id);
}

void MainWindow::addFR_2(QPixmap pic, QString name, int cam, double confidence)
{
    qDebug() << "addfr_2 call ";

    // tilerdisplayWindow->only_uniqueFace_show_inTiles(pic,name,cam);

    QString camer = QString::number(cam);

    Not *newNot= new Not(pic, name, camer, confidence, this);
    newNot->setFixedWidth((this->wid) - (this->wid/4+this->wid/2)+10);
    nots->addNot(newNot);
    nots->setVisible(true);

    dataInsertIntoDbFace(pic, cam, name);
}

void MainWindow::addNotToBarLP(Notification *noti)
{
    qDebug()<<"carnotbar";//<<" carType = "<<noti->name;
    if(noti->name.mid(0,1) != "!"){
        try{
            LpSingleWidg *newNot = new LpSingleWidg(noti->m_pic, noti->pic, noti->name, noti->cam, "", this);
            newNot->setFixedWidth((this->wid) - (this->wid/4+this->wid/2)+30);
            //    LPNotif *newNot= new LPNotif(noti->pic, noti->name, noti->cam, "", this);
            lpnots->addNotLP(newNot);
            lpnots->setVisible(true);
            delete noti;
        }catch(...){

        }
    }
    notOn= true;

    /// for lpr
    //    QString str = noti->name;
    int recog;
    //    if(str.mid(0,1) == "!")
    //    {
    recog = 0;
    //        noti->name.remove(0,1);
    //            faceUniq *u_newNot= new faceUniq(noti->pic, noti->name, 0.0, recog, this);
    //            uniq_face_window->u_addNot(u_newNot);// uniquefacewidget class instance of uniq_face_window

    //    }
    //    else{
    //        recog = 1;
    //    }


}

void MainWindow::deleteLastOneDayFromEightDays()
{
    qDebug()<<"deleteLastOneDayFromEightDays timer call";

    if(connectionDB()){
        //        QString qDeleteLastdate = "SELECT DISTINCT STRFTIME('%Y-%m-%d', date_time) from PersonFace ORDER by date_time DESC;";
        QString qDeleteLastdate = "SELECT DISTINCT STRFTIME('%Y-%m-%d', date_time) from detected_LPR ORDER by date_time DESC;";

        QSqlQuery quDel;
        if(quDel.exec(qDeleteLastdate)){
            qDebug() << "Total number of rows affected = "<< quDel.size();
            int tracking_to_row = 0;
            while(quDel.next()){
                ++tracking_to_row;
                if(tracking_to_row > 7){
                    //                    //qDebug() << "Output = " << quDel.value(0).toString();
                    //                    QString _del = "delete from PersonFace where STRFTIME('%Y-%m-%d', date_time) = ?;";
                    QString _del = "delete from detected_LPR where STRFTIME('%Y-%m-%d', date_time) = ?;";

                    QSqlQuery q_del;
                    q_del.prepare(_del);
                    q_del.addBindValue(quDel.value(0).toString());
                    if(q_del.exec()){
                        //                        //qDebug() << "Delete -> " << quDel.value(0).toString() << " " << quDel.numRowsAffected();
                    }/*else{
                        ////qDebug() << "Output = " << quDel.value(0).toString();
                        ////qDebug() << q_del.lastQuery();
                        ////qDebug() << q_del.lastError();
                    }*/

                }
            }
        }
    }
}

void MainWindow::callDoWorkFromMain()
{
    qDebug() << "callDoWorkFromMain call hosse ............................................";
    //    if(!worker->main_pi.empty()  && !worker->pi.empty()){
    cv::imwrite("/home/sigmind/Pictures/bla/main.jpeg" , worker->main_pi);
    emit requestUpdateLPR(worker->main_pi ,worker->pi, worker->s, worker->ind, worker->obj_color, api_str_for_lpr);
    //    }
}
void MainWindow::blinkTimerSl(){
    QString object = ui->objectCombo->currentText();
    //    QString object = myStyles::objects.at(ui->objectCombo->currentIndex());
    //    int color = myStyles::colorValues.at(ui->colorCombo->currentIndex()-1);
    ////qDebug() << "Object & Color = " << object << " " << color;
    if(left_clicked_full_disp_blink == false){
        if(source_and_object.second == 0){
            if(QString::compare("Face", object) == 0){
                if(blink_check == false){
                    blink_check = true;
                }else{
                    blink_check = false;
                }
                if(blink_check == true){
                    frame->setGeometry(rects[source_and_object.first].left, rects[source_and_object.first].top, rects[source_and_object.first].right, rects[source_and_object.first].bot);    // Just some fixed values to test
                    frame->show();
                }else{
                    frame->close();
                }
            }
        }
    }else if(left_clicked_full_disp_blink == true){
        int x = wid/4+2;
        int y = menubar_height+33;
        int w = wid/2;
        int h = hei/2;
        //qDebug() << x << " out " << y << " " << w << " " << h;
        if(source_and_object.second == 0){
            if(QString::compare("Face", object) == 0){
                if(blink_check == false){
                    blink_check = true;
                }else{
                    blink_check = false;
                }
                if(blink_check == true){
                    frame->setGeometry(x, y, w, h);    // Just some fixed values to test
                    frame->show();
                }else{
                    frame->close();
                }
            }
        }
    }

}

void MainWindow::blinkTimerSearchByName()
{
    QString tempF = ui->faceLineEdit->text();
    if(QString::compare(tempF, name_and_source.first) == 0){
        if(blink_check_by_name == false){
            blink_check_by_name = true;
        }else{
            blink_check_by_name = false;
        }
        if(blink_check_by_name == true){
            frame_search_by_name->setGeometry(rects[source_and_object.first].left, rects[source_and_object.first].top, rects[source_and_object.first].right, rects[source_and_object.first].bot);    // Just some fixed values to test
            frame_search_by_name->show();
        }else{
            frame_search_by_name->close();
        }
    }


}


//void MainWindow::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setPen(Qt::darkGreen);
//    painter.drawRect(512, 68,683, 220);

////    painter.setPen(Qt::darkGray);
////    painter.drawLine(512, 68, 683, 68);
//}
MainWindow::~MainWindow()
{
    emit finishedDS();
    //worker->abort();
    // thread->wait();
    // //qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    // delete thread;
    // delete worker;

    // delete dsc;

    //  warker->abort();
    //FRthread->wait();
    ////qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    // delete FRthread;
    // delete warker;
    // delete newFeed2;
    // delete newFeed3;
    //delete newFeed4;
    //deepstream_thread->abort();

    delete deepstream_thread;

    //    g_print ("Returned, stopping playback\n");
    //    gst_element_set_state (pipeline, GST_STATE_NULL);
    //    g_print ("Deleting pipeline\n");
    //    gst_object_unref (GST_OBJECT (pipeline));
    //    g_source_remove (bus_watch_id);
    //    g_main_loop_unref (loop);
    delete sbi;
    delete search;
    delete frame;
    delete frame_search_by_name;
    delete ui;
}

void MainWindow::centerAndResize() {
    // get the dimension available on this screen
    QSize availableSize = qApp->desktop()->availableGeometry().size();
    int width = availableSize.width();
    int height = availableSize.height();
    ////qDebug() << "Available dimensions " << width << "x" << height;
    width *= 0.5; // 90% of the screen size
    height *= 0.9; // 90% of the screen size
    ////qDebug() << "Computed dimensions " << width << "x" << height;
    QSize newSize( width, height );
    this->setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    newSize,
                    qApp->desktop()->availableGeometry()
                    )
                );
}

void MainWindow::setNegative_left_clicked_full_disp_blink()
{
    staticO->left_clicked_full_disp_blink = false;
}

void MainWindow::setPositive_left_clicked_full_disp_blink()
{
    staticO->left_clicked_full_disp_blink = true;
}
QString MainWindow::singleCharLprBangToEng(QString data){
    ////qDebug() << "singleCharLprBangToEng(QString data){ = " << data;
    if(data.isEmpty()){
        return "";
    }
    QMap<QString, QString> map;
    //    map.insert("\u0985", "A");
    //    map.insert("\u0986", "AA");
    //    map.insert("\u0987", "I");
    //    map.insert("\u0988", "II");
    //    map.insert("\u0989", "U");
    //    map.insert("\u0990", "UU");
    //    map.insert("\u098F", "E");
    //    map.insert("\u0990", "AI");
    //    map.insert("\u0993", "O");
    //    map.insert("\u0994", "AU");
    //    map.insert("\u09E6", "0");
    //    map.insert("\u09E7", "1");
    //    map.insert("\u09E8", "2");
    //    map.insert("\u09E9", "3");
    //    map.insert("\u09EA", "4");
    //    map.insert("\u09EB", "5");
    //    map.insert("\u09EC", "6");
    //    map.insert("\u09ED", "7");
    //    map.insert("\u09EE", "8");
    //    map.insert("\u09EF", "9");
    //    map.insert("\u09BE", "AA");
    //    map.insert("\u09BF", "I");
    //    map.insert("\u09C0", "II");
    //    map.insert("\u09C1", "U");
    //    map.insert("\u09C2", "UU");
    //    map.insert("\u09C3", "R");
    //    map.insert("\u09C4", "RR");
    //    map.insert("\u09C7", "E");
    //    map.insert("\u09C8", "AI");
    //    map.insert("\u09CB", "O");
    //    map.insert("\u09CC", "AU");
    map.insert("\u0995","KA");
    map.insert("\u0996","KHA");
    map.insert("\u0997","GA");
    map.insert("\u0998","GHA");
    map.insert("\u0999","NGA");
    map.insert("\u099A","CA");
    map.insert("\u099B","CHA");
    map.insert("\u099C","JA");
    map.insert("\u099D","JHA");
    map.insert("\u099E","NYA");
    map.insert("\u099F","TTA");
    map.insert("\u09A0","TTHA");
    map.insert("\u09A1","DDA");
    map.insert("\u09A2","DDHA");
    map.insert("\u09A3","NNA");
    map.insert("\u09A4","TA");
    map.insert("\u09A5","THA");
    map.insert("\u09A6","DA");
    map.insert("\u09A7","DHA");
    map.insert("\u09A8","NA");
    map.insert("\u09AA","PA");
    map.insert("\u09AB","PHA");
    map.insert("\u09AC","BA");
    map.insert("\u09AD","BHA");
    map.insert("\u09AE","MA");
    map.insert("\u09AF","YA");
    map.insert("\u09B0","RA");
    map.insert("\u09B2","LA");
    map.insert("\u09B6","SHA");
    map.insert("\u09B7","SSA");
    map.insert("\u09B8","SA");
    map.insert("\u09B9","HA");

    QMapIterator<QString, QString> it_map(map);
    int flg = 0;
    while(it_map.hasNext()){
        it_map.next();
        if(it_map.key() == data.mid(data.length()-1, 1)){
            //qDebug() << "char = " <<it_map.value();
            flg = 1;
            return it_map.value();
            break;
        }
    }
    if(flg == 0){
        ////qDebug() <<"First l = "<< data.length();
        QString dat = data.mid(0, data.length()-1);
        ////qDebug() <<"Second l = "<< dat.length();

        singleCharLprBangToEng(dat);
    }

    return "";

}

void MainWindow::detectedLpToDb(QString num_plate, QString date_time, QString color, QString parent_img_path, QString child_img_path)
{
    qDebug()<<"detectedLpToDb call";

    QSqlQuery qLp, qLp_insert;
    if (qLp.exec(
                "CREATE TABLE detected_LPR ( "
                "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                "number_plate TEXT, "
                "date_time DATETIME, "
                "color varchar(50), "
                "parentImgPath text, "
                "childImgPath text "
                "); "
                )){
        qDebug()<< "Table created lpr successfully!";
    }else{
        qDebug() << "Lp table not created??? "<<qLp.lastError();
    }

    qLp_insert.prepare("insert into detected_LPR "
                       "( number_plate, date_time, color, parentImgPath, childImgPath) "
                       "values (?, ?, ?, ?, ?) ; ");
    qLp_insert.addBindValue(num_plate);
    qLp_insert.addBindValue(date_time);
    qLp_insert.addBindValue(color);
    qLp_insert.addBindValue(parent_img_path);
    qLp_insert.addBindValue(child_img_path);
    qLp_insert.exec();
}

QString MainWindow::lprBanglaToEnglishTransform(QString data)
{
    qDebug()<<"original data "<< data;
    QRegExp rx("(\\ |\\-)");

    //    qDebug()<<"after split data str : "<<(data.split(rx))<<" "<<(data.split(rx))[0]
    //           <<" "<<(data.split(rx))[1];

    data = (data.split(rx))[0];

    qDebug()<<"lprBanglaToEnglishTransform call "<<data;

    QMap<QString, QString> map;
    map.insert("\u0985", "A");
    map.insert("\u0986", "AA");
    map.insert("\u0987", "I");
    map.insert("\u0988", "II");
    map.insert("\u0989", "U");
    map.insert("\u0990", "UU");
    map.insert("\u098F", "E");
    map.insert("\u0990", "AI");
    map.insert("\u0993", "O");
    map.insert("\u0994", "AU");
    map.insert("\u09E6", "0");
    map.insert("\u09E7", "1");
    map.insert("\u09E8", "2");
    map.insert("\u09E9", "3");
    map.insert("\u09EA", "4");
    map.insert("\u09EB", "5");
    map.insert("\u09EC", "6");
    map.insert("\u09ED", "7");
    map.insert("\u09EE", "8");
    map.insert("\u09EF", "9");
    map.insert("\u09BE", "AA");
    map.insert("\u09BF", "I");
    map.insert("\u09C0", "II");
    map.insert("\u09C1", "U");
    map.insert("\u09C2", "UU");
    map.insert("\u09C3", "R");
    map.insert("\u09C4", "RR");
    map.insert("\u09C7", "E");
    map.insert("\u09C8", "AI");
    map.insert("\u09CB", "O");
    map.insert("\u09CC", "AU");
    map.insert("\u0995","KA");
    map.insert("\u0996","KHA");
    map.insert("\u0997","GA");
    map.insert("\u0998","GHA");
    map.insert("\u0999","NGA");
    map.insert("\u099A","CA");
    map.insert("\u099B","CHA");
    map.insert("\u099C","JA");
    map.insert("\u099D","JHA");
    map.insert("\u099E","NYA");
    map.insert("\u099F","TTA");
    map.insert("\u09A0","TTHA");
    map.insert("\u09A1","DDA");
    map.insert("\u09A2","DDHA");
    map.insert("\u09A3","NNA");
    map.insert("\u09A4","TA");
    map.insert("\u09A5","THA");
    map.insert("\u09A6","DA");
    map.insert("\u09A7","DHA");
    map.insert("\u09A8","NA");
    map.insert("\u09AA","PA");
    map.insert("\u09AB","PHA");
    map.insert("\u09AC","BA");
    map.insert("\u09AD","BHA");
    map.insert("\u09AE","MA");
    map.insert("\u09AF","YA");
    map.insert("\u09B0","RA");
    map.insert("\u09B2","LA");
    map.insert("\u09B6","SHA");
    map.insert("\u09B7","SSA");
    map.insert("\u09B8","SA");
    map.insert("\u09B9","HA");

    QMap<QString, QString> map_akar_ukar;

    map_akar_ukar.insert("\u09BE", "AA");
    map_akar_ukar.insert("\u09BF", "I");
    map_akar_ukar.insert("\u09C0", "II");
    map_akar_ukar.insert("\u09C1", "U");
    map_akar_ukar.insert("\u09C2", "UU");
    map_akar_ukar.insert("\u09C3", "R");
    map_akar_ukar.insert("\u09C4", "RR");
    map_akar_ukar.insert("\u09C7", "E");
    map_akar_ukar.insert("\u09C8", "AI");
    map_akar_ukar.insert("\u09CB", "O");
    map_akar_ukar.insert("\u09CC", "AU");//ano
    map_akar_ukar.insert("\u0980", "AU");
    map_akar_ukar.insert("\u0981", "AU");
    map_akar_ukar.insert("\u0982", "AU");
    map_akar_ukar.insert("\u0983", "AU");
    map_akar_ukar.insert("\u09F0", "AU");
    map_akar_ukar.insert("\u09F1", "AU");
    map_akar_ukar.insert("\u09F2", "AU");
    map_akar_ukar.insert("\u09F3", "AU");
    map_akar_ukar.insert("\u09F4", "AU");
    map_akar_ukar.insert("\u09F5", "AU");
    map_akar_ukar.insert("\u09F6", "AU");
    map_akar_ukar.insert("\u09F7", "AU");
    map_akar_ukar.insert("\u09F8", "AU");
    map_akar_ukar.insert("\u09F9", "AU");
    map_akar_ukar.insert("\u09FA", "AU");
    map_akar_ukar.insert("\u09FB", "AU");
    map_akar_ukar.insert("\u09FC", "AU");
    map_akar_ukar.insert("\u09FD", "AU");
    map_akar_ukar.insert("\u09FE", "AU");
    map_akar_ukar.insert("\u09E0", "AU");
    map_akar_ukar.insert("\u09E1", "AU");
    map_akar_ukar.insert("\u09D7", "AU");
    map_akar_ukar.insert("\u09BC", "AU");
    map_akar_ukar.insert("\u09BD", "AU");
    map_akar_ukar.insert("\u09CD", "AU");
    map_akar_ukar.insert("\u09CE", "AU");

    QMap<QString, QString> final_map_str;
    //    // barishal division
    //    final_map_str.insert("BARAGANA", "Barguna");
    //    final_map_str.insert("BARASHALA", "Barishal");
    //    final_map_str.insert("BHALAMA", "Bhola");
    //    final_map_str.insert("JHALAKHATTA", "Jhalokati");
    //    final_map_str.insert("PATTAKHA", "Patuakhali");
    //    final_map_str.insert("PARAJAPA", "Pirojpur");

    //    // chattogram division
    //    final_map_str.insert("BANADARA", "Bandarban");
    //    final_map_str.insert("CADAPA", "Chandpur");
    //    final_map_str.insert("CATTATTAGA", "Chattogram");
    //    final_map_str.insert("KAMALA", "Cumilla");
    //    final_map_str.insert("KAKASABA", "Cox's Bazar");
    //    final_map_str.insert("PHANAMA", "Feni");
    //    final_map_str.insert("KHAGADDA", "Khagrachhari");
    //    final_map_str.insert("LAKASSAMA", "Lakshmipur");
    //    final_map_str.insert("NAYAKHA", "Noakhali");
    //    final_map_str.insert("RANGAGA", "Rangamati");

    //    // Dhaka Division
    //    final_map_str.insert("DDHAKA", "Dhaka");
    //    final_map_str.insert("PHARADAPA", "Faridpur");
    //    final_map_str.insert("GAJAPA", "Gazipur");
    //    final_map_str.insert("GAPALAGA", "Gopalganj");
    //    final_map_str.insert("KASHARAGA", "Kishoreganj");
    //    final_map_str.insert("MADARA", "Madaripur");
    //    final_map_str.insert("MANAKAGA", "Manikganj");
    //    final_map_str.insert("MANASA", "Munshiganj");
    //    final_map_str.insert("NARAYA", "Narayanganj");
    //    final_map_str.insert("NARASADA", "Narsingdi");
    //    final_map_str.insert("RAJABADDA", "Rajbari");
    //    final_map_str.insert("SHARAYATA", "Shariatpur");
    //    final_map_str.insert("TTANGAGA", "Tangail");

    //    // KHULNA DIVISION
    //    final_map_str.insert("BAGARAHA", "Bagerhat");
    //    final_map_str.insert("CAYADDA", "Chuadanga");
    //    final_map_str.insert("YASHARAMA", "Jashore");
    //    final_map_str.insert("JHANAIDA", "Jhenaidah");
    //    final_map_str.insert("KHALANA", "Khulna");
    //    final_map_str.insert("KASSATTA", "Kushtia");
    //    final_map_str.insert("MAGARA", "Magura");
    //    final_map_str.insert("MAHARAPA", "Meherpur");
    //    final_map_str.insert("NADDAILA", "Narail");
    //    final_map_str.insert("SATAKASSA", "Satkhira");

    //    // MYMENSINGH DEVISION
    //    final_map_str.insert("JAMALAPA", "Jamalpur");
    //    final_map_str.insert("MAYAMANASA", "Mymensingh");
    //    final_map_str.insert("NATARAKA", "Netrokona");
    //    final_map_str.insert("SHARAPARA", "Sherpur");

    //    // RAJSHAHI DEVISION
    //    final_map_str.insert("BAGADDA", "Bogura");
    //    final_map_str.insert("JAYAPARA", "Joypurhat");
    //    final_map_str.insert("NAOGA", "Naogaon");
    //    final_map_str.insert("NATTARA", "Natore");
    //    final_map_str.insert("CAPAI", "Chapainawabganj");
    //    final_map_str.insert("PABANA", "Pabna");
    //    final_map_str.insert("RAJASHAHA", "Rajshahi");
    //    final_map_str.insert("SARAJAGA", "Sirajganj");

    //    // RANGPUR DIVISION
    //    final_map_str.insert("DANAJAPA", "Dinajpur");
    //    final_map_str.insert("GAIBANA", "Gaibandha");
    //    final_map_str.insert("KADDAGA", "Kurigram");
    //    final_map_str.insert("LALAMANA", "Lalmonirhat");
    //    final_map_str.insert("NALAPHAMA", "Nilphamari");
    //    final_map_str.insert("PANYACAGADDA", "Panchagarh");
    //    final_map_str.insert("RAPARA", "Rangpur");
    //    final_map_str.insert("TTHAKARAGA", "Thakurgaon");

    //    //SYLHET DEVISION
    //    final_map_str.insert("HABAGANYA", "Habiganj");
    //    final_map_str.insert("MALABHABA", "Moulvibazar");
    //    final_map_str.insert("SANAMAGA", "Sunamganj");
    //    final_map_str.insert("SALATTA", "Sylhet");

    /// recent added by johurul
    // barishal division
    final_map_str.insert("BARAGANA", "Barguna");
    final_map_str.insert("BARASHALA", "Barishal");
    final_map_str.insert("BHALA", "Bhola");
    final_map_str.insert("JHALAKATTHA", "Jhalokati");
    final_map_str.insert("PATTAKHALA", "Patuakhali");
    final_map_str.insert("PARAJAPARA", "Pirojpur");

    // chattogram division
    final_map_str.insert("BANADARABANA", "Bandarban");
    final_map_str.insert("CADAPARA", "Chandpur");
    final_map_str.insert("CATTATTAGARAMA", "Chattogram");
    final_map_str.insert("KAMALALA", "Cumilla");
    final_map_str.insert("KAKASABAJARA", "Cox's Bazar");
    final_map_str.insert("PHANA", "Feni");
    final_map_str.insert("KHAGACHA", "Khagrachhari");
    final_map_str.insert("LAKASSAMAPARA", "Lakshmipur");
    final_map_str.insert("NAYAKHALA", "Noakhali");
    final_map_str.insert("RANGAGAMATTA", "Rangamati");

    // Dhaka Division
    final_map_str.insert("DDHAKA", "Dhaka");
    final_map_str.insert("PHARADAPARA", "Faridpur");
    final_map_str.insert("GAJAPARA", "Gazipur");
    final_map_str.insert("GAPALAGANYAJA", "Gopalganj");
    final_map_str.insert("KASHARAGANYAJA", "Kishoreganj");
    final_map_str.insert("MADARAPARA", "Madaripur");
    final_map_str.insert("MANAKAGANYAJA", "Manikganj");
    final_map_str.insert("MANASAGANYAJA", "Munshiganj");
    final_map_str.insert("NARAYA", "Narayanganj");
    final_map_str.insert("NARASADA", "Narsingdi");
    final_map_str.insert("RAJABADDA", "Rajbari");
    final_map_str.insert("SHARAYATAPARA", "Shariatpur");
    final_map_str.insert("TTANGAGAILA", "Tangail");

    // KHULNA DIVISION
    final_map_str.insert("BAGARAHATTA", "Bagerhat");
    final_map_str.insert("CAYADDA", "Chuadanga");
    final_map_str.insert("YASHARA", "Jashore");
    final_map_str.insert("JHANAIDAHA", "Jhenaidah");
    final_map_str.insert("KHALANA", "Khulna");
    final_map_str.insert("KASSATTA", "Kushtia");
    final_map_str.insert("MAGARA", "Magura");
    final_map_str.insert("MAHARAPARA", "Meherpur");
    final_map_str.insert("NADDAILA", "Narail");
    final_map_str.insert("SATAKASSARA", "Satkhira");

    // MYMENSINGH DEVISION
    final_map_str.insert("JAMALAPARA", "Jamalpur");
    final_map_str.insert("MAYAMANASA", "Mymensingh");
    final_map_str.insert("NATARAKANNA", "Netrokona");
    final_map_str.insert("SHARAPARA", "Sherpur");

    // RAJSHAHI DEVISION
    final_map_str.insert("BAGADDA", "Bogura");
    final_map_str.insert("JAYAPARA", "Joypurhat");
    final_map_str.insert("NAOGA", "Naogaon");
    final_map_str.insert("NATTARA", "Natore");
    final_map_str.insert("CAPAINABABAGANYAJA", "Chapainawabganj");
    final_map_str.insert("PABANA", "Pabna");
    final_map_str.insert("RAJASHAHA", "Rajshahi");
    final_map_str.insert("SARAJAGANYAJA", "Sirajganj");

    // RANGPUR DIVISION
    final_map_str.insert("DANAJAPARA", "Dinajpur");
    final_map_str.insert("GAIBANADHA", "Gaibandha");
    final_map_str.insert("KADDAGA", "Kurigram");
    final_map_str.insert("LALAMANARAHATTA", "Lalmonirhat");
    final_map_str.insert("NALAPHAMARA", "Nilphamari");
    final_map_str.insert("PANYACAGADDA", "Panchagarh");
    final_map_str.insert("RAPARA", "Rangpur");
    final_map_str.insert("TTHAKARAGAO", "Thakurgaon");

    //SYLHET DEVISION
    final_map_str.insert("HABAGANYAJA", "Habiganj");
    final_map_str.insert("MALABHABAJARA", "Moulvibazar");
    final_map_str.insert("SANAMAGANYAJA", "Sunamganj");
    final_map_str.insert("SALATTA", "Sylhet");

    //QString data = "মানিকগঞ্জ মেট্রো ট";
    QByteArray string = data.toUtf8();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString encodedString = codec->toUnicode(string);
    int length_of_encodedString = encodedString.length();
    qDebug() << "length - " << length_of_encodedString << " and encode_str : " << encodedString;



    QList<QString> res;

    //    qDebug()<<"scrap district str : "<<encodedString.mid(0, 6);

    //    for(int i = 0; i < encodedString.mid(0, 6).length(); i++){
    for(int i = 0; i < encodedString.length(); i++){
        QMapIterator<QString, QString> it_map_akar_ukar(map_akar_ukar);
        int flg = 0;
        while(it_map_akar_ukar.hasNext()){
            it_map_akar_ukar.next();
            if(encodedString[i] == it_map_akar_ukar.key()){
                flg = 1;
                continue;
            }
        }
        if(flg == 1){
            continue;
        }else{
            QMapIterator<QString, QString> it_map(map);
            while(it_map.hasNext()){
                it_map.next();
                if(it_map.key() == encodedString[i]){
                    ////qDebug() << "char = " <<it_map.value();
                    res.push_back(it_map.value());
                    break;
                }
            }
            ////qDebug() << "Char - > " << encodedString[i];
            //res.push_back(codec->toUnicode(encodedString[i]));
        }
    }
    QString res1;
    for(int i = 0; i < res.length(); i++){
        res1+=res[i];
    }
    qDebug() << "Res1 = " << res1;
    QMapIterator<QString, QString> it_map(final_map_str);
    while(it_map.hasNext()){
        it_map.next();
        if(it_map.key() == res1 || it_map.key().mid(0, 5) == res1.mid(0, 5)
                || it_map.key().contains(res1) == true || res1.contains(it_map.key())){
            //            qDebug() << "return district name = " << it_map.value();
            if(res1 == "" || res1.size() <= 2){
                qDebug() << "return original str = "<<data<<" "<<res1;
                data = "Dhaka-";
                return data;
            }else if(res1 != ""){
                qDebug() << "return district name = " << it_map.value();
                return it_map.value();
            }
            else{
                qDebug() << "return default lpr text "<<data;
                data = "Dhaka-";
                return data;
            }
            break;
        }
    }
    data = "Dhaka-"+data;
    return data;
}

void MainWindow::dispInMainWind()
{
    //Display* display = dsc->disToMain;

    Window x11w = dsc->singleWin;
    /// display into mainwindow using qt
    XReparentWindow(display, x11w, staticO->winId(), ((staticO->wid/4)+52), staticO->menubar_height+8);
    XMapWindow(display, x11w);


    //    Window x11root1 = XRootWindow(display, 0);
    //    int x = 0;
    //    int y = 0;
    //    unsigned int width = 300;
    //    unsigned int height = 300;

    //    unsigned int borderWidth = 0;
    //    long colorBlue = 0xff0000ff;

    //    Window x11w1 = XCreateSimpleWindow(display, x11root1, x, y,
    //                                       width, height, borderWidth, 1 /*magic number*/, colorBlue);


    //    XReparentWindow(display, x11w1, x11w, (staticO->wid/4)+100, staticO->menubar_height+8);
    //    XMapWindow(display, x11w1);

    //    int screen;
    //    screen  = XDefaultScreen(display);
    //    XGCValues gr_values;
    //    gr_values.function =   GXcopy;
    //    gr_values.plane_mask = AllPlanes;
    //    gr_values.foreground = BlackPixel(display,screen);
    //    gr_values.background = WhitePixel(display,screen);
    //    GC gr_context;
    //    gr_context=XCreateGC(display,x11w,
    //                         GCFunction | GCPlaneMask | GCForeground | GCBackground,
    //                         &gr_values);
    //    XEvent event;
    //    while(1){
    //        XNextEvent(display,&event);

    //        switch(event.type){
    //        case Expose:
    //            XDrawLine(display,x11w1,gr_context,0,0, 100, 100);
    //            //XDrawString(display,x11w,gr_context,100,100,"hello",5);
    //            break;
    //        case KeyPress:
    //            XCloseDisplay(display);
    //            exit(0);

    //        }
    //    }


    //    XReparentWindow(display, x11w, staticO->winId(), (0), staticO->menubar_height+8);
    //    XMapWindow(display, x11w1);
}

void MainWindow::dispInMainWind2()
{
    display = dsc->disToMain;

    XSynchronize(display, True);
}

int MainWindow::getDispWidth()
{
    return staticO->wid;
}

int MainWindow::getDispHeight()
{
    return staticO->hei;
}
//void MainWindow::getDisFromDs(Display*){

//}
void MainWindow::batchDirMain(QString dir_path)
{
    qDebug() << "batchDirMain";
    //emit batchDirFromMain(dir_path);
    //    warker->finishTh();
    warker->batchEnrollment(dir_path);
}
void MainWindow::fromBatchEnr(QString name, QString path)
{
    emit valueProgChange(1);
    qDebug() << "Name = " << name << " " << path;
    addToAddFace(name, path);
}

void MainWindow::nlBatchNotify(QString name)
{
    //    QMessageBox msgBox;
    //    msgBox.setText(name+" is not loaded!");
    //    msgBox.exec();

    QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Info",
                                          name+" is not loaded.",
                                          QMessageBox::Ok);

    //    QTimer *msgBoxCloseTimer = new QTimer(this);
    //    msgBoxCloseTimer->setInterval(3000);
    //    msgBoxCloseTimer->setSingleShot(true);
    //    connect(msgBoxCloseTimer, SIGNAL(timeout()), msgBox, SLOT(reject()));
    //    msgBoxCloseTimer->start();

    msgBox->exec();
}

void MainWindow::nBatchLoadingDone(int names, int coun)
{
    pr->close();
    pr->resetData();
    //    //qDebug() << "Names = " << names << " Coun = " << coun;
    QMessageBox *msgBox;
    msgBox= new QMessageBox(QMessageBox::Information, "Info",
                            "Total numbers of objects = "+QString::number(names)+"\n"
                                                                                 "Successfully loaded = "+QString::number(names-coun)+"\n"
                                                                                                                                      "Could not load = "+QString::number(coun),
                            QMessageBox::Ok);

    QTimer *msgBoxCloseTimer = new QTimer(this);
    msgBoxCloseTimer->setInterval(10000);
    msgBoxCloseTimer->setSingleShot(true);
    connect(msgBoxCloseTimer, SIGNAL(timeout()), msgBox, SLOT(reject()));
    msgBoxCloseTimer->start();

    msgBox->exec();
}

void MainWindow::getSuspectCheckStateFromSettingsDialog(bool state)
{
    qDebug() << "Got state " << state;
    suspect_state = state;
}

void MainWindow::totalSizeOfNameToProg(int val)
{
    emit setDifferSettings(val);
}

void MainWindow::fr_thresholed_value(float frthrsh){
    FRThreshold = frthrsh;
    qDebug()<<"fr_threshold value "<<FRThreshold;
}

void MainWindow::lpr_api_select_value(QString api_tess_or_google)
{
    qDebug()<<"allah help us>> api_tess_or_google :  "<<api_tess_or_google;
    api_str_for_lpr = api_tess_or_google;
}

void MainWindow::fromSearchByGI(QString img_path, QString dir_path)
{
    //qDebug() << "MainWindow::fromSearchByGI";
    // warker->searchByImgToDir(img_path, dir_path);
}

void MainWindow::inMain(QStringList list)
{
    emit goSearchByGivenIm(list);
}

void MainWindow::loadDetectedFace()
{
    //    std::ifstream TD_file("detected-face-serial.dat");
    //    std::ifstream name_file("detected-face-names-serial.dat");

    //    if(TD_file.good() && name_file.good()) {
    //        try{
    //            deserialize("detected-face-serial.dat") >> detected_temp_descriptors;
    //            deserialize("detected-face-names-serial.dat") >> detected_names;
    //        }catch(...){

    //        }
    //    }

    //qDebug() << "Is lam " << detected_temp_descriptors.size() << " " << detected_names.size();

}

void MainWindow::faceDesFromWark()
{
    QStringList list;
    //qDebug() << "Size of faceDes " << faceDescriptor.size() << " " << detected_temp_descriptors.size();
    //    for (size_t i = 0; i < faceDescriptor.size(); ++i){
    //        //            double mn=100.0; int mtch=-1;
    //        for (size_t j = 0; j < detected_temp_descriptors.size(); ++j){
    //            //                mn = length(face_descriptors[i]-dir_template_descriptors[j]);
    //            ////qDebug() << "Allah";
    //            double diff = length(faceDescriptor[i]-detected_temp_descriptors[j]);
    //            if (diff < 0.45){
    //                std::string path = detected_names[j+j+1];
    //                list.append(QString::fromStdString(path));
    //            }
    //        }
    //    }
    emit goSBI(list);
}

void MainWindow::fromSearchByImgtoMain(QString face)
{
    //   warker->detectFaceFromImage(face);
}

//for deploy
void MainWindow::make_notification_for_unique_face(QPixmap pic, QString name, int cam, int clusterId, int timesOfSameImg, double confidence, int recognize, QString gender, int age)
{
    qDebug()<<"make notification for unique face show into bottom ";

    //QString camer = QString::number(cam);
    //QString clstrId = QString::number(clusterId);
    //QString timesImg = QString::number(timesOfSameImg);

    faceUniq *u_newNot= new faceUniq(pic, name, confidence, recognize, gender, age, this);
    //uniq_face_window->u_addNot(u_newNot);
    //    connect(u_newNot, SIGNAL(emt_uniq_fce(QPixmap)), configdb, SLOT(showFaceToConfigDB(QPixmap)));// face enrollment

    uniq_face_window->u_addNot(u_newNot);// uniquefacewidget class instance of uniq_face_window
    //uniq_face_window->setVisible(true);
    notOn= true;

    /// show faces into tilerdisplay window [tilerdisplay.ui]
    //tilerdisplayWindow->addFR(pic, "face", cam);

}

void MainWindow::getDispRowsColumns(int row, int col)
{
    //        row = 3; col = 3;

    int x = wid/4+2;
    int y = menubar_height+33;
    int w = wid/2;
    int h = hei/2;
    //qDebug() << "Finally =========== " << x << ", " << y << ", " << w << ", " << h;
    int tot_width = w-x;
    int tot_height = h-y;
    //    int tot_width = w;
    //    int tot_height = h;

    //    int add_wid;
    //    int add_col;
    //    if(row<col){
    //        add_wid = w/col;
    //        add_col = h;
    //    }else if(row>col){
    //        add_wid = w;
    //        add_col = h/row;
    //    }else{
    //        add_wid = w/row;
    //        add_col = h/col;
    //    }
    //    while(x <= w && y <= h){

    //    }
    ////qDebug() << "Total w and h " << tot_width << ", " << tot_height;
    //    int a1, a2, b1, b2, c1, c2, d1, d2;
    //    a1 = x; a2 = y;
    //    b1 = w; b2 = y;
    //    c1 = x; c2 = h;
    //    d1 = w; d2 = h;

    //    int single_width = tot_width/col;
    //    int single_column = tot_height/row;
    int single_width = w/col;
    int single_column = h/row;
    //single_column -= y;
    //qDebug() << "Single wid and col = " << single_width << ", " << single_column;


    //        for(int i = x; i <= w; i+=single_width){
    //            //qDebug() << "width = " << i;
    //        }
    //        for(int i = y; i <= h; i+=single_column){
    //            //qDebug() << "height = " << i;
    //        }

    //        for(int i = y; i <= h; i+=single_column){
    //            for(int j = x; j <= w; j+=single_width){
    //                cout <<j<<","<<i << " ";
    //            }
    //            cout << "\n";
    //        }

    QVector<QVector<QPair<int, int>> > vect;
    int x_, y_;
    x_ = x;
    y_ = y;
    for(int i = 0; i <= row; i++){
        QVector<QPair<int, int>> vt;
        for(int j = 0; j <= col; j++){
            //            //qDebug() << "Rajshahi " << x_ << " " << y_;
            vt.push_back(qMakePair(x_, y_));
            x_ += single_width;
        }
        x_ = x;
        y_ += single_column;
        vect.push_back(vt);
    }

    for(int i = 1; i < vect.size(); i++){
        for(int j = 1; j < vect[i].size(); j++){
            cout << "00 = "<<vect[i-1][j-1].first<<","<<vect[i-1][j-1].second <<" "
                                                                             << "01 = "<<vect[i-1][j].first<<","<<vect[i-1][j].second <<" "
                                                                             << "10 = "<<vect[i][j-1].first<<","<<vect[i][j-1].second <<" "
                                                                             << "11 = "<<vect[i][j].first<<","<<vect[i][j].second << endl;
            //watchcam::rectangle rect(vect[i-1][j-1].first,vect[i-1][j].second,vect[i][j-1].second,vect[i][j].first);

            watchcam::rectangle rect(vect[i-1][j-1].first,vect[i-1][j].second,single_width,single_column);
            rects.push_back(rect);
        }
        cout << endl;
    }

    //    //qDebug() << "watchcam::rectangle rect(1,2,3,4)";
    //    for(int i = 0; i < rects.size(); i++){
    //        //qDebug() << rects[i].left;
    //    }



    //    for(int i = x; i <= w; i+=single_width){
    //        for (int j = y; j <= h; j+=single_column){
    //            //qDebug() << "Index = " <<i<<" "<<j;
    //        }
    //    }


    //    Display* display1 = XOpenDisplay(NULL);

    //    XSynchronize(display1, True);

    //    Window x11root = XDefaultRootWindow(display1);

    //    int x1 = 500;
    //    int y1 = 500;
    //    unsigned int width = 721;
    //    unsigned int height = 461;

    //    unsigned int borderWidth = 0;
    //    long colorBlue = 0xff0000ff;

    //    Window x11w = XCreateSimpleWindow(display1, x11root, x1, y1,
    //                                      width, height, borderWidth, 1 /*magic number*/, colorBlue);

    //    XReparentWindow(display1, x11w, staticO->winId(), (staticO->wid/4), staticO->hei/4);
    //    //XReparentWindow(display, x11w, staticO->winId(), (0), staticO->menubar_height+8);
    //    XMapWindow(display1, x11w);


}

void MainWindow::addToAddFace(QString name, QString image_path)
{
    //================================================================================

    //    QPixmap pic;
    //    qDebug() << "before load img appropri";
    //    pic.load(image_path);
    ////    bool flg = pic.load(image_path, "png");
    //    qDebug() << "load after img appropri  ";

    //    QString face_path = "./faces/";
    //    QDir myDir;
    //    QString folder_name = "temp_late2";
    //    QString img_path;
    //    QString image_name;
    //    if(!myDir.exists(folder_name)) //if no directory so create directory
    //    {
    //        myDir.mkpath(face_path+folder_name);
    //        //            image_name = name+".png";
    //        //                image_name = QString::fromUtf8(names_batch[i-1].c_str()) + ".jpg";
    //        image_name = name + ".png";
    //        img_path = face_path+folder_name+"/"+image_name;
    //    }else {
    //        myDir.mkpath(face_path+folder_name);
    //        //            image_name = name+".png";
    //        //                image_name = QString::fromUtf8(names_batch[i-1].c_str()) + ".jpg";
    //        image_name = name + ".png";
    //        img_path = face_path+folder_name+"/"+image_name;
    //    }
    //    QFile file(face_path+folder_name+"/"+image_name);
    //    file.open(QIODevice::WriteOnly);
    //    pic.save(&file, "PNG");
    //    //    pic.save(&file, "JPG");

    //    image_path = img_path;

    //========================================================================================

    qDebug() << "write img appropri";

    if(connectionDB()){
        QSqlQuery queryt; // sql query execution object

        QString create_table_query =
                "create table ADD_FACE ( "
                "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name TEXT not null UNIQUE, "
                "position TEXT, "
                "address TEXT, "
                "phone TEXT, "
                "access_pass TEXT, "
                "image_path TEXT not null"
                ");"
                ;

        if(queryt.exec(create_table_query)){
            //qDebug() << "Table Created";
        }else {
            //qDebug() << "Table Created failed";
        }

        QSqlQuery query;
        query.prepare("INSERT INTO ADD_FACE (name, position, address, phone, access_pass, image_path) VALUES (?,?,?,?,?,?);");
        query.addBindValue(name);
        query.addBindValue("");
        query.addBindValue("");
        query.addBindValue("");
        query.addBindValue("");
        query.addBindValue(image_path);

        if(query.exec()){ // Successfully executed then show pop up message box
            //qDebug() << "Inserted "<< endl;
            //        QMessageBox msg_box;
            //        msg_box.setText("Successfully Inserted");
            //        msg_box.exec();
        }else {
            //qDebug() << "Not inserted!" << endl;
            //        QMessageBox msg_box;
            //        msg_box.setText("Cant inserted!");
            //        msg_box.exec();
        }
    }
}

/* control all Notification related Tasks */
void MainWindow::NotificationManager()
{
    //connect(newFeed2, SIGNAL(addlpNotMan(QPixmap, QString, int)),this, SIGNAL(emitLP(QPixmap, QString, int)));

    /* for tiles show faces window tab connecton [ temporary now, go to on_tileButton_clicked] */
    //connect(this, SIGNAL(addFrNotMan(QPixmap, QString, int)), facesWindow, SLOT(addFR(QPixmap, QString, int)));

    //    connect(this, SIGNAL(notifyFaceNotMan(QPixmap, QString, int, int, int)), this, SLOT(makeNotification(QPixmap, QString, int, int, int)));

    /* for unique face tile [ temporay now, go to on_tileButton_clicked] */
    //connect(this, SIGNAL(addUniqeFaceNotMan(QPixmap, QString, int, dlib::matrix<float,(long)0,(long)1>)), facesWindow, SLOT(addUniqueFace(QPixmap, QString, int, dlib::matrix<float,(long)0,(long)1>)));

    /* for face notification show right bar[ temporay now, go to on_tileButton_clicked] */
    // connect(facesWindow, SIGNAL(notifyFaceFromUniqueFace(QPixmap, QString, int, int, int)), this, SLOT(makeNotification(QPixmap, QString, int, int, int)));

    //qDebug()<<"notification manager functio call test ok ";
}

int MainWindow::getLastDBId(){
    if(connectionDB()){
        QString qu_s =
                "select Id from FeedAddFace where "
                "Id in (select max(Id) from FeedAddFace);"
                ;
        QSqlQuery qu;
        if(qu.exec(qu_s)){
            while(qu.next()){
                int id = qu.value(0).toInt();
                check_last_id = id;
            }
        }
    }

    return check_last_id;
}

void MainWindow::emitFunction(cv::Mat foo)
{
    emit emitDSFace(foo.clone(), 5);
}



void MainWindow::setSearchFaceOn()
{
    ui->searchFaceButton->setStyleSheet(myStyles::searchOn);
}

void MainWindow::setSearchObjectOn()
{
    //  ui->searchFaceButton->setStyleSheet(myStyles::defaultStyle);
    ui->searchObjectButton->setText("Searching");
}

void MainWindow::setSearchFaceOff()
{
    //  ui->searchObjectButton->setStyleSheet(myStyles::searchOn);
    ui->searchObjectButton->setText("Search OFF");
}

void MainWindow::setSearchObjectOff()
{
    ui->searchObjectButton->setStyleSheet(myStyles::defaultStyle);
}

void MainWindow::on_searchFaceButton_clicked()
{
    QString tempF = ui->faceLineEdit->text();
    if(!tempF.isEmpty()){
        //  ui->startButton->setStyleSheet("background-color: rgba(255, 0, 0, 150);")
        searchFOn = !searchFOn;
        if(searchFOn)
        {
            // setSearchObjectOn();
            ui->searchFaceButton->setText("Searching Face ...");
            //ui->searchObjectButton->setT;
            //this->setStyleSheet("MainWindow{background-color:green}");
            ui->searchFaceButton->setStyleSheet("background-color: rgba(255, 0, 0, 150);");
            blink_timer_search_by_name->start(1000);
        }
        else
        {
            // ui->searchObjectButton->setStyleSheet(myStyles::defaultStyle);
            // setSearchObjectOff();
            ui->searchFaceButton->setText("Search Face OFF");
            //  this->setStyleSheet("MainWindow{background-color:red}");
            ui->searchFaceButton->setStyleSheet("background-color: rgb(0, 0, 0);");
            // found = false;
            blink_timer_search_by_name->stop();
            blink_check_by_name = false;
            frame_search_by_name->close();
        }
    }



    //    for(int i=0; i<feeds.size(); i++)
    //    {
    //        feeds[i]->search_requested(tempF,-1,"");
    //    }

}

void MainWindow::on_searchLPRbutton_clicked()
{
    lp_id = 0;

    tilerdisplayWindow->clearLPwithCarPairVector();

    if (tilerdisplayWindow != nullptr)
    {
        delete tilerdisplayWindow;
        tilerdisplayWindow = new TilerDisplay(this);
    }

    tilerdisplayWindow->show();

    QString search_info = ui->LPRlineEdit->text();
    search_info = "%"+search_info+"%";

    qDebug()<<"from user LP : "<<search_info;

    if(connectionDB()){
        QSqlQuery query;
        query.prepare("select ID, number_plate,date_time, color, parentImgPath, childImgPath from detected_LPR "
                      "where (number_plate Like ?);");
        query.addBindValue(search_info);

        if(query.exec()){
            //            qDebug() << "Yes data found" ;
            while(query.next()){

                QString number_plate = query.value(1).toString();
                QString parent_path = query.value(4).toString();
                QString child_path = query.value(5).toString();
                //                qDebug()<<"number_plate : "<<number_plate<<" child_path : "<<child_path<<" parent_path : "<<parent_path;

                QPixmap pic, main_pic;
                pic.load(child_path);
                main_pic.load(parent_path);


                tilerdisplayWindow->add_search_lp_To_tiles(pic, number_plate, lp_id, parent_path);

                lp_id = lp_id+1;

            }
            ui->LPRlineEdit->setText("");// search box set as empty
        }


    }


    /// for backup
    /*
    LPR = ui->LPRlineEdit->text();
    QString srch = ">>>>>>>>> Search LPR requested <<<<<<<<<<";

    qDebug()<<"LPR res : "<<LPR;

    qDebug(qUtf8Printable(srch));
    qDebug(qUtf8Printable(LPR));
    searchLPRon = !searchLPRon;
    if(searchLPRon)
    {
        // setSearchObjectOn();
        //  ui->searchFaceButton->setText("Searching Face ...");
        //ui->searchObjectButton->setT;
        // this->setStyleSheet("MainWindow{background-color:green}");
        ui->searchLPRbutton->setStyleSheet("background-color: rgba(255, 0, 0, 150);");


    }
    else
    {
        // ui->searchObjectButton->setStyleSheet(myStyles::defaultStyle);
        // setSearchObjectOff();
        // ui->searchFaceButton->setText("Search Face OFF");
        //  this->setStyleSheet("MainWindow{background-color:red}");
        ui->searchLPRbutton->setStyleSheet("background-color: rgb(0, 0, 0);");
        // found = false;
        QString fuck = "fcuk";
        LPR = fuck;
    }
*/


}

void MainWindow::on_searchObjectButton_clicked()
{
    //    QString object = myStyles::objects.at(ui->objectCombo->currentIndex());
    QString object = ui->objectCombo->currentText();
    //    //qDebug() << "Object ======== " << object;
    //    int color = myStyles::colorValues.at(ui->colorCombo->currentIndex()-1);
    if(!QString::compare(object, "None") == 0){
        //        QString srch = ">>>>>>>>> Search requested <<<<<<<<<<";
        //        qDebug(qUtf8Printable(srch));
        //        qDebug(qUtf8Printable(object));
        //        qDebug(qUtf8Printable(QString::number(color)));

        searchOn = !searchOn;
        if(searchOn)
        {
            // setSearchObjectOn();
            ui->searchObjectButton->setText("Searching ...");
            //ui->searchObjectButton->setT;
            // this->setStyleSheet("MainWindow{background-color:green}");
            ui->searchObjectButton->setStyleSheet("background-color: rgba(255, 0, 0, 150);");

            //        blink_check_from_ui = true;
            ////qDebug() << "Splash window";
            blink_timer->start(1000);// 5 second



        }

        else
        {
            // ui->searchObjectButton->setStyleSheet(myStyles::defaultStyle);
            // setSearchObjectOff();
            ui->searchObjectButton->setText("Search Object");
            //  this->setStyleSheet("MainWindow{background-color:red}");
            ui->searchObjectButton->setStyleSheet("background-color:white;");
            // found = false;
            //blink_check_from_ui = false;
            blink_timer->stop();
            blink_check = false;
            frame->close();

        }
    }
    //    for(int i=0; i<feeds.size(); i++)
    //    {
    //        feeds[i]->search_requested("",color,object);
    //    }

}
void MainWindow::on_startButton_pressed()
{
    //        if(!running){

    //            //        manager->get(QNetworkRequest(QUrl("http://www.sigmindai.net/wc-surv/wc-surv.php?passkey=secret-wc")));

    //            //        ui->startButton->setText("Checking..");
    //            //        ui->startButton->setStyleSheet("background-color: rgb(170, 255, 127);");
    //            //        //start camera

    //            ////        cam = new Camera(ui->linkLine->text().toStdString().c_str());
    //            ////        cam->moveToThread(thread);

    //            //        connect(cam, SIGNAL(ui_go(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >)), this,
    //            //               SLOT(update_ui(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >)));
    //            //        connect(cam, SIGNAL(start_requested()), thread, SLOT(start()));
    //            //        connect(thread, SIGNAL(started()), cam, SLOT(go()));
    //            //        cam->start();

    //            //        ui->menuBar->setDisabled(false);
    //            //       // ui->actionFootage_analysis->setDisabled(false);
    //            //        ui->scrollArea->setDisabled(false);
    //            running = true;

    //        }
    //        else {
    //            ui->startButton->setText("Invalid");

    //            // ui->startButton->setDisabled(true);

    //            //close camera
    //            //  ui->menuBar->setDisabled(true);   // Uncomment for trial
    //            // ui->actionFootage_analysis->setDisabled(true);
    //            //   ui->scrollArea->setDisabled(true);  // Uncomment for trial
    //            running = false;
    //        }
}

void MainWindow::notificationSLot(bool)
{
    if(!notOn){
        //nots->setVisible(true);
        notOn= true;
    }
    else {
        //nots->setVisible(false);
        notOn= false;
    }
}
void MainWindow::makeNotification(QPixmap m_pic, QPixmap pic, QString name, int cam, int clusterId, int timesOfSameImg, double confidence, QString gender, int age, QString color){


    QString camer = QString::number(cam);
    QString clstrId = QString::number(clusterId);
    QString timesImg = QString::number(timesOfSameImg);

    //    Not *newNot= new Not(pic, name, camer, clstrId, timesImg, confidence, this);
    Not *newNot= new Not(m_pic, pic, name, camer, clstrId, timesImg, confidence, gender, age, this, color);
    newNot->setFixedWidth((this->wid) - (this->wid/4+this->wid/2)+10);
    //nots->addNot(newNot);

    nots->addNot(clstrId, newNot);// notWidget class instance of nots
    nots->setVisible(true);
    notOn= true;
}

void MainWindow::makeNotification(QPixmap person, QPixmap pic, QString name, int cam, int clusterId, int timesOfSameImg, double confidence, QString gender, int age)
{
    qDebug()<<"makenotface function call come from adduniqueface method ";

    //    Notification *newNoti= new Notification(name, "", QString::number(cam), pic.scaledToHeight(140), QString::number(clusterId), QString::number(timesOfSameImg));
    //    emailController->addNot(newNoti);

    QString camer = QString::number(cam);
    QString clstrId = QString::number(clusterId);
    QString timesImg = QString::number(timesOfSameImg);

    //    Not *newNot= new Not(pic, name, camer, clstrId, timesImg, confidence, this);
    Not *newNot= new Not(pic, name, camer, clstrId, timesImg, confidence, gender, age, this);
    newNot->setFixedWidth((this->wid) - (this->wid/4+this->wid/2)+10);
    //nots->addNot(newNot);

    nots->addNot(clstrId, newNot);// notWidget class instance of nots
    qDebug()<<"makenot test j";
    nots->setVisible(true);
    //        nots->setVisible(false);
    notOn= true;

    /// for recognized faces show into tiles
    tilerdisplayWindow->uniqueLicencePlateShowInTiles(pic, name, cam, "");
    tilerdisplayWindow->personShowInTiles(person, name, cam, "");
}

void MainWindow::addNotToBar(Notification *noti)
{
    //qDebug()<<"facenotbar"<<" faceType = "<<noti->name;
    //Not *newNot= new Not(noti->pic, noti->name, noti->cam, noti->clusterId, noti->timesOfSameImg, this);
    //nots->addNot(newNot);
    //    QString clstr = noti->clusterId;
    //    delete noti;
    //    nots->addNot(clstr, newNot);// notWidget class instance of nots
    //    nots->setVisible(true);
    //    notOn= true;

}

void MainWindow::setNotPosition()
{
    int y= ui->menuBar->geometry().y();//+ 20;
    //   int y= this->height()-980;
    int x= this->width()/*-402*/;
    //qDebug() << "x = " << x << " " << " y = " << y;

    //        nots->move(this->wid/4+this->wid/2+5,this->menubar_height+8);
    //        nots->setFixedWidth((this->wid) - (this->wid/4+this->wid/2)+10);
    //        nots->setFixedHeight(this->hei-88);

    nots->move(this->wid/4+this->wid/2+5+50,this->menubar_height+8);
    nots->setFixedWidth((this->wid) - (this->wid/4+this->wid/2)+10-50);
    nots->setFixedHeight(this->hei-88);

    lpnots->move(0,this->menubar_height+8);
    //    lpnots->setFixedWidth((this->wid) - (this->wid/4+this->wid/2)+10);
    lpnots->setFixedWidth((this->wid) - (this->wid/4+this->wid/2)+60);
    lpnots->setFixedHeight(this->hei-88);
}

int MainWindow::widthCal()
{
    ////qDebug() << flowLayout->geometry().width();
    int rem = (flowLayout->geometry().width())%(myStyles::minWidth);
    int res = (flowLayout->geometry().width())/(myStyles::minWidth);
    if(rem)
    {
        ////qDebug() << "hey " << (res+1);
        return (flowLayout->geometry().width()-1)/(res+1);
    }
    else
    {
        ////qDebug() << "res" << res;
        return (myStyles::minWidth-1);
    }
}

void MainWindow::setSizes(int width)
{
    int height= (width*9)/16;
    myStyles::runningFeedWidth = width;
    myStyles::runningFeedHeight = height;

    ////qDebug() << "inside sizes " << width;
    //    for(int i=0;i<feeds.size();i++){
    //        feeds[i]->setSizes(width, height);
    //    }
}

void MainWindow::on_actionAdd_Camera_triggered()
{
    //    Feed *newFeed= new Feed(cam_count++,myStyles::runningFeedWidth,myStyles::runningFeedHeight, darknet_mutex, templates_names, template_descriptors, this);
    //    newFeed->set_blacklist_descriptor(blacklist_descriptors);

    //    feeds.push_back(newFeed);
    //    connect(newFeed, SIGNAL(emitFace(QPixmap , QString, int)), this, SLOT(addFace_triggered(QPixmap,QString,int)));
    //    connect(newFeed, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
    //    connect(newFeed, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
    //    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
    //    connect(newFeed, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));

    //    //flowLayout->addWidget(newFeed);
    //    flowLayout->addWidget(newFeed);

    //    ////qDebug() << ui->scrollAreaWidgetContents->geometry().height() << endl;

    //    setSizes(widthCal());
    //    thread = new QThread();
    //    worker = new Worker();

    //worker->moveToThread(thread);

    //connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));

    //  connect(thread, SIGNAL(started()), worker, SLOT(doWork(int)));
    //connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), worker, SLOT(doWork(QPixmap,QString,int)));
    //connect(worker, SIGNAL(valueChanged(QPixmap,QString,int)), this, SLOT(addLP(QPixmap,QString,int)));
    //connect(worker, SIGNAL(finishedLPR()), thread, SLOT(quit()), Qt::DirectConnection);


    //    FRthread = new QThread();
    //    warker = new Warker();

    //    warker->moveToThread(FRthread);
    //   // warker->setup(templates_names, template_descriptors);
    //  //  connect(this,SIGNAL(load_template()), warker, SLOT(receive_template()));

    //   //  load_faces();
    //    connect(warker, SIGNAL(warkRequested()), FRthread, SLOT(start()));

    //  //  connect(thread, SIGNAL(started()), worker, SLOT(doWork(int)));
    //    connect(this, SIGNAL(requestUpdateFR(cv::Mat,QString,int)), warker, SLOT(doWark(cv::Mat,QString,int)));
    //   //connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), this, SLOT(valueChanged(QPixmap,QString,int));
    //          //  connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT()

    //   // connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT(valueChanged(QPixmap,QString,int)));
    //      connect(warker, SIGNAL(valueFRChanged(QPixmap,QString,int,matrix<float,0,1>)), this, SLOT(addFR(QPixmap,QString,int,matrix<float,0,1>)));
    //    connect(warker, SIGNAL(finishedFR()), FRthread, SLOT(quit()), Qt::DirectConnection);


}

void MainWindow::replyFinished(QNetworkReply *rep){
    //    if(rep->readAll() == "ok") {
    //        //qDebug() << "valid";

    //        trialTimer= new QTimer(this);
    //        connect(trialTimer, SIGNAL(timeout()), this, SLOT(trialCheck()));
    //        trialTimer->start(300000);

    //        manager = new QNetworkAccessManager(this);

    //        connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinishedOnline(QNetworkReply*)));
    //    }
    //    else {
    //        //qDebug() << rep->readAll();
    //        //qDebug() << "error trial starting";
    //        ui->startButton->setDisabled(true);
    //        expireDialog *expire = new expireDialog;
    //        expire->setAttribute( Qt::WA_DeleteOnClose );   // Uncomment for trial
    //        expire->show();
    //        this->close();
    //    }


}

void MainWindow::replyFinishedOnline(QNetworkReply *rep){
    if(rep->readAll() == "ok") {
        //        //qDebug() << "valid";

    }

    else {
        //        trialTimer->stop();
        //        ui->startButton->setDisabled(false);
        //        expireDialog *expire = new expireDialog;
        //        expire->setAttribute( Qt::WA_DeleteOnClose );
        //        expire->show();

        //        this->close();
    }


}

void MainWindow::trialCheck(){
    // manager->get(QNetworkRequest(QUrl("http://www.sigmindai.net/wc-surv/wc-surv.php?passkey=secret-wc")));

}

void MainWindow::disagreed(){
    ui->startButton->setDisabled(true);
    ui->actionAdd_Camera->setDisabled(true);
    ui->actionFootage_analysis->setDisabled(true);
    ui->scrollArea->setDisabled(true);
    this->close();
}

void MainWindow::agreed(){

    ui->startButton->setDisabled(false);
    ui->startButton->setDisabled(false);
    ui->actionAdd_Camera->setDisabled(false);
    ui->actionFootage_analysis->setDisabled(false);
    ui->scrollArea->setDisabled(false);
    //ui->actionAdd_Camera->setDisabled(false);

}

void MainWindow::on_startButton_released()
{
    //        if(running){
    //            ui->startButton->setText("BHTPA-JT");
    //            ui->startButton->setStyleSheet("background-color: rgba(255, 0, 0, 150);");

    //            ui->startButton->setDisabled(false);
    //        }
    //        else{
    //            ui->startButton->setText("Check");
    //            ui->startButton->setStyleSheet("background-color: rgb(170, 255, 127);");
    //        }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    setSizes(widthCal());
    setNotPosition();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(notOn){
        if(!nots->geometry().contains(event->pos())) {
            //nots->setVisible(false);
            notOn=false;
        }
    }
}

void MainWindow::on_actionShow_Faces_triggered()
{
    //facesWindow = new Faces(this);
    //facesWindow->setAttribute( Qt::WA_DeleteOnClose , true);
    // facesWindow->show();

}

void MainWindow::on_actionAdd_face_triggered()
{

    //facesWindow->show();
}

void MainWindow::addFace_triggered(cv::Mat pic, int indx)
{
    QString enc = "receive Face";

    // facesWindow->addFR(pic, enc, indx);
    // tilerdisplayWindow->only_uniqueFace_show_inTiles(pic, enc, indx);

    //qDebug() << " Inside addFace_triggered";
    // warker->requestWark();

    // emit requestUpdateFR(pic, enc, indx);

}

void MainWindow::fromDsToMain(cv::Mat main_obj, cv::Mat sub_obj_of_main){

    //    staticO->DSaddLPR_triggered(main_obj, sub_obj_of_main, 100, 100.0, 1, "QString::fromUtf8(rect.str_color.c_str())");

    QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) main_obj.data, main_obj.cols, main_obj.rows, QImage::Format_RGB888));
    QString lpr_path_for_first = "./captures/Object/";
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    QDir myDir;
    if(!myDir.exists(lpr_path_for_first)){
        myDir.mkpath(lpr_path_for_first);
    }
    pict.save(lpr_path_for_first+time+"1.png");
    pict =  QPixmap::fromImage(QImage((unsigned char*) sub_obj_of_main.data, sub_obj_of_main.cols, sub_obj_of_main.rows, QImage::Format_RGB888));
    pict.save(lpr_path_for_first+time+"2.png");
}

void MainWindow::fromDsToMain(Buf_info::names_buf_info *info)
{
    staticO->DSaddFace_triggered(info);
}

void MainWindow::fromDsToMain(cv::Mat pic, watchcam::rectangle rect)
{

    if(rect.type == 0){
        qDebug()<<"person test";
        staticO->DSaddFace_triggered(pic,rect);
    }else if(rect.type == 2){
        qDebug()<<"face test";
        staticO->DSaddFace_triggered(pic,rect);
    }

}

void MainWindow::fromDsToMainForOvercrowding(int cam_id)
{
    cam_id = cam_id + 1;// because camId started in 0, so add 1
    staticO->DSoverCrowd_triggered(cam_id);

    qDebug()<<"fromDsToMainForOvercrowding() call in mw and camera id: "<<cam_id;

}

void MainWindow::fromDsToMain(cv::Mat pic, int n, double fps_val, std::vector< watchcam::rectangle > ds_rects, int type)
{
    //    //qDebug() << "..............>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<........... " << QString::fromUtf8(color.c_str());

    //    if(type == 0){ // found face
    //        staticO->DSaddFace_triggered(pic, n, 1, ds_rects);
    //    }else if (type == 1) { // found lpr
    //        staticO->DSaddLPR_triggered(pic, n, 1, ds_rects);
    //    }
    for(int i = 0; i < ds_rects.size(); i++){
        if(ds_rects[i].type == 2){ // found face
            //staticO->DSaddFace_triggered(pic, n, 1, ds_rects[i].type, QString::fromUtf8(ds_rects[i].str_color.c_str()));
            //            QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) pic.data, pic.cols, pic.rows, QImage::Format_RGB888));
            //            QString lpr_path_for_first = "./captures/face_check/";
            //            QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
            //            QDir myDir;
            //            if(!myDir.exists(lpr_path_for_first)){
            //                myDir.mkpath(lpr_path_for_first);
            //            }
            //            pict.save(lpr_path_for_first+QString::fromUtf8(ds_rects[i].str_color.c_str())+time+".png");
        }else if (ds_rects[i].type == 0) { // found lpr
            //            staticO->DSaddLPR_triggered(pic, pic, n, 1, ds_rects[i].type, QString::fromUtf8(ds_rects[i].str_color.c_str()));
            //            QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) pic.data, pic.cols, pic.rows, QImage::Format_RGB888));
            //            QString lpr_path_for_first = "./captures/lpr_check/";
            //            QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
            //            QDir myDir;
            //            if(!myDir.exists(lpr_path_for_first)){
            //                myDir.mkpath(lpr_path_for_first);
            //            }
            //            pict.save(lpr_path_for_first+QString::fromUtf8(ds_rects[i].str_color.c_str())+time+".png");
        }
    }
}

void MainWindow::fromDsToMain(cv::Mat main_obj, cv::Mat sub_obj_of_main, watchcam::rectangle rect)
{
    qDebug()<<"inside fromdstomain " << rect.type<<" "<<QString::fromUtf8(rect.str_label.c_str());

    if(rect.type == 1){ ///LP
        qDebug()<<" rect type 1 "<<rect.type<<" lp";
        std::string path = "/home/sigmind/Desktop/car/" ;
        //        cv::imwrite(path+ ".jpeg", main_obj);

        staticO->DSaddLPR_triggered(main_obj, sub_obj_of_main, rect.source_id, 0.0, 0, "hello");
        //staticO->DSaddFace_triggered(pic, n, 1, ds_rects[i].type, QString::fromUtf8(ds_rects[i].str_color.c_str()));
    }
    if (rect.type == 10) { ///Face
        qDebug()<<"test rect type 0";
        //        std::string path = "/home/sigmind/Desktop/lp/" ;
        //        cv::imwrite(path+ ".jpeg", sub_obj_of_main);

        //            staticO->DSaddFace_triggered(main_obj, sub_obj_of_main, "hello", rect.source_id, "hello");
        staticO->DSaddFace_triggered(main_obj, sub_obj_of_main, "hello", rect.source_id, "hello");
    }

    //    try{
    //        //        staticO->DSaddFace_triggered(main_obj, sub_obj_of_main, rect);
    //        int s = rect.person.size();
    //        if(s>=0 && s < 100){
    //            //            for(int i = 0; i < s; i++){
    //            //                cv::Mat *sub = rect.person[i].first;
    //            //                float distance = rect.person[i].second;
    //            //                qDebug()<<"before dsaddface trig first-----------------------------";
    //            //                staticO->DSaddFace_triggered(main_obj, sub, sub_obj_of_main,  rect.source_id, distance, 0,QString::fromUtf8(rect.mask_or_unmask.c_str()), QString::fromUtf8(rect.str_color.c_str()), 1, s);
    //            //            }
    //            QString mask_st = QString::fromUtf8(rect.mask_or_unmask.c_str());
    //            //            staticO->uniq_face_window->setLabelForShowMaskDis("There are "+QString::number(staticO->unmask)+" peoples are not wearing "
    //            //                                                                                                            "mask and "
    //            //                                                                                                            "violating distance there are "+QString::number(staticO->distance_vio) +" peoples!");
    //            //            qDebug()<<"before dsaddface trig second++++++++++++++++++++++++++++++++++++";
    //            //staticO->DSaddFace_triggered(main_obj, sub_obj_of_main, rect.source_id, rect.fps, s, QString::fromUtf8(rect.str_color.c_str()), mask_st, 0, s);
    //        staticO->DSaddFace_triggered(main_obj, sub_obj_of_main, mask_st, rect.source_id, "color");
    //        }

    //    }catch(...){

    //    }
}

void MainWindow::fromDsToMain(cv::Mat *main_obj, cv::Mat *sub_obj_of_main, Buf_info::names_buf_info *buf)
{
   // cv:imwrite("")
    staticO->DSaddFace_triggered(main_obj, sub_obj_of_main, buf);
}

//void MainWindow::dowarkStarted(){

//    emit requestUpdateFR(warker->inf);
//    qDebug() << "Thread on success fully";

//}

void MainWindow::dowarkStarted(){

    qDebug()<<"test dowarkstarted >>>>>>>>>>";

    //    emit requestUpdateFR(warker->m_pic, warker->pic_b, warker->name_b, warker->indx_b, FRThreshold, warker->fps_vlue, suspect_state, warker->obj_color, 0, 0);
    emit requestUpdateFR(warker->m_pic, warker->pic_b, warker->indx_b, suspect_state, FRThreshold);
    //    }

    //    emit requestUpdateFR(warker->inf);
    //    qDebug() << "ppppppppppppppp "<< ppppp << " fffffffffffffffffffff "<< fffff;
    //    if(ppppp == true && warker->person_list_check == 1){
    ////        qDebug() << "Namaj ..................... "<< warker->fps_vlue << " " << warker->person_list_check;
    //        emit requestUpdateFR(warker->m_pic, warker->close_m_pic, warker->pic_b,warker->name_b, warker->indx_b, FRThreshold, warker->distance_per, suspect_state, warker->obj_color, warker->person_list_check, warker->size_of_dist);
    //    }
    //    else if(fffff == true  && warker->person_list_check == 0){
    //        emit requestUpdateFR(warker->m_pic, warker->pic_b,warker->name_b, warker->indx_b, FRThreshold, warker->fps_vlue, suspect_state, warker->obj_color, warker->person_list_check, warker->size_of_dist);
    //    }
    ppppp = false;
    fffff = false;

    //    qDebug() << "Thread on success fully";
    //    emit requestUpdateFR(warker->person, warker->face, warker->buf);
    //    emit requestUpdateFR(warker->inf);

}

void MainWindow::dbSyncDowark()
{
    //qDebug()<<"dbSyncDowark conter "<<++counter;
    emit requestDoWark(++check_last_id, sync_var->pic_s, sync_var->name_s, sync_var->index_s, sync_var->confidence_s, sync_var->gender);
}

void MainWindow::callAddToDb(int Id, QPixmap pic, QString str, int indx, double confidence,
                             QString date_time, int sync_states, QString date, QString img_name, QString image_path, int rec, QString gender){
    //qDebug() << "Befor add to db cntt2 "<<++cntt2;
    //addToDB(Id, pic, str, indx, confidence, date_time, sync_states, date, img_name, image_path, rec, gender);
    //qDebug() << "after add to db\n";



}

void MainWindow::syncChecker(){
    if(connectionDB()){
        QSqlQuery query;
        QString qu =
                "select id, person_path, face_path, date_time, source, mask_st, status from PersonFace where status=?;"
                ;
        query.prepare(qu);
        query.addBindValue(0);
        if(query.exec()){
            while(query.next()){
                sync_ch->id = query.value(0).toInt();
                sync_ch->person = query.value(1).toString();
                sync_ch->face = query.value(2).toString();
                sync_ch->date_time = query.value(3).toString();
                sync_ch->source = query.value(4).toInt();
                sync_ch->mask_st = query.value(5).toString();
                sync_ch->status = query.value(6).toInt();
                //                //qDebug() << "Id = " << query.value(0).toInt();
                //                int idc = query.value(0).toInt();
                //                QString namec = query.value(1).toString();
                //                QString save_pathc = query.value(2).toString();
                //                QString date_timec = query.value(3).toString();
                //                double con = query.value(4).toDouble();
                //                int video_srcc = query.value(5).toInt();
                //                int statesc = query.value(6).toInt();
                //                int rec_check_or_not = query.value(7).toInt();

                //                this->idc = idc;
                //                this->namec = namec;
                //                this->save_pathc = save_pathc;
                //                this->date_timec = date_timec;
                //                this->con = con;
                //                this->video_srcc = video_srcc;
                //                this->statesc = statesc;
                //                rec_check = rec_check_or_not;

                sync_ch->requestWorkSyChT();
            }
        }
    }
}

void MainWindow::syncChCallDoWark(){
    //qDebug() << this->idc << " " << this->namec << " " << this->date_timec << " " << this->video_srcc;
    //    emit data_transfer_to_syncDowark(this->idc, this->namec, this->save_pathc, this->date_timec, this->con,
    //                                     this->video_srcc, this->statesc, rec_check);
    emit data_transfer_to_syncDowark(sync_ch->id, sync_ch->person, sync_ch->face,
                                     sync_ch->date_time, sync_ch->source
                                     , sync_ch->mask_st, sync_ch->status);
}

void MainWindow::updateFeedAddFace(int id){
    if(connectionDB()){
        QString str =
                "update PersonFace set status = ? where id = ?;"
                ;
        QSqlQuery qu;
        qu.prepare(str);
        qu.addBindValue(1);
        qu.addBindValue(id);
        if(qu.exec()){
            //qDebug() << "Update Done!";
        }
    }
}

void MainWindow::DSaddFace_triggered(Buf_info::names_buf_info *info)
{
    //    warker->inf = info;
    //    if(face_detection_check_or_uncheck == true){
    //        warker->requestWark();
    //    }

}

void MainWindow::DSaddFace_triggered(cv::Mat *person, cv::Mat *face, Buf_info::names_buf_info *buf)
{

    //    warker->person = person->clone();
    //    warker->face = face->clone();
    //    warker->buf = buf;
    //    if(face_detection_check_or_uncheck == true){
    //        warker->requestWark();
    //    }
}

void MainWindow::DSaddFace_triggered(cv::Mat *person, cv::Mat *face, watchcam::rectangle)
{
    //    warker->m_pic = person->clone();
    //    warker->pic_b = face->clone();
    //    warker->close_m_pic = close_m_pic->clone();
    //    warker->name_b = mask_or_unmask;
    //    warker->indx_b = indx;
    //    warker->fps_vlue = fps_val;
    //    warker->obj_color = obj_color;
    //    warker->person_list_check = per_list_check;
    //    warker->size_of_dist = size_of_p_l;
}

void MainWindow::DSaddFace_triggered(cv::Mat *m_pic, cv::Mat* close_m_pic, cv::Mat *pic, int indx, double fps_val, /*std::vector< *//*watchcam::rectangle *//*>*/ int ds_rects, QString obj_color, QString mask_or_unmask, int per_list_check, int size_of_p_l)
{
    //    //    for(int i = 0; i < ds_rects.size(); i++){
    //    source_and_object.first = indx;
    //    source_and_object.second = ds_rects/*[i]*//*.type*/;
    //    QString enc = "receive Face";
    //    qDebug()<<"inside dsaddface first=============================";
    //    warker->m_pic = m_pic->clone();
    //    warker->pic_b = pic->clone();
    //    warker->close_m_pic = close_m_pic->clone();
    //    warker->name_b = mask_or_unmask;
    //    warker->indx_b = indx;
    //    warker->distance_per = fps_val;
    //    warker->obj_color = obj_color;
    //    warker->person_list_check = per_list_check;
    //    warker->size_of_dist = size_of_p_l;
    //    if(face_detection_check_or_uncheck == true){
    //        ppppp = true;
    ////        qDebug() << "Final data insertion ...................... "<< indx << " " << mask_or_unmask << " " << obj_color << " " << size_of_p_l;
    //        warker->requestWark();
    //    }
}

void MainWindow::DSaddFace_triggered(cv::Mat *m_pic, cv::Mat *pic, int indx, double fps_val, /*std::vector< *//*watchcam::rectangle *//*>*/ int ds_rects, QString obj_color, QString mask_or_unmask, int per_list_check, int size_of_p_l)
{
    //    for(int i = 0; i < ds_rects.size(); i++){
    //    source_and_object.first = indx;
    //    source_and_object.second = ds_rects/*[i]*//*.type*/;

    //    qDebug()<<"face dsaddface inside###################################";

    //    QPixmap mpic =  QPixmap::fromImage(QImage((unsigned char*) m_pic->clone().data, m_pic->clone().cols, m_pic->clone().rows, QImage::Format_RGB888));
    //    QPixmap fpic =  QPixmap::fromImage(QImage((unsigned char*) pic->clone().data, pic->clone().cols, pic->clone().rows, QImage::Format_RGB888));


    //   m_pic->release();
    //   pic->release();
    //    helperThread->helperdatacolpf = new HelperDataCollection(mpic, fpic, mask_or_unmask, indx, obj_color);
    //    helperThread->firstpic = mpic;
    //    helperThread->thirdpic = fpic;
    //    helperThread->mask = mask_or_unmask;
    //    helperThread->index = indx;
    //    helperThread->color = obj_color;
    //    helperThread->requestWorkan();
    //    //testerThread->requestWork();
    qDebug()<<"mask_or_unmask:"<<mask_or_unmask;

    QString enc = "receive Face";
    //    warker->m_pic = m_pic->clone();
    //    warker->pic_b = pic->clone();
    //    warker->name_b = mask_or_unmask;
    //    warker->indx_b = indx;
    //    warker->fps_vlue = fps_val;
    //    warker->obj_color = obj_color;
    //    warker->person_list_check = per_list_check;
    //    warker->size_of_dist = size_of_p_l;


    //    qDebug() << " DSaddFace_triggered Basedul isalm \n";
    //    if(face_detection_check_or_uncheck == true){
    //        fffff = true;
    //        warker->requestWark();
    //    }
}
void MainWindow::DSaddFace_triggered(cv::Mat *m_pic, cv::Mat *pic, int indx, double fps_val, /*std::vector< *//*watchcam::rectangle *//*>*/ int ds_rects, QString obj_color, QString mask_or_unmask, int per_list_check)
{
    //    for(int i = 0; i < ds_rects.size(); i++){
    source_and_object.first = indx;
    source_and_object.second = ds_rects/*[i]*//*.type*/;


    QString enc = "receive Face";
    //    warker->m_pic = m_pic->clone();
    //    warker->pic_b = pic->clone();
    //    warker->name_b = mask_or_unmask;
    //    warker->indx_b = indx;
    //    warker->fps_vlue = fps_val;
    //    warker->obj_color = obj_color;
    //    warker->person_list_check = per_list_check;


    //    qDebug() << " DSaddFace_triggered Basedul isalm \n";
    //    if(face_detection_check_or_uncheck == true){
    //        warker->requestWark();
    //    }
}
void MainWindow::DSaddFace_triggered(cv::Mat *m_pic, cv::Mat *pic, int indx, double fps_val, /*std::vector< *//*watchcam::rectangle *//*>*/ int ds_rects, QString obj_color, QString mask_or_unmask)
{

    source_and_object.first = indx;
    source_and_object.second = ds_rects/*[i]*//*.type*/;


    QString enc = "receive Face";
    //    warker->m_pic = m_pic->clone();
    //    warker->pic_b = pic->clone();
    //    warker->name_b = mask_or_unmask;
    //    warker->indx_b = indx;
    //    warker->fps_vlue = (int)fps_val;
    //    warker->obj_color = obj_color;

    //    //    qDebug() << " DSaddFace_triggered Basedul isalm \n";
    //    ////qDebug() << "DS object name = " << this->metaObject()->className() << endl;

    //    //       facesWindow->addFR(pic, enc, indx);
    //    ////qDebug() << "Main Thread Id = " << thread()->currentThreadId();
    //    //this->pic = pic; this->enc = enc; this->indx = indx;

    //    //warker->abort();
    //    if(face_detection_check_or_uncheck == true){
    //        warker->requestWark();
    //    }


    // cv::Mat spirit = cv::imread("/home/sigmind/xhuv.png");

    //emit requestUpdateFR(pic,enc, indx);
    //warker->doWark(pic,enc, indx);
    //spirit.release();
    //  pic.release();

}

void MainWindow::DSaddFace_triggered(cv::Mat m_pic, cv::Mat pic, QString mask_or_unmask, int indx, QString obj_color)
{
    qDebug() << "test DSaddFace triggered";

    QPixmap mpic =  QPixmap::fromImage(QImage((unsigned char*) m_pic.data, m_pic.cols, m_pic.rows, QImage::Format_RGB888));
    QPixmap fpic =  QPixmap::fromImage(QImage((unsigned char*) pic.data, pic.cols, pic.rows, QImage::Format_RGB888));


    //       m_pic->release();
    //       pic->release();
    //            helperThread->helperdatacolpf = new HelperDataCollection(mpic, fpic, mask_or_unmask, indx, obj_color);
    //    helperThread->firstpic = mpic;
    //    helperThread->thirdpic = fpic;
    //    helperThread->mask = mask_or_unmask;
    //    helperThread->index = indx;
    //    helperThread->color = obj_color;
    //    helperThread->requestWorkan();

    warker->m_pic = m_pic;
    warker->pic_b = pic;
    warker->name_b = mask_or_unmask;
    warker->indx_b = indx;
    warker->fps_vlue = 10.0;
    warker->obj_color = obj_color;

    //if(face_detection_check_or_uncheck == true){
    warker->requestWark();
    //}
}

void MainWindow::DSaddFace_triggered(cv::Mat obj, watchcam::rectangle rct)
{
    if(rct.type == 0){
        //qDebug()<<"person test";
        /* stop helper thread for temporary overcrowd testing */

        //        QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) obj.data, obj.cols, obj.rows, QImage::Format_RGB888));
        //        helperThread->firstpic = pict;

        //        helperThread->index = rct.source_id;
        //        helperThread->overcrowed_val = overcrowed_value_from_ds;
        //        helperThread->requestWorkan();

    }else if(rct.type == 2){
        qDebug()<<"face test DSaddFace triggered";
        //addFace_triggered(obj,rct.source_id);
        warker->m_pic = obj;
        warker->indx_b = rct.source_id;

        if(face_detection_check_or_uncheck == true){
            warker->requestWark();
        }
    }
}

void MainWindow::DSoverCrowd_triggered(int cmm)// for over crowd
{
    //    qDebug() << "DSaddLPR_triggered for over_crowd....";

    overThread->overcroweded_vl = cmm;
    overThread->requestOveran();
}

void MainWindow::DSaddLPR_triggered(cv::Mat main_obj, cv::Mat pic, int indx, double fps_val, int ds_rects, QString obj_color_){
    qDebug() << "DSaddLPR_triggered";

    //    try{
    //        QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) main_obj->data, main_obj->cols, main_obj->rows, QImage::Format_RGB888));
    //    //    QString lpr_path_for_first = "./captures/Object/";
    //    //    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    //    //    QDir myDir;
    //    //    if(!myDir.exists(lpr_path_for_first)){
    //    //        myDir.mkpath(lpr_path_for_first);
    //    //    }
    //    //    pict.save(lpr_path_for_first+time+"1.png");
    //        QPixmap pict_ =  QPixmap::fromImage(QImage((unsigned char*) pic->data, pic->cols, pic->rows, QImage::Format_RGB888));
    //    //    pict.save(lpr_path_for_first+time+"2.png");
    //        if(!pict.isNull() && !pict_.isNull()){
    //            qDebug()<< "addLP(pict, pi)";
    //            addLP(pict, pict_, "bal", 0, "sal");
    //    //        main_obj->deallocate();
    //    //        pic->deallocate();
    //        }
    //    }catch(...){

    //    }


    try{
        source_and_object.first = indx;
        source_and_object.second = ds_rects/*.type*/;
        //    for(int i = 0; i < ds_rects.size(); i++){
        //        source_and_object.first = indx;
        //        source_and_object.second = ds_rects[i].type;
        qDebug() << ":::::::::::::::::::::::::::::::::::::::::::::::: ";
        //    }
        //    QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) pic.data, pic.cols, pic.rows, QImage::Format_RGB888));
        worker->main_pi = main_obj;
        worker->pi = pic;
        worker->s = "Person";
        worker->ind = indx;
        worker->obj_color = obj_color_;
        qDebug()<<"lpr_detection_check_or_uncheck : "<<lpr_detection_check_or_uncheck;
        //if(lpr_detection_check_or_uncheck == true){
        worker->requestWork();
        //}
    }catch(...){

    }


}

QString MainWindow::encodeString(QString data)
{
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
        ////qDebug()<<encodedString[i]<<" "<<"9";
        //        else {
        //            //qDebug()<<encodedString[i];
        //        }

    }
    return encodedString;
}

void MainWindow::dataInsertIntoDb(QPixmap person, QPixmap face, int source, QString mask_status)
{
    if(connectionDB()){

        if(QString::compare(mask_status, "clear") != 0){
            QString face_path = "./captures/masked/";
            QString obliq = "/";
            // QString format = "dd.MM.yyyy";
            QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            date_time = encodeString(date_time);
            QString at = "<at>";
            QString date = QDate::currentDate().toString("yyyy.MM.dd");
            QString img_path = face_path+date+obliq;
            QString image_name = img_path+at+QTime::currentTime().toString();

            QDir myDir;
            if(!myDir.exists(date)) //if no directory so create directory
            {
                myDir.mkpath(img_path);
                person.save(image_name+"person.png");
                face.save(image_name+"face.png");
            }

            QSqlQuery query;


            if (query.exec(
                        "CREATE TABLE PersonFace ( "
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "person_path VARCHAR(250) NOT NULL, "
                        "face_path VARCHAR(250) NOT NULL, "
                        "date_time DATETIME NOT NULL, "
                        "source int not null, "
                        "mask_st varchar(150) not null, "
                        "status int not null "
                        "); "
                        )){
                qDebug()<< "Table created";
            }
            query.prepare("INSERT INTO PersonFace (person_path, face_path, date_time, source, mask_st, status)"
                          " VALUES (?,?,?,?,?,?);");
            query.addBindValue(image_name+"person.png");
            query.addBindValue(image_name+"face.png");
            query.addBindValue(date_time);
            query.addBindValue(source);
            query.addBindValue(mask_status);
            query.addBindValue(0);
            query.exec();
        }
        else{
            QString face_path = "./captures/nomask/";
            QString obliq = "/";
            // QString format = "dd.MM.yyyy";
            QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            date_time = encodeString(date_time);
            QString at = "<at>";
            QString date = QDate::currentDate().toString("yyyy.MM.dd");
            QString img_path = face_path+date+obliq;
            QString image_name = img_path+at+QTime::currentTime().toString();

            QDir myDir;
            if(!myDir.exists(date)) //if no directory so create directory
            {
                myDir.mkpath(img_path);
                person.save(image_name+"person.png");
                face.save(image_name+"face.png");
            }

            QSqlQuery query;


            if (query.exec(
                        "CREATE TABLE PersonFace ( "
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "person_path VARCHAR(250) NOT NULL, "
                        "face_path VARCHAR(250) NOT NULL, "
                        "date_time DATETIME NOT NULL, "
                        "source int not null, "
                        "mask_st varchar(150) not null, "
                        "status int not null "
                        "); "
                        )){
                qDebug()<< "Table created";
            }
            query.prepare("INSERT INTO PersonFace (person_path, face_path, date_time, source, mask_st, status)"
                          " VALUES (?,?,?,?,?,?);");
            query.addBindValue(image_name+"person.png");
            query.addBindValue(image_name+"face.png");
            query.addBindValue(date_time);
            query.addBindValue(source);
            query.addBindValue(mask_status);
            query.addBindValue(0);
            query.exec();
        }

    }
}

void MainWindow::dataInsertIntoDbPerson(QPixmap person, int source)
{
    qDebug() << "dataInsertIntoDbPerson call";

    QString face_path = "./captures/person/";
    QString obliq = "/";
    // QString format = "dd.MM.yyyy";
    QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    date_time = encodeString(date_time);
    QString at = "<at>";
    QString date = QDate::currentDate().toString("yyyy.MM.dd");
    QString img_path = face_path+date+obliq;
    QString image_name = img_path+at+QTime::currentTime().toString()+".png";

    QDir myDir;
    if(!myDir.exists(date)) //if no directory so create directory
    {
        myDir.mkpath(img_path);
        person.save(image_name);
    }

    if(connectionDB()){
        QSqlQuery query;


        if (query.exec(
                    "CREATE TABLE Person ( "
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "person_path VARCHAR(250) NOT NULL, "
                    "date_time DATETIME NOT NULL, "
                    "source int not null, "
                    "); "
                    )){
            qDebug()<< "person Table created";
        }
        query.prepare("INSERT INTO Person (person_path, date_time, source)"
                      " VALUES (?,?,?);");
        query.addBindValue(image_name);
        query.addBindValue(date_time);
        query.addBindValue(source);
        query.exec();
    }
}

void MainWindow::dataInsertIntoDbFace(QPixmap face, int source, QString nam)
{
    qDebug() << "dataInsertIntoDbFace call";

    QString face_path = "./captures/face/";
    QString obliq = "/";
    // QString format = "dd.MM.yyyy";
    QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    date_time = encodeString(date_time);
    QString at = "<at>";
    QString date = QDate::currentDate().toString("yyyy.MM.dd");
    QString img_path = face_path+date+obliq;
    QString image_name = img_path+nam+at+QTime::currentTime().toString()+".png";

    QDir myDir;
    if(!myDir.exists(date)) //if no directory so create directory
    {
        myDir.mkpath(img_path);
        face.save(image_name);
    }

    if(connectionDB()){

        QSqlQuery query;

        qDebug()<< "connectiondb true";

        if (query.exec(
                    "CREATE TABLE Face ( "
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "face_path VARCHAR(250) NOT NULL, "
                    "date_time DATETIME NOT NULL, "
                    "source int not null, "
                    "); "
                    )){
            qDebug()<< "face Table created";
        }
        query.prepare("INSERT INTO Face (face_path, date_time, source)"
                      " VALUES (?,?,?);");
        query.addBindValue(image_name);
        query.addBindValue(date_time);
        query.addBindValue(source);
        query.exec();
    }

}

void MainWindow::dataInsertIntoDb(QPixmap person, QPixmap face, int source, QString mask_status, QString color_status, QString gender, int age, int total_list_of_person_who_violate_distance_rule)
{
    if(connectionDB()){
        QString face_path = "/media/sigmind/sdcard/all/";
        QString obliq = "/";
        // QString format = "dd.MM.yyyy";
        QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        date_time = encodeString(date_time);
        QString at = "<at>";
        QString date = QDate::currentDate().toString("yyyy.MM.dd");
        QString img_path = face_path+date+obliq;
        QString image_name = img_path+at+QTime::currentTime().toString();

        QDir myDir;
        if(!myDir.exists(date)) //if no directory so create directory
        {
            myDir.mkpath(img_path);
            person.save(image_name+"person.png");
            face.save(image_name+"face.png");
        }

        QSqlQuery query;

        if (query.exec(
                    "CREATE TABLE PersonFace ( "
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "person_path VARCHAR(250) NOT NULL, "
                    "face_path VARCHAR(250) NOT NULL, "
                    "date_time DATETIME NOT NULL, "
                    "source int not null, "
                    "distance_vio int not null, "
                    "gender varchar(150) not null, "
                    "mask_st varchar(150) not null, "
                    "age int not null, "
                    "color varchar(50) not null"
                    "); "
                    )){
            qDebug()<< "Table created";
        }
        query.prepare("INSERT INTO PersonFace (person_path, face_path, date_time, source, distance_vio, gender, mask_st, age, color)"
                      " VALUES (?,?,?,?,?,?,?,?,?);");
        query.addBindValue(image_name+"person.png");
        query.addBindValue(image_name+"face.png");
        query.addBindValue(date_time);
        query.addBindValue(source);
        query.addBindValue(total_list_of_person_who_violate_distance_rule);
        query.addBindValue(gender);
        query.addBindValue(mask_status);
        query.addBindValue(age);
        query.addBindValue(color_status);
        query.exec();
    }
}
void MainWindow::addLPR_triggered(QPixmap pic, int indx)
{
    // worker->abort();
    //thread->wait(); // If the thread is not running, this will immediately return.
    QString enc = "receive tileLP";
    //    worker->requestWork();

    //    emit requestUpdateLPR(pic, enc, indx);
    // QString trig = "Add LPR triggered";
    // facesWindow->addLPR(pic, trig, indx);
}

void MainWindow::addFR(QPixmap ma_pic,QPixmap pic, QString str, int indx, double confidence, /*dlib::matrix<float,(long)0,(long)1> pic_template*/ int fpsValue, int rec_or_not, QString gender, int age, QString color, int person_list_check)
{
    name_and_source.first = str;
    name_and_source.second = indx;

    if(person_list_check == 0){
        if(QString::compare("Unknown", str) == 0 || QString::compare("clear", str) == 0){
            ++unmask;
        }
        //         facesWindow->addUniqueFace(ma_pic, pic, str, indx, pic_template, confidence, fpsValue, rec_or_not, gender,age, color);
    }/*else if(person_list_check == 1){
        Notification *newNoti= new Notification(ma_pic.scaledToHeight(140), color, "", QString::number(indx), pic.scaledToHeight(140), "", "");
        lpr_emailController->addNotLPR(newNoti);
    }*/
}
//addFR(QPixmap,QPixmap,QString,int, double, dlib::matrix<float,(long)0,(long)1>, int, int, QString, int, QString, int, int)
void MainWindow::addFR(QPixmap ma_pic,QPixmap pic, QString str, int indx, double confidence, dlib::matrix<float,(long)0,(long)1> pic_template, int fpsValue, int rec_or_not, QString gender, int age, QString color, int person_list_check, int sz)
{
    qDebug() << "dddddddddddddddddddddddddddddddddddddddddddd";
    name_and_source.first = str;
    name_and_source.second = indx;

    if(person_list_check == 0){
        if(QString::compare("Unknown_mask", str) == 0 || QString::compare("clear", str) == 0){
            ++unmask;
        }
        //  facesWindow->addUniqueFace(ma_pic, pic, str, indx, pic_template, confidence, fpsValue, rec_or_not, gender,age, color);
        //        qDebug() << ">>>>>>>>>>>>>>>>>>>>> <<<<<<<<<<<<<<<<<<<<<<<<< "<< indx;
        dataInsertIntoDb(ma_pic, pic, indx, str, color, gender, age, sz);
    }
}

void MainWindow::addFR(QPixmap ma_pic, QPixmap pic, QPixmap face, float distance)
{
    ++distance_vio;
    Notification *newNoti= new Notification(ma_pic.scaledToHeight(140), "Distance: "+QString::number(distance, 'f', 2), "", 0, pic.scaledToHeight(140), "", "");
    lpr_emailController->addNotLPR(newNoti);

    QString lpr_path_for_first = "./captures/Object/";
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    QDir myDir;
    if(!myDir.exists(lpr_path_for_first)){
        myDir.mkpath(lpr_path_for_first);
    }
    ma_pic.save(lpr_path_for_first+time+"1.png");
    pic.save(lpr_path_for_first+time+"2.png");
    face.save(lpr_path_for_first+time+"3.png");
}

void MainWindow::addFR(QPixmap ma_pic, QPixmap pic, QPixmap face, float distance, int source, QString mask_status, QString color_status, int total_violate_distance)
{
    ++distance_vio;
    Notification *newNoti= new Notification(ma_pic.scaledToHeight(140), "Distance: "+QString::number(distance, 'f', 2), "", 0, pic.scaledToHeight(140), "", "");
    lpr_emailController->addNotLPR(newNoti);


    dataInsertIntoDb(ma_pic, pic, face, source, distance, mask_status, color_status, total_violate_distance);
    qDebug() << "Final data insertion ...................... "<< source << " " << mask_status << " " << color_status << " " << total_violate_distance;
}

void MainWindow::dataInsertIntoDb(QPixmap person, QPixmap close_dis_person, QPixmap face, int source_index, float distance, QString mask_status, QString color_status, int total_close_person){
    QString lpr_path_for_first = "./captures/Object/";
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    QDir myDir;
    if(!myDir.exists(lpr_path_for_first)){
        myDir.mkpath(lpr_path_for_first);
    }
    person.save(lpr_path_for_first+time+"1.png");
    close_dis_person.save(lpr_path_for_first+time+"2.png");
    face.save(lpr_path_for_first+time+"3.png");

    QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    date_time = encodeString(date_time);

    QSqlQuery query;

    if (query.exec(
                "CREATE TABLE PersonPersonFace ( "
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "person_path VARCHAR(250) NOT NULL, "
                "close_person_path VARCHAR(250) NOT NULL, "
                "face_path VARCHAR(250) NOT NULL, "
                "date_time DATETIME NOT NULL, "
                "source int not null, "
                "distance int not null, "
                "mask_st varchar(150) not null, "
                "color_st varchar(150) not null, "
                "tot_close_per int not null "
                "); "
                )){
        qDebug()<< "Table created";
    }
    query.prepare("INSERT INTO PersonPersonFace (person_path, close_person_path,face_path, date_time, source, distance, mask_st, color_st, tot_close_per)"
                  " VALUES (?,?,?,?,?,?,?,?,?);");
    query.addBindValue(lpr_path_for_first+time+"1.png");
    query.addBindValue(lpr_path_for_first+time+"2.png");
    query.addBindValue(lpr_path_for_first+time+"3.png");
    query.addBindValue(date_time);
    query.addBindValue(source_index);
    query.addBindValue(distance);
    query.addBindValue(mask_status);
    query.addBindValue(color_status);
    query.addBindValue(total_close_person);
    query.exec();
}

// picture split and get two part for folder writting
void MainWindow::addLP(QPixmap first_pic, QString first_str, QPixmap second_pic, QString second_str)
{
    /// bangla to english
    //    second_str = encodeStringForLPRtrainData(second_str);

    qDebug() << "first_str == " << first_str<<" second_str digit == " << second_str;
    QRegExp re("^[0-9]+$");  // a digit (\d), zero or more times (*)

    /// for only full image
    /*
    if (re.exactMatch(second_str)){
        qDebug() << "second_str == " << second_str;

        /// this device path
        QString lpr_path_for_first = "./captures/license_plates/";

        QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
        QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");

        QDir myDir;
        if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
            myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
        }
        QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.gt.txt");
        if(!input_file.open(QFile::WriteOnly)){
            qDebug() << "Error opening for write: " << input_file.errorString();
            return;
        }
        QTextStream outStream(&input_file);
        outStream << first_str;
        //outStream << str.mid(0, str.indexOf("\n"));
        input_file.close();
        first_pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");// pic write
//        second_pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"3.png");// pic write

//        QFile input_file4(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"4.gt.txt");
//        if(!input_file4.open(QFile::WriteOnly)){
//            qDebug() << "Error opening for write: " << input_file4.errorString();
//            return;
//        }
//        QTextStream outStream4(&input_file4);
//        outStream4 << second_str;
//        //outStream << str.mid(0, str.indexOf("\n"));
//        input_file4.close();
    }
*/



    /// for first and second half crop image

    //    if (re.exactMatch(second_str)){
    qDebug() << "second_str == " << second_str;

    /// this device path
    QString lpr_path_for_first = "./captures/license_plates/";

    QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
    QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");

    QDir myDir;
    if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
        myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
    }
    //        QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.gt.txt");
    QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.gt.txt");
    if(!input_file.open(QFile::WriteOnly)){
        qDebug() << "Error opening for write: " << input_file.errorString();
        return;
    }
    QTextStream outStream(&input_file);
    //        if(first_str != ""){
    if(first_str.QString::isEmpty() == false){
        qDebug() << "first_str not null: " << first_str;
        outStream << first_str;
    }

    //outStream << str.mid(0, str.indexOf("\n"));
    input_file.close();
    first_pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");// pic write
    //        second_pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"3.png");// pic write
    second_pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png");// pic write

    //        QFile input_file4(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"4.gt.txt");
    QFile input_file4(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.gt.txt");
    if(!input_file4.open(QFile::WriteOnly)){
        qDebug() << "Error opening for write: " << input_file4.errorString();
        return;
    }
    QTextStream outStream4(&input_file4);
    //        if(second_str != ""){
    if(second_str.QString::isEmpty() == false){
        qDebug() << "second_str not null: " << second_str;
        outStream4 << second_str;
    }
    //outStream << str.mid(0, str.indexOf("\n"));
    input_file4.close();
    //    }



}


QString MainWindow::encodeStringForLPRtrainData(QString data)
{
    QByteArray string = data.toUtf8();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString encodedString_main = codec->toUnicode(string);
    int l = encodedString_main.length();
    QString encodedString;

    //    qDebug()<<"l = "<<l<<" encodedString = "<<encodedString;

    //    int len = d.length();
    //qDebug()<<"string = "<<d<<" length = "<<len;
    int j=0;
    for(int i=0;i<l;i++){
        if(encodedString_main[i] == "\u09e6")
        {
            //            encodedString[j++] = '0';
            encodedString.append('0');

            /*
                qDebug()<<encodedString[i]<<" "<<"0";*/
        }


        else if(encodedString_main[i] == "\u09e7")
        {
            //            encodedString[j++] = '1';
            encodedString.append('1');
        }
        //qDebug()<<encodedString[i]<<" "<<"1";

        else if(encodedString_main[i] == "\u09e8")
        {
            //            encodedString[j++] = '2';
            encodedString.append('2');
        }
        // qDebug()<<encodedString[i]<<" "<<"2";

        else if(encodedString_main[i] == "\u09e9")
        {
            //            encodedString[j++] = '3';
            encodedString.append('3');
        }
        //qDebug()<<encodedString[i]<<" "<<"3";

        else if(encodedString_main[i] == "\u09ea")
        {
            //            encodedString[j++] = '4';
            encodedString.append('4');
        }
        //qDebug()<<encodedString[i]<<" "<<"4";

        else if(encodedString_main[i] == "\u09eb")
        {
            //            encodedString[j++] = '5';
            encodedString.append('5');
        }
        // qDebug()<<encodedString[i]<<" "<<"5";

        else if(encodedString_main[i] == "\u09ec")
        {
            //            encodedString[j++] = '6';
            encodedString.append('6');
        }
        //qDebug()<<encodedString[i]<<" "<<"6";

        else if(encodedString_main[i] == "\u09ed")
        {
            //            encodedString[j++] = '7';
            encodedString.append('7');
        }
        //qDebug()<<encodedString[i]<<" "<<"7";

        else if(encodedString_main[i] == "\u09ee")
        {
            //            encodedString[j++] = '8';
            encodedString.append('8');
        }
        //qDebug()<<encodedString[i]<<" "<<"8";

        else if(encodedString_main[i] == "\u09ef")
        {
            //            encodedString[j++] = '9';
            encodedString.append('9');
        }else{
            continue;
        }
        //qDebug()<<encodedString[i]<<" "<<"9";
        //        else {
        //            qDebug()<<encodedString[i];
        //        }

    }
    qDebug() << "encodedString = " << encodedString;
    return encodedString;
}



void MainWindow::cleanSpecificRecordVideo()
{
    recordDeleteTimer->stop();

    QStringList colmname;
    //QDir directory("/home/sigmind/Videos/records");// given default directory
    QDir directory(smart_record_video_save_directory);// dynamic dir from user

    // /home/sigmind/Basedul_islam/WC-Tegra-DS/alarm-audio-files/cam1.mp3

    QStringList videos = directory.entryList(QStringList() << "*.mp4" <<"*.MP4"<<"*.mkv"<<"*.MKV",QDir::Files);
    foreach(QString filename, videos) {
        //qDebug() <<"filename:"<< filename;
        colmname<<filename;
    }

    qDebug()<<"total record list size: "<<colmname.size();

    for(int i = 0; i < colmname.size(); i++){
        qDebug()<<"i = "<<i<<" : "<<colmname.at(i);
        //        QRegExp R_date("(0[1-9]|[12][0-9]|3[01]{1,2})-(0[1-9]|[12]{1,2})-(19[0-9][0-9]|20[0-9][0-9])");
        QRegExp R_date("(19[0-9][0-9]|20[0-9][0-9])(0[1-9]|[12]{1,2})(0[1-9]|[12][0-9]|3[01]{1,2})");
        QStringList myList;
        int pos = 0;
        while((pos = R_date.indexIn(colmname.at(i), pos)) != -1){
            myList << R_date.cap(0);
            qDebug() << "date: " << R_date.cap(0);
            pos += R_date.matchedLength();
            stor_date.insert(R_date.cap(0));
        }
        myList.clear();
    }
    qDebug()<<"unique days count set size:"<<stor_date.size();
    QString date_dir = smart_record_video_save_directory;

    if(stor_date.size() > how_may_days){// days =30 default

        QString store_first_date;
        QSet<QString>::const_iterator i = stor_date.constBegin();
        while (i != stor_date.constEnd()) {// take first date here and quit loop
            //qDebug() <<"first date"<< *i;
            store_first_date = *i;
            ++i;
            break;
        }
        qDebug()<<"store_first_date:"<<store_first_date;

        for(int j = 0; j < colmname.size(); j++){// delete record files
            QString temp = QString(colmname.at(j));
            QString match = QString(store_first_date);

            if(temp.contains(match)){
                qDebug() <<"match value: "<< temp.contains(match);
                qDebug()<<"delete "<<date_dir+colmname.at(j);
                ///home/sigmind/Videos/records/watchcam_0_00000_20200731-085525_20178 (3rd copy).mp4
                //                QFile bf( colmname.at(j) ); // delete video from folder
                //                bf.remove();
                //                bf.flush();

                QFile::remove(date_dir+colmname.at(j));
            }

        }
    }

    colmname.clear();
    stor_date.clear();

    //3600000 -> means 1 minute
    recordDeleteTimer->start(18000000);// 5 minute

}

//void MainWindow::addLP(QPixmap main_pic, QPixmap pic, QString str, int indx, QString color)
//{

//    qDebug() << "addLp Notificaiton and lp "<<str<<", "<<color;

//    ////    QPixmap pict =  QPixmap::fromImage(QImage((unsigned char*) main_pic.data, main_pic.cols, main_pic.rows, QImage::Format_RGB888));
////        QString lpr_path_for_first = "./captures/Object/";
////        QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
////        QDir myDir;
////        if(!myDir.exists(lpr_path_for_first)){
////            myDir.mkpath(lpr_path_for_first);
////        }
////        main_pic.save(lpr_path_for_first+time+"1.png");
//    ////    pict =  QPixmap::fromImage(QImage((unsigned char*) pic.data, pic.cols, pic.rows, QImage::Format_RGB888));
////        pic.save(lpr_path_for_first+time+"2.png");

//    Notification *newNoti= new Notification(main_pic.scaledToHeight(140), "abc", "", QString::number(indx), pic.scaledToHeight(140), "", "");
//    //    facesWindow->uniqueLicencePlateShowInTiles(pic, "abc", indx, color);
//    lpr_emailController->addNotLPR(newNoti);
//}


// for LOCC
void MainWindow::addLP(QPixmap main_pic, QPixmap pic, QString str, int indx, QString color)
{

    //    "ঢাঁকামেট্রোগ\n১৪-৭৩১৭\n\n \n"
    qDebug() << "addLP =============**************** lp: " << str << " " << str.length();

    qDebug() << "Now return from worker thread show notificaion";

    QString trig = "Add LPR triggered";
    std::stringstream plateStream;
    std::wstring plateID = str.toStdWString().c_str();
    int i=0;



    for (auto &letter : plateID) {
        if (letter == L'৮') {

            plateStream << "8";
        }
        else if (letter == L'৩') {

            plateStream << "3";
        }
        else if (letter == L'৭') {

            plateStream << "7";
        }
        else if (letter == L'৭') {

            plateStream << "7";
        }
        else if (letter == L'৬') {

            plateStream << "6";
        }
        else if (letter == L'৯') {

            plateStream << "9";
        }
        else if (letter == L'৫') {

            plateStream << "5";
        }
        else if (letter == L'৪') {

            plateStream << "4";
        }
        else if (letter == L'২') {

            plateStream << "2";
        }
        else if (letter == L'১') {

            plateStream << "1";
        }
        else if (letter == L'০') {

            plateStream << "0";
        }


        else if (letter == L'ক') {

            plateStream << "Ka-";
        }
        else if (letter == L'ঢ') {

            plateStream << "Dha";
        }
        else if (letter == L'ম') {

            plateStream << "Me";
        }
        else if (letter == L'ট') {

            plateStream << "Tro-";
        }
        i++;
    }


    std::string plateData = plateStream.str();
    QString qstr = QString::fromStdString(plateData);


    //    QByteArray encodedString = qstr.toUtf8(); // some ISO 8859-5 encoded text
    //    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-5");
    //    QString string = codec->toUnicode(encodedString);

    QString sub_qstr = qstr.mid(qstr.length()-6, 6);
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)

    QString take_first_two_digit = qstr.mid((qstr.length()-6+(6 - sub_qstr.length())), 2);
    //qDebug() <<" str:"<<qstr<< " sub_qstr value>>>"<< sub_qstr<<" teststr"<<take_first_two_digit;

    /// for bottom lp known, unknown all show
    //     unique_lp_to_main_window(pic, sub_qstr, int, int, int, double, int, QString, int);
    //unique_lp_to_main_window(pic, sub_qstr, 1, 1, 1, 51.07, 1, "lp", 1);

    if (re.exactMatch(sub_qstr) == true){              // Check for last 6 digits
        if(sub_qstr.length() >= 1){
            qDebug() << "Digit check start = " << sub_qstr;

            //            Notification *newNoti= new Notification(main_pic.scaledToHeight(140), "Dhaka Ka 21-"+sub_qstr, color, QString::number(indx), pic.scaledToHeight(140), "", "");
            //            lpr_emailController->addNotLPR(newNoti);
            //            tilerdisplayWindow->only_uniqueFace_show_inTiles(pic, "Dhaka", indx);
            //            tilerdisplayWindow->addFR(main_pic, "Dhaka", indx);

            if(!(str.mid(0, str.indexOf("\n")).isEmpty())){

                QString lpr_trs = lprBanglaToEnglishTransform(str.mid(0, str.indexOf("\n")));
                //                qDebug()<<"ok sabbir";
                //                QString lpr_trs = str.mid(0, str.indexOf("\n"));// ja ache tay store kora hoyse
                QString lpr_full_origin = str.mid(0, str.indexOf("\n"));

                QString scrap_last_char = lpr_full_origin.mid(lpr_full_origin.length()-1, lpr_full_origin.length());
                QString singleLastLett = singleCharLprBangToEng(scrap_last_char);

                qDebug() << "full lpr str: " <<lpr_full_origin<<" lpr_trs bangla to eng : "<<lpr_trs<<" and length : "<< lpr_full_origin.length()
                         <<" "<<scrap_last_char<<" convert eng : "<<singleLastLett<<"\n";

                //                if(lpr_trs == "Bogura"){
                //                lpr_trs = "Dhaka";///default
                //                }

                //QString singleLastLett = singleCharLprBangToEng(str.mid(0, str.indexOf("\n")));
                //                singleLastLett =  "DA"  sub_qstr "278006"
                //                qDebug() << "singleLastLett = " << singleLastLett<<"\n";
                qDebug()<<" sub_qstr digit: "<< sub_qstr;

                //                uniqLpSet.insert(lpr_trs+" "+singleLastLett+" "+sub_qstr);
                //                if(uniqLpSet.size() > 1000){
                //                    uniqLpSet.clear();
                //                }
                //                if(uniqLpSet.size() > uniqLpChecker){
                //                    uniqLpChecker = uniqLpSet.size();
                //                    Notification *newNotif= new Notification(main_pic.scaledToHeight(140), lpr_trs+" "+singleLastLett+" "+sub_qstr, "", QString::number(indx), pic.scaledToHeight(140), "", "");
                //                    uniqueLpShowInLeftNotif(newNotif, "!"+lpr_trs+" "+singleLastLett+" "+take_first_two_digit);

                //                }

                int flag_sus_lpr = 0;

                qDebug() << "lpr_trs "<<lpr_trs<<" lpr_trs.length: "<<lpr_trs.length()<<" sub_qstr:"<<sub_qstr;

                //                if(!lpr_trs.isEmpty() && !singleLastLett.isEmpty() && !sub_qstr.isEmpty()){// jodi empty na hoy
                //                if(!lpr_trs.isEmpty() && lpr_trs.length() >=5 && !sub_qstr.isEmpty()){// jodi empty na hoy
                //                if(!lpr_trs.isEmpty() && lpr_trs.length() >=0 && !sub_qstr.isEmpty()){// locc
                if( lpr_trs.length() >=2  ){// locc
                    //                    QSqlQuery retrive_table_data;

                    //                    if(retrive_table_data.exec("select * from given_lpr;")){// table name is given_lpr

                    //                        while(retrive_table_data.next()){

                    //                            QString number_plate = retrive_table_data.value(1).toString();
                    //                            number_plate = number_plate.mid(number_plate.length()-6, 6);
                    qDebug() << "valid lpr";

                    //                            if(QString::compare(sub_qstr, number_plate) == 0 || number_plate.contains(sub_qstr) == true || sub_qstr.contains(number_plate) == true){


                    flag_sus_lpr = 1;

                    //                                QString lpr_path_for_first = "/media/sigmind/sdcard/captures/license_plates/";
                    //                        QString lpr_path_for_first = "./captures/license_plates/";

//                    QString lpr_path_for_first = "./captures/license_plates/";
                    QString lpr_path_for_first = "/mnt/watchcam/captures/license_plates/";

                    QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
                    QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");

                    QDir myDir;
                    if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
                        myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
                    }

                    QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.txt");
                    if(!input_file.open(QFile::WriteOnly)){
                        qDebug() << "Error opening for write: " << input_file.errorString();
                        return;
                    }
                    QTextStream outStream(&input_file);

                    outStream << lpr_trs+" "+singleLastLett+" "+sub_qstr;
                    input_file.close();

                    pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");// pic write
                    main_pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png");// pic write

                    detectedLpToDb(lpr_trs+" "+singleLastLett+" "+sub_qstr, encodeString(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")), color, lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png", lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");

                    //                                Notification *newNoti= new Notification(main_pic.scaledToHeight(140), lpr_trs+" "+singleLastLett+" "+sub_qstr, color, QString::number(indx), pic.scaledToHeight(140), "", "");
                    //                                facesWindow->uniqueLicencePlateShowInTiles(pic, lpr_trs+singleLastLett+sub_qstr, indx, color);

                    //                                uniqLpSet.insert(lpr_trs+" "+singleLastLett+" "+sub_qstr);

                    qDebug()<<"lpr color inside addLP : "<<color;

                    //                    Notification *newNoti= new Notification(main_pic.scaledToHeight(140), lpr_trs +"-"+singleLastLett+" "+sub_qstr, color, QString::number(indx), pic.scaledToHeight(140), "", "");
                    Notification *newNoti= new Notification(main_pic, lpr_trs +"-"+singleLastLett+" "+sub_qstr, color, QString::number(indx), pic, "", "");

                    //Notification *newNoti= new Notification(main_pic.scaledToHeight(140), "Dhaka", color, QString::number(indx), pic.scaledToHeight(140), "", "");

                    /// recent added by Johurul for show the lp and car

                    tilerdisplayWindow->only_uniqueFace_show_inTiles( pic, pic, lpr_trs +"-"+singleLastLett+" "+sub_qstr, indx, "");
                    tilerdisplayWindow->addFR(main_pic, lpr_trs +"-"+singleLastLett+" "+sub_qstr, indx);


                    //                    facesWindow->uniqueLicencePlateShowInTiles(pic, lpr_trs+sub_qstr, indx, color);
                    //                    facesWindow->addFR(pic, lpr_trs+sub_qstr, indx);
                    //                    facesWindow->detectedLpShowInTiles(main_pic, lpr_trs+sub_qstr, indx, color);

                    cker = cker+1;
                    uniqLpSet.insert(lpr_trs +"-"+singleLastLett+" "+sub_qstr+QString::number(cker));
                    qDebug()<<"uniqLpSet size : "<<uniqLpSet.size();
                    if(uniqLpSet.size() > 1000){
                        lpr_emailController->addNotLPR(newNoti);
                        uniqLpSet.clear();
                        uniqLpChecker = 0;
                    }
                    if(uniqLpSet.size() > uniqLpChecker){
                        uniqLpChecker = uniqLpSet.size();
                        lpr_emailController->addNotLPR(newNoti);
                    }


                }
                // not match with db
                if(flag_sus_lpr == 0){//zero kore dite hobe
                    //                            QString lpr_path_for_first = "/media/sigmind/sdcard/captures/Suspect_license_plates/";
                    //                        QString lpr_path_for_first = "./captures/Suspect_license_plates/";
                    QString lpr_path_for_first = "/mnt/nvme0n1p1/captures/Suspect_license_plates/";
                    QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
                    QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
                    /*
                    QDir myDir;
                    if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
                        myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
                    }

                    QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.txt");
                    if(!input_file.open(QFile::WriteOnly)){
                        qDebug() << "Error opening for write: " << input_file.errorString();
                        return;
                    }
                    QTextStream outStream(&input_file);
                    //                    outStream << lpr_trs+" "+singleLastLett+" "+sub_qstr;
                    //                    outStream << lpr_trs+"-"+singleLastLett+" "+sub_qstr;
                    input_file.close();*/

                    //                    pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");// pic write
                    //                    main_pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png");// pic write

                    qDebug()<<"suspect lpr";

                    //                            detectedLpToDb(lpr_trs+" "+singleLastLett+" "+sub_qstr, encodeString(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")), color, lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png", lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");

                    //                            Notification *newNoti= new Notification(main_pic, "!"+lpr_trs+" "+singleLastLett+" "+sub_qstr, color, QString::number(indx), pic.scaledToHeight(140), "", "");
                    //                            facesWindow->uniqueLicencePlateShowInTiles(pic, lpr_trs+singleLastLett+sub_qstr, indx, color);

                    //                            uniqLpSet.insert(lpr_trs+" "+singleLastLett+" "+sub_qstr);

                    Notification *newNoti= new Notification(main_pic.scaledToHeight(140), lpr_trs+" "+sub_qstr, color, QString::number(indx), pic.scaledToHeight(140), "", "");
                    //                    facesWindow->uniqueLicencePlateShowInTiles(pic, lpr_trs+sub_qstr, indx, color);
                    //                    facesWindow->detectedLpShowInTiles(main_pic, lpr_trs+sub_qstr, indx, color);

                    //                    uniqLpSet.insert(lpr_trs+" "+sub_qstr);

                    //                    if(uniqLpSet.size() > 1000){
                    //                        uniqLpSet.clear();
                    //                    }
                    //                    if(uniqLpSet.size() > uniqLpChecker){
                    //                        uniqLpChecker = uniqLpSet.size();
                    //                        //                                lpr_emailController->addNotLPR(newNoti);//show monitor Right Side notif suspect lpr
                    //                        //uniqueLpShowInLeftNotif(newNoti, "!"+lpr_trs+" "+singleLastLett+" "+take_first_two_digit);
                    //                    }
                }


            }



        }
    }




    //        }



    //    }

    //    bool num_check = true;
    //    for(int i = 0; i < sub_qstr.length(); i++){
    //        if(sub_qstr.at(i) >= 0 &&  sub_qstr.at(i) <=9 ){
    //            //qDebug() << "(int) sub_qstr.at(i) = " <<  sub_qstr.at(i);
    //        }
    //    }

    //    QString date_time_db =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //    date_time_db = encodeString(date_time_db);
    //    QString img_path;
    //    QDir myDir;
    //    if(!myDir.exists(lpr_path+"/"+date)){
    //        myDir.mkpath(lpr_path+"/"+date);
    //        img_path = lpr_path+"/"+date+"/"+qstr+"_"+QTime::currentTime().toString()+".png";
    //        QFile file(img_path);
    //        file.open(QIODevice::WriteOnly);
    //        pic.save(&file, "PNG");
    //    }else{
    //        myDir.mkpath(lpr_path+"/"+date);
    //        img_path = lpr_path+"/"+date+"/"+qstr+"_"+QTime::currentTime().toString()+".png";
    //        QFile file(img_path);
    //        file.open(QIODevice::WriteOnly);
    //        pic.save(&file, "PNG");
    //    }
    ////    QFile file(lpr_path+qstr);
    ////    file.open(QIODevice::WriteOnly);
    ////    pic.save(&file, "PNG");

    //    std::string plateRequest = LPR.toUtf8().constData();

    //    //           if(plateData.find(plateRequest) != std::string::npos) {
    //    //               //makeNotification(pic, qstr, indx);
    //    //               emit notifyLPR(pic, qstr, indx);
    //    //           }
    //    //facesWindow->addObject(pic, str, indx);
    //    //    facesWindow->addLPR(pic, str, indx);



    //    Notification *newNoti= new Notification(str, "", QString::number(indx), pic.scaledToHeight(140), "", "");
    //    lpr_emailController->addNotLPR(newNoti);
}
//*/


//void MainWindow::addLP(QPixmap main_pic, QPixmap pic, QString str, int indx, QString color)
//{

//    //    QSqlQuery qLp;
//    //    if (qLp.exec(
//    //                "CREATE TABLE LPR ( "
//    //                "Id int not null primary key autoincrement, "
//    //                "number_plate TEXT)"
//    //                "; "
//    //                )){
//    //        ////qDebug()<< "Table created";
//    //    }

//    //qDebug() << "addLP =============**************** " << str << " " << str.length() << " " << str.mid(0, str.indexOf("\n"));




//    QString trig = "Add LPR triggered";
//    std::stringstream plateStream;
//    std::wstring plateID = str.toStdWString().c_str();
//    int i=0;



//    for (auto &letter : plateID) {
//        if (letter == L'৮') {

//            plateStream << "8";
//        }
//        else if (letter == L'৩') {

//            plateStream << "3";
//        }
//        else if (letter == L'৭') {

//            plateStream << "7";
//        }
//        else if (letter == L'৭') {

//            plateStream << "7";
//        }
//        else if (letter == L'৬') {

//            plateStream << "6";
//        }
//        else if (letter == L'৯') {

//            plateStream << "9";
//        }
//        else if (letter == L'৫') {

//            plateStream << "5";
//        }
//        else if (letter == L'৪') {

//            plateStream << "4";
//        }
//        else if (letter == L'২') {

//            plateStream << "2";
//        }
//        else if (letter == L'১') {

//            plateStream << "1";
//        }
//        else if (letter == L'০') {

//            plateStream << "0";
//        }


//        else if (letter == L'ক') {

//            plateStream << "Ka-";
//        }
//        else if (letter == L'ঢ') {

//            plateStream << "Dha";
//        }
//        else if (letter == L'ম') {

//            plateStream << "Me";
//        }
//        else if (letter == L'ট') {

//            plateStream << "Tro-";
//        }
//        i++;
//    }


//    std::string plateData = plateStream.str();
//    QString lpr_path = "./captures/license_plates/";
//    QString date =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//    QString qstr = QString::fromStdString(plateData);

//    //    Notification *newNoti= new Notification(main_pic.scaledToHeight(140), qstr, "", QString::number(indx), pic.scaledToHeight(140), "", "");
//    ////    facesWindow->uniqueLicencePlateShowInTiles(pic, lpr_trs+singleLastLett+sub_qstr, indx, color);
//    //    lpr_emailController->addNotLPR(newNoti);

//    //    QByteArray encodedString = qstr.toUtf8(); // some ISO 8859-5 encoded text
//    //    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-5");
//    //    QString string = codec->toUnicode(encodedString);
//    //qDebug() << "LPR ==== ++++ "<< qstr;
//    QString sub_qstr = qstr.mid(qstr.length()-6, 6);
//    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)

//    if (re.exactMatch(sub_qstr) == true){              // Check for last 6 digits
//        if(sub_qstr.length() >= 3/* && (qstr.contains(sub_qstr) == true || sub_qstr.contains(qstr) == true )*/){

//            //qDebug() << "Digit check start = " << sub_qstr;

//            //            QString lpr_path_for_first = "./captures/license_plates/";
//            //            QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//            //            QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
//            //            QDir myDir;
//            //            if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//            //                myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//            //            }
//            //            QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.txt");
//            //            if(!input_file.open(QFile::WriteOnly)){
//            //                //qDebug() << "Error opening for write: " << input_file.errorString();
//            //                return;
//            //            }
//            //            QTextStream outStream(&input_file);
//            //            outStream << str;
//            //            //outStream << str.mid(0, str.indexOf("\n"));
//            //            input_file.close();
//            //            pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");// pic write

//            //        int l = pic.rect().left();
//            //        int t = pic.rect().top();
//            //        int r = pic.rect().right();
//            //        int b = pic.rect().bottom();
//            //        QPixmap first_half = pic.copy(0, 0, pic.width(), pic.height()/2);
//            //        first_half.save("/home/sigmind/Desktop/based.png");

//            /*for(int mn = 0 ; mn < 4; mn++){
//                switch(mn){
//                case 0:
//                {
//                    QString lpr_path_for_first = "./captures/license_plates/";
//                    QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                    QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
//                    QDir myDir;
//                    if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                        myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                    }
//    //                QImage image(80, 30, QImage::Format_ARGB32_Premultiplied);
//    //                QPainter painter(&image);
//    //                painter.fillRect(image.rect(), Qt::white);
//    //                painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter,str.mid(0, str.indexOf("\n")));
//    //                image.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");
//                    QPixmap first_half = pic.copy(0, 0, pic.width(), pic.height()/2);
//                    first_half.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");
//                    //first_name = lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"/"+"1.png";
//                    break;
//                }

//                case 1:
//                {
//                    QString lpr_path_for_first = "./captures/license_plates/";
//                    QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                    QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
//                    QDir myDir;
//                    if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                        myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                    }
//                    QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.txt");
//                    if(!input_file.open(QFile::WriteOnly)){
//                        //qDebug() << "Error opening for write: " << input_file.errorString();
//                        return;
//                    }
//                    QTextStream outStream(&input_file);
//                    outStream << str.mid(0, str.indexOf("\n"));
//                    input_file.close();
//                    //first_text = lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"/"+"2.txt";
//                    break;
//                }
//                case 2:
//                {
//                    QString lpr_path_for_first = "./captures/license_plates/";
//                    QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                    QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
//                    QDir myDir;
//                    if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                        myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                    }
//    //                QImage image(80, 30, QImage::Format_ARGB32_Premultiplied);
//    //                QPainter painter(&image);
//    //                painter.fillRect(image.rect(), Qt::white);
//    //                painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter,str.mid(str.indexOf("\n")+1, str.length()));
//    //                image.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png");
//                    QPixmap first_half = pic.copy(0, pic.height()/2, pic.width(), pic.height());
//                    first_half.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png");
//                    //second_name = lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"/"+"3.png";
//                    break;
//                }
//                case 3:
//                {
//                    QString lpr_path_for_first = "./captures/license_plates/";
//                    QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                    QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
//                    QDir myDir;
//                    if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                        myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                    }
//                    QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.txt");
//                    if(!input_file.open(QFile::WriteOnly)){
//                        //qDebug() << "Error opening for write: " << input_file.errorString();
//                        return;
//                    }
//                    QTextStream outStream(&input_file);
//                    outStream << str.mid(str.indexOf("\n")+1, str.length());
//                    input_file.close();
//                    //second_text = lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"/"+"4.txt";
//                    break;
//                }
//                }
//            }*/

//            //            Notification *newNoti= new Notification(str, "", QString::number(indx), pic.scaledToHeight(140), "", "");
//            //            lpr_emailController->addNotLPR(newNoti);

//            if(!(str.mid(0, str.indexOf("\n")).isEmpty())){
//                QString lpr_trs = lprBanglaToEnglishTransform(str.mid(0, str.indexOf("\n")));
//                //qDebug() << "lpr_trs ==============  " << lpr_trs;
//                QString singleLastLett = singleCharLprBangToEng(str.mid(0, str.indexOf("\n")));
//                //qDebug() << "singleLastLett = " << singleLastLett;

//                if(!lpr_trs.isEmpty() && !singleLastLett.isEmpty()){


//                    QSqlQuery retrive_table_data;

//                    if(retrive_table_data.exec("select * from given_lpr;")){

//                        int flag_sus_lpr = 0;

//                        while(retrive_table_data.next()){

//                            QString number_plate = retrive_table_data.value(1).toString();
//                            number_plate = number_plate.mid(number_plate.length()-6, 6);
//                            //qDebug() << "number_plate = " << number_plate << " " << sub_qstr;

//                            if(QString::compare(sub_qstr, number_plate) == 0 || number_plate.contains(sub_qstr) == true || sub_qstr.contains(number_plate) == true){


//                                flag_sus_lpr = 1;

//                                QString lpr_path_for_first = "./captures/license_plates/";
//                                QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                                QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");

//                                QDir myDir;
//                                if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                                    myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                                }
//                                //                                QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.txt");
//                                //                                if(!input_file.open(QFile::WriteOnly)){
//                                //                                    //qDebug() << "Error opening for write: " << input_file.errorString();
//                                //                                    return;
//                                //                                }
//                                //                                QTextStream outStream(&input_file);
//                                //                                outStream << lpr_trs+" "+singleLastLett+" "+sub_qstr;
//                                //                                //outStream << str.mid(0, str.indexOf("\n"));
//                                //                                input_file.close();
//                                pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");// pic write
//                                main_pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png");// pic write

//                                detectedLpToDb(lpr_trs+" "+singleLastLett+" "+sub_qstr, encodeString(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")), color, lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png", lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");

//                                Notification *newNoti= new Notification(main_pic.scaledToHeight(140), lpr_trs+" "+singleLastLett+" "+sub_qstr, "", QString::number(indx), pic.scaledToHeight(140), "", "");
//                                facesWindow->uniqueLicencePlateShowInTiles(pic, lpr_trs+singleLastLett+sub_qstr, indx, color);
//                                lpr_emailController->addNotLPR(newNoti);


//                                break;

//                            }


//                            /*if(QString::compare(sub_qstr, number_plate) == 0 ){

//                                QString first_name, first_text, second_name, second_text;

//                                for(int mn = 0 ; mn < 4; mn++){
//                                    switch(mn){
//                                    case 0:
//                                    {
//                                        QString lpr_path_for_first = "./captures/license_plates/";
//                                        QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                                        QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
//                                        QDir myDir;
//                                        if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                                            myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                                        }
//                                        QImage image(80, 30, QImage::Format_ARGB32_Premultiplied);
//                                        QPainter painter(&image);
//                                        painter.fillRect(image.rect(), Qt::white);
//                                        painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter,str.mid(0, str.indexOf("\n")));
//                                        image.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");
//                                        //first_name = lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"/"+"1.png";
//                                        break;
//                                    }

//                                    case 1:
//                                    {
//                                        QString lpr_path_for_first = "./captures/license_plates/";
//                                        QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                                        QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
//                                        QDir myDir;
//                                        if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                                            myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                                        }
//                                        QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.txt");
//                                        if(!input_file.open(QFile::WriteOnly)){
//                                            //qDebug() << "Error opening for write: " << input_file.errorString();
//                                            return;
//                                        }
//                                        QTextStream outStream(&input_file);
//                                        outStream << str.mid(0, str.indexOf("\n"));
//                                        input_file.close();
//                                        //first_text = lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"/"+"2.txt";
//                                        break;
//                                    }
//                                    case 2:
//                                    {
//                                        QString lpr_path_for_first = "./captures/license_plates/";
//                                        QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                                        QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
//                                        QDir myDir;
//                                        if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                                            myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                                        }
//                                        QImage image(80, 30, QImage::Format_ARGB32_Premultiplied);
//                                        QPainter painter(&image);
//                                        painter.fillRect(image.rect(), Qt::white);
//                                        painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter,str.mid(str.indexOf("\n")+1, str.length()));
//                                        image.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png");
//                                        //second_name = lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"/"+"3.png";
//                                        break;
//                                    }
//                                    case 3:
//                                    {
//                                        QString lpr_path_for_first = "./captures/license_plates/";
//                                        QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                                        QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");
//                                        QDir myDir;
//                                        if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                                            myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                                        }
//                                        QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.txt");
//                                        if(!input_file.open(QFile::WriteOnly)){
//                                            //qDebug() << "Error opening for write: " << input_file.errorString();
//                                            return;
//                                        }
//                                        QTextStream outStream(&input_file);
//                                        outStream << str.mid(str.indexOf("\n")+1, str.length());
//                                        input_file.close();
//                                        //second_text = lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"/"+"4.txt";
//                                        break;
//                                    }
//                                    }
//                                }


//                                //                    //qDebug() << "Car found!";
//            //                    QString date_time_db =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//            //                    date_time_db = encodeString(date_time_db);
//                                //                    QString img_path;
//                                //                    QDir myDir;
//                                //                    if(!myDir.exists(lpr_path+"/"+date)){
//                                //                        myDir.mkpath(lpr_path+"/"+date);
//                                //                        img_path = lpr_path+"/"+date+"/"+qstr+"_"+QTime::currentTime().toString()+".png";
//                                //                        QFile file(img_path);
//                                //                        file.open(QIODevice::WriteOnly);
//                                //                        pic.save(&file, "PNG");
//                                //                    }else{
//                                //                        myDir.mkpath(lpr_path+"/"+date);
//                                //                        img_path = lpr_path+"/"+date+"/"+qstr+"_"+QTime::currentTime().toString()+".png";
//                                //                        QFile file(img_path);
//                                //                        file.open(QIODevice::WriteOnly);
//                                //                        pic.save(&file, "PNG");
//                                //                    }
//                                //                    //    QFile file(lpr_path+qstr);
//                                //                    //    file.open(QIODevice::WriteOnly);
//                                //                    //    pic.save(&file, "PNG");

//                                //                    std::string plateRequest = LPR.toUtf8().constData();

//                                //                    //           if(plateData.find(plateRequest) != std::string::npos) {
//                                //                    //               //makeNotification(pic, qstr, indx);
//                                //                    //               emit notifyLPR(pic, qstr, indx);
//                                //                    //           }
//                                //                    //facesWindow->addObject(pic, str, indx);
//                                //                    //    facesWindow->addLPR(pic, str, indx);
//            //                    QSqlQuery qLp, qLp_insert;
//            //                    if (qLp.exec(
//            //                                "CREATE TABLE detected_LPR ( "
//            //                                "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
//            //                                "first_name text, "
//            //                                "first_text text, "
//            //                                "second_name text, "
//            //                                "second_text text, "
//            //                                "date_time DATETIME "
//            //                                "); "
//            //                                )){
//            //                        //qDebug()<< "Table created lpr";
//            //                    }else{
//            //                        //qDebug() << "Lp table not created "<<qLp.lastError();
//            //                    }
//            //                    //qDebug() << "Dynamic = " << first_name << " " << first_text << " " << second_name << " " << second_text;
//            //                    qLp_insert.prepare("insert into detected_LPR "
//            //                                       "( first_name, first_text, second_name, second_text, date_time ) "
//            //                                       "values (?, ?, ?, ?, ?) ; ");
//            //                    qLp_insert.addBindValue(first_name);
//            //                    qLp_insert.addBindValue(first_text);
//            //                    qLp_insert.addBindValue(second_name);
//            //                    qLp_insert.addBindValue(second_text);
//            //                    qLp_insert.addBindValue(date_time_db);
//            //                    qLp_insert.exec();
//            //                    //qDebug() << "Dynamic1 = " << first_name << " " << first_text << " " << second_name << " " << second_text;

//                                Notification *newNoti= new Notification(str, "", QString::number(indx), pic.scaledToHeight(140), "", "");
//                                lpr_emailController->addNotLPR(newNoti);
//                            }*/
//                        }
//                        if(flag_sus_lpr == 0){//zero kore dite hobe
//                            QString lpr_path_for_first = "./captures/Suspect_license_plates/";
//                            QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
//                            QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");

//                            QDir myDir;
//                            if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
//                                myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
//                            }
//                            //                            QFile input_file(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.txt");
//                            //                            if(!input_file.open(QFile::WriteOnly)){
//                            //                                //qDebug() << "Error opening for write: " << input_file.errorString();
//                            //                                return;
//                            //                            }
//                            //                            QTextStream outStream(&input_file);
//                            //                            outStream << lpr_trs+" "+singleLastLett+" "+sub_qstr;
//                            //                            //outStream << str.mid(0, str.indexOf("\n"));
//                            //                            input_file.close();
//                            pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");// pic write
//                            main_pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png");// pic write

//                            detectedLpToDb(lpr_trs+" "+singleLastLett+" "+sub_qstr, encodeString(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")), color, lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"2.png", lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");

//                            Notification *newNoti= new Notification(main_pic, "!"+lpr_trs+" "+singleLastLett+" "+sub_qstr, "", QString::number(indx), pic.scaledToHeight(140), "", "");
//                            facesWindow->uniqueLicencePlateShowInTiles(pic, lpr_trs+singleLastLett+sub_qstr, indx, color);
//                            lpr_emailController->addNotLPR(newNoti);
//                        }


//                    }



//                }
//            }




//        }



//    }

//    //    bool num_check = true;
//    //    for(int i = 0; i < sub_qstr.length(); i++){
//    //        if(sub_qstr.at(i) >= 0 &&  sub_qstr.at(i) <=9 ){
//    //            //qDebug() << "(int) sub_qstr.at(i) = " <<  sub_qstr.at(i);
//    //        }
//    //    }

//    //    QString date_time_db =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//    //    date_time_db = encodeString(date_time_db);
//    //    QString img_path;
//    //    QDir myDir;
//    //    if(!myDir.exists(lpr_path+"/"+date)){
//    //        myDir.mkpath(lpr_path+"/"+date);
//    //        img_path = lpr_path+"/"+date+"/"+qstr+"_"+QTime::currentTime().toString()+".png";
//    //        QFile file(img_path);
//    //        file.open(QIODevice::WriteOnly);
//    //        pic.save(&file, "PNG");
//    //    }else{
//    //        myDir.mkpath(lpr_path+"/"+date);
//    //        img_path = lpr_path+"/"+date+"/"+qstr+"_"+QTime::currentTime().toString()+".png";
//    //        QFile file(img_path);
//    //        file.open(QIODevice::WriteOnly);
//    //        pic.save(&file, "PNG");
//    //    }
//    ////    QFile file(lpr_path+qstr);
//    ////    file.open(QIODevice::WriteOnly);
//    ////    pic.save(&file, "PNG");

//    //    std::string plateRequest = LPR.toUtf8().constData();

//    //    //           if(plateData.find(plateRequest) != std::string::npos) {
//    //    //               //makeNotification(pic, qstr, indx);
//    //    //               emit notifyLPR(pic, qstr, indx);
//    //    //           }
//    //    //facesWindow->addObject(pic, str, indx);
//    //    //    facesWindow->addLPR(pic, str, indx);



//    //    Notification *newNoti= new Notification(str, "", QString::number(indx), pic.scaledToHeight(140), "", "");
//    //    lpr_emailController->addNotLPR(newNoti);
//}


void MainWindow::addObject(QPixmap pic, QString str, int indx)
{

    //  facesWindow->addObject(pic, str, indx);
}

void MainWindow::on_actionTracking_triggered()
{
    trackingWindow = new trackingSettingsDialog(this);
    trackingWindow->show();

}

void MainWindow::on_tileButton_clicked()
{
    //    facesWindow = new Faces(this);
    //     facesWindow->setAttribute( Qt::WA_DeleteOnClose , true);
    //loop_off = TRUE;

    //      facesWindow->show();
    //    std::pair<int, int> ab, abcd;
    //    ab.first = 1;
    //    ab.second = 3;
    //    abcd.first = 2;
    //    abcd.second = 9;
    //    std::vector<std::pair<int, int>> abc;
    //    abc.push_back(ab);
    //    abc.push_back(abcd);

    //    emit sourceDivisorPassToDS(abc);

    /// issue is here, show faceswindow or tilerdisplay
    if (tilerdisplayWindow != nullptr)
    {
        delete tilerdisplayWindow;
        tilerdisplayWindow = new TilerDisplay(this);
    }
//    tilerdisplayWindow->show();
    //        newSettings->show();

    /// for onvif module
    onvif_h->show();
}



void MainWindow::on_actionSettings_triggered()
{
    //settingsDialog *newexSettings= new settingsDialog(this);
    //connect(newSettings, SIGNAL(objectSensitivityChanged()), this, SLOT(setObjectThreshold()));
    //    newSettings->exec();
    newSettings->show();
    //newexSettings->exec();
}

void MainWindow::setObjectThreshold()
{
    //    for(int i=0;i<feeds.size();i++){
    //        feeds[i]->reset_object_threshold();
    //    }
}

void MainWindow::on_actionRTSS_triggered()
{
    //facesWindow->deleteLater();
}

//void MainWindow::on_actionFootage_analysis_triggered()
//{
//    footage= new footageWindow(this);
//    footage->par_mutex = darknet_mutex;
//    footage->setAttribute( Qt::WA_DeleteOnClose );
//    footage->show();
//}
void MainWindow::on_actionAbout_2_triggered()
{
    aboutDialog *about = new aboutDialog(this);
    about->setAttribute( Qt::WA_DeleteOnClose );
    about->show();
}
//void valueChanged(QPixmap p, QString str, int indx)
//{
//   // emit valueChangedALL(p, str,indx);
//}
void MainWindow::cleanTiles()
{
    trialTimer->stop();
    //    if (facesWindow != nullptr)
    //    {
    //        facesWindow->deleteLater();
    //        // delete facesWindow;
    //        facesWindow = new Faces(this);
    //        trialTimer->start(3600000);
    //        // facesWindow->setAttribute( Qt::WA_DeleteOnClose , true);
    //    }
}

bool MainWindow::AddToLoadTemplate(QString name, QString path)
{
    qDebug() << "img Name " << name << " and img path : " << path;
    //qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<Done>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;

    //    FRthread->quit();
    //    warker->requestWark();

    //     QImageReader reader(path);
    //     QSize size_of_image = reader.size();
    //     int height = size_of_image.height();
    //     int width = size_of_image.width();
    //     //qDebug() << "Height = " << height << " Width " << width << endl;

    //     if(width>=500 && height>=500){

    //     }

    bool face_found_in_image = warker->loadImageIntoLoadTemplate(name,path);

    //bool face_found_in_image = warker->loadImageIntoLoadTemplate("tomm","/home/sigmind/watchcam-testedOK/faces/temp_late/name4.png");

    //bool face_found_in_image = warker->loadImageIntoLoadTemplate("tomm","/home/sigmind/watchcam-testedOK/faces/tanmoy.jpg");

    if(face_found_in_image == true){
        qDebug() << "valid image in load_temp";
        return true;
    }else {
        qDebug() << "Not valid image in load_tem";
        return false;
    }

    ////qDebug() << " ___________________________________________________ ";
    //emit loadforsingle(name, path);

}

void MainWindow::deleteFromLoadTem(QString image_path, QString image_name)
{
    //    //qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<< deleteFromLoadTem >>>>>>>>>>>>>>>>>>>>>>>" << endl;

    // warker->deleteFromTemplate(image_path, image_name);
}

void MainWindow::addToDB(int Id,QPixmap m_pic, QPixmap pic, QString str, int indx,
                         double confidence, QString date_time,
                         int sync_states,
                         QString date, QString im_path, QString image_name, int rec_or_not, QString gender, int age, QString color){
    //qDebug() << "In add to db" << endl;
    /* Database implementation*/
    if(connectionDB()){
        //        //qDebug() << "HelloFeedStatic";
        //        QString face_path = "./captures/faces/";
        //        QString obliq = "/";
        //        // QString format = "dd.MM.yyyy";
        //        //QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        //        date_time = encodeString(date_time);
        //        QString at = "<at>";
        //        QString date = QDate::currentDate().toString("dd.MM.yyyy");
        //        QString img_path = face_path+date+obliq;
        //        //        QString image_name = img_path+str+at+".png";
        //        QString image_name = img_path+str+at+QTime::currentTime().toString()+".png";



        QDir myDir;
        if(!myDir.exists(date)) //if no directory so create directory
        {
            myDir.mkpath(im_path);
            //            image_name = image_name+"1.png";
            //            QFile file(image_name+"2.png");
            //            file.open(QIODevice::WriteOnly);
            //            pic.save(&file, "PNG");

            //            QFile file1(image_name+"1.png");
            //            file1.open(QIODevice::WriteOnly);
            //            m_pic.save(&file1, "PNG");
            //            file1.close();

            pic.save(image_name+"2.png");
            m_pic.save(image_name+"1.png");

        }

        QSqlQuery query;

        if (query.exec(
                    "CREATE TABLE FeedAddFace ( "
                    "Id int not null, "
                    "name TEXT, "
                    "savePath VARCHAR(250) NOT NULL, "
                    "savePathPerson VARCHAR(250) NOT NULL, "
                    "date_time DATETIME NOT NULL, "
                    "confidence double NOT NULL, "
                    "video_src int not null, "
                    "states int not null, "
                    "rec_check int not null, "
                    "Gender varchar(150) not null, "
                    "age int not null, "
                    "color varchar(50) not null"
                    "); "
                    )){
            ////qDebug()<< "Table created";
        }

        query.prepare("INSERT INTO FeedAddFace (Id, name, savePath, savePathPerson, date_time, confidence, video_src, states, rec_check, Gender, age, color) VALUES (?,?,?,?,?,?,?,?,?,?,?,?);");
        query.addBindValue(Id);
        query.addBindValue(str);
        query.addBindValue(image_name+"2.png");
        query.addBindValue(image_name+"1.png");
        query.addBindValue(date_time);
        query.addBindValue(confidence);
        query.addBindValue(indx);
        query.addBindValue(sync_states);
        query.addBindValue(rec_or_not);
        query.addBindValue(gender);
        query.addBindValue(age);
        query.addBindValue(color);

        if (query.exec()){
            ////qDebug() << "Done";
        }else{
            //            //qDebug() <<"Executed error "<< query.executedQuery();
            //qDebug() << "Last Error " << query.lastError();
            //            //qDebug() << "Not Done";
        }


    }else{
        ////qDebug() << "HelloNotFeed";
    }
}

void MainWindow::on_actionDatabase_Configuration_triggered()
{
    //qDebug() << "basedul " << endl;
    //    configdb->show();
    configdb->exec();
    //    show_face->show();
}

void MainWindow::on_actionSearch_by_date_and_time_triggered()
{
    search_by_date_time search_ob; // search from dynamic database, object creation
    search_ob.setModal(true);
    search_ob.exec();
}

void MainWindow::on_actionStudent_Attendece_triggered()
{
    ReportGenerateFromtoTo rep;
    rep.setModal(true);
    rep.exec();
}

void MainWindow::on_actionEmployee_Attendence_triggered()
{
    //qDebug() << "Employee attendence" << endl;
    EmployeeAttendence empa;
    empa.setModal(true);
    empa.exec();
}

//void MainWindow::on_actionTotal_Present_Time_For_Each_Employe_triggered()
//{

//}

void MainWindow::on_actionTotal_Present_Time_For_Each_Employe_toggled(bool arg1)
{

}

void MainWindow::on_actionTotal_Present_Time_For_Each_Employe_triggered()
{
    CalculateTimePerObject cal;
    cal.setModal(true);
    cal.exec();
}

void MainWindow::on_actionSearch_By_Given_Image_triggered()
{
    //search->show();
    sbi->show();
    //warker->detectFaceFromImage("/home/sigmind/Pictures/WC-Tegra-DS/xhuv.png");
}

void MainWindow::on_actionFace_Notification_triggered()
{
    if(!checker_not_flg){
        nots->setVisible(true);
        checker_not_flg= true;
        ////qDebug()<<"set visible true";
    }
    else {
        nots->setVisible(false);
        checker_not_flg= false;
        ////qDebug()<<"set visible false";
    }
}

void MainWindow::on_startButton_clicked()
{
    qDebug()<<"on_startButton_clicked call";
    newSettings->show();
}

void MainWindow::on_actionMedia_Player_triggered()
{
    qDebug()<<"on_actionOpen_Media_Player_triggered clicked";

    player_obj = new Player();

#if defined(Q_WS_SIMULATOR)
    player_obj->setAttribute(Qt::WA_LockLandscapeOrientation);
    player_obj->showMaximized();
#else
    player_obj->showMaximized();
#endif

    player_obj->show();
}
