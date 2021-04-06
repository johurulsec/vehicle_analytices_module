#include "search_by_date_time.h"
#include "ui_search_by_date_time.h"

search_by_date_time::search_by_date_time(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search_by_date_time)
{
    //qDebug() << "Constructor Hello";
    ui->setupUi(this);

    ui->dateTimeEdit_from->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit_to->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

    ui->horizontalSlider_threshhold_value->setValue(0);

    ui->checkBox_recognized->setChecked(false);
    ui->checkBox_unrecognized->setChecked(false);

    ui->tableView_search_by_date->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView_search_by_date->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_search_by_date->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_search_by_date->setFocusPolicy(Qt::NoFocus);

    ui->tableView_search_by_date->setColumnCount(5);
    QStringList colmname;
    colmname << "Name" << "Save path" << "Time stamp" << "Confidence" << "Source";
    ui->tableView_search_by_date->setHorizontalHeaderLabels(colmname);

    modal = new QSqlQueryModel();
    modal1 = new QSqlQueryModel();

    if(connectionDB()){
        QSqlQuery query;
        if(query.exec("SELECT name, savePath, date_time as Time_stamp, confidence, video_src FROM FeedAddFace;")){
            //modal->setQuery(query);
            //qDebug() << query.lastQuery() << endl;
            while(query.next()){
                QString name = query.value(0).toString();
                QString save_path = query.value(1).toString();
                QString time_stamp = query.value(2).toString();
                int con = query.value(3).toInt();
                int video_src = query.value(4).toInt();


                int i = ui->tableView_search_by_date->rowCount();

                ui->tableView_search_by_date->insertRow(i);
                ui->tableView_search_by_date->setItem(i, 0, new QTableWidgetItem(name));
                ui->tableView_search_by_date->setItem(i, 1, new QTableWidgetItem(save_path));
                ui->tableView_search_by_date->setItem(i, 2, new QTableWidgetItem(time_stamp));
                ui->tableView_search_by_date->setItem(i, 3, new QTableWidgetItem(QString::number(con)));
                ui->tableView_search_by_date->setItem(i, 4, new QTableWidgetItem(QString::number(video_src)));

            }

            ui->tableView_search_by_date->horizontalHeader()->setVisible(true);
            ui->tableView_search_by_date->verticalHeader()->hide();
            //        ui->tableView_search_by_date->setModel(modal);
        }
    }
}

search_by_date_time::~search_by_date_time()
{
    //qDebug() << "Destructor";
    delete ui;
    delete modal;
    delete modal1;
}

