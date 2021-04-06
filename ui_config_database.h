/********************************************************************************
** Form generated from reading UI file 'config_database.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_DATABASE_H
#define UI_CONFIG_DATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_config_database
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_search;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *lineEdit_search_box;
    QTableWidget *tableView_inserted_data_show;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_delete;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_name;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_name;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_position;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEdit_position;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_address;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit_address;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_phone;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *lineEdit_phone;
    QHBoxLayout *horizontalLayout_15;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_access_pass;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *lineEdit_access_pass;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_image_show;
    QSpacerItem *verticalSpacer_5;
    QPushButton *pushButton_take_photo;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_12;
    QLineEdit *lineEditDB;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_add_information;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_webCam_photo;

    void setupUi(QDialog *config_database)
    {
        if (config_database->objectName().isEmpty())
            config_database->setObjectName(QStringLiteral("config_database"));
        config_database->resize(776, 363);
        layoutWidget = new QWidget(config_database);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(310, 10, 461, 341));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_search = new QLabel(layoutWidget);
        label_search->setObjectName(QStringLiteral("label_search"));

        horizontalLayout_3->addWidget(label_search);

        horizontalSpacer_7 = new QSpacerItem(13, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        lineEdit_search_box = new QLineEdit(layoutWidget);
        lineEdit_search_box->setObjectName(QStringLiteral("lineEdit_search_box"));

        horizontalLayout_3->addWidget(lineEdit_search_box);


        verticalLayout_3->addLayout(horizontalLayout_3);

        tableView_inserted_data_show = new QTableWidget(layoutWidget);
        tableView_inserted_data_show->setObjectName(QStringLiteral("tableView_inserted_data_show"));

        verticalLayout_3->addWidget(tableView_inserted_data_show);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_8);

        pushButton_reset = new QPushButton(layoutWidget);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));

        horizontalLayout_14->addWidget(pushButton_reset);

        pushButton_delete = new QPushButton(layoutWidget);
        pushButton_delete->setObjectName(QStringLiteral("pushButton_delete"));
        pushButton_delete->setAutoDefault(false);

        horizontalLayout_14->addWidget(pushButton_delete);


        verticalLayout_3->addLayout(horizontalLayout_14);

        widget = new QWidget(config_database);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 278, 344));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_name = new QLabel(widget);
        label_name->setObjectName(QStringLiteral("label_name"));

        horizontalLayout->addWidget(label_name);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_2->addLayout(horizontalLayout);

        lineEdit_name = new QLineEdit(widget);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));

        horizontalLayout_2->addWidget(lineEdit_name);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_position = new QLabel(widget);
        label_position->setObjectName(QStringLiteral("label_position"));

        horizontalLayout_6->addWidget(label_position);

        horizontalSpacer_3 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        horizontalLayout_5->addLayout(horizontalLayout_6);

        lineEdit_position = new QLineEdit(widget);
        lineEdit_position->setObjectName(QStringLiteral("lineEdit_position"));

        horizontalLayout_5->addWidget(lineEdit_position);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_address = new QLabel(widget);
        label_address->setObjectName(QStringLiteral("label_address"));

        horizontalLayout_8->addWidget(label_address);

        horizontalSpacer_4 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        horizontalLayout_7->addLayout(horizontalLayout_8);

        lineEdit_address = new QLineEdit(widget);
        lineEdit_address->setObjectName(QStringLiteral("lineEdit_address"));

        horizontalLayout_7->addWidget(lineEdit_address);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_phone = new QLabel(widget);
        label_phone->setObjectName(QStringLiteral("label_phone"));

        horizontalLayout_10->addWidget(label_phone);

        horizontalSpacer_5 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);


        horizontalLayout_9->addLayout(horizontalLayout_10);

        lineEdit_phone = new QLineEdit(widget);
        lineEdit_phone->setObjectName(QStringLiteral("lineEdit_phone"));

        horizontalLayout_9->addWidget(lineEdit_phone);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_access_pass = new QLabel(widget);
        label_access_pass->setObjectName(QStringLiteral("label_access_pass"));

        horizontalLayout_16->addWidget(label_access_pass);

        horizontalSpacer_9 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_9);


        horizontalLayout_15->addLayout(horizontalLayout_16);

        lineEdit_access_pass = new QLineEdit(widget);
        lineEdit_access_pass->setObjectName(QStringLiteral("lineEdit_access_pass"));

        horizontalLayout_15->addWidget(lineEdit_access_pass);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_image_show = new QLabel(widget);
        label_image_show->setObjectName(QStringLiteral("label_image_show"));

        horizontalLayout_11->addWidget(label_image_show);

        verticalSpacer_5 = new QSpacerItem(20, 88, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_11->addItem(verticalSpacer_5);

        pushButton_take_photo = new QPushButton(widget);
        pushButton_take_photo->setObjectName(QStringLiteral("pushButton_take_photo"));
        pushButton_take_photo->setAutoDefault(false);

        horizontalLayout_11->addWidget(pushButton_take_photo);


        verticalLayout->addLayout(horizontalLayout_11);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(270, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        lineEditDB = new QLineEdit(widget);
        lineEditDB->setObjectName(QStringLiteral("lineEditDB"));

        horizontalLayout_12->addWidget(lineEditDB);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_6);

        pushButton_add_information = new QPushButton(widget);
        pushButton_add_information->setObjectName(QStringLiteral("pushButton_add_information"));
        pushButton_add_information->setAutoDefault(false);

        horizontalLayout_12->addWidget(pushButton_add_information);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setAutoDefault(false);

        horizontalLayout_4->addWidget(pushButton);

        pushButton_webCam_photo = new QPushButton(widget);
        pushButton_webCam_photo->setObjectName(QStringLiteral("pushButton_webCam_photo"));
        pushButton_webCam_photo->setAutoDefault(false);

        horizontalLayout_4->addWidget(pushButton_webCam_photo);


        verticalLayout_2->addLayout(horizontalLayout_4);


        retranslateUi(config_database);

        QMetaObject::connectSlotsByName(config_database);
    } // setupUi

    void retranslateUi(QDialog *config_database)
    {
        config_database->setWindowTitle(QApplication::translate("config_database", "Dialog", Q_NULLPTR));
        label_search->setText(QApplication::translate("config_database", "Search", Q_NULLPTR));
        pushButton_reset->setText(QApplication::translate("config_database", "Reset", Q_NULLPTR));
        pushButton_delete->setText(QApplication::translate("config_database", "Delete", Q_NULLPTR));
        label_name->setText(QApplication::translate("config_database", "Name", Q_NULLPTR));
        label_position->setText(QApplication::translate("config_database", "Position", Q_NULLPTR));
        label_address->setText(QApplication::translate("config_database", "Address", Q_NULLPTR));
        label_phone->setText(QApplication::translate("config_database", "Phone", Q_NULLPTR));
        label_access_pass->setText(QApplication::translate("config_database", "Access pass", Q_NULLPTR));
        label_image_show->setText(QString());
        pushButton_take_photo->setText(QApplication::translate("config_database", "Upload Photo", Q_NULLPTR));
        pushButton_add_information->setText(QApplication::translate("config_database", "Add", Q_NULLPTR));
        pushButton->setText(QApplication::translate("config_database", "Batch Enrollment", Q_NULLPTR));
        pushButton_webCam_photo->setText(QApplication::translate("config_database", "Take Photo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class config_database: public Ui_config_database {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_DATABASE_H
