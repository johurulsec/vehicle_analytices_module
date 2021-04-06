#include "reportgeneratefromtoto.h"
#include "ui_reportgeneratefromtoto.h"
#include <QThread>

ReportGenerateFromtoTo::ReportGenerateFromtoTo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportGenerateFromtoTo)
{
    //thread()->wait(10000);
    ////qDebug() << "cons report" << endl;
    ui->setupUi(this);
    //this->setAttribute(Qt::WA_DeleteOnClose);
    model = new QSqlQueryModel();
    printer = new QPrinter(QPrinter::PrinterResolution);
    doc = new QTextDocument();
    resetAllInfo(); // reset ui
}

ReportGenerateFromtoTo::~ReportGenerateFromtoTo()
{
    //qDebug() << "Des report generate" << endl;
    if(connectionDB()){
        QSqlQuery query;
        if(query.exec("drop table if exists data;")){/*//qDebug() << "delete";*/}
    }
    delete ui;
    delete printer;
    delete doc;
    delete model;
}

void ReportGenerateFromtoTo::resetAllInfo()

{
    ////qDebug() << "Reset all ldlkfsklfjdsf" << endl;
    ui->tableView_faces_show->setColumnCount(5);
    QStringList colmname;
    colmname << "Name" << "Save path" << "Time stamp" << "Confidence" << "Source";
    ui->tableView_faces_show->setHorizontalHeaderLabels(colmname);
    ui->tableView_faces_show->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView_faces_show->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_faces_show->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_faces_show->setFocusPolicy(Qt::NoFocus);
    ui->dateTimeEdit_to->setDate(QDate::fromString( "2000-01-01 00:00:00", "yyyy-MM-dd hh:mm::ss" ));
    ui->dateTimeEdit_from->setDate(QDate::fromString( "2000-01-01 00:00:00", "yyyy-MM-dd hh:mm::ss" ));
    ui->dateTimeEdit_to->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit_from->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->pushButton_export_as_pdf->setEnabled(false);

    //    ui->tableView_faces_show->clear();
    //    ui->tableView_faces_show->reset();

    ui->tableView_faces_show->setRowCount(0);

    if(connectionDB()){
        QSqlQuery query;
        if(query.exec("drop table if exists data;")){/*//qDebug() << "delete";*/}
        QString table_cr =
                "create table data as "
                "select name, savePath, strftime('%Y-%m-%d %H:%M:%S', date_time) as Time_stamp, confidence, video_src from FeedAddFace "
                "WHERE "
                "id IN (SELECT "
                "MAX(Id) "
                "FROM "
                "FeedAddFace "
                "GROUP BY name)"
                ";"
                ;
        query.prepare(table_cr);
        if(query.exec()){/*//qDebug() << "Create temporary table" << endl;*/}/*else {
            //qDebug() << "Else error " << query.lastError() << endl;
        }*/
        QString table_query =
                "select name, savePath, Time_stamp, confidence, video_src from data"
                ";"
                ;
        query.prepare(table_query);
        if(query.exec()){
            while(query.next()){
                QString name = query.value(0).toString();
                QString save_path = query.value(1).toString();
                QString time_stamp = query.value(2).toString();
                int con = query.value(3).toInt();
                int video_src = query.value(4).toInt();


                int i = ui->tableView_faces_show->rowCount();

                ui->tableView_faces_show->insertRow(i);
                ui->tableView_faces_show->setItem(i, 0, new QTableWidgetItem(name));
                ui->tableView_faces_show->setItem(i, 1, new QTableWidgetItem(save_path));
                ui->tableView_faces_show->setItem(i, 2, new QTableWidgetItem(time_stamp));
                ui->tableView_faces_show->setItem(i, 3, new QTableWidgetItem(QString::number(con)));
                ui->tableView_faces_show->setItem(i, 4, new QTableWidgetItem(QString::number(video_src)));

            }
            ui->tableView_faces_show->horizontalHeader()->setVisible(true);
            ui->tableView_faces_show->verticalHeader()->hide();

        }/*else {
            //qDebug() << "Else error " << query.lastQuery() << endl;
        }*/
    }

    //    QSqlDatabase::removeDatabase("watch_cam_ds");

    from = "";
    to = "";
    //ui->radioButton_present->setAutoExclusive(false);
    ui->radioButton_present->setChecked(false);
    //ui->radioButton_absent->setAutoExclusive(false);
    ui->radioButton_absent->setChecked(false);

    radio_present_button = false;
    radio_absent_button = false;

    //    DBImagePathStore.clear();
    //    absentImagePathStore.clear();
    //    folderImagePathStore.clear();
}

