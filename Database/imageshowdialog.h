#ifndef IMAGESHOWDIALOG_H
#define IMAGESHOWDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>


namespace Ui {
class ImageShowDialog;
}

class ImageShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageShowDialog(QWidget *parent = 0);
    ~ImageShowDialog();
    void imageSetIntoLabel(int, QString, QImage);
public slots:



private slots:
    void on_pushButton_modify_clicked();

private:
    Ui::ImageShowDialog *ui;
    QImage image;
    int Id;

signals:
    void modifyDbInfo(int);
};
#endif // IMAGESHOWDIALOG_H
