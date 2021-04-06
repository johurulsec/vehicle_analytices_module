#include "config_database.h"
#include "ui_config_database.h"

config_database::config_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config_database)
{
    ////qDebug() << "constructor" << endl;
    //thread()->wait(100000);
    //    //qDebug() << "Config thread constructor = " << QObject::thread()->currentThreadId();

    ui->setupUi(this);






    ui->pushButton_delete->setEnabled(false);

    //    modal = new QSqlQueryModel();
    //    modal1 = new QSqlQueryModel();

    check_pic_is_loaded_from_uniqe_faces = false;
    capture_flag = false;

    _warking = false;
    _abort = false;

    ui->pushButton_add_information->setEnabled(false);

    image_show_d = new ImageShowDialog(this);
    tableShow();


}
void config_database::tableShow(){
    ui->tableView_inserted_data_show->setColumnCount(7);
    QStringList colmname;
    //ID, name, position, address, phone, access_pass, image_path
    colmname << "ID" << "Name" << "Position" << "Address" << "Phone" << "Access Pass" << "Image Path";
    ui->tableView_inserted_data_show->setHorizontalHeaderLabels(colmname);

    ui->tableView_inserted_data_show->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView_inserted_data_show->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_inserted_data_show->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_inserted_data_show->setFocusPolicy(Qt::NoFocus);

    ui->tableView_inserted_data_show->setAutoScroll(true);
    ui->tableView_inserted_data_show->setRowCount(0);
    if(connectionDB()){
        QSqlQuery query;
        query.prepare("select ID, name, position, address, phone, access_pass, image_path from ADD_FACE;");

        if(query.exec()){
            ////qDebug() << "Yes data found" ;
            ////qDebug() << query.lastQuery();
            while(query.next()){

                int Id = query.value(0).toInt();
                ////qDebug() << "Yes data found" << Id << endl;
                QString name = query.value(1).toString();
                QString position = query.value(2).toString();
                QString address = query.value(3).toString();
                QString phone = query.value(4).toString();
                QString access_pass = query.value(5).toString();
                QString image_path = query.value(6).toString();

                int i = ui->tableView_inserted_data_show->rowCount();

                ui->tableView_inserted_data_show->insertRow(i);
                ui->tableView_inserted_data_show->setItem(i, 0, new QTableWidgetItem(QString::number(Id)));
                ui->tableView_inserted_data_show->setItem(i, 1, new QTableWidgetItem(name));
                ui->tableView_inserted_data_show->setItem(i, 2, new QTableWidgetItem(position));
                ui->tableView_inserted_data_show->setItem(i, 3, new QTableWidgetItem(address));
                ui->tableView_inserted_data_show->setItem(i, 4, new QTableWidgetItem(phone));
                ui->tableView_inserted_data_show->setItem(i, 5, new QTableWidgetItem(access_pass));
                ui->tableView_inserted_data_show->setItem(i, 6, new QTableWidgetItem(image_path));

            }

            ui->tableView_inserted_data_show->verticalHeader()->hide();
        }


    }
}
config_database::~config_database()
{
    ////qDebug() << "Destructor in >>>>>configDb" << endl;
    //    emit emitQuiteThread();
    delete ui;
    //    delete modal;
    //    delete modal1;
    delete image_show_d;
}
void config_database::requestWorkConfigDb()
{
    configdb_mutex.lock();
    //    //qDebug() << "Config Thread" << endl;

    _warking = true;
    _abort = false;

    configdb_mutex.unlock();

    emit warkRequestedConfigDb();
}

void config_database::abortConfigDb()
{
    configdb_mutex.lock();

    if(_warking){
        _abort = true;

    }

    configdb_mutex.unlock();
}

