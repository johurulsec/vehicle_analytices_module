/********************************************************************************
** Form generated from reading UI file 'clusterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLUSTERDIALOG_H
#define UI_CLUSTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_clusterDialog
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QDialog *clusterDialog)
    {
        if (clusterDialog->objectName().isEmpty())
            clusterDialog->setObjectName(QStringLiteral("clusterDialog"));
        clusterDialog->resize(885, 565);
        gridLayout = new QGridLayout(clusterDialog);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(clusterDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 883, 563));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(clusterDialog);

        QMetaObject::connectSlotsByName(clusterDialog);
    } // setupUi

    void retranslateUi(QDialog *clusterDialog)
    {
        clusterDialog->setWindowTitle(QApplication::translate("clusterDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class clusterDialog: public Ui_clusterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLUSTERDIALOG_H
