/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *settingsTab;
    QWidget *generalTab;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *rtssCheck;
    QCheckBox *rtvsCheck;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *adminPassLine;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QWidget *notificationsTab;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *enableNotCheck;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *activeRadio;
    QRadioButton *activeHoursRadio;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *fromActiveText;
    QLabel *label_2;
    QLineEdit *toActiveText;
    QSpacerItem *horizontalSpacer_18;
    QCheckBox *emailCheck;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_17;
    QVBoxLayout *emailVerticalBox;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *addEmail;
    QSpacerItem *horizontalSpacer_16;
    QCheckBox *smsCheck;
    QHBoxLayout *horizontalLayout_23;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit_3;
    QSpacerItem *horizontalSpacer_17;
    QCheckBox *audibleCheck;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *objectAudibleCheck;
    QCheckBox *faceAudibleCheck;
    QSpacerItem *verticalSpacer_2;
    QWidget *ObjectDetection;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *detectionClassBox;
    QCheckBox *faceCheck;
    QCheckBox *maskedFaceCheck;
    QCheckBox *personCheck;
    QCheckBox *baggageCheck;
    QCheckBox *cellPhoneCheck;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *bicycleCHeck;
    QCheckBox *carCheck;
    QCheckBox *busCheck;
    QCheckBox *motorcycleCheck;
    QCheckBox *truckCheck;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *face_check;
    QCheckBox *lpr_check;
    QCheckBox *knifeCheck;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_4;
    QLabel *obDetText;
    QSpacerItem *horizontalSpacer_9;
    QSlider *objectSensitivitySlider;
    QSpacerItem *verticalSpacer_3;
    QWidget *faceTab;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox_suspect;
    QCheckBox *checkbox_unique_face;
    QCheckBox *checkbox_db_sync;
    QCheckBox *faceRecogCheck;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_14;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_13;
    QLineEdit *faceRecogDirLine;
    QPushButton *faceRecogBrowseBut;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_5;
    QLineEdit *blackListDirLine;
    QPushButton *browseBlackList;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_12;
    QLabel *faceDetText;
    QSpacerItem *horizontalSpacer_12;
    QSlider *faceRecogSenseBar;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_24;
    QSpacerItem *horizontalSpacer_19;
    QVBoxLayout *verticalLayout_18;
    QCheckBox *landmarkCheck;
    QCheckBox *smileCheck;
    QCheckBox *glassCheck;
    QCheckBox *emotionCheck;
    QCheckBox *ageCheck;
    QCheckBox *sexCheck;
    QSpacerItem *verticalSpacer_4;
    QWidget *directoryTab;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_20;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_11;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_15;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QVBoxLayout *verticalLayout_16;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *verticalSpacer_5;
    QWidget *exportTab;
    QWidget *tab_camera_list;
    QPushButton *pushButton_add_camera;
    QScrollArea *scrollArea_cam_list;
    QWidget *scrollAreaWidgetContents_cam_list;
    QTableWidget *tableWidget_cam_list;
    QPushButton *pushButtonlogin;
    QCheckBox *susface;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_ip_3;
    QLabel *label_ip_2;
    QLabel *label_ip;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_19;
    QLineEdit *lineEdit_source_index;
    QLineEdit *lineEdit_port;
    QLineEdit *lineEdit_address;
    QLineEdit *lineEdit_cam_name;
    QLineEdit *lineEdit_cam_pass;
    QLineEdit *lineEdit_cam_uri;
    QWidget *tab;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *label_10;
    QTableWidget *tableWidget_addLPR;
    QPushButton *pushButton_addLPR;
    QRadioButton *radioButton_google_api;
    QRadioButton *radioButton_tess_api;
    QLabel *label_26;
    QWidget *tab_3;
    QLabel *label_111;
    QLabel *label_112;
    QLabel *label_113;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_video_results;
    QPushButton *pushButton_select_video_file;
    QScrollArea *scrollArea_for_image_vda;
    QWidget *scrollAreaWidgetContents_results;
    QLabel *label_75;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_25;
    QVBoxLayout *verticalLayout_24;
    QLabel *label_71;
    QLabel *label_72;
    QVBoxLayout *verticalLayout_20;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_73;
    QDateTimeEdit *dateTimeEdit_from;
    QHBoxLayout *horizontalLayout_43;
    QLabel *label_74;
    QDateTimeEdit *dateTimeEdit_to;
    QVBoxLayout *verticalLayout_21;
    QVBoxLayout *verticalLayout_27;
    QHBoxLayout *horizontalLayout_57;
    QCheckBox *checkBox_face_check;
    QCheckBox *checkBox_person;
    QCheckBox *checkBox_masked_face;
    QHBoxLayout *horizontalLayout_58;
    QCheckBox *checkBox_male;
    QCheckBox *checkBox_female;
    QHBoxLayout *horizontalLayout_59;
    QLabel *label_98;
    QSpacerItem *horizontalSpacer_41;
    QHBoxLayout *horizontalLayout_60;
    QLabel *label_99;
    QSpacerItem *horizontalSpacer_42;
    QLineEdit *lineEdit_age_from;
    QHBoxLayout *horizontalLayout_61;
    QLabel *label_100;
    QSpacerItem *horizontalSpacer_43;
    QLineEdit *lineEdit_25_age_to;
    QPushButton *pushButton_search_for_sub_video_ana;
    QVBoxLayout *verticalLayout_22;
    QHBoxLayout *horizontalLayout_51;
    QLabel *label_85;
    QSpacerItem *horizontalSpacer_35;
    QComboBox *comboBox_vehicles;
    QHBoxLayout *horizontalLayout_52;
    QLabel *label_86;
    QSpacerItem *horizontalSpacer_36;
    QLineEdit *lineEdit_searchBox;
    QHBoxLayout *horizontalLayout_53;
    QLabel *label_87;
    QSpacerItem *horizontalSpacer_37;
    QComboBox *combobox_category;
    QPushButton *pushButton_search_vehicles;
    QVBoxLayout *verticalLayout_23;
    QSpacerItem *verticalSpacer_15;
    QVBoxLayout *verticalLayout_29;
    QLabel *label_104;
    QLabel *label_105;
    QSpacerItem *verticalSpacer_16;
    QComboBox *combobox_pick_color;
    QWidget *tab_2;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_24;
    QSpacerItem *horizontalSpacer_21;
    QRadioButton *on_radioButton;
    QRadioButton *off_radioButton;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_23;
    QSpacerItem *horizontalSpacer_20;
    QRadioButton *mp4_radioButton;
    QRadioButton *mkv_radioButton;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_26;
    QLineEdit *video_record_cache_lineEdit;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_19;
    QSpacerItem *horizontalSpacer_25;
    QLineEdit *record_default_duration_lineEdit;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_22;
    QSpacerItem *horizontalSpacer_24;
    QLineEdit *smart_record_duration_lineEdit;
    QWidget *layoutWidget8;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_20;
    QSpacerItem *horizontalSpacer_23;
    QLineEdit *record_start_time_lineEdit;
    QWidget *layoutWidget9;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_21;
    QSpacerItem *horizontalSpacer_22;
    QLineEdit *record_interval_lineEdit;
    QWidget *layoutWidget10;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_11;
    QLineEdit *source_index_lineEdit;
    QWidget *layoutWidget11;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_25;
    QSpacerItem *horizontalSpacer_28;
    QLineEdit *videoRecordDirPathlineEdit;
    QPushButton *videoRecordBrowsepushButton;
    QWidget *layoutWidget12;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_27;
    QLineEdit *keep_record_duration_day_counter_lineEdit;
    QWidget *tab_4;
    QLabel *label_17;
    QWidget *widget_slider_add;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBut;
    QPushButton *cancelBut;
    QPushButton *applyBut;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *settingsDialog)
    {
        if (settingsDialog->objectName().isEmpty())
            settingsDialog->setObjectName(QStringLiteral("settingsDialog"));
        settingsDialog->resize(792, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settingsDialog->sizePolicy().hasHeightForWidth());
        settingsDialog->setSizePolicy(sizePolicy);
        settingsDialog->setBaseSize(QSize(0, 1));
        verticalLayout = new QVBoxLayout(settingsDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        settingsTab = new QTabWidget(settingsDialog);
        settingsTab->setObjectName(QStringLiteral("settingsTab"));
        generalTab = new QWidget();
        generalTab->setObjectName(QStringLiteral("generalTab"));
        verticalLayout_2 = new QVBoxLayout(generalTab);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        rtssCheck = new QCheckBox(generalTab);
        rtssCheck->setObjectName(QStringLiteral("rtssCheck"));

        verticalLayout_2->addWidget(rtssCheck);

        rtvsCheck = new QCheckBox(generalTab);
        rtvsCheck->setObjectName(QStringLiteral("rtvsCheck"));

        verticalLayout_2->addWidget(rtvsCheck);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(generalTab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        adminPassLine = new QLineEdit(generalTab);
        adminPassLine->setObjectName(QStringLiteral("adminPassLine"));

        horizontalLayout_3->addWidget(adminPassLine);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        settingsTab->addTab(generalTab, QString());
        notificationsTab = new QWidget();
        notificationsTab->setObjectName(QStringLiteral("notificationsTab"));
        verticalLayout_3 = new QVBoxLayout(notificationsTab);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        enableNotCheck = new QCheckBox(notificationsTab);
        enableNotCheck->setObjectName(QStringLiteral("enableNotCheck"));

        verticalLayout_3->addWidget(enableNotCheck);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        activeRadio = new QRadioButton(notificationsTab);
        buttonGroup = new QButtonGroup(settingsDialog);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(activeRadio);
        activeRadio->setObjectName(QStringLiteral("activeRadio"));

        verticalLayout_4->addWidget(activeRadio);

        activeHoursRadio = new QRadioButton(notificationsTab);
        buttonGroup->addButton(activeHoursRadio);
        activeHoursRadio->setObjectName(QStringLiteral("activeHoursRadio"));

        verticalLayout_4->addWidget(activeHoursRadio);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        fromActiveText = new QLineEdit(notificationsTab);
        fromActiveText->setObjectName(QStringLiteral("fromActiveText"));
        fromActiveText->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(fromActiveText);

        label_2 = new QLabel(notificationsTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        toActiveText = new QLineEdit(notificationsTab);
        toActiveText->setObjectName(QStringLiteral("toActiveText"));
        toActiveText->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(toActiveText);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_18);


        verticalLayout_4->addLayout(horizontalLayout_4);


        horizontalLayout_6->addLayout(verticalLayout_4);


        verticalLayout_3->addLayout(horizontalLayout_6);

        emailCheck = new QCheckBox(notificationsTab);
        emailCheck->setObjectName(QStringLiteral("emailCheck"));

        verticalLayout_3->addWidget(emailCheck);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        emailVerticalBox = new QVBoxLayout();
        emailVerticalBox->setObjectName(QStringLiteral("emailVerticalBox"));

        verticalLayout_17->addLayout(emailVerticalBox);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        addEmail = new QPushButton(notificationsTab);
        addEmail->setObjectName(QStringLiteral("addEmail"));

        horizontalLayout_21->addWidget(addEmail);


        verticalLayout_17->addLayout(horizontalLayout_21);


        horizontalLayout_5->addLayout(verticalLayout_17);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_16);


        verticalLayout_3->addLayout(horizontalLayout_5);

        smsCheck = new QCheckBox(notificationsTab);
        smsCheck->setObjectName(QStringLiteral("smsCheck"));

        verticalLayout_3->addWidget(smsCheck);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_4);

        lineEdit_3 = new QLineEdit(notificationsTab);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_23->addWidget(lineEdit_3);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_17);


        verticalLayout_3->addLayout(horizontalLayout_23);

        audibleCheck = new QCheckBox(notificationsTab);
        audibleCheck->setObjectName(QStringLiteral("audibleCheck"));

        verticalLayout_3->addWidget(audibleCheck);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        objectAudibleCheck = new QCheckBox(notificationsTab);
        objectAudibleCheck->setObjectName(QStringLiteral("objectAudibleCheck"));

        verticalLayout_6->addWidget(objectAudibleCheck);

        faceAudibleCheck = new QCheckBox(notificationsTab);
        faceAudibleCheck->setObjectName(QStringLiteral("faceAudibleCheck"));

        verticalLayout_6->addWidget(faceAudibleCheck);


        horizontalLayout_7->addLayout(verticalLayout_6);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        settingsTab->addTab(notificationsTab, QString());
        ObjectDetection = new QWidget();
        ObjectDetection->setObjectName(QStringLiteral("ObjectDetection"));
        verticalLayout_9 = new QVBoxLayout(ObjectDetection);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_3 = new QLabel(ObjectDetection);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_9->addWidget(label_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        detectionClassBox = new QVBoxLayout();
        detectionClassBox->setObjectName(QStringLiteral("detectionClassBox"));
        faceCheck = new QCheckBox(ObjectDetection);
        faceCheck->setObjectName(QStringLiteral("faceCheck"));

        detectionClassBox->addWidget(faceCheck);

        maskedFaceCheck = new QCheckBox(ObjectDetection);
        maskedFaceCheck->setObjectName(QStringLiteral("maskedFaceCheck"));

        detectionClassBox->addWidget(maskedFaceCheck);

        personCheck = new QCheckBox(ObjectDetection);
        personCheck->setObjectName(QStringLiteral("personCheck"));

        detectionClassBox->addWidget(personCheck);

        baggageCheck = new QCheckBox(ObjectDetection);
        baggageCheck->setObjectName(QStringLiteral("baggageCheck"));

        detectionClassBox->addWidget(baggageCheck);

        cellPhoneCheck = new QCheckBox(ObjectDetection);
        cellPhoneCheck->setObjectName(QStringLiteral("cellPhoneCheck"));

        detectionClassBox->addWidget(cellPhoneCheck);


        horizontalLayout_8->addLayout(detectionClassBox);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        bicycleCHeck = new QCheckBox(ObjectDetection);
        bicycleCHeck->setObjectName(QStringLiteral("bicycleCHeck"));

        verticalLayout_7->addWidget(bicycleCHeck);

        carCheck = new QCheckBox(ObjectDetection);
        carCheck->setObjectName(QStringLiteral("carCheck"));

        verticalLayout_7->addWidget(carCheck);

        busCheck = new QCheckBox(ObjectDetection);
        busCheck->setObjectName(QStringLiteral("busCheck"));

        verticalLayout_7->addWidget(busCheck);

        motorcycleCheck = new QCheckBox(ObjectDetection);
        motorcycleCheck->setObjectName(QStringLiteral("motorcycleCheck"));

        verticalLayout_7->addWidget(motorcycleCheck);

        truckCheck = new QCheckBox(ObjectDetection);
        truckCheck->setObjectName(QStringLiteral("truckCheck"));

        verticalLayout_7->addWidget(truckCheck);


        horizontalLayout_8->addLayout(verticalLayout_7);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        face_check = new QCheckBox(ObjectDetection);
        face_check->setObjectName(QStringLiteral("face_check"));

        verticalLayout_10->addWidget(face_check);

        lpr_check = new QCheckBox(ObjectDetection);
        lpr_check->setObjectName(QStringLiteral("lpr_check"));

        verticalLayout_10->addWidget(lpr_check);

        knifeCheck = new QCheckBox(ObjectDetection);
        knifeCheck->setObjectName(QStringLiteral("knifeCheck"));

        verticalLayout_10->addWidget(knifeCheck);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_10->addItem(verticalSpacer_6);


        horizontalLayout_8->addLayout(verticalLayout_10);


        verticalLayout_9->addLayout(horizontalLayout_8);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(15);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_4 = new QLabel(ObjectDetection);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_9->addWidget(label_4);

        obDetText = new QLabel(ObjectDetection);
        obDetText->setObjectName(QStringLiteral("obDetText"));
        obDetText->setStyleSheet(QStringLiteral(""));

        horizontalLayout_9->addWidget(obDetText);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);


        verticalLayout_8->addLayout(horizontalLayout_9);

        objectSensitivitySlider = new QSlider(ObjectDetection);
        objectSensitivitySlider->setObjectName(QStringLiteral("objectSensitivitySlider"));
        objectSensitivitySlider->setMinimumSize(QSize(0, 30));
        objectSensitivitySlider->setFocusPolicy(Qt::StrongFocus);
        objectSensitivitySlider->setOrientation(Qt::Horizontal);
        objectSensitivitySlider->setTickPosition(QSlider::TicksBelow);

        verticalLayout_8->addWidget(objectSensitivitySlider);


        verticalLayout_9->addLayout(verticalLayout_8);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_3);

        settingsTab->addTab(ObjectDetection, QString());
        faceTab = new QWidget();
        faceTab->setObjectName(QStringLiteral("faceTab"));
        verticalLayout_5 = new QVBoxLayout(faceTab);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        checkBox_suspect = new QCheckBox(faceTab);
        checkBox_suspect->setObjectName(QStringLiteral("checkBox_suspect"));

        verticalLayout_5->addWidget(checkBox_suspect);

        checkbox_unique_face = new QCheckBox(faceTab);
        checkbox_unique_face->setObjectName(QStringLiteral("checkbox_unique_face"));

        verticalLayout_5->addWidget(checkbox_unique_face);

        checkbox_db_sync = new QCheckBox(faceTab);
        checkbox_db_sync->setObjectName(QStringLiteral("checkbox_db_sync"));

        verticalLayout_5->addWidget(checkbox_db_sync);

        faceRecogCheck = new QCheckBox(faceTab);
        faceRecogCheck->setObjectName(QStringLiteral("faceRecogCheck"));

        verticalLayout_5->addWidget(faceRecogCheck);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalSpacer_14 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_14);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_13 = new QLabel(faceTab);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_16->addWidget(label_13);

        faceRecogDirLine = new QLineEdit(faceTab);
        faceRecogDirLine->setObjectName(QStringLiteral("faceRecogDirLine"));

        horizontalLayout_16->addWidget(faceRecogDirLine);

        faceRecogBrowseBut = new QPushButton(faceTab);
        faceRecogBrowseBut->setObjectName(QStringLiteral("faceRecogBrowseBut"));

        horizontalLayout_16->addWidget(faceRecogBrowseBut);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_13);


        verticalLayout_11->addLayout(horizontalLayout_16);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_5 = new QLabel(faceTab);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_11->addWidget(label_5);

        blackListDirLine = new QLineEdit(faceTab);
        blackListDirLine->setObjectName(QStringLiteral("blackListDirLine"));

        horizontalLayout_11->addWidget(blackListDirLine);

        browseBlackList = new QPushButton(faceTab);
        browseBlackList->setObjectName(QStringLiteral("browseBlackList"));

        horizontalLayout_11->addWidget(browseBlackList);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_10);


        verticalLayout_11->addLayout(horizontalLayout_11);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_12 = new QLabel(faceTab);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_15->addWidget(label_12);

        faceDetText = new QLabel(faceTab);
        faceDetText->setObjectName(QStringLiteral("faceDetText"));
        faceDetText->setStyleSheet(QStringLiteral(""));

        horizontalLayout_15->addWidget(faceDetText);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_12);


        verticalLayout_11->addLayout(horizontalLayout_15);

        faceRecogSenseBar = new QSlider(faceTab);
        faceRecogSenseBar->setObjectName(QStringLiteral("faceRecogSenseBar"));
        faceRecogSenseBar->setMinimumSize(QSize(0, 30));
        faceRecogSenseBar->setOrientation(Qt::Horizontal);
        faceRecogSenseBar->setTickPosition(QSlider::TicksBelow);

        verticalLayout_11->addWidget(faceRecogSenseBar);


        horizontalLayout_14->addLayout(verticalLayout_11);


        verticalLayout_5->addLayout(horizontalLayout_14);

        label_14 = new QLabel(faceTab);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_5->addWidget(label_14);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        horizontalSpacer_19 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_19);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        landmarkCheck = new QCheckBox(faceTab);
        landmarkCheck->setObjectName(QStringLiteral("landmarkCheck"));

        verticalLayout_18->addWidget(landmarkCheck);

        smileCheck = new QCheckBox(faceTab);
        smileCheck->setObjectName(QStringLiteral("smileCheck"));

        verticalLayout_18->addWidget(smileCheck);

        glassCheck = new QCheckBox(faceTab);
        glassCheck->setObjectName(QStringLiteral("glassCheck"));

        verticalLayout_18->addWidget(glassCheck);

        emotionCheck = new QCheckBox(faceTab);
        emotionCheck->setObjectName(QStringLiteral("emotionCheck"));

        verticalLayout_18->addWidget(emotionCheck);

        ageCheck = new QCheckBox(faceTab);
        ageCheck->setObjectName(QStringLiteral("ageCheck"));

        verticalLayout_18->addWidget(ageCheck);

        sexCheck = new QCheckBox(faceTab);
        sexCheck->setObjectName(QStringLiteral("sexCheck"));

        verticalLayout_18->addWidget(sexCheck);


        horizontalLayout_24->addLayout(verticalLayout_18);


        verticalLayout_5->addLayout(horizontalLayout_24);

        verticalSpacer_4 = new QSpacerItem(17, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        settingsTab->addTab(faceTab, QString());
        directoryTab = new QWidget();
        directoryTab->setObjectName(QStringLiteral("directoryTab"));
        verticalLayout_13 = new QVBoxLayout(directoryTab);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(-1, 15, -1, -1);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(15);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_11 = new QLabel(directoryTab);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_14->addWidget(label_11);

        label_7 = new QLabel(directoryTab);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_14->addWidget(label_7);


        horizontalLayout_20->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(15);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        lineEdit = new QLineEdit(directoryTab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_15->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(directoryTab);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        verticalLayout_15->addWidget(lineEdit_2);


        horizontalLayout_20->addLayout(verticalLayout_15);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(15);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        pushButton_2 = new QPushButton(directoryTab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_16->addWidget(pushButton_2);

        pushButton = new QPushButton(directoryTab);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_16->addWidget(pushButton);


        horizontalLayout_20->addLayout(verticalLayout_16);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_15);


        verticalLayout_13->addLayout(horizontalLayout_20);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_5);

        settingsTab->addTab(directoryTab, QString());
        exportTab = new QWidget();
        exportTab->setObjectName(QStringLiteral("exportTab"));
        settingsTab->addTab(exportTab, QString());
        tab_camera_list = new QWidget();
        tab_camera_list->setObjectName(QStringLiteral("tab_camera_list"));
        pushButton_add_camera = new QPushButton(tab_camera_list);
        pushButton_add_camera->setObjectName(QStringLiteral("pushButton_add_camera"));
        pushButton_add_camera->setGeometry(QRect(260, 270, 89, 31));
        scrollArea_cam_list = new QScrollArea(tab_camera_list);
        scrollArea_cam_list->setObjectName(QStringLiteral("scrollArea_cam_list"));
        scrollArea_cam_list->setGeometry(QRect(370, 0, 421, 491));
        scrollArea_cam_list->setMinimumSize(QSize(421, 491));
        scrollArea_cam_list->setWidgetResizable(true);
        scrollAreaWidgetContents_cam_list = new QWidget();
        scrollAreaWidgetContents_cam_list->setObjectName(QStringLiteral("scrollAreaWidgetContents_cam_list"));
        scrollAreaWidgetContents_cam_list->setGeometry(QRect(0, 0, 419, 489));
        tableWidget_cam_list = new QTableWidget(scrollAreaWidgetContents_cam_list);
        tableWidget_cam_list->setObjectName(QStringLiteral("tableWidget_cam_list"));
        tableWidget_cam_list->setGeometry(QRect(0, 0, 421, 491));
        tableWidget_cam_list->setDragEnabled(true);
        scrollArea_cam_list->setWidget(scrollAreaWidgetContents_cam_list);
        pushButtonlogin = new QPushButton(tab_camera_list);
        pushButtonlogin->setObjectName(QStringLiteral("pushButtonlogin"));
        pushButtonlogin->setGeometry(QRect(150, 270, 89, 31));
        susface = new QCheckBox(tab_camera_list);
        susface->setObjectName(QStringLiteral("susface"));
        susface->setGeometry(QRect(20, 240, 201, 23));
        layoutWidget = new QWidget(tab_camera_list);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 321, 184));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        label_ip_3 = new QLabel(layoutWidget);
        label_ip_3->setObjectName(QStringLiteral("label_ip_3"));

        verticalLayout_12->addWidget(label_ip_3);

        label_ip_2 = new QLabel(layoutWidget);
        label_ip_2->setObjectName(QStringLiteral("label_ip_2"));

        verticalLayout_12->addWidget(label_ip_2);

        label_ip = new QLabel(layoutWidget);
        label_ip->setObjectName(QStringLiteral("label_ip"));

        verticalLayout_12->addWidget(label_ip);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_12->addWidget(label_6);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_12->addWidget(label_8);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_12->addWidget(label_9);


        horizontalLayout_10->addLayout(verticalLayout_12);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        lineEdit_source_index = new QLineEdit(layoutWidget);
        lineEdit_source_index->setObjectName(QStringLiteral("lineEdit_source_index"));

        verticalLayout_19->addWidget(lineEdit_source_index);

        lineEdit_port = new QLineEdit(layoutWidget);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));

        verticalLayout_19->addWidget(lineEdit_port);

        lineEdit_address = new QLineEdit(layoutWidget);
        lineEdit_address->setObjectName(QStringLiteral("lineEdit_address"));

        verticalLayout_19->addWidget(lineEdit_address);

        lineEdit_cam_name = new QLineEdit(layoutWidget);
        lineEdit_cam_name->setObjectName(QStringLiteral("lineEdit_cam_name"));

        verticalLayout_19->addWidget(lineEdit_cam_name);

        lineEdit_cam_pass = new QLineEdit(layoutWidget);
        lineEdit_cam_pass->setObjectName(QStringLiteral("lineEdit_cam_pass"));

        verticalLayout_19->addWidget(lineEdit_cam_pass);

        lineEdit_cam_uri = new QLineEdit(layoutWidget);
        lineEdit_cam_uri->setObjectName(QStringLiteral("lineEdit_cam_uri"));

        verticalLayout_19->addWidget(lineEdit_cam_uri);


        horizontalLayout_10->addLayout(verticalLayout_19);

        settingsTab->addTab(tab_camera_list, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 441, 471));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 0, 0, 1, 1);

        tableWidget_addLPR = new QTableWidget(layoutWidget1);
        tableWidget_addLPR->setObjectName(QStringLiteral("tableWidget_addLPR"));

        gridLayout->addWidget(tableWidget_addLPR, 1, 0, 1, 1);

        pushButton_addLPR = new QPushButton(layoutWidget1);
        pushButton_addLPR->setObjectName(QStringLiteral("pushButton_addLPR"));

        gridLayout->addWidget(pushButton_addLPR, 2, 0, 1, 1);

        radioButton_google_api = new QRadioButton(tab);
        radioButton_google_api->setObjectName(QStringLiteral("radioButton_google_api"));
        radioButton_google_api->setGeometry(QRect(490, 50, 112, 23));
        radioButton_tess_api = new QRadioButton(tab);
        radioButton_tess_api->setObjectName(QStringLiteral("radioButton_tess_api"));
        radioButton_tess_api->setGeometry(QRect(620, 50, 112, 23));
        label_26 = new QLabel(tab);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(490, 10, 211, 17));
        settingsTab->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label_111 = new QLabel(tab_3);
        label_111->setObjectName(QStringLiteral("label_111"));
        label_111->setGeometry(QRect(250, 0, 201, 17));
        label_111->setMinimumSize(QSize(190, 17));
        label_111->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 0);"));
        label_112 = new QLabel(tab_3);
        label_112->setObjectName(QStringLiteral("label_112"));
        label_112->setEnabled(true);
        label_112->setGeometry(QRect(460, 0, 181, 17));
        label_112->setMinimumSize(QSize(160, 17));
        label_112->setStyleSheet(QStringLiteral("background-color:rgb(0, 255, 0)"));
        label_113 = new QLabel(tab_3);
        label_113->setObjectName(QStringLiteral("label_113"));
        label_113->setGeometry(QRect(650, 0, 91, 17));
        label_113->setMinimumSize(QSize(85, 17));
        label_113->setStyleSheet(QStringLiteral("background-color:rgb(0, 255, 0)"));
        scrollArea_2 = new QScrollArea(tab_3);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(10, 190, 169, 291));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_video_results = new QWidget();
        scrollAreaWidgetContents_video_results->setObjectName(QStringLiteral("scrollAreaWidgetContents_video_results"));
        scrollAreaWidgetContents_video_results->setGeometry(QRect(0, 0, 167, 289));
        scrollArea_2->setWidget(scrollAreaWidgetContents_video_results);
        pushButton_select_video_file = new QPushButton(tab_3);
        pushButton_select_video_file->setObjectName(QStringLiteral("pushButton_select_video_file"));
        pushButton_select_video_file->setGeometry(QRect(40, 164, 121, 21));
        pushButton_select_video_file->setStyleSheet(QStringLiteral("background-color: rgb(61, 234, 37);"));
        scrollArea_for_image_vda = new QScrollArea(tab_3);
        scrollArea_for_image_vda->setObjectName(QStringLiteral("scrollArea_for_image_vda"));
        scrollArea_for_image_vda->setGeometry(QRect(190, 190, 571, 291));
        scrollArea_for_image_vda->setMinimumSize(QSize(571, 291));
        scrollArea_for_image_vda->setMaximumSize(QSize(571, 291));
        scrollArea_for_image_vda->setFrameShadow(QFrame::Plain);
        scrollArea_for_image_vda->setLineWidth(0);
        scrollArea_for_image_vda->setWidgetResizable(true);
        scrollAreaWidgetContents_results = new QWidget();
        scrollAreaWidgetContents_results->setObjectName(QStringLiteral("scrollAreaWidgetContents_results"));
        scrollAreaWidgetContents_results->setGeometry(QRect(0, 0, 569, 289));
        scrollArea_for_image_vda->setWidget(scrollAreaWidgetContents_results);
        label_75 = new QLabel(tab_3);
        label_75->setObjectName(QStringLiteral("label_75"));
        label_75->setGeometry(QRect(230, 170, 61, 17));
        label_75->setMinimumSize(QSize(60, 17));
        label_75->setStyleSheet(QStringLiteral("background-color: rgb(61, 234, 37);"));
        layoutWidget2 = new QWidget(tab_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 16, 741, 157));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        verticalLayout_25 = new QVBoxLayout();
        verticalLayout_25->setObjectName(QStringLiteral("verticalLayout_25"));
        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setObjectName(QStringLiteral("verticalLayout_24"));
        label_71 = new QLabel(layoutWidget2);
        label_71->setObjectName(QStringLiteral("label_71"));
        label_71->setMinimumSize(QSize(227, 32));
        label_71->setStyleSheet(QLatin1String("color: rgb(44, 238, 11);\n"
"background-color: rgb(173, 127, 168);"));

        verticalLayout_24->addWidget(label_71);

        label_72 = new QLabel(layoutWidget2);
        label_72->setObjectName(QStringLiteral("label_72"));
        label_72->setMinimumSize(QSize(227, 32));
        label_72->setStyleSheet(QLatin1String("color: rgb(44, 238, 11);\n"
"background-color: rgb(173, 127, 168);"));

        verticalLayout_24->addWidget(label_72);


        verticalLayout_25->addLayout(verticalLayout_24);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setObjectName(QStringLiteral("horizontalLayout_42"));
        label_73 = new QLabel(layoutWidget2);
        label_73->setObjectName(QStringLiteral("label_73"));
        label_73->setMinimumSize(QSize(39, 29));
        label_73->setStyleSheet(QLatin1String("background-color:rgb(114, 159, 207);\n"
"font: 11pt \"Ubuntu\";\n"
"border-color: rgb(246, 25, 235);"));
        label_73->setFrameShape(QFrame::Box);
        label_73->setFrameShadow(QFrame::Raised);
        label_73->setLineWidth(1);
        label_73->setTextFormat(Qt::AutoText);

        horizontalLayout_42->addWidget(label_73);

        dateTimeEdit_from = new QDateTimeEdit(layoutWidget2);
        dateTimeEdit_from->setObjectName(QStringLiteral("dateTimeEdit_from"));
        dateTimeEdit_from->setMinimumSize(QSize(180, 26));
        dateTimeEdit_from->setStyleSheet(QStringLiteral("border-color: rgb(204, 0, 0);"));

        horizontalLayout_42->addWidget(dateTimeEdit_from);


        verticalLayout_20->addLayout(horizontalLayout_42);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setObjectName(QStringLiteral("horizontalLayout_43"));
        label_74 = new QLabel(layoutWidget2);
        label_74->setObjectName(QStringLiteral("label_74"));
        label_74->setMinimumSize(QSize(39, 30));
        label_74->setStyleSheet(QStringLiteral("background-color:rgb(114, 159, 207)"));
        label_74->setFrameShape(QFrame::Box);
        label_74->setFrameShadow(QFrame::Raised);
        label_74->setLineWidth(2);

        horizontalLayout_43->addWidget(label_74);

        dateTimeEdit_to = new QDateTimeEdit(layoutWidget2);
        dateTimeEdit_to->setObjectName(QStringLiteral("dateTimeEdit_to"));
        dateTimeEdit_to->setMinimumSize(QSize(180, 26));
        dateTimeEdit_to->setStyleSheet(QStringLiteral("border-color: rgb(204, 0, 0);"));

        horizontalLayout_43->addWidget(dateTimeEdit_to);


        verticalLayout_20->addLayout(horizontalLayout_43);


        verticalLayout_25->addLayout(verticalLayout_20);


        horizontalLayout_12->addLayout(verticalLayout_25);

        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        verticalLayout_27 = new QVBoxLayout();
        verticalLayout_27->setObjectName(QStringLiteral("verticalLayout_27"));
        horizontalLayout_57 = new QHBoxLayout();
        horizontalLayout_57->setObjectName(QStringLiteral("horizontalLayout_57"));
        checkBox_face_check = new QCheckBox(layoutWidget2);
        checkBox_face_check->setObjectName(QStringLiteral("checkBox_face_check"));
        checkBox_face_check->setMinimumSize(QSize(90, 23));
        checkBox_face_check->setStyleSheet(QStringLiteral("background-color:rgb(246, 25, 235)"));

        horizontalLayout_57->addWidget(checkBox_face_check);

        checkBox_person = new QCheckBox(layoutWidget2);
        checkBox_person->setObjectName(QStringLiteral("checkBox_person"));
        checkBox_person->setMinimumSize(QSize(89, 23));
        checkBox_person->setStyleSheet(QStringLiteral("background-color:rgb(246, 25, 235)"));

        horizontalLayout_57->addWidget(checkBox_person);


        verticalLayout_27->addLayout(horizontalLayout_57);

        checkBox_masked_face = new QCheckBox(layoutWidget2);
        checkBox_masked_face->setObjectName(QStringLiteral("checkBox_masked_face"));
        checkBox_masked_face->setMinimumSize(QSize(187, 23));
        checkBox_masked_face->setStyleSheet(QStringLiteral("background-color:rgb(245, 121, 0)"));

        verticalLayout_27->addWidget(checkBox_masked_face);

        horizontalLayout_58 = new QHBoxLayout();
        horizontalLayout_58->setObjectName(QStringLiteral("horizontalLayout_58"));
        checkBox_male = new QCheckBox(layoutWidget2);
        checkBox_male->setObjectName(QStringLiteral("checkBox_male"));
        checkBox_male->setMinimumSize(QSize(90, 23));
        checkBox_male->setStyleSheet(QStringLiteral("background-color:rgb(246, 25, 235)"));

        horizontalLayout_58->addWidget(checkBox_male);

        checkBox_female = new QCheckBox(layoutWidget2);
        checkBox_female->setObjectName(QStringLiteral("checkBox_female"));
        checkBox_female->setMinimumSize(QSize(89, 23));
        checkBox_female->setStyleSheet(QStringLiteral("background-color:rgb(246, 25, 235)"));

        horizontalLayout_58->addWidget(checkBox_female);


        verticalLayout_27->addLayout(horizontalLayout_58);


        verticalLayout_21->addLayout(verticalLayout_27);

        horizontalLayout_59 = new QHBoxLayout();
        horizontalLayout_59->setObjectName(QStringLiteral("horizontalLayout_59"));
        label_98 = new QLabel(layoutWidget2);
        label_98->setObjectName(QStringLiteral("label_98"));
        label_98->setMinimumSize(QSize(31, 27));
        label_98->setStyleSheet(QStringLiteral("background-color:rgb(187, 228, 51)"));
        label_98->setFrameShape(QFrame::Box);
        label_98->setFrameShadow(QFrame::Raised);
        label_98->setLineWidth(0);

        horizontalLayout_59->addWidget(label_98);

        horizontalSpacer_41 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_59->addItem(horizontalSpacer_41);

        horizontalLayout_60 = new QHBoxLayout();
        horizontalLayout_60->setObjectName(QStringLiteral("horizontalLayout_60"));
        label_99 = new QLabel(layoutWidget2);
        label_99->setObjectName(QStringLiteral("label_99"));
        label_99->setMinimumSize(QSize(36, 25));
        label_99->setStyleSheet(QLatin1String("border-color: rgb(239, 41, 41);\n"
"background-color: rgb(114, 159, 207);\n"
"color: rgb(61, 234, 37);"));
        label_99->setFrameShape(QFrame::Box);
        label_99->setFrameShadow(QFrame::Raised);
        label_99->setLineWidth(0);

        horizontalLayout_60->addWidget(label_99);

        horizontalSpacer_42 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_60->addItem(horizontalSpacer_42);

        lineEdit_age_from = new QLineEdit(layoutWidget2);
        lineEdit_age_from->setObjectName(QStringLiteral("lineEdit_age_from"));
        lineEdit_age_from->setMinimumSize(QSize(27, 25));

        horizontalLayout_60->addWidget(lineEdit_age_from);


        horizontalLayout_59->addLayout(horizontalLayout_60);

        horizontalLayout_61 = new QHBoxLayout();
        horizontalLayout_61->setObjectName(QStringLiteral("horizontalLayout_61"));
        label_100 = new QLabel(layoutWidget2);
        label_100->setObjectName(QStringLiteral("label_100"));
        label_100->setMinimumSize(QSize(20, 25));
        label_100->setStyleSheet(QLatin1String("border-color: rgb(239, 41, 41);\n"
"background-color: rgb(114, 159, 207);\n"
"color: rgb(61, 234, 37);"));
        label_100->setFrameShape(QFrame::Box);
        label_100->setFrameShadow(QFrame::Raised);
        label_100->setLineWidth(0);

        horizontalLayout_61->addWidget(label_100);

        horizontalSpacer_43 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_61->addItem(horizontalSpacer_43);

        lineEdit_25_age_to = new QLineEdit(layoutWidget2);
        lineEdit_25_age_to->setObjectName(QStringLiteral("lineEdit_25_age_to"));
        lineEdit_25_age_to->setMinimumSize(QSize(27, 25));

        horizontalLayout_61->addWidget(lineEdit_25_age_to);


        horizontalLayout_59->addLayout(horizontalLayout_61);


        verticalLayout_21->addLayout(horizontalLayout_59);

        pushButton_search_for_sub_video_ana = new QPushButton(layoutWidget2);
        pushButton_search_for_sub_video_ana->setObjectName(QStringLiteral("pushButton_search_for_sub_video_ana"));

        verticalLayout_21->addWidget(pushButton_search_for_sub_video_ana);


        horizontalLayout_12->addLayout(verticalLayout_21);

        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        horizontalLayout_51 = new QHBoxLayout();
        horizontalLayout_51->setObjectName(QStringLiteral("horizontalLayout_51"));
        label_85 = new QLabel(layoutWidget2);
        label_85->setObjectName(QStringLiteral("label_85"));
        label_85->setStyleSheet(QStringLiteral("background-color:rgb(114, 159, 207)"));
        label_85->setFrameShape(QFrame::Box);
        label_85->setFrameShadow(QFrame::Raised);
        label_85->setLineWidth(1);

        horizontalLayout_51->addWidget(label_85);

        horizontalSpacer_35 = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_51->addItem(horizontalSpacer_35);

        comboBox_vehicles = new QComboBox(layoutWidget2);
        comboBox_vehicles->setObjectName(QStringLiteral("comboBox_vehicles"));
        comboBox_vehicles->setAutoFillBackground(false);
        comboBox_vehicles->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_51->addWidget(comboBox_vehicles);


        verticalLayout_22->addLayout(horizontalLayout_51);

        horizontalLayout_52 = new QHBoxLayout();
        horizontalLayout_52->setObjectName(QStringLiteral("horizontalLayout_52"));
        label_86 = new QLabel(layoutWidget2);
        label_86->setObjectName(QStringLiteral("label_86"));
        label_86->setStyleSheet(QStringLiteral("background-color:rgb(114, 159, 207)"));
        label_86->setFrameShape(QFrame::Box);
        label_86->setFrameShadow(QFrame::Raised);
        label_86->setLineWidth(1);

        horizontalLayout_52->addWidget(label_86);

        horizontalSpacer_36 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_52->addItem(horizontalSpacer_36);

        lineEdit_searchBox = new QLineEdit(layoutWidget2);
        lineEdit_searchBox->setObjectName(QStringLiteral("lineEdit_searchBox"));
        lineEdit_searchBox->setStyleSheet(QStringLiteral("border-color: rgb(204, 0, 0);"));

        horizontalLayout_52->addWidget(lineEdit_searchBox);


        verticalLayout_22->addLayout(horizontalLayout_52);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setObjectName(QStringLiteral("horizontalLayout_53"));
        label_87 = new QLabel(layoutWidget2);
        label_87->setObjectName(QStringLiteral("label_87"));
        label_87->setStyleSheet(QStringLiteral("background-color:rgb(114, 159, 207)"));
        label_87->setFrameShape(QFrame::Box);
        label_87->setFrameShadow(QFrame::Raised);

        horizontalLayout_53->addWidget(label_87);

        horizontalSpacer_37 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_53->addItem(horizontalSpacer_37);

        combobox_category = new QComboBox(layoutWidget2);
        combobox_category->setObjectName(QStringLiteral("combobox_category"));
        combobox_category->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_53->addWidget(combobox_category);


        verticalLayout_22->addLayout(horizontalLayout_53);

        pushButton_search_vehicles = new QPushButton(layoutWidget2);
        pushButton_search_vehicles->setObjectName(QStringLiteral("pushButton_search_vehicles"));

        verticalLayout_22->addWidget(pushButton_search_vehicles);


        horizontalLayout_12->addLayout(verticalLayout_22);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QStringLiteral("verticalLayout_23"));
        verticalSpacer_15 = new QSpacerItem(13, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_23->addItem(verticalSpacer_15);

        verticalLayout_29 = new QVBoxLayout();
        verticalLayout_29->setObjectName(QStringLiteral("verticalLayout_29"));
        label_104 = new QLabel(layoutWidget2);
        label_104->setObjectName(QStringLiteral("label_104"));
        label_104->setStyleSheet(QStringLiteral("background-color:rgb(173, 127, 168)"));

        verticalLayout_29->addWidget(label_104);

        label_105 = new QLabel(layoutWidget2);
        label_105->setObjectName(QStringLiteral("label_105"));
        label_105->setStyleSheet(QStringLiteral("background-color:rgb(173, 127, 168)"));

        verticalLayout_29->addWidget(label_105);


        verticalLayout_23->addLayout(verticalLayout_29);

        verticalSpacer_16 = new QSpacerItem(18, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_23->addItem(verticalSpacer_16);

        combobox_pick_color = new QComboBox(layoutWidget2);
        combobox_pick_color->setObjectName(QStringLiteral("combobox_pick_color"));
        combobox_pick_color->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        verticalLayout_23->addWidget(combobox_pick_color);


        horizontalLayout_12->addLayout(verticalLayout_23);

        settingsTab->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget3 = new QWidget(tab_2);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(20, 20, 381, 25));
        horizontalLayout_29 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(0, 0, 0, 0);
        label_24 = new QLabel(layoutWidget3);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_29->addWidget(label_24);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_21);

        on_radioButton = new QRadioButton(layoutWidget3);
        on_radioButton->setObjectName(QStringLiteral("on_radioButton"));

        horizontalLayout_29->addWidget(on_radioButton);

        off_radioButton = new QRadioButton(layoutWidget3);
        off_radioButton->setObjectName(QStringLiteral("off_radioButton"));

        horizontalLayout_29->addWidget(off_radioButton);

        layoutWidget4 = new QWidget(tab_2);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(20, 50, 381, 25));
        horizontalLayout_28 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(layoutWidget4);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_28->addWidget(label_23);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_20);

        mp4_radioButton = new QRadioButton(layoutWidget4);
        mp4_radioButton->setObjectName(QStringLiteral("mp4_radioButton"));

        horizontalLayout_28->addWidget(mp4_radioButton);

        mkv_radioButton = new QRadioButton(layoutWidget4);
        mkv_radioButton->setObjectName(QStringLiteral("mkv_radioButton"));

        horizontalLayout_28->addWidget(mkv_radioButton);

        layoutWidget5 = new QWidget(tab_2);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(21, 110, 381, 27));
        horizontalLayout_18 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        label_18 = new QLabel(layoutWidget5);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_18->addWidget(label_18);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_26);

        video_record_cache_lineEdit = new QLineEdit(layoutWidget5);
        video_record_cache_lineEdit->setObjectName(QStringLiteral("video_record_cache_lineEdit"));
        video_record_cache_lineEdit->setMinimumSize(QSize(1, 1));

        horizontalLayout_18->addWidget(video_record_cache_lineEdit);

        layoutWidget6 = new QWidget(tab_2);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(21, 140, 381, 27));
        horizontalLayout_19 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(layoutWidget6);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_19->addWidget(label_19);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_25);

        record_default_duration_lineEdit = new QLineEdit(layoutWidget6);
        record_default_duration_lineEdit->setObjectName(QStringLiteral("record_default_duration_lineEdit"));
        record_default_duration_lineEdit->setMinimumSize(QSize(1, 1));

        horizontalLayout_19->addWidget(record_default_duration_lineEdit);

        layoutWidget7 = new QWidget(tab_2);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(21, 170, 381, 27));
        horizontalLayout_22 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        horizontalLayout_22->setContentsMargins(0, 0, 0, 0);
        label_22 = new QLabel(layoutWidget7);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_22->addWidget(label_22);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_24);

        smart_record_duration_lineEdit = new QLineEdit(layoutWidget7);
        smart_record_duration_lineEdit->setObjectName(QStringLiteral("smart_record_duration_lineEdit"));
        smart_record_duration_lineEdit->setMinimumSize(QSize(1, 1));

        horizontalLayout_22->addWidget(smart_record_duration_lineEdit);

        layoutWidget8 = new QWidget(tab_2);
        layoutWidget8->setObjectName(QStringLiteral("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(21, 200, 381, 27));
        horizontalLayout_25 = new QHBoxLayout(layoutWidget8);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        horizontalLayout_25->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(layoutWidget8);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_25->addWidget(label_20);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_23);

        record_start_time_lineEdit = new QLineEdit(layoutWidget8);
        record_start_time_lineEdit->setObjectName(QStringLiteral("record_start_time_lineEdit"));
        record_start_time_lineEdit->setMinimumSize(QSize(1, 1));

        horizontalLayout_25->addWidget(record_start_time_lineEdit);

        layoutWidget9 = new QWidget(tab_2);
        layoutWidget9->setObjectName(QStringLiteral("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(21, 240, 381, 27));
        horizontalLayout_26 = new QHBoxLayout(layoutWidget9);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(layoutWidget9);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_26->addWidget(label_21);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_22);

        record_interval_lineEdit = new QLineEdit(layoutWidget9);
        record_interval_lineEdit->setObjectName(QStringLiteral("record_interval_lineEdit"));
        record_interval_lineEdit->setMinimumSize(QSize(1, 1));

        horizontalLayout_26->addWidget(record_interval_lineEdit);

        layoutWidget10 = new QWidget(tab_2);
        layoutWidget10->setObjectName(QStringLiteral("layoutWidget10"));
        layoutWidget10->setGeometry(QRect(20, 280, 381, 27));
        horizontalLayout_17 = new QHBoxLayout(layoutWidget10);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(layoutWidget10);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_17->addWidget(label_16);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_11);

        source_index_lineEdit = new QLineEdit(layoutWidget10);
        source_index_lineEdit->setObjectName(QStringLiteral("source_index_lineEdit"));
        source_index_lineEdit->setMinimumSize(QSize(1, 1));

        horizontalLayout_17->addWidget(source_index_lineEdit);

        layoutWidget11 = new QWidget(tab_2);
        layoutWidget11->setObjectName(QStringLiteral("layoutWidget11"));
        layoutWidget11->setGeometry(QRect(20, 80, 381, 27));
        horizontalLayout_30 = new QHBoxLayout(layoutWidget11);
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        horizontalLayout_30->setContentsMargins(0, 0, 0, 0);
        label_25 = new QLabel(layoutWidget11);
        label_25->setObjectName(QStringLiteral("label_25"));

        horizontalLayout_30->addWidget(label_25);

        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_30->addItem(horizontalSpacer_28);

        videoRecordDirPathlineEdit = new QLineEdit(layoutWidget11);
        videoRecordDirPathlineEdit->setObjectName(QStringLiteral("videoRecordDirPathlineEdit"));

        horizontalLayout_30->addWidget(videoRecordDirPathlineEdit);

        videoRecordBrowsepushButton = new QPushButton(layoutWidget11);
        videoRecordBrowsepushButton->setObjectName(QStringLiteral("videoRecordBrowsepushButton"));

        horizontalLayout_30->addWidget(videoRecordBrowsepushButton);

        layoutWidget12 = new QWidget(tab_2);
        layoutWidget12->setObjectName(QStringLiteral("layoutWidget12"));
        layoutWidget12->setGeometry(QRect(20, 320, 380, 27));
        horizontalLayout_13 = new QHBoxLayout(layoutWidget12);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(layoutWidget12);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_13->addWidget(label_15);

        horizontalSpacer_27 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_27);

        keep_record_duration_day_counter_lineEdit = new QLineEdit(layoutWidget12);
        keep_record_duration_day_counter_lineEdit->setObjectName(QStringLiteral("keep_record_duration_day_counter_lineEdit"));

        horizontalLayout_13->addWidget(keep_record_duration_day_counter_lineEdit);

        settingsTab->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        label_17 = new QLabel(tab_4);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(40, 40, 231, 17));
        widget_slider_add = new QWidget(tab_4);
        widget_slider_add->setObjectName(QStringLiteral("widget_slider_add"));
        widget_slider_add->setGeometry(QRect(10, 70, 742, 251));
        scrollArea = new QScrollArea(widget_slider_add);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(9, 9, 721, 231));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 719, 229));
        scrollArea->setWidget(scrollAreaWidgetContents);
        settingsTab->addTab(tab_4, QString());

        horizontalLayout_2->addWidget(settingsTab);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox = new QGroupBox(settingsDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBut = new QPushButton(groupBox);
        okBut->setObjectName(QStringLiteral("okBut"));
        okBut->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(okBut);

        cancelBut = new QPushButton(groupBox);
        cancelBut->setObjectName(QStringLiteral("cancelBut"));
        cancelBut->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(cancelBut);

        applyBut = new QPushButton(groupBox);
        applyBut->setObjectName(QStringLiteral("applyBut"));
        applyBut->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(applyBut);


        verticalLayout->addWidget(groupBox);


        retranslateUi(settingsDialog);
        QObject::connect(audibleCheck, SIGNAL(toggled(bool)), faceAudibleCheck, SLOT(setEnabled(bool)));
        QObject::connect(faceRecogCheck, SIGNAL(toggled(bool)), faceRecogBrowseBut, SLOT(setEnabled(bool)));
        QObject::connect(smsCheck, SIGNAL(toggled(bool)), lineEdit_3, SLOT(setEnabled(bool)));
        QObject::connect(audibleCheck, SIGNAL(toggled(bool)), objectAudibleCheck, SLOT(setEnabled(bool)));
        QObject::connect(enableNotCheck, SIGNAL(toggled(bool)), activeRadio, SLOT(setEnabled(bool)));
        QObject::connect(enableNotCheck, SIGNAL(toggled(bool)), activeHoursRadio, SLOT(setEnabled(bool)));
        QObject::connect(activeHoursRadio, SIGNAL(toggled(bool)), fromActiveText, SLOT(setEnabled(bool)));
        QObject::connect(activeHoursRadio, SIGNAL(toggled(bool)), toActiveText, SLOT(setEnabled(bool)));
        QObject::connect(enableNotCheck, SIGNAL(toggled(bool)), activeRadio, SLOT(setChecked(bool)));
        QObject::connect(faceRecogCheck, SIGNAL(toggled(bool)), faceRecogDirLine, SLOT(setEnabled(bool)));
        QObject::connect(faceRecogCheck, SIGNAL(toggled(bool)), faceRecogSenseBar, SLOT(setEnabled(bool)));
        QObject::connect(enableNotCheck, SIGNAL(toggled(bool)), emailCheck, SLOT(toggle()));
        QObject::connect(faceRecogCheck, SIGNAL(toggled(bool)), blackListDirLine, SLOT(setEnabled(bool)));
        QObject::connect(faceRecogCheck, SIGNAL(toggled(bool)), browseBlackList, SLOT(setEnabled(bool)));
        QObject::connect(emailCheck, SIGNAL(toggled(bool)), addEmail, SLOT(setEnabled(bool)));

        settingsTab->setCurrentIndex(9);


        QMetaObject::connectSlotsByName(settingsDialog);
    } // setupUi

    void retranslateUi(QDialog *settingsDialog)
    {
        settingsDialog->setWindowTitle(QApplication::translate("settingsDialog", "Dialog", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        settingsTab->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        rtssCheck->setText(QApplication::translate("settingsDialog", "RTSS", Q_NULLPTR));
        rtvsCheck->setText(QApplication::translate("settingsDialog", "RTVS", Q_NULLPTR));
        label->setText(QApplication::translate("settingsDialog", "Admin Password", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(generalTab), QApplication::translate("settingsDialog", "General", Q_NULLPTR));
        enableNotCheck->setText(QApplication::translate("settingsDialog", "Enable Notifications", Q_NULLPTR));
        activeRadio->setText(QApplication::translate("settingsDialog", "Keep active", Q_NULLPTR));
        activeHoursRadio->setText(QApplication::translate("settingsDialog", "Set active hours", Q_NULLPTR));
        label_2->setText(QApplication::translate("settingsDialog", "to", Q_NULLPTR));
        emailCheck->setText(QApplication::translate("settingsDialog", "Email to", Q_NULLPTR));
        addEmail->setText(QApplication::translate("settingsDialog", "Add", Q_NULLPTR));
        smsCheck->setText(QApplication::translate("settingsDialog", "SMS to", Q_NULLPTR));
        audibleCheck->setText(QApplication::translate("settingsDialog", "Audible alert", Q_NULLPTR));
        objectAudibleCheck->setText(QApplication::translate("settingsDialog", "Objects", Q_NULLPTR));
        faceAudibleCheck->setText(QApplication::translate("settingsDialog", "Face", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(notificationsTab), QApplication::translate("settingsDialog", "Notifications", Q_NULLPTR));
        label_3->setText(QApplication::translate("settingsDialog", "Detection classes", Q_NULLPTR));
        faceCheck->setText(QApplication::translate("settingsDialog", "Person", Q_NULLPTR));
        maskedFaceCheck->setText(QApplication::translate("settingsDialog", "Bicycle", Q_NULLPTR));
        personCheck->setText(QApplication::translate("settingsDialog", "Car", Q_NULLPTR));
        baggageCheck->setText(QApplication::translate("settingsDialog", "Motorcycle", Q_NULLPTR));
        cellPhoneCheck->setText(QApplication::translate("settingsDialog", "Bus", Q_NULLPTR));
        bicycleCHeck->setText(QApplication::translate("settingsDialog", "Truck", Q_NULLPTR));
        carCheck->setText(QApplication::translate("settingsDialog", "Backpack", Q_NULLPTR));
        busCheck->setText(QApplication::translate("settingsDialog", "Handbag", Q_NULLPTR));
        motorcycleCheck->setText(QApplication::translate("settingsDialog", "Suitcase", Q_NULLPTR));
        truckCheck->setText(QApplication::translate("settingsDialog", "Cell phone", Q_NULLPTR));
        face_check->setText(QApplication::translate("settingsDialog", "Face", Q_NULLPTR));
        lpr_check->setText(QApplication::translate("settingsDialog", "Licence plate number", Q_NULLPTR));
        knifeCheck->setText(QApplication::translate("settingsDialog", "Masked face", Q_NULLPTR));
        label_4->setText(QApplication::translate("settingsDialog", "Object detection sensitivity - ", Q_NULLPTR));
        obDetText->setText(QApplication::translate("settingsDialog", "100", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(ObjectDetection), QApplication::translate("settingsDialog", "Object Detection", Q_NULLPTR));
        checkBox_suspect->setText(QApplication::translate("settingsDialog", "Suspect", Q_NULLPTR));
        checkbox_unique_face->setText(QApplication::translate("settingsDialog", "Unique Face show", Q_NULLPTR));
        checkbox_db_sync->setText(QApplication::translate("settingsDialog", "DB Sync Checker", Q_NULLPTR));
        faceRecogCheck->setText(QApplication::translate("settingsDialog", "Face recognition", Q_NULLPTR));
        label_13->setText(QApplication::translate("settingsDialog", "Database Directory", Q_NULLPTR));
        faceRecogBrowseBut->setText(QApplication::translate("settingsDialog", "Browse", Q_NULLPTR));
        label_5->setText(QApplication::translate("settingsDialog", "Blacklist Directory  ", Q_NULLPTR));
        browseBlackList->setText(QApplication::translate("settingsDialog", "Browse", Q_NULLPTR));
        label_12->setText(QApplication::translate("settingsDialog", "True positive acceptance- ", Q_NULLPTR));
        faceDetText->setText(QApplication::translate("settingsDialog", "100", Q_NULLPTR));
        label_14->setText(QApplication::translate("settingsDialog", "Facial Profiling", Q_NULLPTR));
        landmarkCheck->setText(QApplication::translate("settingsDialog", "Landmark", Q_NULLPTR));
        smileCheck->setText(QApplication::translate("settingsDialog", "Smile", Q_NULLPTR));
        glassCheck->setText(QApplication::translate("settingsDialog", "Glass", Q_NULLPTR));
        emotionCheck->setText(QApplication::translate("settingsDialog", "Emotion", Q_NULLPTR));
        ageCheck->setText(QApplication::translate("settingsDialog", "Age", Q_NULLPTR));
        sexCheck->setText(QApplication::translate("settingsDialog", "Sex", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(faceTab), QApplication::translate("settingsDialog", "Face Detection", Q_NULLPTR));
        label_11->setText(QApplication::translate("settingsDialog", "Video Detection log", Q_NULLPTR));
        label_7->setText(QApplication::translate("settingsDialog", "Instance log", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("settingsDialog", "Browse", Q_NULLPTR));
        pushButton->setText(QApplication::translate("settingsDialog", "Browse", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(directoryTab), QApplication::translate("settingsDialog", "Directory", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(exportTab), QApplication::translate("settingsDialog", "Export/Import", Q_NULLPTR));
        pushButton_add_camera->setText(QApplication::translate("settingsDialog", "Add Camera", Q_NULLPTR));
        pushButtonlogin->setText(QApplication::translate("settingsDialog", "Login", Q_NULLPTR));
        susface->setText(QApplication::translate("settingsDialog", "Notify for Unknown Faces", Q_NULLPTR));
        label_ip_3->setText(QApplication::translate("settingsDialog", "Source Index", Q_NULLPTR));
        label_ip_2->setText(QApplication::translate("settingsDialog", "Port", Q_NULLPTR));
        label_ip->setText(QApplication::translate("settingsDialog", "IP Address", Q_NULLPTR));
        label_6->setText(QApplication::translate("settingsDialog", "Username", Q_NULLPTR));
        label_8->setText(QApplication::translate("settingsDialog", "Password:", Q_NULLPTR));
        label_9->setText(QApplication::translate("settingsDialog", "RTSP URL", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(tab_camera_list), QApplication::translate("settingsDialog", "Camera List", Q_NULLPTR));
        label_10->setText(QApplication::translate("settingsDialog", "White List", Q_NULLPTR));
        pushButton_addLPR->setText(QApplication::translate("settingsDialog", "ADD", Q_NULLPTR));
        radioButton_google_api->setText(QApplication::translate("settingsDialog", "Google API", Q_NULLPTR));
        radioButton_tess_api->setText(QApplication::translate("settingsDialog", "Tess API", Q_NULLPTR));
        label_26->setText(QApplication::translate("settingsDialog", "Select The API For OCR LP", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(tab), QApplication::translate("settingsDialog", "Add LPR", Q_NULLPTR));
        label_111->setText(QApplication::translate("settingsDialog", "                    Subjects", Q_NULLPTR));
        label_112->setText(QApplication::translate("settingsDialog", "                    Objetcs", Q_NULLPTR));
        label_113->setText(QApplication::translate("settingsDialog", "      Color", Q_NULLPTR));
        pushButton_select_video_file->setText(QApplication::translate("settingsDialog", "Load from File", Q_NULLPTR));
        label_75->setText(QApplication::translate("settingsDialog", "Results:", Q_NULLPTR));
        label_71->setText(QApplication::translate("settingsDialog", "                      Search", Q_NULLPTR));
        label_72->setText(QApplication::translate("settingsDialog", "                        Box", Q_NULLPTR));
        label_73->setText(QApplication::translate("settingsDialog", "From", Q_NULLPTR));
        label_74->setText(QApplication::translate("settingsDialog", "To     :", Q_NULLPTR));
        checkBox_face_check->setText(QApplication::translate("settingsDialog", "Face", Q_NULLPTR));
        checkBox_person->setText(QApplication::translate("settingsDialog", "Person", Q_NULLPTR));
        checkBox_masked_face->setText(QApplication::translate("settingsDialog", "Masked face", Q_NULLPTR));
        checkBox_male->setText(QApplication::translate("settingsDialog", "Male", Q_NULLPTR));
        checkBox_female->setText(QApplication::translate("settingsDialog", "Female", Q_NULLPTR));
        label_98->setText(QApplication::translate("settingsDialog", "Age:", Q_NULLPTR));
        label_99->setText(QApplication::translate("settingsDialog", "From", Q_NULLPTR));
        lineEdit_age_from->setText(QApplication::translate("settingsDialog", "10", Q_NULLPTR));
        label_100->setText(QApplication::translate("settingsDialog", "To ", Q_NULLPTR));
        lineEdit_25_age_to->setText(QApplication::translate("settingsDialog", "40", Q_NULLPTR));
        pushButton_search_for_sub_video_ana->setText(QApplication::translate("settingsDialog", "Search Subjects", Q_NULLPTR));
        label_85->setText(QApplication::translate("settingsDialog", "Vehicles", Q_NULLPTR));
        label_86->setText(QApplication::translate("settingsDialog", "License plate", Q_NULLPTR));
        lineEdit_searchBox->setText(QApplication::translate("settingsDialog", "search", Q_NULLPTR));
        lineEdit_searchBox->setPlaceholderText(QApplication::translate("settingsDialog", "Search", Q_NULLPTR));
        label_87->setText(QApplication::translate("settingsDialog", "Category", Q_NULLPTR));
        pushButton_search_vehicles->setText(QApplication::translate("settingsDialog", "Search Vehicles", Q_NULLPTR));
        label_104->setText(QApplication::translate("settingsDialog", "      Pick", Q_NULLPTR));
        label_105->setText(QApplication::translate("settingsDialog", "     color", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(tab_3), QApplication::translate("settingsDialog", "Video Analytics", Q_NULLPTR));
        label_24->setText(QApplication::translate("settingsDialog", "Smart Record:", Q_NULLPTR));
        on_radioButton->setText(QApplication::translate("settingsDialog", "ON", Q_NULLPTR));
        off_radioButton->setText(QApplication::translate("settingsDialog", "OFF", Q_NULLPTR));
        label_23->setText(QApplication::translate("settingsDialog", "Container Type:", Q_NULLPTR));
        mp4_radioButton->setText(QApplication::translate("settingsDialog", "MP4", Q_NULLPTR));
        mkv_radioButton->setText(QApplication::translate("settingsDialog", "MKV", Q_NULLPTR));
        label_18->setText(QApplication::translate("settingsDialog", "Record Video Cache(Sec)", Q_NULLPTR));
        label_19->setText(QApplication::translate("settingsDialog", "Record Default Duration(Sec)", Q_NULLPTR));
        label_22->setText(QApplication::translate("settingsDialog", "Smart Record Duration(Sec)", Q_NULLPTR));
        label_20->setText(QApplication::translate("settingsDialog", "Record Start Time(Sec)", Q_NULLPTR));
        label_21->setText(QApplication::translate("settingsDialog", "Record Interval(Sec)", Q_NULLPTR));
        label_16->setText(QApplication::translate("settingsDialog", "Source Index:", Q_NULLPTR));
        label_25->setText(QApplication::translate("settingsDialog", "Record Directory:", Q_NULLPTR));
        videoRecordBrowsepushButton->setText(QApplication::translate("settingsDialog", "Browse", Q_NULLPTR));
        label_15->setText(QApplication::translate("settingsDialog", "Keep Record Duration(Days):", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(tab_2), QApplication::translate("settingsDialog", "Smart Record", Q_NULLPTR));
        label_17->setText(QApplication::translate("settingsDialog", "Line Draw Configure From Slider:", Q_NULLPTR));
        settingsTab->setTabText(settingsTab->indexOf(tab_4), QApplication::translate("settingsDialog", "LineDrawConfSlider", Q_NULLPTR));
        groupBox->setTitle(QString());
        okBut->setText(QApplication::translate("settingsDialog", "OK", Q_NULLPTR));
        cancelBut->setText(QApplication::translate("settingsDialog", "Cancel", Q_NULLPTR));
        applyBut->setText(QApplication::translate("settingsDialog", "Apply", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class settingsDialog: public Ui_settingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
