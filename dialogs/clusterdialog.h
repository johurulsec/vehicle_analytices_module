#ifndef CLUSTERDIALOG_H
#define CLUSTERDIALOG_H

#include <QDialog>
#include <flowlayout.h>
#include <face.h>
#include <dialogs/clusterdialog.h>

namespace Ui {
class clusterDialog;
}

class clusterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit clusterDialog(QWidget *parent = 0);
    ~clusterDialog();

    void addFace(Face*);

private:
    Ui::clusterDialog *ui;

    FlowLayout* flowlayout;
};

#endif // CLUSTERDIALOG_H
