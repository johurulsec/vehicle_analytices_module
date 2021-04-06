/********************************************************************************
** Form generated from reading UI file 'feed.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEED_H
#define UI_FEED_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Feed
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *feedGridLayout;
    QLabel *feedLabel;

    void setupUi(QWidget *Feed)
    {
        if (Feed->objectName().isEmpty())
            Feed->setObjectName(QStringLiteral("Feed"));
        Feed->resize(640, 300);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Feed->sizePolicy().hasHeightForWidth());
        Feed->setSizePolicy(sizePolicy);
        Feed->setMinimumSize(QSize(400, 300));
        Feed->setMaximumSize(QSize(640, 480));
        Feed->setStyleSheet(QStringLiteral("background-color: #4f5154;"));
        gridLayout_2 = new QGridLayout(Feed);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        feedGridLayout = new QGridLayout();
        feedGridLayout->setObjectName(QStringLiteral("feedGridLayout"));
        feedLabel = new QLabel(Feed);
        feedLabel->setObjectName(QStringLiteral("feedLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(feedLabel->sizePolicy().hasHeightForWidth());
        feedLabel->setSizePolicy(sizePolicy1);
        feedLabel->setMinimumSize(QSize(0, 0));

        feedGridLayout->addWidget(feedLabel, 0, 0, 1, 1);


        gridLayout_2->addLayout(feedGridLayout, 1, 0, 1, 1);


        retranslateUi(Feed);

        QMetaObject::connectSlotsByName(Feed);
    } // setupUi

    void retranslateUi(QWidget *Feed)
    {
        Feed->setWindowTitle(QApplication::translate("Feed", "Form", Q_NULLPTR));
        feedLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Feed: public Ui_Feed {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEED_H
