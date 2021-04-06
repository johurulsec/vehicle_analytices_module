#include "faces.h"
#include "ui_faces.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include "warker.h"

cv::Mat Faces::QImageToMat(const QImage& src) {
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat result = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0,  1,1,  2,2 };
    cv::mixChannels( &mat, 1, &result, 1, from_to, 3 );
    return result;
}

Faces::Faces(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Faces)
{
    ui->setupUi(this);



    mainLayout = new QGridLayout;
    grid_show_all_faces = new QGridLayout; // Initialize Grid Layout
    grid_show_uniq_faces = new QGridLayout;
    grid_show_recog_faces = new QGridLayout;
    grid_show_unique_lpr = new QGridLayout;

    flowLayout= new FlowLayout(0,0,0);
    flowLayout2= new FlowLayout(0,0,0);
    flowLayout3= new FlowLayout(0,0,0);
    flowLayout4= new FlowLayout(0,0,0);

    ui->scrollAreaWidgetContents->setLayout(grid_show_all_faces);
    //    ui->scrollAreaWidgetContents_2->setLayout(flowLayout2);
    ui->scrollAreaWidgetContents_2->setLayout(grid_show_uniq_faces);
    //    ui->scrollAreaWidgetContents_3->setLayout(flowLayout3);
    ui->scrollAreaWidgetContents_3->setLayout(grid_show_unique_lpr);
    //ui->scrollAreaWidgetContents_4->setLayout(flowLayout4);
    ui->scrollAreaWidgetContents_4->setLayout(grid_show_recog_faces);

    ui->scrollAreaWidgetContents_5->setLayout(grid_show_unique_lpr);

    // ui->scrollAreaFaces->verticalScrollBar()->setSliderPosition(label->height());
    ui->tabWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(2);
    ui->tabWidget->setCurrentIndex(3);

    ui->tabWidget->setCurrentIndex(4);

    //connect(this, SIGNAL(notifyLPR(QPixmap,QString,int)),
    isScroll= true;
    layout = new QHBoxLayout;

    memset(sameFacesTimesIdCount, 0, sizeof(sameFacesTimesIdCount));// at first, samefacesTimesIdCount array memory all index value is zero
    flg = 2;
    cluster_templates.clear();
    storeInitClValue = (int)cluster_templates.size();

    //qDebug()<<"thread id faces constr "<<thread()->currentThreadId();
}

