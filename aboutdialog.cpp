#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
   // QPixmap pixmap("./rsc/wc.png");
    //ui->aboutImage->setPixmap(pixmap);

    this->setWindowTitle("About");
}

aboutDialog::~aboutDialog()
{
    delete ui;
}
