#ifndef NOT_H
#define NOT_H

#include <QWidget>
#include <QTime>
#include <QPixmap>
#include <QDebug>
#include "DatabaseConnection/sqlite_connection.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "QString"

namespace Ui {
class Not;
}

class Not : public QWidget
{
    Q_OBJECT

public:
    explicit Not(QPixmap, QString, QString, QString, QString, double, QWidget *parent = 0);
    explicit Not(QPixmap, QString, QString, QString, QString, double, QString, int, QWidget *parent = 0);
    explicit Not(QPixmap,QPixmap, QString, QString, QString, QString, double, QString, int, QWidget *parent, QString color);
    //Not(pic, name, camer, confidence, this);
    explicit Not(QPixmap, QString, QString, double, QWidget *parent = 0);
    ~Not();

private:
    Ui::Not *ui;
    int i=1;
};

#endif // NOT_H
