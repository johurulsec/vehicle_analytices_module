#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QInputDialog>
#include <QDir>
#include <QScrollBar>

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);
    //    std::vector<int> source_num;
    //    source_num = emit getSourceVecFromDs();
    //    qDebug() << "value riayd " << source_num.size();


    obValues = myStyles::objectValues;
    emailList = myStyles::emailsTo;
    faceFolder = myStyles::faceFolderRelative;
    blackFolder = myStyles::blackFolderRelative;

    //    //qDebug() << obValues;
    //    //qDebug() << emailList;

    ui->faceCheck->setChecked(obValues.at(0));
    ui->maskedFaceCheck->setChecked(obValues.at(1));
    ui->personCheck->setChecked(obValues.at(2));
    ui->baggageCheck->setChecked(obValues.at(3));
    ui->cellPhoneCheck->setChecked(obValues.at(4));
    ui->bicycleCHeck->setChecked(obValues.at(5));
    ui->carCheck->setChecked(obValues.at(6));
    ui->busCheck->setChecked(obValues.at(7));
    ui->motorcycleCheck->setChecked(obValues.at(8));
    ui->truckCheck->setChecked(obValues.at(9));
    //    ui->licenseCheck->setChecked(obValues.at(10));
    ui->knifeCheck->setChecked(obValues.at(11));
    ui->checkBox_suspect->setChecked(true);
    ui->face_check->setChecked(true);
    ui->lpr_check->setChecked(true);

    ui->checkbox_unique_face->setChecked(false);
    ui->checkbox_db_sync->setChecked(false);
    emailCount=0;
    foreach(QString em, emailList){

        EmailBox *box = new EmailBox(emailCount, em, this);
        connect(box, SIGNAL(removeBox(int)), this, SLOT(removeEmail(int)));
        connect(box, SIGNAL(textChange(int,QString)), this, SLOT(textChange(int,QString)));

        ui->emailVerticalBox->addWidget(box);
        emailCount++;
    }


    ui->settingsTab->setCurrentIndex(0);
    ui->emailCheck->toggled(false);
    ui->smsCheck->toggled(false);
    ui->audibleCheck->toggled(false);
    ui->enableNotCheck->setChecked(myStyles::notificationFlag);
    ui->enableNotCheck->toggled(myStyles::notificationFlag);
    ui->emailCheck->setChecked(myStyles::notificationFlag);

    ui->faceRecogCheck->setChecked(myStyles::faceRecognitionFlag);
    ui->faceRecogCheck->toggled(myStyles::faceRecognitionFlag);
    ui->faceRecogDirLine->setText(myStyles::faceFolderRelative);

    ui->blackListDirLine->setText(myStyles::blackFolderRelative);

    ui->objectSensitivitySlider->setValue(myStyles::objectSensitivitySlider);
    //ui->faceRecogSenseBar->setValue(myStyles::faceSensitivitySlider);
    ui->faceRecogSenseBar->setValue(55);

    ui->obDetText->setText(QString::number(myStyles::objectSensitivityValue));
    ui->faceDetText->setText(QString::number(myStyles::faceSensitivityValue));

    ui->faceRecogDirLine->setReadOnly(true);
    ui->blackListDirLine->setReadOnly(true);

    objectSensitivityChange= false;
    faceSensitivityChange=false;

    consLike();

    // infor = new cameraListWidget(this);



    //    loadIntoWidget();
    //    ui->scrollArea_cam_list->setLayout(ui->verticalLayout_cam_list_s);
    //ui->scrollArea_cam_list->verticalScrollBar()->setSliderPosition(ui->scrollArea_cam_list->verticalScrollBar()->maximum());
    //    ui->scrollArea_camera_list->verticalScrollBar()->setSliderPosition(ui->scrollArea_camera_list->verticalScrollBar()->maximum());

    //    ui->pushButton_add_camera->setEnabled(false);

    ui->faceRecogSenseBar->setValue(0.45);// given that, defualt threshold value

    ui->tableWidget_addLPR->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidget_addLPR->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_addLPR->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_addLPR->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget_addLPR->setAutoScroll(true);
    ui->tableWidget_addLPR->resizeRowsToContents();
    ui->tableWidget_addLPR->resizeColumnsToContents();
    ui->tableWidget_addLPR->horizontalHeader()->setStretchLastSection(true);

    videoAnalyticsCons();

    //----------------------- for smart record
    ui->on_radioButton->setChecked(false);//default
    ui->off_radioButton->setChecked(true);
    ui->mp4_radioButton->setChecked(true);//default
    ui->mkv_radioButton->setChecked(false);
    //===============

    ///for LPR OCR selection radio button
    ui->radioButton_google_api->setChecked(false);//default true
    ui->radioButton_tess_api->setChecked(true);//default false

    //----------------- for line drawing
    grid_slider = new QGridLayout; // Initialize Grid Layout
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
    ui->scrollAreaWidgetContents->setLayout(grid_slider);

    //./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt

    collectWhichSourceEnableOrNot();// return total source no

    int i;
    for (i = 0; i < store_source_id_list.size(); ++i){

        int srcId = store_source_id_list.at(i);
        double divVal = store_divisor_value_list.at(i) * 10.0;// multiply 10 for slider full value
        qDebug()<<"srcId : "<<srcId;

        singleSlider *single_slider = new singleSlider(srcId, divVal, this);

        grid_slider->addWidget(single_slider, 0, column_index++);// rowNo- 0 and colomnNo- increasing
        ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());

        stor_sldr_lst.push_back(single_slider);

    }
    //=================

}

void settingsDialog::collectWhichSourceEnableOrNot()
{

    QFile input_file("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");

    input_file.open(QIODevice::WriteOnly | QIODevice::ReadOnly);
    QTextStream in(&input_file);

    QString fstpart = "[source", trdpart = "]";
    QString fsten = "enable=";

    QString cap_src;

    bool ck=false;
    while(!in.atEnd()){
        QString line = in.readLine();
        if(fstpart + line.mid(7, 1) + trdpart == line || fstpart + line.mid(7, 2) + trdpart == line || fstpart + line.mid(7, 3) + trdpart == line){// compare source no (0 to 999)
            cap_src = line;
            //qDebug()<<"match src :"<<line;
            ck=true;
            continue;
        }
        if(ck){
            //qDebug()<<"enable :"<<line;
            if(fsten+line.mid(7, 1) == line && line.mid(7, 1) =="1"){

                QString tm;
                if(cap_src.size() == 9){
                    tm = cap_src.mid(7, 1);
                }else if(cap_src.size() == 10){
                    tm = cap_src.mid(7, 2);
                }else if(cap_src.size() == 11){
                    tm = cap_src.mid(7, 3);
                }

                int str_to_int = tm.toInt();
                //qDebug()<<"match enable :"<<line<<" and src is : "<<str_to_int<<" tm sz: "<<cap_src.size();
                store_source_id_list.push_back(str_to_int);
                cap_src = "";
            }
            ck= false;
        }

    }

    qDebug()<<"total source no is : "<<store_source_id_list.size();

    for(int m = 0;m<store_source_id_list.size(); m++){
        qDebug()<<"source Id : "<<store_source_id_list.at(m);
    }

    retriveDivisorValue();
}

