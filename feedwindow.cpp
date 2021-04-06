#include "feedwindow.h"
#include "ui_feedwindow.h"
#include <QDebug>
#include <cmath>
#include <QDebug>

//#include "PTZControl/Ptz.h"
//#include "PTZControl/UserDefine.h"
#include <iostream>
#include <QThread>

#include <dialogs/registerfacedialog.h>
#include <mystyles.h>

using namespace std;

//CPtz a_PTZ; //from ptz.h for controlling ptz

//void CALLBACK DisConnectFunc1(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
//{
//    printf("Call DisConnectFunc: lLoginID[0x%x]\n", lLoginID);
//}

bool PTZController(int nType, bool bStop)
{
    bool bRet = false;
  //  bRet = a_PTZ.PtzBasicControl(nType, 1, bStop);
    return bRet;
}

//LLONG mm_lLoginHandle;

FeedWindow::FeedWindow(bool type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FeedWindow)
{
    ui->setupUi(this);
    //qDebug() << width();
    //qDebug() <<height();
    w = width();
    h = height();

    ratio =  (float) w/h;

    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);


    ptzType = type;

    //qDebug() << ptzType;

    if (type) {

        //CLIENT_Init
//        CLIENT_Init(DisConnectFunc1, 0);

//        NET_DEVICEINFO deviceInfo = {0};
//        int error = 0;

//        //CLIENT_Login
//       // mm_lLoginHandle = CLIENT_Login("192.168.1.223", 37777, "admin", "00125680Sigmind", &deviceInfo, &error);
//         mm_lLoginHandle = CLIENT_Login("123.200.23.238", 37777, "admin", "w12345678", &deviceInfo, &error);
//        if(mm_lLoginHandle == 0)
//        {
//            cout << "PTZ Login failed!" << endl;
//        }
//        else
//        {
//            a_PTZ.SetLoginID(mm_lLoginHandle);

//            for(int i = 1; i <= deviceInfo.byChanNum; i++)
//            {
//                a_PTZ.SetChannel(0);
//            }
//            cout << "Login successful!" << endl;
//        }

//        std::cout << "login ID: " << a_PTZ.getLoginID() << " channel: " << a_PTZ.getChannel() << endl;

        //CLIENT_ControlDeviceEx(a_PTZ.getLoginID(), DH_CTRL_REBOOT, NULL, NULL, 1000);
    }//connect drag functionality

    //ui->imageLabel->setScaledContents(true);

    //ui->scrollArea->setWidgetResizable(true);

    this->setCursor(QCursor(Qt::OpenHandCursor));
}

FeedWindow::~FeedWindow()
{
    delete ui;
    if(ptzType){
//        BOOL bSuccess = CLIENT_Logout(mm_lLoginHandle);
//        if(bSuccess)
//        {
//            cout << "Logout successful" << endl;
//        }
//        else
//        {
//            cout << "Logout failed" << endl;
//        }

//        //CLIENT_Cleanup
//        CLIENT_Cleanup();
    }

}

void FeedWindow::receiveVideoFeed(QPixmap pic)
{
//    //qDebug()<<pic.width()<<" "<<pic.height()<<" "<<ui->imageLabel->height()<<endl;
    if(ratio < myStyles::winRatio){
        ////qDebug() << "width";
        ui->imageLabel->setPixmap(pic.scaledToWidth(w, Qt::SmoothTransformation));
    }
    else {
        ////qDebug() << "height";
        ui->imageLabel->setPixmap(pic.scaledToHeight(h, Qt::SmoothTransformation));
    }
}

void FeedWindow::resizeEvent(QResizeEvent *)
{
    w = width();
    h = height();
    ratio =  (float) w/h;

}

void FeedWindow::mouseMoveEvent(QMouseEvent *event)
{



}

void FeedWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << "in";
    this->setCursor(QCursor(Qt::OpenHandCursor));
    if(!ptzType) return;
    if (event->button() == Qt::LeftButton){

        if ((event->pos() - dragStartPosition).manhattanLength() < 50) return;

        int xChange = event->pos().x() - dragStartPosition.x() ;
        int yChange = event->pos().y() - dragStartPosition.y() ;

        //qDebug() << "release" << xChange;
        //qDebug() << "release" << yChange;


        if(abs(xChange) > abs(yChange)){
//            if(xChange>0) {
//                //left
//                cout << "left: " << CLIENT_DHPTZControlEx(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_PTZ_LEFT_CONTROL, 0, 8, 0, FALSE) << endl;
//                QThread::msleep(xChange/2);
//                cout << "left: " << CLIENT_DHPTZControlEx(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_PTZ_LEFT_CONTROL, 0, 8, 0, TRUE) << endl;

//            }
//            else {
//                //right
//                cout << "right: " << CLIENT_DHPTZControlEx(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_PTZ_RIGHT_CONTROL, 0, 8, 0, FALSE) << endl;
//                QThread::msleep(abs(xChange)/2);
//                cout << "right: " << CLIENT_DHPTZControlEx(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_PTZ_RIGHT_CONTROL, 0, 8, 0, TRUE) << endl;
//            }
        }
        else {
//            if(yChange>0) {
//                //up
//                cout << "up: " << CLIENT_DHPTZControlEx(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_PTZ_UP_CONTROL, 0, 8, 0, FALSE)<< endl;
//                QThread::msleep(yChange/2);
//                cout << "up: " << CLIENT_DHPTZControlEx(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_PTZ_UP_CONTROL, 0, 8, 0, TRUE) << endl;

//            }
//            else {
//                //down
//                cout << "down: " << CLIENT_DHPTZControlEx(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_PTZ_DOWN_CONTROL, 0, 8, 0, FALSE) << endl;
//                QThread::msleep(abs(yChange)/2);
//                cout << "down: " << CLIENT_DHPTZControlEx(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_PTZ_DOWN_CONTROL, 0, 8, 0, TRUE) << endl;
//            }
        }

    }
}

#ifndef QT_NO_WHEELEVENT
void FeedWindow::wheelEvent (QWheelEvent *e)
{
    //
    if(!ptzType) return;
    QString result;
//    if (e->delta() > 0) {

//        if (e->orientation() == Qt::Vertical) {
//            result = "Mouse Wheel Event: UP";
//            CLIENT_DHPTZControlEx2(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_EXTPTZ_FASTGOTO, 0, 0, 2, FALSE, NULL);
//            QThread::msleep(150);
//        } else {
//            result = "Mouse Wheel Event: LEFT";
//        }
//    } else if (e->delta() < 0) {
//        if (e->orientation() == Qt::Vertical) {
//            result = "Mouse Wheel Event: DOWN";
//            CLIENT_DHPTZControlEx2(a_PTZ.getLoginID(), a_PTZ.getChannel(), DH_EXTPTZ_FASTGOTO, 0, 0, -2, FALSE, NULL);
//            QThread::msleep(150);
//        } else {
//            result = "Mouse Wheel Event: RIGHT";
//        }
//    }
//    //qDebug() << result;
}
#endif

void FeedWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        dragStartPosition = event->pos();
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    }
    else if(event->button() == Qt::MiddleButton){
      //  QPixmap pic("/home/sigmind/watchcamV1/watchcamQtDebug/loading.jpg");
          QPixmap pic(":/.rsc/sigmindLogo.png");
        registerFaceDialog *faceDialog= new registerFaceDialog(pic, this);
        faceDialog->show();
    }
}

void FeedWindow::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
    {
        //qDebug() << e->pos();
    }
}
