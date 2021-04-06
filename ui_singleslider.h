/********************************************************************************
** Form generated from reading UI file 'singleslider.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLESLIDER_H
#define UI_SINGLESLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_singleSlider
{
public:
    QSlider *verticalSlider;
    QLabel *label;

    void setupUi(QWidget *singleSlider)
    {
        if (singleSlider->objectName().isEmpty())
            singleSlider->setObjectName(QStringLiteral("singleSlider"));
        singleSlider->resize(69, 207);
        singleSlider->setMinimumSize(QSize(68, 200));
        verticalSlider = new QSlider(singleSlider);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(30, 10, 16, 160));
        verticalSlider->setOrientation(Qt::Vertical);
        label = new QLabel(singleSlider);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 180, 71, 20));

        retranslateUi(singleSlider);

        QMetaObject::connectSlotsByName(singleSlider);
    } // setupUi

    void retranslateUi(QWidget *singleSlider)
    {
        singleSlider->setWindowTitle(QApplication::translate("singleSlider", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("singleSlider", "slider", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class singleSlider: public Ui_singleSlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLESLIDER_H
