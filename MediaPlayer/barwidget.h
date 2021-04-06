#ifndef BARWIDGET_H
#define BARWIDGET_H

#include <QWidget>

class BarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BarWidget(QWidget *parent = nullptr);
    void assignRanges(QList<QList<int>> msRanges);

    QList<QList<int>> msRanges;
    QList<int> source_ids;
    QWidget *parent;
    int source_id;

    QList<int> lcs;
    QList<int> frs;
    QList<int> ods;
    int checkbox_FR = 0;
    int checkbox_LC = 0;
    int checkbox_OD = 0;

signals:

public slots:

private:
    int maptoRange(int);
protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // BARWIDGET_H