void settingsDialog::retriveDivisorValue()
{

    QFile input_file("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");

    input_file.open(QIODevice::WriteOnly | QIODevice::ReadOnly);
    QTextStream in(&input_file);

    QStringList lst,lst2;

    while(!in.atEnd()){
        QString line = in.readLine();
        lst+=line;//load config file here
    }

    qDebug()<<"list size is >>> "<<lst.size();
    //divisor=4
    QString dbsr = "divisor=";
    QString fstpart = "[source", trdpart = "]";
    QString fsten = "enable=";

    QString cap_src;
    bool ck=false, flg=false;
    int index=0;

    for(int l=0; l<lst.size(); l++){

        if(fstpart + lst.at(l).mid(7, 1) + trdpart == lst.at(l) || fstpart + lst.at(l).mid(7, 2) + trdpart == lst.at(l) || fstpart + lst.at(l).mid(7, 3) + trdpart == lst.at(l)){// compare source no (0 to 999)
            cap_src = lst.at(l);
            qDebug()<<"match src :"<<cap_src;
            ck=true;
            flg = true;
            //lst2+=lst.at(l);
            continue;
        }else if(ck && flg){
            flg = false;

            //lst2+=lst.at(l);
            qDebug()<<"enable str : "<<lst.at(l);
            if(fsten+lst.at(l).mid(7, 1) == lst.at(l) && lst.at(l).mid(7, 1) == "1"){// check enable 1 or 0 here
                ck=true;
                qDebug()<<"match enable : "<<lst.at(l);

            }else{
                ck=false;
                qDebug()<<"match disable : "<<lst.at(l);
            }

        }else if("divisor=" == lst.at(l).mid(0, 8) && ck == true){

            QString s = lst.at(l).mid(8, lst.at(l).size());
            double div_only_val = s.toDouble();
            qDebug()<<"get first time dibisor val : "<<div_only_val;
            store_divisor_value_list.push_back(div_only_val);


            //            qDebug()<<"str_to_int : "<<str_to_int;

            //            int update_sl_val = store_slider_pair_value[index].second;//take runtime slider value
            //            index++;

            //            QString tm2 = "divisor="+ QString::number(update_sl_val);
            //            qDebug()<<"update_sl_val: "<<update_sl_val<<" tm2: "<<tm2;
            //            lst2 += tm2;

            cap_src = "";
            ck = false;

        }else{
            //lst2+=lst.at(l);
        }

    }

    //    input_file.resize(0);// clear file data hare
    //    qDebug()<<"lst2 sz : "<<lst2.size();

    //    for(int ii = 0;ii<lst2.size();ii++){// file write again
    //        in<<lst2.at(ii)<<"\n";//write into file
    //    }

    in.flush();
    input_file.close();

    lst.clear();
    lst2.clear();

}

void settingsDialog::videoAnalyticsCons(){

    ui->dateTimeEdit_from->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit_to->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

    ui->dateTimeEdit_from->setDateTime(QDateTime::fromString("2020-01-01 00:00:00", "yyyy-MM-dd hh:mm:ss"));
    ui->dateTimeEdit_to->setDateTime(QDateTime::fromString("2100-12-31 23:59:59", "yyyy-MM-dd hh:mm:ss"));

    ui->checkBox_face_check->setChecked(true);//default
    ui->checkBox_person->setChecked(true);//default
    ui->checkBox_male->setChecked(true);
    ui->checkBox_female->setChecked(true);
    ui->checkBox_masked_face->setChecked(true);

    QStringList colors;
    colors <<"select" <<"Red" << "Green" <<"Blue" << "Black" <<"White";
    ui->combobox_pick_color->addItems(colors);

    QStringList category;
    category<<"select"<<"Large Vehicle"<<"Sedan";
    ui->combobox_category->addItems(category);

    QStringList vehicles_type;
    vehicles_type<<"select"<<"Car"<<"Bus"<<"Truck"<<"CNG"<<"Bicycle";
    ui->comboBox_vehicles->addItems(vehicles_type);

    face_v = false; person_v = false; mask_face_v = false; male_v = false; female_v = false;

    ui->lineEdit_age_from->setText("5");
    ui->lineEdit_25_age_to->setText("80");

    grid_show_all_faces = new QGridLayout;
    ui->scrollAreaWidgetContents_results->setLayout(grid_show_all_faces);

    //    ui->scrollArea_for_image_vda->verticalScrollBar()->setSliderPosition(ui->scrollArea_for_image_vda->verticalScrollBar()->maximum());

    //    faceList = new QList<VD_Face*>();
}



void settingsDialog::updateRtsp(QString src, QString rtsp)
{
    QFile input_file("./.cfg/source8_1080p_dec_infer-resnet_tracker_tiled_display_fp16_nano_one.txt");
    if (!input_file.open(QFile::ReadOnly)) {
        //qDebug() << "Error opening for read: " << input_file.errorString();
        return;
    }
    QTextStream in(&input_file);

    QStringList str;
    int i = 0;
    while(!in.atEnd()){
        QString line = in.readLine();
        if(line == src){
            i = 1;
        }
        if(i>=1 && i<=6){
            if(i==6){
                ////qDebug() << "Rtsp ===== " << rtsp;
                str.append(rtsp);
            }else{
                str.append(line);
            }

            ++i;
        }else{
            str.append(line);
            i=0;
        }
    }
    input_file.close();

    if(!input_file.open(QFile::WriteOnly)){
        //qDebug() << "Error opening for write: " << input_file.errorString();
        return;
    }
    QTextStream outStream(&input_file);
    for(int i = 0; i < str.size(); i++){
        outStream << str[i]<<"\n";
    }
    input_file.close();
    str.clear();
    consLike();
    //    //qDebug() << "Hujur " << str;
}

void settingsDialog::loadDataFromTableForLPR()
{
    QStringList col;
    col << "ID" << "LPR";
    ui->tableWidget_addLPR->setRowCount(0);
    ui->tableWidget_addLPR->setColumnCount(2);
    ui->tableWidget_addLPR->setHorizontalHeaderLabels(col);






    if(connectionDB()){
        QSqlQuery qLprToTableWidget;
        if(qLprToTableWidget.exec("select * from given_lpr;")){
            while(qLprToTableWidget.next()){
                int Id = qLprToTableWidget.value(0).toInt();
                QString nmbr_plate = qLprToTableWidget.value(1).toString();
                int i = ui->tableWidget_addLPR->rowCount();
                ui->tableWidget_addLPR->insertRow(i);
                ui->tableWidget_addLPR->setItem(i, 0, new QTableWidgetItem(QString::number(Id)));
                ui->tableWidget_addLPR->setItem(i, 1, new QTableWidgetItem(nmbr_plate));
            }
        }
    }
}

settingsDialog::~settingsDialog()
{
    //qDebug() << "settingsDialog::~settingsDialog()";
    list_of_path.clear();
    for(int i = 0; i < faceList.size(); i++){
        delete faceList.at(0); // deallocation done
        faceList.removeFirst();
    }
    delete ui;
    //    cam_info_list->clear();
    //    delete cam_info_list;
    //delete infor;

    store_slider_pair_value.clear();
    for(int i=0;i<stor_sldr_lst.size(); i++){
        delete stor_sldr_lst.at(i);
    }
    stor_sldr_lst.clear();
}

