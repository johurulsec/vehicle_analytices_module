#ifndef TILERDISPLAY_H
#define TILERDISPLAY_H

#include <QDialog>
#include <face.h>
#include <flowlayout.h>

#include <QWidget>
#include <QScrollBar>
#include <QQueue>
#include<QString>
#include<cstring>
#include<iostream>
#include<cstdio>
#include "QSet"
#include <dialogs/clusterdialog.h>
#include "dialogs/carimgshowdialog.h"
#include <QPair>
#include <QVector>

QT_BEGIN_NAMESPACE

class QGridLayout;

QT_END_NAMESPACE

namespace Ui {
class TilerDisplay;
}

class TilerDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit TilerDisplay(QWidget *parent = nullptr);
    ~TilerDisplay();
    void addFR(QPixmap , QString , int );
    void only_uniqueFace_show_inTiles(QPixmap, QPixmap, QString, int, QString);
    QList<Face*> LPwithCarList;

    QVector<QPair<int, QString>> LPwithCarPairVector;
    void clearLPwithCarPairVector();

public slots:
    void displayLPCorespondingCarImage(int);
    void add_search_lp_To_tiles(QPixmap , QString , int, QString);
    void uniqueLicencePlateShowInTiles(QPixmap , QString , int, QString);
    void personShowInTiles(QPixmap , QString , int, QString);

private:
    Ui::TilerDisplay *ui;
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
    QList<Face*> uniqueLprList;

    QGridLayout *grid_show_person;
    int row_index_per = 0; int column_index_per = 0;
    QList<Face*> personList;

    CarImgShowDialog *car_img_show_dialog_obj;
};

#endif // TILERDISPLAY_H
