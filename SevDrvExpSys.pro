#-------------------------------------------------
#
# Project created by QtCreator 2022-06-07T10:49:44
#
#-------------------------------------------------
INCLUDEPATH+=$${PWD}/FrontEnd/include/
INCLUDEPATH+=$${PWD}/BackEnd/include/
INCLUDEPATH+=$${PWD}/SimKernel/include/

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
    BackEnd/src/BackGroundTask.cpp \
    SimKernel/src/MechModel.cpp \
    SimKernel/src/SevCtlPrmTblDef.cpp \
    SimKernel/src/CurrCtlLoop.cpp \
    SimKernel/src/Cia402AppEmu.cpp \
    SimKernel/src/SevDrvTask.cpp \
    SimKernel/src/SevDrvObj.cpp \
    SimKernel/src/SevDrvMeas.cpp \
    SimKernel/src/SevHardRes.cpp \
    SimKernel/src/SeqCtlFunc.cpp \
    FrontEnd/src/tabmodectl.cpp \
    BackEnd/src/TuningCmd.cpp

HEADERS  += mainwindow.h \
        FrontEnd/include/qttreemanager.h \
    FrontEnd/include/gtplot.h \
    FrontEnd/include/qcpitemhandletag.h \
    FrontEnd/include/qcpitemmeasure.h \
    FrontEnd/include/qcustomplot.h \
    FrontEnd/include/plotunitgraph.h \
    BackEnd/include/BackGroundTask.h \
    BackEnd/include/DspCpu.h \
    SimKernel/include/MechModel.h \
    SimKernel/include/SevCtlPrmTblDef.h \
    SimKernel/include/CurrCtlLoop.h \
    SimKernel/include/Cia402AppEmu.h \
    SimKernel/include/SevDrvTask.h \
    SimKernel/include/SevDrvObj.h \
    SimKernel/include/SevDrvMeas.h \
    SimKernel/include/SevHardRes.h \
    SimKernel/include/SeqCtlFunc.h \
    FrontEnd/include/tabmodectl.h \
    BackEnd/include/TuningCmd.h

FORMS    += mainwindow.ui \
    FrontEnd/ui/plotunitgraph.ui \
    FrontEnd/ui/tabmodectl.ui

RESOURCES += \
    servodrv.qrc
