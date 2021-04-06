/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "player.h"

#include "playercontrols.h"
#include "playlistmodel.h"
#include "histogramwidget.h"
#include <Database/config_database.h>
#include <DatabaseConnection/sqlite_connection.h>
#include <QSqlQuery>
#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QAudioProbe>
#include <QMediaMetaData>
#include <QtWidgets>
#include <QDebug>

Player::Player(QWidget *parent) : QWidget(parent)
    , videoWidget(0)
    , coverLabel(0)
    , slider(0)
    , colorDialog(0)
{
    qDebug()<<"johir-0 player constructor call";

    QFile file("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.contains("[source")) {
            qDebug()<<line;
                no_of_sources++;
            }
    }

    qDebug()<< "no_of_sources: "<< no_of_sources;

    player = new QMediaPlayer(this);
    // owned by PlaylistModel
    playlist = new QMediaPlaylist();
    player->setPlaylist(playlist);

    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
    connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPositionChanged(int)));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
    connect(player, SIGNAL(bufferStatusChanged(int)), this, SLOT(bufferingProgress(int)));
    connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));
    connect(player, &QMediaPlayer::stateChanged, this, &Player::stateChanged);

    videoWidget = new VideoWidget(this);//first times call
    player->setVideoOutput(videoWidget);

    lbl = new QLabel(this);
    lbl->setAlignment(Qt::AlignCenter);
    QPixmap pix;

       /** to check wether load ok */
