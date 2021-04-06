/********************************************************************************
** Form generated from reading UI file 'imageshowdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGESHOWDIALOG_H
#define UI_IMAGESHOWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ImageShowDialog
{
public:
    QLabel *label_image_show_d;
    QPushButton *pushButton_modify;

    void setupUi(QDialog *ImageShowDialog)
    {
        if (ImageShowDialog->objectName().isEmpty())
            ImageShowDialog->setObjectName(QStringLiteral("ImageShowDialog"));
        ImageShowDialog->resize(163, 164);
        label_image_show_d = new QLabel(ImageShowDialog);
        label_image_show_d->setObjectName(QStringLiteral("label_image_show_d"));
        label_image_show_d->setGeometry(QRect(10, 10, 131, 101));
        pushButton_modify = new QPushButton(ImageShowDialog);
        pushButton_modify->setObjectName(QStringLiteral("pushButton_modify"));
        pushButton_modify->setGeometry(QRect(10, 130, 89, 25));

        retranslateUi(ImageShowDialog);

        QMetaObject::connectSlotsByName(ImageShowDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageShowDialog)
    {
        ImageShowDialog->setWindowTitle(QApplication::translate("ImageShowDialog", "Dialog", Q_NULLPTR));
        label_image_show_d->setText(QString());
        pushButton_modify->setText(QApplication::translate("ImageShowDialog", "Modify", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageShowDialog: public Ui_ImageShowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGESHOWDIALOG_H
