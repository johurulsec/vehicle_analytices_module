/********************************************************************************
** Form generated from reading UI file 'carimgshowdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARIMGSHOWDIALOG_H
#define UI_CARIMGSHOWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_CarImgShowDialog
{
public:
    QLabel *label_car_show;

    void setupUi(QDialog *CarImgShowDialog)
    {
        if (CarImgShowDialog->objectName().isEmpty())
            CarImgShowDialog->setObjectName(QStringLiteral("CarImgShowDialog"));
        CarImgShowDialog->resize(267, 276);
        label_car_show = new QLabel(CarImgShowDialog);
        label_car_show->setObjectName(QStringLiteral("label_car_show"));
        label_car_show->setGeometry(QRect(10, 10, 251, 261));

        retranslateUi(CarImgShowDialog);

        QMetaObject::connectSlotsByName(CarImgShowDialog);
    } // setupUi

    void retranslateUi(QDialog *CarImgShowDialog)
    {
        CarImgShowDialog->setWindowTitle(QApplication::translate("CarImgShowDialog", "Dialog", Q_NULLPTR));
        label_car_show->setText(QApplication::translate("CarImgShowDialog", "Car", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CarImgShowDialog: public Ui_CarImgShowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARIMGSHOWDIALOG_H
