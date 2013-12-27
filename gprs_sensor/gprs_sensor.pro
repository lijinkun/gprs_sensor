#-------------------------------------------------
#
# Project created by QtCreator 2013-12-22T20:04:56
#
#-------------------------------------------------

QT       += core gui
QT       += opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gprs_sensor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwindow.cpp \
    treeview.cpp

HEADERS  += mainwindow.h \
    glwindow.h \
    treeview.h

FORMS    += mainwindow.ui

RESOURCES += \
    images/res.qrc

RC_FILE = gprs_sensor.rc


