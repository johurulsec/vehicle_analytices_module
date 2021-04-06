#ifndef FACEINFO_H
#define FACEINFO_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class FaceInfo;
}

class FaceInfo : public QWidget
{
    Q_OBJECT

public:
    explicit FaceInfo(QWidget *parent, QPixmap);
    ~FaceInfo();

private:
    Ui::FaceInfo *ui;
};

#endif // FACEINFO_H
