#include "calculatetimeperobject.h"
#include "ui_calculatetimeperobject.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

CalculateTimePerObject::CalculateTimePerObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalculateTimePerObject)
{
    ui->setupUi(this);
    check_box = new int[32];
    resetAll();
}

CalculateTimePerObject::~CalculateTimePerObject()
{
    delete ui;
    delete [] check_box;
    check_box = NULL;
}
void CalculateTimePerObject::unCheckCheckBox(){
    ui->checkBox_1->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);
    ui->checkBox_8->setChecked(false);
    ui->checkBox_9->setChecked(false);
    ui->checkBox_10->setChecked(false);
    ui->checkBox_11->setChecked(false);
    ui->checkBox_12->setChecked(false);
    ui->checkBox_13->setChecked(false);
    ui->checkBox_14->setChecked(false);
    ui->checkBox_15->setChecked(false);
    ui->checkBox_16->setChecked(false);
    ui->checkBox_17->setChecked(false);
    ui->checkBox_18->setChecked(false);
    ui->checkBox_19->setChecked(false);
    ui->checkBox_20->setChecked(false);
    ui->checkBox_21->setChecked(false);
    ui->checkBox_22->setChecked(false);
    ui->checkBox_23->setChecked(false);
    ui->checkBox_24->setChecked(false);
    ui->checkBox_25->setChecked(false);
    ui->checkBox_26->setChecked(false);
    ui->checkBox_27->setChecked(false);
    ui->checkBox_28->setChecked(false);
    ui->checkBox_29->setChecked(false);
    ui->checkBox_30->setChecked(false);
    ui->checkBox_31->setChecked(false);
    ui->checkBox_32->setChecked(false);
}
void CalculateTimePerObject::resetAll()
{

    ui->tableWidget_calculate->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidget_calculate->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_calculate->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_calculate->setFocusPolicy(Qt::NoFocus);

    ui->dateTimeEdit_from->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit_two->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit_from->setDateTime(QDateTime::fromString( "2000-01-01 00:00:00", "yyyy-MM-dd hh:mm::ss" ));
    ui->dateTimeEdit_two->setDateTime(QDateTime::fromString( "2000-01-01 00:00:00", "yyyy-MM-dd hh:mm::ss" ));


    unCheckCheckBox();
    ui->pushButton_export_as_pdf->setEnabled(false);

    for (int i = 0; i < 32; i++){
        check_box[i] = 0;
    }

    ui->checkBox_1->setEnabled(true);
    ui->checkBox_2->setEnabled(true);
    ui->checkBox_3->setEnabled(true);
    ui->checkBox_4->setEnabled(true);
    ui->checkBox_5->setEnabled(true);
    ui->checkBox_6->setEnabled(true);
    ui->checkBox_7->setEnabled(true);
    ui->checkBox_8->setEnabled(true);
    ui->checkBox_9->setEnabled(true);
    ui->checkBox_10->setEnabled(true);
    ui->checkBox_11->setEnabled(true);
    ui->checkBox_12->setEnabled(true);
    ui->checkBox_13->setEnabled(true);
    ui->checkBox_14->setEnabled(true);
    ui->checkBox_15->setEnabled(true);
    ui->checkBox_16->setEnabled(true);
    ui->checkBox_17->setEnabled(true);
    ui->checkBox_18->setEnabled(true);
    ui->checkBox_19->setEnabled(true);
    ui->checkBox_20->setEnabled(true);
    ui->checkBox_21->setEnabled(true);
    ui->checkBox_22->setEnabled(true);
    ui->checkBox_23->setEnabled(true);
    ui->checkBox_24->setEnabled(true);
    ui->checkBox_25->setEnabled(true);
    ui->checkBox_26->setEnabled(true);
    ui->checkBox_27->setEnabled(true);
    ui->checkBox_28->setEnabled(true);
    ui->checkBox_29->setEnabled(true);
    ui->checkBox_30->setEnabled(true);
    ui->checkBox_31->setEnabled(true);
    ui->checkBox_32->setEnabled(true);

    QPalette pal = ui->checkBox_1->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_1->setAutoFillBackground(true);
    ui->checkBox_1->setPalette(pal);
    ui->checkBox_1->update();

    pal = ui->checkBox_2->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_2->setAutoFillBackground(true);
    ui->checkBox_2->setPalette(pal);
    ui->checkBox_2->update();

    pal = ui->checkBox_3->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_3->setAutoFillBackground(true);
    ui->checkBox_3->setPalette(pal);
    ui->checkBox_3->update();

    pal = ui->checkBox_4->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_4->setAutoFillBackground(true);
    ui->checkBox_4->setPalette(pal);
    ui->checkBox_4->update();

    pal = ui->checkBox_5->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_5->setAutoFillBackground(true);
    ui->checkBox_5->setPalette(pal);
    ui->checkBox_5->update();

    pal = ui->checkBox_6->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_6->setAutoFillBackground(true);
    ui->checkBox_6->setPalette(pal);
    ui->checkBox_6->update();

    pal = ui->checkBox_7->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_7->setAutoFillBackground(true);
    ui->checkBox_7->setPalette(pal);
    ui->checkBox_7->update();

    pal = ui->checkBox_8->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_8->setAutoFillBackground(true);
    ui->checkBox_8->setPalette(pal);
    ui->checkBox_8->update();

    pal = ui->checkBox_9->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_9->setAutoFillBackground(true);
    ui->checkBox_9->setPalette(pal);
    ui->checkBox_9->update();

    pal = ui->checkBox_10->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_10->setAutoFillBackground(true);
    ui->checkBox_10->setPalette(pal);
    ui->checkBox_10->update();

    pal = ui->checkBox_11->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_11->setAutoFillBackground(true);
    ui->checkBox_11->setPalette(pal);
    ui->checkBox_11->update();

    pal = ui->checkBox_12->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_12->setAutoFillBackground(true);
    ui->checkBox_12->setPalette(pal);
    ui->checkBox_12->update();

    pal = ui->checkBox_13->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_13->setAutoFillBackground(true);
    ui->checkBox_13->setPalette(pal);
    ui->checkBox_13->update();

    pal = ui->checkBox_14->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_14->setAutoFillBackground(true);
    ui->checkBox_14->setPalette(pal);
    ui->checkBox_14->update();

    pal = ui->checkBox_15->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_15->setAutoFillBackground(true);
    ui->checkBox_15->setPalette(pal);
    ui->checkBox_15->update();

    pal = ui->checkBox_16->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_16->setAutoFillBackground(true);
    ui->checkBox_16->setPalette(pal);
    ui->checkBox_16->update();

    pal = ui->checkBox_17->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_17->setAutoFillBackground(true);
    ui->checkBox_17->setPalette(pal);
    ui->checkBox_17->update();

    pal = ui->checkBox_18->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_18->setAutoFillBackground(true);
    ui->checkBox_18->setPalette(pal);
    ui->checkBox_18->update();

    pal = ui->checkBox_19->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_19->setAutoFillBackground(true);
    ui->checkBox_19->setPalette(pal);
    ui->checkBox_19->update();

    pal = ui->checkBox_20->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_20->setAutoFillBackground(true);
    ui->checkBox_20->setPalette(pal);
    ui->checkBox_20->update();

    pal = ui->checkBox_21->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_21->setAutoFillBackground(true);
    ui->checkBox_21->setPalette(pal);
    ui->checkBox_21->update();

    pal = ui->checkBox_22->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_22->setAutoFillBackground(true);
    ui->checkBox_22->setPalette(pal);
    ui->checkBox_22->update();

    pal = ui->checkBox_23->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_23->setAutoFillBackground(true);
    ui->checkBox_23->setPalette(pal);
    ui->checkBox_23->update();

    pal = ui->checkBox_24->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_24->setAutoFillBackground(true);
    ui->checkBox_24->setPalette(pal);
    ui->checkBox_24->update();

    pal = ui->checkBox_25->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_25->setAutoFillBackground(true);
    ui->checkBox_25->setPalette(pal);
    ui->checkBox_25->update();

    pal = ui->checkBox_26->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_26->setAutoFillBackground(true);
    ui->checkBox_26->setPalette(pal);
    ui->checkBox_26->update();

    pal = ui->checkBox_27->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_27->setAutoFillBackground(true);
    ui->checkBox_27->setPalette(pal);
    ui->checkBox_27->update();

    pal = ui->checkBox_28->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_28->setAutoFillBackground(true);
    ui->checkBox_28->setPalette(pal);
    ui->checkBox_28->update();

    pal = ui->checkBox_29->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_29->setAutoFillBackground(true);
    ui->checkBox_29->setPalette(pal);
    ui->checkBox_29->update();

    pal = ui->checkBox_30->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_30->setAutoFillBackground(true);
    ui->checkBox_30->setPalette(pal);
    ui->checkBox_30->update();

    pal = ui->checkBox_31->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_31->setAutoFillBackground(true);
    ui->checkBox_31->setPalette(pal);
    ui->checkBox_31->update();

    pal = ui->checkBox_32->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->checkBox_32->setAutoFillBackground(true);
    ui->checkBox_32->setPalette(pal);
    ui->checkBox_32->update();


    pal = ui->pushButton_select_in->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->pushButton_select_in->setAutoFillBackground(true);
    ui->pushButton_select_in->setPalette(pal);
    ui->pushButton_select_in->update();

    pal = ui->pushButton_select_out->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui->pushButton_select_out->setAutoFillBackground(true);
    ui->pushButton_select_out->setPalette(pal);
    ui->pushButton_select_out->update();

    from = "";
    to = "";

    ui->pushButton_generate->setEnabled(false);


    ui->tableWidget_calculate->setColumnCount(4);
    QStringList colmname;
    colmname << "Name" << "Date" << "Confidence" << "Video Source";
    ui->tableWidget_calculate->setHorizontalHeaderLabels(colmname);
    ui->tableWidget_calculate->setRowCount(0);

    if(connectionDB()){
        QString present_que =
                "select name, strftime('%Y-%m-%d', date_time) as to_date, confidence, video_src from FeedAddFace "
                "WHERE "
                "strftime('%Y-%m-%d', date_time) = DATE('now') "
                "and "
                "id IN (SELECT "
                "MAX(Id) "
                "FROM "
                "FeedAddFace "
                "GROUP BY name)"
                ";"
                ;
        QSqlQuery presen_qu_e;
        if(presen_qu_e.exec(present_que)){
            while(presen_qu_e.next()){
                QString name = presen_qu_e.value(0).toString();
                QString date = presen_qu_e.value(1).toString();
                QString confidence = presen_qu_e.value(2).toString();
                QString video_src = presen_qu_e.value(3).toString();
                //QString image_path = presen_qu_e.value(4).toString();


                int i = ui->tableWidget_calculate->rowCount();

                ui->tableWidget_calculate->insertRow(i);
                ui->tableWidget_calculate->setItem(i, 0, new QTableWidgetItem(name));
                ui->tableWidget_calculate->setItem(i, 1, new QTableWidgetItem(date));
                ui->tableWidget_calculate->setItem(i, 2, new QTableWidgetItem(confidence));
                ui->tableWidget_calculate->setItem(i, 3, new QTableWidgetItem(video_src));
                //ui->tableWidget_calculate->setItem(i, 4, new QTableWidgetItem(image_path));
            }
            ui->tableWidget_calculate->horizontalHeader()->setVisible(true);
            ui->tableWidget_calculate->verticalHeader()->hide();
        }
    }

}
void CalculateTimePerObject::selectIn(){

    if(ui->checkBox_1->isChecked()){
        //        QPalette pal = ui->checkBox_1->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_1->setAutoFillBackground(true);
        //        ui->checkBox_1->setPalette(pal);
        //        ui->checkBox_1->update();
        check_box[0] = 1;
    }
    if(ui->checkBox_2->isChecked()){
        //        QPalette pal = ui->checkBox_2->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_2->setAutoFillBackground(true);
        //        ui->checkBox_2->setPalette(pal);
        //        ui->checkBox_2->update();


        check_box[1] = 1;
    }
    if(ui->checkBox_3->isChecked()){
        //        QPalette pal = ui->checkBox_3->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_3->setAutoFillBackground(true);
        //        ui->checkBox_3->setPalette(pal);
        //        ui->checkBox_3->update();


        check_box[2] = 1;
    }
    if(ui->checkBox_4->isChecked()){
        //        QPalette pal = ui->checkBox_4->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_4->setAutoFillBackground(true);
        //        ui->checkBox_4->setPalette(pal);
        //        ui->checkBox_4->update();


        check_box[3] = 1;
    }
    if(ui->checkBox_5->isChecked()){
        //        QPalette pal = ui->checkBox_5->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_5->setAutoFillBackground(true);
        //        ui->checkBox_5->setPalette(pal);
        //        ui->checkBox_5->update();
        check_box[4] = 1;
    }
    if(ui->checkBox_6->isChecked()){
        //        QPalette pal = ui->checkBox_6->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_6->setAutoFillBackground(true);
        //        ui->checkBox_6->setPalette(pal);
        //        ui->checkBox_6->update();
        check_box[5] = 1;
    }
    if(ui->checkBox_7->isChecked()){
        //        QPalette pal = ui->checkBox_7->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_7->setAutoFillBackground(true);
        //        ui->checkBox_7->setPalette(pal);
        //        ui->checkBox_7->update();
        check_box[6] = 1;
    }
    if(ui->checkBox_8->isChecked()){
        //        QPalette pal = ui->checkBox_8->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_8->setAutoFillBackground(true);
        //        ui->checkBox_8->setPalette(pal);
        //        ui->checkBox_8->update();
        check_box[7] = 1;
    }
    if(ui->checkBox_9->isChecked()){
        //        QPalette pal = ui->checkBox_9->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_9->setAutoFillBackground(true);
        //        ui->checkBox_9->setPalette(pal);
        //        ui->checkBox_9->update();
        check_box[8] = 1;
    }
    if(ui->checkBox_10->isChecked()){
        //        QPalette pal = ui->checkBox_10->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_10->setAutoFillBackground(true);
        //        ui->checkBox_10->setPalette(pal);
        //        ui->checkBox_10->update();
        check_box[9] = 1;
    }
    if(ui->checkBox_11->isChecked()){
        //        QPalette pal = ui->checkBox_11->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_11->setAutoFillBackground(true);
        //        ui->checkBox_11->setPalette(pal);
        //        ui->checkBox_11->update();
        check_box[10] = 1;
    }
    if(ui->checkBox_12->isChecked()){
        //        QPalette pal = ui->checkBox_12->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_12->setAutoFillBackground(true);
        //        ui->checkBox_12->setPalette(pal);
        //        ui->checkBox_12->update();
        check_box[11] = 1;
    }
    if(ui->checkBox_13->isChecked()){
        //        QPalette pal = ui->checkBox_13->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_13->setAutoFillBackground(true);
        //        ui->checkBox_13->setPalette(pal);
        //        ui->checkBox_13->update();
        check_box[12] = 1;
    }
    if(ui->checkBox_14->isChecked()){
        //        QPalette pal = ui->checkBox_14->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_14->setAutoFillBackground(true);
        //        ui->checkBox_14->setPalette(pal);
        //        ui->checkBox_14->update();
        check_box[13] = 1;
    }
    if(ui->checkBox_15->isChecked()){
        //        QPalette pal = ui->checkBox_15->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_15->setAutoFillBackground(true);
        //        ui->checkBox_15->setPalette(pal);
        //        ui->checkBox_15->update();
        check_box[14] = 1;
    }
    if(ui->checkBox_16->isChecked()){
        //        QPalette pal = ui->checkBox_16->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_16->setAutoFillBackground(true);
        //        ui->checkBox_16->setPalette(pal);
        //        ui->checkBox_16->update();
        check_box[15] = 1;
    }
    if(ui->checkBox_17->isChecked()){
        //        QPalette pal = ui->checkBox_17->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_17->setAutoFillBackground(true);
        //        ui->checkBox_17->setPalette(pal);
        //        ui->checkBox_17->update();
        check_box[16] = 1;
    }
    if(ui->checkBox_18->isChecked()){
        //        QPalette pal = ui->checkBox_18->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_18->setAutoFillBackground(true);
        //        ui->checkBox_18->setPalette(pal);
        //        ui->checkBox_18->update();
        check_box[17] = 1;
    }
    if(ui->checkBox_19->isChecked()){
        //        QPalette pal = ui->checkBox_19->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_19->setAutoFillBackground(true);
        //        ui->checkBox_19->setPalette(pal);
        //        ui->checkBox_19->update();
        check_box[18] = 1;
    }
    if(ui->checkBox_20->isChecked()){
        //        QPalette pal = ui->checkBox_20->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_20->setAutoFillBackground(true);
        //        ui->checkBox_20->setPalette(pal);
        //        ui->checkBox_20->update();
        check_box[19] = 1;
    }
    if(ui->checkBox_21->isChecked()){
        //        QPalette pal = ui->checkBox_21->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_21->setAutoFillBackground(true);
        //        ui->checkBox_21->setPalette(pal);
        //        ui->checkBox_21->update();
        check_box[20] = 1;
    }
    if(ui->checkBox_22->isChecked()){
        //        QPalette pal = ui->checkBox_22->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_22->setAutoFillBackground(true);
        //        ui->checkBox_22->setPalette(pal);
        //        ui->checkBox_22->update();
        check_box[21] = 1;
    }
    if(ui->checkBox_23->isChecked()){
        //        QPalette pal = ui->checkBox_23->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_23->setAutoFillBackground(true);
        //        ui->checkBox_23->setPalette(pal);
        //        ui->checkBox_23->update();
        check_box[22] = 1;
    }
    if(ui->checkBox_24->isChecked()){
        //        QPalette pal = ui->checkBox_24->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_24->setAutoFillBackground(true);
        //        ui->checkBox_24->setPalette(pal);
        //        ui->checkBox_24->update();
        check_box[23] = 1;
    }
    if(ui->checkBox_25->isChecked()){
        //        QPalette pal = ui->checkBox_25->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_25->setAutoFillBackground(true);
        //        ui->checkBox_25->setPalette(pal);
        //        ui->checkBox_25->update();
        check_box[24] = 1;
    }
    if(ui->checkBox_26->isChecked()){
        //        QPalette pal = ui->checkBox_26->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_26->setAutoFillBackground(true);
        //        ui->checkBox_26->setPalette(pal);
        //        ui->checkBox_26->update();
        check_box[25] = 1;
    }
    if(ui->checkBox_27->isChecked()){
        //        QPalette pal = ui->checkBox_27->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_27->setAutoFillBackground(true);
        //        ui->checkBox_27->setPalette(pal);
        //        ui->checkBox_27->update();
        check_box[26] = 1;
    }
    if(ui->checkBox_28->isChecked()){
        //        QPalette pal = ui->checkBox_28->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_28->setAutoFillBackground(true);
        //        ui->checkBox_28->setPalette(pal);
        //        ui->checkBox_28->update();
        check_box[27] = 1;
    }
    if(ui->checkBox_29->isChecked()){
        check_box[28] = 1;
        //        QPalette pal = ui->checkBox_29->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_29->setAutoFillBackground(true);
        //        ui->checkBox_29->setPalette(pal);
        //        ui->checkBox_29->update();
    }
    if(ui->checkBox_30->isChecked()){
        check_box[29] = 1;
        //        QPalette pal = ui->checkBox_30->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_30->setAutoFillBackground(true);
        //        ui->checkBox_30->setPalette(pal);
        //        ui->checkBox_30->update();
    }
    if(ui->checkBox_31->isChecked()){
        check_box[30] = 1;
        //        QPalette pal = ui->checkBox_31->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_31->setAutoFillBackground(true);
        //        ui->checkBox_31->setPalette(pal);
        //        ui->checkBox_31->update();
    }
    if(ui->checkBox_32->isChecked()){
        check_box[31] = 1;
        //        QPalette pal = ui->checkBox_32->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::blue));
        //        ui->checkBox_32->setAutoFillBackground(true);
        //        ui->checkBox_32->setPalette(pal);
        //        ui->checkBox_32->update();
    }


    for (int i = 0; i < 32; i++){
        if(check_box[i] == 1){
            QPalette pal;
            switch(i){
            case 0:
                pal = ui->checkBox_1->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_1->setAutoFillBackground(true);
                ui->checkBox_1->setPalette(pal);
                ui->checkBox_1->update();
                ui->checkBox_1->setEnabled(false);
                break;
            case 1:
                pal = ui->checkBox_2->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_2->setAutoFillBackground(true);
                ui->checkBox_2->setPalette(pal);
                ui->checkBox_2->update();
                ui->checkBox_2->setEnabled(false);
                break;
            case 2:
                pal = ui->checkBox_3->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_3->setAutoFillBackground(true);
                ui->checkBox_3->setPalette(pal);
                ui->checkBox_3->update();
                ui->checkBox_3->setEnabled(false);
                break;
            case 3:
                pal = ui->checkBox_4->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_4->setAutoFillBackground(true);
                ui->checkBox_4->setPalette(pal);
                ui->checkBox_4->update();
                ui->checkBox_4->setEnabled(false);
                break;
            case 4:
                pal = ui->checkBox_5->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_5->setAutoFillBackground(true);
                ui->checkBox_5->setPalette(pal);
                ui->checkBox_5->update();
                ui->checkBox_5->setEnabled(false);
                break;
            case 5:
                pal = ui->checkBox_6->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_6->setAutoFillBackground(true);
                ui->checkBox_6->setPalette(pal);
                ui->checkBox_6->update();
                ui->checkBox_6->setEnabled(false);
                break;
            case 6:
                pal = ui->checkBox_7->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_7->setAutoFillBackground(true);
                ui->checkBox_7->setPalette(pal);
                ui->checkBox_7->update();
                ui->checkBox_7->setEnabled(false);
                break;
            case 7:
                pal = ui->checkBox_8->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_8->setAutoFillBackground(true);
                ui->checkBox_8->setPalette(pal);
                ui->checkBox_8->update();
                ui->checkBox_8->setEnabled(false);
                break;
            case 8:
                pal = ui->checkBox_9->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_9->setAutoFillBackground(true);
                ui->checkBox_9->setPalette(pal);
                ui->checkBox_9->update();
                ui->checkBox_9->setEnabled(false);
                break;
            case 9:
                pal = ui->checkBox_10->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_10->setAutoFillBackground(true);
                ui->checkBox_10->setPalette(pal);
                ui->checkBox_10->update();
                ui->checkBox_10->setEnabled(false);
                break;
            case 10:
                pal = ui->checkBox_11->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_11->setAutoFillBackground(true);
                ui->checkBox_11->setPalette(pal);
                ui->checkBox_11->update();
                ui->checkBox_11->setEnabled(false);
                break;
            case 11:
                pal = ui->checkBox_12->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_12->setAutoFillBackground(true);
                ui->checkBox_12->setPalette(pal);
                ui->checkBox_12->update();
                ui->checkBox_12->setEnabled(false);
                break;
            case 12:
                pal = ui->checkBox_13->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_13->setAutoFillBackground(true);
                ui->checkBox_13->setPalette(pal);
                ui->checkBox_13->update();
                ui->checkBox_13->setEnabled(false);
                break;
            case 13:
                pal = ui->checkBox_14->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_14->setAutoFillBackground(true);
                ui->checkBox_14->setPalette(pal);
                ui->checkBox_14->update();
                ui->checkBox_14->setEnabled(false);
                ui->checkBox_14->setEnabled(false);
                break;
            case 14:
                pal = ui->checkBox_15->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_15->setAutoFillBackground(true);
                ui->checkBox_15->setPalette(pal);
                ui->checkBox_15->update();
                ui->checkBox_15->setEnabled(false);
                break;
            case 15:
                pal = ui->checkBox_16->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_16->setAutoFillBackground(true);
                ui->checkBox_16->setPalette(pal);
                ui->checkBox_16->update();
                ui->checkBox_16->setEnabled(false);
                break;
            case 16:
                pal = ui->checkBox_17->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_17->setAutoFillBackground(true);
                ui->checkBox_17->setPalette(pal);
                ui->checkBox_17->update();
                ui->checkBox_17->setEnabled(false);
                break;
            case 17:
                pal = ui->checkBox_18->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_18->setAutoFillBackground(true);
                ui->checkBox_18->setPalette(pal);
                ui->checkBox_18->update();
                ui->checkBox_18->setEnabled(false);
                break;
            case 18:
                pal = ui->checkBox_19->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_19->setAutoFillBackground(true);
                ui->checkBox_19->setPalette(pal);
                ui->checkBox_19->update();
                ui->checkBox_19->setEnabled(false);
                break;
            case 19:
                pal = ui->checkBox_20->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_20->setAutoFillBackground(true);
                ui->checkBox_20->setPalette(pal);
                ui->checkBox_20->update();
                ui->checkBox_20->setEnabled(false);
                break;
            case 20:
                pal = ui->checkBox_21->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_21->setAutoFillBackground(true);
                ui->checkBox_21->setPalette(pal);
                ui->checkBox_21->update();
                ui->checkBox_21->setEnabled(false);
                break;
            case 21:
                pal = ui->checkBox_22->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_22->setAutoFillBackground(true);
                ui->checkBox_22->setPalette(pal);
                ui->checkBox_22->update();
                ui->checkBox_22->setEnabled(false);
                break;
            case 22:
                pal = ui->checkBox_23->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_23->setAutoFillBackground(true);
                ui->checkBox_23->setPalette(pal);
                ui->checkBox_23->update();
                ui->checkBox_23->setEnabled(false);
                break;
            case 23:
                pal = ui->checkBox_24->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_24->setAutoFillBackground(true);
                ui->checkBox_24->setPalette(pal);
                ui->checkBox_24->update();
                ui->checkBox_24->setEnabled(false);
                break;
            case 24:
                pal = ui->checkBox_25->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_25->setAutoFillBackground(true);
                ui->checkBox_25->setPalette(pal);
                ui->checkBox_25->update();
                ui->checkBox_25->setEnabled(false);
                break;
            case 25:
                pal = ui->checkBox_26->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_26->setAutoFillBackground(true);
                ui->checkBox_26->setPalette(pal);
                ui->checkBox_26->update();
                ui->checkBox_26->setEnabled(false);
                break;
            case 26:
                pal = ui->checkBox_27->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_27->setAutoFillBackground(true);
                ui->checkBox_27->setPalette(pal);
                ui->checkBox_27->update();
                ui->checkBox_27->setEnabled(false);
                break;
            case 27:
                pal = ui->checkBox_28->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_28->setAutoFillBackground(true);
                ui->checkBox_28->setPalette(pal);
                ui->checkBox_28->update();
                ui->checkBox_28->setEnabled(false);
                break;
            case 28:
                pal = ui->checkBox_29->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_29->setAutoFillBackground(true);
                ui->checkBox_29->setPalette(pal);
                ui->checkBox_29->update();
                ui->checkBox_29->setEnabled(false);
                break;
            case 29:
                pal = ui->checkBox_30->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_30->setAutoFillBackground(true);
                ui->checkBox_30->setPalette(pal);
                ui->checkBox_30->update();
                ui->checkBox_30->setEnabled(false);
                break;
            case 30:
                pal = ui->checkBox_31->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_31->setAutoFillBackground(true);
                ui->checkBox_31->setPalette(pal);
                ui->checkBox_31->update();
                ui->checkBox_31->setEnabled(false);
                break;
            case 31:
                pal = ui->checkBox_32->palette();
                pal.setColor(QPalette::Button, QColor(Qt::blue));
                ui->checkBox_32->setAutoFillBackground(true);
                ui->checkBox_32->setPalette(pal);
                ui->checkBox_32->update();
                ui->checkBox_32->setEnabled(false);
                break;
            }
        }
    }
    unCheckCheckBox();
}
void CalculateTimePerObject::selectOut(){

    if(ui->checkBox_1->isChecked()){
        //        QPalette pal = ui->checkBox_1->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_1->setAutoFillBackground(true);
        //        ui->checkBox_1->setPalette(pal);
        //        ui->checkBox_1->update();
        check_box[0] = 2;
    }
    if(ui->checkBox_2->isChecked()){
        //        QPalette pal = ui->checkBox_2->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_2->setAutoFillBackground(true);
        //        ui->checkBox_2->setPalette(pal);
        //        ui->checkBox_2->update();


        check_box[1] = 2;
    }
    if(ui->checkBox_3->isChecked()){
        //        QPalette pal = ui->checkBox_3->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_3->setAutoFillBackground(true);
        //        ui->checkBox_3->setPalette(pal);
        //        ui->checkBox_3->update();


        check_box[2] = 2;
    }
    if(ui->checkBox_4->isChecked()){
        //        QPalette pal = ui->checkBox_4->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_4->setAutoFillBackground(true);
        //        ui->checkBox_4->setPalette(pal);
        //        ui->checkBox_4->update();


        check_box[3] = 2;
    }
    if(ui->checkBox_5->isChecked()){
        //        QPalette pal = ui->checkBox_5->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_5->setAutoFillBackground(true);
        //        ui->checkBox_5->setPalette(pal);
        //        ui->checkBox_5->update();
        check_box[4] = 2;
    }
    if(ui->checkBox_6->isChecked()){
        //        QPalette pal = ui->checkBox_6->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_6->setAutoFillBackground(true);
        //        ui->checkBox_6->setPalette(pal);
        //        ui->checkBox_6->update();
        check_box[5] = 2;
    }
    if(ui->checkBox_7->isChecked()){
        //        QPalette pal = ui->checkBox_7->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_7->setAutoFillBackground(true);
        //        ui->checkBox_7->setPalette(pal);
        //        ui->checkBox_7->update();
        check_box[6] = 2;
    }
    if(ui->checkBox_8->isChecked()){
        //        QPalette pal = ui->checkBox_8->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_8->setAutoFillBackground(true);
        //        ui->checkBox_8->setPalette(pal);
        //        ui->checkBox_8->update();
        check_box[7] = 2;
    }
    if(ui->checkBox_9->isChecked()){
        //        QPalette pal = ui->checkBox_9->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_9->setAutoFillBackground(true);
        //        ui->checkBox_9->setPalette(pal);
        //        ui->checkBox_9->update();
        check_box[8] = 2;
    }
    if(ui->checkBox_10->isChecked()){
        //        QPalette pal = ui->checkBox_10->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_10->setAutoFillBackground(true);
        //        ui->checkBox_10->setPalette(pal);
        //        ui->checkBox_10->update();
        check_box[9] = 2;
    }
    if(ui->checkBox_11->isChecked()){
        //        QPalette pal = ui->checkBox_11->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_11->setAutoFillBackground(true);
        //        ui->checkBox_11->setPalette(pal);
        //        ui->checkBox_11->update();
        check_box[10] = 2;
    }
    if(ui->checkBox_12->isChecked()){
        //        QPalette pal = ui->checkBox_12->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_12->setAutoFillBackground(true);
        //        ui->checkBox_12->setPalette(pal);
        //        ui->checkBox_12->update();
        check_box[11] = 2;
    }
    if(ui->checkBox_13->isChecked()){
        //        QPalette pal = ui->checkBox_13->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_13->setAutoFillBackground(true);
        //        ui->checkBox_13->setPalette(pal);
        //        ui->checkBox_13->update();
        check_box[12] = 2;
    }
    if(ui->checkBox_14->isChecked()){
        //        QPalette pal = ui->checkBox_14->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_14->setAutoFillBackground(true);
        //        ui->checkBox_14->setPalette(pal);
        //        ui->checkBox_14->update();
        check_box[13] = 2;
    }
    if(ui->checkBox_15->isChecked()){
        //        QPalette pal = ui->checkBox_15->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_15->setAutoFillBackground(true);
        //        ui->checkBox_15->setPalette(pal);
        //        ui->checkBox_15->update();
        check_box[14] = 2;
    }
    if(ui->checkBox_16->isChecked()){
        //        QPalette pal = ui->checkBox_16->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_16->setAutoFillBackground(true);
        //        ui->checkBox_16->setPalette(pal);
        //        ui->checkBox_16->update();
        check_box[15] = 2;
    }
    if(ui->checkBox_17->isChecked()){
        //        QPalette pal = ui->checkBox_17->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_17->setAutoFillBackground(true);
        //        ui->checkBox_17->setPalette(pal);
        //        ui->checkBox_17->update();
        check_box[16] = 2;
    }
    if(ui->checkBox_18->isChecked()){
        //        QPalette pal = ui->checkBox_18->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_18->setAutoFillBackground(true);
        //        ui->checkBox_18->setPalette(pal);
        //        ui->checkBox_18->update();
        check_box[17] = 2;
    }
    if(ui->checkBox_19->isChecked()){
        //        QPalette pal = ui->checkBox_19->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_19->setAutoFillBackground(true);
        //        ui->checkBox_19->setPalette(pal);
        //        ui->checkBox_19->update();
        check_box[18] = 2;
    }
    if(ui->checkBox_20->isChecked()){
        //        QPalette pal = ui->checkBox_20->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_20->setAutoFillBackground(true);
        //        ui->checkBox_20->setPalette(pal);
        //        ui->checkBox_20->update();
        check_box[19] = 2;
    }
    if(ui->checkBox_21->isChecked()){
        //        QPalette pal = ui->checkBox_21->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_21->setAutoFillBackground(true);
        //        ui->checkBox_21->setPalette(pal);
        //        ui->checkBox_21->update();
        check_box[20] = 2;
    }
    if(ui->checkBox_22->isChecked()){
        //        QPalette pal = ui->checkBox_22->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_22->setAutoFillBackground(true);
        //        ui->checkBox_22->setPalette(pal);
        //        ui->checkBox_22->update();
        check_box[21] = 2;
    }
    if(ui->checkBox_23->isChecked()){
        //        QPalette pal = ui->checkBox_23->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_23->setAutoFillBackground(true);
        //        ui->checkBox_23->setPalette(pal);
        //        ui->checkBox_23->update();
        check_box[22] = 2;
    }
    if(ui->checkBox_24->isChecked()){
        //        QPalette pal = ui->checkBox_24->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_24->setAutoFillBackground(true);
        //        ui->checkBox_24->setPalette(pal);
        //        ui->checkBox_24->update();
        check_box[23] = 2;
    }
    if(ui->checkBox_25->isChecked()){
        //        QPalette pal = ui->checkBox_25->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_25->setAutoFillBackground(true);
        //        ui->checkBox_25->setPalette(pal);
        //        ui->checkBox_25->update();
        check_box[24] = 2;
    }
    if(ui->checkBox_26->isChecked()){
        //        QPalette pal = ui->checkBox_26->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_26->setAutoFillBackground(true);
        //        ui->checkBox_26->setPalette(pal);
        //        ui->checkBox_26->update();
        check_box[25] = 2;
    }
    if(ui->checkBox_27->isChecked()){
        //        QPalette pal = ui->checkBox_27->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_27->setAutoFillBackground(true);
        //        ui->checkBox_27->setPalette(pal);
        //        ui->checkBox_27->update();
        check_box[26] = 2;
    }
    if(ui->checkBox_28->isChecked()){
        //        QPalette pal = ui->checkBox_28->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_28->setAutoFillBackground(true);
        //        ui->checkBox_28->setPalette(pal);
        //        ui->checkBox_28->update();
        check_box[27] = 2;
    }
    if(ui->checkBox_29->isChecked()){
        check_box[28] = 2;
        //        QPalette pal = ui->checkBox_29->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_29->setAutoFillBackground(true);
        //        ui->checkBox_29->setPalette(pal);
        //        ui->checkBox_29->update();
    }
    if(ui->checkBox_30->isChecked()){
        check_box[29] = 2;
        //        QPalette pal = ui->checkBox_30->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_30->setAutoFillBackground(true);
        //        ui->checkBox_30->setPalette(pal);
        //        ui->checkBox_30->update();
    }
    if(ui->checkBox_31->isChecked()){
        check_box[30] = 2;
        //        QPalette pal = ui->checkBox_31->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_31->setAutoFillBackground(true);
        //        ui->checkBox_31->setPalette(pal);
        //        ui->checkBox_31->update();
    }
    if(ui->checkBox_32->isChecked()){
        check_box[31] = 2;
        //        QPalette pal = ui->checkBox_32->palette();
        //        pal.setColor(QPalette::Button, QColor(Qt::red));
        //        ui->checkBox_32->setAutoFillBackground(true);
        //        ui->checkBox_32->setPalette(pal);
        //        ui->checkBox_32->update();
    }


    for (int i = 0; i < 32; i++){
        if(check_box[i] == 2){
            QPalette pal;
            switch(i){
            case 0:
                pal = ui->checkBox_1->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_1->setAutoFillBackground(true);
                ui->checkBox_1->setPalette(pal);
                ui->checkBox_1->update();
                ui->checkBox_1->setEnabled(false);
                break;
            case 1:
                pal = ui->checkBox_2->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_2->setAutoFillBackground(true);
                ui->checkBox_2->setPalette(pal);
                ui->checkBox_2->update();
                ui->checkBox_2->setEnabled(false);
                break;
            case 2:
                pal = ui->checkBox_3->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_3->setAutoFillBackground(true);
                ui->checkBox_3->setPalette(pal);
                ui->checkBox_3->update();
                ui->checkBox_3->setEnabled(false);
                break;
            case 3:
                pal = ui->checkBox_4->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_4->setAutoFillBackground(true);
                ui->checkBox_4->setPalette(pal);
                ui->checkBox_4->update();
                ui->checkBox_4->setEnabled(false);
                break;
            case 4:
                pal = ui->checkBox_5->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_5->setAutoFillBackground(true);
                ui->checkBox_5->setPalette(pal);
                ui->checkBox_5->update();
                ui->checkBox_5->setEnabled(false);
                break;
            case 5:
                pal = ui->checkBox_6->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_6->setAutoFillBackground(true);
                ui->checkBox_6->setPalette(pal);
                ui->checkBox_6->update();
                ui->checkBox_6->setEnabled(false);
                break;
            case 6:
                pal = ui->checkBox_7->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_7->setAutoFillBackground(true);
                ui->checkBox_7->setPalette(pal);
                ui->checkBox_7->update();
                ui->checkBox_7->setEnabled(false);
                break;
            case 7:
                pal = ui->checkBox_8->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_8->setAutoFillBackground(true);
                ui->checkBox_8->setPalette(pal);
                ui->checkBox_8->update();
                ui->checkBox_8->setEnabled(false);
                break;
            case 8:
                pal = ui->checkBox_9->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_9->setAutoFillBackground(true);
                ui->checkBox_9->setPalette(pal);
                ui->checkBox_9->update();
                ui->checkBox_9->setEnabled(false);
                break;
            case 9:
                pal = ui->checkBox_10->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_10->setAutoFillBackground(true);
                ui->checkBox_10->setPalette(pal);
                ui->checkBox_10->update();
                ui->checkBox_10->setEnabled(false);
                break;
            case 10:
                pal = ui->checkBox_11->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_11->setAutoFillBackground(true);
                ui->checkBox_11->setPalette(pal);
                ui->checkBox_11->update();
                ui->checkBox_11->setEnabled(false);
                break;
            case 11:
                pal = ui->checkBox_12->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_12->setAutoFillBackground(true);
                ui->checkBox_12->setPalette(pal);
                ui->checkBox_12->update();
                ui->checkBox_12->setEnabled(false);
                break;
            case 12:
                pal = ui->checkBox_13->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_13->setAutoFillBackground(true);
                ui->checkBox_13->setPalette(pal);
                ui->checkBox_13->update();
                ui->checkBox_13->setEnabled(false);
                break;
            case 13:
                pal = ui->checkBox_14->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_14->setAutoFillBackground(true);
                ui->checkBox_14->setPalette(pal);
                ui->checkBox_14->update();
                ui->checkBox_14->setEnabled(false);
                ui->checkBox_14->setEnabled(false);
                break;
            case 14:
                pal = ui->checkBox_15->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_15->setAutoFillBackground(true);
                ui->checkBox_15->setPalette(pal);
                ui->checkBox_15->update();
                ui->checkBox_15->setEnabled(false);
                break;
            case 15:
                pal = ui->checkBox_16->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_16->setAutoFillBackground(true);
                ui->checkBox_16->setPalette(pal);
                ui->checkBox_16->update();
                ui->checkBox_16->setEnabled(false);
                break;
            case 16:
                pal = ui->checkBox_17->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_17->setAutoFillBackground(true);
                ui->checkBox_17->setPalette(pal);
                ui->checkBox_17->update();
                ui->checkBox_17->setEnabled(false);
                break;
            case 17:
                pal = ui->checkBox_18->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_18->setAutoFillBackground(true);
                ui->checkBox_18->setPalette(pal);
                ui->checkBox_18->update();
                ui->checkBox_18->setEnabled(false);
                break;
            case 18:
                pal = ui->checkBox_19->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_19->setAutoFillBackground(true);
                ui->checkBox_19->setPalette(pal);
                ui->checkBox_19->update();
                ui->checkBox_19->setEnabled(false);
                break;
            case 19:
                pal = ui->checkBox_20->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_20->setAutoFillBackground(true);
                ui->checkBox_20->setPalette(pal);
                ui->checkBox_20->update();
                ui->checkBox_20->setEnabled(false);
                break;
            case 20:
                pal = ui->checkBox_21->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_21->setAutoFillBackground(true);
                ui->checkBox_21->setPalette(pal);
                ui->checkBox_21->update();
                ui->checkBox_21->setEnabled(false);
                break;
            case 21:
                pal = ui->checkBox_22->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_22->setAutoFillBackground(true);
                ui->checkBox_22->setPalette(pal);
                ui->checkBox_22->update();
                ui->checkBox_22->setEnabled(false);
                break;
            case 22:
                pal = ui->checkBox_23->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_23->setAutoFillBackground(true);
                ui->checkBox_23->setPalette(pal);
                ui->checkBox_23->update();
                ui->checkBox_23->setEnabled(false);
                break;
            case 23:
                pal = ui->checkBox_24->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_24->setAutoFillBackground(true);
                ui->checkBox_24->setPalette(pal);
                ui->checkBox_24->update();
                ui->checkBox_24->setEnabled(false);
                break;
            case 24:
                pal = ui->checkBox_25->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_25->setAutoFillBackground(true);
                ui->checkBox_25->setPalette(pal);
                ui->checkBox_25->update();
                ui->checkBox_25->setEnabled(false);
                break;
            case 25:
                pal = ui->checkBox_26->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_26->setAutoFillBackground(true);
                ui->checkBox_26->setPalette(pal);
                ui->checkBox_26->update();
                ui->checkBox_26->setEnabled(false);
                break;
            case 26:
                pal = ui->checkBox_27->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_27->setAutoFillBackground(true);
                ui->checkBox_27->setPalette(pal);
                ui->checkBox_27->update();
                ui->checkBox_27->setEnabled(false);
                break;
            case 27:
                pal = ui->checkBox_28->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_28->setAutoFillBackground(true);
                ui->checkBox_28->setPalette(pal);
                ui->checkBox_28->update();
                ui->checkBox_28->setEnabled(false);
                break;
            case 28:
                pal = ui->checkBox_29->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_29->setAutoFillBackground(true);
                ui->checkBox_29->setPalette(pal);
                ui->checkBox_29->update();
                ui->checkBox_29->setEnabled(false);
                break;
            case 29:
                pal = ui->checkBox_30->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_30->setAutoFillBackground(true);
                ui->checkBox_30->setPalette(pal);
                ui->checkBox_30->update();
                ui->checkBox_30->setEnabled(false);
                break;
            case 30:
                pal = ui->checkBox_31->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_31->setAutoFillBackground(true);
                ui->checkBox_31->setPalette(pal);
                ui->checkBox_31->update();
                ui->checkBox_31->setEnabled(false);
                break;
            case 31:
                pal = ui->checkBox_32->palette();
                pal.setColor(QPalette::Button, QColor(Qt::red));
                ui->checkBox_32->setAutoFillBackground(true);
                ui->checkBox_32->setPalette(pal);
                ui->checkBox_32->update();
                ui->checkBox_32->setEnabled(false);
                break;
            }
        }
    }
    unCheckCheckBox();
}
void CalculateTimePerObject::on_pushButton_select_in_clicked()
{
    selectIn();
    for(int i = 0; i < 32; i++){
        if(check_box[i] == 1){
            QPalette pal = ui->pushButton_select_in->palette();
            pal.setColor(QPalette::Button, QColor(Qt::blue));
            ui->pushButton_select_in->setAutoFillBackground(true);
            ui->pushButton_select_in->setPalette(pal);
            ui->pushButton_select_in->update();
            ui->pushButton_generate->setEnabled(true);
            break;
        }
    }

}

