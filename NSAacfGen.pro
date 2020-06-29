#-------------------------------------------------
#
# Project created by QtCreator 2017-11-18T08:41:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NSAacfGen
TEMPLATE = app


SOURCES += main.cpp\
        nsaacfgen.cpp \
    acfdatapoint.cpp \
    correctionset.cpp \
    mushor.cpp \
    about.cpp \
    acfstatus.cpp \
    basefilelists.cpp \
    antennacalinfo.cpp \
    freqref.cpp

HEADERS  += nsaacfgen.h \
    acfdatapoint.h \
    correctionset.h \
    freqref.h \
    mushor.h \
    about.h \
    acfstatus.h \
    basefilelists.h \
    antennacalinfo.h \
    globals.h

FORMS    += nsaacfgen.ui \
    about.ui

OTHER_FILES +=

RESOURCES += \
    resources.qrc

DISTFILES +=
