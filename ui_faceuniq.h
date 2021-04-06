/********************************************************************************
** Form generated from reading UI file 'faceuniq.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEUNIQ_H
#define UI_FACEUNIQ_H

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

class Ui_faceUniq
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_date_time;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_uniq_image;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_name_confid;

    void setupUi(QWidget *faceUniq)
    {
        if (faceUniq->objectName().isEmpty())
            faceUniq->setObjectName(QStringLiteral("faceUniq"));
        faceUniq->resize(216, 237);
        faceUniq->setMinimumSize(QSize(216, 237));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(211, 215, 207, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(233, 235, 231, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(105, 107, 103, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(141, 143, 138, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        faceUniq->setPalette(palette);
        layoutWidget = new QWidget(faceUniq);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 3, 211, 231));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_date_time = new QLabel(layoutWidget);
        label_date_time->setObjectName(QStringLiteral("label_date_time"));
        label_date_time->setMinimumSize(QSize(0, 41));

        verticalLayout->addWidget(label_date_time);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalSpacer = new QSpacerItem(40, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout->addItem(verticalSpacer);

        label_uniq_image = new QLabel(layoutWidget);
        label_uniq_image->setObjectName(QStringLiteral("label_uniq_image"));
        label_uniq_image->setMinimumSize(QSize(100, 80));
        label_uniq_image->setMaximumSize(QSize(100, 80));

        horizontalLayout->addWidget(label_uniq_image);

        verticalSpacer_2 = new QSpacerItem(40, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout->addItem(verticalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        label_name_confid = new QLabel(layoutWidget);
        label_name_confid->setObjectName(QStringLiteral("label_name_confid"));
        label_name_confid->setMinimumSize(QSize(0, 70));
        QFont font;
        font.setPointSize(11);
        label_name_confid->setFont(font);

        verticalLayout->addWidget(label_name_confid);


        retranslateUi(faceUniq);

        QMetaObject::connectSlotsByName(faceUniq);
    } // setupUi

    void retranslateUi(QWidget *faceUniq)
    {
        faceUniq->setWindowTitle(QApplication::translate("faceUniq", "Form", Q_NULLPTR));
        label_date_time->setText(QApplication::translate("faceUniq", "TextLabel", Q_NULLPTR));
        label_uniq_image->setText(QApplication::translate("faceUniq", "TextLabel", Q_NULLPTR));
        label_name_confid->setText(QApplication::translate("faceUniq", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class faceUniq: public Ui_faceUniq {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEUNIQ_H
