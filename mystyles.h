#ifndef MYSTYLES_H
#define MYSTYLES_H

#include <QString>
#include <QDebug>
#include <QDir>


class myStyles
{
public:
    myStyles();

    void setSettingsValues();
    void initializeValues();


    static QString defaultStyle;
    static QString searchOn;
    static QString blinkOff;
    static QString blinkOn;
    static QString blinkOnG;

    static QString toolTip;

    static int borderThickness;

    static int minWidth;
    static int runningFeedWidth;
    static int runningFeedHeight;

    static int buttonsWidth;
    static int buttonHeight;

    static QString faceFolderRelative;
    static QString blackFolderRelative;

    static QString trackingFlag;

    static int notificationFlag;
    static int faceRecognitionFlag;
    static int faceSensitivitySlider;
    static float faceSensitivityValue;

    static int objectSensitivitySlider;
    static float objectSensitivityValue;

    static float winRatio;

    static QStringList colors;
    static QStringList objects;
    static QList<int> colorValues;
    static QList<int> objectValues;

    static QStringList emailsTo;

    void setDefaultStyle(QString q)
    {
        defaultStyle = q;
    }
    void setSearchOn(QString q)
    {
        searchOn = q;
    }
    void setBlinkOff(QString q)
    {
        blinkOff = q;
    }
    void setBlinkOn(QString q)
    {
        blinkOn = q;
        //blinkOnG = g;
    }

    void setToolTip(QString q)
    {
        toolTip = q;
    }
    void setBorderThickness(int q)
    {
        borderThickness = q;
    }
    void setMinWidth(int q)
    {
        minWidth = q;
    }
    void setRunningFeedWidth(int q)
    {
        runningFeedWidth = q;
    }
    void setRunningFeedHeight(int q)
    {
        runningFeedHeight = q;
    }
    void setButtonsWidth(int q)
    {
        buttonsWidth = q;
    }
    void setButtonHeight(int q)
    {
        buttonHeight = q;
    }
    void setFaceFolder(QString q)
    {
        faceFolderRelative = q;
    }



    QString getDefaultStyle()
    {
        return defaultStyle;
    }
    QString getSearchOn()
    {
        return searchOn;
    }
    QString getBlinkOff()
    {
        return blinkOff;
    }
    QString getBlinkOn()
    {
        return blinkOn;
    }
    QString getToolTip()
    {
        return toolTip;
    }
    int getBorderThickness()
    {
        return borderThickness;
    }
    int getMinWidth()
    {
        return minWidth;
    }
    int getRunningFeedWidth()
    {
        return runningFeedWidth;
    }
    int getRunningFeedHeight()
    {
        return runningFeedHeight;
    }
    int getButtonsWidth()
    {
        return buttonsWidth;
    }
    int getButtonHeight()
    {
        return buttonHeight;
    }
    QString getFaceFolder()
    {
        return faceFolderRelative;
    }

};



#endif // MYSTYLES_H
