/********************************************************************************
** Form generated from reading UI file 'searchbyimage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHBYIMAGE_H
#define UI_SEARCHBYIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchByImage
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_selectImage;
    QPushButton *pushButton_selectImage;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox_get_imagePath;
    QHBoxLayout *horizontalLayout;
    QLabel *label_get_img;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *SearchByImage)
    {
        if (SearchByImage->objectName().isEmpty())
            SearchByImage->setObjectName(QStringLiteral("SearchByImage"));
        SearchByImage->resize(449, 185);
        widget = new QWidget(SearchByImage);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 431, 166));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_selectImage = new QLabel(widget);
        label_selectImage->setObjectName(QStringLiteral("label_selectImage"));
        label_selectImage->setMinimumSize(QSize(121, 131));
        label_selectImage->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:repeat, x1:0.945, y1:0.102, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));

        verticalLayout->addWidget(label_selectImage);

        pushButton_selectImage = new QPushButton(widget);
        pushButton_selectImage->setObjectName(QStringLiteral("pushButton_selectImage"));

        verticalLayout->addWidget(pushButton_selectImage);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        comboBox_get_imagePath = new QComboBox(widget);
        comboBox_get_imagePath->setObjectName(QStringLiteral("comboBox_get_imagePath"));

        verticalLayout_2->addWidget(comboBox_get_imagePath);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_get_img = new QLabel(widget);
        label_get_img->setObjectName(QStringLiteral("label_get_img"));
        label_get_img->setMinimumSize(QSize(111, 111));
        label_get_img->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:repeat, x1:0.945, y1:0.102, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));

        horizontalLayout->addWidget(label_get_img);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(SearchByImage);

        QMetaObject::connectSlotsByName(SearchByImage);
    } // setupUi

    void retranslateUi(QDialog *SearchByImage)
    {
        SearchByImage->setWindowTitle(QApplication::translate("SearchByImage", "Dialog", Q_NULLPTR));
        label_selectImage->setText(QString());
        pushButton_selectImage->setText(QApplication::translate("SearchByImage", "Select Image", Q_NULLPTR));
        label_get_img->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SearchByImage: public Ui_SearchByImage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHBYIMAGE_H
