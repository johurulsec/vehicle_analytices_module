/********************************************************************************
** Form generated from reading UI file 'showface.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWFACE_H
#define UI_SHOWFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowFace
{
public:
    QScrollArea *scrollArea_grid;
    QWidget *scrollAreaWidgetContents_face_show;

    void setupUi(QWidget *ShowFace)
    {
        if (ShowFace->objectName().isEmpty())
            ShowFace->setObjectName(QStringLiteral("ShowFace"));
        ShowFace->resize(665, 500);
        ShowFace->setMinimumSize(QSize(665, 500));
        ShowFace->setMaximumSize(QSize(665, 500));
        scrollArea_grid = new QScrollArea(ShowFace);
        scrollArea_grid->setObjectName(QStringLiteral("scrollArea_grid"));
        scrollArea_grid->setGeometry(QRect(0, 0, 665, 500));
        scrollArea_grid->setMinimumSize(QSize(665, 500));
        scrollArea_grid->setMaximumSize(QSize(665, 500));
        scrollArea_grid->setWidgetResizable(true);
        scrollAreaWidgetContents_face_show = new QWidget();
        scrollAreaWidgetContents_face_show->setObjectName(QStringLiteral("scrollAreaWidgetContents_face_show"));
        scrollAreaWidgetContents_face_show->setGeometry(QRect(0, 0, 663, 498));
        scrollArea_grid->setWidget(scrollAreaWidgetContents_face_show);

        retranslateUi(ShowFace);

        QMetaObject::connectSlotsByName(ShowFace);
    } // setupUi

    void retranslateUi(QWidget *ShowFace)
    {
        ShowFace->setWindowTitle(QApplication::translate("ShowFace", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShowFace: public Ui_ShowFace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWFACE_H
