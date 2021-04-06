#include "cameralistwidget.h"
#include "ui_cameralistwidget.h"

cameraListWidget::cameraListWidget(QWidget *parent, camera_list_helper cam_info) :
    QWidget(parent),
    ui(new Ui::cameraListWidget)
{
    ui->setupUi(this);

//    cam_info.printCameralistHelper();

    ui->label_cam_list->setText("Name: "+cam_info.getSourceName()+" Enable: "+cam_info.getEnable()+" Type: "+cam_info.getType()+"\n"+"Uri: "+cam_info.getUri()+"\ngpu_id: "+cam_info.getGpuId()+" Number of Source: "+cam_info.getNumSources());
}

cameraListWidget::cameraListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cameraListWidget)
{
    ui->setupUi(this);

    //ui->label_cam_list->setText("Name: "+cam_info.getSourceName()+" Enable: "+cam_info.getEnable()+" Type: "+cam_info.getType()+"\n"+"Uri: "+cam_info.getUri()+"\ngpu_id: "+cam_info.getGpuId()+" Number of Source: "+cam_info.getNumSources());
}

cameraListWidget::~cameraListWidget()
{
    delete ui;
}

void cameraListWidget::addCamWidget(camera_list_helper cam_info)
{
    ui->label_cam_list->setText("Name: "+cam_info.getSourceName()+" Enable: "+cam_info.getEnable()+" Type: "+cam_info.getType()+"\n"+"Uri: "+cam_info.getUri()+"\ngpu_id: "+cam_info.getGpuId()+" Number of Source: "+cam_info.getNumSources());
}

void cameraListWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton){
        emit emitClickedOnCameraInfo();
    }
}
