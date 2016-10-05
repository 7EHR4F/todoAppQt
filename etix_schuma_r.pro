#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T19:43:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = etix_schuma_r
TEMPLATE = app


SOURCES += main.cpp\
    todo.cpp \
    todopool.cpp \
    core.cpp

HEADERS  += \
    todo.h \
    todopool.h \
    core.h

FORMS    += mainwindow.ui

DISTFILES += \
    save.json
