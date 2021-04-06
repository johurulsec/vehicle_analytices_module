#include "overcrowdthread.h"
#define BITS 8

OvercrowdThread::OvercrowdThread(QObject *parent) : QObject(parent)
{

}

void OvercrowdThread::requestOveran()
{
    qDebug()<< "requestOveran.......................................4";

    emit requestedOverThStart();

}

void OvercrowdThread::playMusic(char *argv)
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

void OvercrowdThread::dowark(int over_crowd)
{
    qDebug() << "Overcrowded tread ----------------- and over_c: "<<over_crowd;

    if(over_crowd > 0 && over_crowd <= 64){
        QPixmap pict;
        pict.load("./faces/shuvom.png");

        emit valueFRChanged(pict, over_crowd);// for only overcrowd

        //        //    emit valueFRChangedForOvercrowded(over_crowd);
        QString audio_file_path = "./alarm-audio-files/cam" + QString::number(over_crowd) + ".mp3";
        qDebug()<<"audio_file_path of camera id: "<<audio_file_path;

        char* cstr;
        std::string fname = audio_file_path.toStdString();
        cstr = new char [fname.size()+1];
        strcpy( cstr, fname.c_str() );

        playMusic(cstr);
    }

    emit finishedOverTh();
}
