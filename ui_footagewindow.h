/********************************************************************************
** Form generated from reading UI file 'footagewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOOTAGEWINDOW_H
#define UI_FOOTAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <VLCQtWidgets/WidgetSeek.h>
#include <VLCQtWidgets/WidgetVideo.h>

QT_BEGIN_NAMESPACE

class Ui_footageWindow
{
public:
    QAction *actionPause;
    QAction *actionStop;
    QAction *actionOpen;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *verticalWidget_1;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLineEdit *file;
    QPushButton *browse;
    QPushButton *analyze;
    QHBoxLayout *horizontalLayout;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_3;
    VlcWidgetVideo *video;
    VlcWidgetSeek *seek;
    QWidget *horizontalWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pause;
    QPushButton *stop;
    QWidget *layoutProcessed;
    QVBoxLayout *verticalLayout_5;
    QLabel *imageLabel;
    QWidget *verticalWidget_2;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QScrollArea *scrollAreaAll;
    QWidget *allScrollAreaWidgetContents;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollAreaObject;
    QWidget *objectsScrollAreaWidgetContents;
    QWidget *tab_3;
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea_2;
    QWidget *uniqueScrollAreaWidgetContents;
    QWidget *tab_4;
    QGridLayout *gridLayout_4;
    QScrollArea *scrollArea_3;
    QWidget *facesScrollAreaWidgetContents;
    QPushButton *log;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuControls;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *footageWindow)
    {
        if (footageWindow->objectName().isEmpty())
            footageWindow->setObjectName(QStringLiteral("footageWindow"));
        footageWindow->resize(1114, 800);
        actionPause = new QAction(footageWindow);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        actionStop = new QAction(footageWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionOpen = new QAction(footageWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralwidget = new QWidget(footageWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalWidget_1 = new QWidget(centralwidget);
        verticalWidget_1->setObjectName(QStringLiteral("verticalWidget_1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(verticalWidget_1->sizePolicy().hasHeightForWidth());
        verticalWidget_1->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(verticalWidget_1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(verticalWidget_1);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        file = new QLineEdit(groupBox);
        file->setObjectName(QStringLiteral("file"));

        horizontalLayout_2->addWidget(file);

        browse = new QPushButton(groupBox);
        browse->setObjectName(QStringLiteral("browse"));

        horizontalLayout_2->addWidget(browse);

        analyze = new QPushButton(groupBox);
        analyze->setObjectName(QStringLiteral("analyze"));

        horizontalLayout_2->addWidget(analyze);


        verticalLayout->addWidget(groupBox);


        verticalLayout_2->addWidget(verticalWidget_1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalWidget = new QWidget(centralwidget);
        verticalWidget->setObjectName(QStringLiteral("verticalWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(verticalWidget->sizePolicy().hasHeightForWidth());
        verticalWidget->setSizePolicy(sizePolicy1);
        verticalWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout_3 = new QVBoxLayout(verticalWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        video = new VlcWidgetVideo(verticalWidget);
        video->setObjectName(QStringLiteral("video"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(video->sizePolicy().hasHeightForWidth());
        video->setSizePolicy(sizePolicy2);
        video->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(video);

        seek = new VlcWidgetSeek(verticalWidget);
        seek->setObjectName(QStringLiteral("seek"));
        sizePolicy.setHeightForWidth(seek->sizePolicy().hasHeightForWidth());
        seek->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(seek);

        horizontalWidget_2 = new QWidget(verticalWidget);
        horizontalWidget_2->setObjectName(QStringLiteral("horizontalWidget_2"));
        sizePolicy.setHeightForWidth(horizontalWidget_2->sizePolicy().hasHeightForWidth());
        horizontalWidget_2->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(horizontalWidget_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pause = new QPushButton(horizontalWidget_2);
        pause->setObjectName(QStringLiteral("pause"));
        pause->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(pause);

        stop = new QPushButton(horizontalWidget_2);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(stop);


        verticalLayout_3->addWidget(horizontalWidget_2);


        horizontalLayout->addWidget(verticalWidget);

        layoutProcessed = new QWidget(centralwidget);
        layoutProcessed->setObjectName(QStringLiteral("layoutProcessed"));
        sizePolicy1.setHeightForWidth(layoutProcessed->sizePolicy().hasHeightForWidth());
        layoutProcessed->setSizePolicy(sizePolicy1);
        layoutProcessed->setMaximumSize(QSize(16777215, 16777215));
        layoutProcessed->setStyleSheet(QStringLiteral(""));
        verticalLayout_5 = new QVBoxLayout(layoutProcessed);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        imageLabel = new QLabel(layoutProcessed);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setMinimumSize(QSize(640, 480));
        imageLabel->setMaximumSize(QSize(640, 480));
        imageLabel->setStyleSheet(QStringLiteral(""));

        verticalLayout_5->addWidget(imageLabel, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        horizontalLayout->addWidget(layoutProcessed);

        verticalWidget_2 = new QWidget(centralwidget);
        verticalWidget_2->setObjectName(QStringLiteral("verticalWidget_2"));
        sizePolicy1.setHeightForWidth(verticalWidget_2->sizePolicy().hasHeightForWidth());
        verticalWidget_2->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(verticalWidget_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tabWidget = new QTabWidget(verticalWidget_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollAreaAll = new QScrollArea(tab);
        scrollAreaAll->setObjectName(QStringLiteral("scrollAreaAll"));
        sizePolicy2.setHeightForWidth(scrollAreaAll->sizePolicy().hasHeightForWidth());
        scrollAreaAll->setSizePolicy(sizePolicy2);
        scrollAreaAll->setWidgetResizable(true);
        allScrollAreaWidgetContents = new QWidget();
        allScrollAreaWidgetContents->setObjectName(QStringLiteral("allScrollAreaWidgetContents"));
        allScrollAreaWidgetContents->setGeometry(QRect(0, 0, 198, 548));
        scrollAreaAll->setWidget(allScrollAreaWidgetContents);

        gridLayout->addWidget(scrollAreaAll, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollAreaObject = new QScrollArea(tab_2);
        scrollAreaObject->setObjectName(QStringLiteral("scrollAreaObject"));
        scrollAreaObject->setWidgetResizable(true);
        objectsScrollAreaWidgetContents = new QWidget();
        objectsScrollAreaWidgetContents->setObjectName(QStringLiteral("objectsScrollAreaWidgetContents"));
        objectsScrollAreaWidgetContents->setGeometry(QRect(0, 0, 198, 548));
        scrollAreaObject->setWidget(objectsScrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollAreaObject, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_3 = new QGridLayout(tab_3);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollArea_2 = new QScrollArea(tab_3);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        uniqueScrollAreaWidgetContents = new QWidget();
        uniqueScrollAreaWidgetContents->setObjectName(QStringLiteral("uniqueScrollAreaWidgetContents"));
        uniqueScrollAreaWidgetContents->setGeometry(QRect(0, 0, 198, 548));
        scrollArea_2->setWidget(uniqueScrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_4 = new QGridLayout(tab_4);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        scrollArea_3 = new QScrollArea(tab_4);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        facesScrollAreaWidgetContents = new QWidget();
        facesScrollAreaWidgetContents->setObjectName(QStringLiteral("facesScrollAreaWidgetContents"));
        facesScrollAreaWidgetContents->setGeometry(QRect(0, 0, 198, 548));
        scrollArea_3->setWidget(facesScrollAreaWidgetContents);

        gridLayout_4->addWidget(scrollArea_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());

        verticalLayout_4->addWidget(tabWidget);

        log = new QPushButton(verticalWidget_2);
        log->setObjectName(QStringLiteral("log"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(log->sizePolicy().hasHeightForWidth());
        log->setSizePolicy(sizePolicy3);

        verticalLayout_4->addWidget(log);

        progressBar = new QProgressBar(verticalWidget_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        sizePolicy3.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy3);
        progressBar->setMinimum(0);
        progressBar->setValue(50);

        verticalLayout_4->addWidget(progressBar);


        horizontalLayout->addWidget(verticalWidget_2);


        verticalLayout_2->addLayout(horizontalLayout);

        footageWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(footageWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1114, 19));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuControls = new QMenu(menubar);
        menuControls->setObjectName(QStringLiteral("menuControls"));
        footageWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(footageWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        footageWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuControls->menuAction());
        menuFile->addAction(actionOpen);
        menuControls->addAction(actionPause);
        menuControls->addAction(actionStop);

        retranslateUi(footageWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(footageWindow);
    } // setupUi

    void retranslateUi(QMainWindow *footageWindow)
    {
        footageWindow->setWindowTitle(QApplication::translate("footageWindow", "Footage Analyzer", Q_NULLPTR));
        actionPause->setText(QApplication::translate("footageWindow", "Pause", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionPause->setShortcut(QApplication::translate("footageWindow", "Ctrl+P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionStop->setText(QApplication::translate("footageWindow", "Stop", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionStop->setShortcut(QApplication::translate("footageWindow", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("footageWindow", "Open", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("footageWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        groupBox->setTitle(QApplication::translate("footageWindow", "Analyze video footage", Q_NULLPTR));
        browse->setText(QApplication::translate("footageWindow", "Browse", Q_NULLPTR));
        analyze->setText(QApplication::translate("footageWindow", "Analyze", Q_NULLPTR));
        pause->setText(QApplication::translate("footageWindow", "Pause", Q_NULLPTR));
        stop->setText(QApplication::translate("footageWindow", "Stop", Q_NULLPTR));
        imageLabel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("footageWindow", "All", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("footageWindow", "Objects", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("footageWindow", "Unique Faces", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("footageWindow", "Face times", Q_NULLPTR));
        log->setText(QApplication::translate("footageWindow", "Log details", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("footageWindow", "file", Q_NULLPTR));
        menuControls->setTitle(QApplication::translate("footageWindow", "controls", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class footageWindow: public Ui_footageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOOTAGEWINDOW_H