void Faces::addUniqueFaceToTiles(QPixmap pic, QString name, int idx, dlib::matrix<float,0,1> pic_template)
{
    //qDebug()<<"addUniqueFaceToTiles call";

    //    QString face_path = "./captures/faces/";
    //    QString obliq = "/";
    //   // QString forma = "dd.MM.yyyy";
    //    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    //    QString at = "<at>";
    //     //QDir().mkdir(date);

    //    QString img_path = face_path+date+obliq;
    //     QDir myDir;
    //     if(!myDir.exists(date))
    //     {

    //         myDir.mkpath(img_path);
    //         QFile file(img_path+name+at+QTime::currentTime().toString());
    //         file.open(QIODevice::WriteOnly);
    //         pic.save(&file, "PNG");

    //     }



    int cl = cluster_templates.size();
    double mn= 100.0;
    for(int i=0; i<cluster_templates.size(); i++)
    {
        double diff = dlib::length(pic_template-cluster_templates[i]);
        if(diff<mn && diff<0.5)
        {
            mn= diff;
            cl = i;
        }
    }
    if(cl == cluster_templates.size()) cluster_templates.push_back(pic_template);

    Face *newFace = new Face;
    newFace->setFace(pic, name, idx,cl);
    connect(newFace, SIGNAL(emitPicDB(QPixmap)), this, SLOT(justcheck(QPixmap)));
    flowLayout->addWidget(newFace);

    //    QString face_path = "./captures/faces/";
    //   // QString qstr = QString::fromStdString(plateD);
    //    QFile file(face_path+name);
    //    file.open(QIODevice::WriteOnly);
    //    pic.save(&file, "PNG");

    Face *newFaceVector = new Face;
    newFaceVector->setFace(pic, name, idx,cl);

    if(allFaces.size()){
        if(allFaces.size()-1<cl){
            Face *newFaceClick = new Face;
            newFaceClick->setFace(pic, name, idx,cl);
            connect(newFaceClick, SIGNAL(emitCluster(int)), this, SLOT(displayCluster(int)));
            connect(newFaceClick, SIGNAL(emitPicDB(QPixmap)), this, SLOT(justcheck(QPixmap)));
            flowLayout2->addWidget(newFaceClick);

            QList<Face*> faceCluster;
            faceCluster.push_back(newFaceVector);

            allFaces.push_back(faceCluster);
            ui->tabWidget->setTabText(1, " Unique Faces (" + QString::number(allFaces.size()) + ")");
            //qDebug()<<"only unique face push>>";
        }
        else {
            allFaces[cl].push_back(newFaceVector);
            //qDebug()<<"duplicate face push hare else "<<++cnt_test;
        }
    }
    else {
        //qDebug()<<"else only for onetime";
        Face *newFaceClick = new Face;
        newFaceClick->setFace(pic, name, idx,cl);
        connect(newFaceClick, SIGNAL(emitCluster(int)), this, SLOT(displayCluster(int)));
        connect(newFaceClick, SIGNAL(emitPicDB(QPixmap)), this, SLOT(justcheck(QPixmap)));
        flowLayout2->addWidget(newFaceClick);

        QList<Face*> faceCluster;
        faceCluster.push_back(newFaceVector);
        allFaces.push_back(faceCluster);
        ui->tabWidget->setTabText(1, " Unique Faces (" + QString::number(allFaces.size()) + ")");
    }

    // if((ui->scrollAreaFaces->verticalScrollBar()->maximum()-ui->scrollAreaFaces->verticalScrollBar()->sliderPosition())<500) {
    //ui->scrollAreaFaces->verticalScrollBar()->setSliderPosition(ui->scrollAreaFaces->verticalScrollBar()->maximum());
    // }
}

void Faces::only_uniqueFace_show_inTiles(QPixmap pic, QString name, int idx)
{
    Face *uniqFace = new Face();
    uniqFace->setObject(pic, name, idx);

    qDebug()<<"only_uniqueFace_show_inTiles call faces.cpp";

    connect(uniqFace, SIGNAL(emitPicDB(QPixmap)), this, SLOT(justcheck(QPixmap)));

    // Checked Image Null or Not! After getting correct image, hold into list.
    if (!pic.isNull()){
        //qDebug()<<"pic is not null"<<" uniq_faceList.size() >>"<<uniq_faceList.size();
        if (uniq_faceList.size() < 100){// Checked size of list is 100 or not!
            //qDebug()<<"uniq_faceList less than 100";
            uniq_faceList.push_back(uniqFace); // Added face in Lists
            grid_show_uniq_faces->addWidget(uniqFace, row_index_u, column_index_u); // load data into grid layout.
            ui->tabWidget->setTabText(1, " Unique Faces (" + QString::number(uniq_faceList.size()) + ")");

        }else {
            //qDebug()<<"face list greater than 100";
            delete uniq_faceList.at(0); // deallocation done
            uniq_faceList.removeFirst(); // remove first element
            uniq_faceList.push_back(uniqFace); // face added into list
            ui->tabWidget->setTabText(1, " Unique Faces (" + QString::number(uniq_faceList.size()) + ")");

            QListIterator<Face*> iter(uniq_faceList); // iterator
            iter.toFront(); // iterator start from first


            // set face into grid layout which are new come
            for (int i = 0; i < 10; ++i){
                for (int j = 0; j < 10; ++j){
                    // for 100 cell
                    grid_show_uniq_faces->addWidget(iter.next(), i, j); // load data into grid layout.
                }

            }

        }
        //  Grid index customize
        if(column_index_u == 10){
            //qDebug()<<"colum index equal 10";
            row_index_u++;
            column_index_u = -1;
        }

        if(row_index_u == 10){
            //qDebug()<<"row equal 10";
            row_index_u = 0;
        }
        column_index_u++;
    }

    ui->scrollAreaCluster->verticalScrollBar()->setSliderPosition(ui->scrollAreaCluster->verticalScrollBar()->maximum());

}

