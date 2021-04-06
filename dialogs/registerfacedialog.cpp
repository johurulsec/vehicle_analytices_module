#include "registerfacedialog.h"
#include "ui_registerfacedialog.h"

registerFaceDialog::registerFaceDialog(QPixmap pix, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerFaceDialog)
{
    ui->setupUi(this);

    ui->imageLabel->setPixmap(pix.scaledToWidth(300, Qt::FastTransformation));
}

registerFaceDialog::~registerFaceDialog()
{
    delete ui;
}

void registerFaceDialog::on_buttonBox_accepted()
{

}

void registerFaceDialog::on_buttonBox_rejected()
{

}
