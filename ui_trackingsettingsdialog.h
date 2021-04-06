/********************************************************************************
** Form generated from reading UI file 'trackingsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKINGSETTINGSDIALOG_H
#define UI_TRACKINGSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_trackingSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *trackingBox;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *trackingSettingsDialog)
    {
        if (trackingSettingsDialog->objectName().isEmpty())
            trackingSettingsDialog->setObjectName(QStringLiteral("trackingSettingsDialog"));
        trackingSettingsDialog->resize(491, 274);
        verticalLayout = new QVBoxLayout(trackingSettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(trackingSettingsDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        trackingBox = new QHBoxLayout();
        trackingBox->setObjectName(QStringLiteral("trackingBox"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        trackingBox->addWidget(label);


        verticalLayout_2->addLayout(trackingBox);


        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(trackingSettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(trackingSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), trackingSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), trackingSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(trackingSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *trackingSettingsDialog)
    {
        trackingSettingsDialog->setWindowTitle(QApplication::translate("trackingSettingsDialog", "Dialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("trackingSettingsDialog", "GroupBox", Q_NULLPTR));
        label->setText(QApplication::translate("trackingSettingsDialog", "Tracking", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class trackingSettingsDialog: public Ui_trackingSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKINGSETTINGSDIALOG_H
