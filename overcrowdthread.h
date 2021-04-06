#ifndef OVERCROWDTHREAD_H
#define OVERCROWDTHREAD_H

#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include <ao/ao.h>
#include <mpg123.h>
#include <string.h>

class OvercrowdThread : public QObject
{
    Q_OBJECT
public:
    explicit OvercrowdThread(QObject *parent = nullptr);

    int overcroweded_vl;
    void requestOveran();
    void playMusic(char *argv);

signals:
    void requestedOverThStart();
    void finishedOverTh();
    void valueFRChanged(QPixmap, int);

public slots:
    void dowark(int);

};

#endif // OVERCROWDTHREAD_H
