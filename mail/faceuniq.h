
//#ifndef FACEUNIQ_H
//#define FACEUNIQ_H

//#include <QWidget>
//#include <QTime>
//#include <QPixmap>
//#include <QDebug>
//#include "DatabaseConnection/sqlite_connection.h"
//#include <QSqlQueryModel>
//#include <QSqlQuery>
//#include "QString"
//#include <QMouseEvent>

//namespace Ui {
//class faceUniq;
//}

//class faceUniq : public QWidget
//{
//    Q_OBJECT

//public:
//    explicit faceUniq(QPixmap, QString, QString, QString, QString, double, QWidget *parent = 0);
//    ~faceUniq();

//private slots:
//    void mousePressEvent(QMouseEvent *e);

//private:
//    Ui::faceUniq *ui;
//    int i=1, cntt=0;
//    QPixmap pictr;

//signals:
//    void emt_uniq_fce(QPixmap);
//};

//#endif // FACEUNIQ_H


#ifndef FACEUNIQ_H
#define FACEUNIQ_H

#include <QWidget>
#include <QTime>
#include <QPixmap>
#include <QDebug>
#include "DatabaseConnection/sqlite_connection.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "QString"
#include <QMouseEvent>
#include <qpainter.h>
#include <QColor>

namespace Ui {
class faceUniq;
}

class faceUniq : public QWidget
{
    Q_OBJECT

public:
    explicit faceUniq(QPixmap, QString, double, int, QString, int, QWidget *parent = 0);
    explicit faceUniq(QPixmap, QString, double, int,  QWidget *parent = 0);
    ~faceUniq();

private slots:
    void mousePressEvent(QMouseEvent *e);

private:
    Ui::faceUniq *ui;
    int i=1, cntt=0;
    QPixmap pictr;

signals:
    void emt_uniq_fce(QPixmap);
};

#endif // FACEUNIQ_H