//       if(pix.load("/home/sigmind/mp_qt5.9/resources/no_signal.jpg")){
//    if(pix.load("/home/sigmind/QT-media-player/resources/no_signal.jpg")){
    if(pix.load("./resources/no_signal.jpg")){
           /** scale pixmap to fit in label'size and keep ratio of pixmap */
//        int w = 800;
//        int h = 515;
//        qDebug()<<"w: "<<w<<"h: "<<h;
//        pix = pix.scaled(w,h);
           lbl->setPixmap(pix);
       }

    stackedWidget = new QStackedWidget;
    stackedWidget->setFixedHeight(600);
    stackedWidget->addWidget(videoWidget);
    stackedWidget->addWidget(lbl);

    stackedWidget->setCurrentIndex(0);

    playlistModel = new PlaylistModel(this);// second times call
    playlistModel->setPlaylist(playlist);

    playlistView = new QListView(this);
    playlistView->setModel(playlistModel);
    playlistView->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));



    connect(playlistView, SIGNAL(activated(QModelIndex)), this, SLOT(jump(QModelIndex)));


    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, player->duration() / 1000);
    slider->setFixedHeight(7);

    // Test
    timeslider = new TimeSlider(Qt::Horizontal, this);//third times call
    timeslider->setMinimum(0);
    timeslider->setMaximum(86399);
    timeslider->setEnabled(false);
    timeslider->setStyleSheet("QSlider::groove:horizontal { "
                              "background-color: black;"
                              "border: 0px solid #424242;"
                              "height: 1px; "
                              "border-radius: 4px;}"

                              "QSlider::handle:horizontal {"
                              "background-color: #9F2425;"
                              "width: 3px;"
                              "height: 7px;"
                              "line-height: 20px;"
                              "margin-top: -5px;"
                              "margin-bottom: -5px;"
                              "margin-left: 6px;"
                              "margin-right: 6px;}"

                          "QSlider::handle:horizontal:hover {"
                              "border-radius: 10px;}"
                              );


    labelDuration = new QLabel(this);
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

    labelHistogram = new QLabel(this);
    labelHistogram->setText("Histogram:");
    videoHistogram = new HistogramWidget(this);//fourth times call
    audioHistogram = new HistogramWidget(this);// fourth call again
    QHBoxLayout *histogramLayout = new QHBoxLayout;
    histogramLayout->addWidget(labelHistogram);
    histogramLayout->addWidget(videoHistogram, 1);
    histogramLayout->addWidget(audioHistogram, 2);


    videoProbe = new QVideoProbe(this);
    connect(videoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), videoHistogram, SLOT(processFrame(QVideoFrame)));
    videoProbe->setSource(player);

    audioProbe = new QAudioProbe(this);
    connect(audioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), audioHistogram, SLOT(processBuffer(QAudioBuffer)));
    audioProbe->setSource(player);

    QPushButton *openButton = new QPushButton(tr("Open"), this);

    connect(openButton, SIGNAL(clicked()), this, SLOT(open()));

    controls = new PlayerControls(this);//fifth times call
    controls->setState(player->state());
    controls->setVolume(player->volume());
    controls->setMuted(controls->isMuted());

    connect(controls, SIGNAL(play()), player, SLOT(play()));
    connect(controls, SIGNAL(pause()), player, SLOT(pause()));
    connect(controls, SIGNAL(stop()), player, SLOT(stop()));
    connect(controls, SIGNAL(next()), playlist, SLOT(next()));
    connect(controls, SIGNAL(previous()), this, SLOT(previousClicked()));
    connect(controls, SIGNAL(changeVolume(int)), player, SLOT(setVolume(int)));
    connect(controls, SIGNAL(changeMuting(bool)), player, SLOT(setMuted(bool)));
    connect(controls, SIGNAL(changeRate(qreal)), player, SLOT(setPlaybackRate(qreal)));

    connect(controls, SIGNAL(changeRateS(qreal)), player, SLOT(setPlaybackRate(qreal)));

    connect(controls, SIGNAL(stop()), videoWidget, SLOT(update()));

    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
            controls, SLOT(setState(QMediaPlayer::State)));
    connect(player, SIGNAL(volumeChanged(int)), controls, SLOT(setVolume(int)));
    connect(player, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));

    fullScreenButton = new QPushButton(tr("FullScreen"), this);
    fullScreenButton->setCheckable(true);

    sources = new QComboBox(this);
    sources->setMaximumWidth(50);
    connect(sources,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(onSourcesChanged(const QString&)));

    checkbox_FR = new QCheckBox("Face Recognition",this);
    QPalette p = checkbox_FR->palette();
    p.setColor(QPalette::Active, QPalette::Base, QColor(0, 150, 0));
    checkbox_FR->setPalette(p);
    connect(checkbox_FR,SIGNAL(stateChanged(int)),this,SLOT(oncheckboxchanged()));

    checkbox_OD = new QCheckBox("Object Detection",this);
    p = checkbox_OD->palette();
    p.setColor(QPalette::Active, QPalette::Base, QColor(255,140,0));
    checkbox_OD->setPalette(p);
    connect(checkbox_OD,SIGNAL(stateChanged(int)),this,SLOT(oncheckboxchanged()));

    checkbox_LC = new QCheckBox("Line Crossings",this);
    p = checkbox_LC->palette();
    p.setColor(QPalette::Active, QPalette::Base, QColor(160,0,160));
    checkbox_LC->setPalette(p);
    connect(checkbox_LC,SIGNAL(stateChanged(int)),this,SLOT(oncheckboxchanged()));

    colorButton = new QPushButton(tr("Color Options..."), this);
    colorButton->setEnabled(false);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(showColorDialog()));

    QBoxLayout *playlistLayout = new QVBoxLayout;

    calendar = new QCalendarWidget(this);
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setMaximumDate(QDate(3000, 1, 1));
    calendar->setGridVisible(true);


    searchButton = new QPushButton(tr("Search"), this);
    connect(searchButton, SIGNAL(clicked()), this, SLOT(onSearchButtonClicked()));

    openLogButton = new QPushButton(tr("Browse"), this);
    connect(openLogButton, SIGNAL(clicked()), this, SLOT(onOpenLogButtonClicked()));
    echoLogPath = new QLineEdit(this);

    QHBoxLayout *hButtonLayout = new QHBoxLayout;

