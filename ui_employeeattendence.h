/********************************************************************************
** Form generated from reading UI file 'employeeattendence.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEEATTENDENCE_H
#define UI_EMPLOYEEATTENDENCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmployeeAttendence
{
public:
    QCalendarWidget *calendarWidget_date;
    QTableWidget *tableWidget_employee;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QTimeEdit *timeEdit_from_time;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QTimeEdit *timeEdit_to_time;
    QPushButton *pushButton_generate;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_export_as_pdf;

    void setupUi(QDialog *EmployeeAttendence)
    {
        if (EmployeeAttendence->objectName().isEmpty())
            EmployeeAttendence->setObjectName(QStringLiteral("EmployeeAttendence"));
        EmployeeAttendence->resize(941, 420);
        calendarWidget_date = new QCalendarWidget(EmployeeAttendence);
        calendarWidget_date->setObjectName(QStringLiteral("calendarWidget_date"));
        calendarWidget_date->setGeometry(QRect(10, 10, 451, 221));
        calendarWidget_date->setGridVisible(false);
        calendarWidget_date->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        calendarWidget_date->setNavigationBarVisible(true);
        calendarWidget_date->setDateEditEnabled(false);
        tableWidget_employee = new QTableWidget(EmployeeAttendence);
        tableWidget_employee->setObjectName(QStringLiteral("tableWidget_employee"));
        tableWidget_employee->setGeometry(QRect(470, 10, 461, 401));
        widget = new QWidget(EmployeeAttendence);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 250, 451, 30));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        timeEdit_from_time = new QTimeEdit(widget);
        timeEdit_from_time->setObjectName(QStringLiteral("timeEdit_from_time"));

        horizontalLayout->addWidget(timeEdit_from_time);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(20, 26));

        horizontalLayout_2->addWidget(label_2);

        timeEdit_to_time = new QTimeEdit(widget);
        timeEdit_to_time->setObjectName(QStringLiteral("timeEdit_to_time"));

        horizontalLayout_2->addWidget(timeEdit_to_time);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        pushButton_generate = new QPushButton(widget);
        pushButton_generate->setObjectName(QStringLiteral("pushButton_generate"));

        horizontalLayout_3->addWidget(pushButton_generate);

        widget1 = new QWidget(EmployeeAttendence);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 290, 451, 27));
        horizontalLayout_4 = new QHBoxLayout(widget1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_reset = new QPushButton(widget1);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));
        pushButton_reset->setEnabled(true);
        pushButton_reset->setMinimumSize(QSize(146, 0));

        horizontalLayout_4->addWidget(pushButton_reset);

        pushButton_export_as_pdf = new QPushButton(widget1);
        pushButton_export_as_pdf->setObjectName(QStringLiteral("pushButton_export_as_pdf"));
        pushButton_export_as_pdf->setEnabled(true);
        pushButton_export_as_pdf->setMinimumSize(QSize(146, 0));

        horizontalLayout_4->addWidget(pushButton_export_as_pdf);


        retranslateUi(EmployeeAttendence);

        QMetaObject::connectSlotsByName(EmployeeAttendence);
    } // setupUi

    void retranslateUi(QDialog *EmployeeAttendence)
    {
        EmployeeAttendence->setWindowTitle(QApplication::translate("EmployeeAttendence", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("EmployeeAttendence", "From", Q_NULLPTR));
        label_2->setText(QApplication::translate("EmployeeAttendence", "To", Q_NULLPTR));
        pushButton_generate->setText(QApplication::translate("EmployeeAttendence", "Generate", Q_NULLPTR));
        pushButton_reset->setText(QApplication::translate("EmployeeAttendence", "Reset", Q_NULLPTR));
        pushButton_export_as_pdf->setText(QApplication::translate("EmployeeAttendence", "Export as pdf", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EmployeeAttendence: public Ui_EmployeeAttendence {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEEATTENDENCE_H
