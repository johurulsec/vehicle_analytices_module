#include "servicelpr.h"

int serviceLPR::name_lpr = 0;

serviceLPR::serviceLPR(QObject *parent) : QObject(parent)
{
    lpr_mail = new MailNotification();
    _abort=false;
}

serviceLPR::~serviceLPR()
{
    //qDebug()<<"serviceLPR destructor";
    lprnots.clear();
    completeNots.clear();
}

void serviceLPR::addToServiceLPR(Notification *noti)
{
//    if(checkComplete(noti)){
//        //qDebug() << "lpr check passed"<<" pictype = "<<noti->name;
//        notimutex.lock();
//        lprnots.enqueue(noti);

//        /* Car detection signal */

//        //qDebug() << "check LP";
//        emit addNotSignalLP(noti);

//        notimutex.unlock();
//    }
    emit addNotSignalLP(noti);
}

bool serviceLPR::checkComplete(Notification *noti)
{
    notimutex.lock();
    if(!lprnots.isEmpty()){
        foreach (Notification *NotiQ, lprnots) {

            //if(noti->name == NotiQ->name){
            //  //qDebug() << "already in nots" << noti->name;
            //  notimutex.unlock();
            // return false;

            // }
        }
    }
    notimutex.unlock();

    comnotimutex.lock();

    //    if(!completeNots.isEmpty()){
    //        foreach (Notification *comNot, completeNots) {

    //           if(noti->name == comNot->name){
    //               //qDebug() << "already in complete nots" << noti->name;
    //               comnotimutex.unlock();
    //               return false;

    //           }
    //        }
    //    }
    comnotimutex.unlock();
    return true;
}

void serviceLPR::dequeCompleteSlot()
{
    //qDebug() << "dequed complete\n\n\n\n\n\n";
    comnotimutex.lock();
    if(!completeNots.isEmpty()) //qDebug() << completeNots.dequeue()->name;
    comnotimutex.unlock();
}

void serviceLPR::abort()
{
    abortmutex.lock();
    _abort= true;
    abortmutex.unlock();
}

void serviceLPR::sendNextEmail()
{
    while(true){
        abortmutex.lock();
        if(_abort) {
            abortmutex.unlock();
            break;
        }
        abortmutex.unlock();


        notimutex.lock();
        if(!lprnots.isEmpty()){

            Notification *newNot= lprnots.dequeue();
            notimutex.unlock();

            comnotimutex.lock();
            completeNots.enqueue(newNot);
            emit addTimer();
            comnotimutex.unlock();

            newNot->setParameters();
            lpr_mail->setSubject(newNot->subject.toStdString());
            lpr_mail->setMessage(newNot->message.toStdString());
            lpr_mail->addAttachment(newNot->picBase64.toStdString());

            //qDebug() << "before email \n\n\n";
            lpr_mail->sendEmail();
            //qDebug() << "after mail \n\n\n";
        }
        else {
            notimutex.unlock();
        }
    }
    //qDebug() << "aborting";
    emit finished();
}
