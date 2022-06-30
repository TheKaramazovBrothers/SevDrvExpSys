#-------------------------------------------------
#
# Project created by QtCreator 2022-06-07T10:49:44
#
#-------------------------------------------------
INCLUDEPATH+=$${PWD}/FrontEnd/include/
INCLUDEPATH+=$${PWD}/BackEnd/include/

QT       += widgets printsupport
QT       += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SevDrvExpSys
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        FrontEnd/src/qttreemanager.cpp \
    FrontEnd/src/gtplot.cpp \
    FrontEnd/src/qcpitemhandletag.cpp \
    FrontEnd/src/qcpitemmeasure.cpp \
    FrontEnd/src/qcustomplot.cpp \
    FrontEnd/src/plotunitgraph.cpp \
    BackEnd/src/BackGroundTask.cpp

HEADERS  += mainwindow.h \
        FrontEnd/include/qttreemanager.h \
    FrontEnd/include/gtplot.h \
    FrontEnd/include/qcpitemhandletag.h \
    FrontEnd/include/qcpitemmeasure.h \
    FrontEnd/include/qcustomplot.h \
    FrontEnd/include/plotunitgraph.h \
    BackEnd/include/BackGroundTask.h \
    BackEnd/include/DspCpu.h

FORMS    += mainwindow.ui \
    FrontEnd/ui/plotunitgraph.ui

RESOURCES += \
    servodrv.qrc
