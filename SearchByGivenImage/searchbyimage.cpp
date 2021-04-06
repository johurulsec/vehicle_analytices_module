#include "searchbyimage.h"
#include "ui_searchbyimage.h"
#include <QFileDialog>
#include <QDebug>

SearchByImage::SearchByImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchByImage)
{
    ui->setupUi(this);
}

SearchByImage::~SearchByImage()
{
    delete ui;
}

void SearchByImage::on_pushButton_selectImage_clicked()
{
    QString sel_img = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png)"));
    if(QString::compare(sel_img, "") != 0){
        QImage image;
        bool valid/* = true*/ = image.load(sel_img);
        if(valid){
            QPalette pal = ui->pushButton_selectImage->palette();
            pal.setColor(QPalette::Button, QColor(Qt::red));
            ui->pushButton_selectImage->setAutoFillBackground(true);
            ui->pushButton_selectImage->setPalette(pal);
            ui->pushButton_selectImage->update();
            image = image.scaledToWidth(ui->label_selectImage->width(), Qt::SmoothTransformation);
            image = image.scaledToHeight(ui->label_selectImage->height(), Qt::SmoothTransformation);
            ui->label_selectImage->setPixmap(QPixmap::fromImage(image));
            ui->pushButton_selectImage->setText("Wait...");
            emit fromSearchByImg(sel_img);
        }
    }
}

void SearchByImage::fromMain_Wark(QStringList list)
{
    if(list.size() != 0){
        ui->comboBox_get_imagePath->addItems(list);
        QImage image;
        image.load(ui->comboBox_get_imagePath->currentText());
        image = image.scaledToWidth(ui->label_get_img->width(), Qt::SmoothTransformation);
        image = image.scaledToHeight(ui->label_get_img->height(), Qt::SmoothTransformation);
        ui->label_get_img->setPixmap(QPixmap::fromImage(image));
        QPalette pal = ui->pushButton_selectImage->palette();
        pal.setColor(QPalette::Button, QColor(Qt::white));
        ui->pushButton_selectImage->setAutoFillBackground(true);
        ui->pushButton_selectImage->setPalette(pal);
        ui->pushButton_selectImage->update();
        ui->pushButton_selectImage->setText("select");
    }else{
        QPalette pal = ui->pushButton_selectImage->palette();
        pal.setColor(QPalette::Button, QColor(Qt::white));
        ui->pushButton_selectImage->setAutoFillBackground(true);
        ui->pushButton_selectImage->setPalette(pal);
        ui->pushButton_selectImage->update();
        ui->pushButton_selectImage->setText("select");
        ui->label_get_img->setText("Couldn't Found!");
    }

}

void SearchByImage::closeEvent(QCloseEvent *event)
{
    ui->comboBox_get_imagePath->clear();
    ui->label_get_img->clear();
    ui->label_selectImage->clear();
    QPalette pal = ui->pushButton_selectImage->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->pushButton_selectImage->setAutoFillBackground(true);
    ui->pushButton_selectImage->setPalette(pal);
    ui->pushButton_selectImage->update();
    ui->pushButton_selectImage->setText("select");

}

void SearchByImage::on_comboBox_get_imagePath_activated(const QString &arg1)
{
    //qDebug() << "ComboBox_get_imagePath";
    QImage image;
    image.load(arg1);
    image = image.scaledToWidth(ui->label_get_img->width(), Qt::SmoothTransformation);
    image = image.scaledToHeight(ui->label_get_img->height(), Qt::SmoothTransformation);
    ui->label_get_img->setPixmap(QPixmap::fromImage(image));
}
