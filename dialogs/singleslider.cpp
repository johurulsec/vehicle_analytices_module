#include "singleslider.h"
#include "ui_singleslider.h"

singleSlider::singleSlider(int srcId, double divVal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::singleSlider)
{
    ui->setupUi(this);
    ui->label->setText("Source:"+ QString::number(srcId));
    ui->verticalSlider->setValue(divVal);
    source_id = srcId;
}

singleSlider::~singleSlider()
{
    delete ui;
}

int singleSlider::getSliderValue()
{
    return (double)ui->verticalSlider->value();
}

QString singleSlider::getSourceValue()
{
    return ui->label->text();
}

void singleSlider::justReturnSourceIdAndSliderValue()
{
    double a= (double)ui->verticalSlider->value();
    emit emitSourceId(source_id, a);
}
