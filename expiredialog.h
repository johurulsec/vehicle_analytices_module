#ifndef EXPIREDIALOG_H
#define EXPIREDIALOG_H

#include <QDialog>

namespace Ui {
class expireDialog;
}

class expireDialog : public QDialog
{
    Q_OBJECT

public:
    explicit expireDialog(QWidget *parent = 0);
    ~expireDialog();

private:
    Ui::expireDialog *ui;
};

#endif // EXPIREDIALOG_H
