#include "vd_face.h"
#include "ui_vd_face.h"

VD_Face::VD_Face(QWidget *parent, QPixmap pic) :
    QWidget(parent),
    ui(new Ui::VD_Face)
{
    ui->setupUi(this);
//    this->show();
    pic = pic.scaledToWidth(ui->faceLabel->width(), Qt::SmoothTransformation);
    pic = pic.scaledToHeight(ui->faceLabel->height(), Qt::SmoothTransformation);
    ui->faceLabel->setPixmap(pic);
//    ui->faceLabel->setScaledContents( true );

//    ui->faceLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

//    image = image.scaledToWidth(ui->faceLabel->width(), Qt::SmoothTransformation);
//    image = image.scaledToHeight(ui->faceLabel->height(), Qt::SmoothTransformation);
//    ui->faceLabel->setPixmap(QPixmap::fromImage(image));
}
//void VD_Face::setObject(QPixmap pic, QString name, int cam)
//{
////    //qDebug()<<"set object call"<<cam++;;

//    //pictr = pic;
////    ui->faceLabel->setPixmap(pic);
////    ui->faceLabel->setScaledContents( true );
////    ui->faceLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
//    //ui->faceLabel->setToolTip("Name: "+ name + "\n" + "camera: " + QString::number(cam) + "\n" + getCurrentTime());

//}

VD_Face::~VD_Face()
{
    delete ui;
}