QString ReportGenerateFromtoTo::encodeBanglishToEnglishDT(QString data)
{
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

    }
    return encodedString;
}

void ReportGenerateFromtoTo::dataRetrive()
{
    QString curr_date = QDate::currentDate().toString("dd.MM.yyyy");
    curr_date = encodeBanglishToEnglishDT(curr_date);
    QString curr_time = QTime::currentTime().toString("h:m:s ap");
    curr_time = encodeBanglishToEnglishDT(curr_time);

    //    QString imran =
    //            "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>"
    //            "<html>"
    //            "<head>"
    //            "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>"
    //            "</head>"
    //            "<body class='fr-no-selection'>"
    //            "<div>"
    //            "<table style='width:100%;'>"
    //            "<tbody>"
    //            "<tr>"
    //            "<td style='width:40.8922%;'>"
    //            "<img src='https://1.bp.blogspot.com/-lFSG8NAJMQ0/XdeVCzePoLI/AAAAAAAAAAQ/6e18gne71Lkpi_hkWe6J_g166Pkd76BpQCEwYBhgL/s1600/Sigmind_Logo.png' alt='Sigmind logo' style='width: 80px; height: 80px;'>"
    //            "</td>"
    //            "<td style='width:58.9219%;text-align:right;'>"
    //            "<table style='width:80%;margin-left:calc(20%);'>"
    //            "<tbody>"
    //            "<tr>"
    //            "<td style='width:75.3785%;'>"
    //            "<div style='text-align:left;'><strong><span style='font-size:16px;'>info@sigmind.ai</span></strong></div>"
    //            "</td>"
    //            "<td style='width:24.2231%;'>"
    //            "<img src='https://img.icons8.com/material-outlined/25/000000/important-mail.png'>"
    //            "</td>"
    //            "</tr>"
    //            "<tr>"
    //            "<td style='width:75.3785%;'>"
    //            "<div style='text-align:left;'><strong>+</strong><span style='font-size:16px;'><strong>8801747078074"
    //            "<br>"
    //            "</strong></span></div>"
    //            "</td>"
    //            "<td style='width:24.2231%;'>"
    //            "<img src='https://img.icons8.com/windows/25/000000/phone.png'>"
    //            "</td>"
    //            "</tr>"
    //            "<tr>"
    //            "<td style='width:75.3785%;'>"
    //            "<div style='text-align:left;'><span style='font-size:16px;'><strong>#1, Software Technology Park, Janata Tawer, Kawran Bazar, Dhaka-1215&nbsp;</strong>"
    //            "<br>"
    //            "</span></div>"
    //            "</td>"
    //            "<td style='width:24.2231%;'>"
    //            "<img src='https://img.icons8.com/material-outlined/25/000000/address.png'>"
    //            "</td>"
    //            "</tr>"
    //            "<tr>"
    //            "<td style='width:75.3785%;'>"
    //            "<div style='text-align:left;'><strong><span style='font-size:16px;'>www.sigmind.ai</span></strong></div>"
    //            "</td>"
    //            "<td style='width:24.2231%;'>"
    //            "<img src='https://img.icons8.com/ios-glyphs/25/000000/internet.png'>"
    //            "</td>"
    //            "</tr>"
    //            "</tbody>"
    //            "</table>"
    //            "</td>"
    //            "</tr>"
    //            "</tbody>"
    //            "</table>"
    //            "<hr>"
    //            "<h1 style='text-align:center;'><span style='color:rgb(0,0,0);font-size:20px;'>Recognition Report Generate Time</span></h1>"
    //            "<table border='1' style='width:100%;'>"
    //            "<tbody>"
    //            "<tr>"
    //            "<td style='width:50.0000%;'>"
    //            "<div style='text-align:center;'><strong><span style='font-size:16px;'>From: "+from+"</span></strong></div>"
    //            "</td>"
    //            "<td style='width:50.0000%;'>"
    //            "<div style='text-align:center;'><strong><span style='font-size:16px;'>To: "+to+"&nbsp;</span></strong></div>"
    //            "</td>"
    //            "</tr>"
    //            "</tbody>"
    //            "</table>"
    //            "<table border='1' style='width:100%;'>"
    //            "<tbody>"
    //            "<tr>"
    //            "<td style='width:25%;text-align:center;background-color:rgb(174,215,255);'><strong><span style='font-size: 14px;'>A1</span></strong></td>"
    //            "<td style='width:25%;background-color:rgb(174,215,255);'>"
    //            "<div style='text-align:center;'><strong><span style='font-size: 14px;'>B1</span></strong></div>"
    //            "</td>"
    //            "<td style='width:25%;background-color:rgb(174,215,255);'>"
    //            "<div style='text-align:center;'><strong><span style='font-size: 14px;'>C1</span></strong></div>"
    //            "</td>"
    //            "<td style='width:25%;background-color:rgb(174,215,255);'>"
    //            "<div style='text-align:center;'><strong><span style='font-size: 14px;'>D1</span></strong></div>"
    //            "</td>"
    //            "</tr>"
    //            "<tr>"
    //            "<td style='width:25%;background-color:rgb(239,239,239);'>"
    //            "<div style='text-align:center;'><strong><span style='font-size: 14px;'>A2</span></strong></div>"
    //            "</td>"
    //            "<td style='width:25%;background-color:rgb(239,239,239);'>"
    //            "<div style='text-align:center;'><strong><span style='font-size: 14px;'>B2</span></strong></div>"
    //            "</td>"
    //            "<td style='width:25%;background-color:rgb(239,239,239);'>"
    //            "<div style='text-align:center;'><strong><span style='font-size: 14px;'>C2</span></strong></div>"
    //            "</td>"
    //            "<td style='width:25%;background-color:rgb(239,239,239);'>"
    //            "<div style='text-align:center;'><strong><span style='font-size: 14px;'>D2</span></strong></div>"
    //            "</td>"
    //            "</tr>"
    //            "</tbody>"
    //            "</table>"
    //            "<p>"
    //            "<br>"
    //            "</p>"
    //            "</div>"
    //            "<div style='position:relative;'><em>"
    //            "<p style='position:fixed;bottom:0;width:100%;text-align:right;'>Powered by Sigmindd</p>"
    //            "</em></div>"
    //            "</body>"
    //            "</html>"
    //            ;

    header_details =
            "<html>"
            "<head>"

            " </head>"
            "<body>"
            "<h4 align='center'>Sigmind.AI</h4>"
            "<h5 align='center'>Software Technology Park, Kawran Bazar, Dhaka-1215</h5>"
            "<h6 align='center'>Bangladesh</h6>"
            //            "<p>"
            //            "Report generation time: "+curr_date+", "+curr_time+
            //            "</p>"
            //            "<p>"
            //            "From: "+from+"&nbsp; &nbsp;"+"To: "+to+
            //            "</p>"
            //            "<p>"
            //            "To &nbsp; &nbsp; &nbsp;: "+to_time_g+
            //            "</p>"
            "<br/>"
            //            "<table id='t01'>"
            //            "<tr>"
            //            "<th >Name</th>"
            //            "<th>Time stamp</th>"
            //            "<th >Confidence</th>"
            //            "<th >Source</th>"
            //            "<th >Image</th>"
            //            "</tr>"

            ;
    if(connectionDB()){
        QSqlQuery query;
        if(radio_present_button == true){

            header_details.append(
                        "<p>"
                        "Report generation time: "+curr_date+", "+curr_time+
                        "</p>"
                        "<p>"
                        "Present list"
                        "</p>"
                        );

            header_details.append(
                        "<!-- Codes by HTML.am -->"

                        "<!-- CSS Code -->"
                        "<style type='text/css' scoped>"
                        "table.GeneratedTable {"
                        "width:100%;"
                        "background-color:#FFFFFF;"
                        "border-collapse:collapse;border-width:1px;"
                        "border-color:#336600;"
                        "border-style:solid;"
                        "color:#009900;"
                        "}"

                        "table.GeneratedTable td, table.GeneratedTable th {"
                        "border-width:1px;"
                        "border-color:#336600;"
                        "border-style:solid;"
                        "padding:3px;"
                        "}"

                        "table.GeneratedTable thead {"
                        "background-color:#CCFF99;"
                        "}"
                        "</style>"

                        "<!-- HTML Code -->"
                        "<table class='GeneratedTable'>"
                        "<thead>"
                        "<tr>"
                        "<th>Name</th>"
                        "<th>Time stamp</th>"
                        "<th>Confidence</th>"
                        "<th>Source</th>"
                        "<th>Image</th>"
                        "</tr>"
                        "</thead>"
                        "<tbody>"
                        );

            //            QString from_to_query =
            //                    "SELECT "
            //                    "name, savePath, date_format(date_time, '%Y-%m-%d %H:%i:%s') as Time_stamp, confidence, video_src "
            //                    "FROM "
            //                    "sigmind_ai.FeedAddFace "
            //                    "WHERE "
            //                    "(date_time BETWEEN :from AND :to) "
            //                    "and "
            //                    "id IN (SELECT "
            //                    "MAX(Id) "
            //                    "FROM "
            //                    "FeedAddFace "
            //                    "GROUP BY name)"
            //                    ";"
            //                    ;
            //if(query.exec("select * from data")){//qDebug() << "Table found";}else{//qDebug() << "Table not found" << endl;}
            QString from_to_query;
            from_to_query = "select name, savePath, Time_stamp, confidence, video_src from data "
                            "where "
                            "strftime('%Y-%m-%d %H:%M:%S', Time_stamp) >= :from "
                            "and "
                            "strftime('%Y-%m-%d %H:%M:%S', Time_stamp) <= :to"
                            ";"
                    ;
            //from_to_query = "select name, savePath, Time_stamp, confidence, video_src from data WHERE (Time_stamp BETWEEN '2019-12-14 18:45:05' AND '2019-12-19 11:58:29');";
            query.prepare(from_to_query);
            query.bindValue(":from", from);
            query.bindValue(":to", to);

            ui->tableView_faces_show->setColumnCount(5);
            QStringList colmname;
            colmname << "Name" << "Path" << "Time" << "Confidence" << "Source";
            ui->tableView_faces_show->setHorizontalHeaderLabels(colmname);
            ui->tableView_faces_show->setRowCount(0);

            if(query.exec()){
                //qDebug() << "Done query " << query.lastQuery() << endl;
                while(query.next()){
                    QSqlQuery pre;
                    if(pre.exec("select name from ADD_FACE;"))
                    {
                        QString nameF = query.value(0).toString();
                        QString path = query.value(1).toString();
                        QString time = query.value(2).toString();
                        int con_int = query.value(3).toInt();QString con = QString::number(con_int);
                        QString src = query.value(4).toString();

                        while(pre.next()){

                            QString nameA = pre.value(0).toString();

                            if(QString::compare(nameF, nameA, Qt::CaseInsensitive) == 0){
                                ////qDebug() << nameF << " dldld " << nameA << endl;
                                model->setQuery(pre);
                                int i = ui->tableView_faces_show->rowCount();

                                ui->tableView_faces_show->insertRow(i);
                                ui->tableView_faces_show->setItem(i, 0, new QTableWidgetItem(nameF));
                                ui->tableView_faces_show->setItem(i, 1, new QTableWidgetItem(path));
                                ui->tableView_faces_show->setItem(i, 2, new QTableWidgetItem(time));
                                ui->tableView_faces_show->setItem(i, 3, new QTableWidgetItem(con));
                                ui->tableView_faces_show->setItem(i, 4, new QTableWidgetItem(src));
                                header_details.append(
                                            "<tr>"
                                            "<td>"+nameF+"</td>"
                                                         "<td>"+time+"</td>"
                                                                     "<td>"+con+"</td>"
                                                                                "<td>"+src+"</td>"
                                                                                           "<td>"
                                                                                           "<img src='"+path+"' width='56' height='30'>"
                                                                                                             "</td>"
                                                                                                             "</tr>"
                                            );
                            }
                        }
                    }
                }
            }else {
                //qDebug() << "Not query " << query.lastQuery() << endl;
            }


            ////qDebug() << "Helo q2" << endl;
            //            QString qs =
            //                    "create temporary table uniqeObject SELECT "
            //                    "* "
            //                    "FROM "
            //                    "FeedAddFace "
            //                    "WHERE "
            //                    "(date_time BETWEEN :from AND :to) "
            //                    "and "
            //                    "(Id IN (SELECT "
            //                    "MAX(Id) "
            //                    "FROM "
            //                    "FeedAddFace "
            //                    "GROUP BY name));"
            //                    ;

            //            query.prepare(qs);
            //            query.bindValue(":from", from_date_time_st);
            //            query.bindValue(":to", to_date_time_st);
            //            if(query.exec()){//qDebug() << "temp table" << endl;}

            //            QString from_to_query =
            //                    "SELECT "
            //                    "ADD_FACE.name, "
            //                    "ADD_FACE.phone, "
            //                    "ADD_FACE.address, "
            //                    "uniqeObject.date_time, "
            //                    "ADD_FACE.image_path "
            //                    "FROM "
            //                    "ADD_FACE "
            //                    "inner JOIN "
            //                    "uniqeObject ON ADD_FACE.name = uniqeObject.name;"
            //                    ;
            //            query.prepare(from_to_query);

            //            ui->tableView_faces_show->setColumnCount(5);
            //            QStringList colmname;
            //            colmname << "Name" << "Phone number" << "Address" << "Time stamp" << "Image path";
            //            ui->tableView_faces_show->setHorizontalHeaderLabels(colmname);
            //            ui->tableView_faces_show->setRowCount(0);

            //            if(query.exec()){
            //                ////qDebug() << "Helo q1" << endl;
            //                model->setQuery(query);
            //                while(query.next()){
            //                    QString name = query.value(0).toString();
            //                    QString phone = query.value(1).toString();
            //                    QString address = query.value(2).toString();
            //                    QString time = query.value(3).toString();
            //                    QString path = query.value(4).toString();

            //                    int i = ui->tableView_faces_show->rowCount();

            //                    ui->tableView_faces_show->insertRow(i);
            //                    ui->tableView_faces_show->setItem(i, 0, new QTableWidgetItem(name));
            //                    ui->tableView_faces_show->setItem(i, 1, new QTableWidgetItem(phone));
            //                    ui->tableView_faces_show->setItem(i, 2, new QTableWidgetItem(address));
            //                    ui->tableView_faces_show->setItem(i, 3, new QTableWidgetItem(time));
            //                    ui->tableView_faces_show->setItem(i, 4, new QTableWidgetItem(path));

            //                }

            //                ui->tableView_faces_show->verticalHeader()->hide();

            //            }
            //            query.exec("drop table uniqeObject;");
        }else if(radio_absent_button == true){
            header_details.append(
                        "<p>"
                        "Report generation time: "+curr_date+", "+curr_time+
                        "</p>"
                        "<p>"
                        "Absent list"
                        "</p>"
                        );

            header_details.append(
                        "<!-- Codes by HTML.am -->"

                        "<!-- CSS Code -->"
                        "<style type='text/css' scoped>"
                        "table.GeneratedTable {"
                        "width:100%;"
                        "background-color:#FFFFFF;"
                        "border-collapse:collapse;border-width:1px;"
                        "border-color:#336600;"
                        "border-style:solid;"
                        "color:#009900;"
                        "}"

                        "table.GeneratedTable td, table.GeneratedTable th {"
                        "border-width:1px;"
                        "border-color:#336600;"
                        "border-style:solid;"
                        "padding:3px;"
                        "}"

                        "table.GeneratedTable thead {"
                        "background-color:#CCFF99;"
                        "}"
                        "</style>"

                        "<!-- HTML Code -->"
                        "<table class='GeneratedTable'>"
                        "<thead>"
                        "<tr>"
                        "<th>Name</th>"
                        "<th>Position</th>"
                        "<th>Phone</th>"
                        "<th>Address</th>"
                        "<th>Image</th>"
                        "</tr>"
                        "</thead>"
                        "<tbody>"
                        );
            QSqlQuery pre;
            QString prq = "select name, position, address, phone, image_path from ADD_FACE;";
            if(pre.exec(prq)){
                while(pre.next()){

                    QString nameA = pre.value(0).toString();
                    QString position = pre.value(1).toString();
                    QString address = pre.value(2).toString();
                    QString phone = pre.value(3).toString();
                    QString image_path = pre.value(4).toString();
                    bool flag = false;

                    //                    QString from_to_query =
                    //                            "SELECT "
                    //                            "name, savePath, date_format(date_time, '%Y-%m-%d %H:%i:%s') as Time_stamp, confidence, video_src "
                    //                            "FROM "
                    //                            "sigmind_ai.FeedAddFace "
                    //                            "WHERE "
                    //                            "(date_time BETWEEN :from AND :to) "
                    //                            "and "
                    //                            "id IN (SELECT "
                    //                            "MAX(Id) "
                    //                            "FROM "
                    //                            "FeedAddFace "
                    //                            "GROUP BY name)"
                    //                            ";"
                    //                            ;
                    QString from_to_query;
                    from_to_query = "select name, savePath, Time_stamp, confidence, video_src from data "
                                    "where "
                                    "strftime('%Y-%m-%d %H:%M:%S', Time_stamp) >= :from "
                                    "and "
                                    "strftime('%Y-%m-%d %H:%M:%S', Time_stamp) <= :to"
                                    ";"
                            ;

                    query.prepare(from_to_query);
                    query.bindValue(":from", from);
                    query.bindValue(":to", to);

                    if(query.exec()){
                        while(query.next()){

                            {
                                QString nameF = query.value(0).toString();
                                QString path = query.value(1).toString();
                                QString time = query.value(2).toString();
                                QString con = query.value(3).toString();
                                QString src = query.value(4).toString();

                                if(QString::compare(nameF, nameA, Qt::CaseInsensitive) == 0){
                                    ////qDebug() << nameF << " dldld " << nameA << endl;
                                    flag = true;
                                }
                            }
                        }
                    }
                    if(flag == false){
                        model->setQuery(query);

                        int i = ui->tableView_faces_show->rowCount();

                        ui->tableView_faces_show->insertRow(i);
                        ui->tableView_faces_show->setItem(i, 0, new QTableWidgetItem(nameA));
                        ui->tableView_faces_show->setItem(i, 1, new QTableWidgetItem(position));
                        ui->tableView_faces_show->setItem(i, 2, new QTableWidgetItem(address));
                        ui->tableView_faces_show->setItem(i, 3, new QTableWidgetItem(phone));
                        ui->tableView_faces_show->setItem(i, 4, new QTableWidgetItem(image_path));
                        header_details.append(
                                    "<tr>"
                                    "<td>"+nameA+"</td>"
                                                 "<td>"+position+"</td>"
                                                                 "<td>"+address+"</td>"
                                                                                "<td>"+phone+"</td>"
                                                                                             "<td>"
                                                                                             "<img src='"+image_path+"' width='56' height='30'>"
                                                                                                                     "</td>"
                                                                                                                     "</tr>"
                                    );
                    }
                }
            }

        }else {
            header_details.append(
                        "<p>"
                        "Report generation time: "+curr_date+", "+curr_time+
                        "</p>"
                        );
            header_details.append(
                        "<!-- Codes by HTML.am -->"

                        "<!-- CSS Code -->"
                        "<style type='text/css' scoped>"
                        "table.GeneratedTable {"
                        "width:100%;"
                        "background-color:#FFFFFF;"
                        "border-collapse:collapse;border-width:1px;"
                        "border-color:#336600;"
                        "border-style:solid;"
                        "color:#009900;"
                        "}"

                        "table.GeneratedTable td, table.GeneratedTable th {"
                        "border-width:1px;"
                        "border-color:#336600;"
                        "border-style:solid;"
                        "padding:3px;"
                        "}"

                        "table.GeneratedTable thead {"
                        "background-color:#CCFF99;"
                        "}"
                        "</style>"

                        "<!-- HTML Code -->"
                        "<table class='GeneratedTable'>"
                        "<thead>"
                        "<tr>"
                        "<th>Name</th>"
                        "<th>Time stamp</th>"
                        "<th>Confidence</th>"
                        "<th>Source</th>"
                        "<th>Image</th>"
                        "</tr>"
                        "</thead>"
                        "<tbody>"
                        );

            //            QString from_to_query =
            //                    "SELECT "
            //                    "name, savePath, date_format(date_time, '%Y-%m-%d %H:%i:%s') as Time_stamp, confidence, video_src "
            //                    "FROM "
            //                    "sigmind_ai.FeedAddFace "
            //                    "WHERE "
            //                    "(date_time BETWEEN :from AND :to) "
            //                    "and "
            //                    "id IN (SELECT "
            //                    "MAX(Id) "
            //                    "FROM "
            //                    "FeedAddFace "
            //                    "GROUP BY name)"
            //                    ";"
            //                    ;
            QString from_to_query;
            from_to_query = "select name, savePath, Time_stamp, confidence, video_src from data "
                            "where "
                            "strftime('%Y-%m-%d %H:%M:%S', Time_stamp) >= :from "
                            "and "
                            "strftime('%Y-%m-%d %H:%M:%S', Time_stamp) <= :to"
                            ";"
                    ;
            query.prepare(from_to_query);
            query.bindValue(":from", from);
            query.bindValue(":to", to);

            ui->tableView_faces_show->setColumnCount(5);
            QStringList colmname;
            colmname << "Name" << "Sava Path" << "Time stamp" << "Confidence" << "Video Source";
            ui->tableView_faces_show->setHorizontalHeaderLabels(colmname);
            ui->tableView_faces_show->setRowCount(0);

            if(query.exec()){
                model->setQuery(query);

                while(query.next()){
                    QString name = query.value(0).toString();
                    QString save_path = query.value(1).toString();
                    QString time_stamp = query.value(2).toString();
                    int con = query.value(3).toInt();
                    int video_src = query.value(4).toInt();

                    int i = ui->tableView_faces_show->rowCount();

                    ui->tableView_faces_show->insertRow(i);
                    ui->tableView_faces_show->setItem(i, 0, new QTableWidgetItem(name));
                    ui->tableView_faces_show->setItem(i, 1, new QTableWidgetItem(save_path));
                    ui->tableView_faces_show->setItem(i, 2, new QTableWidgetItem(time_stamp));
                    ui->tableView_faces_show->setItem(i, 3, new QTableWidgetItem(QString::number(con)));
                    ui->tableView_faces_show->setItem(i, 4, new QTableWidgetItem(QString::number(video_src)));
                    header_details.append(
                                "<tr>"
                                "<td>"+name+"</td>"
                                            "<td>"+time_stamp+"</td>"
                                                              "<td>"+QString::number(con)+"</td>"
                                                                                          "<td>"+QString::number(video_src)+"</td>"
                                                                                                                            "<td>"
                                                                                                                            "<img src='"+save_path+"' width='56' height='30'>"
                                                                                                                                                   "</td>"
                                                                                                                                                   "</tr>"
                                );
                }

            }

            //        if(query.exec()){
            //            model->setQuery(query);

            //            while(query.next()){
            //                QString name = query.value(0).toString();
            //                QString save_path = query.value(1).toString();
            //                QString time_stamp = query.value(2).toString();
            //                int con = query.value(3).toInt();
            //                int video_src = query.value(4).toInt();

            //                int i = ui->tableView_faces_show->rowCount();

            //                ui->tableView_faces_show->insertRow(i);
            //                ui->tableView_faces_show->setItem(i, 0, new QTableWidgetItem(name));
            //                ui->tableView_faces_show->setItem(i, 1, new QTableWidgetItem(save_path));
            //                ui->tableView_faces_show->setItem(i, 2, new QTableWidgetItem(time_stamp));
            //                ui->tableView_faces_show->setItem(i, 3, new QTableWidgetItem(QString::number(con)));
            //                ui->tableView_faces_show->setItem(i, 4, new QTableWidgetItem(QString::number(video_src)));

            //            }

            //            ui->tableView_faces_show->verticalHeader()->hide();
            //            ui->tableView_faces_show->setModel(model);
        }
        header_details.append(
                    //                        "</table>"
                    "</tbody>"
                    "</table>"
                    );
    }
}

