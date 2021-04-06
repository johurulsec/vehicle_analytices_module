#ifndef FACES_H
#define FACES_H

#include <QDialog>
#include <face.h>
#include <flowlayout.h>
#include <faces.h>
#include <dialogs/clusterdialog.h>

#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <QWidget>
#include <QScrollBar>
#include <QDialog>
#include <QQueue>

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>

#include<iostream>
#include<cstdio>
#include "QThread"
#include "lpr.h"
#include "QSet"

using namespace  std;

QT_BEGIN_NAMESPACE

class QGridLayout;

QT_END_NAMESPACE

namespace Ui {
class Faces;
}




class Faces : public QDialog
{
    Q_OBJECT

public:
    explicit Faces(QWidget *parent = 0);
    ~Faces();

    //    QThread *thread;
    //     Worker *worker;
    QList<QList<Face*>> allFaces;
    QHBoxLayout *layout;
    QGridLayout *mainLayout;
    // QLayoutItem *horizontalLayout;
    FlowLayout *flowLayout;
    FlowLayout *flowLayout2;
    FlowLayout *flowLayout3;
    FlowLayout *flowLayout4;

    void addFR(QPixmap, QString, int);
    void addObject(QPixmap, QString, int);
    void addLPR(QPixmap pic, QString name, int idx);
    void addFaceRecognized(QPixmap pic, QString name, int idx);
    bool isScroll;

    std::vector<dlib::matrix<float,(long)0,(long)1>> cluster_templates;

    void clearLayout(QLayout *layout);
    void remove(QGridLayout *layout, int row, int column, bool deleteWidgets);
    void deleteChildWidgets(QLayoutItem *item);
    void removeRow(QGridLayout *layout, int row, bool deleteWidgets);


    cv::Mat QImageToMat(const QImage& src);

    int sameFacesTimesIdCount[112345]={0};

    int flg = 2;
    int storeInitClValue, cnttag = 3;

public slots:
    //void addLPR(QPixmap, QString, int);
    void receiveTile(QPixmap, QString, int);
    void receiveTileLP(QPixmap, QString, int);
    void displayCluster(int);
    void addUniqueFace(QPixmap, QPixmap, QString, int, dlib::matrix<float,(long)0,(long)1>, double, int, int, QString, int);
    void addUniqueFace(QPixmap, QPixmap, QString, int, dlib::matrix<float,(long)0,(long)1>, double, int, int, QString, int, QString);
    void justcheck(QPixmap);
    void addUniqueFaceToTiles(QPixmap , QString , int , dlib::matrix<float,0,1> );
    void only_uniqueFace_show_inTiles(QPixmap , QString , int);
    void uniqueLicencePlateShowInTiles(QPixmap , QString , int, QString);

private slots:
    void add_recog_face_To_tiles(QPixmap , QString , int);

signals:
    void notifyLPR(QPixmap p, QString str, int indx);

    void notifyFaceFromUniqueFace(QPixmap, QPixmap, QString, int, int, int, double, QString, int);
    void notifyFaceFromUniqueFace(QPixmap, QPixmap, QString, int, int, int, double, QString, int, QString);
    void emitPicDB_mw_signal(QPixmap);
    void unique_face_to_main_window(QPixmap, QString, int, int, int, double, int, QString, int);

private:
    Ui::Faces *ui;
    int i=0;
    /*Update parts by Basedul and Johurul*/
        QGridLayout *grid_show_all_faces; // faces show in Grid layout
        int row_index = 0; int column_index = 0; // Grid layout index
        QList<Face*> faceList; // List, used for hold face.
        int cnt_test=0;

        QGridLayout *grid_show_uniq_faces;
        int row_index_u = 0; int column_index_u = 0;
        QList<Face*> uniq_faceList; // List, used for hold uniq face.

        QGridLayout *grid_show_recog_faces;
        int row_index_r = 0; int column_index_r = 0;
        QList<Face*> recog_faceList;

        QGridLayout *grid_show_unique_lpr;
        int row_index_lpr = 0; int column_index_lpr = 0;
        QList<Lpr*> uniqueLprList;
        QSet<QString>setlpr;
        int updateCheckerLpr = 0;
        int cker = 0;

signals:
    void requestUpdateLPR(QPixmap pic, QString str, int indx);
    //  void requestUpdateR(QPixmap pic, QString str, int indx);

};

#endif // FACES_H
