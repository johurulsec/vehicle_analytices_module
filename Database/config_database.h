#ifndef CONFIG_DATABASE_H
#define CONFIG_DATABASE_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include "DatabaseConnection/sqlite_connection.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <Database/imageshowdialog.h>
#include <warker.h>
#include <QMutex>
//#include <QObject>
#include <QThread>
#include <QTimer>
#include<Database/webcam.h>
#include<QWaitCondition>
#include <QCloseEvent>
#include <QSqlQuery>
#include <QShowEvent>

namespace Ui {
class config_database;
}

class config_database : public QDialog
{
    Q_OBJECT

public:
    explicit config_database(QWidget *parent = nullptr);
    ~config_database();
    //    void uniqeFaceToConfigDB(QPixmap);

    void requestWorkConfigDb();
    void abortConfigDb();
    void funTable();
    void setEnableTrueOrFalse();
    void tableShow();

private slots:
    void on_pushButton_take_photo_clicked();

    void on_pushButton_add_information_clicked();


    void on_lineEdit_search_box_returnPressed();

    void on_pushButton_delete_clicked();

    void on_tableView_inserted_data_show_clicked(const QModelIndex &index);
    void addNewFaceOnDB(int pic);
    void uniqeFaceToConfigDB(QPixmap);

    void testThread();

    void on_pushButton_webCam_photo_clicked();

    void on_pushButton_clicked();

    void on_pushButton_reset_clicked();
    void showFaceToConfigDB(QPixmap);

public slots:
    void setCaptureImageToLabel(QImage);
    void setCaptureImageToDB(QString);
    void slotFlagChangedOfWebcamAndUploadPhoto();
    void updateAddFaceTableData(int);


protected:
    void closeEvent(QCloseEvent *event) override;
    void showEvent( QShowEvent * event );

signals:
    bool AddToLoadTemplate(QString name_, QString face_path);
    void deleteFromLoadTem(QString, QString);// delete from load template vector.
    void emitQuiteThread();

    void warkRequestedConfigDb();
    void finishedConfigDb();
    void batchDir(QString);


private:
    Ui::config_database *ui;

    // Image upload
    QImage image;
    QString file_name;
    bool valid;

    //    QSqlQueryModel *modal, *modal1;

    QPixmap pic;
    bool check_pic_is_loaded_from_uniqe_faces;

    QMutex configdb_mutex;
    QWaitCondition waitcondition;

    bool _warking;
    bool _abort;

    WebCam *ObjectOfWebcam;

    QImage capture_image;
    bool capture_flag;


    ImageShowDialog *image_show_d;

    int Id;
    QString name_up;
    QPixmap capture_showface_img;

};
// Insert into database
static bool insertDataIntoTable(QString name, QString position, QString address, QString phone, QString access_pass, QString image_path){
    QSqlQuery query;
    query.prepare("INSERT INTO ADD_FACE (name, position, address, phone, access_pass, image_path) VALUES (?,?,?,?,?,?);");
    query.addBindValue(name);
    query.addBindValue(position);
    query.addBindValue(address);
    query.addBindValue(phone);
    query.addBindValue(access_pass);
    query.addBindValue(image_path);

    if(query.exec()){ // Successfully executed then show pop up message box
        ////qDebug() << "Inserted "<< endl;
        //        QMessageBox msg_box;
        //        msg_box.setText("Successfully Inserted");
        //        msg_box.exec();
        return true;
    }else {
        ////qDebug() << "Not inserted!" << endl;
        //        QMessageBox msg_box;
        //        msg_box.setText("Cant inserted!");
        //        msg_box.exec();
    }
    return false;
}
// Delete from database
static void deleteFromDatabasBySelectedRow(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM ADD_FACE WHERE ID = ?");
    query.addBindValue(id);
    if(query.exec()){
        QMessageBox msg_box;
        msg_box.setText("Successfully Deleted");
        msg_box.exec();
    }else {
        ////qDebug() << "Not delete";
    }
}

// Delete from database AddFace Table
static void deleteFromAddFaceTable(QString path){

    if(connectionDB()){
        QSqlQuery query;
        query.prepare("DELETE FROM ADD_FACE WHERE image_path = ?");
        query.addBindValue(path);
        if(query.exec()){
            ////qDebug() << "delete from ADD_FACE "<< path;
        }else {
            ////qDebug() << "Not delete";
        }
    }
}


#endif // CONFIG_DATABASE_H
