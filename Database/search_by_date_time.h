#ifndef SEARCH_BY_DATE_TIME_H
#define SEARCH_BY_DATE_TIME_H

#include <QDialog>
#include <QDebug>
#include <DatabaseConnection/sqlite_connection.h>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QTextCodec>
#include <QByteArray>
#include <Database/imageshowdialog.h>
#include <QSqlQuery>

namespace Ui {
class search_by_date_time;
}

class search_by_date_time : public QDialog
{
    Q_OBJECT

public:
    explicit search_by_date_time(QWidget *parent = nullptr);
    ~search_by_date_time();

signals:
    void emitImagePath(QString);
private slots:
    void on_pushButton_search_clicked();

    void on_tableView_search_by_date_clicked(const QModelIndex &index);

private:
    Ui::search_by_date_time *ui;
    QSqlQueryModel *modal, *modal1; // model set into tableview

    // toTime, fromTime, threashHoldValue. use after delete operation.
    QString toTime, fromTime;
    double threshValue;
    bool rec_check, unrec_check;
};

static QString encodeString(QString data){
    QByteArray string = data.toUtf8();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString encodedString = codec->toUnicode(string);
    int l = encodedString.length();

    //    //qDebug()<<"l = "<<l<<" encodedString = "<<encodedString;

    //    int len = d.length();
    ////qDebug()<<"string = "<<d<<" length = "<<len;
    for(int i=0;i<l;i++){
        if(encodedString[i] == "\u09e6")
        {
            encodedString[i] = '0';/*
            //qDebug()<<encodedString[i]<<" "<<"0";*/
        }


        else if(encodedString[i] == "\u09e7")
        {
            encodedString[i] = '1';
        }
        ////qDebug()<<encodedString[i]<<" "<<"1";

        else if(encodedString[i] == "\u09e8")
        {
            encodedString[i] = '2';
        }
        // //qDebug()<<encodedString[i]<<" "<<"2";

        else if(encodedString[i] == "\u09e9")
        {
            encodedString[i] = '3';
        }
        ////qDebug()<<encodedString[i]<<" "<<"3";

        else if(encodedString[i] == "\u09ea")
        {
            encodedString[i] = '4';
        }
        ////qDebug()<<encodedString[i]<<" "<<"4";

        else if(encodedString[i] == "\u09eb")
        {
            encodedString[i] = '5';
        }
        // //qDebug()<<encodedString[i]<<" "<<"5";

        else if(encodedString[i] == "\u09ec")
        {
            encodedString[i] = '6';
        }
        ////qDebug()<<encodedString[i]<<" "<<"6";

        else if(encodedString[i] == "\u09ed")
        {
            encodedString[i] = '7';
        }
        ////qDebug()<<encodedString[i]<<" "<<"7";

        else if(encodedString[i] == "\u09ee")
        {
            encodedString[i] = '8';
        }
        ////qDebug()<<encodedString[i]<<" "<<"8";

        else if(encodedString[i] == "\u09ef")
        {
            encodedString[i] = '9';
        }
        ////qDebug()<<encodedString[i]<<" "<<"9";
        //        else {
        //            //qDebug()<<encodedString[i];
        //        }

    }
    return encodedString;
}

// Delete from database FeedAddFace Table
static void deleteFromFeedAddFaceTable(QString path){

    if(connectionDB()){
        QSqlQuery query;
        query.prepare("DELETE FROM FeedAddFace WHERE savePath = ?");
        query.addBindValue(path);
        if(query.exec()){
            //qDebug() << "delete from FeedAddFace "<< path;
        }else {
            //qDebug() << "Not delete";
        }
    }
}
#endif // SEARCH_BY_DATE_TIME_H
