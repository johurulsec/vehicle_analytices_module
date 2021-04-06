#ifndef PROGRESSBARLOADING_H
#define PROGRESSBARLOADING_H

#include <QDialog>

namespace Ui {
class ProgressBarLoading;
}

class ProgressBarLoading : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressBarLoading(QWidget *parent = 0);
    ~ProgressBarLoading();
    void setProgressBarMaximumValue(float);
    void setProgressBarMinimumValue(float);
    void setMinMax(int, int);
    void resetData();
public slots:
    void setDiffer(int);
    void progressOperation(int);

private:
    Ui::ProgressBarLoading *ui;
    float max;
    float min;
    int differ;
signals:
    void valueChange(int);
};

#endif // PROGRESSBARLOADING_H
