QT += core xml network gui
QT += xmlpatterns

CONFIG += c++11
TARGET = sax
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lz
INCLUDEPATH += $$[QT_INSTALL_PREFIX]/src/3rdparty/zlib
INCLUDEPATH += . sys/docformat

MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build


SOURCES += main.cpp \
    sys/docformat/kzip.cpp \
    sys/docformat/QmyDom.cpp \
    sys/docformat/ooo/converter.cpp \
    sys/docformat/ooo/document.cpp \
    sys/docformat/epub/econverter.cpp \
    sys/docformat/epub/edocument.cpp \
   sys/docformat/ooo/formatproperty.cpp \
   sys/docformat/ooo/styleinformation.cpp \
   sys/docformat/ooo/styleparser.cpp  \
    sys/kernel_document.cpp \
    sys/fastrambuffer.cpp \
    sys/core_htmldriver.cpp \
      sys/core_document.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += sys/docformat/kzip.h \
     sys/docformat/QmyDom.h \
     sys/docformat/ooo/converter.h \
     sys/docformat/ooo/document.h \
    sys/docformat/epub/econverter.h \
    sys/docformat/epub/edocument.h \
    sys/docformat/ooo/formatproperty.h \
    sys/docformat/ooo/styleinformation.h \
    sys/docformat/ooo/styleparser.h  \
    sys/kernel_document.h \
    sys/kernel_load.h \
    sys/fastrambuffer.h \
    sys/core_htmldriver.h \
    sys/core_document.h

