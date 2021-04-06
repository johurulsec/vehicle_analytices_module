#include "lpr.h"
#include "ui_lpr.h"

Lpr::Lpr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lpr)
{
    ui->setupUi(this);
}

Lpr::~Lpr()
{
    delete ui;
}

void Lpr::setObjectLpr(QPixmap pic, QString name, int cam, QString color)
{
    qDebug()<<"set objectLpr call";
    cam++;
    pictr = pic;
    ui->lprLabel->setPixmap(pic);
    ui->lprLabel->setScaledContents( true );
    ui->lprLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->lprLabel->setToolTip("Name: "+ name + "\nColor: "+color+"\nCamera: " + QString::number(cam) + "\n" + getCurrentTime());

}

QString Lpr::getCurrentTime()
{
    QDateTime current = QDateTime::currentDateTime();
    return current.toString("yyyy-MM-dd-hh-mm-ss");
}
