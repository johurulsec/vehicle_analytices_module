#ifndef TIMESLIDER_H
#define TIMESLIDER_H

#include <QWidget>
#include <QSlider>

class TimeSlider : public QSlider
{
    Q_OBJECT
public:
    explicit TimeSlider(Qt::Orientation orientation, QWidget *parent);
    void paintEvent(QPaintEvent *ev);
    void paintEvent(QList<QList<int> > msList);
    void setDurationRect(QList<QList<int>> msList);

    QStyleOptionSlider *opt;
    QRect timeSlider_Rect;

    QRect getSliderRect();

signals:
public slots:
};

#endif // TIMESLIDER_H