void search_by_date_time::on_pushButton_search_clicked()// search button clicked
{
    //    modal->clear();
    ui->tableView_search_by_date->clear();
    ui->tableView_search_by_date->reset();

    ui->tableView_search_by_date->setRowCount(0);


    QDateTime date_time_from = ui->dateTimeEdit_from->dateTime();// from date time
    QString date_time_from_str = date_time_from.toString("yyyy-MM-dd hh:mm:ss");
    date_time_from_str = encodeString(date_time_from_str);
    fromTime = date_time_from_str;
    //    date_time_from_str = "2019-10-01 16:49:17";

    QDateTime date_time_to = ui->dateTimeEdit_to->dateTime(); // to date time
    QString date_time_to_str = date_time_to.toString("yyyy-MM-dd hh:mm:ss");
    date_time_to_str = encodeString(date_time_to_str);
    toTime = date_time_to_str;
    //    date_time_to_str = "2019-10-01 16:49:17";

    double prog_threshHold_value =  ui->progressBar_threshhold_value->value(); // progress bar threshhol value
    threshValue = prog_threshHold_value;

    bool recog_checkbox = ui->checkBox_recognized->checkState(); // recognized box checked or not
    rec_check = recog_checkbox;

    bool unrecog_checkbox = ui->checkBox_unrecognized->checkState();// unrecognized box checked or not
    unrec_check = unrecog_checkbox;


    //qDebug() << "DateFrom " << date_time_from_str << " " << " Prog thresh " << prog_threshHold_value << " Recog " << recog_checkbox << " Unrecog " << unrecog_checkbox << " To date "<< date_time_to_str;

    if(connectionDB()){
        //qDebug() << "CallToDeb";
        QSqlQuery query, query_temporary;

        if(recog_checkbox==true && unrecog_checkbox==false){
            query.prepare("create temporary table dynamicd "
                          "as "
                          "SELECT name, savePath, date_time  as time_stamp, confidence, video_src FROM FeedAddFace "
                          "WHERE (date_time BETWEEN :date_time_from_str AND :date_time_to_str) "
                          "AND "
                          "confidence >= :prog_threshHold_value;"
                          );
        }
        else if(unrecog_checkbox==true && recog_checkbox==false){
            query.prepare(
                        "create temporary table dynamicd "
                        "as "
                        "SELECT name, savePath, date_time  as time_stamp, confidence, video_src FROM FeedAddFace "
                        "WHERE (date_time BETWEEN :date_time_from_str AND :date_time_to_str) "
                        "AND "
                        "confidence <= :prog_threshHold_value;"
                        );
        }
        else if(recog_checkbox==true && unrecog_checkbox==true){
            query.prepare("create temporary table dynamicd "
                          "as "
                          "SELECT name, savePath, date_time  as time_stamp, confidence, video_src FROM FeedAddFace "
                          "WHERE (date_time BETWEEN :date_time_from_str AND :date_time_to_str) "
                          );
        }
        else {
            //qDebug() << "False";
            query.prepare("create temporary table dynamicd "
                          "as "
                          "SELECT name, savePath, date_time  as time_stamp, confidence, video_src FROM FeedAddFace "
                          "WHERE (date_time BETWEEN :date_time_from_str AND :date_time_to_str) ");
        }

        query.bindValue(":date_time_from_str", date_time_from_str);
        query.bindValue(":date_time_to_str", date_time_to_str);
        query.bindValue(":prog_threshHold_value", prog_threshHold_value);

        if(query.exec()){
            //qDebug() << "create temporary table";

            if(query_temporary.exec("select name, savePath, time_stamp, confidence, video_src from dynamicd;")){
                //qDebug()<< "select * from dynamic;";

                //                modal->setQuery(query_temporary);


                while(query_temporary.next()){
                    QString name = query_temporary.value(0).toString();
                    QString save_path = query_temporary.value(1).toString();
                    QString time_stamp = query_temporary.value(2).toString();
                    int con = query_temporary.value(3).toInt();
                    int video_src = query_temporary.value(4).toInt();

                    //qDebug() << "name ..............." << name << endl;

                    int i = ui->tableView_search_by_date->rowCount();

                    ui->tableView_search_by_date->insertRow(i);
                    ui->tableView_search_by_date->setItem(i, 0, new QTableWidgetItem(name));
                    ui->tableView_search_by_date->setItem(i, 1, new QTableWidgetItem(save_path));
                    ui->tableView_search_by_date->setItem(i, 2, new QTableWidgetItem(time_stamp));
                    ui->tableView_search_by_date->setItem(i, 3, new QTableWidgetItem(QString::number(con)));
                    ui->tableView_search_by_date->setItem(i, 4, new QTableWidgetItem(QString::number(video_src)));

                }

                ui->tableView_search_by_date->horizontalHeader()->setVisible(true);
                ui->tableView_search_by_date->verticalHeader()->hide();

                //                ui->tableView_search_by_date->setModel(modal);

                if(query_temporary.exec("DROP TEMPORARY TABLE dynamicd;")){
                    //qDebug() << "Delete temporary table";
                    //            modal1->clear();
                }else {
                    //qDebug() << "cant delete temporary table";
                }


            }else {
                //qDebug() << "cant select * from dynamic table";
            }

            /* after show data into table all user input element reset */

            ui->dateTimeEdit_from->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
            ui->dateTimeEdit_to->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

            ui->horizontalSlider_threshhold_value->setValue(0);

            ui->checkBox_recognized->setChecked(false);
            ui->checkBox_unrecognized->setChecked(false);

        }
        else {
            //qDebug() << "Cant created temporary table";
        }
    }

}


void search_by_date_time::on_tableView_search_by_date_clicked(const QModelIndex &index)
{
//    int row = index.row();
//    QString image_path = index.sibling(row, 1).data().toString();
//    //    //qDebug()<< "Clicked "<< image_path;
//    //    QPixmap pix(image_path);

//    QImage image;
//    bool valid = image.load(image_path);
//    ImageShowDialog *imshow_d;
//    imshow_d = new ImageShowDialog(image_path, image, this);
//    imshow_d->setModal(true);
//    imshow_d->setFixedSize(imshow_d->size());
//    imshow_d->exec();
//    delete imshow_d;
//    ui->tableView_search_by_date->clearSelection();
}
