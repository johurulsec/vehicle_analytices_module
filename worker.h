
#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>
#include <QWidget>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
//#include <string>
//#include <tesseract/baseapi.h>
//#include <leptonica/allheaders.h>
//#include <opencv2/opencv.hpp>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = 0);
    /**
     * @brief Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void requestWork();
    /**
     * @brief Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     */
    void abort();
    QString plateNum;
    QPixmap platePix;
    int plateIndx;
    int imgCounter = 0;
    cv::Mat main_pi; cv::Mat pi; QString s; int ind; QString obj_color;

    QString tessApi(cv::Mat);

private:
    /**
     * @brief Process is aborted when @em true
     */
    bool _abort;
    /**
     * @brief @em true when Worker is doing work
     */
    bool _working;
    /**
     * @brief Protects access to #_abort
     */
    QMutex mutex;



    bool OCRed;

signals:
    /**
     * @brief This signal is emitted when the Worker request to Work
     * @sa requestWork()
     */
    void workRequested();
    /**
     * @brief This signal is emitted when counted value is changed (every sec)
     */
    void valueChanged(QPixmap, QPixmap pic, QString str, int indx, QString);
    void valueChanged(QPixmap first_pic, QString first_str, QPixmap second_pic, QString second_str);

    //void valueChanged(QString plate);

    /**
     * @brief This signal is emitted when process is finished (either by counting 60 sec or being aborted)
     */
    void finished(QNetworkReply*rep);

    void finishedLPR();
    void plateData(QString p);

public slots:
    /**
     * @brief Does something
     *
     * Counts 60 sec in this example.
     * Counting is interrupted if #_aborted is set to true.
     */
    void doWork(cv::Mat, cv::Mat picture, QString str, int indx, QString, QString);
    QString LPRcap(QString encod);

    void syncRequestFinished(QNetworkReply*rep);
    void LPRprint(QPixmap pic, QString str, int indx);
   // void extractPlate(QPixmap picture, QString str, int indx);
};

#endif // WORKER_H
