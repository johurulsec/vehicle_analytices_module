#include "notwidget.h"
#include "ui_notwidget.h"

notWidget::notWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::notWidget)
{
    ui->setupUi(this);
    this->setStyleSheet("border: 8px solid rgb(0, 0, 0);");
    notification_list.clear();
    list.clear();
    //    //qDebug()<<"notwidget constructor here";
    ck=4;
}

notWidget::~notWidget()
{
    notification_list.clear();
    for(int i =0;i<notification_list.size(); i++){
        delete notification_list.at(i);
    }
    list.clear();
    delete ui;
}

void notWidget::addNot(QString clusterId, Not *noti)
{
    qDebug()<<"addnot call test j ";
    if(list.size() < 10)
    {
        qDebug()<<"list size tested "<<list.size();
        QListIterator<int>it(list);
        it.toFront();
        int ck=0;

        for (int j = 0; j<list.size() ; j++) {
            if(it.next() == clusterId.toInt()){// check same image
                qDebug()<<"new Notification 2"<<clusterId;
//                ui->verticalLayout_3->insertWidget(ui->verticalLayout_3->count()-1, noti);
                ui->verticalLayout_3->insertWidget(j+1, noti);
                ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());
                //                //qDebug()<<"notification_list size when list size less than 10 "<<notification_list.size();
                delete notification_list.at(j);
                notification_list[j]=noti;
                ck = 1;
                break;
            }
        }

        if(ck == 0)// new Notification detected
        {
            qDebug()<<"cluster id johurul : "<<clusterId;

            qDebug()<<"new Notification"<<" and list size "<<list.size();
            list.push_back(clusterId.toInt());
            QListIterator<int>it(list);
            it.toFront();

            for(int j=0;j<list.size();j++){
                if(it.next() == clusterId.toInt())
                {
                    qDebug()<<"new Notification 1";
                    ui->verticalLayout_3->insertWidget(j+1, noti);
                    ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());

                    notification_list.push_back(noti);// insert into notification list.
                    ////qDebug() << "size of qlist is in if condition " << notification_list.size();
                    break;
                }
            }
        }
    }

    else {
        QListIterator<int>it(list);
        it.toFront();
        int ck=0;

        for (int j = 0; j<list.size() ; j++) {
            if(it.next() == clusterId.toInt()){// check same image
                ui->verticalLayout_3->insertWidget(j+1, noti);
                ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());
                //qDebug() << "size of qlist is in else condition " << notification_list.size();
                delete notification_list.at(j);
                notification_list[j] = noti;
                ck = 1;
                break;
            }
        }
        if(ck == 0){// new Notification detected
            list.removeFirst();
            list.push_back(clusterId.toInt());

            delete notification_list.at(0); // delete memory
            notification_list.removeFirst(); // remove from first
            notification_list.push_back(noti); // insert into last index

            QListIterator<Not*> iter(notification_list);
            iter.toFront();

            for(int i = 0; i < notification_list.size(); i++){
                ui->verticalLayout_3->insertWidget(i+1,iter.next());
                ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());
            }

            ////qDebug() << "size of qlist is in outside of else condition " << notification_list.size();
        }

    }
}

void notWidget::addNot(Not *noti)
{
    //qDebug() << "addnot call face " << notification_list.size();

    if ( notification_list.size() < 10 ){
        ui->verticalLayout_3->insertWidget(ui->verticalLayout_3->count()-1, noti);
        ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());
        //qDebug() << "size of qlist is in if condition " << notification_list.size();

        notification_list.push_back( noti);
    }else {
        //qDebug() << "size of qlist is in else condition " << notification_list.size();
        delete notification_list.at(0); // delete memory
        notification_list.removeFirst(); // remove from first
        notification_list.push_back(noti); // insert into last index

        QListIterator<Not*> iter(notification_list);
        iter.toFront();

        for(int i = 0; i < notification_list.size(); i++){
            ui->verticalLayout_3->insertWidget(i+1,iter.next());
            ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());
        }
    }
}
