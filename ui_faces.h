/********************************************************************************
** Form generated from reading UI file 'faces.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACES_H
#define UI_FACES_H

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

class Ui_Faces
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
    QWidget *tabCar;
    QGridLayout *gridLayout_5;
    QScrollArea *scrollAreaCar;
    QWidget *scrollAreaWidgetContents_5;

    void setupUi(QDialog *Faces)
    {
        if (Faces->objectName().isEmpty())
            Faces->setObjectName(QStringLiteral("Faces"));
        Faces->resize(962, 802);
        gridLayout_2 = new QGridLayout(Faces);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(Faces);
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 956, 769));
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
        scrollAreaCluster->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 956, 769));
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
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 938, 751));
        scrollAreaLPR->setWidget(scrollAreaWidgetContents_3);

        gridLayout_4->addWidget(scrollAreaLPR, 0, 0, 1, 1);

        tabWidget->addTab(tabLprTab, QString());
        tabCar = new QWidget();
        tabCar->setObjectName(QStringLiteral("tabCar"));
        gridLayout_5 = new QGridLayout(tabCar);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        scrollAreaCar = new QScrollArea(tabCar);
        scrollAreaCar->setObjectName(QStringLiteral("scrollAreaCar"));
        scrollAreaCar->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QStringLiteral("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 938, 751));
        scrollAreaCar->setWidget(scrollAreaWidgetContents_5);

        gridLayout_5->addWidget(scrollAreaCar, 0, 0, 1, 1);

        tabWidget->addTab(tabCar, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(Faces);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(Faces);
    } // setupUi

    void retranslateUi(QDialog *Faces)
    {
        Faces->setWindowTitle(QApplication::translate("Faces", "Tiles", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabAllTiles), QApplication::translate("Faces", "Faces", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabClusterTab), QApplication::translate("Faces", "Unique faces (0)", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabFR), QApplication::translate("Faces", "Recognized Faces", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabLprTab), QApplication::translate("Faces", "License Plates", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabCar), QApplication::translate("Faces", "Car", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Faces: public Ui_Faces {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACES_H
