#ifndef EULA_H
#define EULA_H

#include <QDialog>

namespace Ui {
class eula;
}

class eula : public QDialog
{
    Q_OBJECT

public:
    explicit eula(QWidget *parent = 0);
    ~eula();

private slots:
    void on_agreeButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::eula *ui;

signals:
    void disagree();
    void agree();
};

#endif // EULA_H
