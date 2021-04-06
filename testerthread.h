#ifndef TESTERTHREAD_H
#define TESTERTHREAD_H

#include <QObject>
#include <QDebug>

class TesterThread : public QObject
{
    Q_OBJECT
public:
    explicit TesterThread(QObject *parent = nullptr);

    void requestWork();

signals:
    void requestedWork();
    void finished();

public slots:
    void dowark();
};

#endif // TESTERTHREAD_H
