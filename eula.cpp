#include "eula.h"
#include "ui_eula.h"

eula::eula(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eula)
{
    ui->setupUi(this);
    this->setWindowTitle("End User License Agreement");
}

eula::~eula()
{
    delete ui;
}

void eula::on_agreeButton_clicked()
{
    this->close();
    emit agree();
}

void eula::on_cancelButton_clicked()
{
    this->close();
    emit disagree();
}
