#include "timerulerwidget.h"
#include "timeslider.h"
#include <qpainter.h>
#include <qdebug.h>

TimeRulerWidget::TimeRulerWidget(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"johir-7 timerulerwidget call";

    this->setFixedHeight(16);
    this->setFixedWidth(1214);
    update();

}

void TimeRulerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::black));

    QFont font = painter.font();
    font.setPointSize(5);

    painter.setFont(font);

    QFontMetrics fontMetrics = QFontMetrics(painter.font());


    int frame_width = width()-14;
    int inX = 7;
    int inY = 7;
    int num_portions = 24;
    float portion_width = frame_width/num_portions;

    painter.drawLine(inX,inY,inX + frame_width ,inY);

    float num_pos;


    for(int i=0; i<=num_portions; i++)
    {
      num_pos = fontMetrics.width(QString::number(i)) / 2;

      painter.drawLine(inX,inY,inX,inY + 11);
      painter.drawText(QPoint(inX - num_pos, 5),QString::number(i));

      inX = inX + portion_width;
    }

    inX = 7;
    int temp = 0;

    for(int i=0; i<num_portions * 2; i++)
    {
      temp = inX;
      num_pos = fontMetrics.width(QString::number(i)) / 2;

      for(int j = 0; j<= 3; j++)
      {
          temp = temp + (portion_width/2)/5;
          painter.drawLine(temp , inY, temp, inY+3);
      }

      if (i % 2 != 0)
      {
          painter.drawLine(inX,inY,inX,inY + 6);
      }

      inX = inX + portion_width/2;
    }

}
