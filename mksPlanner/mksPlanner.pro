#-------------------------------------------------
#
# Project created by QtCreator 2015-12-02T18:55:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mksPlanner
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    views/unitswindow.cpp \
    models/unitsmodel.cpp \
    models/unit.cpp \
    models/entitybase.cpp \
    views/dlguniteditor.cpp \
    persistance/persister.cpp \
    persistance/librarybase.cpp \
    persistance/materialslibrary.cpp \
    models/modelbase.cpp

HEADERS  += mainwindow.h \
    views/unitswindow.h \
    models/unitsmodel.h \
    models/unit.h \
    models/entitybase.h \
    views/dlguniteditor.h \
    persistance/persister.h \
    persistance/librarybase.h \
    persistance/materialslibrary.h \
    models/modelbase.h

FORMS    += mainwindow.ui \
    views/unitswindow.ui \
    views/dlguniteditor.ui

CONFIG += mobility
MOBILITY = 

