#ifndef SEARCHBYIMAGE_H
#define SEARCHBYIMAGE_H

#include <QDialog>

namespace Ui {
class SearchByImage;
}

class SearchByImage : public QDialog
{
    Q_OBJECT

public:
    explicit SearchByImage(QWidget *parent = 0);
    ~SearchByImage();

private slots:
    void on_pushButton_selectImage_clicked();

    void on_comboBox_get_imagePath_activated(const QString &arg1);

private:
    Ui::SearchByImage *ui;
signals:
    void fromSearchByImg(QString);
public slots:
    void fromMain_Wark(QStringList);
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // SEARCHBYIMAGE_H
