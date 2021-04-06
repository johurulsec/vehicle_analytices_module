#include "trackingsettingsdialog.h"
#include "ui_trackingsettingsdialog.h"
#include <QPushButton>
#include <QStateMachine>

trackingSettingsDialog::trackingSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trackingSettingsDialog)
{
    ui->setupUi(this);
    QPushButton *button= new QPushButton(this);


    QState *off = new QState();
    off->assignProperty(button, "text", "Off");
    off->setObjectName("off");

    QState *on = new QState();
    on->setObjectName("on");
    on->assignProperty(button, "text", "On");

    off->addTransition(button, SIGNAL(clicked()), on);
    on->addTransition(button, SIGNAL(clicked()), off);

    machine.addState(off);
    machine.addState(on);

    machine.setAnimated(true);
    machine.setInitialState(off);
    machine.start();

    button->resize(100, 50);
    button->show();
    ui->trackingBox->addWidget(button);
}

trackingSettingsDialog::~trackingSettingsDialog()
{
    delete ui;
}

void trackingSettingsDialog::on_buttonBox_accepted()
{
    ////qDebug() << machine.property("text");
    myStyles::trackingFlag = machine.property("text").toString();
    this->close();
}

void trackingSettingsDialog::on_buttonBox_rejected()
{
    this->close();
}