void config_database::funTable()
{
    ui->tableView_inserted_data_show->setColumnCount(7);
    QStringList colmname;
    //ID, name, position, address, phone, access_pass, image_path
    colmname << "ID" << "Name" << "Position" << "Address" << "Phone" << "Access Pass" << "Image Path";
    ui->tableView_inserted_data_show->setHorizontalHeaderLabels(colmname);

    ui->tableView_inserted_data_show->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView_inserted_data_show->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_inserted_data_show->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_inserted_data_show->setFocusPolicy(Qt::NoFocus);

    ui->tableView_inserted_data_show->setAutoScroll(true);


    ui->pushButton_delete->setEnabled(false);

    //    modal = new QSqlQueryModel();
    //    modal1 = new QSqlQueryModel();

    //check_pic_is_loaded_from_uniqe_faces = false;


    _warking = false;
    _abort = false;

    ui->pushButton_add_information->setEnabled(false);

    ui->tableView_inserted_data_show->setRowCount(0);
    if(connectionDB()){
        QSqlQuery query;
        query.prepare("select ID, name, position, address, phone, access_pass, image_path from ADD_FACE;");

        if(query.exec()){
            ////qDebug() << "Yes data found" ;
            ////qDebug() << query.lastQuery();
            while(query.next()){

                int Id = query.value(0).toInt();
                ////qDebug() << "Yes data found" << Id << endl;
                QString name = query.value(1).toString();
                QString position = query.value(2).toString();
                QString address = query.value(3).toString();
                QString phone = query.value(4).toString();
                QString access_pass = query.value(5).toString();
                QString image_path = query.value(6).toString();

                int i = ui->tableView_inserted_data_show->rowCount();

                ui->tableView_inserted_data_show->insertRow(i);
                ui->tableView_inserted_data_show->setItem(i, 0, new QTableWidgetItem(QString::number(Id)));
                ui->tableView_inserted_data_show->setItem(i, 1, new QTableWidgetItem(name));
                ui->tableView_inserted_data_show->setItem(i, 2, new QTableWidgetItem(position));
                ui->tableView_inserted_data_show->setItem(i, 3, new QTableWidgetItem(address));
                ui->tableView_inserted_data_show->setItem(i, 4, new QTableWidgetItem(phone));
                ui->tableView_inserted_data_show->setItem(i, 5, new QTableWidgetItem(access_pass));
                ui->tableView_inserted_data_show->setItem(i, 6, new QTableWidgetItem(image_path));

            }

            ui->tableView_inserted_data_show->verticalHeader()->hide();
        }


    }
}

void config_database::setEnableTrueOrFalse()
{
    //    configdb_mutex.lock();

    //    delete modal;
    //    delete modal1;
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_take_photo->setEnabled(true);
    ui->label_image_show->clear();
    file_name = "";
    //    modal = new QSqlQueryModel();
    //    modal1 = new QSqlQueryModel();

    //    configdb_mutex.unlock();
}

void config_database::addNewFaceOnDB(int pic)
{
    ////qDebug() << " From addNewFaceDB, received value" << QString::number(pic);

    //emit AddToLoadTemplate("name", "/home/sigmind/watchcam-testedOK/faces/tanmoy.jpg");


}

void config_database::uniqeFaceToConfigDB(QPixmap pic)
{
    //    //qDebug() << "I'm in ui" << endl;
    this->show();

    check_pic_is_loaded_from_uniqe_faces = true;
    valid = true;

    this->pic = pic;
    ui->pushButton_take_photo->setEnabled(false);

    ui->label_image_show->setPixmap(pic);
    ui->label_image_show->setScaledContents( true );
    ui->label_image_show->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    ui->lineEdit_name->setText("");
    ui->lineEdit_phone->setText("");
    ui->lineEdit_address->setText("");
    ui->lineEdit_position->setText("");
    ui->lineEdit_access_pass->setText("");


    //    requestWorkConfigDb();
}

void config_database::testThread()
{
    //    //qDebug()<<"Aborting b Config db process in Thread "<<thread()->currentThreadId();
    //    emit finishedConfigDb();
    this->show();
}

