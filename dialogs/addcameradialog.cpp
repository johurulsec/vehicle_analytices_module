#include "addcameradialog.h"
#include "ui_addcameradialog.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>

AddCameraDialog::AddCameraDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCameraDialog)
{
    ui->setupUi(this);

    QFile file("./files/cameras.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    int i=0;
    ui->camerasComboBox->addItem("Select a camera");
    while(!in.atEnd()) {
        QString name = in.readLine();
        QString link = in.readLine();
        QString type = in.readLine();
        QString priorityF = in.readLine();
        QString priorityL = in.readLine();
        cameraNames << name;
        cameraLinks << link;
        cameraTypes << type;
        cameraPriorF << priorityF;
        cameraPriorL << priorityL;
        ui->camerasComboBox->addItem(name + " " + type + " " + priorityF +" "+ priorityL + " " + link + " ");
    }



    file.close();


}

AddCameraDialog::~AddCameraDialog()
{
    //qDebug() << "add camera destroyed \n";
    delete ui;
}

void AddCameraDialog::on_buttonBox_accepted()
{
    if(ui->camerasComboBox->currentIndex()!=0){
        int ind = ui->camerasComboBox->currentIndex()-1;
        if(cameraNames.at(ind).length()){
            bool type= false;
            bool Fprior = false;
            bool Lprior = false;
            if(cameraTypes.at(ind) == "1") type = true;
            // +++++

            if(cameraPriorF.at(ind) == "1") Fprior = true;
            if(cameraPriorL.at(ind) == "1") Lprior = true;
            emit acceptData(cameraNames.at(ind), cameraLinks.at(ind), type, Fprior, Lprior);

        }

    }
    else if(ui->nameLineEdit->text().length() && ui->linkLineEdit->text().length()){
        cameraNames << ui->nameLineEdit->text();
        cameraLinks << ui->linkLineEdit->text();
        QString type = "0";
        QString Fprior = "0";
        QString Lprior = "0";
        if(ui->ptzButton->isChecked()) type = "1";
        cameraTypes << type;
        if(ui->facePrior->isChecked()) {
            Fprior = "1";
            cameraPriorF << Fprior; }
         if(ui->lprPrior->isChecked()) {
            Lprior = "1";
            cameraPriorL << Lprior; }
        QString filename="./files/cameras.txt";
        QFile file( filename );
        if ( file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &file );

            for(int i=0 ; i < cameraNames.length() ; i++){
                stream << cameraNames.at(i) << endl;
                stream << cameraLinks.at(i) << endl;
                stream << cameraTypes.at(i) << endl;
                stream << cameraPriorF.at(i) << endl;
                stream << cameraPriorL.at(i) << endl;
            }
        }

        emit acceptData(ui->nameLineEdit->text(), ui->linkLineEdit->text(), ui->ptzButton->isChecked(), ui->facePrior->isChecked(), ui->lprPrior->isChecked());
    }
    else rejected();
    this->close();

}

void AddCameraDialog::on_buttonBox_rejected()
{
    emit rejected();
}
