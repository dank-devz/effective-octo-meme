#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T15:54:59
#
#-------------------------------------------------

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
        src \
#        src/include \
        app \
        test

app.depends = src
test.depends = src




#DISTFILES += \
#    defaults.pri
