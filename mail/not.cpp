#include "not.h"
#include "ui_not.h"
#include <QDesktopWidget>

Not::Not(QPixmap pic, QString name, QString cam, double confidence, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Not)
{
    ui->setupUi(this);

    ui->image->setPixmap(pic);
    ui->image->setScaledContents( true );
    ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    //qDebug() << "Geometry of not widget = "<< QWidget::frameGeometry().height();
    this->setStyleSheet("/*background-color: rgb(255,0,0); margin:5px;*/ border:3px solid rgb(153, 0, 0); ");//blue

    QPixmap picMatch;
    QString dir = "./faces/temp_late2/";
    QString path = dir+name+".png";

    // QString path;
    //    if(connectionDB()){
    //        QSqlQuery que;
    //        que.prepare("select image_path from ADD_FACE where name = ?;");
    //        que.addBindValue(name);
    //        if(que.exec()){
    //            path = que.value(0).toString();
    //        }
    //        que.clear();
    //    }

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

    //QString faceNo = QString::number(i);
    // ui->text->setAutoFillBackground(true);
    ui->text->setPalette(sample_palette);
    //   sample_label->setText("What ever text");

    //    modal = new QSqlQueryModel();

    //    name = "%"+name+"%";

    //    if(connectionDB()){
    //        //qDebug()<<"connectiondb of Not cpp";
    //        QSqlQuery query;
    //        query.prepare("select position, address, phone from ADD_FACE where (name Like :search_info)");
    //        query.bindValue(":search_info", name);

    //        if(query.exec()){
    //            query.first();
    //            QString position = query.value(0).toString();
    //            QString address = query.value(1).toString();
    //            QString phone = query.value(2).toString();
    //            //qDebug() << "Position +++" << position << endl;
    //            if(position.length()>=3){
    //                ui->text->setText("Name: "+name +"\nPosition: "+position+"\nAddress: "+address+"\nPhone: "+phone +"\nTime:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
    //            }else {
    //                ui->text->setText("Attention !! \n <" + name + "> \n Match:: " + cam + " \n Time:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
    //            }
    //        }
    //    }
    ////qDebug()<<"confidence value in not.cpp "<<confidence;
    ui->text->setText("Name: "+name +"\nTime:: " + QTime::currentTime().toString() +"\nDate::" +  QDate::currentDate().toString("dd.MM.yyyy")+"\nConfidence:" + QString::number(confidence));

}

Not::Not(QPixmap m_pic, QPixmap pic, QString name, QString cam,
         QString cluster, QString imgTimes, double confidence, QString gender, int age, QWidget *parent, QString color) :
    QWidget(parent),
    ui(new Ui::Not)
{
    ui->setupUi(this);
    //    qDebug() << "Dhiscao .....";
    ui->image->setPixmap(pic);
    ui->image->setScaledContents( true );
    ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    ui->imageMatch->setPixmap(m_pic);
    ui->imageMatch->setScaledContents( true );
    ui->imageMatch->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    ui->text->setText("Mask status: "+name +"\nColor status:"+color+"\nTime:: " + QTime::currentTime().toString() +"\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy")+"\nTimes: "+imgTimes +"\nConfidence:" + QString::number(confidence)+"\nGender:"+gender+"\nAge:"+QString::number(age));

    //qDebug() << "Geometry of not widget = "<< QWidget::frameGeometry().height();
    this->setStyleSheet("/*background-color: rgb(255,0,0); margin:5px;*/ border:3px solid rgb(0, 179, 0); ");//blue
    //    QSize newSize( QWidget::frameGeometry().width()-100, QWidget::frameGeometry().height() );

    //    this->setGeometry(
    //                QStyle::alignedRect(
    //                    Qt::LeftToRight,
    //                    Qt::AlignCenter,
    //                    newSize,
    //                    qApp->desktop()->availableGeometry()
    //                    ));
    QPixmap picMatch;
    //    QString dir = "./faces/temp_late/";
    //    QString path = dir+name+".png";

    // QString path;
    //    if(connectionDB()){
    //        QSqlQuery que;
    //        que.prepare("select image_path from ADD_FACE where name = ?;");
    //        que.addBindValue(name);
    //        if(que.exec()){
    //            path = que.value(0).toString();
    //        }
    //        que.clear();
    //    }

    //    QPixmap imgMatch(path);
    //    picMatch = imgMatch;

    //    ui->imageMatch->setPixmap(picMatch);
    //    ui->imageMatch->setScaledContents( true );
    //    ui->imageMatch->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );



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

    //QString faceNo = QString::number(i);
    // ui->text->setAutoFillBackground(true);
    ui->text->setPalette(sample_palette);
    //   sample_label->setText("What ever text");

    //    modal = new QSqlQueryModel();

    //    name = "%"+name+"%";
    //    if(connectionDB()){
    //        //qDebug()<<"connectiondb of Not cpp";
    //        QSqlQuery query;
    //        query.prepare("select position, address, phone, image_path from ADD_FACE where (name = :search_info)");
    //        query.bindValue(":search_info", name);

    //        if(query.exec()){
    //            query.first();
    //            QString path = query.value(3).toString();
    //            QPixmap imgMatch(path);
    //            picMatch = imgMatch;
    //            ui->imageMatch->setPixmap(picMatch);
    //            ui->imageMatch->setScaledContents( true );
    //            ui->imageMatch->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    //            ui->text->setText("Name: "+name +"\nTime:: " + QTime::currentTime().toString() +"\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy")+"\nTimes: "+imgTimes +"\nConfidence:" + QString::number(confidence)+"\nGender:"+gender+"\nAge:"+QString::number(age));
    ////            QString position = query.value(0).toString();
    ////            QString address = query.value(1).toString();
    ////            QString phone = query.value(2).toString();
    ////            //qDebug() << "Position +++" << position << endl;
    ////            if(position.length()>=3){
    ////                ui->text->setText("Name: "+name +"\nPosition: "+position+"\nAddress: "+address+"\nPhone: "+phone +"\nTime:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
    ////            }else {
    ////                ui->text->setText("Attention !! \n <" + name + "> \n Match:: " + cam + " \n Time:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
    ////            }
    //        }
    //    }
    ////qDebug()<<"confidence value in not.cpp "<<confidence;
    //ui->text->setText("Name: "+name +"\nTime:: " + QTime::currentTime().toString() +"\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy")+"\nTimes: "+imgTimes +"\nConfidence:" + QString::number(confidence)+"\nGender:"+gender+", Age:"+QString::number(age));

}


