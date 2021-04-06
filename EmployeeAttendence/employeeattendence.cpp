#include "employeeattendence.h"
#include "ui_employeeattendence.h"

EmployeeAttendence::EmployeeAttendence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeAttendence)
{
    ui->setupUi(this);
    ResetAll();
    printer = new QPrinter();
    doc = new QTextDocument();

}

EmployeeAttendence::~EmployeeAttendence()
{
    delete ui;
    delete printer;
    delete doc;
}

QString EmployeeAttendence::encodeBanglishToEnglishDT(QString data)
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

void EmployeeAttendence::ResetAll()
{
    ui->calendarWidget_date->setMinimumDate(QDate::fromString("2000-01-01", "yyyy-MM-dd"));
    ui->calendarWidget_date->setMaximumDate(QDate::fromString("3000-01-01", "yyyy-MM-dd"));
    ui->calendarWidget_date->setSelectedDate(QDate::currentDate());

    ui->timeEdit_to_time->setTime(QTime::fromString("00:00:00", "hh:mm:ss"));
    ui->timeEdit_from_time->setTime(QTime::fromString("00:00:00", "hh:mm:ss"));

    ui->timeEdit_to_time->setDisplayFormat("hh:mm:ss");
    ui->timeEdit_from_time->setDisplayFormat("hh:mm:ss");

    ui->pushButton_export_as_pdf->setEnabled(false);

    ui->tableWidget_employee->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidget_employee->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_employee->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_employee->setFocusPolicy(Qt::NoFocus);

    ui->tableWidget_employee->setRowCount(0);

    if(connectionDB()){
        QSqlQuery query;
        query.exec("drop table if exists first_entry;");
        query.exec("drop table if exists last_entry;");
        QString qu_drop_first_entry =
                "drop view if exists first_entry;"
                ;
        query.exec(qu_drop_first_entry);
        qu_drop_first_entry =
                "create view first_entry as "
                "SELECT name, strftime('%Y-%m-%d %H:%M:%S', date_time) as in_time from FeedAddFace "
                "WHERE (id IN (SELECT MIN(Id) FROM FeedAddFace where strftime('%Y-%m-%d', date_time) = date('now') "
                "GROUP BY name));"
                ;
        query.exec(qu_drop_first_entry);

        QString qu_drop_last_entry =
                "drop view if exists last_entry;"
                ;
        query.exec(qu_drop_last_entry);
        qu_drop_last_entry =
                "create view last_entry as "
                "SELECT name, strftime('%Y-%m-%d %H:%M:%S', date_time) as out_time from FeedAddFace "
                "WHERE (id IN (SELECT MAX(Id) FROM FeedAddFace where strftime('%Y-%m-%d', date_time) = date('now') "
                "GROUP BY name));"
                ;
        query.exec(qu_drop_last_entry);

        QString final_table =
                "select ADD_FACE.name, ADD_FACE.position, ADD_FACE.phone, "
                "strftime('%H:%M:%S', first_entry.in_time) as Entry, "
                "strftime('%H:%M:%S', last_entry.out_time) as Exit "
                "from first_entry "
                "inner join last_entry on first_entry.name = last_entry.name "
                "inner join ADD_FACE on first_entry.name = ADD_FACE.name"
                ";"
                ;
        //query.prepare(final_table);

        if(query.exec(final_table)){
            //qDebug() << "Name = " << "name" << endl;
            ui->tableWidget_employee->setColumnCount(6);
            QStringList colmname;
            colmname << "Name" << "Position" << "Phone" << "In Time" << "Out Time" << "Total Hours";
            ui->tableWidget_employee->setHorizontalHeaderLabels(colmname);
            ui->tableWidget_employee->setRowCount(0);

            while(query.next()){
                QString name = query.value(0).toString();
                QString position = query.value(1).toString();
                QString phone = query.value(2).toString();
                QString in_time = query.value(3).toString();
                QString out_time = query.value(4).toString();
                QString time_diff = timeDifference(in_time, out_time);


                int i = ui->tableWidget_employee->rowCount();

                ui->tableWidget_employee->insertRow(i);
                ui->tableWidget_employee->setItem(i, 0, new QTableWidgetItem(name));
                ui->tableWidget_employee->setItem(i, 1, new QTableWidgetItem(position));
                ui->tableWidget_employee->setItem(i, 2, new QTableWidgetItem(phone));
                ui->tableWidget_employee->setItem(i, 3, new QTableWidgetItem(in_time));
                ui->tableWidget_employee->setItem(i, 4, new QTableWidgetItem(out_time));
                ui->tableWidget_employee->setItem(i, 5, new QTableWidgetItem(time_diff));
            }
        }
    }
}

