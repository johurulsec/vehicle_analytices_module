#ifndef CALCULATETIMEPEROBJECT_H
#define CALCULATETIMEPEROBJECT_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTextCodec>
#include <DatabaseConnection/sqlite_connection.h>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>

namespace Ui {
class CalculateTimePerObject;
}

class CalculateTimePerObject : public QDialog
{
    Q_OBJECT

public:
    explicit CalculateTimePerObject(QWidget *parent = nullptr);
    ~CalculateTimePerObject();
    void resetAll();
    void selectIn();
    void selectOut();
    void unCheckCheckBox();
    QString encodeBanglishToEnglishDT(QString data);
    QString calculateTime(QString F_U1, QString F_U2, QString name);
    QString timeDifference(QString in_time, QString out_time);
private slots:
    void on_pushButton_select_in_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_select_out_clicked();

    void on_pushButton_generate_clicked();

    void on_pushButton_export_as_pdf_clicked();

private:
    Ui::CalculateTimePerObject *ui;
    int* check_box;
    QString from, to;
    QList<QString> ttime;
    QString header_details;
    QString str;
};

#endif // CALCULATETIMEPEROBJECT_H
