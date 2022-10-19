#----------------------------------------------------------------------------
#
# Project created by QtCreator 2022-06-07T10:49:44
#
#----------------------------------------------------------------------------
DEFINES += __MW_STDINT_H__

INCLUDEPATH += $$quote(D:/Program Files/Polyspace/R2020a/extern/include)
INCLUDEPATH += $$quote(D:/Program Files/Polyspace/R2020a/extern/include/win64)

LIBS+=-L$$quote(D:/Program Files/Polyspace/R2020a/extern/lib/win64/mingw64) -llibmx
LIBS+=-L$$quote(D:/Program Files/Polyspace/R2020a/extern/lib/win64/mingw64) -llibmat
LIBS+=-L$$quote(D:/Program Files/Polyspace/R2020a/extern/lib/win64/mingw64) -llibmex
LIBS+=-L$$quote(D:/Program Files/Polyspace/R2020a/extern/lib/win64/mingw64) -llibeng
LIBS+=-L$$quote(D:/Program Files/Polyspace/R2020a/extern/lib/win64/mingw64) -lmclmcr
LIBS+=-L$$quote(D:/Program Files/Polyspace/R2020a/extern/lib/win64/mingw64) -lmclmcrrt



INCLUDEPATH+=$${PWD}/FrontEnd/include/
INCLUDEPATH+=$${PWD}/BackEnd/include/
INCLUDEPATH+=$${PWD}/SimKernel/include/
INCLUDEPATH+=$${PWD}/AnalysisKernel/include/
INCLUDEPATH+=$${PWD}/FrontEnd/ui/
INCLUDEPATH+=$${PWD}/Lib/include



QT       += widgets printsupport
QT       += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SevDrvExpSys
TEMPLATE = app

UI_DIR  = ./FrontEnd/ui


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
    BackEnd/src/TuningCmd.cpp \
    FrontEnd/src/dialogselectcurve.cpp \
    FrontEnd/src/prmvartable.cpp \
    BackEnd/src/PrmConfigService.cpp \
    SimKernel/src/VelCtlLoop.cpp \
    SimKernel/src/PosCtlLoop.cpp \
    SimKernel/src/PosTrajProd.cpp \
    AnalysisKernel/src/FastFourierTrans.cpp \
    AnalysisKernel/src/SignalAnalysis.cpp \
    FrontEnd/src/dftdialog.cpp \
    SimKernel/src/ExciSigProd.cpp \
    AnalysisKernel/src/OrthCorelAnalysis.cpp

HEADERS  += mainwindow.h \
        FrontEnd/include/qttreemanager.h \
    FrontEnd/include/gtplot.h \
    FrontEnd/include/qcpitemhandletag.h \
    FrontEnd/include/qcpitemmeasure.h \
    FrontEnd/include/qcustomplot.h \
    FrontEnd/include/plotunitgraph.h \
    BackEnd/include/BackGroundTask.h \
    BackEnd/include/DspCpu.h \
    Lib/include/my_fft.h \
    Lib/include/my_prbs_idf_n4sid.h \
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
    BackEnd/include/TuningCmd.h \
    FrontEnd/include/dialogselectcurve.h \
    FrontEnd/include/prmvartable.h \
    BackEnd/include/PrmConfigService.h \
    SimKernel/include/VelCtlLoop.h \
    SimKernel/include/PosCtlLoop.h \
    SimKernel/include/PosTrajProd.h \
    AnalysisKernel/include/FastFourierTrans.h \
    AnalysisKernel/include/SignalAnalysis.h \
    FrontEnd/include/dftdialog.h \
    SimKernel/include/ExciSigProd.h \
    AnalysisKernel/include/OrthCorelAnalysis.h \

FORMS    += \
    FrontEnd/ui/plotunitgraph.ui \
    FrontEnd/ui/tabmodectl.ui \
    FrontEnd/ui/dialogselectcurve.ui \
    FrontEnd/ui/dftdialog.ui \
    FrontEnd/ui/dftsettingdialog.ui \
    FrontEnd/ui/mainwindow.ui

RESOURCES += \
    servodrv.qrc


win32: LIBS += -L$$PWD/Lib/src/ -lmy_fft
win32: LIBS += -L$$PWD/Lib/src/ -lmy_prbs_idf_n4sid

INCLUDEPATH += $$PWD/Lib/src
DEPENDPATH += $$PWD/Lib/src




