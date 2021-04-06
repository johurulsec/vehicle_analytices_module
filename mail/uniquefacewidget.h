#ifndef UNIQUEFACEWIDGET_H
#define UNIQUEFACEWIDGET_H

#include <QWidget>
#include <mail/faceuniq.h>
#include <QScrollBar>
#include "QHBoxLayout"
#include <QPushButton>
#include <QVBoxLayout>
//#include <mainwindow.h>

namespace Ui {
class uniqueFaceWidget;
}

class uniqueFaceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit uniqueFaceWidget(QString, QWidget *parent = 0);
    ~uniqueFaceWidget();
    void setLabelForShowMaskDis(QString);

public slots:
    void u_addNot(faceUniq *);

private:
    Ui::uniqueFaceWidget *ui;

    int count_not = 0; // notification count.
    QList <faceUniq*> uniq_list; // List of notification.
    QList<int>list_u;// list_u of clusterId.
    int ck, coun = 0;
//    QHBoxLayout *box_layout_cam_list;
    QVBoxLayout *box_layout_cam_list;

    QGridLayout *grid_uniq_faces;
    int row_index_u = 0; int column_index_u = 0;
};

#endif // UNIQUEFACEWIDGET_H

