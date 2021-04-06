#include "mystyles.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>


QString myStyles::defaultStyle = "";
QString myStyles::searchOn = "";
//QString myStyles::searchFOn = "";
QString myStyles::blinkOff = "";
QString myStyles::blinkOn = "";
QString myStyles::blinkOnG = "";
QString myStyles::toolTip = "";

int myStyles::borderThickness = 0;

int myStyles::minWidth = 0;
int myStyles::runningFeedWidth = 0;
int myStyles::runningFeedHeight = 0;

int myStyles::buttonsWidth = 0;
int myStyles::buttonHeight = 0;

QString myStyles::faceFolderRelative = "";
QString myStyles::blackFolderRelative = "";
QString myStyles::trackingFlag = "off";

int myStyles::notificationFlag;
int myStyles::faceRecognitionFlag;
int myStyles::faceSensitivitySlider;
float myStyles::faceSensitivityValue;

int myStyles::objectSensitivitySlider;
float myStyles::objectSensitivityValue;

float myStyles::winRatio= (float) 16/9;

QStringList myStyles::colors;
QStringList myStyles::objects;
QList<int> myStyles::colorValues;
QList<int> myStyles::objectValues;
QStringList myStyles::emailsTo;



myStyles::myStyles()
{



}

void myStyles::initializeValues()
{
    setDefaultStyle("");
    setSearchOn("background-color: rgb(115, 210, 22);");
    setBlinkOff("border: 3px solid rgb(37, 37, 38);");
   // setBlinkOff("border: 4px solid rgb(255, 102, 102);");
   // setBlinkOn("border: 22px solid rgb(164, 0, 0);");//, "border: 22px solid rgb(255, 102, 102);");
   // setBlinkOnG("border: 22px solid rgb(255, 102, 102);");
    setBlinkOn("border: 28px solid rgb(51, 255, 51);");

    setMinWidth(640);
    setRunningFeedWidth(640);
    setRunningFeedHeight(480);

    setBorderThickness( 20);

    setButtonsWidth( 50);
    setButtonHeight( 25);

    setFaceFolder( "/home/sigmind/faces");

    QFile file("./files/settings.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        return;
    }



    QTextStream in(&file);
    int i=0;
    while(!in.atEnd()) {

        notificationFlag = in.readLine().toInt();//1
        emailsTo = in.readLine().split(' ');//2

        QStringList list = in.readLine().split(' ');//3

        foreach(QString num, list){
            objectValues << num.toInt();
        }

        objectSensitivitySlider= in.readLine().toInt();//4

        objectSensitivityValue = (float)objectSensitivitySlider/100;

        faceRecognitionFlag = in.readLine().toInt();//5

        faceFolderRelative = in.readLine();//6
        blackFolderRelative = in.readLine();//7

        //qDebug() << "face : " << faceFolderRelative;
        //qDebug() << "black :" << blackFolderRelative;

        faceSensitivitySlider= in.readLine().toInt();//8

        faceSensitivityValue = (float)faceSensitivitySlider/100;
        faceSensitivityValue = 0.55;// default slider value
        ////qDebug() << faceSensitivityValue;

        //qDebug() << "mystyles " << i << " " << objectSensitivityValue;

        i++;
        break;

    }

    winRatio = (float) 16/9;

    colors << "Any" << "White" << "Black" <<"Violet" << "Blue" << "Indigo" << "Green" << "Yellow" << "Orange" << "Red";
    colorValues << -1 << -2 << -3 << 140 << 120 << 100 << 60 << 30 << 15 << 0;
    objects << "None" << "Person" << "Bicycle" << "Car" << "Motorcycle" << "Bus" << "Truck" << "Backpack" << "Handbag" << "Suitcase" << "Cell phone" << "Face" << "Masked face";

    file.close();
}

void myStyles::setSettingsValues()
{
    QString noti = QString::number(notificationFlag);
    QString emails;
    for(int i=0;i<emailsTo.size();i++){
        if(i<emailsTo.size()-1){
            emails += emailsTo.at(i);
            emails += " ";
        }
        else {
            emails += emailsTo.at(i);
        }
    }

    QString obs;

    for(int i=0;i<objectValues.size();i++){
        if(i<objectValues.size()-1){
            obs += QString::number(objectValues.at(i));
            obs += " ";
        }
        else {
            obs += QString::number(objectValues.at(i));
        }
    }
    QString faceRecog = QString::number(faceRecognitionFlag);
    QString faceSense = QString::number(faceSensitivitySlider);
    QString objectSense = QString::number(objectSensitivitySlider);
    //faceSensitivityValue = (float)faceSensitivitySlider/100;
    objectSensitivityValue = (float)objectSensitivitySlider/100;

    ////qDebug() <<"faceSensitivityValue of setSettingsValues method ="<< faceSensitivityValue;

    //qDebug() << "in mystyles" << objectSensitivityValue;

    QFile file("./files/settings.txt");
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << noti<< endl;
        stream << emails<< endl;
        stream << obs<< endl;
        stream << objectSense << endl;
        stream << faceRecog << endl;
        stream << faceFolderRelative<< endl;
        stream << blackFolderRelative<< endl;
        stream << faceSense;
    }
}