void Faces::uniqueLicencePlateShowInTiles(QPixmap piclpr, QString lprstr, int matchIndx, QString color)
{
    qDebug()<<"uniqueLicencePlateShowInTiles call";

    setlpr.insert(lprstr);

    if(setlpr.size() > 1000){
        setlpr.clear();
    }
    if(setlpr.size() > updateCheckerLpr){
        updateCheckerLpr = setlpr.size();

        Lpr *uniqLpr = new Lpr();
        uniqLpr->setObjectLpr(piclpr, lprstr, matchIndx, color);

        // Checked Image Null or Not! After getting correct image, hold into list.
        if (!piclpr.isNull()){

            qDebug()<<"lpr pic is not null"<<" uniqueLprList.size() >>"<<uniqueLprList.size();
            if (uniqueLprList.size() < 100){// Checked size of list is 100 or not!
                qDebug()<<"uniqueLprList less than 100";

//                QString face_path = "/home/sigmind/Desktop/lp/";
//                piclpr.save(face_path, ".PNG");

                uniqueLprList.push_back(uniqLpr); // Added lpr in Lists
                grid_show_unique_lpr->addWidget(uniqLpr, row_index_lpr, column_index_lpr); // load data into grid layout.
                ui->tabWidget->setTabText(3, " Unique LPR (" + QString::number(uniqueLprList.size()) + ")");
//                ui->tabWidget->setTabText(4, "LPR (" + QString::number(uniqueLprList.size()) + ")");

            }else {
                qDebug()<<"lpr list greater than 100";
                delete uniqueLprList.at(0); // deallocation done
                uniqueLprList.removeFirst(); // remove first element
                uniqueLprList.push_back(uniqLpr); // lpr added into list
                ui->tabWidget->setTabText(3, " Unique LPR (" + QString::number(uniqueLprList.size()) + ")");
//                ui->tabWidget->setTabText(4, "LPR (" + QString::number(uniqueLprList.size()) + ")");

                QListIterator<Lpr*> iter(uniqueLprList); // iterator
                iter.toFront(); // iterator start from first


                // set face into grid layout which are new come
                for (int i = 0; i < 10; ++i){
                    for (int j = 0; j < 10; ++j){
                        // for 100 cell
                        grid_show_unique_lpr->addWidget(iter.next(), i, j); // load data into grid layout.
                    }

                }

            }
            //  Grid index customize
            if(column_index_lpr == 10){
                ////qDebug()<<"colum index equal 10";
                row_index_lpr++;
                column_index_lpr = -1;
            }

            if(row_index_lpr == 10){
                ////qDebug()<<"row equal 10";
                row_index_lpr = 0;
            }
            column_index_lpr++;
        }

        ui->scrollAreaLPR->verticalScrollBar()->setSliderPosition(ui->scrollAreaLPR->verticalScrollBar()->maximum());
//        ui->scrollAreaCar->verticalScrollBar()->setSliderPosition(ui->scrollAreaCar->verticalScrollBar()->maximum());

    }
}

void Faces::add_recog_face_To_tiles(QPixmap pic, QString name, int idx)
{
    Face *newFace2 = new Face();
    newFace2->setObject(pic, name, idx);

    qDebug()<<"add_recog_face_To_tiles call";

    // Checked Image Null or Not! After getting correct image, hold into list.
    if (!pic.isNull()){

        if (recog_faceList.size() < 100){// Checked size of list is 100 or not!
            qDebug()<<"facelist less than 100";
            recog_faceList.push_back(newFace2); // Added face in Lists
            grid_show_recog_faces->addWidget(newFace2, row_index_r, column_index_r); // load data into grid layout.
            ui->tabWidget->setTabText(2, " Recognized Faces (" + QString::number(recog_faceList.size()) + ")");

        }else {
            qDebug()<<"face list greater than 100";
            delete recog_faceList.at(0); // deallocation done
            recog_faceList.removeFirst(); // remove first element
            recog_faceList.push_back(newFace2); // face added into list
            ui->tabWidget->setTabText(2, " Recognized Faces (" + QString::number(recog_faceList.size()) + ")");

            QListIterator<Face*> iter(recog_faceList); // iterator
            iter.toFront(); // iterator start from first

            // set face into grid layout which are new come
            for (int i = 0; i < 10; ++i){
                for (int j = 0; j < 10; ++j){
                    // for 100 cell
                    grid_show_recog_faces->addWidget(iter.next(), i, j); // load data into grid layout.

                }

            }

        }
        //  Grid index customize
        if(column_index_r == 10){
            ////qDebug()<<"colum index equal 10";
            row_index_r++;
            column_index_r = -1;
        }

        if(row_index_r == 10){
            ////qDebug()<<"row equal 10";
            row_index_r = 0;
        }
        column_index_r++;
    }
    ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());
}

