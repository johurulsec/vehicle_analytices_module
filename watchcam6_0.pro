#-------------------------------------------------
#
# Project created by QtCreator 2018-03-09T17:26:42
#
#-------------------------------------------------

QT += core gui network concurrent multimedia multimediawidgets
QT += sql widgets widgets
QT += printsupport
#QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = watchcamSS-Tegra-DS5
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_LFLAGS += -no-pie

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += main.cpp\
        mainwindow.cpp \
  #  feed.cpp \
    mystyles.cpp \
   # camera.cpp \
    flowlayout.cpp \
    faces.cpp \
    face.cpp \
    feedwindow.cpp \
    person.cpp \
    dialogs/addcameradialog.cpp \
    dialogs/trackingsettingsdialog.cpp \
#    AI_src/activation_layer.c \
#    AI_src/activations.c \
#    AI_src/art.c \
#    AI_src/avgpool_layer.c \
#    AI_src/batchnorm_layer.c \
#    AI_src/blas.c \
#    AI_src/box.c \
#    AI_src/captcha.c \
#    AI_src/cifar.c \
#    AI_src/classifier.c \
#    AI_src/coco.c \
#    AI_src/col2im.c \
#    AI_src/compare.c \
#    AI_src/connected_layer.c \
#    AI_src/convolutional_layer.c \
#    AI_src/cost_layer.c \
#    AI_src/crnn_layer.c \
#    AI_src/crop_layer.c \
#    AI_src/darknet.c \
#    AI_src/data.c \
#    AI_src/deconvolutional_layer.c \
#    AI_src/demo.c \
#    AI_src/detection_layer.c \
#    AI_src/detector.c \
#    AI_src/dice.c \
#    AI_src/dropout_layer.c \
#    AI_src/gemm.c \
#    AI_src/go.c \
#    AI_src/gru_layer.c \
#    AI_src/im2col.c \
#    AI_src/image.c \
#    AI_src/layer.c \
#    AI_src/list.c \
#    AI_src/local_layer.c \
#    AI_src/lsd.c \
#    AI_src/matrix.c \
#    AI_src/maxpool_layer.c \
#    AI_src/network.c \
#    AI_src/nightmare.c \
#    AI_src/normalization_layer.c \
#    AI_src/option_list.c \
#    AI_src/parser.c \
#    AI_src/region_layer.c \
#    AI_src/regressor.c \
#    AI_src/reorg_layer.c \
#    AI_src/rnn_layer.c \
#    AI_src/rnn_vid.c \
#    AI_src/rnn.c \
#    AI_src/route_layer.c \
#    AI_src/shortcut_layer.c \
#    AI_src/softmax_layer.c \
#    AI_src/super.c \
#    AI_src/swag.c \
#    AI_src/tag.c \
#    AI_src/tree.c \
#    AI_src/utils.c \
#    AI_src/voxel.c \
#    AI_src/writing.c \
#    AI_src/yolo.c \
    rectangle.cpp \
    dialogs/registerfacedialog.cpp \
    dialogs/analyzedialog.cpp \
    dialogs/settingsdialog.cpp \
    dialogs/tilewidget.cpp \
    components/colorobjectwidget.cpp \
    mail/mailnotification.cpp \
    tracking.cpp \
    dialogs/clusterdialog.cpp \
    components/emailbox.cpp \
    mail/servicecontroller.cpp \
    mail/service.cpp \
    mail/notification.cpp \
    mail/not.cpp \
    mail/notwidget.cpp \
    expiredialog.cpp \
    eula.cpp \
    aboutdialog.cpp \
    worker.cpp \
    warker.cpp \
    DS_sources/apps/apps-common/src/deepstream_common.c \
    DS_sources/apps/apps-common/src/deepstream_config_file_parser.c \
    DS_sources/apps/apps-common/src/deepstream_dewarper_bin.c \
    DS_sources/apps/apps-common/src/deepstream_dsexample.c \
    DS_sources/apps/apps-common/src/deepstream_osd_bin.c \
    DS_sources/apps/apps-common/src/deepstream_perf.c \
    DS_sources/apps/apps-common/src/deepstream_primary_gie_bin.c \
    DS_sources/apps/apps-common/src/deepstream_secondary_gie_bin.c \
    DS_sources/apps/apps-common/src/deepstream_sink_bin.c \
    DS_sources/apps/apps-common/src/deepstream_source_bin.c \
    DS_sources/apps/apps-common/src/deepstream_streammux.c \
    DS_sources/apps/apps-common/src/deepstream_tiled_display_bin.c \
    DS_sources/apps/apps-common/src/deepstream_tracker_bin.c \
    DS_sources/apps/apps-common/src/deepstream_dsanalytics.c \
    CameraList/camera_list_helper.cpp \
    CameraList/cameralistwidget.cpp \
    Database/config_database.cpp \
    Database/imageshowdialog.cpp \
    Database/search_by_date_time.cpp \
    GenerateReport/reportgeneratefromtoto.cpp \
    deepstream_source_code.cpp \
    Database/webcam.cpp \
    EmployeeAttendence/employeeattendence.cpp \
    CaluculateTimePerObBetweenInOutTime/calculatetimeperobject.cpp \
    db_sync/db_sync.cpp \
    db_sync/sync_checker.cpp \
    dialogs/progressbarloading.cpp \
    ShowFaceInTiles/showface.cpp \
    ShowFaceInTiles/faceinfo.cpp \
    SearchByGivenImage/searchbygivenimage.cpp \
    SearchByGivenImage/searchbyimage.cpp \
    mail/uniquefacewidget.cpp \
    mail/faceuniq.cpp \
    mail/servicelpr.cpp \
    mail/servicecontrollerforlpr.cpp \
