include(../defaults.pri)
QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fast-food-app
CONFIG -= testlib
TEMPLATE = lib

SOURCES += mainwindow.cpp \
    database.cpp \
    restauranttablemodel.cpp \
    menutablemodel.cpp \
    carttablemodel.cpp \
    adminlogin.cpp

HEADERS  += include/mainwindow.h \
    include/database.h \
    include/restauranttablemodel.h \
    include/menutablemodel.h \
    include/trip.h \
    include/carttablemodel.h \
    include/adminlogin.h

FORMS    += form/mainwindow.ui \
                form/adminlogin.ui


QTPLUGIN += qsqlmysql
