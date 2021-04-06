#include "feed.h"
#include "ui_feed.h"
#include <QDebug>
#include <QPushButton>
#include <QInputDialog>
#include <QDir>
#include <dlib/opencv.h>
#include <qpainter.h>
#include <QColor>


Feed::Feed(int inx,int w, int h, QMutex * qm, std::vector<std::string> &names, std::vector<dlib::matrix<float,(long)0,(long)1>> &descriptors, QWidget *parent) :
    QWidget(parent), face_names(names), face_descriptors(descriptors),
    ui(new Ui::Feed)
{
    ui->setupUi(this);

    QFile File(":/qdarkstyle/styleFeed.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);

    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);

    setMinimumSize(w, h);
    setMaximumSize(w, h);

    ////qDebug() << "size set "<< width() << " " << height();

    //QPixmap pic("/home/xhuv/watchcamV1/watchcam5_0/pic.png");
    //ui->feedLabel->setPixmap(pic);

    ui->feedLabel->setScaledContents(true);
    ui->feedLabel->setStyleSheet(myStyles::blinkOff);

    //ui->feedLabel->setMouseTracking(true);



    addCameraButton = new QPushButton(this);
    //addCameraButton->setText("add");
    ui->feedGridLayout->addWidget(addCameraButton, 0, 0, 1, 1, Qt::AlignCenter);

    QPixmap pixmap(":/icons/add.png");
    QIcon ButtonIcon(pixmap);
    addCameraButton->setIcon(ButtonIcon);
    addCameraButton->setIconSize(pixmap.rect().size());

    //addCameraButton->setIconSize(pixmap.rect().size());

    closeCameraButton = new QPushButton(this);
    //closeCameraButton->setText("close");
    closeCameraButton->setVisible(false);


    QPixmap pixma(":/icons/cancel.png");
    QIcon ButtonIco(pixma);
    closeCameraButton->setIcon(ButtonIco);
    closeCameraButton->setIconSize(pixma.rect().size());

    enlargeCameraButton = new QPushButton(this);
    //enlargeCameraButton->setText("enlarge");
    enlargeCameraButton->setVisible(false);

    QPixmap pixm(":/icons/monitor.png");
    QIcon ButtonIc(pixm);
    enlargeCameraButton->setIcon(ButtonIc);
    enlargeCameraButton->setIconSize(pixm.rect().size());

    tilesButton = new QPushButton(this);
    tilesButton->setVisible(false);

    QPixmap pix(":/icons/tiles.png");
    QIcon ButtonI(pix);
    tilesButton->setIcon(ButtonI);
    tilesButton->setIconSize(pix.rect().size());

    setButtonPlacements(w);


    connect(addCameraButton, SIGNAL(clicked(bool)),this,SLOT(addCamera(bool)));
    connect(closeCameraButton, SIGNAL(clicked(bool)), this, SLOT(closeCamera(bool)));
    connect(enlargeCameraButton, SIGNAL(clicked(bool)), this, SLOT(enlargeCamera(bool)));
    connect(tilesButton, SIGNAL(clicked(bool)), this, SLOT(tilesOpen(bool)));



    facesWindow= new Faces(this);
    facesWin=false;
    connect(this, SIGNAL(emitTile(QPixmap,QString,int)), facesWindow, SLOT(receiveTile(QPixmap,QString,int)));
    connect(this, SIGNAL(emitTile(QPixmap,QString,int)), facesWindow, SLOT(receiveTileLP(QPixmap,QString,int)));
    //connect(ui->feedLabel, SIGNAL())

    ////qDebug()<< ui->feedLabel->width();
    ////qDebug()<< ui->feedLabel->height();

    mutex = qm;

    indx = inx;

    ui->feedLabel->setStyleSheet(myStyles::blinkOff);

    //blinkOn();

}

Feed::~Feed()
{

    delete ui;
}

void Feed::mousePressEvent(QMouseEvent *event)
{

    //qDebug() <<event->x();
    //qDebug() <<event->y();
    X = event->x();
    Y = event->y();
    mClicked = true;
}


void Feed::face_database_update()
{
    if(cam!=NULL)
    {
        //  cam->face_database_update();
    }
}

void Feed::reset_object_threshold()
{
    if(cam!=NULL)
    {
        cam->reset_object_threshold(myStyles::objectSensitivityValue);
        //     cam->thresh = cam->hier_thresh*(1.0- myStyles::objectSensitivityValue);
        //qDebug() <<"value: "<<myStyles::objectSensitivityValue<<" "<< cam->thresh<<"\n\n";
    }
}

