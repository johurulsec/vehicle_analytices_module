/********************************************************************************
** Form generated from reading UI file 'registerfacedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERFACEDIALOG_H
#define UI_REGISTERFACEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registerFaceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *imageLabel;
    QWidget *formWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameFace;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout;
    QLabel *statusLabel;

    void setupUi(QDialog *registerFaceDialog)
    {
        if (registerFaceDialog->objectName().isEmpty())
            registerFaceDialog->setObjectName(QStringLiteral("registerFaceDialog"));
        registerFaceDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(registerFaceDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(registerFaceDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_2, 0, Qt::AlignTop);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        imageLabel = new QLabel(registerFaceDialog);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));

        horizontalLayout_4->addWidget(imageLabel, 0, Qt::AlignHCenter);


        verticalLayout->addLayout(horizontalLayout_4);

        formWidget = new QWidget(registerFaceDialog);
        formWidget->setObjectName(QStringLiteral("formWidget"));
        sizePolicy.setHeightForWidth(formWidget->sizePolicy().hasHeightForWidth());
        formWidget->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(formWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(formWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        nameFace = new QLineEdit(formWidget);
        nameFace->setObjectName(QStringLiteral("nameFace"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameFace);


        verticalLayout->addWidget(formWidget);

        buttonBox = new QDialogButtonBox(registerFaceDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        statusLabel = new QLabel(registerFaceDialog);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusLabel->sizePolicy().hasHeightForWidth());
        statusLabel->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(statusLabel, 0, Qt::AlignRight);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(registerFaceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), registerFaceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), registerFaceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(registerFaceDialog);
    } // setupUi

    void retranslateUi(QDialog *registerFaceDialog)
    {
        registerFaceDialog->setWindowTitle(QApplication::translate("registerFaceDialog", "Dialog", Q_NULLPTR));
        label_2->setText(QApplication::translate("registerFaceDialog", "Add Face for recognition", Q_NULLPTR));
        imageLabel->setText(QApplication::translate("registerFaceDialog", "TextLabel", Q_NULLPTR));
        label->setText(QApplication::translate("registerFaceDialog", "Name", Q_NULLPTR));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class registerFaceDialog: public Ui_registerFaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERFACEDIALOG_H
