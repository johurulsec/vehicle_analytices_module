#ifndef EMAILBOX_H
#define EMAILBOX_H

#include <QWidget>

namespace Ui {
class EmailBox;
}

class EmailBox : public QWidget
{
    Q_OBJECT

public:
    explicit EmailBox(int, QString, QWidget *parent = 0);
    ~EmailBox();

    int id;
    QString email;

signals:
    void removeBox(int);

    void textChange(int ,QString);

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::EmailBox *ui;
};

#endif // EMAILBOX_H
