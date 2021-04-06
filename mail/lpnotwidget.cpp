#include "lpnotwidget.h"
#include "ui_lpnotwidget.h"

LpNotWidget::LpNotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LpNotWidget)
{
    ui->setupUi(this);
    this->setStyleSheet("border: 8px solid rgb(0, 0, 0);");
}

LpNotWidget::~LpNotWidget()
{
    notification_listLP.clear();
    delete ui;
}

void LpNotWidget::addNotLP(LpSingleWidg *noti)
{
    //qDebug() << "Notification LP is found";


    if ( notification_listLP.size() < 10 ){ // count number of notification.

        ui->verticalLayout_3->insertWidget(ui->verticalLayout_3->count()-1,noti);
        ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());

        notification_listLP.push_back(noti);// insert into notification list.
        //qDebug() << "size of qlist is in if condition " << notification_listLP.size();

    } else {

        delete notification_listLP.at(0); // delete memory
        notification_listLP.removeFirst(); // remove from first
        notification_listLP.push_back(noti); // insert into last index

        QListIterator<LpSingleWidg*> iter(notification_listLP);
        iter.toFront();

        for(int i = 0; i < notification_listLP.size(); i++){
            ui->verticalLayout_3->insertWidget(i,iter.next());
            ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());
        }

        //qDebug() << "size of qlist is in outside of if condition " << notification_listLP.size();

    }

}
