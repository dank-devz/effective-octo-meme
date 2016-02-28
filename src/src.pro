include(../defaults.pri)
QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fast-food-app
CONFIG -= testlib
TEMPLATE = lib

SOURCES += mainwindow.cpp \
    database.cpp \
    restauranttablemodel.cpp \
    menutablemodel.cpp

HEADERS  += include/mainwindow.h \
    include/database.h \
    include/restauranttablemodel.h \
    include/menutablemodel.h

FORMS    += form/mainwindow.ui

QTPLUGIN += qsqlmysql
