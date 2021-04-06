#ifndef SEARCHBYGIVENIMAGE_H
#define SEARCHBYGIVENIMAGE_H

#include <QDialog>

namespace Ui {
class SearchByGivenImage;
}

class SearchByGivenImage : public QDialog
{
    Q_OBJECT

public:
    explicit SearchByGivenImage(QWidget *parent = 0);
    ~SearchByGivenImage();

private slots:
    void on_pushButton_select_img_clicked();

    void on_pushButton_directory_clicked();

    void on_pushButton_search_clicked();

    void on_comboBox_found_image_list_activated(const QString &arg1);

private:
    Ui::SearchByGivenImage *ui;
    QString given_img, given_dir;

    bool img_file_ch;
    bool dir_ch;
signals:
    void goMainW(QString, QString);
public slots:
    void cathList(QStringList);
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // SEARCHBYGIVENIMAGE_H