void CalculateTimePerObject::on_pushButton_reset_clicked()
{
    resetAll();
}

void CalculateTimePerObject::on_pushButton_select_out_clicked()
{
    selectOut();
    for(int i = 0; i < 32; i++){
        if(check_box[i] == 2){
            QPalette pal = ui->pushButton_select_out->palette();
            pal.setColor(QPalette::Button, QColor(Qt::red));
            ui->pushButton_select_out->setAutoFillBackground(true);
            ui->pushButton_select_out->setPalette(pal);
            ui->pushButton_select_out->update();
            ui->pushButton_generate->setEnabled(true);
            break;
        }
    }
}

void CalculateTimePerObject::on_pushButton_generate_clicked()
{
    QString curr_date = QDate::currentDate().toString("yyyy-MM-dd");
    curr_date = encodeBanglishToEnglishDT(curr_date);
    QString curr_time = QTime::currentTime().toString("h:m:s ap");
    curr_time = encodeBanglishToEnglishDT(curr_time);

    QDateTime from_date_time_edit = ui->dateTimeEdit_from->dateTime();
    QString from_date_time_st = from_date_time_edit.toString("yyyy-MM-dd hh:mm:ss");
    from_date_time_st = encodeBanglishToEnglishDT(from_date_time_st);

    QDateTime to_date_time_edit = ui->dateTimeEdit_two->dateTime();
    QString to_date_time_st = to_date_time_edit.toString("yyyy-MM-dd hh:mm:ss");
    to_date_time_st = encodeBanglishToEnglishDT(to_date_time_st);

    from = from_date_time_st;
    to = to_date_time_st;

    header_details =
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
                "<th>Name</th>"
                "<th>First In Time</th>"
                "<th>Last Out Time</th>"
                "<th>Total Hours</th>"
                "<th>Image</th>"
                "</tr>"
                "</thead>"
                "<tbody>"
                );

    ui->tableWidget_calculate->setColumnCount(4);
    QStringList colmname;
    colmname << "Name" << "First In Time" << "Last Out Time" << "Total Hours";
    ui->tableWidget_calculate->setHorizontalHeaderLabels(colmname);
    ui->tableWidget_calculate->setRowCount(0);



    if(connectionDB()){
        QString present_que =
                "select name, image_path from ADD_FACE"
                ";"
                ;
        QSqlQuery presen_qu_e, qy;
        if(presen_qu_e.exec(present_que)){

            int i = ui->tableWidget_calculate->rowCount();

            while(presen_qu_e.next()){
                QString name = presen_qu_e.value(0).toString();
                QString image_path = presen_qu_e.value(1).toString();
                ////qDebug() << "Name = " << name;

                QString in_view =
                        "create view "+name+"in as "
                                            "select Id, name, strftime('%Y-%m-%d %H:%M:%S', date_time) as first_in_time, savePath, video_src from FeedAddFace where ("
                        ;
                int x = 0;
                for(int i = 0; i < 32; i++){
                    if(check_box[i] == 1){
                        if(x==0){
                            in_view.append(
                                        "video_src = "+QString::number(i)
                                        );
                        }else {
                            in_view.append(
                                        " or video_src = "+QString::number(i)
                                        );
                        }
                        x++;
                    }
                }
                in_view.append(
                            ") and "
                            "name = '"+name+
                            "' and "
                            "strftime('%Y-%m-%d %H:%M:%S', date_time) >= '"+from+
                            "' and "
                            "strftime('%Y-%m-%d %H:%M:%S', date_time) <= '"+to+
                            "';"
                            );
                QSqlQuery ku;
                if(ku.exec(in_view)){
                    ////qDebug() << "Kuuuu ";
                    ////qDebug() <<ku.lastQuery();
                }else{//qDebug() << "kuuu "<<ku.lastError(); //qDebug() <<ku.lastQuery();
                }

                QString out_view =
                        "create view "+name+"out as "
                                            "select Id, name, strftime('%Y-%m-%d %H:%M:%S', date_time) as first_out_time, savePath, video_src from FeedAddFace where ("
                        ;
                int y = 0;
                for(int i = 0; i < 32; i++){
                    if(check_box[i] == 2){
                        if(y==0){
                            out_view.append(
                                        "video_src = "+QString::number(i)
                                        );
                        }else {
                            out_view.append(
                                        " or video_src = "+QString::number(i)
                                        );
                        }
                        y++;
                    }
                }
                out_view.append(
                            ") and "
                            "name = '"+name+
                            "' and "
                            "strftime('%Y-%m-%d %H:%M:%S', date_time) >= '"+from+
                            "' and "
                            "strftime('%Y-%m-%d %H:%M:%S', date_time) <= '"+to+
                            "';"
                            );
                QSqlQuery lu;
                if(lu.exec(out_view)){
                    ////qDebug() << "ulll ";
                    ////qDebug() <<lu.lastQuery();
                }else{//qDebug() << "ull "<<lu.lastError(); //qDebug() <<lu.lastQuery();
                }


                QString F_IN, F_OUT;


                QSqlQuery query_for_first_detected_in_table;
                QString first_detected_in_table =
                        "select Id, name, strftime('%Y-%m-%d %H:%M:%S', first_in_time) as first_in_time from "+name+"in where "
                                                                                                                    "(Id IN (SELECT "
                                                                                                                    "MIN(Id) "
                                                                                                                    "FROM "
                        +name+"in)) limit 1;"
                        ;
                if(query_for_first_detected_in_table.exec(first_detected_in_table)){
                    while(query_for_first_detected_in_table.next()){
                        F_IN = query_for_first_detected_in_table.value(2).toString();
                        ////qDebug() << F_IN;
                    }
                }else{//qDebug() << "First " << query_for_first_detected_in_table.lastError();
                }


                QSqlQuery query_for_first_detected_out_table;
                QString first_detected_out_table =
                        "select Id, name, strftime('%Y-%m-%d %H:%M:%S', first_out_time) as first_out_time from "+name+"out where "
                                                                                                                      "(Id IN (SELECT "
                                                                                                                      "MIN(Id) "
                                                                                                                      "FROM "
                        +name+"out)) limit 1;"
                        ;
                if(query_for_first_detected_out_table.exec(first_detected_out_table)){
                    while(query_for_first_detected_out_table.next()){
                        F_OUT = query_for_first_detected_out_table.value(2).toString();
                        ////qDebug() << F_OUT;
                    }
                }else{//qDebug() << "Second " << query_for_first_detected_out_table.lastError();
                }

                QSqlQuery query_for_first_detected_out_table1;
                QString first_detected_out_table1 =
                        "select Id, name, strftime('%Y-%m-%d %H:%M:%S', first_out_time) as first_out_time from "+name+"out where "
                                                                                                                      "(Id IN (SELECT "
                                                                                                                      "MAX(Id) "
                                                                                                                      "FROM "
                        +name+"out)) limit 1;"
                        ;
                QString lastout_time;
                if(query_for_first_detected_out_table1.exec(first_detected_out_table1)){
                    while(query_for_first_detected_out_table1.next()){
                        lastout_time = query_for_first_detected_out_table1.value(2).toString();
                        ////qDebug() << lastout_time;
                    }
                }else{//qDebug() << "Second " << query_for_first_detected_out_table1.lastError();
                }

                //qDebug() << "Basedul " << F_IN << " " << F_OUT;
                QString tot_time = calculateTime(F_IN, F_OUT, name);


                if(!F_IN.QString::isEmpty() && !F_OUT.QString::isEmpty()){

                    //qDebug() << name << " " << F_IN << " " << lastout_time << " " << tot_time;

                    ui->tableWidget_calculate->insertRow(i);
                    ui->tableWidget_calculate->setItem(i, 0, new QTableWidgetItem(name));
                    ui->tableWidget_calculate->setItem(i, 1, new QTableWidgetItem(F_IN));
                    ui->tableWidget_calculate->setItem(i, 2, new QTableWidgetItem(lastout_time));
                    ui->tableWidget_calculate->setItem(i, 3, new QTableWidgetItem(tot_time));

                    header_details.append(
                                "<tr>"
                                "<td>"+name+"</td>"
                                "<td>"+F_IN+"</td>"
                                "<td>"+lastout_time+"</td>"
                                "<td>"+tot_time+"</td>"
                                "<td>"
                                "<img src='"+image_path+"' width='56' height='50'>"
                                "</td>"
                                "</tr>"
                                );
                }

                if(ku.exec("drop view if exists "+name+"in")){////qDebug() << "namein";
                }else{//qDebug()<< "name in not "<< ku.lastError();
                }
                if(lu.exec("drop view if exists "+name+"out")){////qDebug() << "nameout";
                }else{//qDebug()<< "name out not "<< lu.lastError();
                }
            }
            ui->tableWidget_calculate->horizontalHeader()->setVisible(true);
            ui->tableWidget_calculate->verticalHeader()->hide();
            header_details.append(
                        "</tbody>"
                        "</table>"
                        );
        }
    }
    ui->pushButton_export_as_pdf->setEnabled(true);
}

