/********************************************************************************
** Form generated from reading UI file 'progressbarloading.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSBARLOADING_H
#define UI_PROGRESSBARLOADING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_ProgressBarLoading
{
public:
    QProgressBar *progressBar_loading;

    void setupUi(QDialog *ProgressBarLoading)
    {
        if (ProgressBarLoading->objectName().isEmpty())
            ProgressBarLoading->setObjectName(QStringLiteral("ProgressBarLoading"));
        ProgressBarLoading->resize(306, 85);
        ProgressBarLoading->setMinimumSize(QSize(306, 85));
        ProgressBarLoading->setMaximumSize(QSize(306, 85));
        progressBar_loading = new QProgressBar(ProgressBarLoading);
        progressBar_loading->setObjectName(QStringLiteral("progressBar_loading"));
        progressBar_loading->setGeometry(QRect(0, 30, 306, 23));
        progressBar_loading->setMinimumSize(QSize(306, 23));
        progressBar_loading->setMaximumSize(QSize(306, 23));
        progressBar_loading->setValue(24);

        retranslateUi(ProgressBarLoading);

        QMetaObject::connectSlotsByName(ProgressBarLoading);
    } // setupUi

    void retranslateUi(QDialog *ProgressBarLoading)
    {
        ProgressBarLoading->setWindowTitle(QApplication::translate("ProgressBarLoading", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProgressBarLoading: public Ui_ProgressBarLoading {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSBARLOADING_H
