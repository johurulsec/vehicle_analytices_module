#include "expiredialog.h"
#include "ui_expiredialog.h"

expireDialog::expireDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::expireDialog)
{
    ui->setupUi(this);
    QPixmap pixmap(":/.rsc/wc.png");
    ui->aboutImage->setPixmap(pixmap);

    this->setWindowTitle("Trial");
}

expireDialog::~expireDialog()
{
    delete ui;
}