void Faces::addUniqueFace(QPixmap m_pic, QPixmap pic, QString name, int idx, dlib::matrix<float,(long)0,(long)1> pic_template, double confidence, int fpsValue, int rec_or_not_value, QString gender, int age, QString color){

    // extra
    rec_or_not_value = 1;

    if(fpsValue < 1){
        fpsValue = 1;
        //qDebug()<<"fpsValue less than 1 "<<fpsValue;
    }

    if(cluster_templates.size() > 112344){
        cluster_templates.clear();
        memset(sameFacesTimesIdCount, 0, sizeof(sameFacesTimesIdCount));
    }
    int cl = cluster_templates.size();

    double mn= 100.0;
    for(int i=0; i<cluster_templates.size(); i++)
    {
        double diff = dlib::length(pic_template-cluster_templates[i]);
        if(diff<mn && diff<0.55)// match same image
        {
            mn= diff;
            cl = i;// cluster ID store for same image
            //qDebug() << " >>>>>>>>>>>> CL falue inside loop= \n" << QString::number(cl);
        }
    }
    //qDebug() << " >>>>>>>>>>>> CL falue outside loop= \n" << QString::number(cl);

    if(cl == cluster_templates.size())//always push unique face
    {

        ////qDebug()<<"cl "<<cl<<" "<<cluster_templates.size();
        cluster_templates.push_back(pic_template);

        sameFacesTimesIdCount[cl] = sameFacesTimesIdCount[cl] + 1;
        int stor = sameFacesTimesIdCount[cl];
        stor = (int)stor/fpsValue;
//        qDebug() << "valo if "<< confidence << " " << rec_or_not_value;
        if(confidence >0.0 && rec_or_not_value == 1){

            emit notifyFaceFromUniqueFace(m_pic, pic, name, idx, cl, stor, confidence, gender, age, color);
            add_recog_face_To_tiles(pic, name, idx);
        }
        emit unique_face_to_main_window(pic, name, idx, cl, stor, confidence, rec_or_not_value, gender, age);

        only_uniqueFace_show_inTiles(pic, name, idx);// known, unknown unique faces show in tiles
    }
    else{

        sameFacesTimesIdCount[cl] = sameFacesTimesIdCount[cl] + 1;
        int stor = sameFacesTimesIdCount[cl];
        stor = (int)stor/fpsValue;
//        qDebug() << "blallllllllllllllllllllllllllllllllllllllll else"<< confidence << " " << rec_or_not_value;
        if(confidence >0.0 && rec_or_not_value == 1)
        {

            emit notifyFaceFromUniqueFace(m_pic, pic, name, idx, cl, stor, confidence, gender, age, color);
        }
    }

//    int cl = 10;
//    int stor = 10;
//    emit notifyFaceFromUniqueFace(m_pic, pic, name, idx, cl, stor, confidence, gender, age, color);

}

