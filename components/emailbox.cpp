#include "emailbox.h"
#include "ui_emailbox.h"

EmailBox::EmailBox(int idx,QString em, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmailBox)
{
    ui->setupUi(this);
    id= idx;
    email =  em;
    ui->lineEdit->setText(em);
}

EmailBox::~EmailBox()
{
    delete ui;
}



void EmailBox::on_pushButton_clicked()
{
    emit removeBox(id);
    this->close();
}

void EmailBox::on_lineEdit_textChanged(const QString &arg1)
{
    email = arg1;
    emit textChange(id, email);
}
