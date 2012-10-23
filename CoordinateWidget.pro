#-------------------------------------------------
#
# Project created by QtCreator 2012-09-21T21:53:49
#
#-------------------------------------------------

QT       += core gui

TARGET = CoordinateWidget
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
    debugmodebox.cpp

HEADERS  += mainwindow.h \
    coordinateview.h \
    coordinatescene.h \
    command.h \
    abstractpaintalgorithm.h \
    algorithmdda.h \
    defines.h \
    painter.h \
    algorithmbresenham.h \
    debugmodebox.h

FORMS    += mainwindow.ui \
    debugmodebox.ui
