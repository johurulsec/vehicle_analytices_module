#include "face.h"
#include "ui_face.h"

Face::Face(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Face)
{
    ui->setupUi(this);
    id=-1;
}

Face::~Face()
{
    delete ui;
}

void Face::setFace(QPixmap pic, QString name, int cam, int cluster)
{
    qDebug()<<"setFace call";
    cam++;
    id= cluster;
    pictr = pic;
    ui->faceLabel->setPixmap(pic);
    ui->faceLabel->setScaledContents( true );
    ui->faceLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->faceLabel->setToolTip("Name: "+ name + "\n" + "camera: " + QString::number(cam) + "\n" + getCurrentTime() + "\n" + QString::number(cluster));
    //delete pic;

}

void Face::setObject(QPixmap pic, QString name, int cam)
{
    ////qDebug()<<"set object call";
    cam++;
    pictr = pic;
    ui->faceLabel->setPixmap(pic);
    ui->faceLabel->setScaledContents( true );
    ui->faceLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->faceLabel->setToolTip("Name: "+ name + "\n" + "camera: " + QString::number(cam) + "\n" + getCurrentTime());
}

void Face::removeObject(QPixmap pic, QString name, int cam)
{
    // cam++;
    // ui->faceLabel->clear();

    // ui->faceLabel->setScaledContents( true );
    //  ui->faceLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    // ui->faceLabel->setToolTip("Name: "+ name + "\n" + "camera: " + QString::number(cam) + "\n" + getCurrentTime());
}

QString Face::getCurrentTime()
{
    QDateTime current = QDateTime::currentDateTime();
    return current.toString("yyyy-MM-dd-hh-mm-ss");
}

void Face::mousePressEvent(QMouseEvent *e)
{
    ////qDebug()<<"thread id of face cls "<<thread()->currentThreadId();
    qDebug()<<"mousepress event call";

    if(e->buttons() == Qt::LeftButton){
//        emit emitPicDB(pictr);
        emit emitCluster(id);
        ////qDebug() << "hello mousepress Left" << endl;
    }

    else if(e->buttons() == Qt::RightButton){
//        emit emitPicDB(pictr);
        emit emitCluster(id);
        ////qDebug() << "hello mousepress right" << endl;
    }
}

void Face::mouseDoubleClickEvent(QMouseEvent *)
{
    qDebug() << "mouse double click event call" << endl;
    emit emitCluster(id);
}