void Faces::addUniqueFace(QPixmap main_pic_person, QPixmap pic, QString name, int idx, dlib::matrix<float,(long)0,(long)1> pic_template, double confidence, int fpsValue, int rec_or_not_value, QString gender, int age)
{

    QString lpr_path_for_first = "/mnt/nvme0n1p1/captures/faces/";

    QString date_for_first =  QDateTime::currentDateTime().toString("dd-MM-yyyy");
    QString qstr_for_first = QDateTime::currentDateTime().toString("hh:mm:ss");

    QDir myDir;
    if(!myDir.exists(lpr_path_for_first+"/"+date_for_first)){
        myDir.mkpath(lpr_path_for_first+"/"+date_for_first);
    }
    cker = cker+1;
//    pic.save(lpr_path_for_first+"/"+date_for_first+"/"+cker+"_"+"1.png");// pic write
    pic.save(lpr_path_for_first+"/"+date_for_first+"/"+qstr_for_first+"_"+"1.png");// pic write

    if(fpsValue < 1){
        fpsValue = 1;
        //qDebug()<<"fpsValue less than 1 "<<fpsValue;
    }

    if(cluster_templates.size() > 112344){
        cluster_templates.clear();
        memset(sameFacesTimesIdCount, 0, sizeof(sameFacesTimesIdCount));
    }
    int cl = cluster_templates.size();

    double mn= 100.0;
    for(int i=0; i<cluster_templates.size(); i++)
    {
        double diff = dlib::length(pic_template-cluster_templates[i]);
        if(diff<mn && diff<0.55)// match same image
        {
            mn= diff;
            cl = i;// cluster ID store for same image
            //qDebug() << " >>>>>>>>>>>> CL falue inside loop= \n" << QString::number(cl);
        }
    }
    qDebug() << " >>>>>>>>>>>> CL falue outside loop= " << QString::number(cl)<<"\n";

    if(cl == cluster_templates.size())//always push unique face
    {
        ////qDebug()<<"cl "<<cl<<" "<<cluster_templates.size();
        cluster_templates.push_back(pic_template);

        sameFacesTimesIdCount[cl] = sameFacesTimesIdCount[cl] + 1;
        int stor = sameFacesTimesIdCount[cl];
        stor = (int)stor/fpsValue;
        qDebug()<<"sameFacesTimesIdCount[cl] = "<<sameFacesTimesIdCount[cl]<<" fpsValue "<<fpsValue<<" stor of times "<<stor;

        if(confidence >0.0 && rec_or_not_value == 1){
            qDebug()<<"confidence greater than zero "<<confidence;
            emit notifyFaceFromUniqueFace(main_pic_person, pic, name, idx, cl, stor, confidence, gender, age);
            add_recog_face_To_tiles(pic, name, idx);
        }
        if(rec_or_not_value == 0){//suspect face
            emit unique_face_to_main_window(pic, name, idx, cl, stor, confidence, rec_or_not_value, gender, age);
        }

        //addFR(pic,name,idx);// for all faces show in tiles

        only_uniqueFace_show_inTiles(pic, name, idx);// known, unknown unique faces show in tiles

        //        addUniqueFaceToTiles(pic, name, idx, pic_template);
        //  emit notifyFaceFromUniqueFace(pic, name, idx, cl, stor, confidence);

        ////qDebug()<<"cl if ="<<cl<<" sameFacesTimesIdCount = "<<sameFacesTimesIdCount[cl];

        //        Face *uniqFace = new Face();
        //        uniqFace->setObject(pic, name, idx);
        //        flowLayout2->addWidget(uniqFace);
        //        connect(uniqFace, SIGNAL(emitPicDB(QPixmap)), this, SLOT(justcheck(QPixmap)));
        //        ui->tabWidget->setTabText(1, " Unique Faces (" + QString::number(cluster_templates.size()) + ")");
    }
    else{
        sameFacesTimesIdCount[cl] = sameFacesTimesIdCount[cl] + 1;
        int stor = sameFacesTimesIdCount[cl];
        stor = (int)stor/fpsValue;
        ////qDebug()<<"sameFacesTimesIdCount[cl] = "<<sameFacesTimesIdCount[cl]<<" fpsValue "<<fpsValue<<" stor of times "<<stor;
        if(confidence >0.0 && rec_or_not_value == 1)
        {
            qDebug()<<"else adduniqueface";
            emit notifyFaceFromUniqueFace(main_pic_person, pic, name, idx, cl, stor, confidence, gender, age);
        }
        if(rec_or_not_value == 0){//suspect face
            qDebug()<<"unique_face_to_main_window emitted.......else";
            emit unique_face_to_main_window(pic, name, idx, cl, stor, confidence, rec_or_not_value, gender, age);
        }

        //addFR(pic,name,idx);//show all faces in tiles

        //addUniqueFaceToTiles(pic, name, idx, pic_template);
        ////qDebug()<<"cl else="<<cl<<" sameFacesTimesIdCount = "<<sameFacesTimesIdCount[cl];

        //        Face *uniqFace = new Face();
        //        uniqFace->setObject(pic, name, idx);
        //        flowLayout2->addWidget(uniqFace);
        //        connect(uniqFace, SIGNAL(emitPicDB(QPixmap)), this, SLOT(justcheck(QPixmap)));
        //        ui->tabWidget->setTabText(1, " Unique Faces (" + QString::number(cluster_templates.size()) + ")");
    }
}