#    mail/lpnotif.cpp
    mail/lpsinglewidg.cpp \
#    mail/lpnotwidget.cpp
    mail/lpnotwidget.cpp \
    lpr.cpp \
    dialogs/vd_face.cpp \
    names_buf_info.cpp \
    helperthread.cpp \
    tilerdisplay.cpp \
    testerthread.cpp \
    dialogs/singleslider.cpp \
    overcrowdthread.cpp \
    dialogs/carimgshowdialog.cpp \
    HelperClasses/perspectivetransformation.cpp \
    HelperClasses/WolfBinarization.cpp \
    MediaPlayer/player.cpp \
    MediaPlayer/playercontrols.cpp \
    MediaPlayer/playlistmodel.cpp \
    MediaPlayer/histogramwidget.cpp \
    MediaPlayer/videowidget.cpp \
    MediaPlayer/timeslider.cpp \
    MediaPlayer/barwidget.cpp \
    MediaPlayer/timerulerwidget.cpp \
    onvif_hasan/wsseapi.cpp \
    onvif_hasan/wsddapi.cpp \
    onvif_hasan/wsaapi.cpp \
    onvif_hasan/threads.cpp \
    onvif_hasan/stdsoap2.cpp \
    onvif_hasan/soapRemoteDiscoveryBindingProxy.cpp \
    onvif_hasan/soapPullPointSubscriptionBindingProxy.cpp \
    onvif_hasan/soapPTZBindingProxy.cpp \
    onvif_hasan/soapMediaBindingProxy.cpp \
    onvif_hasan/soapDeviceBindingProxy.cpp \
    onvif_hasan/soapC.cpp \
    onvif_hasan/smdevp.cpp \
    onvif_hasan/onvifdiscoClient.cpp \
    onvif_hasan/onvifdiscoC.cpp \
    onvif_hasan/mecevp.cpp \
    onvif_hasan/mainwindow_onvif.cpp \
    onvif_hasan/duration.cpp \
    onvif_hasan/dom.cpp \
    onvif_hasan/discoverythread.cpp \
    onvif_hasan/discoveryobj.cpp

HEADERS  += mainwindow.h \
   # feed.h \
    mystyles.h \
  #  camera.h \
    flowlayout.h \
    faces.h \
    face.h \
    feedwindow.h \
    person.h \
    dialogs/addcameradialog.h \
    dialogs/trackingsettingsdialog.h \