void ReportGenerateFromtoTo::on_pushButton_reset_clicked()
{
    resetAllInfo();
}

void ReportGenerateFromtoTo::on_pushButton_generate_clicked()
{
    delete model;
    model = new QSqlQueryModel();

    ui->tableView_faces_show->clear();
    ui->tableView_faces_show->reset();

    ui->tableView_faces_show->setRowCount(0);

    QDateTime from_date_time_edit = ui->dateTimeEdit_from->dateTime();
    QString from_date_time_st = from_date_time_edit.toString("yyyy-MM-dd hh:mm:ss");
    from_date_time_st = encodeBanglishToEnglishDT(from_date_time_st);

    QDateTime to_date_time_edit = ui->dateTimeEdit_to->dateTime();
    QString to_date_time_st = to_date_time_edit.toString("yyyy-MM-dd hh:mm:ss");
    to_date_time_st = encodeBanglishToEnglishDT(to_date_time_st);

    from = from_date_time_st;
    to = to_date_time_st;

    if(ui->radioButton_present->isChecked()){
        radio_present_button = true;
    }else if(ui->radioButton_absent->isChecked()){
        radio_absent_button = true;
    }

    dataRetrive();

    if(model->rowCount() < 1){
        ui->pushButton_export_as_pdf->setEnabled(false);
    }else {
        ui->pushButton_export_as_pdf->setEnabled(true);
    }
}

