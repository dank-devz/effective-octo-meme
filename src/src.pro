include(../defaults.pri)
QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32 {
  TARGET = ../fast-food-app
}
unix {
  TARGET = fast-food-app
}
CONFIG -= testlib
TEMPLATE = lib

SOURCES += mainwindow.cpp \
    database.cpp \
    restauranttablemodel.cpp \
    menutablemodel.cpp \
    trip.cpp \
    carttablemodel.cpp \
    adminlogin.cpp \
    addrestaurant.cpp \
    location.cpp \
    additemspopup.cpp

HEADERS  += include/mainwindow.h \
            include/database.h \
            include/restauranttablemodel.h \
            include/menutablemodel.h \
            include/trip.h \
            include/location.h \
            include/carttablemodel.h \
            include/adminlogin.h \
    include/addrestaurant.h \
    include/additemspopup.h

FORMS    += form/mainwindow.ui \
            form/adminlogin.ui \
    form/addrestaurant.ui \
    form/additemspopup.ui

QTPLUGIN += qsqlmysql

DISTFILES += \
    ../app/qtdark.qss
