#-------------------------------------------------
#
# Project created by QtCreator 2018-08-21T14:28:19
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IntelligentCar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controller.cpp \
    cholenmap.cpp \
    leftwidget.cpp \
    serialportassistant.cpp \
    lightheart.cpp \
    carheart.cpp \
    lightinstructions.cpp \
    carinstructions.cpp

HEADERS  += mainwindow.h \
    controller.h \
    cholenmap.h \
    leftwidget.h \
    serialportassistant.h \
    lightheart.h \
    carheart.h \
    lightinstructions.h \
    carinstructions.h

FORMS    += mainwindow.ui \
    controller.ui \
    leftwidget.ui \
    serialportassistant.ui

RESOURCES += \
    res.qrc
