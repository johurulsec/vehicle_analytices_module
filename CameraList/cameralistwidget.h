#ifndef CAMERALISTWIDGET_H
#define CAMERALISTWIDGET_H

#include <QWidget>
#include "camera_list_helper.h"
#include <QMouseEvent>

namespace Ui {
class cameraListWidget;
}

class cameraListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit cameraListWidget(QWidget *parent, camera_list_helper cam_info);
    explicit cameraListWidget(QWidget *parent);
    ~cameraListWidget();
    void addCamWidget(camera_list_helper cam_info);

    void mouseDoubleClickEvent(QMouseEvent*); // Mouse double clicked event
signals:
    void emitClickedOnCameraInfo();

private:
    Ui::cameraListWidget *ui;
};

#endif // CAMERALISTWIDGET_H
