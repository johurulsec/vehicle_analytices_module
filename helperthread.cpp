#include "helperthread.h"
#include <QThread>

#define BITS 8

HelperThread::HelperThread(QObject *parent) : QObject(parent)
{

    //    pp = false;
    //    pf = false;
}

//void HelperThread::requestWork()
//{
//    qDebug()<< "requestWork........................................1";
//    mutex.lock();
//    pp = true;
//    mutex.unlock();

//    emit requestedWork();
//}

void HelperThread::playMusic(char *argv)
{
    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

    //    if(argc < 2)
    //        exit(0);

    /* initializations */
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    /* open the file and get the decoding format */
    mpg123_open(mh, argv);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    /* decode and play */
    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK){
        ao_play(dev, (char*)buffer, done);
    }


    /* clean up */
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
}

void HelperThread::requestWorkan()
{
    qDebug()<< "requestWorkan........................................2";
    //mutex.lock();
    //pf = true;
    //mutex.unlock();
    emit requestedWorkan();
}

//void HelperThread::dowark(HelperDataCollection* hdc)
//{
//    qDebug() << "Helper thread ----------------------------------------------1";
//    emit valueFRChanged(hdc->getFirstpic(), hdc->getSecondpic(), hdc->getThirdpic(),
//                        hdc->getDistance(), hdc->getIndex(), hdc->getMask(), hdc->getColor(), hdc->getSizeOfCl());
////    delete hdc;
//    emit finishedTh();
//}

//void HelperThread::dowark(HelperDataCollection *hdc, int)
//{
//    qDebug() << "Helper thread ----------------------------------------------2";
//    emit valueFRChanged(hdc->getFirstpic(), hdc->getThirdpic(), hdc->getMask(), hdc->getIndex(), hdc->getColor());
//    delete hdc;
//    emit finishedTh();
//}

void HelperThread::dowark(QPixmap g_f, QPixmap g_s, QString g_m, int g_i, QString g_c)
{
    qDebug() << "Helper tread ----------------------------------------------22232323";
    emit valueFRChanged(g_f, g_s, g_m, g_i, g_c);
    //    QEventLoop loop;
    //    QTimer::singleShot(1000, &loop, SLOT(quit()));
    //    loop.exec();

    //    mutex.lock();
    //    pf = false;

    //    mutex.unlock();

    emit finishedTh();
}

void HelperThread::dowark(QPixmap per, int ind, int over_crowd)
{
    qDebug() << "b Helper tread -----------------22232323 and over_c: "<<over_crowd;
    //emit valueFRChanged(g_f, g_s, g_m, g_i, g_c);

        emit valueFRChanged(per, ind);// for person
//    if(over_crowd > 0 && over_crowd <= 64){
//        emit valueFRChanged(per, over_crowd);// for only overcrowd

//        //    emit valueFRChangedForOvercrowded(over_crowd);
//        QString audio_file_path = "./alarm-audio-files/cam" + QString::number(over_crowd) + ".mp3";
//        qDebug()<<"audio_file_path of camera id: "<<audio_file_path;

//        char* cstr;
//        std::string fname = audio_file_path.toStdString();
//        cstr = new char [fname.size()+1];
//        strcpy( cstr, fname.c_str() );

//        //playMusic(cstr);
//    }

    //    QEventLoop loop;
    //    QTimer::singleShot(1000, &loop, SLOT(quit()));
    //    loop.exec();

    //    mutex.lock();
    //    pf = false;

    //    mutex.unlock();

    emit finishedTh();
}

//void HelperThread::dowark()
//{
//    qDebug() << "Helper tread ----------------------------------------------22";
////    emit valueFRChanged(g_f, g_s, g_m, g_i, g_c);
////    QEventLoop loop;
////    QTimer::singleShot(1000, &loop, SLOT(quit()));
////    loop.exec();

//    //    mutex.lock();
//    //    pf = false;

//    //    mutex.unlock();

//    emit finishedTh();
//}

//void HelperThread::dowark(QPixmap fp, QPixmap sp, QPixmap tp, double ds, int ind, QString m, QString c, int s)
//{
//    qDebug() << "Helper thread ----------------------------------------------11";

//    mutex.lock();
//    pp = false;
//    mutex.unlock();
//    emit valueFRChanged(fp, sp, tp, ds, ind, m, c, s);

//    //    delete hdc;
//    emit finishedTh();
//}
