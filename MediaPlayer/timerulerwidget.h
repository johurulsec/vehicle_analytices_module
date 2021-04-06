#ifndef TIMERULERWIDGET_H
#define TIMERULERWIDGET_H

#include <QWidget>
#include "timeslider.h"

class TimeRulerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimeRulerWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    TimeSlider *timeslider;

signals:

public slots:
};

#endif // TIMERULERWIDGET_H
