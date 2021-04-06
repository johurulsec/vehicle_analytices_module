#-------------------------------------------------
#
# Project created by QtCreator 2020-01-17T17:53:26

# Successfully Compiled, Run and Tested by ABu Anas Shuvom, Founder and CEO at SIGMIND
#
#-------------------------------------------------

QT       += core gui

DESTDIR = RTSPlib

TARGET = RTSPlib
TEMPLATE = lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#DESTDIR = ./obj

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CONFIG += c++11



SOURCES += \
    getrtsp.cpp \
    gsoap-onvif-mod/plugin/dom.cpp \
    gsoap-onvif-mod/plugin/duration.cpp \
    gsoap-onvif-mod/plugin/mecevp.cpp \
    gsoap-onvif-mod/plugin/smdevp.cpp \
        gsoap-onvif-mod/plugin/threads.cpp \
   # gsoap-onvif-mod/plugin/wsddapi.cpp \
    gsoap-onvif-mod/proxycpp/soapAdvancedSecurityServiceBindingProxy.cpp \
    gsoap-onvif-mod/plugin/wsaapi.cpp \
    gsoap-onvif-mod/plugin/wsseapi.cpp \
    gsoap-onvif-mod/proxycpp/soapDeviceBindingProxy.cpp \
    gsoap-onvif-mod/proxycpp/soapMediaBindingProxy.cpp \
#    gsoap-onvif-mod/proxycpp/soapMediaBindingService.cpp \
    gsoap-onvif-mod/proxycpp/soapPTZBindingProxy.cpp \
#    gsoap-onvif-mod/proxycpp/soapPTZBindingService.cpp \
    gsoap-onvif-mod/proxycpp/soapPullPointSubscriptionBindingProxy.cpp \
#    gsoap-onvif-mod/proxycpp/soapPullPointSubscriptionBindingService.cpp \
    gsoap-onvif-mod/proxycpp/soapRemoteDiscoveryBindingProxy.cpp \
    gsoap-onvif-mod/soapC.cpp \
    gsoap-onvif-mod/soapClient.cpp \
    gsoap-onvif-mod/stdsoap2.cpp
#    onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/onvif/discoveryobj.cpp \
#    onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/onvif/discoverythread.cpp \
#    onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/onvif/server.cpp \
#    onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/onvifdiscoC.cpp \
#    onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/onvifdiscoClient.cpp \
#    onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/stdsoap2.cpp \
#    onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/threads.cpp \
#    onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/wsaapi.cpp \
#    onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/wsddapi.cpp \
#    onvif/discoverythread.cpp \
#    onvif/discoveryobj.cpp \



HEADERS += \
        getrtsp.h \
        gsoap-onvif-mod/ErrorLog.h \
        gsoap-onvif-mod/onvif.h \
        gsoap-onvif-mod/plugin/duration.h \
        gsoap-onvif-mod/plugin/mecevp.h \
        gsoap-onvif-mod/plugin/smdevp.h \
        gsoap-onvif-mod/plugin/threads.h \
        gsoap-onvif-mod/plugin/wsaapi.h \
        gsoap-onvif-mod/plugin/wsddapi.h \
        gsoap-onvif-mod/plugin/wsseapi.h \
        gsoap-onvif-mod/soap-include/soapAdvancedSecurityServiceBindingProxy.h \
        gsoap-onvif-mod/soap-include/soapAdvancedSecurityServiceBindingService.h \
        gsoap-onvif-mod/soap-include/soapDeviceBindingProxy.h \
        gsoap-onvif-mod/soap-include/soapDeviceBindingService.h \
        gsoap-onvif-mod/soap-include/soapDeviceIOBindingProxy.h \
        gsoap-onvif-mod/soap-include/soapDeviceIOBindingService.h \
        gsoap-onvif-mod/soap-include/soapImagingBindingProxy.h \
        gsoap-onvif-mod/soap-include/soapImagingBindingService.h \
        gsoap-onvif-mod/soap-include/soapMediaBindingProxy.h \
        gsoap-onvif-mod/soap-include/soapMediaBindingService.h \
        gsoap-onvif-mod/soap-include/soapPTZBindingProxy.h \
        gsoap-onvif-mod/soap-include/soapPTZBindingService.h \
        gsoap-onvif-mod/soap-include/soapPullPointSubscriptionBindingProxy.h \
        gsoap-onvif-mod/soap-include/soapPullPointSubscriptionBindingService.h \
        gsoap-onvif-mod/soap-include/soapRemoteDiscoveryBindingProxy.h \
        gsoap-onvif-mod/soap-include/soapRemoteDiscoveryBindingService.h \
        gsoap-onvif-mod/soap-include/soapwsddProxy.h \
        gsoap-onvif-mod/soap-include/soapwsddService.h \
        gsoap-onvif-mod/soap-include/soapwsrmProxy.h \
        gsoap-onvif-mod/soap-include/soapwsrmService.h \
        gsoap-onvif-mod/soapH.h \
        gsoap-onvif-mod/soapStub.h \
        gsoap-onvif-mod/stdsoap2.h
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/onvif/descdevice.h \
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/onvif/discoveryobj.h \
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/onvif/discoverythread.h \
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/onvifdiscoH.h \
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/onvifdiscoStub.h \
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/stdsoap2.h \
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/stlvector.h \
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/threads.h \
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/wsaapi.h \
#        onvif-qt-server-client/onviflibs/onvifcore/OnvifDiscoveryLib/soap/wsddapi.h \
#        soap/onvifdiscoH.h \
#        soap/onvifdiscoStub.h \
#    onvif/descdevice.h \
#    onvif/discoverythread.h \
#    onvif/discoveryobj.h







INCLUDEPATH += gsoap-onvif-mod/soap-include/ gsoap-onvif-mod/plugin/ gsoap-onvif-mod/

QMAKE_CC = gcc
#QMAKE_CXX = g++
QMAKE_LFLAGS += -Wall -g -w -fPIC -DWITH_NONAMESPACES -fno-use-cxa-atexit -fexceptions -DWITH_DOM  -DWITH_OPENSSL -DSOAP_DEBUG
CONFIG += link_pkgconfig
LIBS += -lssl -lcrypto
#OBJECTS_DIR += ./obj/


# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
