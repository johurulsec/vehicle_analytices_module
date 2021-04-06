/********************************************************************************
** Form generated from reading UI file 'mainwindow_onvif.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_ONVIF_H
#define UI_MAINWINDOW_ONVIF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_onvif
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_header;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_rtsp;
    QLineEdit *Username_edit;
    QComboBox *onvifDevCB;
    QPushButton *pushButton_login;
    QPushButton *display_video;
    QPushButton *btnSendProb;
    QSpacerItem *horizontalSpacer;
    QLineEdit *pass_lineEdit;
    QPushButton *row_up;
    QPushButton *row_down;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QComboBox *movement_step;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *ZoomIn;
    QLabel *label_2;
    QPushButton *ZoomOut;
    QGridLayout *gridLayout_3;
    QPushButton *leftlower;
    QPushButton *left;
    QPushButton *middle_circle;
    QPushButton *down;
    QPushButton *leftupper;
    QPushButton *up;
    QPushButton *rightupper;
    QPushButton *right;
    QPushButton *rightlower;
    QPushButton *pushButton_add;
    QPushButton *pushButton_remove;
    QPushButton *Undo_remove;
    QPushButton *pushButton_write;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow_onvif)
    {
        if (MainWindow_onvif->objectName().isEmpty())
            MainWindow_onvif->setObjectName(QStringLiteral("MainWindow_onvif"));
        MainWindow_onvif->resize(1016, 515);
        centralWidget = new QWidget(MainWindow_onvif);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_header = new QLabel(centralWidget);
        label_header->setObjectName(QStringLiteral("label_header"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label_header->setFont(font);
        label_header->setAlignment(Qt::AlignCenter);
        label_header->setMargin(1);
        label_header->setIndent(-1);

        verticalLayout->addWidget(label_header);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_2->setVerticalSpacing(6);
        lineEdit_rtsp = new QLineEdit(centralWidget);
        lineEdit_rtsp->setObjectName(QStringLiteral("lineEdit_rtsp"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_rtsp->sizePolicy().hasHeightForWidth());
        lineEdit_rtsp->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(lineEdit_rtsp, 2, 0, 1, 3);

        Username_edit = new QLineEdit(centralWidget);
        Username_edit->setObjectName(QStringLiteral("Username_edit"));
        sizePolicy.setHeightForWidth(Username_edit->sizePolicy().hasHeightForWidth());
        Username_edit->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(Username_edit, 1, 0, 1, 1);

        onvifDevCB = new QComboBox(centralWidget);
        onvifDevCB->setObjectName(QStringLiteral("onvifDevCB"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(onvifDevCB->sizePolicy().hasHeightForWidth());
        onvifDevCB->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(onvifDevCB, 0, 0, 1, 3);

        pushButton_login = new QPushButton(centralWidget);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_login->sizePolicy().hasHeightForWidth());
        pushButton_login->setSizePolicy(sizePolicy2);
        pushButton_login->setMaximumSize(QSize(58, 25));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_login->setFont(font1);

        gridLayout_2->addWidget(pushButton_login, 1, 3, 1, 1);

        display_video = new QPushButton(centralWidget);
        display_video->setObjectName(QStringLiteral("display_video"));
        sizePolicy2.setHeightForWidth(display_video->sizePolicy().hasHeightForWidth());
        display_video->setSizePolicy(sizePolicy2);
        display_video->setMaximumSize(QSize(58, 25));
        display_video->setFont(font1);

        gridLayout_2->addWidget(display_video, 2, 3, 1, 1);

        btnSendProb = new QPushButton(centralWidget);
        btnSendProb->setObjectName(QStringLiteral("btnSendProb"));
        sizePolicy2.setHeightForWidth(btnSendProb->sizePolicy().hasHeightForWidth());
        btnSendProb->setSizePolicy(sizePolicy2);
        btnSendProb->setMaximumSize(QSize(58, 25));
        btnSendProb->setBaseSize(QSize(0, 0));
        btnSendProb->setFont(font1);

        gridLayout_2->addWidget(btnSendProb, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 1, 1, 1);

        pass_lineEdit = new QLineEdit(centralWidget);
        pass_lineEdit->setObjectName(QStringLiteral("pass_lineEdit"));
        sizePolicy.setHeightForWidth(pass_lineEdit->sizePolicy().hasHeightForWidth());
        pass_lineEdit->setSizePolicy(sizePolicy);
        pass_lineEdit->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(pass_lineEdit, 1, 2, 1, 1);

        row_up = new QPushButton(centralWidget);
        row_up->setObjectName(QStringLiteral("row_up"));
        row_up->setMinimumSize(QSize(25, 25));
        row_up->setMaximumSize(QSize(25, 25));

        gridLayout_2->addWidget(row_up, 0, 5, 1, 1);

        row_down = new QPushButton(centralWidget);
        row_down->setObjectName(QStringLiteral("row_down"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(row_down->sizePolicy().hasHeightForWidth());
        row_down->setSizePolicy(sizePolicy3);
        row_down->setMinimumSize(QSize(25, 25));
        row_down->setMaximumSize(QSize(25, 25));

        gridLayout_2->addWidget(row_down, 1, 5, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));

        horizontalLayout_5->addLayout(horizontalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        movement_step = new QComboBox(centralWidget);
        movement_step->setObjectName(QStringLiteral("movement_step"));

        verticalLayout_4->addWidget(movement_step);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, -1, 0, -1);
        ZoomIn = new QPushButton(centralWidget);
        ZoomIn->setObjectName(QStringLiteral("ZoomIn"));
        sizePolicy3.setHeightForWidth(ZoomIn->sizePolicy().hasHeightForWidth());
        ZoomIn->setSizePolicy(sizePolicy3);
        ZoomIn->setMinimumSize(QSize(40, 35));
        ZoomIn->setMaximumSize(QSize(40, 35));

        horizontalLayout_4->addWidget(ZoomIn);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setMinimumSize(QSize(40, 35));
        label_2->setMaximumSize(QSize(40, 35));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_2);

        ZoomOut = new QPushButton(centralWidget);
        ZoomOut->setObjectName(QStringLiteral("ZoomOut"));
        sizePolicy3.setHeightForWidth(ZoomOut->sizePolicy().hasHeightForWidth());
        ZoomOut->setSizePolicy(sizePolicy3);
        ZoomOut->setMinimumSize(QSize(40, 35));
        ZoomOut->setMaximumSize(QSize(40, 35));

        horizontalLayout_4->addWidget(ZoomOut);


        verticalLayout_4->addLayout(horizontalLayout_4);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        leftlower = new QPushButton(centralWidget);
        leftlower->setObjectName(QStringLiteral("leftlower"));
        sizePolicy3.setHeightForWidth(leftlower->sizePolicy().hasHeightForWidth());
        leftlower->setSizePolicy(sizePolicy3);
        leftlower->setMinimumSize(QSize(40, 35));
        leftlower->setMaximumSize(QSize(40, 35));

        gridLayout_3->addWidget(leftlower, 2, 0, 1, 1);

        left = new QPushButton(centralWidget);
        left->setObjectName(QStringLiteral("left"));
        sizePolicy3.setHeightForWidth(left->sizePolicy().hasHeightForWidth());
        left->setSizePolicy(sizePolicy3);
        left->setMinimumSize(QSize(40, 35));
        left->setMaximumSize(QSize(40, 35));

        gridLayout_3->addWidget(left, 1, 0, 1, 1);

        middle_circle = new QPushButton(centralWidget);
        middle_circle->setObjectName(QStringLiteral("middle_circle"));
        sizePolicy3.setHeightForWidth(middle_circle->sizePolicy().hasHeightForWidth());
        middle_circle->setSizePolicy(sizePolicy3);
        middle_circle->setMinimumSize(QSize(40, 35));
        middle_circle->setMaximumSize(QSize(40, 35));

        gridLayout_3->addWidget(middle_circle, 1, 1, 1, 1);

        down = new QPushButton(centralWidget);
        down->setObjectName(QStringLiteral("down"));
        sizePolicy3.setHeightForWidth(down->sizePolicy().hasHeightForWidth());
        down->setSizePolicy(sizePolicy3);
        down->setMinimumSize(QSize(40, 35));
        down->setMaximumSize(QSize(40, 35));

        gridLayout_3->addWidget(down, 2, 1, 1, 1);

        leftupper = new QPushButton(centralWidget);
        leftupper->setObjectName(QStringLiteral("leftupper"));
        sizePolicy3.setHeightForWidth(leftupper->sizePolicy().hasHeightForWidth());
        leftupper->setSizePolicy(sizePolicy3);
        leftupper->setMinimumSize(QSize(40, 35));
        leftupper->setMaximumSize(QSize(40, 35));

        gridLayout_3->addWidget(leftupper, 0, 0, 1, 1);

        up = new QPushButton(centralWidget);
        up->setObjectName(QStringLiteral("up"));
        sizePolicy3.setHeightForWidth(up->sizePolicy().hasHeightForWidth());
        up->setSizePolicy(sizePolicy3);
        up->setMinimumSize(QSize(40, 35));
        up->setMaximumSize(QSize(40, 35));

        gridLayout_3->addWidget(up, 0, 1, 1, 1);

        rightupper = new QPushButton(centralWidget);
        rightupper->setObjectName(QStringLiteral("rightupper"));
        sizePolicy3.setHeightForWidth(rightupper->sizePolicy().hasHeightForWidth());
        rightupper->setSizePolicy(sizePolicy3);
        rightupper->setMinimumSize(QSize(40, 35));
        rightupper->setMaximumSize(QSize(40, 35));

        gridLayout_3->addWidget(rightupper, 0, 2, 1, 1);

        right = new QPushButton(centralWidget);
        right->setObjectName(QStringLiteral("right"));
        sizePolicy3.setHeightForWidth(right->sizePolicy().hasHeightForWidth());
        right->setSizePolicy(sizePolicy3);
        right->setMinimumSize(QSize(40, 35));
        right->setMaximumSize(QSize(40, 35));

        gridLayout_3->addWidget(right, 1, 2, 1, 1);

        rightlower = new QPushButton(centralWidget);
        rightlower->setObjectName(QStringLiteral("rightlower"));
        sizePolicy3.setHeightForWidth(rightlower->sizePolicy().hasHeightForWidth());
        rightlower->setSizePolicy(sizePolicy3);
        rightlower->setMinimumSize(QSize(40, 35));
        rightlower->setMaximumSize(QSize(40, 35));

        gridLayout_3->addWidget(rightlower, 2, 2, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);

        pushButton_add = new QPushButton(centralWidget);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));
        sizePolicy1.setHeightForWidth(pushButton_add->sizePolicy().hasHeightForWidth());
        pushButton_add->setSizePolicy(sizePolicy1);
        pushButton_add->setMaximumSize(QSize(16777215, 40));
        pushButton_add->setFont(font1);

        verticalLayout_4->addWidget(pushButton_add);

        pushButton_remove = new QPushButton(centralWidget);
        pushButton_remove->setObjectName(QStringLiteral("pushButton_remove"));
        sizePolicy1.setHeightForWidth(pushButton_remove->sizePolicy().hasHeightForWidth());
        pushButton_remove->setSizePolicy(sizePolicy1);
        pushButton_remove->setMaximumSize(QSize(16777215, 40));
        pushButton_remove->setFont(font1);

        verticalLayout_4->addWidget(pushButton_remove);

        Undo_remove = new QPushButton(centralWidget);
        Undo_remove->setObjectName(QStringLiteral("Undo_remove"));
        sizePolicy1.setHeightForWidth(Undo_remove->sizePolicy().hasHeightForWidth());
        Undo_remove->setSizePolicy(sizePolicy1);
        Undo_remove->setMaximumSize(QSize(16777215, 40));
        Undo_remove->setFont(font1);

        verticalLayout_4->addWidget(Undo_remove);

        pushButton_write = new QPushButton(centralWidget);
        pushButton_write->setObjectName(QStringLiteral("pushButton_write"));
        sizePolicy1.setHeightForWidth(pushButton_write->sizePolicy().hasHeightForWidth());
        pushButton_write->setSizePolicy(sizePolicy1);
        pushButton_write->setMaximumSize(QSize(16777215, 40));
        pushButton_write->setFont(font1);

        verticalLayout_4->addWidget(pushButton_write);

        verticalLayout_4->setStretch(0, 3);
        verticalLayout_4->setStretch(1, 3);
        verticalLayout_4->setStretch(2, 5);
        verticalLayout_4->setStretch(3, 3);
        verticalLayout_4->setStretch(4, 3);
        verticalLayout_4->setStretch(5, 3);
        verticalLayout_4->setStretch(6, 3);

        horizontalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout_5->setStretch(0, 8);
        horizontalLayout_5->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 2);

        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setRowCount(0);

        gridLayout->addWidget(tableWidget, 0, 2, 2, 1);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(1, 7);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 2);
        gridLayout->setColumnStretch(2, 2);

        verticalLayout->addLayout(gridLayout);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 35);

        gridLayout_4->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow_onvif->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow_onvif);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1016, 22));
        MainWindow_onvif->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow_onvif);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow_onvif->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow_onvif);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow_onvif->setStatusBar(statusBar);

        retranslateUi(MainWindow_onvif);

        QMetaObject::connectSlotsByName(MainWindow_onvif);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_onvif)
    {
        MainWindow_onvif->setWindowTitle(QApplication::translate("MainWindow_onvif", "MainWindow_onvif", Q_NULLPTR));
        label_header->setText(QApplication::translate("MainWindow_onvif", "WatchCam", Q_NULLPTR));
        Username_edit->setPlaceholderText(QApplication::translate("MainWindow_onvif", "Username", Q_NULLPTR));
        pushButton_login->setText(QApplication::translate("MainWindow_onvif", "LogIn", Q_NULLPTR));
        display_video->setText(QApplication::translate("MainWindow_onvif", "View", Q_NULLPTR));
        btnSendProb->setText(QApplication::translate("MainWindow_onvif", "Search", Q_NULLPTR));
        pass_lineEdit->setPlaceholderText(QApplication::translate("MainWindow_onvif", "Password", Q_NULLPTR));
        row_up->setText(QString());
        row_down->setText(QString());
        ZoomIn->setText(QString());
        label_2->setText(QApplication::translate("MainWindow_onvif", "Zoom", Q_NULLPTR));
        ZoomOut->setText(QString());
        leftlower->setText(QString());
        left->setText(QString());
        middle_circle->setText(QString());
        down->setText(QString());
        leftupper->setText(QString());
        up->setText(QString());
        rightupper->setText(QString());
        right->setText(QString());
        rightlower->setText(QString());
        pushButton_add->setText(QApplication::translate("MainWindow_onvif", "Add", Q_NULLPTR));
        pushButton_remove->setText(QApplication::translate("MainWindow_onvif", "Remove", Q_NULLPTR));
        Undo_remove->setText(QApplication::translate("MainWindow_onvif", "Undo", Q_NULLPTR));
        pushButton_write->setText(QApplication::translate("MainWindow_onvif", "Save", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow_onvif", "IP Address", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow_onvif", "Port", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow_onvif", "RTSP url", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_onvif: public Ui_MainWindow_onvif {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_ONVIF_H
