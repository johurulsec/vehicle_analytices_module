/********************************************************************************
** Form generated from reading UI file 'lpr.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LPR_H
#define UI_LPR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lpr
{
public:
    QGridLayout *gridLayout;
    QLabel *lprLabel;

    void setupUi(QWidget *Lpr)
    {
        if (Lpr->objectName().isEmpty())
            Lpr->setObjectName(QStringLiteral("Lpr"));
        Lpr->resize(190, 140);
        Lpr->setMinimumSize(QSize(190, 140));
        Lpr->setMaximumSize(QSize(160, 160));
        Lpr->setStyleSheet(QStringLiteral("border: 1px solid rgb(100, 200, 200)"));
        gridLayout = new QGridLayout(Lpr);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lprLabel = new QLabel(Lpr);
        lprLabel->setObjectName(QStringLiteral("lprLabel"));
        lprLabel->setMinimumSize(QSize(190, 140));

        gridLayout->addWidget(lprLabel, 0, 0, 1, 1);


        retranslateUi(Lpr);

        QMetaObject::connectSlotsByName(Lpr);
    } // setupUi

    void retranslateUi(QWidget *Lpr)
    {
        Lpr->setWindowTitle(QApplication::translate("Lpr", "Lpr", Q_NULLPTR));
        lprLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Lpr: public Ui_Lpr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LPR_H
