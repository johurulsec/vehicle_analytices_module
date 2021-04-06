#ifndef SINGLESLIDER_H
#define SINGLESLIDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class singleSlider;
}

class singleSlider : public QWidget
{
    Q_OBJECT

public:
    explicit singleSlider(int, double, QWidget *parent = 0);
    ~singleSlider();
    int getSliderValue();
    QString getSourceValue();
    void justReturnSourceIdAndSliderValue();

signals:
     void emitSourceId(int, double);

private:
    Ui::singleSlider *ui;
    int source_id;
};

#endif // SINGLESLIDER_H