#    AI_src/activation_layer.h \
#    AI_src/activations.h \
#    AI_src/avgpool_layer.h \
#    AI_src/batchnorm_layer.h \
#    AI_src/blas.h \
#    AI_src/box.h \
#    AI_src/bugfixes.h \
#    AI_src/classifier.h \
#    AI_src/col2im.h \
#    AI_src/connected_layer.h \
#    AI_src/convolutional_layer.h \
#    AI_src/cost_layer.h \
#    AI_src/crnn_layer.h \
#    AI_src/crop_layer.h \
#    AI_src/cuda.h \
#    AI_src/data.h \
#    AI_src/deconvolutional_layer.h \
#    AI_src/demo.h \
#    AI_src/detection_layer.h \
#    AI_src/dropout_layer.h \
#    AI_src/gemm.h \
#    AI_src/gru_layer.h \
#    AI_src/im2col.h \
#    AI_src/image.h \
#    AI_src/layer.h \
#    AI_src/linefinder.h \
#    AI_src/list.h \
#    AI_src/local_layer.h \
#    AI_src/matrix.h \
#    AI_src/maxpool_layer.h \
#    AI_src/network.h \
#    AI_src/normalization_layer.h \
#    AI_src/option_list.h \
#    AI_src/parser.h \
#    AI_src/region_layer.h \
#    AI_src/reorg_layer.h \
#    AI_src/rnn_layer.h \
#    AI_src/route_layer.h \
#    AI_src/shortcut_layer.h \mainwindow.h \
#    AI_src/softmax_layer.h \
#    AI_src/stb_image_write.h \
#    AI_src/stb_image.h \
#    AI_src/tree.h \
#    AI_src/utils.h \
    dialogs/registerfacedialog.h \
    dialogs/analyzedialog.h \
    dialogs/settingsdialog.h \
    dialogs/tilewidget.h \
    components/colorobjectwidget.h \
    mail/mailnotification.h \
    tracking.h \
    dialogs/clusterdialog.h \
    components/emailbox.h \
    mail/servicecontroller.h \
    mail/service.h \
    mail/notification.h \
    mail/not.h \
    mail/notwidget.h \
    expiredialog.h \
    eula.h \
    aboutdialog.h \
    worker.h \
    warker.h \
    deepstream/deepstream_app.h \
    CameraList/camera_list_helper.h \
    CameraList/cameralistwidget.h \
    DatabaseConnection/sqlite_connection.h\
    Database/config_database.h \
    Database/imageshowdialog.h \
    Database/search_by_date_time.h \
    GenerateReport/reportgeneratefromtoto.h \
    deepstream_source_code.h \
    Database/webcam.h \
    EmployeeAttendence/employeeattendence.h \
    CaluculateTimePerObBetweenInOutTime/calculatetimeperobject.h \
    db_sync/db_sync.h \
    db_sync/sync_checker.h \
    dialogs/progressbarloading.h \
    ShowFaceInTiles/showface.h \
    ShowFaceInTiles/faceinfo.h \
    SearchByGivenImage/searchbygivenimage.h \
    SearchByGivenImage/searchbyimage.h \
    mail/uniquefacewidget.h \
    mail/faceuniq.h \
    mail/servicelpr.h \
    mail/servicecontrollerforlpr.h \
#    mail/lpnotif.h
    mail/lpsinglewidg.h \
#    mail/lpnotwidget.h
    mail/lpnotwidget.h \
    lpr.h \
    dialogs/vd_face.h \
    rectangle.h \
    names_buf_info.h \
    helperthread.h \
    tilerdisplay.h \
    testerthread.h \
    dialogs/singleslider.h \
    overcrowdthread.h \
    dialogs/carimgshowdialog.h \
    HelperClasses/perspectivetransformation.h \
    HelperClasses/WolfBinarization.h \
    MediaPlayer/player.h \
    MediaPlayer/playercontrols.h \
    MediaPlayer/playlistmodel.h \
    MediaPlayer/histogramwidget.h \
    MediaPlayer/videowidget.h \
    MediaPlayer/timeslider.h \
    MediaPlayer/barwidget.h \
    MediaPlayer/timerulerwidget.h \
    onvif_hasan/wsseapi.h \
    onvif_hasan/wsddapi.h \
    onvif_hasan/wsdd.nsmap \
    onvif_hasan/wsaapi.h \
    onvif_hasan/threads.h \
    onvif_hasan/stdsoap2.h \
    onvif_hasan/soapStub.h \
    onvif_hasan/soapRemoteDiscoveryBindingProxy.h \
    onvif_hasan/soapPullPointSubscriptionBindingProxy.h \
    onvif_hasan/soapPTZBindingProxy.h \
    onvif_hasan/soapMediaBindingProxy.h \
    onvif_hasan/soapH.h \
    onvif_hasan/soapDeviceBindingProxy.h \
    onvif_hasan/smdevp.h \
    onvif_hasan/onvifdiscoH.h \
    onvif_hasan/onvifdeviceStub.h \
    onvif_hasan/onvifdeviceH.h \
    onvif_hasan/mecevp.h \
    onvif_hasan/mainwindow_onvif.h \
    onvif_hasan/ErrorLog.h \
    onvif_hasan/duration.h \
    onvif_hasan/discoverythread.h \
    onvif_hasan/discoveryobj.h \
    onvif_hasan/descdevice.h



