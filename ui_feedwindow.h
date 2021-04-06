/********************************************************************************
** Form generated from reading UI file 'feedwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEEDWINDOW_H
#define UI_FEEDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_FeedWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *imageLabel;

    void setupUi(QDialog *FeedWindow)
    {
        if (FeedWindow->objectName().isEmpty())
            FeedWindow->setObjectName(QStringLiteral("FeedWindow"));
        FeedWindow->resize(1008, 567);
        FeedWindow->setMinimumSize(QSize(1008, 567));
        FeedWindow->setLayoutDirection(Qt::LeftToRight);
        FeedWindow->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        gridLayout = new QGridLayout(FeedWindow);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        imageLabel = new QLabel(FeedWindow);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));

        gridLayout->addWidget(imageLabel, 0, 0, 1, 1);


        retranslateUi(FeedWindow);

        QMetaObject::connectSlotsByName(FeedWindow);
    } // setupUi

    void retranslateUi(QDialog *FeedWindow)
    {
        FeedWindow->setWindowTitle(QApplication::translate("FeedWindow", "Feed", Q_NULLPTR));
        imageLabel->setText(QApplication::translate("FeedWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FeedWindow: public Ui_FeedWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEEDWINDOW_H
