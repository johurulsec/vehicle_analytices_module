#include "imageshowdialog.h"
#include "ui_imageshowdialog.h"

ImageShowDialog::ImageShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageShowDialog)
{

    ui->setupUi(this);

}

//ImageShowDialog::ImageShowDialog(int Id, QString path, QImage image, QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::ImageShowDialog)
//{

//    ui->setupUi(this);
//    //qDebug() << "Image path ++++" << path;
//    this->Id = Id;

//    if(QString::compare(path, QString()) != 0){
//        bool valid = image.load(path);
//        if (valid){
//            //qDebug() << "Image found";
//            image = image.scaledToWidth(ui->label_image_show_d->width(), Qt::SmoothTransformation);
//            image = image.scaledToHeight(ui->label_image_show_d->height(), Qt::SmoothTransformation);
//            ui->label_image_show_d->setPixmap(QPixmap::fromImage(image));
//        }
//        else {
//             ui->label_image_show_d->setText("Image not found");
//        }
//    }else {
//        //qDebug() << "path is empty";
//    }

//}


ImageShowDialog::~ImageShowDialog()
{
    //qDebug() << "Image show dialog destructor called!";
    delete ui;
}

void ImageShowDialog::imageSetIntoLabel(int Id, QString path, QImage image)
{
    qDebug() << "Image path ++++" << path;
    this->Id = Id;

    if(QString::compare(path, QString()) != 0){
        qDebug() << "before Image load for showing";
        bool valid = image.load(path);
        qDebug() << "after Image load for showing";
        if (valid){
            qDebug() << "Image found";
            image = image.scaledToWidth(ui->label_image_show_d->width(), Qt::SmoothTransformation);
            image = image.scaledToHeight(ui->label_image_show_d->height(), Qt::SmoothTransformation);
            ui->label_image_show_d->setPixmap(QPixmap::fromImage(image));

        }
        else {
            qDebug() << "Image not found";
             ui->label_image_show_d->setText("Image not found");
        }
    }else {
        qDebug() << "path is empty";
    }
}

void ImageShowDialog::on_pushButton_modify_clicked()
{
    emit modifyDbInfo(Id);
    this->close();
}
