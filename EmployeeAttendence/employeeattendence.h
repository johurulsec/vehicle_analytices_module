#ifndef EMPLOYEEATTENDENCE_H
#define EMPLOYEEATTENDENCE_H

#include <QDialog>
#include <DatabaseConnection/sqlite_connection.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTextCodec>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include<QDebug>

namespace Ui {
class EmployeeAttendence;
}

class EmployeeAttendence : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeAttendence(QWidget *parent = nullptr);
    ~EmployeeAttendence();
    QString encodeBanglishToEnglishDT(QString);
    void ResetAll();
    QString timeDifference(QString, QString);

private slots:
    void on_pushButton_reset_clicked();

    void on_pushButton_generate_clicked();

    void on_pushButton_export_as_pdf_clicked();

private:
    Ui::EmployeeAttendence *ui;
    QString from, to;
    QPrinter *printer;
    QTextDocument *doc;
};

#endif // EMPLOYEEATTENDENCE_H
