/********************************************************************************
** Form generated from reading UI file 'vd_face.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VD_FACE_H
#define UI_VD_FACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VD_Face
{
public:
    QLabel *faceLabel;

    void setupUi(QWidget *VD_Face)
    {
        if (VD_Face->objectName().isEmpty())
            VD_Face->setObjectName(QStringLiteral("VD_Face"));
        VD_Face->resize(160, 160);
        VD_Face->setMinimumSize(QSize(160, 160));
        VD_Face->setMaximumSize(QSize(160, 160));
        VD_Face->setStyleSheet(QStringLiteral("border: 1px solid rgb(100, 200, 200)"));
        faceLabel = new QLabel(VD_Face);
        faceLabel->setObjectName(QStringLiteral("faceLabel"));
        faceLabel->setGeometry(QRect(0, 0, 160, 160));
        faceLabel->setMinimumSize(QSize(160, 160));
        faceLabel->setMaximumSize(QSize(160, 160));

        retranslateUi(VD_Face);

        QMetaObject::connectSlotsByName(VD_Face);
    } // setupUi

    void retranslateUi(QWidget *VD_Face)
    {
        VD_Face->setWindowTitle(QApplication::translate("VD_Face", "Face", Q_NULLPTR));
        faceLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VD_Face: public Ui_VD_Face {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VD_FACE_H
