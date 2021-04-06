#ifndef FACE_H
#define FACE_H

#include <QWidget>
#include <QDateTime>
#include <QMouseEvent>
#include "QDebug"
#include "QThread"

namespace Ui {
class Face;
}

class Face : public QWidget
{
    Q_OBJECT

public:
    explicit Face(QWidget *parent = 0);
    ~Face();

    void setFace(QPixmap , QString, int, int);
    void setObject(QPixmap , QString, int);
    void removeObject(QPixmap pic, QString name, int cam);
    QString getCurrentTime();

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void emitCluster(int);
    void emitPicDB(QPixmap);

private:
    Ui::Face *ui;
    int id;

    void mouseDoubleClickEvent(QMouseEvent*);
    QPixmap pictr;
};

#endif // FACE_H