Not::Not(QPixmap pic, QString name, QString cam, QString cluster, QString imgTimes, double confidence, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Not)
{
    ui->setupUi(this);

    ui->image->setPixmap(pic);
    ui->image->setScaledContents( true );
    ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    //qDebug() << "Geometry of not widget = "<< QWidget::frameGeometry().height();
    this->setStyleSheet("/*background-color: rgb(255,0,0); margin:5px;*/ border:3px solid rgb(153, 0, 0); ");//blue
    //    QSize newSize( QWidget::frameGeometry().width()-100, QWidget::frameGeometry().height() );

    //    this->setGeometry(
    //                QStyle::alignedRect(
    //                    Qt::LeftToRight,
    //                    Qt::AlignCenter,
    //                    newSize,
    //                    qApp->desktop()->availableGeometry()
    //                    ));
    QPixmap picMatch;
    QString dir = "./faces/temp_late/";
    QString path = dir+name+".png";

    // QString path;
    //    if(connectionDB()){
    //        QSqlQuery que;
    //        que.prepare("select image_path from ADD_FACE where name = ?;");
    //        que.addBindValue(name);
    //        if(que.exec()){
    //            path = que.value(0).toString();
    //        }
    //        que.clear();
    //    }

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

    //QString faceNo = QString::number(i);
    // ui->text->setAutoFillBackground(true);
    ui->text->setPalette(sample_palette);
    //   sample_label->setText("What ever text");

    //    modal = new QSqlQueryModel();

    //    name = "%"+name+"%";
    if(connectionDB()){
        //qDebug()<<"connectiondb of Not cpp";
        QSqlQuery query;
        query.prepare("select position, address, phone from ADD_FACE where (name Like :search_info)");
        query.bindValue(":search_info", name);

        if(query.exec()){
            query.first();
            QString position = query.value(0).toString();
            QString address = query.value(1).toString();
            QString phone = query.value(2).toString();
            //qDebug() << "Position +++" << position << endl;
            if(position.length()>=3){
                ui->text->setText("Name: "+name +"\nPosition: "+position+"\nAddress: "+address+"\nPhone: "+phone +"\nTime:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
            }else {
                ui->text->setText("Attention !! \n <" + name + "> \n Match:: " + cam + " \n Time:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
            }
        }
    }
    ////qDebug()<<"confidence value in not.cpp "<<confidence;
    ui->text->setText("Name: "+name +"\nTime:: " + QTime::currentTime().toString() +"\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy")+"\nTimes: "+imgTimes +"\nConfidence:" + QString::number(confidence));

}
Not::Not(QPixmap pic, QString name, QString cam, QString cluster, QString imgTimes, double confidence, QString gender, int age, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Not)
{
    ui->setupUi(this);

    ui->image->setPixmap(pic);
    ui->image->setScaledContents( true );
    ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    //qDebug() << "Geometry of not widget = "<< QWidget::frameGeometry().height();
    this->setStyleSheet("/*background-color: rgb(255,0,0); margin:5px;*/ border:3px solid rgb(0, 179, 0); ");//blue
    //    QSize newSize( QWidget::frameGeometry().width()-100, QWidget::frameGeometry().height() );

    //    this->setGeometry(
    //                QStyle::alignedRect(
    //                    Qt::LeftToRight,
    //                    Qt::AlignCenter,
    //                    newSize,
    //                    qApp->desktop()->availableGeometry()
    //                    ));
    //    QPixmap picMatch;

    //    QString dir = "./faces/temp_late2/";
    qDebug() << "before load jpg img from temp j and name: "<<name;
    //    QString path = dir+name+".png";
    QString dir = "./faces/temp_late/";
    QString path = dir+name+".jpg";
    qDebug() << "aftre load jpg img from temp j";

    // QString path;
    //    if(connectionDB()){
    //        QSqlQuery que;
    //        que.prepare("select image_path from ADD_FACE where name = ?;");
    //        que.addBindValue(name);
    //        if(que.exec()){
    //            path = que.value(0).toString();
    //        }
    //        que.clear();
    //    }

    //    QPixmap imgMatch(path);

    QPixmap picMatch = path;

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

    //QString faceNo = QString::number(i);
    // ui->text->setAutoFillBackground(true);
    ui->text->setPalette(sample_palette);
    //   sample_label->setText("What ever text");

    //    modal = new QSqlQueryModel();

    //    name = "%"+name+"%";

    //    if(connectionDB()){
    //        qDebug()<<"connectiondb of Not cpp";
    //        QSqlQuery query;
    //        query.prepare("select position, address, phone, image_path from ADD_FACE where (name = :search_info)");
    //        query.bindValue(":search_info", name);

    //        if(query.exec()){
    //            query.first();
    ////            QString path = query.value(3).toString();
    ////            qDebug() << "path in not.cpp of db : "<<path;
    ////            QPixmap imgMatch(path);
    ////            picMatch = imgMatch;
    ////            ui->imageMatch->setPixmap(picMatch);
    ////            ui->imageMatch->setScaledContents( true );
    ////            ui->imageMatch->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ////            ui->text->setText("Name: "+name +"\nTime:: " + QTime::currentTime().toString() +"\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy")+"\nTimes: "+imgTimes +"\nConfidence:" + QString::number(confidence)+"\nGender:"+gender+"\nAge:"+QString::number(age));

    ////            QString position = query.value(0).toString();
    ////            QString address = query.value(1).toString();
    ////            QString phone = query.value(2).toString();
    ////            //qDebug() << "Position +++" << position << endl;
    ////            if(position.length()>=3){
    ////                ui->text->setText("Name: "+name +"\nPosition: "+position+"\nAddress: "+address+"\nPhone: "+phone +"\nTime:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
    ////            }else {
    ////                ui->text->setText("Attention !! \n <" + name + "> \n Match:: " + cam + " \n Time:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
    ////            }
    //        }
    //    }

    if(connectionDB()){
        qDebug()<<"connectiondb of Not cpp";
        QSqlQuery query;
        //        query.prepare("select position, address, phone, image_path from ADD_FACE where (name = :search_info)");
        query.prepare("select name, position, address, phone, access_pass, image_path from ADD_FACE where (name = :search_info)");
        query.bindValue(":search_info", name);

        if(query.exec()){
            query.first();

            QString name_of_face = query.value(0).toString();
            QString position_face = query.value(1).toString();
            QString address_face = query.value(2).toString();
            QString phone_face = query.value(3).toString();
            QString access_pass_face = query.value(4).toString();
            QString img_path_face = query.value(5).toString();

            QPixmap imgMatch(img_path_face);
            picMatch = imgMatch;
            ui->imageMatch->setPixmap(picMatch);
            ui->imageMatch->setScaledContents( true );
            ui->imageMatch->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

            qDebug() << "name_of_face : "<<name_of_face<<" position_face : "<<position_face<<"address_face : "<<address_face<<" phone_face : "<<phone_face
                     <<" access_pass_face : "<<access_pass_face<<" img_path_face : "<<img_path_face<<endl;

            ui->text->setText("Name: "+name +"\nTime:: " + QTime::currentTime().toString() +"\nDate::" +  QDate::currentDate().toString("dd.MM.yyyy")+"\nConfidence:" + QString::number(confidence));

            //            if(position.length()>=3){
            //                ui->text->setText("Name: "+name +"\nPosition: "+position+"\nAddress: "+address+"\nPhone: "+phone +"\nTime:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
            //            }else {
            //                ui->text->setText("Attention !! \n <" + name + "> \n Match:: " + cam + " \n Time:: " + QTime::currentTime().toString() + "\n Date::" +  QDate::currentDate().toString("dd.MM.yyyy"));
            //            }
        }
    }



//    ui->text->setText("Name: "+name +"\nTime:: " + QTime::currentTime().toString() +"\nDate::" +  QDate::currentDate().toString("dd.MM.yyyy")+"\nConfidence:" + QString::number(confidence));

}

Not::~Not()
{
    delete ui;
}