void Feed::set_blacklist_descriptor(std::vector<dlib::matrix<float,0l,1l> > blacklist)
{
    blacklist_descriptors = blacklist;
    //qDebug() << "blacklist size: "<<blacklist.size()<<" blacklist descriptor size: "<<blacklist_descriptors.size()<<endl;
}

void Feed::blinkOn()
{
    blinkTimer= new QTimer(this);
    blinking = true;

    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(changeColor()));
    blinkTimer->start(400);
}

void Feed::blinkOff()
{
    blinkTimer->stop();
    blinking = false;
    ui->feedLabel->setStyleSheet(myStyles::blinkOff);
    disconnect(blinkTimer, SIGNAL(timeout()), this, SLOT(changeColor()));
}

void Feed::changeColor()
{
    if(ui->feedLabel->styleSheet()== myStyles::blinkOn) {
        //  ui->feedLabel->setStyleSheet(myStyles::blinkOnG);


        ui->feedLabel->setStyleSheet(myStyles::blinkOff);
    }
    else if(ui->feedLabel->styleSheet()== myStyles::blinkOff){
        ui->feedLabel->setStyleSheet(myStyles::blinkOn);
        //  ui->feedLabel->setStyleSheet(myStyles::blinkOnG);
    }

}

void Feed::hoverEnter(QHoverEvent *)
{
    ////qDebug() <<"mouse entered";
    if(cameraSet)
    {
        closeCameraButton->setVisible(true);
        enlargeCameraButton->setVisible(true);
        tilesButton->setVisible(true);
    }
    //if(cameraSet) closeCameraButton->setVisible(true);
}

void Feed::hoverLeave(QHoverEvent *)
{
    ////qDebug() <<"mouse left";
    closeCameraButton->setVisible(false);
    enlargeCameraButton->setVisible(false);
    tilesButton->setVisible(false);

}

bool Feed::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;

    default:
        break;
    }
    return QWidget::event(event);
}


