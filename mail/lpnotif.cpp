#include "lpnotif.h"
#include "ui_lpnotif.h"

LPNotif::LPNotif(QPixmap pic, QString name, QString cam, QString time,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LPNotif)
{
    ui->setupUi(this);

    ui->image->setPixmap(pic);
    ui->image->setScaledContents( true );
    ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    QPixmap picMatch;
    QString dir = "./faces/temp_late/";
    QString path = dir+name+".jpg";

    QPixmap imgMatch(path);
    picMatch = imgMatch;

    ui->imageMatch->setPixmap(picMatch);
    ui->imageMatch->setScaledContents( true );
    ui->imageMatch->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );



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
    ui->text->setText("Attention !! \n <" + name + "Match:: " + cam + " \n Time:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));

}

LPNotif::~LPNotif()
{
    delete ui;
}
