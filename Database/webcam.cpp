#include "webcam.h"
#include "ui_webcam.h"

#include <QCameraViewfinder>
#include <QCameraInfo>

#include <QMessageBox>

Q_DECLARE_METATYPE(QCameraInfo)

WebCam::WebCam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebCam)
{
    ui->setupUi(this);
    //connect(ui->captureWidget, &QTabWidget::currentChanged, this, &WebCam::updateCaptureMode);

    //qDebug()<<"ck 0 before set camera method in constructor";
    setCamera(QCameraInfo::defaultCamera());
}

WebCam::~WebCam()
{
    //qDebug()<<"destructor of webcam";

    m_camera.reset();
    m_imageCapture.reset();

    delete ui;
}

void WebCam::setCamera(const QCameraInfo &cameraInfo)
{
    //qDebug()<<"ck 1 set camera method starting..";
    m_camera.reset(new QCamera(cameraInfo));

    //    connect(m_camera.data(), &QCamera::stateChanged, this, &WebCam::updateCameraState);
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &WebCam::displayCameraError);

    m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

    m_camera->setViewfinder(ui->viewfinder);

    connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &WebCam::readyForCapture);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &WebCam::processCapturedImage);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &WebCam::imageSaved);
    connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
            this, &WebCam::displayCaptureError);

    //ui->captureWidget->setTabEnabled(1, (m_camera->isCaptureModeSupported(QCamera::CaptureStillImage)));

    updateCaptureMode();
    //ui->captureWidget->setEnabled(true);
    ui->takeImageButton->setEnabled(true);
    m_camera->start();
}

void WebCam::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);
    //qDebug()<<"requestId ="<<requestId;
    QImage scaledImage = img.scaled(ui->viewfinder->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    QString face_path = "./captures/webCamImages/";
    QString obliq = "/";
    // QString format = "dd.MM.yyyy";
    QString date = QDate::currentDate().toString("dd.MM.yyyy");

    QString at = "<at>";

    QString img_path = face_path+date+obliq;
    QDir myDir;
    if(!myDir.exists(date)) //if no directory so create directory
    {
        myDir.mkpath(img_path);
        QString image_name = img_path+at+"webCamFace "+QTime::currentTime().toString()+".png";
        QFile file(image_name);
        file.open(QIODevice::WriteOnly);
        scaledImage.save(&file, "PNG");
    }

    emit emitImageToSetLabel(scaledImage);
    // Display captured image for 2 seconds.
    //qDebug()<<"ck 5 before display capture method in processCapturedImage";
    //displayCapturedImage();
    //QTimer::singleShot(2000, this, &WebCam::displayViewfinder);
}

void WebCam::takeImage()
{
    //qDebug()<<"ck 4 take Image method";
    m_isCapturingImage = true;
    m_imageCapture->capture();
}

void WebCam::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    //qDebug()<<"displayCaptureError method";
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    m_isCapturingImage = false;
}

void WebCam::updateCaptureMode()
{
    //int tabIndex = ui->captureWidget->currentIndex();
    QCamera::CaptureModes captureMode = QCamera::CaptureStillImage;

    if (m_camera->isCaptureModeSupported(captureMode)){
        //qDebug()<<"ck 2 update capture mode method";
        m_camera->setCaptureMode(captureMode);
    }
}

void WebCam::displayCameraError()
{
    //qDebug()<<"Camera::displayCameraError";
    QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void WebCam::displayViewfinder()
{
    //qDebug()<<"ck 8 displayViewfinder method (of QTimer) set current index";
    ui->stackedWidget->setCurrentIndex(0);
}

void WebCam::displayCapturedImage()
{
    //qDebug()<<"ck 6 inside display capture method";
    ui->stackedWidget->setCurrentIndex(1);
}

void WebCam::readyForCapture(bool ready)
{
    //qDebug()<<"ck 3 ready for capture"<<" and ready variable valu ="<<ready;
    ui->takeImageButton->setEnabled(ready);
}

void WebCam::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    //qDebug()<<"ck 7 imageSaved method";

    QString image_path_of_webcam_photo = QDir::toNativeSeparators(fileName);
    //qDebug()<<"Captured path "<<image_path_of_webcam_photo;

    /* set capture photo path into DB */
    emit imagePathWebcamPhoto(image_path_of_webcam_photo);

    m_isCapturingImage = false;
}

void WebCam::closeEvent(QCloseEvent *event)
{
    //qDebug()<<"Camera::closeEvent";
    if (m_isCapturingImage) {
        setEnabled(false);
        event->ignore();
    } else {
        event->accept();

        m_camera.reset();
        m_imageCapture.reset();

        delete ui;
        emitFlagChangedOfWebcamAndUploadPhoto();
    }
}

void WebCam::on_takeImageButton_clicked()
{
    takeImage();// from webcam
}
