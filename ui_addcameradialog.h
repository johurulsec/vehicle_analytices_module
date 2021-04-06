/********************************************************************************
** Form generated from reading UI file 'addcameradialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCAMERADIALOG_H
#define UI_ADDCAMERADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddCameraDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameLineEdit;
    QLabel *label_2;
    QLineEdit *linkLineEdit;
    QRadioButton *ptzButton;
    QRadioButton *facePrior;
    QRadioButton *lprPrior;
    QRadioButton *radioButton_3;
    QFrame *line;
    QTextBrowser *textBrowser;
    QComboBox *camerasComboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddCameraDialog)
    {
        if (AddCameraDialog->objectName().isEmpty())
            AddCameraDialog->setObjectName(QStringLiteral("AddCameraDialog"));
        AddCameraDialog->resize(439, 397);
        verticalLayout = new QVBoxLayout(AddCameraDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(AddCameraDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        nameLineEdit = new QLineEdit(groupBox_2);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameLineEdit);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        linkLineEdit = new QLineEdit(groupBox_2);
        linkLineEdit->setObjectName(QStringLiteral("linkLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, linkLineEdit);

        ptzButton = new QRadioButton(groupBox_2);
        ptzButton->setObjectName(QStringLiteral("ptzButton"));
        QPalette palette;
        QBrush brush(QColor(170, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        QBrush brush2(QColor(212, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush2);
        QBrush brush3(QColor(85, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush3);
        QBrush brush4(QColor(113, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush4);
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush5);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush5);
        QBrush brush7(QColor(212, 127, 127, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush5);
        ptzButton->setPalette(palette);

        formLayout->setWidget(2, QFormLayout::FieldRole, ptzButton);

        facePrior = new QRadioButton(groupBox_2);
        facePrior->setObjectName(QStringLiteral("facePrior"));

        formLayout->setWidget(5, QFormLayout::FieldRole, facePrior);

        lprPrior = new QRadioButton(groupBox_2);
        lprPrior->setObjectName(QStringLiteral("lprPrior"));

        formLayout->setWidget(6, QFormLayout::FieldRole, lprPrior);

        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        formLayout->setWidget(7, QFormLayout::FieldRole, radioButton_3);

        line = new QFrame(groupBox_2);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(3, QFormLayout::SpanningRole, line);

        textBrowser = new QTextBrowser(groupBox_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        formLayout->setWidget(4, QFormLayout::FieldRole, textBrowser);


        verticalLayout_3->addLayout(formLayout);

        camerasComboBox = new QComboBox(groupBox_2);
        camerasComboBox->setObjectName(QStringLiteral("camerasComboBox"));

        verticalLayout_3->addWidget(camerasComboBox);


        verticalLayout_2->addWidget(groupBox_2);


        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(AddCameraDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AddCameraDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddCameraDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddCameraDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddCameraDialog);
    } // setupUi

    void retranslateUi(QDialog *AddCameraDialog)
    {
        AddCameraDialog->setWindowTitle(QApplication::translate("AddCameraDialog", "Dialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("AddCameraDialog", "Add Camera", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("AddCameraDialog", "Camera list", Q_NULLPTR));
        label->setText(QApplication::translate("AddCameraDialog", "Camera Name", Q_NULLPTR));
        label_2->setText(QApplication::translate("AddCameraDialog", "Camera Link", Q_NULLPTR));
        ptzButton->setText(QApplication::translate("AddCameraDialog", "PTZ ??", Q_NULLPTR));
        facePrior->setText(QApplication::translate("AddCameraDialog", "Face Priority", Q_NULLPTR));
        lprPrior->setText(QApplication::translate("AddCameraDialog", "License Plate Priority", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("AddCameraDialog", "General", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("AddCameraDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600; text-decoration: underline; color:#aa0000;\">Select Your Priority Modes</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddCameraDialog: public Ui_AddCameraDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCAMERADIALOG_H