//    playlistLayout->addWidget(calendar);

    playlistLayout->addLayout(hButtonLayout);

    QGridLayout *controlsLayout = new QGridLayout;

    QPushButton *button[10][10];

    int count=0,i,j;

//    QFile file("");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QTextStream in(&file);
//    while (!in.atEnd()) {
//        QString line = in.readLine();
//        process_line(line);
//    }

    for(i=1;i<8;i++)
    {
        for(j=0;j<5;j++)
        {
            if(count<=35)
            {

                button[i][j] = new QPushButton(QString::number(count));

                connect(button[i][j], SIGNAL(clicked()), this, SLOT(onbuttonclicked()));

                button[i][j]->setCheckable(true);
                button[i][j]->setFixedHeight(30);
                button[i][j]->setFixedWidth(30);

                controlsLayout->addWidget(button[i][j], i, j);

                if(count > no_of_sources){button[i][j]->setDisabled(true);}

                count++;
            }
        }
    }
//    QSpacerItem *groupBox2Spacer = new QSpacerItem(100,0,QSizePolicy::Expanding, QSizePolicy::Expanding);
//    controlsLayout->addItem(groupBox2Spacer, 8, 0);

//    controlsLayout->addItem(, 0, 0);
    controlsLayout->setHorizontalSpacing(0);
    controlsLayout->setVerticalSpacing(0);

    controlsLayout->setContentsMargins(0, 0, 0, 0);
    controlsLayout->setSpacing(0);

    hButtonLayout->addLayout(controlsLayout);
    hButtonLayout->addWidget(calendar);


//    hButtonLayout->addWidget(echoLogPath);
//    hButtonLayout->addWidget(openLogButton);

    playlistLayout->addWidget(searchButton);

    playlistLayout->addWidget(playlistView);


    QBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(stackedWidget, 2);
    displayLayout->addLayout(playlistLayout);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    //controlLayout->addWidget(openButton);
    QLabel *source_label = new QLabel(this);
    source_label->setText("Playback Source: ");
    controlLayout->addWidget(source_label);
    controlLayout->addWidget(sources);
    controlLayout->addStretch(1);
    controlLayout->addWidget(checkbox_LC);
    controlLayout->addWidget(checkbox_FR);
    controlLayout->addWidget(checkbox_OD);

    controlLayout->addWidget(controls);

    controlLayout->addWidget(fullScreenButton);
    //controlLayout->addWidget(sources);
    controlLayout->addWidget(colorButton);

    layout = new QVBoxLayout;
    layout->addLayout(displayLayout);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(slider);
    hLayout->addWidget(labelDuration);

    QHBoxLayout *htimesliderGroupLayout = new QHBoxLayout;

    vtimesliderLayout = new QVBoxLayout;

    bar = new BarWidget;//sixth times call
    timeruler = new TimeRulerWidget;//seventh times call

    vtimesliderLayout->addWidget(timeruler);
    vtimesliderLayout->addWidget(timeslider);
    vtimesliderLayout->addWidget(bar);

    timeLabel = new QLabel(this);
    timeLabel->setText("00:00:00");
    timeLabel->setStyleSheet("QLabel{"
                             "max-width: 50px;"
                             "font-size: 10px;}");
    timeLabel->setFixedWidth(50);


    htimesliderGroupLayout->addLayout(vtimesliderLayout);
    htimesliderGroupLayout->addWidget(timeLabel);


    layout->addLayout(htimesliderGroupLayout);


    connect(timeslider, SIGNAL(valueChanged(int)),this, SLOT(onTimesliderChanged(int)));

    // End

    layout->addLayout(hLayout);
    layout->addLayout(controlLayout);
    layout->addLayout(histogramLayout);

    setLayout(layout);

    if (!isPlayerAvailable()) {
        qDebug()<<"player is not available!!!";

        QMessageBox::warning(this, tr("Service not available"),
                             tr("The QMediaPlayer object does not have a valid service.\n"\
                                "Please check the media service plugins are installed."));

        controls->setEnabled(false);
        playlistView->setEnabled(false);
        openButton->setEnabled(false);
        colorButton->setEnabled(false);
        fullScreenButton->setEnabled(false);
    }

    metaDataChanged();
}