QString EmployeeAttendence::timeDifference(QString in_time, QString out_time)
{
    QTime in_t = QTime::fromString(in_time, "hh:mm:ss");
    int in_h = in_t.hour();
    int in_m = in_t.minute();
    int in_s = in_t.second();

    QTime out_t = QTime::fromString(out_time, "hh:mm:ss");
    int out_h = out_t.hour();
    int out_m = out_t.minute();
    int out_s = out_t.second();

    int t_h = out_h-in_h;
    if(out_m<in_m){out_m+=60;}
    int t_m = out_m-in_m;
    if(out_s<in_s){out_s+=60;}
    int t_s = out_s-in_s;
    return QString::number(t_h)+":"+QString::number(t_m)+":"+QString::number(t_s);
}

void EmployeeAttendence::on_pushButton_reset_clicked()
{
    ResetAll();
}

void EmployeeAttendence::on_pushButton_generate_clicked()
{
    QString selected_date = ui->calendarWidget_date->selectedDate().toString("yyyy-MM-dd");
    selected_date = encodeBanglishToEnglishDT(selected_date);
    //    //qDebug() << "S " << selected_date << endl;
    QString from_time = ui->timeEdit_from_time->time().toString("hh:mm:ss");
    from_time = encodeBanglishToEnglishDT(from_time);
    //    //qDebug() << "S B" << from_time << endl;
    QString to_time = ui->timeEdit_to_time->time().toString("hh:mm:ss");
    to_time = encodeBanglishToEnglishDT(to_time);

    QString date_from = selected_date+" "+from_time;
    QString date_to = selected_date+" "+to_time;

    from = date_from;
    to = date_to;

    bool flag = false;

    ////qDebug() << selected_date << " helo" << endl;

    if(connectionDB()){
        ////qDebug() << "connectionDB" << endl;

        QSqlQuery query;
        query.exec("drop view if exists first_entry;");
        query.exec("drop view if exists last_entry;");


        QString qu_drop_first_entry =
                "drop table if exists first_entry;"
                ;
        if(query.exec(qu_drop_first_entry)){//qDebug() << "Delete first view";
        }
        qu_drop_first_entry =
                "SELECT name, strftime('%Y-%m-%d %H:%M:%S', date_time) as in_time from FeedAddFace "
                "WHERE (id IN (SELECT MIN(Id) FROM FeedAddFace where strftime('%Y-%m-%d', date_time) = ? "
                "GROUP BY name));"
                ;
        query.prepare(qu_drop_first_entry);
        query.addBindValue(selected_date);
        if(query.exec()){
            //qDebug() << query.lastQuery();
            //qDebug() << "View 1";
            while(query.next()){
                QString name = query.value(0).toString();
                QString in_time = query.value(1).toString();
                //qDebug() <<"b1"<< name << " " << in_time << endl;
                QSqlQuery qu1;
                qu1.exec("create table if not exists "
                         "first_entry "
                         "( "
                         "name varchar(50), "
                         "in_time DATETIME not null"
                         ");");
                QSqlQuery q1;
                q1.prepare("insert into first_entry "
                           "(name, in_time) "
                           "values (:name,:in_time);");
                q1.bindValue(":name", name);
                q1.bindValue(":in_time", in_time);
                if(q1.exec()){
                    //qDebug() << "Insert tab1" << endl;
                }else {
                    //qDebug() <<"B1"<< query.lastError() << endl;
                }
            }
        }else {
            //qDebug() << "Cant create view 1"<< query.lastError() << endl;
        }
    }

    if(connectionDB()){
        QSqlQuery query;
        QString qu_drop_last_entry =
                "drop table if exists last_entry;"
                ;
        if(query.exec(qu_drop_last_entry)){//qDebug() << "delete view 2";
        }

        //selected_date = "2019-12-23";
        QSqlQuery qu;
        QString qu_create_last_entry =
                "SELECT name, strftime('%Y-%m-%d %H:%M:%S', date_time) as out_time from FeedAddFace "
                "WHERE (Id IN (SELECT MAX(Id) FROM FeedAddFace where strftime('%Y-%m-%d', date_time) = ? "
                "GROUP BY name));"
                ;
        qu.prepare(qu_create_last_entry);
        qu.addBindValue(selected_date);
        if(qu.exec()){
            //qDebug() << "View 2";
            while(qu.next()){
                QString name = qu.value(0).toString();
                QString out_time = qu.value(1).toString();
                //qDebug() <<"b2"<< name << " " << out_time << endl;
                QSqlQuery qu1, qu2;
                qu1.exec("create table if not exists "
                         "last_entry "
                         "( "
                         "name varchar(50), "
                         "out_time DATETIME not null"
                         ");");
                qu2.prepare("insert into last_entry "
                            "(name, out_time) "
                            "values (?,?);");
                qu2.addBindValue(name);
                qu2.addBindValue(out_time);
                if(qu2.exec()){
                    //qDebug() << "Insert tab2" << endl;
                }else {
                    //qDebug() <<"B2"<< query.lastError() << endl;
                }
            }
        }else {
            //qDebug() << qu.lastQuery();
            //qDebug() << qu.lastError() << endl;
        }
    }

    if(connectionDB()){

        QSqlQuery query;


        QString final_table =
                "select ADD_FACE.name, ADD_FACE.position, ADD_FACE.phone, "
                "strftime('%H:%M:%S', first_entry.in_time) as Entry, "
                "strftime('%H:%M:%S', last_entry.out_time) as Exit "
                "from first_entry "
                "inner join last_entry on first_entry.name = last_entry.name "
                "inner join ADD_FACE on first_entry.name = ADD_FACE.name "
                "where "
                "strftime('%Y-%m-%d %H:%M:%S', first_entry.in_time) >= ? "
                "and "
                "strftime('%Y-%m-%d %H:%M:%S', last_entry.out_time) <= ?"
                ";"
                ;
        query.prepare(final_table);
        query.addBindValue(date_from);
        query.addBindValue(date_to);
        if(query.exec()){
            //qDebug() << "Hwllops " << endl;
            ui->tableWidget_employee->setColumnCount(6);
            QStringList colmname;
            colmname << "Name" << "Position" << "Phone" << "In Time" << "Out Time" << "Total Hours";
            ui->tableWidget_employee->setHorizontalHeaderLabels(colmname);
            ui->tableWidget_employee->setRowCount(0);

            while(query.next()){

                flag = true;

                QString name = query.value(0).toString();
                QString position = query.value(1).toString();
                QString phone = query.value(2).toString();
                QString in_time = query.value(3).toString();
                QString out_time = query.value(4).toString();
                QString time_diff = timeDifference(in_time, out_time);

                ////qDebug() << name << " ajhala " << time_diff << endl;

                int i = ui->tableWidget_employee->rowCount();

                ui->tableWidget_employee->insertRow(i);
                ui->tableWidget_employee->setItem(i, 0, new QTableWidgetItem(name));
                ui->tableWidget_employee->setItem(i, 1, new QTableWidgetItem(position));
                ui->tableWidget_employee->setItem(i, 2, new QTableWidgetItem(phone));
                ui->tableWidget_employee->setItem(i, 3, new QTableWidgetItem(in_time));
                ui->tableWidget_employee->setItem(i, 4, new QTableWidgetItem(out_time));
                ui->tableWidget_employee->setItem(i, 5, new QTableWidgetItem(time_diff));
            }
        }else {
            //qDebug() << "ab " << query.lastError() << endl;
        }
    }
    ////qDebug() << "Size of row c " << model.rowCount() << endl;
    if(flag == false){
        ui->pushButton_export_as_pdf->setEnabled(false);
    }else{
        ui->pushButton_export_as_pdf->setEnabled(true);
    }
}

