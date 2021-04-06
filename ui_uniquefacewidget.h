/********************************************************************************
** Form generated from reading UI file 'uniquefacewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNIQUEFACEWIDGET_H
#define UI_UNIQUEFACEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_uniqueFaceWidget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *uniqueFaceWidget)
    {
        if (uniqueFaceWidget->objectName().isEmpty())
            uniqueFaceWidget->setObjectName(QStringLiteral("uniqueFaceWidget"));
        uniqueFaceWidget->setWindowModality(Qt::WindowModal);
        uniqueFaceWidget->resize(969, 282);
        uniqueFaceWidget->setMinimumSize(QSize(742, 251));
        uniqueFaceWidget->setStyleSheet(QLatin1String("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(197, 207, 206);"));
        layoutWidget = new QWidget(uniqueFaceWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 951, 271));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(layoutWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setEnabled(true);
        scrollArea->setMinimumSize(QSize(729, 206));
        scrollArea->setMaximumSize(QSize(1000, 250));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 947, 248));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(uniqueFaceWidget);

        QMetaObject::connectSlotsByName(uniqueFaceWidget);
    } // setupUi

    void retranslateUi(QWidget *uniqueFaceWidget)
    {
        uniqueFaceWidget->setWindowTitle(QApplication::translate("uniqueFaceWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class uniqueFaceWidget: public Ui_uniqueFaceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNIQUEFACEWIDGET_H
