#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <mystyles.h>
#include <QDebug>
#include <components/emailbox.h>
#include <QFileDialog>
#include "CameraList/cameralistwidget.h"
#include <flowlayout.h>
#include <QVBoxLayout>
#include "CameraList/camera_list_helper.h"
#include "getrtsp.h"
#include <QMessageBox>
#include <QShortcut>
#include "QDateTime"
#include "QTextStream"
#include "QDir"
#include <DatabaseConnection/sqlite_connection.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QWheelEvent>
#include <dialogs/vd_face.h>

#include "dialogs/singleslider.h"
#include <QScrollBar>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingsDialog(QWidget *parent = 0);
    ~settingsDialog();
    void loadFromTextFile();
    void loadIntoWidget();
    void editSourceNumber();
    get_rtsp *get_link = NULL;
    void consLike();
    void updateRtsp(QString, QString);
    void loadDataFromTableForLPR();
    void videoAnalyticsCons();
    void wheelEvent(QWheelEvent *event);
    void closeEvent(QCloseEvent *event);
    void imageLoadForVideoAnalytics();
    void maleFace(int fromAge, int toAge);
    void malePerson(int fromAge, int toAge);
    void femaleFace(int fromAge, int toAge);
    void femalePerson(int fromAge, int toAge);
    void faceMaleFemale(int fromAge, int toAge);
    void personMaleFemale(int fromAge, int toAge);
    void imageSetToWindow(QString);
    void readDataUsingMouseWheel(int);
    void readDataUsingMouseWheel();

    QList<singleSlider *>stor_sldr_lst;
//    QVector<QPair<int, int>>store_slider_pair_value;
    std::vector<std::pair<int, double>>store_slider_pair_value;
    QList<int>store_source_id_list;
    QList<double>store_divisor_value_list;

private slots:

    void on_okBut_pressed();

    void on_okBut_released();

    void on_applyBut_pressed();

    void on_cancelBut_clicked();

    void on_addEmail_clicked();

    void on_faceRecogBrowseBut_pressed();

    void on_objectSensitivitySlider_valueChanged(int value);

    void on_faceRecogSenseBar_valueChanged(int value);

    void on_browseBlackList_clicked();

    void on_settingsTab_tabBarClicked(int index);

    void on_pushButton_add_camera_clicked();
    void on_pushButtonlogin_clicked();

    void on_checkBox_suspect_clicked();

    void on_okBut_clicked();

    void on_tableWidget_cam_list_doubleClicked(const QModelIndex &index);

    //    void on_tableWidget_cam_list_cellChanged(int row, int column);

    //    void on_tableWidget_cam_list_cellEntered(int row, int column);

    //    void on_tableWidget_cam_list_cellClicked(int row, int column);

    void on_objectSensitivitySlider_actionTriggered(int action);

    void on_pushButton_addLPR_clicked();

    void on_tableWidget_addLPR_doubleClicked(const QModelIndex &index);

    void on_face_check_clicked();

    void on_lpr_check_clicked();

    void on_pushButton_search_for_sub_video_ana_clicked();

    void on_pushButton_search_vehicles_clicked();

    //--------------------
    void displayAllSourceIdFromSlider();
    void collectWhichSourceEnableOrNot();
    void retriveDivisorValue();

    //-----------------------

    void on_videoRecordBrowsepushButton_pressed();

    void on_radioButton_google_api_clicked();

    void on_radioButton_tess_api_clicked();

signals:
    void objectSensitivityChanged();
    void faceSensitivityChanged();
    void transferSuspectStateToMainWindow(bool);
    void fr_thresholed_value_settingdialog(float);
    void lpr_api_select_value_settingdialog(QString);
    void checkFaceDetection(bool);
    void checkLprDetection(bool);
//    std::vector<int> getSourceVecFromDs();
    void smartRecordDayCount(int, QString);
    void setDivisortoMain(std::vector<std::pair<int, double>>);

public slots:
    void removeEmail(int);
    void textChange(int, QString);
    void getDataAfterLefClicked();
    void delete_lpr_from_db_and_ui(int);

    //---------
    void updateConfigDivisorValueWhichTakenFromSlider();

    void updateConfigFileForVideoRecord();
    void stopSmartRecForSpecificSourceIndex(QString, int);
    //--------------------------

private:
    Ui::settingsDialog *ui;

    void applyChanges();

    QList<int> obValues;

    QStringList emailList;

    myStyles mystyle;

    int emailCount;

    QString faceFolder;
    QString blackFolder;

    bool objectSensitivityChange;
    /* define recent*/
    bool faceSensitivityChange;

    /* Write into file*/
    QString last_source;

    /*Camera list info*/
    QVector<camera_list_helper> *cam_info_list;

    /*Camera layout*/
    //QVBoxLayout* box_layout_cam_list;
    //cameraListWidget* infor;
    float previous_value = 0.45;
    bool _flag = true;

    bool face_v, person_v, mask_face_v, male_v, female_v;

    QGridLayout *grid_show_all_faces; // faces show in Grid layout
    int row_index = 0; int column_index = 0; // Grid layout index
    QList<VD_Face*> faceList;

    QList<QString> list_of_path;
    QPair<int, int> track_index;

    //----------------------
    int smart_record_on_off_value = 0;
    int container_value = 0;
    bool smart_rec_on_val = false;
    QString api_check_value_lp;

    QGridLayout *grid_slider;
    int column_index_slider=0;

};

#endif // SETTINGSDIALOG_H