FORMS    += mainwindow.ui \
    feed.ui \
    faces.ui \
    face.ui \
    feedwindow.ui \
    dialogs/addcameradialog.ui \
    dialogs/trackingsettingsdialog.ui \
    dialogs/registerfacedialog.ui \
    #dialogs/footagewindow.ui \
    dialogs/analyzedialog.ui \
    dialogs/settingsdialog.ui \
    dialogs/tilewidget.ui \
    components/colorobjectwidget.ui \
    dialogs/clusterdialog.ui \
    components/emailbox.ui \
    mail/not.ui \
    mail/notwidget.ui \
    expiredialog.ui \
    eula.ui \
    aboutdialog.ui \
    CameraList/cameralistwidget.ui \
    Database/config_database.ui \
    Database/imageshowdialog.ui \
    Database/search_by_date_time.ui \
    GenerateReport/reportgeneratefromtoto.ui \
    Database/webcam.ui \
    EmployeeAttendence/employeeattendence.ui \
    CaluculateTimePerObBetweenInOutTime/calculatetimeperobject.ui \
    dialogs/progressbarloading.ui \
    ShowFaceInTiles/showface.ui \
    ShowFaceInTiles/faceinfo.ui \
    SearchByGivenImage/searchbygivenimage.ui \
    SearchByGivenImage/searchbyimage.ui \
    mail/uniquefacewidget.ui \
    mail/faceuniq.ui \
#    mail/lpnotif.ui
    mail/lpsinglewidg.ui \
#    mail/lpnotwidget.ui
    mail/lpnotwidget.ui \
    lpr.ui \
    dialogs/vd_face.ui \
    tilerdisplay.ui \
    dialogs/singleslider.ui \
    dialogs/carimgshowdialog.ui \
    onvif_hasan/mainwindow_onvif.ui


OBJECTS_DIR = ./objs/
QMAKE_CFLAGS += -DPLATFORM_TEGRA
QMAKE_CC = gcc
DEFINES += GPU DLIB_JPEG_SUPPORT CUDNN

QMAKE_CFLAGS        += -std=c++11
QMAKE_CXXFLAGS      += -std=c++11
INCLUDEPATH += -I/usr/include/opencv4/opencv2  /usr/local/cuda/include -I./rapidjson/include /home/sigmind/Pictures/sabbir/car_wiht_lp_and_recogFace_with_DBFace_branch_bkup/.HTPA-KK-1/curlpp/include
QMAKE_LFLAGS = -Wl,-O3  -DDLIB_JPEG_SUPPORT
LIBS +=  `pkg-config --cflags --libs opencv4` -lm -lX11 -llapack -lcurlpp -lcurl  -ldlib -L/usr/local/cuda/lib64 -lcuda -lcurand -lcusolver -lcudart -lcblas -lcublas

DEPENDPATH +=  RTSP-generator
INCLUDEPATH += RTSP-generator
#LIBS +=      -L../WC-Tegra-DS/OnvifDist -lRTSPlib\
#LIBS+= -lm -L/usr/local/deepstream -lnvdsgst_meta -lnvds_meta -lnvdsgst_helper -lm \
#       -Wl,-rpath,/usr/local/deepstream

LIBS+= -lm -L/usr/local/deepstream -lnvdsgst_meta -lnvds_meta -lnvdsgst_helper -lm \
#       -Wl,-rpath,/usr/local/deepstream

#LIBS+= -lm -L/opt/nvidia/deepstream/deepstream-5.0/lib -lnvdsgst_meta -lnvds_meta -lnvdsgst_helper -lnvds_utils -lm \
#       -lgstrtspserver-1.0 -ldl -Wl,-rpath,/opt/nvidia/deepstream/deepstream-5.0/lib

LIBS+= -lm -L/opt/nvidia/deepstream/deepstream-5.1/lib -lnvdsgst_meta -lnvds_meta -lnvdsgst_helper -lnvdsgst_smartrecord -lnvds_utils -lm \
       -lgstrtspserver-1.0 -ldl -Wl,-rpath,/opt/nvidia/deepstream/deepstream-5.1/lib

#LIBS+= -L$(LIB_INSTALL_DIR) -lnvdsgst_meta -lnvds_meta -lnvdsgst_helper -lnvds_utils -lm \
#       -lgstrtspserver-1.0 -Wl,-rpath,$(LIB_INSTALL_DIR)

