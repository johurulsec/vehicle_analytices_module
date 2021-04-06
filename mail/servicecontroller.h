#ifndef SERVICECONTROLLER_H
#define SERVICECONTROLLER_H

#include <QObject>
#include <mail/service.h>
#include <mail/notification.h>
#include <QTimer>

class ServiceController : public QObject
{
    Q_OBJECT
public:
    explicit ServiceController(QObject *parent = 0);
    ~ServiceController();

    service *mailer;
    QThread *mailingServiceThread;

    void addNot(Notification*);

signals:
    void addANot(Notification* noti);

public slots:
    void startANotTimer();
    void timerEnd();
};

#endif // SERVICECONTROLLER_H
