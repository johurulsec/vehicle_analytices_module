#ifndef SERVICECONTROLLERFORLPR_H
#define SERVICECONTROLLERFORLPR_H

#include <QObject>
#include <mail/notification.h>
#include <QTimer>
#include <mail/servicelpr.h>

class ServiceControllerForLPR : public QObject
{
    Q_OBJECT
public:
    explicit ServiceControllerForLPR(QObject *parent = 0);
    ~ServiceControllerForLPR();

    serviceLPR *lpr_mailer;

    QThread *lpr_mailingServiceThread;

    void addNotLPR(Notification*);

signals:
    void addANotLP(Notification* noti);

public slots:
    void startANotTimer();
    void timerEnd();
};

#endif // SERVICECONTROLLERFORLPR_H