void config_database::on_pushButton_take_photo_clicked()
{
    ui->pushButton_webCam_photo->setEnabled(false);

    ////qDebug()<<"Aborting b Config db process in Thread "<<thread()->currentThreadId();
    //    configdb_mutex.lock();
    file_name = QFileDialog::getOpenFileName(this, tr("choose"), "", tr("images (*.png)"));

    if(QString::compare(file_name, QString()) != 0){
        valid = image.load(file_name);
        ////qDebug()<<"valid check >>";

        if(valid){
            ////qDebug()<<"valid check if >>";
            image = image.scaledToWidth(ui->label_image_show->width(), Qt::SmoothTransformation);
            image = image.scaledToHeight(ui->label_image_show->height(), Qt::SmoothTransformation);
            ui->label_image_show->setPixmap(QPixmap::fromImage(image));

        }
        else {
            QMessageBox msg_box;
            msg_box.setText("Take a photo");
            msg_box.exec();
            ui->label_image_show->setFocus();
        }
    }
    //    configdb_mutex.unlock();
    ui->pushButton_add_information->setEnabled(true);
    ui->pushButton_webCam_photo->setEnabled(true);
}
void config_database::on_pushButton_add_information_clicked()
{

    QString up = ui->pushButton_add_information->text();
    qDebug()<<"j pushButton_add_information 1";

    if(QString::compare(up, "Update") == 0){
        ////qDebug()<<"update condition true";

        QString name, position, address, phone, access_pass; // user information

        /* take user input */
        name = ui->lineEdit_name->text();
        position = ui->lineEdit_position->text();
        address = ui->lineEdit_address->text();
        phone = ui->lineEdit_phone->text();
        access_pass = ui->lineEdit_access_pass->text();

        if(name.QString::isEmpty()){
            QMessageBox msg_box;
            msg_box.setText("Name field empty!");
            msg_box.exec();
            ui->lineEdit_name->setFocus();
            ui->lineEdit_name->setText("");
        }

        QPixmap pic;
        pic.load(file_name);
        QString face_path = "./faces/";
        QDir myDir;
        QString folder_name = "temp_late";
        QString image_path;
        QString image_name;
        if(!myDir.exists(folder_name)) //if no directory so create directory
        {
            myDir.mkpath(face_path+folder_name);
            image_name = name+".png";
            image_path = face_path+folder_name+"/"+image_name;
        }else {
            myDir.mkpath(face_path+folder_name);
            image_name = name+".png";
            image_path = face_path+folder_name+"/"+image_name;
        }
        QFile file(face_path+folder_name+"/"+image_name);
        file.open(QIODevice::WriteOnly);
        pic.save(&file, "PNG");

        std::string newFile = image_path.toStdString();
        QString file_name_ = QString::fromUtf8(newFile.c_str());
        pic.load(file_name_);
        QImage imagedup = pic.toImage();

        if(!imagedup.isNull()){
            bool check_load_temp_late = emit AddToLoadTemplate(name, file_name_);
            ////qDebug() << "check_load_temp_late ........... " << check_load_temp_late;
            if(check_load_temp_late == true/* || check_load_temp_late == false*/){

                if(connectionDB()){
                    QString str = "update ADD_FACE set name = ?, position = ?, address = ?, phone = ?, access_pass = ?, image_path = ? where ID = ? ;";
                    QSqlQuery qr;
                    qr.prepare(str);
                    qr.addBindValue(name);
                    qr.addBindValue(position);
                    qr.addBindValue(address);
                    qr.addBindValue(phone);
                    qr.addBindValue(access_pass);
                    qr.addBindValue(image_path);
                    qr.addBindValue(Id);
                    if(qr.exec()){
                        ////qDebug() << "last " << qr.lastQuery();
                        int rr = qr.numRowsAffected();
                        if(rr != 0){
                            QFile bf( file_name ); // delete picture from folder
                            bf.remove();
                            bf.flush();
                            emit deleteFromLoadTem(file_name, name_up);// delete from load temp
                            QMessageBox msg_box;
                            msg_box.setText("Updated done!");
                            msg_box.exec();
                            ui->lineEdit_name->setText("");
                            ui->lineEdit_phone->setText("");
                            ui->lineEdit_address->setText("");
                            ui->lineEdit_position->setText("");
                            ui->lineEdit_access_pass->setText("");
                            ui->label_image_show->clear();
                        }else{
                            QMessageBox msg_box;
                            msg_box.setText("Not update");
                            msg_box.exec();
                        }
                    }else {
                        //                        //qDebug() << "last " << qr.lastQuery();
                        //                        //qDebug() << "last q " << qr.lastError();
                    }
                }
            }else{
                QMessageBox msg_box;
                msg_box.setText("Not update");
                msg_box.exec();
            }
        }else {
            QFile bf( file_name_ ); // delete picture from folder
            bf.remove();
            bf.flush();
            QMessageBox msg_box;
            msg_box.setText("Not update");
            msg_box.exec();
        }
    }else{
        //        modal->clear();
        //        modal1->clear();
        qDebug() << "j pushButton_add_information 2" << endl;

        QString name, position, address, phone, access_pass; // user information
        pic.load(file_name);

        qDebug()<<"j before pic load and valid val: "<<valid;

        if(valid == true){ // if image is load then valid is true;
            ////qDebug()<<"valid true tested";

            /* take user input */
            name = ui->lineEdit_name->text();
            position = ui->lineEdit_position->text();
            address = ui->lineEdit_address->text();
            phone = ui->lineEdit_phone->text();
            access_pass = ui->lineEdit_access_pass->text();

            if(name.QString::isEmpty()){
                QMessageBox msg_box;
                msg_box.setText("Name field empty!");
                msg_box.exec();
                ui->lineEdit_name->setFocus();
                ui->lineEdit_name->setText("");
            }
            //            if(position.QString::isEmpty()){
            //                QMessageBox msg_box;
            //                msg_box.setText("Position field empty!");
            //                msg_box.exec();
            //                ui->lineEdit_position->setFocus();
            //                ui->lineEdit_position->setText("");
            //            }
            //            if(address.QString::isEmpty()){
            //                QMessageBox msg_box;
            //                msg_box.setText("Address field empty!");
            //                msg_box.exec();
            //                ui->lineEdit_phone->setFocus();
            //                ui->lineEdit_phone->setText("");
            //            }
            //            if(phone.QString::isEmpty()){
            //                QMessageBox msg_box;
            //                msg_box.setText("Phone number field empty!");
            //                msg_box.exec();
            //                ui->lineEdit_phone->setFocus();
            //                ui->lineEdit_phone->setText("");
            //            }

            //            if(access_pass.QString::isEmpty()){
            //                QMessageBox msg_box;
            //                msg_box.setText("Access pass field empty!");
            //                msg_box.exec();
            //                ui->lineEdit_access_pass->setFocus();
            //                ui->lineEdit_access_pass->setText("");
            //            }

            if(!name.QString::isEmpty()/* && !position.QString::isEmpty() && !address.QString::isEmpty() && !phone.QString::isEmpty() && !access_pass.QString::isEmpty()*/){
                // checked database connection
                if(connectionDB()){
                    qDebug()<<"j connectionDB check : ";

                    ////qDebug() << "successful connect db of if condi";
                    QSqlQuery query; // sql query execution object

                    QString create_table_query =
                            "create table ADD_FACE ( "
                            "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "name TEXT not null UNIQUE, "
                            "position TEXT, "
                            "address TEXT, "
                            "phone TEXT, "
                            "access_pass TEXT, "
                            "image_path TEXT not null"
                            ");"
                            ;

                    if(query.exec(create_table_query)){
                        ////qDebug() << "Table Created";
                    }else {
                        ////qDebug() << "Table Created failed";
                    }


                    QString smartRecordLogQuery =
                            "create table SmartRecordLog ( "
                            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "session_id	int NOT NULL,"
                            "source_id	int NOT NULL,"
                            "record_duration	VARCHAR ( 20 ) NOT NULL,"
                            "dir_path	VARCHAR ( 100 ) NOT NULL,"
                            "file_name	VARCHAR ( 100 ) NOT NULL,"
                            "LC	int NOT NULL,"
                            "FR	int NOT NULL,"
                            "OD	int NOT NULL,"
                            "time_stamp	DATETIME NOT NULL"
                            ");"
                            ;

                    if(query.exec(smartRecordLogQuery)){
                        qDebug() << "smartRecordLogQuery Created";
                    }else {
                        qDebug() << "smartRecordLogQuery Failed";
                    }

                    // image write into folder

                    QString face_path = "./faces/";
                    QDir myDir, myDir2;
                    QString folder_name = "temp_late";

                    if(check_pic_is_loaded_from_uniqe_faces  == true){
                        pic = capture_showface_img;
                        check_pic_is_loaded_from_uniqe_faces  = false;
                        ui->pushButton_take_photo->setEnabled(true);// that means upload photo button
                        ui->pushButton_webCam_photo->setEnabled(true);
                        ////qDebug()<<"chek complete";
                        //                        if(!pic.isNull())
                        //                            //qDebug()<<"check_pic_is_loaded_from_uniqe_faces pic is null";
                        //                        else {
                        //                            //qDebug()<<"check_pic_is_loaded_from_uniqe_faces is correct";
                        //                        }
                    }
                    /* caputures from user hujur*/

                    if(capture_flag == true){
                        ////qDebug()<<"camera face capture";
                        pic = QPixmap::fromImage(capture_image);// QImgae into QPixmap
                        capture_flag = false;
                    }

                    /* end of hujur*/
                    //                //qDebug() << "File name" << file_name << endl;

                    QString image_path;

                    QString image_name, img_nam2, image_path2;

                    QString folder_name2 =  "temp_late2";
                    if(!myDir2.exists(folder_name2)) //if no directory so create directory
                    {
                        qDebug() << "temp_late2 create" << endl;

                        myDir2.mkpath(face_path+folder_name2);
                        img_nam2 = name+".png";
                        image_path2 = face_path+folder_name2+"/"+img_nam2;
                    }

                    if(!myDir.exists(folder_name)) //if no directory so create directory
                    {
                        qDebug() << "j If con 3" << endl;
                        //                QPixmap pic;
                        //                pic.load(file_name);

                        myDir.mkpath(face_path+folder_name);
                        image_name = name+".jpg";
                        //                QFile file(face_path+folder_name+"/"+image_name);
                        //                file.open(QIODevice::WriteOnly);
                        //                pic.save(&file, "PNG");

                        image_path = face_path+folder_name+"/"+image_name;
                    }
                    else {
                        qDebug() << "j Else con 4" << endl;
                        //                QPixmap pic;
                        //                pic.load(file_name);

                        myDir.mkpath(face_path+folder_name);
                        image_name = name+".jpg";

                        image_path = face_path+folder_name+"/"+image_name;

                        myDir2.mkpath(face_path+folder_name2);
                        img_nam2 = name+".png";
                        image_path2 = face_path+folder_name2+"/"+img_nam2;

                    }

                    ui->lineEdit_name->setText("");
                    ui->lineEdit_phone->setText("");
                    ui->lineEdit_address->setText("");
                    ui->lineEdit_position->setText("");
                    ui->lineEdit_access_pass->setText("");
                    ui->label_image_show->clear();

                    int len_access_pass = access_pass.length(); // length of access pass

                    QString access_pass_another = ""; int index_of_access_pass = 0;

                    for(int i = 0; i < len_access_pass; ){
                        if(index_of_access_pass % 2 != 0){
                            access_pass_another+=',';
                        }else {
                            access_pass_another+=access_pass.at(i);
                            ++i;
                        }
                        ++index_of_access_pass;
                    }
                    ////qDebug() << access_pass_another << "(((((((((((((((" << endl;

//                    bool insertion_check = insertDataIntoTable(name, position, address, phone, access_pass_another, image_path); // insert into table
                    // for testing of image_path2
                    bool insertion_check = insertDataIntoTable(name, position, address, phone, access_pass_another, image_path2); // insert into table

                    //                access_pass_another.clear();
                    qDebug()<<"insertion_check: "<<insertion_check;

                    if(insertion_check){
                        if(pic.isNull()){
                            ////qDebug()<<"pic is not >>valid";
                        }
                        else{
                            ////qDebug()<<">>pic is valid";
                        }
                        qDebug()<<"j insertion_check 5";

                        QFile file(face_path+folder_name+"/"+image_name);
                        file.open(QIODevice::WriteOnly);
                        pic.save(&file, "JPG");
                        file.flush();

                        // for testing
                        QFile file2(face_path+folder_name2+"/"+img_nam2);
                        file2.open(QIODevice::WriteOnly);
                        pic.save(&file2, "PNG");
                        file2.flush();

                        std::string newFile = image_path.toStdString();
                        QString file_name_ = QString::fromUtf8(newFile.c_str());
                        //                    QString file_name_ = file_name;
                        ////qDebug() << "File name " << name+" "+file_name_ << endl;
                        ////qDebug() << "emit AddToLoadTemplate(name, file_name_);" << endl;

                        ////qDebug() << " Before Emit config_db\n";

                        bool check_load_temp_late = emit AddToLoadTemplate(name, file_name_);
                        //                    bool check_load_temp_late = true;
                        //                    bool check_load_temp_late = emit AddToLoadTemplate(name, file_name);

                        qDebug()<<"check_load_temp_late: "<<check_load_temp_late;

                        if(check_load_temp_late == true){

                            QMessageBox msgBox;
                            msgBox.setText("SuccessFully loaded!");
                            msgBox.exec();

//                            pic.load(file_name_);
//                            QImage imagedup = pic.toImage();
//                            if(!imagedup.isNull()){
//                                //qDebug()<<"image is right, tested";
//                            }
//                            else {
//                                //qDebug()<<"false image write, so again write..";

//                                ui->lineEditDB->setText("Invalid Image");

//                                QFile bf( file_name_ ); // delete picture from folder
//                                bf.remove();
//                                bf.flush();

//                                deleteFromAddFaceTable(file_name_);
//                                pic.load(file_name);
//                                ////qDebug()<<"file name again ="<<file_name;

//                                QFile file(face_path+folder_name+"/"+image_name);
//                                file.open(QIODevice::WriteOnly);
//                                pic.save(&file, "PNG");
//                                file.flush();

//                                insertDataIntoTable(name, position, address, phone, access_pass_another, image_path); // insert again into table

//                                //qDebug()<<"again pic write into folder";
//                            }
//                            this->close();

                        }else{

                            QMessageBox msgBox;
                            msgBox.setText("Couldn't loaded!");
                            msgBox.exec();

                            QFile bf( file_name_ ); // delete picture from folder
                            bf.remove();
                            bf.flush();

                            QFile bf2( file_name_ ); // delete picture from folder
                            bf2.remove();
                            bf2.flush();

                            deleteFromAddFaceTable(file_name_);
                            //                        this->close();
                            //qDebug() << "Signal not retrun" << endl;
                        }

                        //                    this->close();

                        ////qDebug() << " After Emit config_db\n";

                        name = "";
                        position= "";
                        address = "";
                        phone = "";
                        access_pass = "";
                        file_name = "";
                        valid = false;

                        //                warker->load_template();
                    }
                    access_pass_another.clear();
                }
            }

            //        //qDebug() << "Name = " << name << " Position = " << position << " Address " << address << " Phone = " << phone << " Image path = " << file_name;
        }
        //    configdb_mutex.unlock();
    }
    tableShow();


}



