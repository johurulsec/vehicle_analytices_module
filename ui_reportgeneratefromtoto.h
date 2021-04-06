/********************************************************************************
** Form generated from reading UI file 'reportgeneratefromtoto.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTGENERATEFROMTOTO_H
#define UI_REPORTGENERATEFROMTOTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReportGenerateFromtoTo
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QDateTimeEdit *dateTimeEdit_from;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QDateTimeEdit *dateTimeEdit_to;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QRadioButton *radioButton_present;
    QRadioButton *radioButton_absent;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_generate;
    QPushButton *pushButton_export_as_pdf;
    QTableWidget *tableView_faces_show;

    void setupUi(QDialog *ReportGenerateFromtoTo)
    {
        if (ReportGenerateFromtoTo->objectName().isEmpty())
            ReportGenerateFromtoTo->setObjectName(QStringLiteral("ReportGenerateFromtoTo"));
        ReportGenerateFromtoTo->resize(866, 443);
        ReportGenerateFromtoTo->setMinimumSize(QSize(866, 439));
        layoutWidget = new QWidget(ReportGenerateFromtoTo);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 21, 285, 162));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Raised);
        label->setLineWidth(5);

        horizontalLayout->addWidget(label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout->addItem(verticalSpacer_2);

        dateTimeEdit_from = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_from->setObjectName(QStringLiteral("dateTimeEdit_from"));

        horizontalLayout->addWidget(dateTimeEdit_from);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setFrameShape(QFrame::Box);
        label_2->setFrameShadow(QFrame::Raised);
        label_2->setLineWidth(5);

        horizontalLayout_2->addWidget(label_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_2->addItem(verticalSpacer);

        dateTimeEdit_to = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_to->setObjectName(QStringLiteral("dateTimeEdit_to"));

        horizontalLayout_2->addWidget(dateTimeEdit_to);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        radioButton_present = new QRadioButton(layoutWidget);
        radioButton_present->setObjectName(QStringLiteral("radioButton_present"));

        horizontalLayout_4->addWidget(radioButton_present);

        radioButton_absent = new QRadioButton(layoutWidget);
        radioButton_absent->setObjectName(QStringLiteral("radioButton_absent"));

        horizontalLayout_4->addWidget(radioButton_absent);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_reset = new QPushButton(layoutWidget);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        pushButton_reset->setFont(font1);
        pushButton_reset->setAutoFillBackground(false);
        pushButton_reset->setStyleSheet(QStringLiteral("border-color: rgb(136, 138, 133);"));
        pushButton_reset->setAutoDefault(true);
        pushButton_reset->setFlat(false);

        horizontalLayout_3->addWidget(pushButton_reset);

        pushButton_generate = new QPushButton(layoutWidget);
        pushButton_generate->setObjectName(QStringLiteral("pushButton_generate"));
        pushButton_generate->setFont(font);

        horizontalLayout_3->addWidget(pushButton_generate);

        pushButton_export_as_pdf = new QPushButton(layoutWidget);
        pushButton_export_as_pdf->setObjectName(QStringLiteral("pushButton_export_as_pdf"));
        pushButton_export_as_pdf->setFont(font);

        horizontalLayout_3->addWidget(pushButton_export_as_pdf);


        verticalLayout->addLayout(horizontalLayout_3);

        tableView_faces_show = new QTableWidget(ReportGenerateFromtoTo);
        tableView_faces_show->setObjectName(QStringLiteral("tableView_faces_show"));
        tableView_faces_show->setGeometry(QRect(320, 10, 541, 431));

        retranslateUi(ReportGenerateFromtoTo);

        pushButton_reset->setDefault(false);


        QMetaObject::connectSlotsByName(ReportGenerateFromtoTo);
    } // setupUi

    void retranslateUi(QDialog *ReportGenerateFromtoTo)
    {
        ReportGenerateFromtoTo->setWindowTitle(QApplication::translate("ReportGenerateFromtoTo", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("ReportGenerateFromtoTo", "From", Q_NULLPTR));
        label_2->setText(QApplication::translate("ReportGenerateFromtoTo", "To", Q_NULLPTR));
        label_4->setText(QApplication::translate("ReportGenerateFromtoTo", "Attendence: ", Q_NULLPTR));
        radioButton_present->setText(QApplication::translate("ReportGenerateFromtoTo", "Present", Q_NULLPTR));
        radioButton_absent->setText(QApplication::translate("ReportGenerateFromtoTo", "Absent", Q_NULLPTR));
        pushButton_reset->setText(QApplication::translate("ReportGenerateFromtoTo", "Reset", Q_NULLPTR));
        pushButton_generate->setText(QApplication::translate("ReportGenerateFromtoTo", "Generate", Q_NULLPTR));
        pushButton_export_as_pdf->setText(QApplication::translate("ReportGenerateFromtoTo", "Export as PDF", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReportGenerateFromtoTo: public Ui_ReportGenerateFromtoTo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTGENERATEFROMTOTO_H
