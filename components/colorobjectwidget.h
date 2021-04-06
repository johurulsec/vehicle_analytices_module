#ifndef COLOROBJECTWIDGET_H
#define COLOROBJECTWIDGET_H

#include <QWidget>
#include <mystyles.h>

namespace Ui {
class colorObjectWidget;
}

class colorObjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit colorObjectWidget(int,QWidget *parent = 0);
    ~colorObjectWidget();

    int id;

signals:
    void setValuesObject(int, QString);
    void setValuesColor(int, int);

private slots:
    void on_comboColor_currentIndexChanged(int index);

    void on_comboObject_currentIndexChanged(int index);

private:
    Ui::colorObjectWidget *ui;
};

#endif // COLOROBJECTWIDGET_H
