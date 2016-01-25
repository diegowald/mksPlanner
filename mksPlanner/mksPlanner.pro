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
    views/calculadoramaterialeswindow.cpp \
    models/validmaterialfiltermodel.cpp \
    views/dlgeditproject.cpp \
    persistance/projectlibrary.cpp \
    models/proyectomodel.cpp \
    models/proyecto.cpp \
    views/projectwindow.cpp \
    models/rubro.cpp \
    models/rubrosmodel.cpp \
    views/dlgeditrubro.cpp \
    persistance/updater.cpp \
    persistance/materialesupdater.cpp \
    models/costomaterialesmodel.cpp \
    models/costomaterial.cpp \
    models/costomaterialesdelegate.cpp \
    models/costomaterialcompuesto.cpp \
    models/rubrosproveedoresmodel.cpp \
    models/rubroroveedor.cpp \
    views/dlgeditrubroproveedor.cpp

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
    views/calculadoramaterialeswindow.h \
    models/validmaterialfiltermodel.h \
    views/dlgeditproject.h \
    persistance/projectlibrary.h \
    models/proyectomodel.h \
    models/proyecto.h \
    views/projectwindow.h \
    models/rubro.h \
    models/rubrosmodel.h \
    views/dlgeditrubro.h \
    persistance/updater.h \
    persistance/materialesupdater.h \
    models/costomaterialesmodel.h \
    models/costomaterial.h \
    models/costomaterialesdelegate.h \
    models/costomaterialcompuesto.h \
    models/rubrosproveedoresmodel.h \
    models/rubroroveedor.h \
    views/dlgeditrubroproveedor.h

FORMS    += mainwindow.ui \
    views/dlguniteditor.ui \
    views/tablewindow.ui \
    views/dlgmaterialeditor.ui \
    views/dlgcomponentematerial.ui \
    views/dlgeditproveedor.ui \
    views/calculadoramaterialeswindow.ui \
    views/dlgeditproject.ui \
    views/projectwindow.ui \
    views/dlgeditrubro.ui \
    views/dlgeditrubroproveedor.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    mksplanner.qrc

