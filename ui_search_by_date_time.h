/********************************************************************************
** Form generated from reading UI file 'search_by_date_time.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_BY_DATE_TIME_H
#define UI_SEARCH_BY_DATE_TIME_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_search_by_date_time
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QDateTimeEdit *dateTimeEdit_from;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QDateTimeEdit *dateTimeEdit_to;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QProgressBar *progressBar_threshhold_value;
    QSpacerItem *horizontalSpacer_6;
    QSlider *horizontalSlider_threshhold_value;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_recognized;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *checkBox_unrecognized;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_search;
    QSpacerItem *horizontalSpacer_9;
    QTableWidget *tableView_search_by_date;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QDialog *search_by_date_time)
    {
        if (search_by_date_time->objectName().isEmpty())
            search_by_date_time->setObjectName(QStringLiteral("search_by_date_time"));
        search_by_date_time->resize(880, 308);
        centralWidget = new QWidget(search_by_date_time);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 881, 361));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 461, 271));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        dateTimeEdit_from = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_from->setObjectName(QStringLiteral("dateTimeEdit_from"));
        dateTimeEdit_from->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        dateTimeEdit_from->setCalendarPopup(false);
        dateTimeEdit_from->setTimeSpec(Qt::TimeZone);

        horizontalLayout->addWidget(dateTimeEdit_from);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer_3 = new QSpacerItem(15, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        dateTimeEdit_to = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_to->setObjectName(QStringLiteral("dateTimeEdit_to"));
        dateTimeEdit_to->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        dateTimeEdit_to->setTimeSpec(Qt::TimeZone);

        horizontalLayout_2->addWidget(dateTimeEdit_to);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalSpacer_10 = new QSpacerItem(40, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_10);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_6->addWidget(label_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        progressBar_threshhold_value = new QProgressBar(layoutWidget);
        progressBar_threshhold_value->setObjectName(QStringLiteral("progressBar_threshhold_value"));
        progressBar_threshhold_value->setMaximum(100);
        progressBar_threshhold_value->setValue(0);

        verticalLayout->addWidget(progressBar_threshhold_value);

        horizontalSpacer_6 = new QSpacerItem(10, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_6);

        horizontalSlider_threshhold_value = new QSlider(layoutWidget);
        horizontalSlider_threshhold_value->setObjectName(QStringLiteral("horizontalSlider_threshhold_value"));
        horizontalSlider_threshhold_value->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider_threshhold_value);


        horizontalLayout_6->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalSpacer_11 = new QSpacerItem(40, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_11);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBox_recognized = new QCheckBox(layoutWidget);
        checkBox_recognized->setObjectName(QStringLiteral("checkBox_recognized"));

        horizontalLayout_4->addWidget(checkBox_recognized);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        checkBox_unrecognized = new QCheckBox(layoutWidget);
        checkBox_unrecognized->setObjectName(QStringLiteral("checkBox_unrecognized"));

        horizontalLayout_4->addWidget(checkBox_unrecognized);


        horizontalLayout_7->addLayout(horizontalLayout_4);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalSpacer_12 = new QSpacerItem(40, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_12);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButton_search = new QPushButton(layoutWidget);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));

        horizontalLayout_9->addWidget(pushButton_search);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);


        verticalLayout_2->addLayout(horizontalLayout_9);

        tableView_search_by_date = new QTableWidget(centralWidget);
        tableView_search_by_date->setObjectName(QStringLiteral("tableView_search_by_date"));
        tableView_search_by_date->setGeometry(QRect(480, 30, 391, 271));
        menuBar = new QMenuBar(search_by_date_time);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 915, 22));
        mainToolBar = new QToolBar(search_by_date_time);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setGeometry(QRect(0, 0, 8, 17));
        statusBar = new QStatusBar(search_by_date_time);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setGeometry(QRect(0, 0, 3, 22));

        retranslateUi(search_by_date_time);
        QObject::connect(horizontalSlider_threshhold_value, SIGNAL(valueChanged(int)), progressBar_threshhold_value, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(search_by_date_time);
    } // setupUi

    void retranslateUi(QDialog *search_by_date_time)
    {
        search_by_date_time->setWindowTitle(QApplication::translate("search_by_date_time", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("search_by_date_time", "From:", Q_NULLPTR));
        label_2->setText(QApplication::translate("search_by_date_time", "To:", Q_NULLPTR));
        label_3->setText(QApplication::translate("search_by_date_time", "Threshold Value", Q_NULLPTR));
        checkBox_recognized->setText(QApplication::translate("search_by_date_time", "Recognized", Q_NULLPTR));
        checkBox_unrecognized->setText(QApplication::translate("search_by_date_time", "Unrecognized", Q_NULLPTR));
        pushButton_search->setText(QApplication::translate("search_by_date_time", "Search", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class search_by_date_time: public Ui_search_by_date_time {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_BY_DATE_TIME_H
