INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT = core core-private
CONFIG += c++11

DEFINES += NOROASI_LIBRARY
load(qt_module)
TARGET = QtOasi

DEFINES += QT_NO_FOREACH

MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build

include($$PWD/qtoasi.pri)

