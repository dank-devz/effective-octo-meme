#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T15:54:59
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/mySQL_win32/

TARGET = fast-food-gui
TEMPLATE = app


SOURCES += src/main.cpp\
           src/mainwindow.cpp

HEADERS  += include/mainwindow.h

FORMS    += form/mainwindow.ui

QTPLUGIN += qsqlmysql
