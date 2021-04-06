#include "searchbygivenimage.h"
#include "ui_searchbygivenimage.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
SearchByGivenImage::SearchByGivenImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchByGivenImage)
{
    ui->setupUi(this);
}

SearchByGivenImage::~SearchByGivenImage()
{
    delete ui;
}

void SearchByGivenImage::on_pushButton_select_img_clicked()
{
    given_img = QFileDialog::getOpenFileName(this,
                                             tr("Open Image"), "/home", tr("Image Files (*.png)"));

    if(QString::compare(given_img, "") != 0){
        //        img_file_ch = true;
        QImage image;
        bool valid/* = true*/ = image.load(given_img);
        if(valid){
            img_file_ch = true;
            QPalette pal = ui->pushButton_select_img->palette();
            pal.setColor(QPalette::Button, QColor(Qt::blue));
            ui->pushButton_select_img->setAutoFillBackground(true);
            ui->pushButton_select_img->setPalette(pal);
            ui->pushButton_select_img->update();
            image = image.scaledToWidth(ui->label_search_by_img->width(), Qt::SmoothTransformation);
            image = image.scaledToHeight(ui->label_search_by_img->height(), Qt::SmoothTransformation);
            ui->label_search_by_img->setPixmap(QPixmap::fromImage(image));
            //            QPixmap pic(given_img);
            //            ui->label_search_by_img->setPixmap(pic);
        }

    }

}

void SearchByGivenImage::on_pushButton_directory_clicked()
{
    given_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                  "/home",
                                                  QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);
    if(QString::compare(given_dir, "") != 0){
        dir_ch = true;
        ui->pushButton_directory->setText(given_dir);
        QPalette pal = ui->pushButton_directory->palette();
        pal.setColor(QPalette::Button, QColor(Qt::blue));
        ui->pushButton_directory->setAutoFillBackground(true);
        ui->pushButton_directory->setPalette(pal);
        ui->pushButton_directory->update();
    }
}


void SearchByGivenImage::on_pushButton_search_clicked()
{
    //qDebug() << "Hello Basedul islam";

    if( img_file_ch == true && dir_ch == true){
        img_file_ch = false;
        dir_ch = false;
        ui->pushButton_search->setText("Wait...");
        QPalette pal = ui->pushButton_search->palette();
        pal.setColor(QPalette::Button, QColor(Qt::red));
        ui->pushButton_search->setAutoFillBackground(true);
        ui->pushButton_search->setPalette(pal);
        ui->pushButton_search->update();


        emit goMainW(given_img, given_dir);

        QPalette pal1 = ui->pushButton_directory->palette();
        pal1.setColor(QPalette::Button, QColor(Qt::white));
        ui->pushButton_directory->setAutoFillBackground(true);
        ui->pushButton_directory->setPalette(pal1);
        ui->pushButton_directory->update();

        QPalette pal2 = ui->pushButton_select_img->palette();
        pal2.setColor(QPalette::Button, QColor(Qt::white));
        ui->pushButton_select_img->setAutoFillBackground(true);
        ui->pushButton_select_img->setPalette(pal2);
        ui->pushButton_select_img->update();

        ui->label_search_by_img->clear();
        ui->pushButton_directory->setText("Select Dir");

    }else{
        QMessageBox msg_box;
        msg_box.setText("Select again Image and Directory");
        given_dir.clear();
        given_img.clear();
        img_file_ch = false;
        dir_ch = false;
        ui->label_search_by_img->clear();

        msg_box.exec();
    }
}

void SearchByGivenImage::cathList(QStringList list)
{
    if(list.size() != 0){
        ui->comboBox_found_image_list->addItems(list);
        QImage image;
        image.load(ui->comboBox_found_image_list->currentText());
        image = image.scaledToWidth(ui->label_selected_img->width(), Qt::SmoothTransformation);
        image = image.scaledToHeight(ui->label_selected_img->height(), Qt::SmoothTransformation);
        ui->label_selected_img->setPixmap(QPixmap::fromImage(image));
    }else{
        QMessageBox msg_box;
        msg_box.setText("Not found!");
        msg_box.exec();
    }
    ui->pushButton_search->setText("Search");
    QPalette pal = ui->pushButton_search->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->pushButton_search->setAutoFillBackground(true);
    ui->pushButton_search->setPalette(pal);
    ui->pushButton_search->update();

}

void SearchByGivenImage::closeEvent(QCloseEvent *event)
{
//    event->accept();
    ui->comboBox_found_image_list->clear();
    ui->label_selected_img->clear();

    QPalette pal = ui->pushButton_search->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->pushButton_search->setAutoFillBackground(true);
    ui->pushButton_search->setPalette(pal);
    ui->pushButton_search->update();

    QPalette pal1 = ui->pushButton_directory->palette();
    pal1.setColor(QPalette::Button, QColor(Qt::white));
    ui->pushButton_directory->setAutoFillBackground(true);
    ui->pushButton_directory->setPalette(pal1);
    ui->pushButton_directory->update();

    QPalette pal2 = ui->pushButton_select_img->palette();
    pal2.setColor(QPalette::Button, QColor(Qt::white));
    ui->pushButton_select_img->setAutoFillBackground(true);
    ui->pushButton_select_img->setPalette(pal2);
    ui->pushButton_select_img->update();

    ui->label_search_by_img->clear();
    ui->pushButton_directory->setText("Select Dir");
}

void SearchByGivenImage::on_comboBox_found_image_list_activated(const QString &arg1)
{
    QImage image;
    image.load(arg1);
    image = image.scaledToWidth(ui->label_selected_img->width(), Qt::SmoothTransformation);
    image = image.scaledToHeight(ui->label_selected_img->height(), Qt::SmoothTransformation);
    ui->label_selected_img->setPixmap(QPixmap::fromImage(image));

}
