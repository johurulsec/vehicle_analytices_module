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


#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStackedWidget>

#include "player.h"

#include "videowidget.h"
#include "playercontrols.h"
#include "playlistmodel.h"
#include "histogramwidget.h"

#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QAudioProbe>
#include <QMediaMetaData>
#include <QtWidgets>
#include <QDebug>

#include "timeslider.h"
#include "barwidget.h"
#include "timerulerwidget.h"

class QAbstractItemView;
class QLabel;
class QMediaPlayer;
class QModelIndex;
class QPushButton;
class QSlider;
class QVideoProbe;
class QVideoWidget;
class QAudioProbe;
class QCalendarWidget;
class TimeSlider;
class PlaylistModel;
class HistogramWidget;
class BarWidget;
class TimeRulerWidget;

class Player : public QWidget
{
    Q_OBJECT

public:
    Player(QWidget *parent = 0);
    ~Player();

    bool isPlayerAvailable() const;

    void addToPlaylist(const QList<QUrl> urls);




signals:
    void fullScreenChanged(bool fullScreen);

private slots:
    void open();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void metaDataChanged();

    void previousClicked();

    void seek(int seconds);
    void jump(const QModelIndex &index);
    void playlistPositionChanged(int);

    void statusChanged(QMediaPlayer::MediaStatus status);
    void stateChanged(QMediaPlayer::State state);
    void bufferingProgress(int progress);
    void videoAvailableChanged(bool available);

    void displayErrorMessage();

    void showColorDialog();

    void onSearchButtonClicked();
    void onOpenLogButtonClicked();

    void onTimesliderChanged(int ms);
    void onbuttonclicked();
    void onSourcesChanged(const QString &);
    void oncheckboxchanged();


   // double mapToRange(int minOutRange, int maxOutRange, int minInRange, int maxInRange, int value);

    void getMatchedUrls();

    QList<QList<int>> extractMSecs(const QList<QUrl> urls);

private:
    void clearHistogram();
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void handleCursor(QMediaPlayer::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);
    int inRange(QList<QList<int>> msRanges, unsigned x);
    void drawDurationRect();

    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    VideoWidget *videoWidget;
    QLabel *coverLabel;
    QSlider *slider;
    TimeSlider *timeslider;
    QLabel *labelDuration;
    QLabel *timeLabel;
    QPushButton *fullScreenButton;
    QComboBox *sources;
    QPushButton *colorButton;
    QPushButton *searchButton;
    QPushButton *openLogButton;
    QDialog *colorDialog;
    PlayerControls *controls;

    QLabel *labelHistogram;
    HistogramWidget *videoHistogram;
    HistogramWidget *audioHistogram;
    QVideoProbe *videoProbe;
    QAudioProbe *audioProbe;

    PlaylistModel *playlistModel;
    QAbstractItemView *playlistView;
    QString trackInfo;
    QString statusInfo;
    qint64 duration;
    QFrame *line;
    QLineEdit *echoLogPath;
    QString filename;
    QCalendarWidget *calendar;

    int no_of_sources = 0;
    QList<QList<int>> msRanges;

    QStackedWidget *stackedWidget;
    QString prev;
    QLabel *lbl;

    QBoxLayout *layout;

    QHBoxLayout *durationLineLayout;

    BarWidget *bar;

    QVBoxLayout *vtimesliderLayout;

    TimeRulerWidget *timeruler;
    QList<QUrl> urls;

    QList<int> lcs;
    QList<int> frs;
    QList<int> ods;

    QList<int> source_ids;
    QList<int> durationList;
    QList<int> pressedbuttons;

    QCheckBox *checkbox_FR;
    QCheckBox *checkbox_OD;
    QCheckBox *checkbox_LC;

};

#endif // PLAYER_H
