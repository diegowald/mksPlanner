include( $${TOP_SOURCE_DIR}/examples/examples.pri )

HEADERS= mainwindow.h
SOURCES= main.cpp mainwindow.cpp
RESOURCES = BarChart.qrc

message( "Building ''$$TARGET'' using LIBS ''$$LIBS''" )
