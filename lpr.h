#ifndef LPR_H
#define LPR_H

#include <QWidget>
#include <QDateTime>
#include <QMouseEvent>
#include "QDebug"

namespace Ui {
class Lpr;
}

class Lpr : public QWidget
{
    Q_OBJECT

public:
    explicit Lpr(QWidget *parent = 0);
    ~Lpr();
    void setObjectLpr(QPixmap , QString, int, QString);
    QString getCurrentTime();

private:
    Ui::Lpr *ui;
    QPixmap pictr;
};

#endif // LPR_H
