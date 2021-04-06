#-------------------------------------------------
#
# Project created by QtCreator 2018-03-09T17:26:42
#
#-------------------------------------------------

QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = watchcamSS-v8
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
    feed.cpp \
    mystyles.cpp \
    camera.cpp \
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
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_common.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_config_file_parser.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_dewarper_bin.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_dsexample.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_osd_bin.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_perf.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_primary_gie_bin.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_secondary_gie_bin.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_sink_bin.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_source_bin.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_streammux.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_tiled_display_bin.c \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_tracker_bin.c

HEADERS  += mainwindow.h \
    feed.h \
    mystyles.h \
    camera.h \
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
#    AI_src/shortcut_layer.h \
#    AI_src/softmax_layer.h \
#    AI_src/stb_image_write.h \
#    AI_src/stb_image.h \
#    AI_src/tree.h \
#    AI_src/utils.h \
    rectangle.h \
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
    deepstream/deepstream_app.h

FORMS    += mainwindow.ui \
    feed.ui \
    faces.ui \
    face.ui \
    feedwindow.ui \
    dialogs/addcameradialog.ui \
    dialogs/trackingsettingsdialog.ui \
    dialogs/registerfacedialog.ui \
    dialogs/footagewindow.ui \
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
    aboutdialog.ui


OBJECTS_DIR = ./objs/
QMAKE_CFLAGS += -DPLATFORM_TEGRA
QMAKE_CC = gcc
DEFINES += GPU DLIB_JPEG_SUPPORT CUDNN

#QMAKE_CFLAGS        += -std=c++11
#QMAKE_CXXFLAGS      += -std=c++11
INCLUDEPATH += /usr/local/include/opencv2 /usr/local/cuda/include -I./rapidjson/include
QMAKE_LFLAGS = -Wl,-O3  -DDLIB_JPEG_SUPPORT
LIBS +=  `pkg-config --cflags --libs opencv` -lm -lX11 -ljpeg -ldlib -lcblas -llapack -lcurl -lcurlpp -L/usr/local/cuda/lib64 -lcuda -lcudart -lcublas -lcurand



#LIBS+= -lm -L/usr/local/deepstream -lnvdsgst_meta -lnvds_meta -lnvdsgst_helper -lm \
#       -Wl,-rpath,/usr/local/deepstream

#LIBS+= -lm -L/usr/local/deepstream -lnvdsgst_meta -lnvds_meta -lnvdsgst_helper -lm \
#       -Wl,-rpath,/usr/local/deepstream

LIBS+= -lm -L/opt/nvidia/deepstream/deepstream-4.0/lib -lnvdsgst_meta -lnvds_meta -lnvdsgst_helper -lnvds_utils -lm \
       -lgstrtspserver-1.0 -Wl,-rpath,/opt/nvidia/deepstream/deepstream-4.0/lib

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

INCLUDEPATH += -I/usr/local/include/cairo/
INCLUDEPATH += \
    /usr/include/gstreamer-1.0 \
    /usr/include/glib-2.0 \
    /usr/lib/x86_64-linux-gnu/glib-2.0/include \
    /home/sigmind/deepstream_sdk_v4.0_jetson/sources/includes \
    /home/sigmind/deepstream_sdk_v4.0_jetson/sources/apps/apps-common/includes \
    /opt/nvidia/deepstream/deepstream-4.0/lib




#LIBS += -L/home/sigmind/PTZControl/bin /home/sigmind/PTZControl/bin export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/sigmind/PTZControl/bin
#LIBS += -L/home/sigmind/PTZControl/bin
#LIBS  += -L/home/sigmind/PTZControl/bin -ldhnetsdk


CONFIG += link_pkgconfig
PKGCONFIG += libcurl
PKGCONFIG += gstreamer-1.0 gstreamer-app-1.0 gstreamer-plugins-base-1.0 gstreamer-video-1.0 x11


DISTFILES += \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_common.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_config_file_parser.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_dewarper_bin.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_dsexample.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_osd_bin.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_perf.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_primary_gie_bin.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_secondary_gie_bin.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_sink_bin.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_source_bin.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_streammux.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_tiled_display_bin.o \
    ../deepstream_sdk_v4.0_jetson/sources/apps/apps-common/src/deepstream_tracker_bin.o

