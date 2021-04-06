#include "analyzedialog.h"
#include "ui_analyzedialog.h"
#include <QFileDialog>
#include <face.h>
#include <QLabel>

analyzeDialog::analyzeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyzeDialog)
{
    ui->setupUi(this);

    flow= new FlowLayout(0,0,0);
    ui->scrollAreaWidgetContents->setLayout(flow);

    lab = new QLabel(this);

    colorObjectNumber = 0;

    colorObjectWidget *newColorObject = new colorObjectWidget(colorObjectNumber, this);


    connect(newColorObject, SIGNAL(setValuesObject(int,QString)), this, SLOT(setObjectFilter(int,QString)));
    connect(newColorObject, SIGNAL(setValuesColor(int,int)), this, SLOT(setColorFilter(int,int)));


    colorValues << myStyles::colorValues.at(0);

    objects << myStyles::objects.at(0);

    ui->colorObjectsLayout->addWidget(newColorObject);

    ui->blackListLayout->addWidget(lab);

}

analyzeDialog::~analyzeDialog()
{
    delete ui;
}

void analyzeDialog::on_addFaceBut_clicked()
{
    QFileDialog dialog(this);
    dialog.setDirectory("./faces");
    dialog.setFileMode(QFileDialog::ExistingFiles);
    QStringList files;
    if (dialog.exec())	files = dialog.selectedFiles();

    QStringList tempFilenames;

    //compare for repeated images
    for(int i=0;i<files.length();i++){
        bool flag = true;
        for(int j=0;j<fileNames.length();j++){
            if(files.at(i)==fileNames.at(j)){
                flag= false;
                break;
            }
        }
        if(flag) {
            tempFilenames << files[i];
        }
    }

    fileNames += tempFilenames;

    for(int i=0;i<tempFilenames.length();i++){
        Face *face = new Face(this);
        QPixmap pic(files.at(i));
        face->setFace(pic.scaledToHeight(200, Qt::FastTransformation), "", 0,0);
        flow->addWidget(face);
    }


}

void analyzeDialog::on_analyzeBut_clicked()
{
//    if(ui->facesCheck->isChecked()){
//        if(fileNames.length() > 0){
//            emit emitAnalyzeFaces(fileNames);
//        }
//    }
//    else if(ui->objectCheck->isChecked()){
//        //qDebug() << colorValues;
//        //qDebug() <<objects;

//        int colorInd = colorValues.at(0);
//        QString ob = objects.at(0);
//        emit emitAnalyzeObject(colorInd, ob);
//    }
//    else if(black){
//        if(!folder.isEmpty()) emit emitAnalyzeBlacklist(folder);
//    }
    int GPUId;
    if(ui->gpu0->isChecked()) GPUId = 0;
    else GPUId = 1;

    this->close();
    this->deleteLater();

    emit emitAnalyzeAll(ui->facesCheck->isChecked(), fileNames, ui->objectCheck->isChecked(), colorValues, objects, ui->blackCheck->isChecked(), folder, GPUId);

}

void analyzeDialog::on_cancelBut_clicked()
{
    this->close();
    this->deleteLater();
}


void analyzeDialog::on_addObjectFilter_clicked()
{
    colorObjectNumber++;
    colorObjectWidget *newColorObject = new colorObjectWidget(colorObjectNumber, this);

    connect(newColorObject, SIGNAL(setValuesObject(int,QString)), this, SLOT(setObjectFilter(int,QString)));
    connect(newColorObject, SIGNAL(setValuesColor(int,int)), this, SLOT(setColorFilter(int,int)));

    colorValues << myStyles::colorValues.at(0);
    objects << myStyles::objects.at(0);
    ui->colorObjectsLayout->addWidget(newColorObject);
}

void analyzeDialog::setObjectFilter(int id,QString obj)
{
    objects.replace(id, obj);
}

void analyzeDialog::setColorFilter(int id, int col)
{
    colorValues.replace(id, col);
}

void analyzeDialog::on_blackBut_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        folder = dir;
        lab->setText(dir);
    }
}
