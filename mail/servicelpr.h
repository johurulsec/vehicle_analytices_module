#ifndef SERVICELPR_H
#define SERVICELPR_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <mail/notification.h>
#include <QQueue>
#include <mail/mailnotification.h>
#include <QTimer>
#include <QString>
#include <QMutex>


class serviceLPR : public QObject
{
    Q_OBJECT
public:
    explicit serviceLPR(QObject *parent = 0);
    ~serviceLPR();

    static int name_lpr;

    QQueue<Notification*> lprnots;
    QQueue<Notification*> completeNots;

    bool checkComplete(Notification*);
    void addToServiceLPR(Notification*);

    MailNotification *lpr_mail;

    QMutex notimutex;
    QMutex comnotimutex;
    QMutex abortmutex;

    bool _abort;

    void abort();
    void dequeCompleteSlot();

signals:
    void addTimer();
    void addNotSignalLP(Notification*);
    void finished();


public slots:
    void sendNextEmail();

};


#endif // SERVICELPR_H
