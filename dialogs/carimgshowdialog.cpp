#include "carimgshowdialog.h"
#include "ui_carimgshowdialog.h"

CarImgShowDialog::CarImgShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarImgShowDialog)
{
    ui->setupUi(this);
}

CarImgShowDialog::~CarImgShowDialog()
{
    delete ui;
}

void CarImgShowDialog::carImageSetIntoLabel(int Id, QString path, QImage image)
{
    bool valid = image.load(path);

    qDebug() << "after Image load for showing";
    if (valid){
        qDebug() << "Image found";
        image = image.scaledToWidth(ui->label_car_show->width(), Qt::SmoothTransformation);
        image = image.scaledToHeight(ui->label_car_show->height(), Qt::SmoothTransformation);
        ui->label_car_show->setPixmap(QPixmap::fromImage(image));

    }
    else {
        qDebug() << "Image not found";
         ui->label_car_show->setText("Image not found");
    }
}
