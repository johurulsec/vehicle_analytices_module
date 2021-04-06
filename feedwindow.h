#ifndef FEEDWINDOW_H
#define FEEDWINDOW_H

#include <QDialog>
#include <QMouseEvent>
#include <QPoint>
#include <QWheelEvent>

namespace Ui {
class FeedWindow;
}

class FeedWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FeedWindow(bool type, QWidget *parent = 0);
    ~FeedWindow();

public slots:
    void receiveVideoFeed(QPixmap);
    void resizeEvent(QResizeEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);



#ifndef QT_NO_WHEELEVENT
    void    wheelEvent(QWheelEvent * event) Q_DECL_OVERRIDE;
#endif

private:
    Ui::FeedWindow *ui;

    int w;
    int h;

    float ratio;

    QPoint dragStartPosition;

    bool ptzType = false;
};

#endif // FEEDWINDOW_H