void Faces::justcheck(QPixmap fce)
{
    //qDebug()<<"test ok capture str ";
    emit emitPicDB_mw_signal(fce);
}

void Faces::displayCluster(int id)
{
    clusterDialog* clDialog= new clusterDialog(this);
    for(int i=0;i<allFaces.at(id).size();i++){

        clDialog->addFace(allFaces.at(id).at(i));
    }
    //clDialog->setAttribute( Qt::WA_DeleteOnClose );
    clDialog->show();
}



//void Faces::addNewLPR(QPixmap pic, QString name, int idx)
//{
//    QString Endo = "LP OCR ed >>>>>>>>>>>>>>>>>>>><<<<<<<<<<<";
//    qDebug(qUtf8Printable(Endo));
//    qDebug(qUtf8Printable(name));
//  //  plateData = enc;//.toUtf8().constData();
//   // plateData = "dhaka";
//   // plateData = name;
// //  emit addLP(pic,name, idx);



//}
void Faces::receiveTile(QPixmap pic, QString str, int indx)
{


    //while(1);
    // Face *newFace = new Face(this);
    // newFace->setFace(pic, str, indx,0);

    //  flowLayout->addWidget(newFace);
    //ui->scrollAreaFaces->verticalScrollBar()->setSliderPosition(ui->scrollAreaFaces->verticalScrollBar()->maximum());
}

void Faces::receiveTileLP(QPixmap pic, QString str, int indx)
{
    //    worker->abort();
    //    thread->wait(); // If the thread is not running, this will immediately return.
    //    QString enc = "receive tileLP";
    //    worker->requestWork();

    //    emit requestUpdateLPR(pic, enc, indx);
    //    worker->abort();
    //    thread->wait(); // If the thread is not running, this will immediately return.
    //    QString enc = "LPR";
    //    worker->requestWork();
    //    emit requestUpdateLPR(pic, str, indx);
    //while(1);
    // Face *newFace = new Face(this);

    // newFace->setObject(pic, str, indx);

    // flowLayout3->addWidget(newFace);
}

void Faces::addObject(QPixmap pic, QString name, int idx)
{
    Face *newFace = new Face(this);
    newFace->setObject(pic, name, idx);

    flowLayout->addWidget(newFace);
}
void Faces::clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}



/**
 * Helper function. Deletes all child widgets of the given layout @a item.
 */
void Faces::deleteChildWidgets(QLayoutItem *item) {
    if (item->layout()) {
        // Process all child items recursively.
        for (int i = 0; i < item->layout()->count(); i++) {
            deleteChildWidgets(item->layout()->itemAt(i));
        }
    }
    delete item->widget();
}

void Faces::removeRow(QGridLayout *layout, int row, bool deleteWidgets) {
    remove(layout, row, -1, deleteWidgets);
    layout->setRowMinimumHeight(row, 0);
    layout->setRowStretch(row, 0);
}

void Faces::remove(QGridLayout *layout, int row, int column, bool deleteWidgets) {
    // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
    for (int i = layout->count() - 1; i >= 0; i--) {
        int r, c, rs, cs;
        layout->getItemPosition(i, &r, &c, &rs, &cs);
        if ((r <= row && r + rs - 1 >= row) || (c <= column && c + cs - 1 >= column)) {
            // This layout item is subject to deletion.
            QLayoutItem *item = layout->takeAt(i);
            if (deleteWidgets) {
                deleteChildWidgets(item);
            }
            delete item;
        }
    }
}


