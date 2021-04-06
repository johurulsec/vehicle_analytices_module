#ifndef HELPERTHREAD_H
#define HELPERTHREAD_H

#include <QObject>
#include <QPixmap>
#include <QString>
//#include <helperdatacollection.h>
#include <QDebug>
#include <QMutex>
#include<QEventLoop>
#include<QTimer>

#include <ao/ao.h>
#include <mpg123.h>
#include <string.h>

class HelperThread : public QObject
{
    Q_OBJECT

    QMutex mutex;
public:
    //HelperDataCollection *helperdatacolpp, *helperdatacolpf;
    QPixmap firstpic, secondpic; QPixmap thirdpic; QString mask; int index, s; QString color;double dis;
    int overcrowed_val;

//    bool pp = false, pf = false;

    explicit HelperThread(QObject *parent = nullptr);
//    void requestWork();
    void requestWorkan();
    void playMusic(char *argv);

signals:
//    void requestedWork();
    void requestedWorkan();
//    void valueFRChanged(QPixmap, QPixmap, QPixmap, float, int, QString, QString, int);
    void valueFRChanged(QPixmap, QPixmap, QString, int, QString);
    void valueFRChanged(QPixmap, int);
    void valueFRChangedForOvercrowded(int);
    void finishedTh();

public slots:
    //void dowark(HelperDataCollection*);
    //void dowark(HelperDataCollection*, int);
    void dowark(QPixmap, QPixmap, QString, int, QString);
    void dowark(QPixmap, int, int);
//    void dowark(QPixmap, QPixmap, QPixmap, double, int, QString, QString, int);
//    void dowark();
};

#endif // HELPERTHREAD_H
