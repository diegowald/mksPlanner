#-------------------------------------------------
#
# Project created by QtCreator 2015-12-02T18:55:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mksPlanner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    views/unitswindow.cpp \
    models/unitsmodel.cpp

HEADERS  += mainwindow.h \
    views/unitswindow.h \
    models/unitsmodel.h

FORMS    += mainwindow.ui \
    views/unitswindow.ui

CONFIG += mobility
MOBILITY = 

