/********************************************************************************
** Form generated from reading UI file 'lpnotif.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LPNOTIF_H
#define UI_LPNOTIF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LPNotif
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *image;
    QLabel *text;
    QLabel *imageMatch;
    QFrame *line;

    void setupUi(QWidget *LPNotif)
    {
        if (LPNotif->objectName().isEmpty())
            LPNotif->setObjectName(QStringLiteral("LPNotif"));
        LPNotif->resize(400, 147);
        LPNotif->setMaximumSize(QSize(400, 147));
        LPNotif->setStyleSheet(QStringLiteral("background-color: rgb(204, 225, 227);"));
        horizontalLayout = new QHBoxLayout(LPNotif);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        image = new QLabel(LPNotif);
        image->setObjectName(QStringLiteral("image"));
        image->setMinimumSize(QSize(130, 140));
        image->setMaximumSize(QSize(200, 140));

        horizontalLayout_2->addWidget(image);

        text = new QLabel(LPNotif);
        text->setObjectName(QStringLiteral("text"));
        text->setMinimumSize(QSize(200, 140));
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
        QBrush brush4(QColor(255, 255, 255, 128));
        brush4.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
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
        QBrush brush5(QColor(255, 255, 255, 128));
        brush5.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
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
        QBrush brush6(QColor(255, 255, 255, 128));
        brush6.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush6);
        text->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Noto Sans CJK JP"));
        font.setPointSize(12);
        text->setFont(font);

        horizontalLayout_2->addWidget(text);

        imageMatch = new QLabel(LPNotif);
        imageMatch->setObjectName(QStringLiteral("imageMatch"));
        imageMatch->setMinimumSize(QSize(130, 140));
        imageMatch->setMaximumSize(QSize(200, 140));

        horizontalLayout_2->addWidget(imageMatch);


        verticalLayout->addLayout(horizontalLayout_2);

        line = new QFrame(LPNotif);
        line->setObjectName(QStringLiteral("line"));
        line->setMinimumSize(QSize(0, 10));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush7(QColor(255, 127, 127, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush7);
        QBrush brush8(QColor(255, 63, 63, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush8);
        QBrush brush9(QColor(127, 0, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush9);
        QBrush brush10(QColor(170, 0, 0, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush10);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        QBrush brush11(QColor(255, 0, 0, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush11);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush2);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush3);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush2);
        QBrush brush12(QColor(0, 0, 0, 128));
        brush12.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush2);
        QBrush brush13(QColor(0, 0, 0, 128));
        brush13.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush2);
        QBrush brush14(QColor(0, 0, 0, 128));
        brush14.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush14);
        line->setPalette(palette1);
        line->setLineWidth(10);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(LPNotif);

        QMetaObject::connectSlotsByName(LPNotif);
    } // setupUi

    void retranslateUi(QWidget *LPNotif)
    {
        LPNotif->setWindowTitle(QApplication::translate("LPNotif", "Form", Q_NULLPTR));
        image->setText(QApplication::translate("LPNotif", "Image", Q_NULLPTR));
        text->setText(QApplication::translate("LPNotif", "Text", Q_NULLPTR));
        imageMatch->setText(QApplication::translate("LPNotif", "imagematch", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LPNotif: public Ui_LPNotif {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LPNOTIF_H
