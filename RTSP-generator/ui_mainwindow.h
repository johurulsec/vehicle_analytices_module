/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btnSendProb;
    QPushButton *btnGetDeviceInformation;
    QPushButton *btnGetMediaURL;
    QComboBox *onvifDevCB;
    QPushButton *btnPTZTest;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *btnReceiverTest;
    QLabel *label_8;
    QPushButton *btnEventTest;
    QLabel *label_9;
    QPushButton *btnAnalyticsTest;
    QLabel *label_10;
    QPushButton *btnVideoAnalyticsDeviceTest;
    QPushButton *btnRecordingControlTest;
    QLabel *label_11;
    QPushButton *btnRecordingSearchTest;
    QLabel *label_12;
    QPushButton *btnReplayControlTest;
    QLabel *label_13;
    QPushButton *btnDisplayTest;
    QLabel *label_14;
    QLineEdit *pass_lineEdit;
    QLineEdit *ip_edit;
    QPushButton *pushButton;
    QLabel *rtsp_label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1051, 539);
        MainWindow->setContextMenuPolicy(Qt::CustomContextMenu);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btnSendProb = new QPushButton(centralWidget);
        btnSendProb->setObjectName(QStringLiteral("btnSendProb"));
        btnSendProb->setGeometry(QRect(10, 110, 151, 23));
        btnGetDeviceInformation = new QPushButton(centralWidget);
        btnGetDeviceInformation->setObjectName(QStringLiteral("btnGetDeviceInformation"));
        btnGetDeviceInformation->setGeometry(QRect(10, 140, 151, 23));
        btnGetMediaURL = new QPushButton(centralWidget);
        btnGetMediaURL->setObjectName(QStringLiteral("btnGetMediaURL"));
        btnGetMediaURL->setGeometry(QRect(10, 170, 151, 23));
        onvifDevCB = new QComboBox(centralWidget);
        onvifDevCB->setObjectName(QStringLiteral("onvifDevCB"));
        onvifDevCB->setGeometry(QRect(540, 140, 371, 22));
        btnPTZTest = new QPushButton(centralWidget);
        btnPTZTest->setObjectName(QStringLiteral("btnPTZTest"));
        btnPTZTest->setGeometry(QRect(10, 200, 151, 23));
        label_1 = new QLabel(centralWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(180, 140, 241, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(180, 170, 181, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(180, 200, 181, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(180, 110, 191, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(680, 110, 81, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 10, 991, 81));
        QFont font;
        font.setPointSize(12);
        font.setItalic(false);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_6->setWordWrap(true);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(180, 230, 211, 16));
        btnReceiverTest = new QPushButton(centralWidget);
        btnReceiverTest->setObjectName(QStringLiteral("btnReceiverTest"));
        btnReceiverTest->setGeometry(QRect(10, 230, 151, 23));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(180, 260, 191, 16));
        btnEventTest = new QPushButton(centralWidget);
        btnEventTest->setObjectName(QStringLiteral("btnEventTest"));
        btnEventTest->setGeometry(QRect(10, 260, 151, 23));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(180, 290, 201, 16));
        btnAnalyticsTest = new QPushButton(centralWidget);
        btnAnalyticsTest->setObjectName(QStringLiteral("btnAnalyticsTest"));
        btnAnalyticsTest->setGeometry(QRect(10, 290, 151, 23));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(180, 320, 291, 21));
        btnVideoAnalyticsDeviceTest = new QPushButton(centralWidget);
        btnVideoAnalyticsDeviceTest->setObjectName(QStringLiteral("btnVideoAnalyticsDeviceTest"));
        btnVideoAnalyticsDeviceTest->setGeometry(QRect(10, 320, 151, 23));
        btnRecordingControlTest = new QPushButton(centralWidget);
        btnRecordingControlTest->setObjectName(QStringLiteral("btnRecordingControlTest"));
        btnRecordingControlTest->setGeometry(QRect(10, 350, 151, 23));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(180, 350, 291, 16));
        btnRecordingSearchTest = new QPushButton(centralWidget);
        btnRecordingSearchTest->setObjectName(QStringLiteral("btnRecordingSearchTest"));
        btnRecordingSearchTest->setGeometry(QRect(10, 380, 151, 23));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(180, 380, 281, 16));
        btnReplayControlTest = new QPushButton(centralWidget);
        btnReplayControlTest->setObjectName(QStringLiteral("btnReplayControlTest"));
        btnReplayControlTest->setGeometry(QRect(10, 410, 151, 23));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(180, 410, 261, 16));
        btnDisplayTest = new QPushButton(centralWidget);
        btnDisplayTest->setObjectName(QStringLiteral("btnDisplayTest"));
        btnDisplayTest->setGeometry(QRect(10, 440, 151, 23));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(180, 440, 211, 16));
        pass_lineEdit = new QLineEdit(centralWidget);
        pass_lineEdit->setObjectName(QStringLiteral("pass_lineEdit"));
        pass_lineEdit->setGeometry(QRect(690, 320, 113, 31));
        ip_edit = new QLineEdit(centralWidget);
        ip_edit->setObjectName(QStringLiteral("ip_edit"));
        ip_edit->setGeometry(QRect(550, 320, 131, 31));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(820, 320, 89, 25));
        rtsp_label = new QLabel(centralWidget);
        rtsp_label->setObjectName(QStringLiteral("rtsp_label"));
        rtsp_label->setGeometry(QRect(550, 180, 361, 61));
        MainWindow->setCentralWidget(centralWidget);
        btnVideoAnalyticsDeviceTest->raise();
        btnSendProb->raise();
        btnGetDeviceInformation->raise();
        btnGetMediaURL->raise();
        onvifDevCB->raise();
        btnPTZTest->raise();
        label_1->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        label_7->raise();
        btnReceiverTest->raise();
        label_8->raise();
        btnEventTest->raise();
        label_9->raise();
        btnAnalyticsTest->raise();
        label_10->raise();
        btnRecordingControlTest->raise();
        label_11->raise();
        btnRecordingSearchTest->raise();
        label_12->raise();
        btnReplayControlTest->raise();
        label_13->raise();
        btnDisplayTest->raise();
        label_14->raise();
        pass_lineEdit->raise();
        ip_edit->raise();
        pushButton->raise();
        rtsp_label->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1051, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OnvifClientTest", Q_NULLPTR));
        btnSendProb->setText(QApplication::translate("MainWindow", "Discover sendProb", Q_NULLPTR));
        btnGetDeviceInformation->setText(QApplication::translate("MainWindow", "getDeviceInformation", Q_NULLPTR));
        btnGetMediaURL->setText(QApplication::translate("MainWindow", "getMediaURL", Q_NULLPTR));
        btnPTZTest->setText(QApplication::translate("MainWindow", "ptz", Q_NULLPTR));
        label_1->setText(QApplication::translate("MainWindow", "Onvif DeviceManager service test", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Onvif Media service test", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Onvif PTZ service test", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Onvif discover service test", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Device list", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "This is a test program wich we can test onvif services. First press Discover sendProb to find onvif devices on network. (c) SIGMIND Inc.\n"
" ", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Onvif Receiver service test", Q_NULLPTR));
        btnReceiverTest->setText(QApplication::translate("MainWindow", "Receiver", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Onvif Event service test", Q_NULLPTR));
        btnEventTest->setText(QApplication::translate("MainWindow", "Event", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Onvif Analytics service test", Q_NULLPTR));
        btnAnalyticsTest->setText(QApplication::translate("MainWindow", "Analytics", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Onvif VideoAnalyticsDevice service test", Q_NULLPTR));
        btnVideoAnalyticsDeviceTest->setText(QApplication::translate("MainWindow", "VideoAnalyticsDevice", Q_NULLPTR));
        btnRecordingControlTest->setText(QApplication::translate("MainWindow", "RecordingControl", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Onvif RecordingControl service test", Q_NULLPTR));
        btnRecordingSearchTest->setText(QApplication::translate("MainWindow", "RecordingSearch", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Onvif RecordingSearch service test", Q_NULLPTR));
        btnReplayControlTest->setText(QApplication::translate("MainWindow", "ReplayControl", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Onvif ReplayControl service test", Q_NULLPTR));
        btnDisplayTest->setText(QApplication::translate("MainWindow", "Display", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "Onvif Display service test", Q_NULLPTR));
        pass_lineEdit->setText(QApplication::translate("MainWindow", "password", Q_NULLPTR));
        ip_edit->setText(QApplication::translate("MainWindow", "IP Address", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Login", Q_NULLPTR));
        rtsp_label->setText(QApplication::translate("MainWindow", "Login to Generate", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
