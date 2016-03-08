#-------------------------------------------------
#
# Project created by QtCreator 2015-12-02T18:55:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

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
    models/proveedoresmodel.cpp \
    models/proveedor.cpp \
    views/dlgeditproveedor.cpp \
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
    views/dlgeditrubroproveedor.cpp \
    persistance/projectupdater.cpp \
    models/planningtask.cpp \
    models/planningtaskmodel.cpp \
    views/dlgeditplanningtask.cpp \
    models/planningtaskmodeladapter.cpp \
    models/materialfiltermodel.cpp \
    models/proveedorbyrubrofiltermodel.cpp \
    models/planningtaskmodelconstraint.cpp \
    models/planningtaskconstraint.cpp \
    models/planningtaskmodelconstraintadapter.cpp \
    models/planningtaskmodelconstraintfiltered.cpp \
    views/dlgeditplanningtaskconstraint.cpp \
    models/executiontask.cpp \
    models/executiontaskmodel.cpp \
    models/executiontaskmodeladapter.cpp \
    models/executiontaskconstraint.cpp \
    models/executiontaskmodelconstraint.cpp \
    models/executiontaskmodelconstraintadapter.cpp \
    views/dlgeditexecutiontask.cpp \
    models/executiontaskmodelconstraintfiltered.cpp

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
    models/proveedoresmodel.h \
    models/proveedor.h \
    views/dlgeditproveedor.h \
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
    views/dlgeditrubroproveedor.h \
    persistance/projectupdater.h \
    models/planningtask.h \
    models/planningtaskmodel.h \
    views/dlgeditplanningtask.h \
    models/planningtaskmodeladapter.h \
    models/materialfiltermodel.h \
    models/proveedorbyrubrofiltermodel.h \
    models/planningtaskmodelconstraint.h \
    models/planningtaskconstraint.h \
    models/planningtaskmodelconstraintadapter.h \
    models/planningtaskmodelconstraintfiltered.h \
    views/dlgeditplanningtaskconstraint.h \
    models/executiontask.h \
    models/executiontaskmodel.h \
    models/executiontaskmodeladapter.h \
    models/executiontaskconstraint.h \
    models/executiontaskmodelconstraint.h \
    models/executiontaskmodelconstraintadapter.h \
    views/dlgeditexecutiontask.h \
    models/executiontaskmodelconstraintfiltered.h

FORMS    += mainwindow.ui \
    views/dlguniteditor.ui \
    views/tablewindow.ui \
    views/dlgmaterialeditor.ui \
    views/dlgcomponentematerial.ui \
    views/dlgeditproveedor.ui \
    views/dlgeditproject.ui \
    views/projectwindow.ui \
    views/dlgeditrubro.ui \
    views/dlgeditrubroproveedor.ui \
    views/dlgeditplanningtask.ui \
    views/dlgeditplanningtaskconstraint.ui \
    views/dlgeditexecutiontask.ui

CONFIG += mobility
MOBILITY =

RESOURCES += \
    mksplanner.qrc

#unix {
#  !macx: LIBEXT = so
#  macx: LIBEXT = dylib
#  CONFIG( static ) {
#    LIBEXT = a
#  }
#  # qmake insists on passing Qt's -L path first, where there could be a different version of our own
#  # libraries. Therefore we pass our own libraries like object files (without -l!) and with full path.
#  LIBS += ../mksPlanner/3rdParty/kdchart-2.5.1-source/lib/libkdchart.so  ../mksPlanner/3rdParty/kdchart-2.5.1-source/lib/libtesttools.so
#}
## The problem is less important on Windows and also harder to fix, so do it the usual way
#win32: LIBS += -L$${TOP_BUILD_DIR}/lib -l$$KDCHARTLIB -l$$TESTTOOLSLIB

#INCLUDEPATH += \
#            ../3rdParty/kdchart-2.5.1-source/include \
#            ../3rdParty/kdchart-2.5.1-source/include/KDChart \
#            ../3rdParty/kdchart-2.5.1-source/include/KDGantt \
#            ../3rdParty/kdchart-2.5.1-source/examples/tools
#DEPENDPATH += \
#            ../3rdParty/kdchart-2.5.1-source/include \
#            ../3rdParty/kdchart-2.5.1-source/examples/tools

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdParty/kdchart-bin/lib/ -lkdchart2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdParty/kdchart-bin/lib/ -lkdchartd2
else:unix: LIBS += -L$$PWD/../../kdchart-bin/lib/ -lkdchart


INCLUDEPATH += $$PWD/../3rdParty/kdchart-2.5.1-source/include/KDChart
INCLUDEPATH += $$PWD/../3rdParty/kdchart-2.5.1-source/include/KDGantt
DEPENDPATH += $$PWD/../3rdParty/kdchart-2.5.1-source/include/KDChart
DEPENDPATH += $$PWD/../3rdParty/kdchart-2.5.1-source/include/KDGantt