void Feed::update_ui(cv::Mat mat, cv::Mat orig, std::vector<watchcam::rectangle > rects)
{

    //    //qDebug()<<"update ui started...\n";
    QPixmap p = QPixmap::fromImage(QImage((unsigned char*) mat.data, mat.cols, mat.rows, QImage::Format_RGB888));
    //    ui->feedLabel->setPixmap(p);

    cv::cvtColor(orig, orig, CV_BGR2RGB);
    QPixmap p2 = QPixmap::fromImage(QImage((unsigned char*) orig.data, orig.cols, orig.rows, QImage::Format_RGB888));
    QPixmap p3 = QPixmap::fromImage(QImage((unsigned char*) orig.data, orig.cols, orig.rows, QImage::Format_RGB888));
    //QPixmap p4;
    bool found = false;
    cv::Mat HSV;
    cv::cvtColor(orig, HSV, CV_RGB2HSV);

    for(int i=0; i<rects.size(); i++)
    {
        //  cv::Mat receivedFrame = rects[i].buFrame;
        //   p4 = QPixmap::fromImage(QImage((unsigned char*) receivedFrame.data, receivedFrame.cols, receivedFrame.rows, QImage::Format_RGB888));
        //  receivedFrame.release();
        if(rects[i].track_id<0)
        {
            if(FACE_TO_SEARCH!="" && QString::fromStdString(rects[i].name).contains(FACE_TO_SEARCH))
            {
                found = true;
                std::cout << '\a';
                break;
            }


        }

        if(OBJECT_TO_SEARCH!="" && QString::fromStdString(rects[i].name).contains(OBJECT_TO_SEARCH))
        {
            found = true;
            QRect r(rects[i].left, rects[i].top, rects[i].width, rects[i].height);
            QString objName = QString::fromStdString(rects[i].name) ;

            emit notify(p2.copy(r), objName, indx);
            std::cout << '\a';
            //blinkOn();
            break;
            // }




            //   if(rects[i].name == OBJECT_TO_SEARCH.toStdString())
            //| (rects[i].track_id<0 && ((!rects[i].is_face && OBJECT_TO_SEARCH.toStdString()=="person") || (rects[i].is_face && OBJECT_TO_SEARCH.toStdString()=="car")))
            //  {
            //        if(QString::fromStdString(rects[i].name).contains(OBJECT_TO_SEARCH))
            //        {
            if(COLOR_TO_SEARCH<=0)
            {
                found = true;
                QRect r(rects[i].left, rects[i].top, rects[i].width, rects[i].height);
                //                //emit notify(p2.copy(r), objName, indx); }
                //            if(COLOR_TO_SEARCH == -2) {
                //                QString objName = "White >> " + QString::fromStdString(rects[i].name) ;

                //                emit notify(p2.copy(r), objName, indx); }
                //            else  if(COLOR_TO_SEARCH == -3) {
                QString objName = "Black/White/Red >> " + QString::fromStdString(rects[i].name)  ;

                emit notify(p2.copy(r), objName, indx);// }
                //            else  if(COLOR_TO_SEARCH == 0) {
                //                QString objName = "Red >> " + QString::fromStdString(rects[i].name) ;
                //                emit notify(p2.copy(r), objName, indx); }
                std::cout << '\a';

                break;
            }
            else {
                double marked = 0.0;
                double total = 0.0;
                double percentage = 0.0;
                for(int l=rects[i].left; l<rects[i].right; l++)
                {
                    for(int k=rects[i].top; k<rects[i].bot; k++)
                    {
                        int val = HSV.at<cv::Vec3b>(k,l)[0];
                        if(std::abs(val-COLOR_TO_SEARCH)<COLOR_VARIANCE || abs(val-COLOR_TO_SEARCH)+COLOR_VARIANCE>180)
                            marked+=1.0;
                        total += 1.0;
                    }
                }
                percentage = marked/total;
                if(percentage>= COLOR_ACCEPTANCE_PERCENTAGE)
                {
                    found = true;
                    QRect r(rects[i].left, rects[i].top, rects[i].width, rects[i].height);
                    /*               if(COLOR_TO_SEARCH == 140) {
                QString objName = "Black >> " + QString::fromStdString(rects[i].name) ;

                emit notify(p2.copy(r), objName, indx); }

//                else */
                    if((COLOR_TO_SEARCH <= 140) && (COLOR_TO_SEARCH > 120)) {
                        QString objName = "Violet >> " + QString::fromStdString(rects[i].name) ;

                        emit notify(p2.copy(r), objName, indx); }
                    else  if((COLOR_TO_SEARCH <= 120) && (COLOR_TO_SEARCH > 100)) {
                        QString objName = "Blue >> " + QString::fromStdString(rects[i].name) ;

                        emit notify(p2.copy(r), objName, indx); }
                    else  if((COLOR_TO_SEARCH <= 100) && (COLOR_TO_SEARCH > 60)) {
                        QString objName = "Indigo >> " + QString::fromStdString(rects[i].name) ;

                        emit notify(p2.copy(r), objName, indx); }
                    else  if((COLOR_TO_SEARCH <= 60) && (COLOR_TO_SEARCH > 30)) {
                        QString objName = "Green >> " + QString::fromStdString(rects[i].name) ;

                        emit notify(p2.copy(r), objName, indx); }
                    else  if((COLOR_TO_SEARCH <= 30) && (COLOR_TO_SEARCH > 15)) {
                        QString objName = "Yellow >> " + QString::fromStdString(rects[i].name) ;

                        emit notify(p2.copy(r), objName, indx); }
                    else  if((COLOR_TO_SEARCH <= 15) && (COLOR_TO_SEARCH > 0)) {
                        QString objName = "Orange >> " + QString::fromStdString(rects[i].name) ;

                        emit notify(p2.copy(r), objName, indx); }

                    std::cout << '\a';

                    break;
                }
            }
        }
        //        else if(QString::fromStdString(rects[i].name).contains("None"))
        //        {
        //            found = false;
        //            //blinkOn();
        //            //searchOn = false;
        //            break;
        //        }
    }
    faceStation(mat, indx);

    for(int i=0,j=0; i<rects.size(); i++)
    {
        //        if(rects[i].is_detected_by_dlib && j<pic_templates.size())
        //        {
        //            QRect r(rects[i].left-20, rects[i].top-20, rects[i].width+40, rects[i].height+40);
        ////            //qDebug() << blacklist_descriptors.size() << " size \n\n\n\n\n\n\n";
        //            for(int k=0; k<blacklist_descriptors.size(); k++)
        //            {
        //                double diff = length(blacklist_descriptors[k]-pic_templates[j]);
        //qDebug() <<  " Rect size diff \n";
        //                if(diff<.45)
        //                {
        //                    //qDebug() << "not emit \n\n\n\n\n\n\n\n\n notification emit";
        //                    emit notify(p2.copy(r), QString::fromStdString(rects[i].name), indx);
        //                    std::cout << '\a';
        //                }
        //            }
        //            faceStation(p2.copy(r), QString::fromStdString(rects[i].name), indx);
        //        }
        if(rects[i].is_face)
        {
            //QRect r(rects[i].left-10, rects[i].top-10, rects[i].width+20, rects[i].height+20);
            //             QRect r(rects[i].left, rects[i].top, rects[i].width, rects[i].height);

            //    faceStation(mat, indx);
            // faceStation(p4.copy(r), indx);
            //  emit notifyLPR(p3.copy(r), QString::fromStdString(rects[i].name), indx);
            //  lprStation(p3.copy(r), plateID, indx);
            // emit notifyLPR()

        }
        if(rects[i].is_LP)
        {
            QRect r(rects[i].left-40, rects[i].top-40, rects[i].width+80, rects[i].height+80);

            lprStation(p3.copy(r), indx);
            //  emit notifyLPR(p3.copy(r), QString::fromStdString(rects[i].name), indx);
            //  lprStation(p3.copy(r), plateID, indx);
            // emit notifyLPR()

        }
    }

    //ui->feedLabel->setPixmap(p.scaled(myStyles::runningFeedWidth,myStyles::runningFeedHeight, Qt::IgnoreAspectRatio,Qt::FastTransformation));
    //    //qDebug()<<mat.rows<<"x"<<mat.cols<<endl;
    ui->feedLabel->setPixmap(p);
    emit emitVideoFeed(p);


    //................face station dismissed....<for now :( > .............//

    if(found)
    {
        ////qDebug() << "found" ;
        if(!blinking) blinkOn();
    }
    else
    {
        ////qDebug() << "not found" ;
        if(blinking)  blinkOff();
    }
    mat.release();
    orig.release();
    HSV.release();
    //    //qDebug()<<"update ui ended...\n";
}