void Faces::addFR(QPixmap pic, QString name, int idx)
{
    //------------

    ////qDebug()<<"addfr call faces threadId "<<thread()->currentThreadId();


    Face *newFace = new Face();
    newFace->setObject(pic, name, idx);

    //    connect(newFace, SIGNAL(emitPicDB(QPixmap)), this, SLOT(justcheck(QPixmap)));

    qDebug() << "addfr call";

    // Checked Image Null or Not! After getting correct image, hold into list.
    if (!pic.isNull()){
        //qDebug()<<"pic is not null"<<" faceList.size() >>"<<faceList.size();
        if (faceList.size() < 100){// Checked size of list is 100 or not!
            qDebug()<<"j facelist less than 100";
            faceList.push_back(newFace); // Added face in Lists
            grid_show_all_faces->addWidget(newFace, row_index, column_index); // load data into grid layout.

        }else {
            qDebug()<<"j face list greater than 100";
            delete faceList.at(0); // deallocation done
            faceList.removeFirst(); // remove first element
            faceList.push_back(newFace); // face added into list

            QListIterator<Face*> iter(faceList); // iterator
            iter.toFront(); // iterator start from first


            // set face into grid layout which are new come
            for (int i = 0; i < 10; ++i){
                for (int j = 0; j < 10; ++j){
                    // for 100 cell
                    grid_show_all_faces->addWidget(iter.next(), i, j); // load data into grid layout.

                }

            }

        }
        //  Grid index customize
        if(column_index == 10){
            //qDebug()<<"colum index equal 10";
            row_index++;
            column_index = -1;
        }

        if(row_index == 10){
            //qDebug()<<"row equal 10";
            row_index = 0;
        }
        column_index++;
    }
    //    //qDebug() << "output is " << faceList.size();

    //    //qDebug() <<  << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
    //    if (faceList.size()==100){
    //        //qDebug() << "Array list size is 100";
    //    }

    //    //qDebug() << "Size ===== " << faceList.size();


    //    flowLayout->addWidget(newFace);

    ui->scrollAreaFaces->verticalScrollBar()->setSliderPosition(ui->scrollAreaFaces->verticalScrollBar()->maximum());

    // -------

    //    QString face_path = "./captures/faces/";
    //    QString obliq = "/";
    //    // QString forma = "dd.MM.yyyy";
    //    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    //    QString at = "<at>";
    //    //QDir().mkdir(date);

    //    QString img_path = face_path+date+obliq;
    //    QDir myDir;
    //    if(!myDir.exists(date))
    //    {

    //        myDir.mkpath(img_path);
    //        QFile file(img_path+name+at+QTime::currentTime().toString());
    //        file.open(QIODevice::WriteOnly);
    //        pic.save(&file, "PNG");

    //    }
    //    //    ui->label->clear();
    //    //     ui->label->setPixmap(pic);
    //    //     ui->label->setScaledContents( true );
    //    //     ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    //    //     QPixmap pic2 = pic;
    //    //        ui->label_2->clear();
    //    //     ui->label_2->setPixmap(pic2);
    //    //     ui->label_2->setScaledContents( true );
    //    //        ui->label_3->clear();
    //    //     QPixmap pic3 = pic2;
    //    //        ui->label->clear();
    //    //     ui->label_3->setPixmap(pic2);
    //    //     ui->label_3->setScaledContents( true );

    //    //     Face *newFace = new Face(this);
    //    //     newFace->setObject(pic, name, idx);
    //    //        ui->faceWidget->setLayout(mainLayout);
    //    //        mainLayout->addWidget(newFace);
    //    //        newFace->removeObject(pic, name, idx);

    //    // ui->faceWidget->deleteLater();
    //    //   mainLayout->removeWidget(mainLayout->itemAtPosition(1, 0)->widget());
    //    //        QLayoutItem *child;
    //    //        while ((child = mainLayout->takeAt(i)) != 0)  {

    //    //            delete child;
    //    //        }

    //    i++;
    //    // remove(mainLayout,0,1,true);
    //    // mainLayout->addWidget(newFace);
    //    // ui->gridLayout_6->setLayout(mainLayout);
    //    //   mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

    //    //     ui->label1->setPixmap(pic);
    //    //     ui->label1->setScaledContents( true );
    //    //     ui->label1->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    //    ////    // ui->label1->setToolTip("Name: "+ name + "\n" + "camera: " + QString::number(cam) + "\n" + getCurrentTime());
    //    //if(i>1)
    //    //{
    //    //    ui->label1->clear();
    //    //    //delete pic;
    //    //    i=0;
    //    //}
    //    Face *newFace = new Face(this);
    //    newFace->setObject(pic, name, idx);
    //    flowLayout->addWidget(newFace);
    //    //   // ui->horizontalLayout->addWidget(newFace);
    //    //    //   //qDebug() << "Labels count: " << ui->horizontalLayout->count();


    //    //         layout->addWidget(newFace);
    //    //         layout->addWidget(button2);
    //    //         layout->addWidget(button3);
    //    //         layout->addWidget(button4);
    //    //         layout->addWidget(button5);

    //    //        // window->setLayout(layout);
    //    //        // window->show();



    //    //     //  delete layout;

    //    //    //   delete ui->horizontalLayout->takeAt(i-1);
    //    //     //  //qDebug() << "Labels count: " << ui->horizontalLayout->count();

    //    ////        QLayoutItem *child = ui->horizontalLayout->takeAt(i);
    //    ////           if (child)
    //    ////           {
    //    ////                delete child->widget();
    //    ////                delete child;
    //    ////           }

    //    //    // delete layout;
    //    //        flowLayout->removeWidget(newFace);
    //    //             //   ui->horizontalLayout->removeWidget(newFace);
    //    //                    delete newFace;
    //    // // clearLayout(ui->horizontalLayout);
    //    //       i=0;
    //    //      //  layout = new QHBoxLayout;
    //    // //   }
    //    ////    flowLayout->addWidget(newFace);
    //    ui->scrollAreaFaces->verticalScrollBar()->setSliderPosition(ui->scrollAreaFaces->verticalScrollBar()->maximum());

    ////    i++;

    ////            if(i>5)
    ////            {



    ////  //  //qDebug() <<"deleted: "<<flowayout->count();

    ////         //       //    }
    ////         i=1;

    //        delete flowLayout;
    ////         //delete ui;
    //        flowLayout= new FlowLayout();



    ////    //    ui->setupUi(this);
    //        ui->scrollAreaWidgetContents->setLayout(flowLayout);
    //     }

    //  delete newFace;

    //     flowLayout= new FlowLayout(0,0,0);


    //     ui->scrollAreaWidgetContents->setLayout(flowLayout);
}

