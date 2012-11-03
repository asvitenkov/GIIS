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
    abstractlinelistener.cpp \
    listenerlinedda.cpp \
    abstractlinepaintalgorithm.cpp \
    listenerlinebresenham.cpp \
    algorithmround.cpp \
    listenerroundalgorithm.cpp \
    algorithmparabola.cpp \
    listenerparabola.cpp \
    algorithmbspline.cpp \
    listenerbspline.cpp \
    listenerbese.cpp \
    algorithmbese.cpp \
    algorithmlinefilling.cpp \
    listenerlinefilling.cpp

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
    abstractlinelistener.h \
    listenerlinedda.h \
    abstractlinepaintalgorithm.h \
    listenerlinebresenham.h \
    algorithmround.h \
    listenerroundalgorithm.h \
    algorithmparabola.h \
    listenerparabola.h \
    algorithmbspline.h \
    listenerbspline.h \
    listenerbese.h \
    algorithmbese.h \
    algorithmlinefilling.h \
    listenerlinefilling.h

FORMS    += mainwindow.ui \
    debugmodebox.ui
