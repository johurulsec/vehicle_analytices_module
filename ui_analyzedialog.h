/********************************************************************************
** Form generated from reading UI file 'analyzedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZEDIALOG_H
#define UI_ANALYZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_analyzeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *facesCheck;
    QWidget *faceWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *faceLay;
    QPushButton *addFaceBut;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QCheckBox *objectCheck;
    QWidget *objectWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *objectLay;
    QVBoxLayout *colorObjectsLayout;
    QPushButton *addObjectFilter;
    QCheckBox *blackCheck;
    QWidget *blackWidget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *blackLay;
    QPushButton *blackBut;
    QVBoxLayout *blackListLayout;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QRadioButton *gpu0;
    QRadioButton *gpu1;
    QWidget *horizontalWidget1;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelBut;
    QPushButton *analyzeBut;
    QButtonGroup *radioGroup;

    void setupUi(QDialog *analyzeDialog)
    {
        if (analyzeDialog->objectName().isEmpty())
            analyzeDialog->setObjectName(QStringLiteral("analyzeDialog"));
        analyzeDialog->resize(611, 583);
        verticalLayout = new QVBoxLayout(analyzeDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(analyzeDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        facesCheck = new QCheckBox(groupBox);
        facesCheck->setObjectName(QStringLiteral("facesCheck"));

        verticalLayout_2->addWidget(facesCheck);

        faceWidget = new QWidget(groupBox);
        faceWidget->setObjectName(QStringLiteral("faceWidget"));
        horizontalLayout_2 = new QHBoxLayout(faceWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(120, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        faceLay = new QVBoxLayout();
        faceLay->setObjectName(QStringLiteral("faceLay"));
        addFaceBut = new QPushButton(faceWidget);
        addFaceBut->setObjectName(QStringLiteral("addFaceBut"));

        faceLay->addWidget(addFaceBut);

        scrollArea = new QScrollArea(faceWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 421, 210));
        scrollArea->setWidget(scrollAreaWidgetContents);

        faceLay->addWidget(scrollArea);


        horizontalLayout_2->addLayout(faceLay);


        verticalLayout_2->addWidget(faceWidget);

        objectCheck = new QCheckBox(groupBox);
        objectCheck->setObjectName(QStringLiteral("objectCheck"));

        verticalLayout_2->addWidget(objectCheck);

        objectWidget = new QWidget(groupBox);
        objectWidget->setObjectName(QStringLiteral("objectWidget"));
        horizontalLayout_3 = new QHBoxLayout(objectWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(120, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        objectLay = new QVBoxLayout();
        objectLay->setObjectName(QStringLiteral("objectLay"));
        colorObjectsLayout = new QVBoxLayout();
        colorObjectsLayout->setObjectName(QStringLiteral("colorObjectsLayout"));

        objectLay->addLayout(colorObjectsLayout);

        addObjectFilter = new QPushButton(objectWidget);
        addObjectFilter->setObjectName(QStringLiteral("addObjectFilter"));

        objectLay->addWidget(addObjectFilter);


        horizontalLayout_3->addLayout(objectLay);


        verticalLayout_2->addWidget(objectWidget);

        blackCheck = new QCheckBox(groupBox);
        blackCheck->setObjectName(QStringLiteral("blackCheck"));

        verticalLayout_2->addWidget(blackCheck);

        blackWidget = new QWidget(groupBox);
        blackWidget->setObjectName(QStringLiteral("blackWidget"));
        horizontalLayout_4 = new QHBoxLayout(blackWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(120, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        blackLay = new QVBoxLayout();
        blackLay->setObjectName(QStringLiteral("blackLay"));
        blackBut = new QPushButton(blackWidget);
        blackBut->setObjectName(QStringLiteral("blackBut"));

        blackLay->addWidget(blackBut);

        blackListLayout = new QVBoxLayout();
        blackListLayout->setObjectName(QStringLiteral("blackListLayout"));

        blackLay->addLayout(blackListLayout);


        horizontalLayout_4->addLayout(blackLay);


        verticalLayout_2->addWidget(blackWidget);

        horizontalWidget = new QWidget(groupBox);
        horizontalWidget->setObjectName(QStringLiteral("horizontalWidget"));
        horizontalWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout_5 = new QHBoxLayout(horizontalWidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        gpu0 = new QRadioButton(horizontalWidget);
        radioGroup = new QButtonGroup(analyzeDialog);
        radioGroup->setObjectName(QStringLiteral("radioGroup"));
        radioGroup->addButton(gpu0);
        gpu0->setObjectName(QStringLiteral("gpu0"));
        gpu0->setChecked(true);

        horizontalLayout_5->addWidget(gpu0);

        gpu1 = new QRadioButton(horizontalWidget);
        radioGroup->addButton(gpu1);
        gpu1->setObjectName(QStringLiteral("gpu1"));

        horizontalLayout_5->addWidget(gpu1);


        verticalLayout_2->addWidget(horizontalWidget);


        verticalLayout->addWidget(groupBox);

        horizontalWidget1 = new QWidget(analyzeDialog);
        horizontalWidget1->setObjectName(QStringLiteral("horizontalWidget1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontalWidget1->sizePolicy().hasHeightForWidth());
        horizontalWidget1->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(horizontalWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelBut = new QPushButton(horizontalWidget1);
        cancelBut->setObjectName(QStringLiteral("cancelBut"));

        horizontalLayout->addWidget(cancelBut);

        analyzeBut = new QPushButton(horizontalWidget1);
        analyzeBut->setObjectName(QStringLiteral("analyzeBut"));

        horizontalLayout->addWidget(analyzeBut);


        verticalLayout->addWidget(horizontalWidget1);


        retranslateUi(analyzeDialog);

        QMetaObject::connectSlotsByName(analyzeDialog);
    } // setupUi

    void retranslateUi(QDialog *analyzeDialog)
    {
        analyzeDialog->setWindowTitle(QApplication::translate("analyzeDialog", "Dialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("analyzeDialog", "Analyze Options", Q_NULLPTR));
        facesCheck->setText(QApplication::translate("analyzeDialog", "Search Face Space", Q_NULLPTR));
        addFaceBut->setText(QApplication::translate("analyzeDialog", "Add Faces to search", Q_NULLPTR));
        objectCheck->setText(QApplication::translate("analyzeDialog", "Search Object space", Q_NULLPTR));
        addObjectFilter->setText(QApplication::translate("analyzeDialog", "Add Object filter", Q_NULLPTR));
        blackCheck->setText(QApplication::translate("analyzeDialog", "Search BlackList Space", Q_NULLPTR));
        blackBut->setText(QApplication::translate("analyzeDialog", "Add Blacklist library", Q_NULLPTR));
        gpu0->setText(QApplication::translate("analyzeDialog", "GPU 0", Q_NULLPTR));
        gpu1->setText(QApplication::translate("analyzeDialog", "GPU 1", Q_NULLPTR));
        cancelBut->setText(QApplication::translate("analyzeDialog", "Cancel", Q_NULLPTR));
        analyzeBut->setText(QApplication::translate("analyzeDialog", "Analyze", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class analyzeDialog: public Ui_analyzeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZEDIALOG_H