void Faces::addFaceRecognized(QPixmap pic, QString name, int idx)
{
    QString face_path = "./captures/faces-recognized/";
    QString obliq = "/";
    // QString forma = "dd.MM.yyyy";
    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    QString at = "<at>";
    //QDir().mkdir(date);

    QString img_path = face_path+date+obliq;
    QDir myDir;
    if(!myDir.exists(date))
    {

        myDir.mkpath(img_path);
        QFile file(img_path+name+at+QTime::currentTime().toString());
        file.open(QIODevice::WriteOnly);
        pic.save(&file, "PNG");

    }

    Face *newFace = new Face(this);
    newFace->setObject(pic, name, idx);
    flowLayout4->addWidget(newFace);
}

void Faces::addLPR(QPixmap pic, QString name, int idx)
{
    qDebug(qUtf8Printable(name));
    Face *newFace = new Face(this);
    QString plate = "addNewLPR theke bolchi";
    newFace->setObject(pic, name, idx);


    flowLayout3->addWidget(newFace);
    QString Endo = "LP OCR ed >>>>>>>>>>>>>>>>>>>><<<<<<<<<<<";
    qDebug(qUtf8Printable(Endo));

    QString lpr_path = "./captures/license_plates/";
    QString obliq = "/";
    // QString forma = "dd.MM.yyyy";
    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    QString at = "<at>";
    //QDir().mkdir(date);

    QString img_path = lpr_path+date+obliq;
    QDir myDir;
    if(!myDir.exists(date))
    {

        myDir.mkpath(img_path);
        QFile file(img_path+name+at+QTime::currentTime().toString());
        file.open(QIODevice::WriteOnly);
        pic.save(&file, "PNG");

    }

}
Faces::~Faces()
{
    cluster_templates.clear();
    for(int i=0;i<faceList.size(); i++){
        delete faceList.at(i);
    }
    for(int j=0; j<uniq_faceList.size(); j++){
        delete uniq_faceList.at(j);
    }

    delete ui;
}