void config_database::on_lineEdit_search_box_returnPressed()// Search specific item from database
{
    //    QMutexLocker locker(&configdb_mutex);
    //    configdb_mutex.lock();
    QString search_info = ui->lineEdit_search_box->text(); // take user input

    if(search_info.QString::isEmpty()){ // user input is empty
        QMessageBox msg_box;
        msg_box.setText("Enter something then press enter");
        msg_box.exec();
        ui->lineEdit_search_box->setFocus();
    }
    else {
        ui->tableView_inserted_data_show->setRowCount(0);
        search_info = "%"+search_info+"%";
        ////qDebug()<<"search info = "<<search_info;
        if(connectionDB()){
            QSqlQuery query;
            query.prepare("select ID, name, position, address, phone, access_pass, image_path from ADD_FACE "
                          "where (name Like ?);");
            query.addBindValue(search_info);

            if(query.exec()){
                ////qDebug() << "Yes data found" ;
                ////qDebug() << query.lastQuery();
                while(query.next()){

                    int Id = query.value(0).toInt();
                    ////qDebug() << "Yes data found" << Id << endl;
                    QString name = query.value(1).toString();
                    QString position = query.value(2).toString();
                    QString address = query.value(3).toString();
                    QString phone = query.value(4).toString();
                    QString access_pass = query.value(5).toString();
                    QString image_path = query.value(6).toString();

                    int i = ui->tableView_inserted_data_show->rowCount();

                    ui->tableView_inserted_data_show->insertRow(i);
                    ui->tableView_inserted_data_show->setItem(i, 0, new QTableWidgetItem(QString::number(Id)));
                    ui->tableView_inserted_data_show->setItem(i, 1, new QTableWidgetItem(name));
                    ui->tableView_inserted_data_show->setItem(i, 2, new QTableWidgetItem(position));
                    ui->tableView_inserted_data_show->setItem(i, 3, new QTableWidgetItem(address));
                    ui->tableView_inserted_data_show->setItem(i, 4, new QTableWidgetItem(phone));
                    ui->tableView_inserted_data_show->setItem(i, 5, new QTableWidgetItem(access_pass));
                    ui->tableView_inserted_data_show->setItem(i, 6, new QTableWidgetItem(image_path));

                }

                ui->tableView_inserted_data_show->verticalHeader()->hide();
                ui->lineEdit_search_box->setText("");// search box set as empty
            }


        }
    }
    //    //qDebug() << "Search " << search_info;
    //    configdb_mutex.unlock();

}



