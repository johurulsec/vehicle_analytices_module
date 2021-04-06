#include "notification.h"

Notification::Notification(QPixmap m_pic, QString nm, QString path, QString camNo, QPixmap p, QString cluster, QString times)
{
    //qDebug()<<"call notification constructor";
    name=nm;
    cam=camNo;
    pic = p;
    this->m_pic = m_pic;

    clusterId = cluster;
    timesOfSameImg = times;

    subject = "";
    message = "";
}

void Notification::setParameters()
{
    QImage image(pic.toImage());
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    image.save(&buffer, "PNG"); // writes the image in PNG format inside the buffer

    picBase64 = QString::fromLatin1(byteArray.toBase64().data());
    ////qDebug() << picBase64;
    dateTime = QDateTime::currentDateTime().toString();

    subject= "সতর্কতা !!" +  name + " কে দেখা গেছে ! ক্যামেরা নম্বর  " + cam + " তে  " + dateTime + "টার সময় " ;
    message= "Watchcam has seen " + name + "in camera " + cam + " at " + dateTime;

    //removed later
    pathToImage = "/home/sigmind/watchcam6_0/files/not.jpg";
}
