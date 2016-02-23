include(../defaults.pri)

QT       += core gui sql testlib

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += test_database.cpp

HEADERS += test_database.h

LIBS += -L../src -lfast-food-app

