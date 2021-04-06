/********************************************************************************
** Form generated from reading UI file 'colorobjectwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLOROBJECTWIDGET_H
#define UI_COLOROBJECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_colorObjectWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *comboColor;
    QComboBox *comboObject;

    void setupUi(QWidget *colorObjectWidget)
    {
        if (colorObjectWidget->objectName().isEmpty())
            colorObjectWidget->setObjectName(QStringLiteral("colorObjectWidget"));
        colorObjectWidget->resize(400, 22);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(colorObjectWidget->sizePolicy().hasHeightForWidth());
        colorObjectWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(colorObjectWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboColor = new QComboBox(colorObjectWidget);
        comboColor->setObjectName(QStringLiteral("comboColor"));

        horizontalLayout->addWidget(comboColor);

        comboObject = new QComboBox(colorObjectWidget);
        comboObject->setObjectName(QStringLiteral("comboObject"));

        horizontalLayout->addWidget(comboObject);


        retranslateUi(colorObjectWidget);

        QMetaObject::connectSlotsByName(colorObjectWidget);
    } // setupUi

    void retranslateUi(QWidget *colorObjectWidget)
    {
        colorObjectWidget->setWindowTitle(QApplication::translate("colorObjectWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class colorObjectWidget: public Ui_colorObjectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLOROBJECTWIDGET_H
