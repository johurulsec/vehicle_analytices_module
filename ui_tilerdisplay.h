/********************************************************************************
** Form generated from reading UI file 'tilerdisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TILERDISPLAY_H
#define UI_TILERDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TilerDisplay
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabAllTiles;
    QGridLayout *gridLayout;
    QScrollArea *scrollAreaFaces;
    QWidget *scrollAreaWidgetContents;
    QWidget *tabClusterTab;
    QGridLayout *gridLayout_3;
    QScrollArea *scrollAreaCluster;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *tabFR;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_4;
    QWidget *tabLprTab;
    QGridLayout *gridLayout_4;
    QScrollArea *scrollAreaLPR;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *tab;
    QScrollArea *scrollAreaPerson;
    QWidget *scrollAreaWidgetContents_8;

    void setupUi(QDialog *TilerDisplay)
    {
        if (TilerDisplay->objectName().isEmpty())
            TilerDisplay->setObjectName(QStringLiteral("TilerDisplay"));
        TilerDisplay->resize(962, 803);
        TilerDisplay->setMinimumSize(QSize(962, 800));
        gridLayout_2 = new QGridLayout(TilerDisplay);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(TilerDisplay);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabAllTiles = new QWidget();
        tabAllTiles->setObjectName(QStringLiteral("tabAllTiles"));
        gridLayout = new QGridLayout(tabAllTiles);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollAreaFaces = new QScrollArea(tabAllTiles);
        scrollAreaFaces->setObjectName(QStringLiteral("scrollAreaFaces"));
        scrollAreaFaces->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 956, 770));
        scrollAreaFaces->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollAreaFaces, 0, 0, 1, 1);

        tabWidget->addTab(tabAllTiles, QString());
        tabClusterTab = new QWidget();
        tabClusterTab->setObjectName(QStringLiteral("tabClusterTab"));
        gridLayout_3 = new QGridLayout(tabClusterTab);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollAreaCluster = new QScrollArea(tabClusterTab);
        scrollAreaCluster->setObjectName(QStringLiteral("scrollAreaCluster"));
        scrollAreaCluster->setMinimumSize(QSize(958, 770));
        scrollAreaCluster->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 956, 770));
        scrollAreaCluster->setWidget(scrollAreaWidgetContents_2);

        gridLayout_3->addWidget(scrollAreaCluster, 0, 0, 1, 1);

        tabWidget->addTab(tabClusterTab, QString());
        tabFR = new QWidget();
        tabFR->setObjectName(QStringLiteral("tabFR"));
        tabFR->setEnabled(true);
        scrollArea = new QScrollArea(tabFR);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setEnabled(true);
        scrollArea->setGeometry(QRect(6, 9, 940, 753));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 938, 751));
        scrollArea->setWidget(scrollAreaWidgetContents_4);
        tabWidget->addTab(tabFR, QString());
        tabLprTab = new QWidget();
        tabLprTab->setObjectName(QStringLiteral("tabLprTab"));
        gridLayout_4 = new QGridLayout(tabLprTab);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        scrollAreaLPR = new QScrollArea(tabLprTab);
        scrollAreaLPR->setObjectName(QStringLiteral("scrollAreaLPR"));
        scrollAreaLPR->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 938, 752));
        scrollAreaLPR->setWidget(scrollAreaWidgetContents_3);

        gridLayout_4->addWidget(scrollAreaLPR, 0, 0, 1, 1);

        tabWidget->addTab(tabLprTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        scrollAreaPerson = new QScrollArea(tab);
        scrollAreaPerson->setObjectName(QStringLiteral("scrollAreaPerson"));
        scrollAreaPerson->setGeometry(QRect(0, 0, 951, 761));
        scrollAreaPerson->setWidgetResizable(true);
        scrollAreaWidgetContents_8 = new QWidget();
        scrollAreaWidgetContents_8->setObjectName(QStringLiteral("scrollAreaWidgetContents_8"));
        scrollAreaWidgetContents_8->setGeometry(QRect(0, 0, 949, 759));
        scrollAreaPerson->setWidget(scrollAreaWidgetContents_8);
        tabWidget->addTab(tab, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(TilerDisplay);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(TilerDisplay);
    } // setupUi

    void retranslateUi(QDialog *TilerDisplay)
    {
        TilerDisplay->setWindowTitle(QApplication::translate("TilerDisplay", "Tiles", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabAllTiles), QApplication::translate("TilerDisplay", "Car", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabClusterTab), QApplication::translate("TilerDisplay", "LPR", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabFR), QApplication::translate("TilerDisplay", "Search LP", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabLprTab), QApplication::translate("TilerDisplay", "RecognizedFaces", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("TilerDisplay", "Person", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TilerDisplay: public Ui_TilerDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TILERDISPLAY_H
