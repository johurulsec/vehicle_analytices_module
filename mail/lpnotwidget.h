#ifndef LPNOTWIDGET_H
#define LPNOTWIDGET_H

#include <QWidget>
#include <mail/lpsinglewidg.h>
#include <QScrollBar>
#include <QDebug>
namespace Ui {
class LpNotWidget;
}

class LpNotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LpNotWidget(QWidget *parent = 0);
    ~LpNotWidget();
public slots:
    void addNotLP(LpSingleWidg *);

private:
    Ui::LpNotWidget *ui;
    /* modify by Johurul */
    int count_notLP = 0; // notification count.
    QList <LpSingleWidg*> notification_listLP; // List of notification.
};

#endif // LPNOTWIDGET_H
