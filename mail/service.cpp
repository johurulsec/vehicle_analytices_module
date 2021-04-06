#include "service.h"

int service::name = 0;

service::service(QObject *parent) : QObject(parent)
{
    mail = new MailNotification();
    _abort=false;
}

void service::addToService(Notification *noti)
{
    //if(checkComplete(noti)){
        //qDebug() << "check passed";
        notimutex.lock();
        //nots.enqueue(noti);
        emit addNotSignal(noti);
        notimutex.unlock();
    //}
}

bool service::checkComplete(Notification *noti)
{
    notimutex.lock();
    if(!nots.isEmpty()){
        foreach (Notification *NotiQ, nots) {

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

void service::dequeCompleteSlot()
{
    //qDebug() << "dequed complete\n\n\n\n\n\n";
    comnotimutex.lock();
    if(!completeNots.isEmpty()) //qDebug() << completeNots.dequeue()->name;
    comnotimutex.unlock();
}

void service::abort()
{
    abortmutex.lock();
    _abort= true;
    abortmutex.unlock();
}

void service::sendNextEmail()
{
    while(true){
        abortmutex.lock();
        if(_abort) {
            abortmutex.unlock();
            break;
        }
        abortmutex.unlock();


        notimutex.lock();
        if(!nots.isEmpty()){

            Notification *newNot= nots.dequeue();
            notimutex.unlock();

            comnotimutex.lock();
            completeNots.enqueue(newNot);
            emit addTimer();
            comnotimutex.unlock();

            newNot->setParameters();
            mail->setSubject(newNot->subject.toStdString());
            mail->setMessage(newNot->message.toStdString());
            mail->addAttachment(newNot->picBase64.toStdString());

            //qDebug() << "before email \n\n\n";
            mail->sendEmail();
            //qDebug() << "after mail \n\n\n";
        }
        else {
            notimutex.unlock();
        }
    }
    //qDebug() << "aborting";
    emit finished();
}
