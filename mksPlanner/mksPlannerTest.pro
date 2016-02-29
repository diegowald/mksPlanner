#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T13:39:43
#
#-------------------------------------------------

QT       += sql testlib

QT       -= gui

CONFIG += c++11

TARGET = tst_mksplannertesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_mksplannertesttest.cpp \
    models/entitybase.cpp \
    models/unit.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    models/entitybase.h \
    models/unit.h