void ReportGenerateFromtoTo::on_pushButton_export_as_pdf_clicked()
{


    if(connectionDB()){
        QSqlQuery query;
        //        QString from_to_query =
        //                "SELECT "
        //                "name, savePath, date_format(date_time, '%Y-%m-%d %H:%i:%s') as Time_stamp, confidence, video_src "
        //                "FROM "
        //                "sigmind_ai.FeedAddFace "
        //                "WHERE "
        //                "(date_time BETWEEN :from AND :to) "
        //                "and "
        //                "id IN (SELECT "
        //                "MAX(Id) "
        //                "FROM "
        //                "FeedAddFace "
        //                "GROUP BY name)"
        //                ";"
        //                ;
        QString from_to_query;
        from_to_query = "select name, savePath, Time_stamp, confidence, video_src from data "
                        "where "
                        "strftime('%Y-%m-%d %H:%M:%S', Time_stamp) >= :from "
                        "and "
                        "strftime('%Y-%m-%d %H:%M:%S', Time_stamp) <= :to"
                        ";"
                ;
        query.prepare(from_to_query);
        query.bindValue(":from", from);
        query.bindValue(":to", to);

        if(query.exec()){
            while(query.next()){
                QString name = query.value(0).toString();
                QString image_path = query.value(1).toString();
                QString date_time = query.value(2).toString();
                double confidence = query.value(3).toDouble();
                int video_source = query.value(4).toInt();


            }

        }
    }
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    //        printer = new QPrinter(QPrinter::PrinterResolution);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setPaperSize(QPrinter::A4);
    printer->setOutputFileName(fileName);
    printer->setColorMode(QPrinter::Color);

    //        doc = new QTextDocument();
    doc->setHtml(header_details);
    doc->setPageSize(printer->pageRect().size()); // This is necessary if you want to hide the page number
    doc->print(printer);

    resetAllInfo();
}
