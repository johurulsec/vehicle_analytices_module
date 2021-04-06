#include "testerthread.h"

TesterThread::TesterThread(QObject *parent) : QObject(parent)
{

}

void TesterThread::dowark()
{
    qDebug()<<"Tested thread running..................";
    emit finished();
}

void TesterThread::requestWork()
{
    qDebug() << "Tester basedul .........";
    emit requestedWork();
}
