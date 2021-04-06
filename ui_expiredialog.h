/********************************************************************************
** Form generated from reading UI file 'expiredialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPIREDIALOG_H
#define UI_EXPIREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_expireDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *aboutImage;
    QLabel *label_3;
    QLabel *expireInfo;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *expireDialog)
    {
        if (expireDialog->objectName().isEmpty())
            expireDialog->setObjectName(QStringLiteral("expireDialog"));
        expireDialog->resize(625, 374);
        verticalLayout = new QVBoxLayout(expireDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        aboutImage = new QLabel(expireDialog);
        aboutImage->setObjectName(QStringLiteral("aboutImage"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(aboutImage->sizePolicy().hasHeightForWidth());
        aboutImage->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(aboutImage, 0, Qt::AlignHCenter);

        label_3 = new QLabel(expireDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMinimumSize(QSize(0, 10));
        label_3->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_3, 0, Qt::AlignHCenter);

        expireInfo = new QLabel(expireDialog);
        expireInfo->setObjectName(QStringLiteral("expireInfo"));
        sizePolicy1.setHeightForWidth(expireInfo->sizePolicy().hasHeightForWidth());
        expireInfo->setSizePolicy(sizePolicy1);
        expireInfo->setMinimumSize(QSize(0, 10));
        expireInfo->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(expireInfo, 0, Qt::AlignHCenter);

        label = new QLabel(expireDialog);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(0, 10));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        label_2 = new QLabel(expireDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(0, 10));

        verticalLayout->addWidget(label_2, 0, Qt::AlignHCenter);


        retranslateUi(expireDialog);

        QMetaObject::connectSlotsByName(expireDialog);
    } // setupUi

    void retranslateUi(QDialog *expireDialog)
    {
        expireDialog->setWindowTitle(QApplication::translate("expireDialog", "Dialog", Q_NULLPTR));
        aboutImage->setText(QApplication::translate("expireDialog", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("expireDialog", "Error :", Q_NULLPTR));
        expireInfo->setText(QApplication::translate("expireDialog", "Check your Internet connection", Q_NULLPTR));
        label->setText(QApplication::translate("expireDialog", "Or", Q_NULLPTR));
        label_2->setText(QApplication::translate("expireDialog", "Check your license validity", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class expireDialog: public Ui_expireDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPIREDIALOG_H
