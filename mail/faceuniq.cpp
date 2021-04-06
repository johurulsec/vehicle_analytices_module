//#include "faceuniq.h"
//#include "ui_faceuniq.h"

//faceUniq::faceUniq(QPixmap pic, QString name, QString cam, QString cluster, QString imgTimes, double confidence, QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::faceUniq)
//{
//    ui->setupUi(this);

//    ui->label_uniq_image->setPixmap(pic);
//    ui->label_uniq_image->setScaledContents( true );
//    ui->label_uniq_image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

//    QPalette sample_palette;
//    sample_palette.setColor(QPalette::Window, Qt::black);
//    sample_palette.setColor(QPalette::WindowText, Qt::black);
//    i++;

//    ui->label_uniq_details->setPalette(sample_palette);

//    ui->label_uniq_details->setText("Name: "+name +"\nTime:: " + QTime::currentTime().toString() +"\nDate::" +  QDate::currentDate().toString("dd.MM.yyyy")+"\nTimes: "+imgTimes +"\nConfidence:" + QString::number(confidence));
//    //qDebug()<<"face uniq constr call "<<++cntt;

//    pictr = pic;
//}

//faceUniq::~faceUniq()
//{
//    //qDebug()<<"face uniq destructor call";
//    delete ui;
//}

//void faceUniq::mousePressEvent(QMouseEvent *e)
//{
//    //qDebug()<<"mouse event of faceuniq";

//    if(e->buttons() == Qt::LeftButton){
//        emit emt_uniq_fce(pictr);
//        //qDebug() << "faceuniq mousepress Left" << endl;
//    }

//    else if(e->buttons() == Qt::RightButton){
//        emit emt_uniq_fce(pictr);
//        //qDebug() << "faceuniq mousepress right" << endl;
//    }
//}


#include "faceuniq.h"
#include "ui_faceuniq.h"

faceUniq::faceUniq(QPixmap pic, QString name, double confidence, int recognized, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::faceUniq)
{
    ui->setupUi(this);

    qDebug()<<"face unique call";

    ui->label_uniq_image->setPixmap(pic);
    ui->label_uniq_image->setScaledContents( true );
    ui->label_uniq_image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::black);
    sample_palette.setColor(QPalette::WindowText, Qt::black);

    if(recognized == 1){
        //this->setStyleSheet("border: 5px solid rgb(51, 255, 51);");//blue
        this->setStyleSheet("/*background-color: rgb(255,0,0); margin:5px;*/ border:3px solid rgb(0, 179, 0); ");//blue
    }else if(recognized != 1){
//        this->setStyleSheet("border: 5px solid rgb(255, 102, 102);");//red
        this->setStyleSheet("/*background-color: rgb(255,0,0); margin:5px;*/ border:3px solid rgb(153, 0, 0); ");//blue
    }

    i++;

    ui->label_date_time->setPalette(sample_palette);
    ui->label_name_confid->setPalette(sample_palette);

    ui->label_date_time->setText("Time:: " + QTime::currentTime().toString() +"\nDate::" +  QDate::currentDate().toString("dd.MM.yyyy"));
    ui->label_name_confid->setText("Name: "+name +"\nConfidence:" + QString::number(confidence));
    ////qDebug()<<"face uniq constr call "<<++cntt;

    pictr = pic;
}

faceUniq::faceUniq(QPixmap pic, QString name, double confidence, int recognized,  QString gender, int age, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::faceUniq)
{
    ui->setupUi(this);

    ui->label_uniq_image->setPixmap(pic);
    ui->label_uniq_image->setScaledContents( true );
    ui->label_uniq_image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::black);
    sample_palette.setColor(QPalette::WindowText, Qt::black);

    if(recognized == 1){
        qDebug()<<"recog of faceuniq ";
        //this->setStyleSheet("border: 5px solid rgb(51, 255, 51);");//blue
        this->setStyleSheet("/*background-color: rgb(255,0,0); margin:5px;*/ border:3px solid rgb(0, 179, 0); ");//blue
    }else if(recognized != 1){
        qDebug()<<"not recog of faceuniq ";
//        this->setStyleSheet("border: 5px solid rgb(255, 102, 102);");//red
        this->setStyleSheet("/*background-color: rgb(255,0,0); margin:5px;*/ border:3px solid rgb(153, 0, 0); ");//blue
    }

    i++;

    ui->label_date_time->setPalette(sample_palette);
    ui->label_name_confid->setPalette(sample_palette);

    ui->label_date_time->setText("Time:: " + QTime::currentTime().toString() +"\nDate::" +  QDate::currentDate().toString("dd.MM.yyyy"));
//    ui->label_name_confid->setText("Mask status : "+name +"\nConfidence:" + QString::number(confidence)+"\nGender: "+gender+"\nAge: "+QString::number(age));
    ui->label_name_confid->setText("Name : "+name +"\nConfidence:" + QString::number(confidence));
    qDebug()<<"face uniq constr call "<<++cntt;

    pictr = pic;
}

faceUniq::~faceUniq()
{
    //qDebug()<<"face uniq destructor call";
    delete ui;
}

void faceUniq::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"mouse event of faceuniq";

    if(e->buttons() == Qt::LeftButton){
        emit emt_uniq_fce(pictr);
        //qDebug() << "faceuniq mousepress Left" << endl;
    }

    else if(e->buttons() == Qt::RightButton){
        emit emt_uniq_fce(pictr);
        //qDebug() << "faceuniq mousepress right" << endl;
    }
}
