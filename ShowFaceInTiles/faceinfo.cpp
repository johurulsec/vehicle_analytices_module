#include "faceinfo.h"
#include "ui_faceinfo.h"

FaceInfo::FaceInfo(QWidget *parent, QPixmap pic) :
    QWidget(parent),
    ui(new Ui::FaceInfo)
{
    ui->setupUi(this);
    ui->label_pic->setPixmap(pic);
    ui->label_pic->setScaledContents( true );
    ui->label_pic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}



FaceInfo::~FaceInfo()
{
    delete ui;
}
