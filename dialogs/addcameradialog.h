#ifndef ADDCAMERADIALOG_H
#define ADDCAMERADIALOG_H

#include <QDialog>

namespace Ui {
class AddCameraDialog;
}

class AddCameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCameraDialog(QWidget *parent = 0);
    ~AddCameraDialog();

    QStringList cameraNames;
    QStringList cameraLinks;
    QStringList cameraTypes;
    QStringList cameraPriorF;
    QStringList cameraPriorL;



private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void acceptData(QString, QString, bool, bool, bool);
    void rejected();

private:
    Ui::AddCameraDialog *ui;
};

#endif // ADDCAMERADIALOG_H
