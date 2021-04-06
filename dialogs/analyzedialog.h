#ifndef ANALYZEDIALOG_H
#define ANALYZEDIALOG_H

#include <QDialog>
#include <flowlayout.h>
#include <QLabel>
#include <mystyles.h>
#include <components/colorobjectwidget.h>
#include <QDebug>


namespace Ui {
class analyzeDialog;
}

class analyzeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit analyzeDialog(QWidget *parent = 0);
    ~analyzeDialog();

private slots:
    void on_addFaceBut_clicked();

    void on_analyzeBut_clicked();

    void on_cancelBut_clicked();

    void on_addObjectFilter_clicked();

    void on_blackBut_clicked();

private:
    Ui::analyzeDialog *ui;

    FlowLayout *flow;

    QStringList fileNames;
    QString folder;

    bool faces = true;
    bool object = false;
    bool black = false;

    QStringList objects;
    QList<int> colorValues;

    QLabel *lab;

    int colorObjectNumber;

signals:
    void emitAnalyzeFaces(QStringList);
    void emitAnalyzeObject(int, QString);
    void emitAnalyzeBlacklist(QString);

    void emitAnalyzeAll(bool, QStringList, bool, QList<int>, QStringList, bool, QString, int);

public slots:
    void setObjectFilter(int, QString);
    void setColorFilter(int, int);


};

#endif // ANALYZEDIALOG_H
