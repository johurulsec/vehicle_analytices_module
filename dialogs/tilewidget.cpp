#include "tilewidget.h"
#include "ui_tilewidget.h"

TileWidget::TileWidget(QPixmap pic, QString name, long time,int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TileWidget)
{
    ui->setupUi(this);
    tilePic = pic;
    tileName = name;
    tileTime = time;
    ui->imageLabel->setPixmap(tilePic);
    clusterId=id;

    this->setToolTip("Name: "+ name + "\n" + "time: " + QString::number((int)time));

}

TileWidget::~TileWidget()
{
    delete ui;
}

void TileWidget::mousePressEvent(QMouseEvent *e)
{

}

void TileWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        emit goToTile(tileTime);
        emit emitCluster(clusterId);
    }
}
