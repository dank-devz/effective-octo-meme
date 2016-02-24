#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T15:54:59
#
#-------------------------------------------------

QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TEMPLATE = app
TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
        src \
        app \
        test

app.depends = src
test.depends = src


#SOURCES += app/main.cpp\
#           src/mainwindow.cpp \
#    src/database.cpp \
#    src/restauranttablemodel.cpp \
#    src/menutablemodel.cpp \
##    test/test_database.cpp

#HEADERS  += src/include/mainwindow.h \
#    src/include/database.h \
#    src/include/restauranttablemodel.h \
#    src/include/menutablemodel.h \
##    test/test_database.h



#DISTFILES += \
#    defaults.pri
