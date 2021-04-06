#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <mail/notification.h>
#include <QQueue>
#include <mail/mailnotification.h>
#include <QTimer>
#include <QString>
#include <QMutex>

class service : public QObject
{
    Q_OBJECT
public:
    explicit service(QObject *parent = 0);
    static int name;

    QQueue<Notification*> nots;
    QQueue<Notification*> completeNots;

    bool checkComplete(Notification*);
    void addToService(Notification*);

    MailNotification *mail;

    QMutex notimutex;
    QMutex comnotimutex;
    QMutex abortmutex;

    bool _abort;

    void abort();
    void dequeCompleteSlot();

signals:
    void addTimer();
    void addNotSignal(Notification*);
    void finished();


public slots:
    void sendNextEmail();

};

#endif // SERVICE_H