void settingsDialog::loadFromTextFile()
{
    // camera list
    //    //qDebug() << "Camera list" << endl;

    cam_info_list = new QVector<camera_list_helper>();

    QFile input_file("./.cfg/source8_1080p_dec_infer-resnet_tracker_tiled_display_fp16_nano_one.txt");

    if(input_file.open(QIODevice::ReadOnly)){

        QTextStream in(&input_file);

        int source_number = 0;
        QString source = "[source"+QString::number(source_number)+"]";

        bool check = false;
        int line_count = 0;

        QString info[6];
        int info_index = 0;

        while(!in.atEnd()){

            QString line = in.readLine();

            //            if(line.at(0) == '#'){
            //                continue;
            //            }

            if(line == source){
                last_source = source;

                //                //qDebug()<<endl << line;
                check = true;
                ++source_number;
                source = "[source"+QString::number(source_number)+"]";
                //                last_source = source;
            }

            if(check == true && line_count <= 6){
                //                //qDebug()<< line << " " << info_index++;

                if(line.at(0) == "#"){
                    continue;
                }else {
                    //                    //qDebug()<< line;
                    ++line_count;
                    info[info_index++] = line;
                }

            }

            if(line_count == 6){
                line_count = 0;
                check = false;
                info_index = 0;

                camera_list_helper *camera_info = new camera_list_helper(info[0], info[1], info[2], info[3], info[4], info[5]);

                cam_info_list->push_back(*camera_info);

                delete camera_info;

            }

        }

        input_file.close();

    }
    this->loadIntoWidget();

}
void settingsDialog::editSourceNumber(){
    QFile input_file("./.cfg/source8_1080p_dec_infer-resnet_tracker_tiled_display_fp16_nano_one.txt");
    if (!input_file.open(QFile::ReadOnly)) {
        //qDebug() << "Error opening for read: " << input_file.errorString();
        return;
    }
    QTextStream in(&input_file);

    QStringList str;
    int i = 0;
    while(!in.atEnd()){
        QString line = in.readLine();
        //        QString str = "[source"+QString::number(i)+"]";
        if("[source" == line.mid(0, 7)){
            if(line.size() < 10){
                int ind = line.mid(7, 1).toInt();
                if(ind != i){
                    str.append("[source"+QString::number(i)+"]");
                }else{
                    str.append("[source"+QString::number(ind)+"]");
                }
                ++i;
            }else if (line.size() >= 10 && line.size() < 100){
                int ind = line.mid(7, 2).toInt();
                if(ind != i){
                    str.append("[source"+QString::number(i)+"]");
                }else{
                    str.append("[source"+QString::number(ind)+"]");
                }
                ++i;
            }
        }else{
            str.append(line);
        }

    }
    //    //qDebug() <<"Sigmind -> "<< str;
    input_file.close();

    if (!input_file.open(QFile::WriteOnly)) {
        //qDebug() << "Error opening for write: " << input_file.errorString();
        return;
    }
    QTextStream outStream(&input_file);
    for(int i = 0; i < str.size(); i++){
        outStream << str[i]<<"\n";
    }
    input_file.close();
    str.clear();
}
void settingsDialog::loadIntoWidget()
{
    ui->tableWidget_cam_list->setRowCount(0);
    ui->tableWidget_cam_list->setColumnCount(2);
    //    ui->tableWidget_cam_list->setColumnCount(5);
    QStringList colmname;
    //colmname << "Source Index" << "RTSP link" << "Enable" << "Type" << "GPU Id";
    colmname << "Source Index" << "RTSP link";
    ui->tableWidget_cam_list->setHorizontalHeaderLabels(colmname);

    ui->tableWidget_cam_list->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidget_cam_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_cam_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_cam_list->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget_cam_list->setAutoScroll(true);

    for(int i = 0; i < cam_info_list->size(); i++){
        int k = ui->tableWidget_cam_list->rowCount();
        camera_list_helper ca = cam_info_list->at(i);
        ui->tableWidget_cam_list->insertRow(k);
        //        //qDebug() << ca.getSourceName();
        ui->tableWidget_cam_list->setItem(k, 0, new QTableWidgetItem(ca.getSourceName()));
        ui->tableWidget_cam_list->setItem(k, 1, new QTableWidgetItem(ca.getUri()));/*
        ui->tableWidget_cam_list->setItem(k, 2, new QTableWidgetItem(ca.getEnable()));
        ui->tableWidget_cam_list->setItem(k, 3, new QTableWidgetItem(ca.getType()));
        ui->tableWidget_cam_list->setItem(k, 4, new QTableWidgetItem(ca.getGpuId()));*/
    }
    ui->tableWidget_cam_list->resizeColumnsToContents();
    ui->tableWidget_cam_list->verticalHeader()->hide();
    //    box_layout_cam_list = new QVBoxLayout(this);
    //    for(int i = 0; i < cam_info_list->size(); i++){

    //        infor = new cameraListWidget(this, cam_info_list->at(i));
    //        connect(infor, SIGNAL(emitClickedOnCameraInfo()), this, SLOT(getDataAfterLefClicked()));

    //        box_layout_cam_list->insertWidget(i, infor);
    //    }
    //    ui->scrollAreaWidgetContents_cam_list->setLayout(box_layout_cam_list);
}

void settingsDialog::removeEmail(int id){
    //emailWidgets.at(id)->hide();
    //emailWidgets.removeAt(id);
    ////qDebug() << id;
    emailList.replace(id, "");
}

void settingsDialog::textChange(int id, QString text)
{
    emailList.replace(id, text);
}

void settingsDialog::getDataAfterLefClicked()
{
    //qDebug() << "Yes!! Done" << endl;
}

void settingsDialog::delete_lpr_from_db_and_ui(int lpr_id)
{
    //qDebug()<<"test lpr delet"<<lpr_id;
    QSqlQuery qlpr;
    qlpr.prepare("delete from given_lpr where ID=?;");
    qlpr.addBindValue(lpr_id);

    if(qlpr.exec()){
        //qDebug()<<"qlpr exec okk";
        loadDataFromTableForLPR();
    }

}




void settingsDialog::on_okBut_pressed()
{
    //apply all changes
    applyChanges();
}

void settingsDialog::on_okBut_released()
{

    this->close();
    //    this->deleteLater();
    //close window
}

void settingsDialog::on_applyBut_pressed()
{
    //apply all changes
    applyChanges();
}

void settingsDialog::on_cancelBut_clicked()
{
    //closeWindow
}

void settingsDialog::updateConfigDivisorValueWhichTakenFromSlider()
{
    qDebug()<<"updateConfigDivisorValueWhichTakenFromSlider call";

    QFile input_file("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");

    input_file.open(QIODevice::WriteOnly | QIODevice::ReadOnly);
    QTextStream in(&input_file);

    QStringList lst,lst2;

    while(!in.atEnd()){
        QString line = in.readLine();
        lst+=line;//load config file here
    }

    qDebug()<<"list size is >>> "<<lst.size();
    //divisor=4
    QString dbsr = "divisor=";
    QString fstpart = "[source", trdpart = "]";
    QString fsten = "enable=";

    QString cap_src;
    bool ck=false, flg=false;
    int index=0;

    for(int l=0; l<lst.size(); l++){

        if(fstpart + lst.at(l).mid(7, 1) + trdpart == lst.at(l) || fstpart + lst.at(l).mid(7, 2) + trdpart == lst.at(l) || fstpart + lst.at(l).mid(7, 3) + trdpart == lst.at(l)){// compare source no (0 to 999)
            cap_src = lst.at(l);
            qDebug()<<"match src :"<<cap_src;
            ck=true;
            flg = true;
            lst2+=lst.at(l);
            continue;
        }else if(ck && flg){
            flg = false;

            lst2+=lst.at(l);
            qDebug()<<"enable str : "<<lst.at(l);
            if(fsten+lst.at(l).mid(7, 1) == lst.at(l) && lst.at(l).mid(7, 1) == "1"){// check enable 1 or 0 here
                ck=true;
                qDebug()<<"match enable : "<<lst.at(l);

            }else{
                ck=false;
                qDebug()<<"match disable : "<<lst.at(l);
            }

        }else if("divisor=" == lst.at(l).mid(0, 8) && ck == true){
            qDebug()<<"dibisor :"<<lst.at(l);
            //                store_source_id_list.size();
            //                store_slider_pair_value[j].first;

            //            QString tm;
            //            if(cap_src.size() == 9){
            //                tm = cap_src.mid(7, 1);
            //            }else if(cap_src.size() == 10){
            //                tm = cap_src.mid(7, 2);
            //            }else if(cap_src.size() == 11){
            //                tm = cap_src.mid(7, 3);
            //            }

            //            int str_to_int = tm.toInt();// take source Id here
            //            qDebug()<<"str_to_int : "<<str_to_int;

            int update_sl_val = store_slider_pair_value[index].second;//take runtime slider value
            index++;

            QString tm2 = "divisor="+ QString::number(update_sl_val);
            qDebug()<<"update_sl_val: "<<update_sl_val<<" tm2: "<<tm2;
            lst2 += tm2;

            cap_src = "";
            ck = false;

        }else{
            lst2+=lst.at(l);
        }

    }

    input_file.resize(0);// clear file data hare
    qDebug()<<"lst2 sz : "<<lst2.size();

    for(int ii = 0;ii<lst2.size();ii++){// file write again
        in<<lst2.at(ii)<<"\n";//write into file
    }

    in.flush();
    input_file.close();

    lst.clear();
    lst2.clear();

    store_slider_pair_value.clear();
    store_source_id_list.clear();
    store_divisor_value_list.clear();

    //    for(int i=0;i<stor_sldr_lst.size(); i++){// slider ui delete here
    //        delete stor_sldr_lst.at(i);
    //    }
    //    stor_sldr_lst.clear();

}