#OBJECTS += darknet_cuda_obj/activation_kernels.o \
#    darknet_cuda_obj/avgpool_layer_kernels.o \
#    darknet_cuda_obj/blas_kernels.o \
#    darknet_cuda_obj/col2im_kernels.o \
#    darknet_cuda_obj/convolutional_kernels.o \
#    darknet_cuda_obj/crop_layer_kernels.o \
#    darknet_cuda_obj/deconvolutional_kernels.o \
#    darknet_cuda_obj/dropout_layer_kernels.o \
#    darknet_cuda_obj/im2col_kernels.o \
#    darknet_cuda_obj/maxpool_layer_kernels.o \
#    darknet_cuda_obj/network_kernels.o \
#    darknet_cuda_obj/cuda.o

RESOURCES += \
    .rsc/myfiles.qrc \
    qdarkstyle/style.qrc

QMAKE_CFLAGS += -DPLATFORM_TEGRA
LIBS       += -lcudnn
#LIBS+= -lm -L/usr/local/deepstream -lnvdsgst_helper -lnvdsgst_meta \
#       -Wl,-rpath,/usr/local/deepstream
# -lVLCQtCore -lVLCQtWidgets
#LIBS += -L/home/sigmind/watchcam-7.0/PTZControl/bin -L/home/sigmind/watchcam-7.0/PTZControl

#INCLUDEPATH += -I/home/sigmind/watchcam-7.0/PTZControl/bin -I/home/sigmind/watchcam-7.0/PTZControl/include -I/home/sigmind/watchcam-7.0/PTZControl

#LIBS += -L/home/sigmind/watchcam-7.0/PTZControl -ldhnetsdk

#INCLUDEPATH += -I/usr/include/tesseract -I/usr/include/leptonica


INCLUDEPATH += /usr/local/include/tesseract
INCLUDEPATH += /usr/local/include/leptonica
LIBS += -ltesseract -llept -lmpg123 -lao

INCLUDEPATH += -I/usr/local/include/cairo/
INCLUDEPATH += \
    /usr/include/gstreamer-1.0 \
    /usr/include/glib-2.0 \
    /usr/lib/aarch64-linux-gnu \
    DS_sources/includes \
    DS_sources/apps/apps-common/includes \
    /opt/nvidia/deepstream/deepstream-5.1/lib \
    /usr/lib \
    /lib/aarch64-linux-gnu \
    /usr/lib/aarch64-linux-gnu/gstreamer-1.0 \
    /opt/nvidia/deepstream/deepstream-5.1/sources/includes




#LIBS += -L/home/sigmind/PTZControl/bin /home/sigmind/PTZControl/bin export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/sigmind/PTZControl/bin
#LIBS += -L/home/sigmind/PTZControl/bin
#LIBS  += -L/home/sigmind/PTZControl/bin -ldhnetsdk
LIBS += -L/usr/lib/aarch64-linux-gnu/libjpeg.so
LIBS += -L/usr/lib/ -ljpeg

CONFIG += link_pkgconfig
PKGCONFIG += libcurl
PKGCONFIG += gstreamer-1.0 gstreamer-app-1.0 gstreamer-plugins-base-1.0 gstreamer-video-1.0 x11

# for onvif module
LIBS += -lssl -lcrypto


DISTFILES += \
    DS_sources/apps/apps-common/src/deepstream_common.o \
    DS_sources/apps/apps-common/src/deepstream_config_file_parser.o \
    DS_sources/apps/apps-common/src/deepstream_dewarper_bin.o \
    DS_sources/apps/apps-common/src/deepstream_dsexample.o \
    DS_sources/apps/apps-common/src/deepstream_osd_bin.o \
    DS_sources/apps/apps-common/src/deepstream_perf.o \
    DS_sources/apps/apps-common/src/deepstream_primary_gie_bin.o \
    DS_sources/apps/apps-common/src/deepstream_secondary_gie_bin.o \
    DS_sources/apps/apps-common/src/deepstream_sink_bin.o \
    DS_sources/apps/apps-common/src/deepstream_source_bin.o \
    DS_sources/apps/apps-common/src/deepstream_streammux.o \
    DS_sources/apps/apps-common/src/deepstream_tiled_display_bin.o \
    DS_sources/apps/apps-common/src/deepstream_tracker_bin.o \
#    onvif_hasan/deepstream_app_source1_peoplenet.txt

