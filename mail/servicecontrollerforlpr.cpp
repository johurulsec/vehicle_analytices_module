#include "servicecontrollerforlpr.h"

ServiceControllerForLPR::ServiceControllerForLPR(QObject *parent) : QObject(parent)
{
    lpr_mailer= new serviceLPR();
    lpr_mailingServiceThread = new QThread(this);
    lpr_mailer->moveToThread(lpr_mailingServiceThread);
    connect(lpr_mailingServiceThread, SIGNAL(started()), lpr_mailer, SLOT(sendNextEmail()));
    connect(lpr_mailer, SIGNAL(addTimer()), this, SLOT(startANotTimer()));
    /* lisence plate siganl and slot*/
    connect(lpr_mailer, SIGNAL(addNotSignalLP(Notification*)), this, SIGNAL(addANotLP(Notification*)));

    connect(lpr_mailer, SIGNAL(finished()), lpr_mailingServiceThread, SLOT(quit()));
    lpr_mailingServiceThread->start();
}

ServiceControllerForLPR::~ServiceControllerForLPR()
{
    //qDebug() << "deleting in service controller_lpr";
    lpr_mailer->abort();
    lpr_mailingServiceThread->quit();
    lpr_mailingServiceThread->wait();

    delete lpr_mailer;
    delete lpr_mailingServiceThread;
}

void ServiceControllerForLPR::addNotLPR(Notification *noti)
{
    //qDebug()<<"addNot check lpr "<<noti->name;
    lpr_mailer->addToServiceLPR(noti);
}

void ServiceControllerForLPR::startANotTimer()
{
    //emit addANot(noti);
    //qDebug() << "timer started";
    QTimer *timer= new QTimer(this);
    timer->setSingleShot(true);
    timer->start(1000);
}

void ServiceControllerForLPR::timerEnd()
{
    lpr_mailer->dequeCompleteSlot();
}