void settingsDialog::updateConfigFileForVideoRecord()
{


    qDebug()<<" updateConfigFileForVideoRecord call";
    // for smart record type 4=RTSP thake lagbe must

    if(ui->on_radioButton->isChecked()){
        smart_rec_on_val = true;
    }else if(ui->off_radioButton->isChecked()){
        smart_rec_on_val = false;
    }

    if(smart_rec_on_val){
        qDebug()<<" smart record on";
        //        ui->source_index_lineEdit->setFocusPolicy(Qt::NoFocus);
        //        ui->source_index_lineEdit->setFocus();

        if(ui->mp4_radioButton->isChecked()){
            container_value = 0;
        }else if(ui->mkv_radioButton->isChecked()){
            container_value = 1;
        }

        QString video_record_path_from_ui = ui->videoRecordDirPathlineEdit->text();
        QString day_counter_for_video_record_from_ui = ui->keep_record_duration_day_counter_lineEdit->text();

        QString source_index_from_ui = ui->source_index_lineEdit->text();
        //source_index_from_ui = "[source" + source_index_from_ui + "]";

        QString container_value_from_ui = QString::number(container_value);


        QString video_record_cache_from_ui = ui->video_record_cache_lineEdit->text();
        QString record_default_duration_from_ui = ui->record_default_duration_lineEdit->text();
        QString smart_record_duration_from_ui = ui->smart_record_duration_lineEdit->text();
        QString record_start_time_from_ui = ui->record_start_time_lineEdit->text();
        QString record_interval_from_ui = ui->record_interval_lineEdit->text();

        if(day_counter_for_video_record_from_ui.QString::isEmpty() == false && video_record_path_from_ui.QString::isEmpty() == false &&
                container_value_from_ui.QString::isEmpty() == false && video_record_cache_from_ui.QString::isEmpty() == false && record_default_duration_from_ui.QString::isEmpty() == false
                && smart_record_duration_from_ui.QString::isEmpty() == false && record_start_time_from_ui.QString::isEmpty() == false
                && record_interval_from_ui.QString::isEmpty() == false){

            qDebug()<<"condition true";
            QFile input_file("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");

            //            input_file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::ReadOnly);
            input_file.open(QIODevice::WriteOnly | QIODevice::ReadOnly);
            QTextStream in(&input_file);

            //QTextStream outStream(&input_file);
            int days = day_counter_for_video_record_from_ui.toInt();
            emit smartRecordDayCount(days, video_record_path_from_ui);
            //qDebug()<<"in "<<in;
            QStringList lst,lst2;

            while(!in.atEnd()){
                QString line_ = in.readLine();
                //qDebug()<<"inside while, each line :"<<line_;
                lst+=line_;

            }

            qDebug()<<"list size is >>> "<<lst.size();
            int ck=0;
            bool flg=false, increamentTrack=false;

            source_index_from_ui = "[source" + source_index_from_ui + "]";

            for(int k = 0;k<lst.size(); k++){
                qDebug()<<"k: "<<k<<" >> "<<lst.at(k);
                if(source_index_from_ui == lst.at(k)){
                    qDebug()<<"match: "<<lst.at(k);
                    lst2+=lst.at(k);
                    ck++;//write into specific line
                    increamentTrack = true;

                }
                else if(ck > 7 && flg == false){//write into specific line

                    lst2+="# smart record specific fields, valid only for source type=4";
                    lst2+="# 0 = disable, 1 = through cloud events, 2 = through cloud + local events";
                    lst2+="smart-record=4";
                    lst2+= "# 0 = mp4, 1 = mkv";
                    QString tm = "smart-rec-container="+container_value_from_ui;

                    lst2+=tm;
                    lst2+= "#smart-rec-file-prefix=watchcam";

                    tm = "smart-rec-dir-path=" + video_record_path_from_ui;
                    lst2+=tm;

                    lst2+="#video cache size in seconds";
                    tm="smart-rec-video-cache="+video_record_cache_from_ui;
                    lst2+=tm;

                    lst2+="#default duration of recording in seconds.";
                    tm = "smart-rec-default-duration=" + record_default_duration_from_ui;
                    lst2+= tm;

                    lst2+="#duration of recording in seconds.";
                    lst2+="#this will override default value.";
                    tm = "smart-rec-duration=" + smart_record_duration_from_ui;
                    lst2+= tm;

                    lst2+="# seconds before the current time to start recording.";
                    tm="smart-rec-start-time=" + record_start_time_from_ui;
                    lst2+= tm;

                    lst2+="# value in seconds to dump video stream.";
                    tm = "smart-rec-interval="+ record_interval_from_ui;
                    lst2+=tm;

                    lst2+=lst.at(k);

                    flg = true;// only one time dukbe ey condition a
                    ck++;

                }
                else{
                    lst2+=lst.at(k);
                    if(increamentTrack){
                        ck++;
                    }
                }

            }
            qDebug()<<"lst2 size : "<<lst2.size();

            input_file.resize(0);// clear file data hare

            for(int ii = 0;ii<lst2.size();ii++){// file write again
                qDebug()<<"ii: "<<ii<<" >> "<<lst2.at(ii);

                in<<lst2.at(ii)<<"\n";//write into file
            }
            in.flush();
            input_file.close();

            lst.clear();
            lst2.clear();

            ui->source_index_lineEdit->setText("");
            ui->videoRecordDirPathlineEdit->setText("");
            ui->keep_record_duration_day_counter_lineEdit->setText("");
            ui->video_record_cache_lineEdit->setText("");
            ui->record_default_duration_lineEdit->setText("");
            ui->smart_record_duration_lineEdit->setText("");
            ui->record_start_time_lineEdit->setText("");
            ui->record_interval_lineEdit->setText("");
            ui->on_radioButton->setChecked(false);
            ui->off_radioButton->setChecked(true);

            QMessageBox msg_box;
            msg_box.setText("successfully included.");
            msg_box.exec();

        }else if(source_index_from_ui.isEmpty() == false){

            source_index_from_ui = "[source" + source_index_from_ui + "]";
            stopSmartRecForSpecificSourceIndex(source_index_from_ui, 4);// update file data and 4 means rtsp link

        }else{
            //qDebug()<<"please fillup all field";
            QMessageBox msg_box;
            msg_box.setText("please FillUp all field!");
            msg_box.exec();
        }
    }else if(smart_rec_on_val == false){
        QString source_index_from_ui = ui->source_index_lineEdit->text();
        if(source_index_from_ui.isEmpty() == false){
            source_index_from_ui = "[source" + source_index_from_ui + "]";

            stopSmartRecForSpecificSourceIndex(source_index_from_ui, 0);// update file data and 0 means smart-rec=0(off)

        }
    }


}

void settingsDialog::stopSmartRecForSpecificSourceIndex(QString capSource, int on_off_value)
{
    qDebug()<<"stopSmartRecForSpecificSourceIndex call "<<capSource;

    QFile input_file("./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt");

    input_file.open(QIODevice::WriteOnly | QIODevice::ReadOnly);
    QTextStream in(&input_file);

    QStringList lst;

    while(!in.atEnd()){
        QString line_ = in.readLine();
        //qDebug()<<"inside while, each line :"<<line_;
        lst+=line_;
        if(capSource == line_){
            qDebug()<<"line_ >>> "<<line_;

            while(!in.atEnd()){
                QString line = in.readLine();
                qDebug()<<"inside inner while "<<line;
                if("smart-record=4" == line){//for off
                    qDebug()<<"smart-record=4 &&& "<<line;
                    //                    line.replace("smart-record=0", "smart-record=4");
                    QString temp = "smart-record="+ QString::number(on_off_value);
                    line.replace(line, temp);
                    lst+=line;
                    //in<<line;
                    qDebug()<<"after replace "<<line;
                    break;
                }else if("smart-record=0" == line){
                    QString temp = "smart-record="+ QString::number(on_off_value);
                    line.replace(line, temp);
                    lst+=line;
                    //in<<line;
                    qDebug()<<"after replace "<<line;
                    break;
                }
                else{
                    lst+=line;
                }
            }

        }
    }

    input_file.resize(0);// clear file data hare

    for(int ii = 0;ii<lst.size();ii++){// file write again
        in<<lst.at(ii)<<"\n";//write into file
    }
    in.flush();
    input_file.close();

    lst.clear();

    ui->source_index_lineEdit->setText("");
    ui->videoRecordDirPathlineEdit->setText("");
    ui->keep_record_duration_day_counter_lineEdit->setText("");
    ui->video_record_cache_lineEdit->setText("");
    ui->record_default_duration_lineEdit->setText("");
    ui->smart_record_duration_lineEdit->setText("");
    ui->record_start_time_lineEdit->setText("");
    ui->record_interval_lineEdit->setText("");

    QMessageBox msg_box;
    msg_box.setText("successfully included.");
    msg_box.exec();
}