Player::~Player()
{
    qDebug()<<"player destructor call";
}

bool Player::isPlayerAvailable() const
{
    qDebug()<<"johir-8 isPlayerAvailable call return value is : "<<player->isAvailable();

    return player->isAvailable();
}

void Player::open()
{
    qDebug()<<"Player::open call";

    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Files"));
    QStringList supportedMimeTypes = player->supportedMimeTypes();
    if (!supportedMimeTypes.isEmpty()) {
        supportedMimeTypes.append("audio/x-m3u"); // MP3 playlists
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    }
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        addToPlaylist(fileDialog.selectedUrls());
}

static bool isPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
    qDebug()<<"johir-12 isPlaylist call";

    if (!url.isLocalFile())
        return false;
    const QFileInfo fileInfo(url.toLocalFile());
    return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}

void Player::addToPlaylist(const QList<QUrl> urls)
{
    qDebug()<<"johir-11 taking all urls and addToPlaylist call";

    foreach (const QUrl &url, urls) {
        qDebug()<<"each urls : "<<url;
        if (isPlaylist(url)){
            //qDebug()<<"each urls : "<<url;
            playlist->load(url);
        }
        else
            playlist->addMedia(url);
    }
}

void Player::durationChanged(qint64 duration)
{
    this->duration = duration/1000;
    slider->setMaximum(duration / 1000);
}

void Player::positionChanged(qint64 progress)
{
    if (!slider->isSliderDown()) {
        slider->setValue(progress / 1000);
//        qDebug()<<"Current msRange "<<(msRanges[playlist->currentIndex()][0]/1000) + (progress/1000);
//        timeslider->setValue((msRanges[playlist->currentIndex()][0]/1000) + (progress/1000));
    }
    updateDurationInfo(progress / 1000);
}

void Player::metaDataChanged()
{
    qDebug()<<"johir-9 metadatachanged call";

    if (player->isMetaDataAvailable()) {
        setTrackInfo(QString("%1 - %2")
                .arg(player->metaData(QMediaMetaData::AlbumArtist).toString())
                .arg(player->metaData(QMediaMetaData::Title).toString()));

        if (coverLabel) {
            QUrl url = player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

            coverLabel->setPixmap(!url.isEmpty()
                    ? QPixmap(url.toString())
                    : QPixmap());
        }
    }
}

void Player::previousClicked()
{
    // Go to previous track if we are within the first 5 seconds of playback
    // Otherwise, seek to the beginning.
    if(player->position() <= 5000)
        playlist->previous();
    else
        player->setPosition(0);
}

void Player::jump(const QModelIndex &index)
{
    if (index.isValid()) {
        playlist->setCurrentIndex(index.row());
        player->play();
    }
}

void Player::playlistPositionChanged(int currentItem)
{
    clearHistogram();
    playlistView->setCurrentIndex(playlistModel->index(currentItem, 0));
}

void Player::seek(int seconds)
{
player->setPosition(seconds * 1000);
}

void Player::statusChanged(QMediaPlayer::MediaStatus status)
{
    handleCursor(status);

    // handle status message
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus:
    case QMediaPlayer::NoMedia:
    case QMediaPlayer::LoadedMedia:
    case QMediaPlayer::BufferingMedia:
    case QMediaPlayer::BufferedMedia:
        setStatusInfo(QString());
        break;
    case QMediaPlayer::LoadingMedia:
        setStatusInfo(tr("Loading..."));
        break;
    case QMediaPlayer::StalledMedia:
        setStatusInfo(tr("Media Stalled"));
        break;
    case QMediaPlayer::EndOfMedia:
        QApplication::alert(this);
        break;
    case QMediaPlayer::InvalidMedia:
        displayErrorMessage();
        break;
    }
}

