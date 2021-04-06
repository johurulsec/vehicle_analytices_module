/********************************************************************************
** Form generated from reading UI file 'webcam.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBCAM_H
#define UI_WEBCAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "qcameraviewfinder.h"

QT_BEGIN_NAMESPACE

class Ui_WebCam
{
public:
    QPushButton *takeImageButton;
    QStackedWidget *stackedWidget;
    QWidget *viewfinderPage;
    QGridLayout *gridLayout_5;
    QCameraViewfinder *viewfinder;
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QWidget *previewPage;
    QGridLayout *gridLayout_4;

    void setupUi(QWidget *WebCam)
    {
        if (WebCam->objectName().isEmpty())
            WebCam->setObjectName(QStringLiteral("WebCam"));
        WebCam->resize(537, 415);
        takeImageButton = new QPushButton(WebCam);
        takeImageButton->setObjectName(QStringLiteral("takeImageButton"));
        takeImageButton->setEnabled(false);
        takeImageButton->setGeometry(QRect(200, 380, 108, 25));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/shutter.svg"), QSize(), QIcon::Normal, QIcon::Off);
        takeImageButton->setIcon(icon);
        stackedWidget = new QStackedWidget(WebCam);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 10, 518, 368));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(145, 145, 145, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        stackedWidget->setPalette(palette);
        viewfinderPage = new QWidget();
        viewfinderPage->setObjectName(QStringLiteral("viewfinderPage"));
        gridLayout_5 = new QGridLayout(viewfinderPage);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        viewfinder = new QCameraViewfinder(viewfinderPage);
        viewfinder->setObjectName(QStringLiteral("viewfinder"));
        viewfinder->setMinimumSize(QSize(500, 350));
        centralwidget = new QWidget(viewfinder);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setGeometry(QRect(-10, 130, 520, 370));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));

        gridLayout_5->addWidget(viewfinder, 0, 0, 1, 1);

        stackedWidget->addWidget(viewfinderPage);
        previewPage = new QWidget();
        previewPage->setObjectName(QStringLiteral("previewPage"));
        gridLayout_4 = new QGridLayout(previewPage);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        stackedWidget->addWidget(previewPage);

        retranslateUi(WebCam);
        QObject::connect(takeImageButton, SIGNAL(clicked()), WebCam, SLOT(takeImage()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WebCam);
    } // setupUi

    void retranslateUi(QWidget *WebCam)
    {
        WebCam->setWindowTitle(QApplication::translate("WebCam", "WebCam", Q_NULLPTR));
        takeImageButton->setText(QApplication::translate("WebCam", "Capture Photo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WebCam: public Ui_WebCam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBCAM_H
