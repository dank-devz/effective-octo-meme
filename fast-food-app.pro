#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T15:54:59
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = ../build-fast-food-app
TEMPLATE = app


SOURCES += src/main.cpp\
           src/mainwindow.cpp \
    src/database.cpp \
    src/restauranttablemodel.cpp

HEADERS  += include/mainwindow.h \
    include/database.h \
    include/restauranttablemodel.h

FORMS    += form/mainwindow.ui

QTPLUGIN += qsqlmysql
