#ifndef CARIMGSHOWDIALOG_H
#define CARIMGSHOWDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class CarImgShowDialog;
}

class CarImgShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CarImgShowDialog(QWidget *parent = 0);
    ~CarImgShowDialog();
    void carImageSetIntoLabel(int, QString, QImage);

private:
    Ui::CarImgShowDialog *ui;
};

#endif // CARIMGSHOWDIALOG_H