void config_database::on_pushButton_delete_clicked()
{
    //    configdb_mutex.lock();
    QModelIndexList selection = ui->tableView_inserted_data_show->selectionModel()->selectedRows(0);// get selected row

    if (!selection.empty()){ // check selection is empty or not
        QModelIndex idIndex = selection.at(0); // value of selected row in 0 index
        int id = idIndex.data().toInt();
        ////qDebug() << "id " << id << endl;


        QString image_path_from_table = ui->tableView_inserted_data_show->model()->index(idIndex.row(), 6).data().toString();
        QString image_name = ui->tableView_inserted_data_show->model()->index(idIndex.row(), 1).data().toString();
        //        //qDebug() << "Path ........" << image_path_from_table;

        /* message box */
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("Delete Album"),
                                       tr("Are you sure you want to delete"),
                                       QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {
            //            //qDebug() << "IDIs " << id;
            if(connectionDB()){

                deleteFromDatabasBySelectedRow(id); // delete from db

                qDebug() << "image_path_from_table " << image_path_from_table << " " << " image_name " << image_name << endl;

                emit deleteFromLoadTem(image_path_from_table, image_name);// delete from load temp

                QFile bf( image_path_from_table ); // delete picture from folder
                bf.remove();

                /* After delete data show all data into table*/
                ui->tableView_inserted_data_show->setRowCount(0);
                QSqlQuery query;
                query.prepare("select ID, name, position, address, phone, access_pass, image_path from ADD_FACE;");

                if(query.exec()){
                    ////qDebug() << "Yes";
                    //                    modal1->setQuery(query);


                    while(query.next()){
                        int Id = query.value(0).toInt();
                        QString name = query.value(1).toString();
                        QString position = query.value(2).toString();
                        QString address = query.value(3).toString();
                        QString phone = query.value(4).toString();
                        QString access_pass = query.value(5).toString();
                        QString image_path = query.value(6).toString();


                        int i = ui->tableView_inserted_data_show->rowCount();

                        ui->tableView_inserted_data_show->insertRow(i);
                        ui->tableView_inserted_data_show->setItem(i, 0, new QTableWidgetItem(QString::number(Id)));
                        ui->tableView_inserted_data_show->setItem(i, 1, new QTableWidgetItem(name));
                        ui->tableView_inserted_data_show->setItem(i, 2, new QTableWidgetItem(position));
                        ui->tableView_inserted_data_show->setItem(i, 3, new QTableWidgetItem(address));
                        ui->tableView_inserted_data_show->setItem(i, 4, new QTableWidgetItem(phone));
                        ui->tableView_inserted_data_show->setItem(i, 5, new QTableWidgetItem(access_pass));
                        ui->tableView_inserted_data_show->setItem(i, 6, new QTableWidgetItem(image_path));

                    }

                    ui->tableView_inserted_data_show->verticalHeader()->hide();
                    //                    ui->tableView_inserted_data_show->setModel(modal1);

                    ui->lineEdit_search_box->setText("");// search box reset by empty value
                }
            }
        }
    }else {
        QMessageBox::information(this, tr("Delete information"),
                                 tr("Select the data you want to delete."));
    }
    //    configdb_mutex.unlock();
}


