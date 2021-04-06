/********************************************************************************
** Form generated from reading UI file 'faceinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEINFO_H
#define UI_FACEINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceInfo
{
public:
    QLabel *label_pic;

    void setupUi(QWidget *FaceInfo)
    {
        if (FaceInfo->objectName().isEmpty())
            FaceInfo->setObjectName(QStringLiteral("FaceInfo"));
        FaceInfo->resize(128, 142);
        FaceInfo->setMinimumSize(QSize(128, 142));
        FaceInfo->setMaximumSize(QSize(128, 142));
        label_pic = new QLabel(FaceInfo);
        label_pic->setObjectName(QStringLiteral("label_pic"));
        label_pic->setGeometry(QRect(12, 10, 101, 121));
        label_pic->setMinimumSize(QSize(100, 120));
        label_pic->setMaximumSize(QSize(128, 142));

        retranslateUi(FaceInfo);

        QMetaObject::connectSlotsByName(FaceInfo);
    } // setupUi

    void retranslateUi(QWidget *FaceInfo)
    {
        FaceInfo->setWindowTitle(QApplication::translate("FaceInfo", "Form", Q_NULLPTR));
        label_pic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FaceInfo: public Ui_FaceInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEINFO_H