void EmployeeAttendence::on_pushButton_export_as_pdf_clicked()
{
    QString curr_date = QDate::currentDate().toString("dd.MM.yyyy");
    curr_date = encodeBanglishToEnglishDT(curr_date);
    QString curr_time = QTime::currentTime().toString("h:m:s ap");
    curr_time = encodeBanglishToEnglishDT(curr_time);

    QString header_details =
            "<html>"
            "<head>"
            "<style>"
            "</style>"
            " </head>"
            "<body>"
            "<h4 align='center'>Sigmin.AI</h4>"
            "<h5 align='center'>Software Technology Park, Kawran Bazar, Dhaka-1215</h5>"
            "<h6 align='center'>Bangladesh</h6>"
            "<p>"
            "Report generation time: "+curr_date+", "+curr_time+
            "</p>"
            "<p>"
            "From: "+from+"&nbsp; &nbsp;"+"To: "+to+
            "</p>"
            "<br/>"
            ;
    header_details.append(
                "<!-- Codes by HTML.am -->"

                "<!-- CSS Code -->"
                "<style type='text/css' scoped>"
                "table.GeneratedTable {"
                "background-color:#FFFFFF;"
                "border-collapse:collapse;border-width:1px;"
                "border-color:#000000;"
                "border-style:solid;"
                "color:	#000000;"
                "align='center'"
                "}"

                "table.GeneratedTable td, table.GeneratedTable th {"
                "border-width:1px;"
                "border-color:#000000;"
                "border-style:solid;"
                "padding:3px;"
                "}"

                "table.GeneratedTable thead {"
                "background-color:#CCFF99;"
                "}"
                "</style>"

                "<!-- HTML Code -->"
                "<table class='GeneratedTable' style='width:100%' align='center'>"
                "<thead>"
                "<tr>"
                "<th>Employee</th>"
                "<th>In Time</th>"
                "<th>Out Time</th>"
                "<th>Total Hours</th>"
                "<th>Image</th>"
                "</tr>"
                "</thead>"
                "<tbody>"
                );

    if(connectionDB()){
        QSqlQuery query;
        QString final_table =
                "select ADD_FACE.name, ADD_FACE.position, ADD_FACE.phone, "
                "strftime('%H:%M:%S', first_entry.in_time) as Entry, "
                "strftime('%H:%M:%S', last_entry.out_time) as Exit, "
                "ADD_FACE.image_path "
                "from first_entry "
                "inner join last_entry on first_entry.name = last_entry.name "
                "inner join ADD_FACE on first_entry.name = ADD_FACE.name "
                "where "
                "strftime('%Y-%m-%d %H:%M:%S', first_entry.in_time) >= :date_from "
                "and "
                "strftime('%Y-%m-%d %H:%M:%S', last_entry.out_time) <= :date_to"
                ";"
                ;
        query.prepare(final_table);
        query.bindValue(":date_from", from);
        query.bindValue(":date_to", to);
        if(query.exec()){
            //qDebug() << "Last value check " << endl;
            while(query.next()){

                QString name = query.value(0).toString();
                QString position = query.value(1).toString();
                QString phone = query.value(2).toString();
                QString in_time = query.value(3).toString();
                QString out_time = query.value(4).toString();
                QString time_diff = timeDifference(in_time, out_time);
                QString image_path = query.value(5).toString();

                header_details.append(
                            "<tr>"
                            "<td>"+name+"<br>"+position+"<br>"+phone+"</td>"
                                                                     "<td>"+in_time+"</td>"
                                                                                    "<td>"+out_time+"</td>"
                                                                                                    "<td>"+time_diff+"</td>"
                                                                                                                     "<td>"
                                                                                                                     "<img src='"+image_path+"' width='56' height='50'>"
                                                                                                                                             "</td>"
                                                                                                                                             "</tr>"
                            );


            }
        }
    }
    header_details.append(
                "</tbody>"
                "</table>"
                );


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

    ResetAll();
}
