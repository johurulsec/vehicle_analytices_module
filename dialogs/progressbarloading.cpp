#include "progressbarloading.h"
#include "ui_progressbarloading.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
ProgressBarLoading::ProgressBarLoading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBarLoading)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
//    ui->progressBar_loading->setMinimum(0);
//    ui->progressBar_loading->setMaximum(100);
    connect(this, SIGNAL(valueChange(int)), ui->progressBar_loading, SLOT(setValue(int)));
}

ProgressBarLoading::~ProgressBarLoading()
{
    delete ui;
}

void ProgressBarLoading::setProgressBarMaximumValue(float max)
{
    this->max = max;
}

void ProgressBarLoading::progressOperation(int num)
{
    this->min += (float) 100/differ;
    //qDebug() << "Min = ----------" << min;
    emit valueChange(this->min);


//    ui->progressBar_loading->setMaximum((int)max);
//    ui->progressBar_loading->setMinimum((int)min);
//    this->show();
//    float val =(float) 100/num;
//    while(min<=max){
//        if(min==max){
//            this->close();
//            break;
//        }
//        emit valueChange(min);
//        QEventLoop loop;
//        QTimer::singleShot(1000, &loop, SLOT(quit()));
//        loop.exec();
//        min+=val;
//    }
//    this->show();
//    ui->progressBar_loading->setMaximum(max);
//    while(max>=1){
//        emit valueChange(max);
//        QEventLoop loop;
//        QTimer::singleShot(1000, &loop, SLOT(quit()));
//        loop.exec();
//        //qDebug() << "Max komate hobe ";
////        ui->progressBar_loading->setValue(max);
//        --max;
    //    }
}

void ProgressBarLoading::setProgressBarMinimumValue(float min)
{
    this->min = min;
}

void ProgressBarLoading::setMinMax(int min, int max)
{
    this->min = min;
    this->max = max;
    ui->progressBar_loading->setMaximum(max);
    ui->progressBar_loading->setMinimum(min);

}

void ProgressBarLoading::resetData()
{
    differ = 0; min = 0; max = 0;
    ui->progressBar_loading->reset();
}

void ProgressBarLoading::setDiffer(int differ)
{
    this->differ = differ;
    this->show();
}