void config_database::on_tableView_inserted_data_show_clicked(const QModelIndex &index)
{
    qDebug() << "johir on_tableView_inserted_data_show_clicked";
    //    configdb_mutex.lock();
    int row = index.row();
    int Id = index.sibling(row, 0).data().toInt();
    QString image_path = index.sibling(row, 6).data().toString();
    qDebug() <<"Image ================ "<< image_path;

    //for testing johurul
    //./faces/temp_late/shuvomvi.jpg
//    QString image_path1 = image_path.mid(0,17);
//    QString image_path2 = image_path.mid(17,image_path.size()- 4);
////    QString image_path3 = image_path.mid(image_path.size()-3, image_path.size());
//    image_path = image_path1 + "2" +image_path2;
////    qDebug() <<"image_path1: "<<image_path1<<" image_path2: "<<image_path2<<" image_path3: "<<image_path3<<" image_path: "<<image_path<<endl;


    QImage image;
    //    bool valid = image.load(image_path);

    // Image show dialog
    //    ImageShowDialog *image_show_d;
    //    image_show_d = new ImageShowDialog(image_path, image, this);
    connect(image_show_d, SIGNAL(modifyDbInfo(int)), this, SLOT(updateAddFaceTableData(int)));
    image_show_d->imageSetIntoLabel(Id, image_path, image);
    image_show_d->setModal(true);
    image_show_d->setFixedSize(image_show_d->size());
    image_show_d->exec();

    ui->pushButton_delete->setEnabled(true);

    //delete image_show_d; // free memory
    //    configdb_mutex.unlock();
}

