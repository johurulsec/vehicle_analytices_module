#include "barwidget.h"
#include "qdebug.h"
#include <qpainter.h>

#include <iostream>
#include <cmath>

BarWidget::BarWidget(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"johir-6 barwidget constr call";

    this->setFixedHeight(9);
    this->setFixedWidth(1214);

}

void BarWidget::paintEvent(QPaintEvent *event)
{
    qDebug()<<"BarWidget::paintEvent call of barwidget.cpp class";

    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(7, 0, width()-14, 8, Qt::white);

    if (!msRanges.isEmpty())
    {
        int initial_pos = 7;

      for(int i = 0; i<source_ids.size();i++)
          if(source_ids[i] == source_id)
          {
              auto dd = ((msRanges[i][1]-msRanges[i][0])-0)/static_cast<double>(86399999-0)*(width()-14-0)+0;

              auto pos = round((msRanges[i][0]-0)/static_cast<double>(86399999-0)*(width()-14-0)+0);

              if(dd<1) {dd=1;}

              painter.fillRect(initial_pos + pos, 0, dd, 2, Qt::red);

              if(checkbox_FR && frs[i] == 1) painter.fillRect(initial_pos + pos, 2, dd, 2, QColor(0, 150, 0));
              if(checkbox_LC && lcs[i] == 1) painter.fillRect(initial_pos + pos, 4, dd, 2, QColor(160,0,160));
              if(checkbox_OD && ods[i] == 1) painter.fillRect(initial_pos + pos, 6, dd, 2, QColor(255,140,0));
//              if(checkbox_FR == 0 && checkbox_LC == 0 && checkbox_OD == 0) painter.fillRect(initial_pos + pos, 0, dd, 2, Qt::red);
//             if(checkbox_FR == 1 && checkbox_LC == 1 && checkbox_OD == 1) painter.fillRect(initial_pos + pos, 0, dd, 2, Qt::red);
          }

//        foreach (auto range, msRanges)
//        {
//            auto dd = ((range[1]-range[0])-0)/static_cast<double>(86399999-0)*(width()-14-0)+0;

//            auto pos = round((range[0]-0)/static_cast<double>(86399999-0)*(width()-14-0)+0);

//            if(dd<1) {dd=1;}
//            painter.fillRect(initial_pos + pos, 0, dd, 2, Qt::red);

//        }

    }


}

//void BarWidget::assignRanges(QList<QList<int>> msRanges)
//{
//    this->msRanges = msRanges;
//    this->source_ids
//}


