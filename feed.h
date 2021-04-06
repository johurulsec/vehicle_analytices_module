#ifndef FEED_H
#define FEED_H

#include <QWidget>
#include <mystyles.h>
#include <QTimer>
#include <QPushButton>
#include "camera.h"
#include <QThread>
#include <QMutex>
#include <QHoverEvent>
#include <QMouseEvent>
#include <faces.h>

#include <feedwindow.h>
#include "AI_src/faceRecognition.h"
#include "rectangle.h"
#include <dlib/dir_nav.h>
#include <dialogs/addcameradialog.h>


using namespace std;

namespace Ui {
class Feed;
}

class Feed : public QWidget
{
    Q_OBJECT

public:
    explicit Feed(int inx,int w, int h, QMutex *qm, std::vector<std::string> &names, std::vector<dlib::matrix<float,0l,1l>> &descriptors, QWidget *parent = 0);
    ~Feed();


    QTimer *blinkTimer;
    bool color=true;
    bool blinking = false;

    QThread *thread;
    Camera *cam;
    QMutex *mutex;
    int indx;
    std::vector<std::string> &face_names;
    std::vector<dlib::matrix<float,0l,1l>> &face_descriptors;
    QString FACE_TO_SEARCH, OBJECT_TO_SEARCH;
    int COLOR_TO_SEARCH;
    int COLOR_VARIANCE = 15;
    double COLOR_ACCEPTANCE_PERCENTAGE = .35;



    std::vector<dlib::matrix<float,0l,1l>> blacklist_descriptors;

    void set_blacklist_descriptor(std::vector<dlib::matrix<float,0l,1l>> blacklist);

    void blinkOn();
    void blinkOff();


    QPushButton *addCameraButton;
    QPushButton *closeCameraButton;
    QPushButton *enlargeCameraButton;
    QPushButton *tilesButton;

    void setSizes(int, int);

    void setButtonPlacements(int);

    void face_database_update();

    bool cameraSet= false;

    void search_requested(QString face, int color, QString obj);

    FeedWindow *feedWindow;
    bool enlargedOn= false;

    dlib::array2d<dlib::rgb_pixel> tracking_img;
    dlib::correlation_tracker tracker;

    bool mClicked= false, tracking = false;
    int X,Y;

    bool ptzType;

    int priority;

    bool facesWin=false;

    Faces *facesWindow;

    void reset_object_threshold();


private:
    Ui::Feed *ui;
   // QThread *thread;

   // Worker *worker;

signals:
    void emitFace(cv::Mat, int);
    void emitLP(QPixmap, int);
    void emitVideoFeed(QPixmap);
    void emitTile(QPixmap , QString, int);
    void notify(QPixmap, QString, int);
    //void notifyLPR(QPixmap,QString, QString);
   // void requestUpdateLPR(QString initial);

public slots:
    void addCamera(bool);
    void initializeCamera(QString, QString, bool, bool Fprior, bool Lprior);
    void initializeCameraMain(QString camera, int prior);
    void closeCamera(bool);
    void enlargeCamera(bool);
    void tilesOpen(bool);
    void update_ui(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >);
    void changeColor();
    void faceStation(cv::Mat, int);
    void lprStation(QPixmap , int);
    void closeEnlargedWindow(int);
    void closeTilesWindow(int);
// void addNewLPR(QString enc);

protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *);


};

#endif // FEED_H
