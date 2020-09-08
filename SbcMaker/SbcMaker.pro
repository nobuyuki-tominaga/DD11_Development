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
    OptionSettingWindow.cpp \
    PasswdSettingDialog.cpp

HEADERS  += SbcMakerMainWindow.h \
    OptionSettingWindow.h \
    PasswdSettingDialog.h

FORMS    += SbcMakerMainWindow.ui \
    OptionSettingWindow.ui \
    PasswdSettingDialog.ui
