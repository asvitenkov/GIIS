#-------------------------------------------------
#
# Project created by QtCreator 2012-09-21T21:53:49
#
#-------------------------------------------------

QT       += core gui

TARGET = GIIS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    coordinateview.cpp \
    coordinatescene.cpp \
    command.cpp \
    abstractpaintalgorithm.cpp \
    algorithmdda.cpp \
    painter.cpp \
    algorithmbresenham.cpp \
    debugmodebox.cpp \
    abstractlistener.cpp \
    listenerdda.cpp

HEADERS  += mainwindow.h \
    coordinateview.h \
    coordinatescene.h \
    command.h \
    abstractpaintalgorithm.h \
    algorithmdda.h \
    defines.h \
    painter.h \
    algorithmbresenham.h \
    debugmodebox.h \
    abstractlistener.h \
    listenerdda.h

FORMS    += mainwindow.ui \
    debugmodebox.ui
