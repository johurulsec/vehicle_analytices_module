#ifndef NOTWIDGET_H
#define NOTWIDGET_H

#include <QWidget>
#include <mail/not.h>
#include <QScrollBar>

namespace Ui {
class notWidget;
}

class notWidget : public QWidget
{
    Q_OBJECT

public:
//    explicit notWidget(QWidget *parent = 0);
    explicit notWidget(QWidget *parent = 0);
    ~notWidget();

public slots:
    void addNot(Not *);
    void addNot(QString, Not *);

private:
    Ui::notWidget *ui;

    int count_not = 0; // notification count.
    QList <Not*> notification_list; // List of notification.
    QList<int>list;// List of clusterId.
    int ck;
};

#endif // NOTWIDGET_H
