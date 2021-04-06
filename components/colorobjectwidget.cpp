#include "colorobjectwidget.h"
#include "ui_colorobjectwidget.h"

#include <QDebug>

colorObjectWidget::colorObjectWidget(int ind, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::colorObjectWidget)
{
    ui->setupUi(this);
    id= ind;

    ui->comboColor->addItems(myStyles::colors);
    ui->comboObject->addItems(myStyles::objects);
}

colorObjectWidget::~colorObjectWidget()
{
    delete ui;
}



void colorObjectWidget::on_comboColor_currentIndexChanged(int index)
{

    emit setValuesColor(id, myStyles::colorValues.at(index));
}

void colorObjectWidget::on_comboObject_currentIndexChanged(int index)
{

    emit setValuesObject(id, myStyles::objects.at(index));
}
