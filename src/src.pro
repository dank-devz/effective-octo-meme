include(../defaults.pri)
QT       += core gui sql testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fast-food-app
#CONFIG -= qt
TEMPLATE = lib

SOURCES += mainwindow.cpp \
    database.cpp \
    restauranttablemodel.cpp \
    menutablemodel.cpp \
#    test/test_database.cpp

HEADERS  += include/mainwindow.h \
    include/database.h \
    include/restauranttablemodel.h \
    include/menutablemodel.h \
#    test/test_database.h

FORMS    += form/mainwindow.ui

QTPLUGIN += qsqlmysql
