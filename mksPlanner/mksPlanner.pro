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
    models/unitsmodel.cpp \
    models/unit.cpp \
    models/entitybase.cpp \
    views/dlguniteditor.cpp \
    persistance/persister.cpp \
    persistance/librarybase.cpp \
    persistance/materialslibrary.cpp \
    models/modelbase.cpp \
    views/tablewindow.cpp \
    models/material.cpp \
    views/dlgmaterialeditor.cpp \
    globalcontainer.cpp \
    models/componentesmateriales.cpp \
    models/componentematerial.cpp \
    views/dlgcomponentematerial.cpp \
    models/materialesbasemodel.cpp \
    models/materialesmodel.cpp \
    models/tasksmodel.cpp \
    models/proveedoresmodel.cpp \
    models/proveedor.cpp \
    views/dlgeditproveedor.cpp \
    models/tareasproveedoresmodel.cpp \
    models/taskproveedor.cpp \
    views/dlgtaskproveedoredit.cpp

HEADERS  += mainwindow.h \
    models/unitsmodel.h \
    models/unit.h \
    models/entitybase.h \
    views/dlguniteditor.h \
    persistance/persister.h \
    persistance/librarybase.h \
    persistance/materialslibrary.h \
    models/modelbase.h \
    views/tablewindow.h \
    models/material.h \
    views/dlgmaterialeditor.h \
    globalcontainer.h \
    models/componentesmateriales.h \
    models/componentematerial.h \
    views/dlgcomponentematerial.h \
    models/materialesbasemodel.h \
    models/materialesmodel.h \
    models/tasksmodel.h \
    models/proveedoresmodel.h \
    models/proveedor.h \
    views/dlgeditproveedor.h \
    models/tareasproveedoresmodel.h \
    models/taskproveedor.h \
    views/dlgtaskproveedoredit.h

FORMS    += mainwindow.ui \
    views/dlguniteditor.ui \
    views/tablewindow.ui \
    views/dlgmaterialeditor.ui \
    views/dlgcomponentematerial.ui \
    views/dlgeditproveedor.ui \
    views/dlgtaskproveedoredit.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    mksplanner.qrc