QString CalculateTimePerObject::calculateTime(QString F_U1, QString F_U2, QString name)
{
    ////qDebug() << F_U1 << " ??? " << F_U2;
    QString timedif = timeDifference(F_U1, F_U2);
    ttime.append(timedif);
    //    if(connectionDB()){
    ////qDebug() << "Good" << endl;

    QString L1, L2, L2F, ag;

    QSqlQuery L1_query;
    QString L1_s =
            "select Id, name, strftime('%Y-%m-%d %H:%M:%S', first_in_time) as L1 from "+name+"in where "
                                                                                             "strftime('%Y-%m-%d %H:%M:%S', first_in_time) > :F_IN and "
                                                                                             "(Id IN (SELECT "
                                                                                             "MAX(Id) "
                                                                                             "FROM "
            +name+"in where strftime('%Y-%m-%d %H:%M:%S', first_in_time) < :LIN)) limit 1;"
            ;
    L1_query.prepare(L1_s);
    L1_query.bindValue(":F_IN", F_U1);
    L1_query.bindValue(":LIN", F_U2);
    if(L1_query.exec()){
        //ebug() << L1_query.lastQuery();
        while(L1_query.next()){
            L1 = L1_query.value(2).toString();
            ////qDebug() <<"L1 = "<< L1;
        }
    }else {
        //ebug() << L1_query.lastError();
    }

    QSqlQuery L2_query;
    QString L2_s =
            "select Id, name, strftime('%Y-%m-%d %H:%M:%S', first_in_time) as L1 from "+name+"in where "
                                                                                             "strftime('%Y-%m-%d %H:%M:%S', first_in_time) > :F_IN and "
                                                                                             "(Id IN (SELECT "
                                                                                             "MIN(Id) "
                                                                                             "FROM "
            +name+"in where strftime('%Y-%m-%d %H:%M:%S', first_in_time) > :LIN)) limit 1;"
            ;
    L2_query.prepare(L2_s);
    L2_query.bindValue(":F_IN", F_U1);
    L2_query.bindValue(":LIN", F_U2);
    if(L2_query.exec()){
        //ebug() << L1_query.lastQuery();
        while(L2_query.next()){
            L2 = L2_query.value(2).toString();
            ////qDebug() <<"L2 = "<< L2;
        }
    }else {
        //ebug() << L1_query.lastError();
    }

    QSqlQuery L2F_query;
    QString L2F_s =
            "select Id, name, strftime('%Y-%m-%d %H:%M:%S', first_out_time) as L2F from "+name+"out where "
                                                                                               "strftime('%Y-%m-%d %H:%M:%S', first_out_time) > :L_IN and "
                                                                                               "(Id IN (SELECT "
                                                                                               "MAX(Id) "
                                                                                               "FROM "
            +name+"out where strftime('%Y-%m-%d %H:%M:%S', first_out_time) < :L2))"
            ;
    L2F_query.prepare(L2F_s);
    L2F_query.bindValue(":L_IN", F_U2);
    L2F_query.bindValue(":L2", L2);
    if(L2F_query.exec()){
        //ebug() << L1_query.lastQuery();
        while(L2F_query.next()){
            L2F = L2F_query.value(2).toString();
            ////qDebug()<<"L2F = " << L2F;
        }
    }else {
        //ebug() << L1_query.lastError();
    }

    QSqlQuery ag_query;
    QString ag_s =
            "select Id, name, strftime('%Y-%m-%d %H:%M:%S', first_out_time) as L2F from "+name+"out where "
                                                                                               "strftime('%Y-%m-%d %H:%M:%S', first_out_time) > :L_IN and "
                                                                                               "(Id IN (SELECT "
                                                                                               "MIN(Id) "
                                                                                               "FROM "
            +name+"out where strftime('%Y-%m-%d %H:%M:%S', first_out_time) > :L2))"
            ;
    ag_query.prepare(ag_s);
    ag_query.bindValue(":L_IN", F_U2);
    ag_query.bindValue(":L2", L2);
    if(ag_query.exec()){
        while(ag_query.next()){
            ag = ag_query.value(2).toString();
            ////qDebug()<<"ag = " << ag;
        }
    }else {
        //ebug() << L1_query.lastError();
    }

    if(L2F<L2){
        calculateTime(L2, ag, name);
    }else {
        //qDebug() << "Done !";
        int total_sec = 0;
        for(int i = 0; i < ttime.size(); i++){
            ////qDebug() << ttime[i];
            QTime t_ = QTime::fromString(ttime[i], "hh:mm:ss");
            int hour = t_.hour();
            int up_h = (hour*3600);
            int min = t_.minute();
            int up_min = (60*min);
            int sec = t_.second()+up_min+up_h;
            total_sec+=sec;
        }
        ttime.clear();
        int g_h = 0, g_m = 0, g_s = 0;
        int vf = total_sec / 3600;
        g_h = vf;
        int vs = total_sec % 3600;
        if(vs>0){
            g_m = vs / 60;
            g_s = vs % 60;
        }
        ////qDebug() << "Total time " <<g_h << ":" << g_m << ":"<<g_s;
        str = QString::number(g_h)+":"+QString::number(g_m)+":"+QString::number(g_s);
        return str;
        //QString tottime = QString::number(g_h)+":"+QString::number(g_m)+":"+QString::number(g_s);
        //return QString::number(g_h)+":"+QString::number(g_m)+":"+QString::number(g_s);
    }

    //    }
    return str;
}
QString CalculateTimePerObject::timeDifference(QString in_time, QString out_time)
{
    QDateTime dt = QDateTime::fromString(in_time, "yyyy-MM-dd hh:mm:ss");
    int in_h = dt.time().hour();
    int in_m = dt.time().minute();
    int in_s = dt.time().second();

    QDateTime dt_ = QDateTime::fromString(out_time, "yyyy-MM-dd hh:mm:ss");
    int out_h = dt_.time().hour();
    int out_m = dt_.time().minute();
    int out_s = dt_.time().second();

    QString t__h, t__m, t__s;

    int t_h = out_h-in_h;
    if(t_h<=9){t__h = '0'+QString::number(t_h);}else{t__h = QString::number(t_h);}
    if(out_m<in_m){out_m+=60;}
    int t_m = out_m-in_m;
    if(t_m<=9){t__m = '0'+QString::number(t_m);}else{t__m = QString::number(t_m);}
    if(out_s<in_s){out_s+=60;}
    int t_s = out_s-in_s;
    if(t_s<=9){t__s = '0'+QString::number(t_s);}else{t__s = QString::number(t_s);}
    //qDebug() << "Tot time = " << t__h+":"+t__m+":"+t__s;
    return t__h+":"+t__m+":"+t__s;
}

