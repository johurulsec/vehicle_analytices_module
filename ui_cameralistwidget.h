/********************************************************************************
** Form generated from reading UI file 'cameralistwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERALISTWIDGET_H
#define UI_CAMERALISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cameraListWidget
{
public:
    QLabel *label_cam_list;

    void setupUi(QWidget *cameraListWidget)
    {
        if (cameraListWidget->objectName().isEmpty())
            cameraListWidget->setObjectName(QStringLiteral("cameraListWidget"));
        cameraListWidget->resize(391, 110);
        cameraListWidget->setMinimumSize(QSize(391, 110));
        label_cam_list = new QLabel(cameraListWidget);
        label_cam_list->setObjectName(QStringLiteral("label_cam_list"));
        label_cam_list->setGeometry(QRect(10, 10, 371, 91));
        label_cam_list->setMinimumSize(QSize(371, 91));
        label_cam_list->setStyleSheet(QStringLiteral("background-color:rgb(136, 138, 133)"));

        retranslateUi(cameraListWidget);

        QMetaObject::connectSlotsByName(cameraListWidget);
    } // setupUi

    void retranslateUi(QWidget *cameraListWidget)
    {
        cameraListWidget->setWindowTitle(QApplication::translate("cameraListWidget", "Form", Q_NULLPTR));
        label_cam_list->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class cameraListWidget: public Ui_cameraListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERALISTWIDGET_H