void config_database::updateAddFaceTableData(int Id)
{
    ////qDebug() << "IDDDDDDDDDDDDDDDDDDDDDDdd" << Id;
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_add_information->setEnabled(true);

    ui->lineEdit_name->setText("");
    ui->lineEdit_phone->setText("");
    ui->lineEdit_address->setText("");
    ui->lineEdit_position->setText("");
    ui->lineEdit_access_pass->setText("");
    ui->label_image_show->clear();
    ui->pushButton_add_information->setText("Update");
    if(connectionDB()){
        QString str = "select name, position, address, phone, access_pass, image_path from ADD_FACE where ID=?";
        QSqlQuery q_str;
        q_str.prepare(str);
        q_str.addBindValue(Id);
        q_str.exec();
        while(q_str.next()){
            QString name = q_str.value(0).toString();
            QString position = q_str.value(1).toString();
            QString address = q_str.value(2).toString();
            QString phone = q_str.value(3).toString();
            QString access_pass = q_str.value(4).toString();
            QString image_path = q_str.value(5).toString();

            ui->lineEdit_name->setText(name);
            ui->lineEdit_position->setText(position);
            ui->lineEdit_address->setText(address);
            ui->lineEdit_phone->setText(phone);
            ui->lineEdit_access_pass->setText(access_pass);
            QImage image;
            image.load(image_path);
            image = image.scaledToWidth(ui->label_image_show->width(), Qt::SmoothTransformation);
            image = image.scaledToHeight(ui->label_image_show->height(), Qt::SmoothTransformation);
            ui->label_image_show->setPixmap(QPixmap::fromImage(image));

            file_name = image_path;
            this->Id = Id;
            this->name_up = name;
        }
    }
}

void config_database::on_pushButton_webCam_photo_clicked()
{
    ////qDebug()<<"webCam button clicked";
    ObjectOfWebcam = new WebCam();
    connect(ObjectOfWebcam, SIGNAL(emitImageToSetLabel(QImage)), this, SLOT(setCaptureImageToLabel(QImage)));
    connect(ObjectOfWebcam, SIGNAL(imagePathWebcamPhoto(QString)), this, SLOT(setCaptureImageToDB(QString)));
    ObjectOfWebcam->show();

    ui->pushButton_webCam_photo->setEnabled(false);
    ui->pushButton_take_photo->setEnabled(false);
    ui->pushButton_add_information->setEnabled(false);

    connect(ObjectOfWebcam, SIGNAL(emitFlagChangedOfWebcamAndUploadPhoto()), this, SLOT(slotFlagChangedOfWebcamAndUploadPhoto()));

}

void config_database::setCaptureImageToLabel(QImage scaledImage)
{
    ////qDebug()<<"config_database::setCaptureImageToLabel method";
    capture_image = scaledImage;
    capture_flag = true;
    valid = true;


    scaledImage = scaledImage.scaledToWidth(ui->label_image_show->width(), Qt::SmoothTransformation);
    scaledImage = scaledImage.scaledToHeight(ui->label_image_show->height(), Qt::SmoothTransformation);

    ui->label_image_show->setPixmap(QPixmap::fromImage(scaledImage));
}

void config_database::setCaptureImageToDB(QString capture_webcam_image_path)
{
    ////qDebug()<<"capture_image_path inside setCaptureImageToDB slot ="<<capture_webcam_image_path;
    //file_name = capture_webcam_image_path;
}

void config_database::slotFlagChangedOfWebcamAndUploadPhoto()
{
    ////qDebug()<<"config_database::slotFlagChangedOfWebcamAndUploadPhoto";

    ui->pushButton_webCam_photo->setEnabled(true);
    ui->pushButton_take_photo->setEnabled(true);
    ui->pushButton_add_information->setEnabled(true);
}

