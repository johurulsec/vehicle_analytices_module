#include "lpsinglewidg.h"
#include "ui_lpsinglewidg.h"
#include <QTime>
#include<QDebug>

LpSingleWidg::LpSingleWidg(QPixmap m_pic, QPixmap pic, QString name, QString cam, QString time,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LpSingleWidg)
{
    qDebug()<<"main pic w : "<<m_pic.width()<<" h : "<<m_pic.height();
    qDebug()<<"lp pic w : "<<pic.width()<<" h : "<<pic.height();

    ui->setupUi(this);
    ui->image->setPixmap(pic);
    ui->image->setScaledContents( true );
    ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    ui->main_pic->setPixmap(m_pic);
    ui->main_pic->setScaledContents( true );
    ui->main_pic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    QPixmap picMatch;
    QString dir = "./faces/temp_late/";
    QString path = dir+name+".jpg";

    QPixmap imgMatch(path);
    picMatch = imgMatch;

//    ui->imageMatch->setPixmap(picMatch);
//    ui->imageMatch->setScaledContents( true );
//    ui->imageMatch->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    if(name.mid(0, 1) != "!"){
            ui->image->setStyleSheet("border: 3px solid rgb(0, 179, 0);");//blue
            ui->text->setStyleSheet("border: 3px solid rgb(0, 179, 0);");//blue
            ui->main_pic->setStyleSheet("border: 3px solid rgb(0, 179, 0);");
        }else if(name.mid(0, 1) == "!"){
            ui->image->setStyleSheet("border: 3px solid rgb(153, 0, 0);");//red
            ui->text->setStyleSheet("border: 3px solid rgb(153, 0, 0);");//red
            name.remove(0, 1);
        }

    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::black);
    sample_palette.setColor(QPalette::WindowText, Qt::black);
    i++;
    //    QString faceNo = QString::number(i);
    //   // ui->text->setAutoFillBackground(true);
    //    ui->text->setPalette(sample_palette);
    // //   sample_label->setText("What ever text");
    //    ui->text->setText("Attention !! \n <" + name + " > \n Spotted !!  \n Camera No:: " + cam + " \n Time:: " + QTime::currentTime().toString());// +"No"+ faceNo);
    //   ui->horizontalLayout_2->setStyleSheet("background-color: rgb(255, 0, 0);");
    //ui->searchFaceButton->setStyleSheet("background-color: rgba(255, 0, 0, 150);");

    QString faceNo = QString::number(i);
    // ui->text->setAutoFillBackground(true);
    ui->text->setPalette(sample_palette);
    //   sample_label->setText("What ever text");
//    ui->text->setText(name + "\nConfidence: 98 \nTime:: " + QTime::currentTime().toString() + "\nDate::" +  QDate::currentDate().toString("dd.MM.yyyy"));// for person
    ui->text->setText(name + "\nCameraNo: " + cam + "\nTime:: " + QTime::currentTime().toString() + "\nDate::" +  QDate::currentDate().toString("dd.MM.yyyy"));// for overcrowd

}

LpSingleWidg::~LpSingleWidg()
{
    delete ui;
}
