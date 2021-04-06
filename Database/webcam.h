#ifndef WEBCAM_H
#define WEBCAM_H

#include <QWidget>
#include<QtWidgets>

#include <QCamera>
#include <QCameraImageCapture>
#include <QScopedPointer>

namespace Ui {
class WebCam;
}

class WebCam : public QWidget
{
    Q_OBJECT

public:
    explicit WebCam(QWidget *parent = nullptr);
    ~WebCam();

    void setCamera(const QCameraInfo &cameraInfo);


    void takeImage();
    void displayCaptureError(int, QCameraImageCapture::Error, const QString &errorString);


    void displayCameraError();


    void updateCaptureMode();

    void processCapturedImage(int requestId, const QImage &img);

    void displayViewfinder();
    void displayCapturedImage();

    void readyForCapture(bool ready);
    void imageSaved(int id, const QString &fileName);

    void justWaitForClosingWidget();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_takeImageButton_clicked();

signals:
    void emitImageToSetLabel(QImage);
    void imagePathWebcamPhoto(QString);
    void emitFlagChangedOfWebcamAndUploadPhoto();

private:
    Ui::WebCam *ui;

    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QCameraImageCapture> m_imageCapture;

    bool m_isCapturingImage = false;

};

#endif // WEBCAM_H
