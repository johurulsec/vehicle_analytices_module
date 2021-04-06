/********************************************************************************
** Form generated from reading UI file 'emailbox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMAILBOX_H
#define UI_EMAILBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmailBox
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *EmailBox)
    {
        if (EmailBox->objectName().isEmpty())
            EmailBox->setObjectName(QStringLiteral("EmailBox"));
        EmailBox->resize(400, 32);
        horizontalLayout = new QHBoxLayout(EmailBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(EmailBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(EmailBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        retranslateUi(EmailBox);

        QMetaObject::connectSlotsByName(EmailBox);
    } // setupUi

    void retranslateUi(QWidget *EmailBox)
    {
        EmailBox->setWindowTitle(QApplication::translate("EmailBox", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("EmailBox", "Remove", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EmailBox: public Ui_EmailBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMAILBOX_H
