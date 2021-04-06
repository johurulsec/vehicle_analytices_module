#ifndef TRACKINGSETTINGSDIALOG_H
#define TRACKINGSETTINGSDIALOG_H

#include <QDialog>
#include <QStateMachine>
#include <QDebug>
#include <mystyles.h>

namespace Ui {
class trackingSettingsDialog;
}

class trackingSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit trackingSettingsDialog(QWidget *parent = 0);
    ~trackingSettingsDialog();

    QStateMachine machine;


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::trackingSettingsDialog *ui;
};

#endif // TRACKINGSETTINGSDIALOG_H
