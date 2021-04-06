#ifndef VD_FACE_H
#define VD_FACE_H

#include <QWidget>

namespace Ui {
class VD_Face;
}

class VD_Face : public QWidget
{
    Q_OBJECT

public:
    explicit VD_Face(QWidget *parent, QPixmap pic);
    ~VD_Face();

private:
    Ui::VD_Face *ui;
};

#endif // VD_FACE_H
