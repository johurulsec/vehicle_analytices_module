#include "clusterdialog.h"
#include "ui_clusterdialog.h"

clusterDialog::clusterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clusterDialog)
{
    ui->setupUi(this);

    flowlayout= new FlowLayout(0,0,0);
    ui->scrollAreaWidgetContents->setLayout(flowlayout);
}

clusterDialog::~clusterDialog()
{
    delete ui;
}

void clusterDialog::addFace(Face *newFace)
{
    flowlayout->addWidget(newFace);
}
