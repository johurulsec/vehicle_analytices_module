#include "servicecontroller.h"

ServiceController::ServiceController(QObject *parent) : QObject(parent)
{
    mailer= new service();
    mailingServiceThread = new QThread(this);
    mailer->moveToThread(mailingServiceThread);
    connect(mailingServiceThread, SIGNAL(started()), mailer, SLOT(sendNextEmail()));
    connect(mailer, SIGNAL(addTimer()), this, SLOT(startANotTimer()));
    connect(mailer, SIGNAL(addNotSignal(Notification*)), this, SIGNAL(addANot(Notification*)));
    connect(mailer, SIGNAL(finished()), mailingServiceThread, SLOT(quit()));
    mailingServiceThread->start();
}

ServiceController::~ServiceController()
{
    //qDebug() << "deleting in service controller";
    mailer->abort();
    mailingServiceThread->quit();
    mailingServiceThread->wait();

    delete mailer;
    delete mailingServiceThread;
}

void ServiceController::addNot(Notification *noti)
{
    mailer->addToService(noti);
    //qDebug() << "added to service";
}

void ServiceController::startANotTimer()
{
    //emit addANot(noti);
    //qDebug() << "timer started";
    QTimer *timer= new QTimer(this);
    timer->setSingleShot(true);
    timer->start(1000);
}

void ServiceController::timerEnd()
{
    mailer->dequeCompleteSlot();
}
