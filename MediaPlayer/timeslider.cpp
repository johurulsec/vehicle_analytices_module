#include "timeslider.h"
#include <QSlider>
#include <QStyle>
#include <QPainter>
#include <QDebug>
#include <QStyleOptionSlider>
#include <QTime>

TimeSlider::TimeSlider(Qt::Orientation orientation, QWidget *parent):
    QSlider(orientation, parent)
{
    qDebug()<<"johir-3 timeslider constr call";

    this->setFixedWidth(1214);
    this->setFixedHeight(10);
}
void TimeSlider::paintEvent(QPaintEvent *ev)
{
    QSlider::paintEvent(ev);
}

QRect TimeSlider::getSliderRect() {

    return timeSlider_Rect;
}

