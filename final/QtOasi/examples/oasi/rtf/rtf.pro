TEMPLATE = app
QT       += core
QT       -= gui
TARGET = hook
CONFIG   += console
CONFIG   -= app_bundle

HEADERS +=
SOURCES += main.cpp
CONFIG += c++11
MOC_DIR = o
RCC_DIR = o
OBJECTS_DIR = o


include(../../src/oasi/qtoasi.pri)

target.path = $$[QT_INSTALL_EXAMPLES]/oasi/rtf
INSTALLS += target
