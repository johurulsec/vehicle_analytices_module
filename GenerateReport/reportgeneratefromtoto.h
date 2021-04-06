#ifndef REPORTGENERATEFROMTOTO_H
#define REPORTGENERATEFROMTOTO_H

#include <QDialog>
#include <DatabaseConnection/sqlite_connection.h>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QTextCodec>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include<QDebug>

#include<string>
#include<iostream>
#include<vector>
#include<dirent.h>
#include<sys/stat.h>

using namespace std;

namespace Ui {
class ReportGenerateFromtoTo;
}

class ReportGenerateFromtoTo : public QDialog
{
    Q_OBJECT

public:
    explicit ReportGenerateFromtoTo(QWidget *parent = nullptr);
    ~ReportGenerateFromtoTo();
    void resetAllInfo();
    QString encodeBanglishToEnglishDT(QString);
    void dataRetrive();

    void GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory);
    std::vector<std::string> folderImagePathStore;
    QList<QString>DBImagePathStore;
    QList<QString>absentImagePathStore;
    QList<QString>uniqueNameList;

private slots:
    void on_pushButton_reset_clicked();

    void on_pushButton_generate_clicked();

    void on_pushButton_export_as_pdf_clicked();

private:
    Ui::ReportGenerateFromtoTo *ui;
    QSqlQueryModel *model;
    QString from, to;
    QPrinter *printer;
    QTextDocument *doc;
    int cnt=0;
    int difference;
    bool onlyone = true;
    bool radio_present_button;
    bool radio_absent_button;
    QString header_details;
};

#endif // REPORTGENERATEFROMTOTO_H