void Player::stateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState)
        clearHistogram();
}

void Player::handleCursor(QMediaPlayer::MediaStatus status)
{
#ifndef QT_NO_CURSOR
    if (status == QMediaPlayer::LoadingMedia ||
        status == QMediaPlayer::BufferingMedia ||
        status == QMediaPlayer::StalledMedia)
        setCursor(QCursor(Qt::BusyCursor));
    else
        unsetCursor();
#endif
}

void Player::bufferingProgress(int progress)
{
    setStatusInfo(tr("Buffering %4%").arg(progress));
}

void Player::videoAvailableChanged(bool available)
{
    if (!available) {
        disconnect(fullScreenButton, SIGNAL(clicked(bool)),
                    videoWidget, SLOT(setFullScreen(bool)));
        disconnect(videoWidget, SIGNAL(fullScreenChanged(bool)),
                fullScreenButton, SLOT(setChecked(bool)));
        videoWidget->setFullScreen(false);
    } else {
        connect(fullScreenButton, SIGNAL(clicked(bool)),
                videoWidget, SLOT(setFullScreen(bool)));
        connect(videoWidget, SIGNAL(fullScreenChanged(bool)),
                fullScreenButton, SLOT(setChecked(bool)));

        if (fullScreenButton->isChecked())
            videoWidget->setFullScreen(true);
    }
    colorButton->setEnabled(available);
}

void Player::setTrackInfo(const QString &info)
{
    trackInfo = info;
    if (!statusInfo.isEmpty())
        setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
    else
        setWindowTitle(trackInfo);
}

void Player::setStatusInfo(const QString &info)
{
    statusInfo = info;
    if (!statusInfo.isEmpty())
        setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
    else
        setWindowTitle(trackInfo);
}

void Player::displayErrorMessage()
{
    setStatusInfo(player->errorString());
}

void Player::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || duration) {
        QTime currentTime((currentInfo/3600)%60, (currentInfo/60)%60, currentInfo%60, (currentInfo*1000)%1000);
        QTime totalTime((duration/3600)%60, (duration/60)%60, duration%60, (duration*1000)%1000);
        QString format = "mm:ss";
        if (duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    labelDuration->setText(tStr);
}

void Player::showColorDialog()
{
    if (!colorDialog) {
        QSlider *brightnessSlider = new QSlider(Qt::Horizontal);
        brightnessSlider->setRange(-100, 100);
        brightnessSlider->setValue(videoWidget->brightness());
        connect(brightnessSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setBrightness(int)));
        connect(videoWidget, SIGNAL(brightnessChanged(int)), brightnessSlider, SLOT(setValue(int)));

        QSlider *contrastSlider = new QSlider(Qt::Horizontal);
        contrastSlider->setRange(-100, 100);
        contrastSlider->setValue(videoWidget->contrast());
        connect(contrastSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setContrast(int)));
        connect(videoWidget, SIGNAL(contrastChanged(int)), contrastSlider, SLOT(setValue(int)));

        QSlider *hueSlider = new QSlider(Qt::Horizontal);
        hueSlider->setRange(-100, 100);
        hueSlider->setValue(videoWidget->hue());
        connect(hueSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setHue(int)));
        connect(videoWidget, SIGNAL(hueChanged(int)), hueSlider, SLOT(setValue(int)));

        QSlider *saturationSlider = new QSlider(Qt::Horizontal);
        saturationSlider->setRange(-100, 100);
        saturationSlider->setValue(videoWidget->saturation());
        connect(saturationSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setSaturation(int)));
        connect(videoWidget, SIGNAL(saturationChanged(int)), saturationSlider, SLOT(setValue(int)));

        QFormLayout *layout = new QFormLayout;
        layout->addRow(tr("Brightness"), brightnessSlider);
        layout->addRow(tr("Contrast"), contrastSlider);
        layout->addRow(tr("Hue"), hueSlider);
        layout->addRow(tr("Saturation"), saturationSlider);

        QPushButton *button = new QPushButton(tr("Close"));
        layout->addRow(button);

        colorDialog = new QDialog(this);
        colorDialog->setWindowTitle(tr("Color Options"));
        colorDialog->setLayout(layout);

        connect(button, SIGNAL(clicked()), colorDialog, SLOT(close()));
    }
    colorDialog->show();
}