void Feed::search_requested(QString face, int color, QString obj)
{
    FACE_TO_SEARCH = face;
    COLOR_TO_SEARCH = color;
    OBJECT_TO_SEARCH = obj;

}


void Feed::addCamera(bool camm)
{
    AddCameraDialog *addCamera = new AddCameraDialog();
    addCamera->setAttribute( Qt::WA_DeleteOnClose );
    connect(addCamera, SIGNAL(acceptData(QString,QString,bool, bool, bool)), this , SLOT(initializeCamera(QString,QString,bool, bool, bool)));
    addCamera->show();

    //    bool ok;
    //    QString camera = QInputDialog::getText(this, tr("Camera Input"),
    //                                            tr("Camera Address"), QLineEdit::Normal,
    //                                            QDir::home().dirName(), &ok);

    //qDebug()<< "camera added";

}


void Feed::initializeCameraMain(QString camera, int prior)
{
    //  if (!name.isEmpty() && !camera.isEmpty()){
    ui->feedLabel->setText("Loading: "+camera);
    //        if(Fprior)
    //        {
    //            priority = 1;
    //        }
    //        else if(Lprior)
    //        {
    //            priority = 2;
    //        }
    //        else
    //        {
    //            priority = 0;
    //        }
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(camera))
    {
        cam = new Camera(indx, camera.toInt(), mutex, prior);
    }
    else
    {
        cam = new Camera(indx, camera.toStdString().c_str(), mutex, prior);
    }

    thread= new QThread();
    cam->moveToThread(thread);
    connect(cam, SIGNAL(ui_go(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >)), this,
            SLOT(update_ui(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >)));
    //        connect(cam, SIGNAL(ui_go(cv::Mat, cv::Mat, std::deque< watchcam::rectangle >)), this,
    //                SLOT(update_ui(cv::Mat, cv::Mat, std::deque< watchcam::rectangle >)));

    connect(cam, SIGNAL(start_requested()), thread, SLOT(start())); // Paisi
    connect(thread, SIGNAL(started()), cam, SLOT(go()));
    //connect(cam, SIGNAL(sendFace(QPixmap , QString, int)), this, SLOT(faceStation(QPixmap , QString, int)));
    //        connect(thread, SIGNAL(started()), cam, SLOT(inf_loop()));
    //thread->start();
    reset_object_threshold();
    cam->start();
    cameraSet = true;
    addCameraButton->setVisible(false);

    // ptzType = type;


    // }
}


