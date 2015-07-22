#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T17:47:08
#
#-------------------------------------------------

QT       += core gui network webkit
QT     += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniCell
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    select.cpp \
    resultwidght.cpp \
    genehandler.cpp \
    organismhandler.cpp \
    pathwaywidget.cpp \
    modulewidget.cpp \
    serverconnector.cpp

HEADERS  += mainwidget.h \
    select.h \
    resultwidght.h \
    genehandler.h \
    organismhandler.h \
    pathwaywidget.h \
    modulewidget.h \
    serverconnector.h

FORMS    += mainwidget.ui \
    select.ui \
    resultwidght.ui \
    pathwaywidget.ui \
    modulewidget.ui
