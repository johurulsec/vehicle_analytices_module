/********************************************************************************
** Form generated from reading UI file 'face.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACE_H
#define UI_FACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Face
{
public:
    QGridLayout *gridLayout;
    QLabel *faceLabel;

    void setupUi(QWidget *Face)
    {
        if (Face->objectName().isEmpty())
            Face->setObjectName(QStringLiteral("Face"));
        Face->resize(160, 160);
        Face->setMinimumSize(QSize(160, 160));
        Face->setMaximumSize(QSize(160, 160));
        Face->setStyleSheet(QStringLiteral("border: 1px solid rgb(100, 200, 200)"));
        gridLayout = new QGridLayout(Face);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        faceLabel = new QLabel(Face);
        faceLabel->setObjectName(QStringLiteral("faceLabel"));
        faceLabel->setMinimumSize(QSize(160, 160));

        gridLayout->addWidget(faceLabel, 0, 0, 1, 1);


        retranslateUi(Face);

        QMetaObject::connectSlotsByName(Face);
    } // setupUi

    void retranslateUi(QWidget *Face)
    {
        Face->setWindowTitle(QApplication::translate("Face", "Face", Q_NULLPTR));
        faceLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Face: public Ui_Face {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACE_H
