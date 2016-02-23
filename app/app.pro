include(../defaults.pri)

QT       += core gui sql testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp

LIBS += -L../src -lfast-food-app
