#-------------------------------------------------
#
# Project created by QtCreator 2017-08-26T14:57:04
#
#-------------------------------------------------

QT  += core gui
QT += core xml network gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += printsupport
CONFIG += c++11
CONFIG += console
# nur für mac sonst machte er ein ordner mit dem app
CONFIG -= app_bundle
TEMPLATE = app
TARGET = edit

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
#  mainwindow.h In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp
HEADERS += interface.h
