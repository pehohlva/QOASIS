QT       += core
cache()
QT       -= gui
TARGET = hook
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
HEADERS +=
SOURCES += main.cpp
CONFIG += c++11
CONFIG += QMAKE_CXXFLAGS_WARN_ON=-w QMAKE_CFLAGS_WARN_ON=-w
MOC_DIR = o
RCC_DIR = o
OBJECTS_DIR = o
# bug 5.9  static lib not run PRE make a dummy ap to try if go tu run patch
#QMAKE_PRE_LINK += ./prebuild.sh
#QMAKE_POST_LINK += ./prebuild.sh

INCLUDEPATH += ../include
DEPENDPATH += ../include

#BINDIR = ../bin
#target.path = $$BINDIR
#INSTALLS += target