void Feed::initializeCamera(QString name, QString camera, bool type, bool Fprior, bool Lprior)
{
    if (!name.isEmpty() && !camera.isEmpty()){
        ui->feedLabel->setText("Loading: "+camera);
        if(Fprior)
        {
            priority = 1;
        }
        else if(Lprior)
        {
            priority = 2;
        }
        else
        {
            priority = 0;
        }
        QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
        if (re.exactMatch(camera))
        {
            cam = new Camera(indx, camera.toInt(), mutex, priority);
        }
        else
        {
            cam = new Camera(indx, camera.toStdString().c_str(), mutex, priority);
        }

        thread= new QThread();
        cam->moveToThread(thread);
        connect(cam, SIGNAL(ui_go(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >)), this,
                SLOT(update_ui(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >)));
        connect(cam, SIGNAL(start_requested()), thread, SLOT(start())); // Paisi
        connect(thread, SIGNAL(started()), cam, SLOT(go()));
        //connect(cam, SIGNAL(sendFace(QPixmap , QString, int)), this, SLOT(faceStation(QPixmap , QString, int)));
        //        connect(thread, SIGNAL(started()), cam, SLOT(inf_loop()));
        //thread->start();
        reset_object_threshold();
        cam->start();
        cameraSet = true;
        addCameraButton->setVisible(false);

        ptzType = type;


    }
}

void Feed::setSizes(int w, int h)
{
    setMinimumSize(w, h);
    setMaximumSize(w, h);
    setButtonPlacements(w);
    ////qDebug() << "on resize size set "<< width() << " " << height();

}

void Feed::setButtonPlacements(int w)
{
    closeCameraButton->setGeometry(w-myStyles::buttonsWidth-myStyles::borderThickness,myStyles::borderThickness,myStyles::buttonsWidth, myStyles::buttonHeight);
    enlargeCameraButton->setGeometry(w-2*myStyles::buttonsWidth-myStyles::borderThickness, myStyles::borderThickness, myStyles::buttonsWidth, myStyles::buttonHeight);
    tilesButton->setGeometry(w-3*myStyles::buttonsWidth-myStyles::borderThickness, myStyles::borderThickness, myStyles::buttonsWidth, myStyles::buttonHeight);

}

void Feed::faceStation(cv::Mat pix, int indx)
{
    //qDebug()<<"face station......\n";
    emit emitFace(pix, indx);
    // emit emitTile(pix, str, indx);
}

void Feed::lprStation(QPixmap pix, int indx)
{

    //qDebug()<<"LPR Station......\n\n\n\n\n\n\n\n\n";
    //   cv::Mat pixData(pix.rows(),pix.cols(),CV_8UC3,pix.scanline());
    //            std::vector<uchar> IMbuffer;
    //          //  std::vector<uint8_t> IMbuffer;
    //            cv::imencode(".png", pixData, IMbuffer);
    //            QByteArray byteArray = QByteArray::fromRawData((const char*)IMbuffer.data(), IMbuffer.size());
    //            QString base64Image(byteArray.toBase64());

    //   QImage plateImg = pix.toImage();

    //   QByteArray byteArray;

    //       QBuffer buffer(&byteArray);

    //       plateImg.save(&buffer, "PNG"); // writes the image in JPEG format inside the buffer

    //       QString base64Image = QString::fromLatin1(byteArray.toBase64().data());

    emit emitLP(pix, indx);
    //emit emitTile(pix, str, indx);
}

void Feed::closeCamera(bool camm)
{
    if(cameraSet)
    {
        cam->end();
        thread->quit();
        thread->wait();
        delete cam;
        delete thread;
    }
    cameraSet = false;


    addCameraButton->setVisible(true);
    closeCameraButton->setVisible(false);
    enlargeCameraButton->setVisible(false);
    tilesButton->setVisible(false);

    close();
}

void Feed::enlargeCamera(bool camm)
{
    if(!enlargedOn)
    {
        feedWindow= new FeedWindow(ptzType, this);
        enlargeCameraButton->setDisabled(true);
        enlargedOn=true;
        connect(this, SIGNAL(emitVideoFeed(QPixmap)), feedWindow, SLOT(receiveVideoFeed(QPixmap)));
        connect(feedWindow, SIGNAL(finished(int)), this, SLOT(closeEnlargedWindow(int)));
        feedWindow->show();
    }
}

void Feed::closeEnlargedWindow(int ww)
{

    if(enlargedOn)
    {
        enlargedOn=false;
        disconnect(this, SIGNAL(emitVideoFeed(QPixmap)), feedWindow, SLOT(receiveVideoFeed(QPixmap)));
        enlargeCameraButton->setDisabled(false);
    }

}

void Feed::closeTilesWindow(int c)
{
    if(facesWin)
    {
        facesWin=false;
        disconnect(facesWindow, SIGNAL(finished(int)), this, SLOT(closeTilesWindow(int)));
        tilesButton->setDisabled(false);
    }
}

void Feed::tilesOpen(bool camm)
{
    if(!facesWin){
        tilesButton->setEnabled(false);
        facesWin=true;

        connect(facesWindow, SIGNAL(finished(int)), this, SLOT(closeTilesWindow(int)));

        facesWindow->show();

    }
}