void settingsDialog::displayAllSourceIdFromSlider()
{
    qDebug()<<"displayAllSourceIdFromSlider call";

    double slider_val; int sourceNo;

    for(int k=0; k< stor_sldr_lst.size(); k++){
        QString s = stor_sldr_lst[k]->getSourceValue().mid(7, stor_sldr_lst[k]->getSourceValue().size());
        sourceNo = s.toInt();//retrieve only source number here
        slider_val =  stor_sldr_lst[k]->getSliderValue();
        slider_val = slider_val/10.0;
        QString str_to_float = QString::number(slider_val, 'f', 1);// take 1 digit after decimal point
        slider_val = str_to_float.toDouble();

        qDebug()<<"source no before :"<<sourceNo<<" slider value before : "<<slider_val;
        //        store_slider_pair_value.push_back(qMakePair(sourceNo, slider_val));
        store_slider_pair_value.push_back(std::make_pair(sourceNo, slider_val));//whole slider value 10 part
    }
    qDebug()<<"store_slider_pair_value size is : "<<store_slider_pair_value.size();

    emit setDivisortoMain(store_slider_pair_value);

    for(int j=0; j< store_slider_pair_value.size(); j++){
        qDebug()<<"source no :"<<store_slider_pair_value[j].first<<" slider value : "<<store_slider_pair_value[j].second;
    }

    updateConfigDivisorValueWhichTakenFromSlider();
}

void settingsDialog::applyChanges()
{
    updateConfigFileForVideoRecord();// for smart record settings tab
    displayAllSourceIdFromSlider();// line drawing into feed using settings menu slider tab

    ////qDebug() << obValues;
    obValues.replace(0, ui->faceCheck->isChecked());
    obValues.replace(1, ui->maskedFaceCheck->isChecked());
    obValues.replace(2, ui->personCheck->isChecked());
    obValues.replace(3, ui->baggageCheck->isChecked());
    obValues.replace(4, ui->cellPhoneCheck->isChecked());
    obValues.replace(5, ui->bicycleCHeck->isChecked());
    obValues.replace(6, ui->carCheck->isChecked());
    obValues.replace(7, ui->busCheck->isChecked());
    obValues.replace(8, ui->motorcycleCheck->isChecked());
    obValues.replace(9, ui->truckCheck->isChecked());
    //    obValues.replace(10, ui->licenseCheck->isChecked());
    obValues.replace(11, ui->knifeCheck->isChecked());

    myStyles::notificationFlag = ui->enableNotCheck->isChecked();
    myStyles::faceRecognitionFlag = ui->faceRecogCheck->isChecked();
    myStyles::faceFolderRelative = faceFolder;
    myStyles::blackFolderRelative = blackFolder;
    myStyles::faceSensitivitySlider = ui->faceRecogSenseBar->value();
    myStyles::objectSensitivitySlider = ui->objectSensitivitySlider->value();

    myStyles::faceSensitivityValue = (float)myStyles::faceSensitivitySlider;
    myStyles::faceSensitivityValue = myStyles::faceSensitivityValue/100;
    myStyles::faceSensitivityValue = (1.0 - myStyles::faceSensitivityValue);

    float recent_value = myStyles::faceSensitivityValue;
    ////qDebug()<<"recent "<<recent_value;

    if(_flag == true){
        _flag = false;
        previous_value = recent_value;
    }

    if(previous_value != recent_value && recent_value != 1){
        previous_value = recent_value;

        QString thres_path = "./files/";
        QString obliq = "/";
        QString s = "user_threshold.txt";
        QString date = QDate::currentDate().toString("dd.MM.yyyy");
        QString img_path = thres_path+date+obliq;

        QDir myDir;
        if(!myDir.exists(date)){
            myDir.mkpath(img_path);
            //qDebug()<<"after create path";
        }

        QString filename = img_path+s;
        //or default path
        //QString filename = "/home/sigmind/Pictures/WC-Tegra-DS/files/user_FR_threshold_data_save.txt";

        QFile file(filename);
        if(file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
            QTextStream stream(&file);
            QString stor = QString::number(previous_value);
            stream<<stor<<"\n";
            ////qDebug()<<"okay";
        }
        file.close();
    }

    float store_face_sen = myStyles::faceSensitivityValue;
    emit fr_thresholed_value_settingdialog(store_face_sen);

    //    emit lpr_api_select_value_settingdialog(api_check_value_lp);

    //    //qDebug() <<"objectSensitivityValue of settingsdialog.cpp in applychanges = " <<myStyles::objectSensitivityValue;

    ////qDebug() <<"faceSensitivityValue of settingsdialog.cpp in applychanges = " <<myStyles::faceSensitivityValue;


    ////qDebug() << obValues;
    myStyles::objectValues = obValues;
    myStyles::emailsTo.clear();

    foreach (QString em, emailList) {
        if(!em.isEmpty()) myStyles::emailsTo << em;
    }
    ////qDebug() << myStyles::objectValues;

    if(objectSensitivityChange) emit objectSensitivityChanged();

    /* define recent */
    //    //qDebug() << "FACE+ " << faceSensitivityChange;
    if(faceSensitivityChange) emit faceSensitivityChanged();


    mystyle.setSettingsValues();
}

void settingsDialog::on_addEmail_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Email address:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()){
        emailList << text;
        EmailBox *box = new EmailBox(emailCount, text, this);
        connect(box, SIGNAL(removeBox(int)), this, SLOT(removeEmail(int)));
        connect(box, SIGNAL(textChange(int,QString)), this, SLOT(textChange(int,QString)));
        ui->emailVerticalBox->addWidget(box);
        emailCount++;
    }
}

void settingsDialog::on_faceRecogBrowseBut_pressed()
{
    QFileDialog dialog(this);
    dialog.setDirectory(faceFolder);
    dialog.setFileMode(QFileDialog::Directory);
    QString dir;
    if (dialog.exec()){
        QStringList files = dialog.selectedFiles();
        dir = files.at(0);

    }

    if (!dir.isEmpty()) {
        QDir currentDir(QDir::currentPath());
        faceFolder= currentDir.relativeFilePath(dir);
        ui->faceRecogDirLine->setText(faceFolder);
    }
}

void settingsDialog::on_objectSensitivitySlider_valueChanged(int value)
{

    if(!objectSensitivityChange) objectSensitivityChange=true;
    ui->obDetText->setText(QString::number((float)value/100));

    QFile input_file("/home/sigmind/Music/deepstream_sdk_v4.0.2_jetson/samples/configs/deepstream-app/config_infer_primary.txt");
    if (!input_file.open(QFile::ReadOnly)) {
        ////qDebug() << "Error opening for read: " << input_file.errorString();
        return;
    }
    ////qDebug() << "++++++++++++++++++++++";
    QTextStream in(&input_file);
    QStringList str;

    while(!in.atEnd()){
        QString line = in.readLine();
        if(line.mid(0, 10) == "threshold="){
            //            //qDebug() << line.mid(0, 10);
            str.append(line.mid(0, 10)+QString::number((float)value/100));
        }else{
            str.append(line);
        }
    }
    input_file.close();

    if (!input_file.open(QFile::WriteOnly)) {
        ////qDebug() << "Error opening for write: " << input_file.errorString();
        return;
    }
    QTextStream outStream(&input_file);
    for(int i = 0; i < str.size(); i++){
        outStream << str[i]<<"\n";
    }
    input_file.close();
    str.clear();

}

void settingsDialog::on_faceRecogSenseBar_valueChanged(int value)
{
    if(!faceSensitivityChange) faceSensitivityChange=true;
    ui->faceDetText->setText(QString::number((float)value/100));
}

void settingsDialog::on_browseBlackList_clicked()
{
    QFileDialog dialog(this);
    dialog.setDirectory(blackFolder);
    dialog.setFileMode(QFileDialog::Directory);
    QString dir;
    if (dialog.exec()){
        QStringList files = dialog.selectedFiles();
        dir = files.at(0);

    }

    if (!dir.isEmpty()) {
        QDir currentDir(QDir::currentPath());
        blackFolder= currentDir.relativeFilePath(dir);
        ui->blackListDirLine->setText(blackFolder);
    }
}

void settingsDialog::on_settingsTab_tabBarClicked(int index)
{
    ////qDebug() << "Add Lpr clicked";
    loadDataFromTableForLPR();

}

void settingsDialog::on_pushButton_add_camera_clicked()
{
    /*User input*/
    QString cam_name = ui->lineEdit_cam_name->text();
    QString cam_pass = ui->lineEdit_cam_pass->text();
    QString cam_uri = ui->lineEdit_cam_uri->text();


    /*Write into file*/
    if(cam_name.QString::isEmpty() == false && cam_pass.QString::isEmpty() == false && cam_uri.QString::isEmpty() == false){

        /*Checked length for write source*/
        QString so_num;
        if(last_source.length() < 10){
            so_num = last_source.at(7);
        }else if(last_source.length() < 100) {
            so_num = QString(last_source.at(7)).append(last_source.at(8));
        }

        int so_num_ = so_num.toInt();
        ++so_num_;
        QString source = "[source"+QString::number(so_num_)+"]";
        //    //qDebug() << "So num " << so_num_;
        int en = 1;
        QString enable = "enable="+QString::number(en);
        int t = 3;
        QString type = "type="+QString::number(t);
        //QString ur = "file://../../streams/sample_1080p_h264.mp4";
        //QString uri = QString("uri="+).append(cam_uri);
        QString uri = "uri="+cam_uri.mid(0, 7)+cam_name+":"+cam_pass+"@"+cam_uri.mid(7, cam_uri.length());
        ////qDebug() << "Uri " << uri;
        int num_src = 1;
        QString num_sources = "num-sources="+QString::number(num_src);
        int gp_id = 0;
        QString gpu_id = "gpu-id="+QString::number(gp_id);



        QFile input_file("./.cfg/source8_1080p_dec_infer-resnet_tracker_tiled_display_fp16_nano_one.txt");

        input_file.open(QIODevice::Append | QIODevice::WriteOnly);

        if(input_file.isOpen()){

            QTextStream outStream(&input_file);
            outStream << "\n"<<source<< "\n"<< "#Name: "+cam_name<<"\n"<<"#Password: "+cam_pass<<"\n"<<enable<< "\n" << type<< "\n" <<uri<< "\n"<<num_sources << "\n" << gpu_id  <<"\n"<< "# (0): memtype_device   - Memory type Device\n# (1): memtype_pinned   - Memory type Host Pinned\n# (2): memtype_unified  - Memory type Unified\ncudadec-memtype=0" << "\n";
            outStream.flush();
            input_file.close();

            ////qDebug()<< "Size1" << cam_info_list->size() << endl;
            cam_info_list->clear();
            delete cam_info_list;
            //delete infor;
            //delete box_layout_cam_list;
            this->loadFromTextFile();
            //            this->loadIntoWidget();
            ////qDebug()<< "Size2" << cam_info_list->size() << endl;

            ui->lineEdit_cam_name->setText("");
            ui->lineEdit_cam_pass->setText("");
            //  ui->lineEdit_cam_uri->setText("");
        }
    }

}

void settingsDialog::on_pushButtonlogin_clicked()
{
    //    get_link = new get_rtsp();
    //    ////qDebug() << "\n**********************RTSP  send********************";

    //    char ipHostName[128] = { 0 };
    //    QString pass_pass = ui->lineEdit_cam_pass->text();

    //    std::string dev_pass = pass_pass.toStdString();
    //    QString IP_add = ui->lineEdit_address->text();
    //    std::string ip_addr =IP_add.toStdString();


    //    strcat(ipHostName, "http://");
    //    strcat(ipHostName, ip_addr.c_str());
    //    strcat(ipHostName, "/onvif/device_service");

    //    std::string rtsp_url = get_link->generate_rtsp(ipHostName,dev_pass.c_str());
    //    //std::string rtsp_url = get_link->generate_rtsp("http://192.168.0.210/onvif/device_service","00125680");
    //    QString retrieved = QString::fromStdString( rtsp_url );

    //    ////qDebug() << " SUCCESS !! Retrieved URL = " << retrieved;

    //    pass_pass = QString::fromStdString(rtsp_url);

    //    //ui->lineEdit_RTSP->setText(pass_pass);
    //    ui->lineEdit_cam_uri->setText(pass_pass);
}


void settingsDialog::on_checkBox_suspect_clicked()
{
    ////qDebug() << "Check box clicked check";
    if(ui->checkBox_suspect->checkState() == Qt::Checked){
        qDebug() << "Hello suspect ck";
        emit transferSuspectStateToMainWindow(true);
    }
    else if(ui->checkBox_suspect->checkState() == Qt::Unchecked){
        qDebug() << "Hello unchecked tested";
        emit transferSuspectStateToMainWindow(false);
    }
}

void settingsDialog::on_okBut_clicked()
{
    this->close();
}

void settingsDialog::on_tableWidget_cam_list_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QString src = index.sibling(row, 0).data().toString();
    QString rtsp = index.sibling(row, 1).data().toString();

    QMessageBox msgBox;
    msgBox.setText("Do you want to delete or update?\n"+rtsp);
    QAbstractButton* del = msgBox.addButton(tr("Delete!"), QMessageBox::YesRole);
    QAbstractButton* edit = msgBox.addButton(tr("Edit!"), QMessageBox::ApplyRole);
    //msgBox.addButton(tr("Nope"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==del) {
        QFile input_file("./.cfg/source8_1080p_dec_infer-resnet_tracker_tiled_display_fp16_nano_one.txt");
        if (!input_file.open(QFile::ReadOnly)) {
            ////qDebug() << "Error opening for read: " << input_file.errorString();
            return;
        }
        QTextStream in(&input_file);
        bool check = false;
        int line_count = 0;

        QStringList str;

        while(!in.atEnd()){
            QString line = in.readLine();
            //            //qDebug() << line;
            if(line == src){
                ////qDebug() << "yes equal";
                check=true;
            }
            if(check == true && line_count <= 12){

                ////qDebug() << line;
                if(line_count == 12){
                    line_count = 0;
                    check = false;
                }
                ++line_count;
                continue;
                //text.replace(QString(line), QString("abc"));
            }else{
                str.append(line);
            }

        }
        input_file.close();


        if (!input_file.open(QFile::WriteOnly)){
            //qDebug() << "Error opening for write: " << input_file.errorString();
            return;
        }
        QTextStream outStream(&input_file);
        for(int i = 0; i < str.size(); i++){
            outStream << str[i]<<"\n";
        }
        input_file.close();
        str.clear();

        cam_info_list->clear();

        delete cam_info_list;
        //delete box_layout_cam_list;
        editSourceNumber();
        loadFromTextFile();
    }else if(msgBox.clickedButton()==edit){
        msgBox.close();
        //        ui->tableWidget_cam_list->editItem(ui->tableWidget_cam_list->item(row, 1));
        bool ok;
        QString text = QInputDialog::getText(0, "Input dialog",
                                             "RTSP URL: ", QLineEdit::Normal,
                                             ui->tableWidget_cam_list->item(row, 1)->text(), &ok);

        if (ok && !text.isEmpty()) {
            QString source = ui->tableWidget_cam_list->item(row, 0)->text();
            //QString rtsp = ui->tableWidget_cam_list->item(row, 1)->text();

            updateRtsp(source, text);
            QMessageBox::information (0, "Update Info!",
                                      "Successfull");
        }
    }
}

void settingsDialog::on_objectSensitivitySlider_actionTriggered(int action)
{
    ////qDebug() << "Action = " <<action;
}

void settingsDialog::on_pushButton_addLPR_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Enter LPR:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()){
        QSqlQuery creQsql, insQSql;
        creQsql.exec("CREATE TABLE given_lpr ( "
                     "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "number_plate TEXT) "
                     ";");
        insQSql.prepare("insert into given_lpr "
                        "( number_plate ) "
                        "values (?);");
        insQSql.addBindValue(text);
        //        insQSql.exec();
        if(insQSql.exec()){
            loadDataFromTableForLPR();
        }
    }
}

void settingsDialog::on_tableWidget_addLPR_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    int lpr_indx = index.sibling(row, 0).data().toInt();
    QString lpr = index.sibling(row, 1).data().toString();

    QMessageBox msgBox;
    msgBox.setText("Do you want to delete or update?\n"+lpr);
    QAbstractButton* del_lpr = msgBox.addButton(tr("Delete!"), QMessageBox::YesRole);
    QAbstractButton* edit_lpr = msgBox.addButton(tr("Edit!"), QMessageBox::ApplyRole);
    //msgBox.addButton(tr("Nope"), QMessageBox::NoRole);

    msgBox.exec();
    if(msgBox.clickedButton() == del_lpr){
        ////qDebug()<<"delete lpr code apply here";
        delete_lpr_from_db_and_ui(lpr_indx);

    }else if(msgBox.clickedButton() == edit_lpr){
        ////qDebug()<<"edit lpr code apply here";
    }
}

void settingsDialog::on_face_check_clicked()
{
    if(ui->face_check->checkState() == Qt::Checked){
        //        //qDebug() << "Hello suspect ck";
        emit checkFaceDetection(true);
    }
    else if(ui->face_check->checkState() == Qt::Unchecked){
        //        //qDebug() << "Hello unchecked tested";
        emit checkFaceDetection(false);
    }
}

