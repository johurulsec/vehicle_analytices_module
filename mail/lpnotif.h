#ifndef LPNOTIF_H
#define LPNOTIF_H

#include <QWidget>
#include <QTime>

namespace Ui {
class LPNotif;
}

class LPNotif : public QWidget
{
    Q_OBJECT

public:
    explicit LPNotif(QPixmap, QString, QString, QString, QWidget *parent = 0);
    ~LPNotif();

private:
    Ui::LPNotif *ui;
    int i = 1;
};

#endif // LPNOTIF_H
