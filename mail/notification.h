#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QString>
#include <QPixmap>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QBuffer>


class Notification
{
public:
    Notification(QPixmap, QString, QString, QString, QPixmap, QString, QString);

       void setParameters();

       QString subject;
       QString name;
       QString pathToImage;
       QString cam;
       QString message;
       QPixmap pic;
       QPixmap m_pic;
       QString picBase64;
       QString dateTime;

       QString clusterId;
       QString timesOfSameImg;
};

#endif // NOTIFICATION_H