void config_database::closeEvent(QCloseEvent *event)
{
    ////qDebug()<<"config_database::closeEvent";

    event->accept();

    ui->lineEdit_name->setText("");
    ui->lineEdit_phone->setText("");
    ui->lineEdit_address->setText("");
    ui->lineEdit_position->setText("");
    ui->lineEdit_access_pass->setText("");
    ui->label_image_show->clear();
    ui->pushButton_add_information->setEnabled(false);

    ui->tableView_inserted_data_show->clear();
    ui->tableView_inserted_data_show->reset();
    ui->tableView_inserted_data_show->setRowCount(0);


    //    delete ui;
    //    delete modal;
    //    delete modal1;
}

void config_database::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    ////qDebug() << "1234567899999999999";
    funTable();
}

void config_database::on_pushButton_clicked()
{
    qDebug() << "j batch enrollment click ";
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    emit batchDir(dir);
}

void config_database::on_pushButton_reset_clicked()
{
    ui->lineEdit_name->setText("");
    ui->lineEdit_phone->setText("");
    ui->lineEdit_address->setText("");
    ui->lineEdit_position->setText("");
    ui->lineEdit_access_pass->setText("");
    ui->label_image_show->clear();
    ui->pushButton_add_information->setEnabled(false);

//    if(connectionDB()){
//        QSqlQuery query;
//        query.prepare("select ID, name, position, address, phone, access_pass, image_path from ADD_FACE;");
//        //query.addBindValue(search_info);

//        if(query.exec()){
//            //qDebug() << "Yes data found" ;
//            //qDebug() << query.lastQuery();
//            while(query.next()){

//                int Id = query.value(0).toInt();
//                ////qDebug() << "Yes data found" << Id << endl;
//                QString name = query.value(1).toString();
//                QString position = query.value(2).toString();
//                QString address = query.value(3).toString();
//                QString phone = query.value(4).toString();
//                QString access_pass = query.value(5).toString();
//                QString image_path = query.value(6).toString();

//                int i = ui->tableView_inserted_data_show->rowCount();

//                ui->tableView_inserted_data_show->insertRow(i);
//                ui->tableView_inserted_data_show->setItem(i, 0, new QTableWidgetItem(QString::number(Id)));
//                ui->tableView_inserted_data_show->setItem(i, 1, new QTableWidgetItem(name));
//                ui->tableView_inserted_data_show->setItem(i, 2, new QTableWidgetItem(position));
//                ui->tableView_inserted_data_show->setItem(i, 3, new QTableWidgetItem(address));
//                ui->tableView_inserted_data_show->setItem(i, 4, new QTableWidgetItem(phone));
//                ui->tableView_inserted_data_show->setItem(i, 5, new QTableWidgetItem(access_pass));
//                ui->tableView_inserted_data_show->setItem(i, 6, new QTableWidgetItem(image_path));

//            }

//            ui->tableView_inserted_data_show->verticalHeader()->hide();
//            ui->lineEdit_search_box->setText("");// search box set as empty
//        }


//    }

//    ui->tableView_inserted_data_show->clear();
//    ui->tableView_inserted_data_show->reset();
    //    ui->tableView_inserted_data_show->setRowCount(0);
}

void config_database::showFaceToConfigDB(QPixmap pictre)
{
        ////qDebug() << "show faces of configdb";
        this->show();

        //this->pic = pic;
        capture_showface_img = pictre;
        check_pic_is_loaded_from_uniqe_faces = true;
        valid = true;

//        ui->pushButton_take_photo->setEnabled(false);// that means upload photo button
//        ui->pushButton_webCam_photo->setEnabled(false);
        ui->pushButton_add_information->setEnabled(true);

        ui->label_image_show->setPixmap(pictre);
        ui->label_image_show->setScaledContents( true );
        ui->label_image_show->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

        QString face_path = "./captures/showface_capture/";
        QString obliq = "/";
        // QString format = "dd.MM.yyyy";
        //QString date_time =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        //date_time = encodeString(date_time);
        QString at = "<at>";
        QString date = QDate::currentDate().toString("dd.MM.yyyy");
        QString img_path = face_path+date+obliq;
        QString image_name = img_path+"face"+at+QTime::currentTime().toString()+".png";

        QDir myDir;
        if(!myDir.exists(date)) //if no directory so create directory
        {
            myDir.mkpath(img_path);
            //QString image_name = img_path+name+at+QTime::currentTime().toString()+".png";
            QFile file(image_name);
            file.open(QIODevice::WriteOnly);
            pictre.save(&file, "PNG");

        }

        ui->lineEdit_name->setText("");
        ui->lineEdit_phone->setText("");
        ui->lineEdit_address->setText("");
        ui->lineEdit_position->setText("");
        ui->lineEdit_access_pass->setText("");
}
