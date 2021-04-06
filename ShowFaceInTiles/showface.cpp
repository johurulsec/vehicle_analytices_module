#include "showface.h"
#include "ui_showface.h"
#include <QPushButton>
#include <QDebug>

ShowFace::ShowFace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowFace)
{
    ui->setupUi(this);
    grid_lay = new QGridLayout();
//    facelist = new QList<FaceInfo*>();
    ui->scrollArea_grid->setLayout(grid_lay);
//    for(int i = 0; i < 10; i++){
//        for (int j = 0; j < 10; j++){
//            QPushButton *btn = new QPushButton("Ok");
//            grid_lay->addWidget(btn, i, j);
//        }
//    }
}

ShowFace::~ShowFace()
{
    delete ui;
}

void ShowFace::addFr(QPixmap pic)
{
    //qDebug() << "AddFr";
//    for(int i = 0; i < 10; i++){
//        for (int j = 0; j < 10; j++){
//            QPushButton *btn = new QPushButton("Ok");
//            grid_lay->addWidget(btn, i, j);
//        }
//    }
    FaceInfo *face = new FaceInfo(this, pic);

    if(facelist.size()<100){
        facelist.push_back(face);
        grid_lay->addWidget(face, row_index, column_index);
    }else{
        delete facelist.at(0);
        facelist.removeFirst();
        facelist.push_back(face);

        QListIterator<FaceInfo*> iter(facelist);
        iter.toFront();

        for(int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                grid_lay->addWidget(iter.next(), i, j);
            }
        }
    }

    if(column_index == 10){
        row_index++;
        column_index=-1;
    }
    if(row_index == 10){
        row_index = 0;
    }
    column_index++;
}

