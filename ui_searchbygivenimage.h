/********************************************************************************
** Form generated from reading UI file 'searchbygivenimage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHBYGIVENIMAGE_H
#define UI_SEARCHBYGIVENIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchByGivenImage
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_search_by_img;
    QPushButton *pushButton_select_img;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_directory;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_search;
    QComboBox *comboBox_found_image_list;
    QGridLayout *gridLayout;
    QLabel *label_selected_img;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *SearchByGivenImage)
    {
        if (SearchByGivenImage->objectName().isEmpty())
            SearchByGivenImage->setObjectName(QStringLiteral("SearchByGivenImage"));
        SearchByGivenImage->resize(453, 159);
        label = new QLabel(SearchByGivenImage);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(230, 10, 111, 31));
        layoutWidget = new QWidget(SearchByGivenImage);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 103, 144));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_search_by_img = new QLabel(layoutWidget);
        label_search_by_img->setObjectName(QStringLiteral("label_search_by_img"));
        label_search_by_img->setMinimumSize(QSize(101, 111));
        label_search_by_img->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:repeat, x1:0.945, y1:0.102, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));

        verticalLayout->addWidget(label_search_by_img);

        pushButton_select_img = new QPushButton(layoutWidget);
        pushButton_select_img->setObjectName(QStringLiteral("pushButton_select_img"));

        verticalLayout->addWidget(pushButton_select_img);

        widget = new QWidget(SearchByGivenImage);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(120, 10, 329, 141));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton_directory = new QPushButton(widget);
        pushButton_directory->setObjectName(QStringLiteral("pushButton_directory"));

        verticalLayout_2->addWidget(pushButton_directory);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_search = new QPushButton(widget);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));

        horizontalLayout->addWidget(pushButton_search);

        comboBox_found_image_list = new QComboBox(widget);
        comboBox_found_image_list->setObjectName(QStringLiteral("comboBox_found_image_list"));
        comboBox_found_image_list->setMinimumSize(QSize(191, 25));

        horizontalLayout->addWidget(comboBox_found_image_list);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_selected_img = new QLabel(widget);
        label_selected_img->setObjectName(QStringLiteral("label_selected_img"));
        label_selected_img->setMinimumSize(QSize(91, 71));
        label_selected_img->setMaximumSize(QSize(91, 71));

        gridLayout->addWidget(label_selected_img, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);


        retranslateUi(SearchByGivenImage);

        QMetaObject::connectSlotsByName(SearchByGivenImage);
    } // setupUi

    void retranslateUi(QDialog *SearchByGivenImage)
    {
        SearchByGivenImage->setWindowTitle(QApplication::translate("SearchByGivenImage", "Dialog", Q_NULLPTR));
        label->setText(QString());
        label_search_by_img->setText(QString());
        pushButton_select_img->setText(QApplication::translate("SearchByGivenImage", "Select Image", Q_NULLPTR));
        pushButton_directory->setText(QApplication::translate("SearchByGivenImage", "Select a Directory", Q_NULLPTR));
        pushButton_search->setText(QApplication::translate("SearchByGivenImage", "Search", Q_NULLPTR));
        label_selected_img->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SearchByGivenImage: public Ui_SearchByGivenImage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHBYGIVENIMAGE_H