void settingsDialog::on_lpr_check_clicked()
{
    if(ui->lpr_check->checkState() == Qt::Checked){
        //        //qDebug() << "Hello suspect ck";
        emit checkLprDetection(true);
    }
    else if(ui->lpr_check->checkState() == Qt::Unchecked){
        //        //qDebug() << "Hello unchecked tested";
        emit checkLprDetection(false);
    }
}
void settingsDialog::imageLoadForVideoAnalytics(){
    if(list_of_path.size() != 0){
        list_of_path.clear();
    }
    if(connectionDB()){
        QSqlQuery que;
        if(que.exec("select savePath from FeedAddFace;")){
            while(que.next()){
                list_of_path.push_back(que.value(0).toString());


                //                QPixmap pic;
                //                pic.load(que.value(0).toString());

                //                //newFace->setObject(pic, "name", 1);

                //                if (!pic.isNull()){

                //                    VD_Face *newFace = new VD_Face(this, pic);
                //                    //                    newFace->show();
                //                    ////qDebug()<<"pic is not null"<<" faceList.size() >>"<<faceList.size();
                //                    if (faceList.size() < 25){// Checked size of list is 100 or not!
                //                        //                        //qDebug()<<"facelist less than 25";
                //                        faceList.push_back(newFace); // Added face in Lists
                //                        grid_show_all_faces->addWidget(newFace, row_index, column_index); // load data into grid layout.

                //                    }else {
                //                        //                        //qDebug()<<"face list greater than 25";
                //                        delete faceList.at(0); // deallocation done
                //                        faceList.removeFirst(); // remove first element
                //                        faceList.push_back(newFace); // face added into list

                //                        QListIterator<VD_Face*> iter(faceList); // iterator
                //                        iter.toFront(); // iterator start from first


                //                        // set face into grid layout which are new come
                //                        for (int i = 0; i < 5; ++i){
                //                            for (int j = 0; j < 5; ++j){
                //                                // for 100 cell
                //                                grid_show_all_faces->addWidget(iter.next(), i, j); // load data into grid layout.

                //                            }

                //                        }

                //                    }
                //                    //  Grid index customize
                //                    if(column_index == 5){
                //                        //                        //qDebug()<<"colum index equal 10";
                //                        row_index++;
                //                        column_index = -1;
                //                    }

                //                    if(row_index == 5){
                //                        //                        //qDebug()<<"row equal 10";
                //                        row_index = 0;
                //                    }
                //                    column_index++;
                //                }
                //                ui->scrollAreaWidgetContents_results->verticalScrollBar()->setSliderPosition(ui->scrollAreaWidgetContents_results->verticalScrollBar()->maximum());

                //                ui->scrollArea_for_image_vda->verticalScrollBar()->setSliderPosition(ui->scrollArea_for_image_vda->verticalScrollBar()->maximum());
            }
            readDataUsingMouseWheel();
        }
        //        ui->scrollArea_for_image_vda->setLayout(grid_show_all_faces);


    }
}
void settingsDialog::imageSetToWindow(QString st){
    QPixmap pic;
    pic.load(st);


    //newFace->setObject(pic, "name", 1);

    if (!pic.isNull()){
        VD_Face *newFace = new VD_Face(this, pic);
        //                    newFace->show();
        ////qDebug()<<"pic is not null"<<" faceList.size() >>"<<faceList.size();
        if (faceList.size() < 25){// Checked size of list is 100 or not!
            //qDebug()<<"f/acelist less than 25";
            faceList.push_back(newFace); // Added face in Lists
            grid_show_all_faces->addWidget(newFace, row_index, column_index); // load data into grid layout.

        }else {
            //                        //qDebug()<<"face list greater than 25";
            delete faceList.at(0); // deallocation done
            faceList.removeFirst(); // remove first element
            faceList.push_back(newFace); // face added into list

            QListIterator<VD_Face*> iter(faceList); // iterator
            iter.toFront(); // iterator start from first


            // set face into grid layout which are new come
            for (int i = 0; i < 5; ++i){
                for (int j = 0; j < 5; ++j){
                    // for 100 cell
                    grid_show_all_faces->addWidget(iter.next(), i, j); // load data into grid layout.

                }

            }

        }
        //  Grid index customize
        if(column_index == 5){
            //            //qDebug()<<"colum index equal 10";
            row_index++;
            column_index = -1;
        }

        if(row_index == 5){
            //            //qDebug()<<"row equal 10";
            row_index = 0;
        }
        column_index++;
    }
}
void settingsDialog::consLike(){
    editSourceNumber();
    loadFromTextFile();
}
void settingsDialog::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    int x = ui->scrollArea_for_image_vda->x();
    int y = ui->scrollArea_for_image_vda->y();
    int w = ui->scrollArea_for_image_vda->width();
    int h = ui->scrollArea_for_image_vda->height()+y;
    //qDebug() << "sdfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa " << x << " " << y << " " << w << " " << h << " " << event->x() << " " << event->y();
    //    if(event->x()>=x && event->x() <= w && event->y()>=y && event->y() <= h){
    //        if (event->orientation() == Qt::Vertical) {
    //            //qDebug() << "numSteps = " << numSteps;
    //            readDataUsingMouseWheel(numSteps);
    //        }
    //    }else{
    //        //qDebug() << "sddddddddddddddddfdf outside";
    //    }
    if (event->orientation() == Qt::Vertical) {
        ////qDebug() << "numSteps = " << numSteps;
        readDataUsingMouseWheel(numSteps);
    }
    event->accept();
}

void settingsDialog::closeEvent(QCloseEvent *event)
{
    ////qDebug() << "settingsDialog::~in close event()";
    list_of_path.clear();
    for(int i = 0; i < faceList.size(); i++){
        delete faceList.at(0); // deallocation done
        faceList.removeFirst();
    }
}
void settingsDialog::readDataUsingMouseWheel(int index){
    if(index == 1){
        --track_index.first;
        --track_index.second;
        if(track_index.first >= 0 && track_index.second <= list_of_path.size()){
            for(int i = track_index.first; i<track_index.second; i++){
                imageSetToWindow(list_of_path.at(i));
            }
        }
    }else if(index == -1){
        ++track_index.first;
        ++track_index.second;
        if(track_index.first >= 0 && track_index.second <= list_of_path.size()){
            for(int i = track_index.first; i<track_index.second; i++){
                imageSetToWindow(list_of_path.at(i));
            }
        }
    }
}
void settingsDialog::readDataUsingMouseWheel(){
    track_index.first = 0;
    track_index.second = 24;
    if(list_of_path.size()>0){
        for(int i = 0; i < 25; i++){
            imageSetToWindow(list_of_path.at(i));
        }
    }
}

void settingsDialog::maleFace(int fromAge, int toAge)
{
    if(list_of_path.size() != 0){
        list_of_path.clear();
    }
    if(connectionDB()){
        QSqlQuery que;
        QString qu_str = "select savePath from FeedAddFace where Gender='Male' and (age between ? and ?);";
        que.prepare(qu_str);
        que.addBindValue(fromAge);
        que.addBindValue(toAge);
        if(que.exec()){
            while(que.next()){
                //                imageSetToWindow(que.value(0).toString());
                list_of_path.push_back(que.value(0).toString());
            }
        }
        readDataUsingMouseWheel();
    }
}

void settingsDialog::malePerson(int fromAge, int toAge)
{
    if(list_of_path.size() != 0){
        list_of_path.clear();
    }
    if(connectionDB()){
        QSqlQuery que;
        QString qu_str = "select savePathPerson from FeedAddFace where Gender='Male' and (age between ? and ?);";
        que.prepare(qu_str);
        que.addBindValue(fromAge);
        que.addBindValue(toAge);
        if(que.exec()){
            while(que.next()){
                //                imageSetToWindow(que.value(0).toString());
                QString str = que.value(0).toString();
                if(!str.isNull()){
                    //                    //qDebug() << "strIsNull";
                    list_of_path.push_back(str);
                }

            }
        }
        readDataUsingMouseWheel();
    }
}

void settingsDialog::femaleFace(int fromAge, int toAge)
{
    if(list_of_path.size() != 0){
        list_of_path.clear();
    }
    if(connectionDB()){
        QSqlQuery que;
        QString qu_str = "select savePath from FeedAddFace where Gender='Female' and (age between ? and ?);";
        que.prepare(qu_str);
        que.addBindValue(fromAge);
        que.addBindValue(toAge);
        if(que.exec()){
            while(que.next()){
                QString str = que.value(0).toString();
                if(!str.isNull()){
                    //                    //qDebug() << "strIsNull";
                    list_of_path.push_back(str);
                }
                //                imageSetToWindow(que.value(0).toString());
            }
        }
        readDataUsingMouseWheel();
    }
}

