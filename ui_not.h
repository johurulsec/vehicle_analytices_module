/********************************************************************************
** Form generated from reading UI file 'not.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOT_H
#define UI_NOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Not
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *image;
    QSpacerItem *horizontalSpacer_2;
    QLabel *text;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *imageMatch;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *Not)
    {
        if (Not->objectName().isEmpty())
            Not->setObjectName(QStringLiteral("Not"));
        Not->resize(340, 160);
        Not->setMinimumSize(QSize(340, 160));
        Not->setMaximumSize(QSize(400, 160));
        Not->setStyleSheet(QStringLiteral("background-color: rgb(204, 225, 227);"));
        widget = new QWidget(Not);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 341, 161));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer);

        image = new QLabel(widget);
        image->setObjectName(QStringLiteral("image"));

        verticalLayout_2->addWidget(image);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);

        text = new QLabel(widget);
        text->setObjectName(QStringLiteral("text"));
        text->setMinimumSize(QSize(121, 141));

        horizontalLayout->addWidget(text);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_3);

        imageMatch = new QLabel(widget);
        imageMatch->setObjectName(QStringLiteral("imageMatch"));

        verticalLayout->addWidget(imageMatch);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_4);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Not);

        QMetaObject::connectSlotsByName(Not);
    } // setupUi

    void retranslateUi(QWidget *Not)
    {
        Not->setWindowTitle(QApplication::translate("Not", "Form", Q_NULLPTR));
        image->setText(QApplication::translate("Not", "TextLabel", Q_NULLPTR));
        text->setText(QApplication::translate("Not", "TextLabel", Q_NULLPTR));
        imageMatch->setText(QApplication::translate("Not", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Not: public Ui_Not {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOT_H
