#ifndef TILEWIDGET_H
#define TILEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class TileWidget;
}

class TileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TileWidget(QPixmap, QString, long,int, QWidget *parent = 0);
    ~TileWidget();

    QPixmap tilePic;
    QString tileName;
    long tileTime;
    int clusterId;

private:
    Ui::TileWidget *ui;


signals:
    void goToTile(long);
    void emitCluster(int);

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
};

#endif // TILEWIDGET_H