void settingsDialog::femalePerson(int fromAge, int toAge)
{
    if(list_of_path.size() != 0){
        list_of_path.clear();
    }
    if(connectionDB()){
        QSqlQuery que;
        QString qu_str = "select savePathPerson from FeedAddFace where Gender='Female' and (age between ? and ?);";
        que.prepare(qu_str);
        que.addBindValue(fromAge);
        que.addBindValue(toAge);
        if(que.exec()){
            while(que.next()){
                //                imageSetToWindow(que.value(0).toString());
                QString str = que.value(0).toString();
                if(!str.isNull()){
                    //                    //qDebug() << "strIsNull";
                    list_of_path.push_back(str);
                }
            }
        }
        readDataUsingMouseWheel();
    }
}

void settingsDialog::faceMaleFemale(int fromAge, int toAge)
{
    if(list_of_path.size() != 0){
        list_of_path.clear();
    }
    if(connectionDB()){
        QSqlQuery que;
        QString qu_str = "select savePath from FeedAddFace where Gender='Female' or Gender='Male' and (age between ? and ?);";
        que.prepare(qu_str);
        que.addBindValue(fromAge);
        que.addBindValue(toAge);
        if(que.exec()){
            while(que.next()){
                //                imageSetToWindow(que.value(0).toString());
                QString str = que.value(0).toString();
                if(!str.isNull()){
                    //                    //qDebug() << "strIsNull";
                    list_of_path.push_back(str);
                }
            }
        }
        readDataUsingMouseWheel();
    }
}

void settingsDialog::personMaleFemale(int fromAge, int toAge)
{
    if(list_of_path.size() != 0){
        list_of_path.clear();
    }
    if(connectionDB()){
        QSqlQuery que;
        QString qu_str = "select savePathPerson from FeedAddFace where Gender='Female' or Gender='Male' and (age between ? and ?);";
        que.prepare(qu_str);
        que.addBindValue(fromAge);
        que.addBindValue(toAge);
        if(que.exec()){
            while(que.next()){
                //                imageSetToWindow(que.value(0).toString());
                QString str = que.value(0).toString();
                if(!str.isNull()){
                    //                    //qDebug() << "strIsNull";
                    list_of_path.push_back(str);
                }
            }
        }
        readDataUsingMouseWheel();
    }
}

void settingsDialog::on_pushButton_search_for_sub_video_ana_clicked()
{
    if(ui->checkBox_face_check->isChecked() == true
            && ui->checkBox_person->isChecked() == true
            && ui->checkBox_masked_face->isChecked() == true
            && ui->checkBox_male->isChecked() == true
            && ui->checkBox_female->isChecked() == true){
        imageLoadForVideoAnalytics();
    }
    else if(ui->checkBox_male->isChecked() == true
            && ui->checkBox_face_check->isChecked() == true){
        //qDebug() << "maleFaceClicked";
        maleFace(ui->lineEdit_age_from->text().toInt(), ui->lineEdit_25_age_to->text().toInt());

    }else if(ui->checkBox_male->isChecked() == true
             && ui->checkBox_person->isChecked() == true){
        malePerson(ui->lineEdit_age_from->text().toInt(), ui->lineEdit_25_age_to->text().toInt());

    }
    else if(ui->checkBox_female->isChecked() == true
            && ui->checkBox_face_check->isChecked() == true){
        femaleFace(ui->lineEdit_age_from->text().toInt(), ui->lineEdit_25_age_to->text().toInt());

    }else if(ui->checkBox_female->isChecked() == true
             && ui->checkBox_person->isChecked() == true){
        femalePerson(ui->lineEdit_age_from->text().toInt(), ui->lineEdit_25_age_to->text().toInt());

    }
    else if(ui->checkBox_face_check->isChecked() == true
            && ui->checkBox_male->isChecked() == true &&
            ui->checkBox_female->isChecked() == true){
        faceMaleFemale(ui->lineEdit_age_from->text().toInt(), ui->lineEdit_25_age_to->text().toInt());

    }else if(ui->checkBox_person->isChecked() == true
             && ui->checkBox_male->isChecked() == true &&
             ui->checkBox_female->isChecked() == true){
        personMaleFemale(ui->lineEdit_age_from->text().toInt(), ui->lineEdit_25_age_to->text().toInt());

    }
}

void settingsDialog::on_pushButton_search_vehicles_clicked()
{
    QString vehi = ui->comboBox_vehicles->itemData(ui->comboBox_vehicles->currentIndex()).toString();
    //    if(QString::compare(vehi, "select")){

    //    }
    QString vehi_cagt = ui->combobox_category->itemData(ui->combobox_category->currentIndex()).toString();
    //    if(QString::compare(vehi_cagt, "select")){

    //    }
    QString vehi_color = ui->combobox_pick_color->itemData(ui->combobox_pick_color->currentIndex()).toString();
    QString lp_text = ui->lineEdit_searchBox->text();
    if(QString::compare(vehi, "select")!=0&&QString::compare(vehi_cagt, "select")!=0&&QString::compare(vehi_color, "select")!=0&&!lp_text.isEmpty()){

        if(list_of_path.size() != 0){
            list_of_path.clear();
        }
        if(connectionDB()){
            QSqlQuery que;
            QString qu_str = "select childImgPath from detected_LPR where color = ? and number_plate = ?;";
            que.prepare(qu_str);
            que.addBindValue(vehi_color);
            que.addBindValue(lp_text);
            if(que.exec()){
                while(que.next()){
                    //                imageSetToWindow(que.value(0).toString());
                    QString str = que.value(0).toString();
                    if(!str.isNull()){
                        //                    //qDebug() << "strIsNull";
                        list_of_path.push_back(str);
                    }
                }
            }
            readDataUsingMouseWheel();
        }

    }else if(QString::compare(vehi, "select")!=0&&QString::compare(vehi_cagt, "select")!=0&&QString::compare(vehi_color, "select")!=0){
        if(list_of_path.size() != 0){
            list_of_path.clear();
        }
        if(connectionDB()){
            QSqlQuery que;
            QString qu_str = "select childImgPath from detected_LPR where color = ?;";
            que.prepare(qu_str);
            que.addBindValue(vehi_color);
            if(que.exec()){
                while(que.next()){
                    //                imageSetToWindow(que.value(0).toString());
                    QString str = que.value(0).toString();
                    if(!str.isNull()){
                        //                    //qDebug() << "strIsNull";
                        list_of_path.push_back(str);
                    }
                }
            }
            readDataUsingMouseWheel();
        }
    }





}

void settingsDialog::on_videoRecordBrowsepushButton_pressed()
{
    qDebug()<<"videoRecordBrowsepushButton call";

    //    QFileDialog dialog(this);
    //    dialog.setDirectory(videoFolder);
    //    dialog.setFileMode(QFileDialog::Directory);
    //    QString dir;
    //    if (dialog.exec()){
    //        QStringList files = dialog.selectedFiles();
    //        dir = files.at(0);

    //    }

    //    if (!dir.isEmpty()) {
    //        QDir currentDir(QDir::currentPath());
    //        videoFolder= currentDir.relativeFilePath(dir);
    //        qDebug()<<"video folder selected path: "<<videoFolder;
    //        ui->videoRecordDirPathlineEdit->setText(videoFolder);
    //    }

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",QFileDialog::ShowDirsOnly   | QFileDialog::DontResolveSymlinks);
    qDebug()<<"video folder selected path: "<<dir;
    ui->videoRecordDirPathlineEdit->setText(dir);
}

void settingsDialog::on_radioButton_google_api_clicked()
{
    qDebug()<<"on_radioButton_google_api_clicked call";

    if(ui->radioButton_google_api->isChecked()){
        qDebug()<<"ui->radioButton_google_api->isChecked";
        api_check_value_lp = "google_api";
        emit lpr_api_select_value_settingdialog(api_check_value_lp);

    }
}

void settingsDialog::on_radioButton_tess_api_clicked()
{
    qDebug()<<"on_radioButton_tess_api_clicked call";

    if(ui->radioButton_tess_api->isChecked()){
        qDebug()<<"ui->radioButton_tess_api->isChecked";
        api_check_value_lp = "tess_api";
        emit lpr_api_select_value_settingdialog(api_check_value_lp);
    }
}
