#ifndef SHOWFACE_H
#define SHOWFACE_H

#include <QWidget>
#include <ShowFaceInTiles/faceinfo.h>
#include <qgridlayout.h>


namespace Ui {
class ShowFace;
}

class ShowFace : public QWidget
{
    Q_OBJECT

public:
    explicit ShowFace(QWidget *parent = 0);
    ~ShowFace();
    void addFr(QPixmap);

private:
    Ui::ShowFace *ui;
    QList<FaceInfo*> facelist;
    QGridLayout *grid_lay;
    int row_index = 0; int column_index = 0;

};

#endif // SHOWFACE_H
