#-------------------------------------------------
#
# Project created by QtCreator 2020-09-08T09:17:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SbcMaker
TEMPLATE = app


SOURCES += main.cpp\
        SbcMakerMainWindow.cpp \
    PasswdSettingDialog.cpp \
    OptionSettingDialog.cpp

HEADERS  += SbcMakerMainWindow.h \
    PasswdSettingDialog.h \
    SbcMakerCommon.h \
    OptionSettingDialog.h

FORMS    += SbcMakerMainWindow.ui \
    PasswdSettingDialog.ui \
    OptionSettingDialog.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/opencv4.pc
#unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/opencv.pc
unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/libcurl.pc

unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/libssl.pc

unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/libcrypto.pc
