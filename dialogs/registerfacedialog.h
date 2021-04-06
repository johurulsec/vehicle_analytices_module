#ifndef REGISTERFACEDIALOG_H
#define REGISTERFACEDIALOG_H

#include <QDialog>

namespace Ui {
class registerFaceDialog;
}

class registerFaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerFaceDialog(QPixmap, QWidget *parent = 0);
    ~registerFaceDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::registerFaceDialog *ui;
};

#endif // REGISTERFACEDIALOG_H
