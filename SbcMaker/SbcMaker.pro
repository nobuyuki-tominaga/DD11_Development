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
    OptionSettingDialog.cpp \
    Settings.cpp

HEADERS  += SbcMakerMainWindow.h \
    PasswdSettingDialog.h \
    SbcMakerCommon.h \
    OptionSettingDialog.h \
    Settings.h

FORMS    += SbcMakerMainWindow.ui \
    PasswdSettingDialog.ui \
    OptionSettingDialog.ui

unix: CONFIG += link_pkgconfig
#unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/opencv4.pc
#unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/opencv.pc
unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/libcurl.pc

unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/libssl.pc

unix: PKGCONFIG += /usr/lib/x86_64-linux-gnu/pkgconfig/libcrypto.pc

win32: LIBS += -L$$PWD/'../../../../../../Program Files/OpenSSL-Win64/lib/' -llibssl
win32: LIBS += -L$$PWD/'../../../../../../Program Files/OpenSSL-Win64/lib/' -llibcrypto
win32: INCLUDEPATH += $$PWD/'../../../../../../Program Files/OpenSSL-Win64/include'
win32: DEPENDPATH += $$PWD/'../../../../../../Program Files/OpenSSL-Win64/include'

win32: LIBS += -L$$PWD/'../../../../../../Program Files/curl-7.72.0-win64-mingw/lib/' -lcurl
win32: INCLUDEPATH += $$PWD/'../../../../../../Program Files/curl-7.72.0-win64-mingw/include'
win32: DEPENDPATH += $$PWD/'../../../../../../Program Files/curl-7.72.0-win64-mingw/include'
