/********************************************************************************
** Form generated from reading UI file 'lpsinglewidg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LPSINGLEWIDG_H
#define UI_LPSINGLEWIDG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LpSingleWidg
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *main_pic;
    QLabel *text;
    QLabel *image;

    void setupUi(QWidget *LpSingleWidg)
    {
        if (LpSingleWidg->objectName().isEmpty())
            LpSingleWidg->setObjectName(QStringLiteral("LpSingleWidg"));
        LpSingleWidg->resize(359, 147);
        LpSingleWidg->setMinimumSize(QSize(359, 147));
        LpSingleWidg->setMaximumSize(QSize(359, 200));
        LpSingleWidg->setStyleSheet(QStringLiteral("background-color: rgb(204, 225, 227);"));
        layoutWidget = new QWidget(LpSingleWidg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 347, 133));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        main_pic = new QLabel(layoutWidget);
        main_pic->setObjectName(QStringLiteral("main_pic"));
        main_pic->setMinimumSize(QSize(111, 131));

        horizontalLayout->addWidget(main_pic);

        text = new QLabel(layoutWidget);
        text->setObjectName(QStringLiteral("text"));
        text->setMinimumSize(QSize(111, 131));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(204, 225, 227, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush2);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush3(QColor(255, 255, 220, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush3);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush2);
        text->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Noto Sans CJK JP"));
        font.setPointSize(9);
        text->setFont(font);

        horizontalLayout->addWidget(text);

        image = new QLabel(layoutWidget);
        image->setObjectName(QStringLiteral("image"));
        image->setMinimumSize(QSize(80, 131));
        image->setMaximumSize(QSize(202, 140));

        horizontalLayout->addWidget(image);


        retranslateUi(LpSingleWidg);

        QMetaObject::connectSlotsByName(LpSingleWidg);
    } // setupUi

    void retranslateUi(QWidget *LpSingleWidg)
    {
        LpSingleWidg->setWindowTitle(QApplication::translate("LpSingleWidg", "Form", Q_NULLPTR));
        main_pic->setText(QString());
        text->setText(QApplication::translate("LpSingleWidg", "Text", Q_NULLPTR));
        image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LpSingleWidg: public Ui_LpSingleWidg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LPSINGLEWIDG_H