void Player::clearHistogram()
{
    QMetaObject::invokeMethod(videoHistogram, "processFrame", Qt::QueuedConnection, Q_ARG(QVideoFrame, QVideoFrame()));
    QMetaObject::invokeMethod(audioHistogram, "processBuffer", Qt::QueuedConnection, Q_ARG(QAudioBuffer, QAudioBuffer()));
}

void Player::onSearchButtonClicked()
{
    qDebug()<<"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<pressedbuttons;

    sources->clear();
    source_ids.clear();

    for(int i = 0; i < pressedbuttons.size(); i++)
    {
        sources->addItem(QString::number(pressedbuttons[i]));
    }

    prev = "NULL";
    playlist->clear();
    player->duration();
    timeslider->setEnabled(true);
    timeslider->setValue(0);
    msRanges.empty();

    getMatchedUrls();


    addToPlaylist(urls);
    msRanges = extractMSecs(urls);

    drawDurationRect();

}

void Player::getMatchedUrls()
{
    urls.clear();
    durationList.clear();
    Qt::DateFormat f = Qt::ISODate;
    QString date = QString(calendar->selectedDate().toString(f));
    date = date.remove( QRegExp( "-" ) );

    if(connectionDB()){

        QString query_string = "SELECT *"
                               "FROM SmartRecordLog";

        QSqlQuery query;

        if(query.exec(query_string))
        {
            while (query.next()) {
                    int source_id = query.value(2).toInt();
                    int duration = query.value(3).toInt();
                    int lc = query.value(6).toInt();
                    int fr = query.value(7).toInt();
                    int od = query.value(8).toInt();
                    QString path = query.value(4).toString() + "/" + query.value(5).toString();

                    qDebug()<<"source_id: " << source_id;
                    qDebug()<<"Duration: "<<duration;
                    qDebug()<<"Path: "<<path;
                    for(int i = 0; i<pressedbuttons.size();i++)
                    {
                        if(pressedbuttons[i] == source_id && path.contains(date))
                        {
                            source_ids.append(source_id);
                            urls.append(QUrl("file://"+ path));
                            durationList.append(duration*1000);
                            lcs.append(lc);
                            ods.append(od);
                            frs.append(fr);
                        }
                    }

                }
        }

        else
        {
            qDebug()<< "Query Execution Failed!";
        }

    }

//    QFile file(this->filename);

//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QTextStream in(&file);
//    while (!in.atEnd()) {
//        QString line = in.readLine();
//        if (line.contains(date))
//        {
//            QRegExp rx("(\\:)");
//            line.split(rx);
//            urls.append(QUrl("file://"+ line.split(rx)[4] + "/" + line.split(rx)[5]));
//            durationList.append((line.split(rx)[3]).replace("ms","").toInt());
//        }
//        qDebug()<<"duration: "<<durationList;
//    }


//    QString PATH = "/media/58064154064133F2/qt-media-player/QT-media-player/videos/";

//    QDirIterator it(PATH, QStringList() << "*.*", QDir::Files, QDirIterator::Subdirectories);
//    while (it.hasNext())
//    {
//        it.next();
//        if (it.filePath().contains(date))
//        {
//            urls.append(QUrl("file://"+it.filePath()));
//        }
//    }
}


QList<QList<int>> Player::extractMSecs(const QList<QUrl> urls)
{
    QList<QList<int>> msRanges;
    int idy = 0;
    foreach (const QUrl &url, urls) {
        QRegExp rx("(\\_|\\.)");
        int idx = 0;
        QList<int> msdata;

        foreach (const QString &s,(url.toString()).split(rx)) {

            if (idx == 3)
            {
                const char mychar = ':';
                QString myString = s.split(QRegExp( "-" ))[1];
                myString.insert(2, mychar);
                myString.insert(5, mychar);
                QTime time = QTime::fromString(myString);
                int ms = time.msecsSinceStartOfDay();
                msdata.append(ms);
                msdata.append(ms + durationList[idy ]);
            }
            idx++;
        }
        idy++;
        msRanges.append(msdata);
    }
    return msRanges;
}

void Player::onTimesliderChanged(int value)
{
    int ms = (value-timeslider->minimum())/static_cast<double>(timeslider->maximum()-timeslider->minimum())*(86399999-0)+0;
    qDebug()<<"ms: "<<ms;
    const QTime t = QTime::fromMSecsSinceStartOfDay(ms);
    timeLabel->setText(t.toString("hh:mm:ss"));

    QString index;
    index.setNum(inRange(msRanges,ms));
    qDebug()<<"range found out: "<<index;

    if(prev != index && index.toInt() < msRanges.size())
    {
        playlist->setCurrentIndex(index.toInt());
        if(!slider->isEnabled())
        {
            slider->setEnabled(true);
            controls->setEnabled(true);
            playlistView->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));
            stackedWidget->setCurrentIndex(0);
        }
        prev = index;
    }

    if(prev == index)
    {
        player->setPosition(ms - msRanges[index.toInt()][0]);
        player->play();

        if(!slider->isEnabled())
        {
            slider->setEnabled(true);
            controls->setEnabled(true);
            playlistView->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));
            stackedWidget->setCurrentIndex(0);

        }
    }

    if(index == QString::number(msRanges.size()))
    {
        player->pause();
        player->setPosition(0);
        slider->setEnabled(false);
        controls->setEnabled(false);
        playlistView->clearSelection();
        stackedWidget->setCurrentIndex(1);
        lbl->setFixedHeight(videoWidget->height());
        lbl->setFixedWidth(videoWidget->width());
    }

}

int Player::inRange(QList<QList<int>> msRanges, unsigned x)
{
    int i;
    for(i = 0; i<source_ids.size();i++)
    {
        if(source_ids[i] == sources->currentText().toInt())
        {
            if((x-msRanges[i][0]) <= (msRanges[i][1]-msRanges[i][0]))
            {
                qDebug()<<"range found: "<<x <<" "<<i;
                break;
            }
        }
    }
    return i;
}

void Player::drawDurationRect()
{
    bar->source_id = sources->currentText().toInt();
    bar->source_ids = source_ids;
    bar->msRanges = msRanges;
    bar->update();
}

void Player::onOpenLogButtonClicked()
{
    this->filename = QFileDialog::getOpenFileName(this,"Select .log File","",".log Files (*.log)");
    this->echoLogPath->setText(this->filename);
}

void Player::onbuttonclicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(button->isChecked())
    {
        pressedbuttons.append(button->text().toInt());
    }

    if(!button->isChecked())
    {
        QMutableListIterator<int> i(pressedbuttons);
        while (i.hasNext()) {
            if (i.next() == button->text().toInt())
                i.remove();
        }

    }
}

void Player::onSourcesChanged(const QString&)
{
    drawDurationRect();
}

void Player::oncheckboxchanged()
{
    if(checkbox_FR->isChecked()) bar->checkbox_FR = 1; else bar->checkbox_FR = 0;
    if(checkbox_LC->isChecked()) bar->checkbox_LC = 1; else bar->checkbox_LC = 0;
    if(checkbox_OD->isChecked()) bar->checkbox_OD = 1; else bar->checkbox_OD = 0;

    bar->lcs = lcs;
    bar->frs = frs;
    bar->ods = ods;

    drawDurationRect();
}