QString CalculateTimePerObject::encodeBanglishToEnglishDT(QString data)
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
            ////qDebug()<<encodedString[i]<<" "<<"0";*/
        }


        else if(encodedString[i] == "\u09e7")
        {
            encodedString[i] = '1';
        }

        else if(encodedString[i] == "\u09e8")
        {
            encodedString[i] = '2';
        }

        else if(encodedString[i] == "\u09e9")
        {
            encodedString[i] = '3';
        }

        else if(encodedString[i] == "\u09ea")
        {
            encodedString[i] = '4';
        }

        else if(encodedString[i] == "\u09eb")
        {
            encodedString[i] = '5';
        }

        else if(encodedString[i] == "\u09ec")
        {
            encodedString[i] = '6';
        }

        else if(encodedString[i] == "\u09ed")
        {
            encodedString[i] = '7';
        }

        else if(encodedString[i] == "\u09ee")
        {
            encodedString[i] = '8';
        }

        else if(encodedString[i] == "\u09ef")
        {
            encodedString[i] = '9';
        }

    }
    return encodedString;
}

void CalculateTimePerObject::on_pushButton_export_as_pdf_clicked()
{
    QPrinter *printer = new QPrinter();
    QTextDocument *doc = new QTextDocument();

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

    delete printer;
    delete doc;

    resetAll();
}
