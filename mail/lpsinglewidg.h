#ifndef LPSINGLEWIDG_H
#define LPSINGLEWIDG_H

#include <QWidget>

namespace Ui {
class LpSingleWidg;
}

class LpSingleWidg : public QWidget
{
    Q_OBJECT

public:
    explicit LpSingleWidg(QPixmap, QPixmap, QString, QString, QString, QWidget *parent = 0);
    ~LpSingleWidg();

private:
    Ui::LpSingleWidg *ui;
    int i = 1;
};

#endif // LPSINGLEWIDG_H
