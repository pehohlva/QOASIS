
QT = core-private
CONFIG += c++11
DEFINES += NDEBUG THREAD_SAFE=1 TEMP_STORE=2 WFLAGS=-Wall
DEFINES += OASI_LIBRARY
MODULE = oasi
CONFIG += release

load(qt_module)

MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build

HEADERS += $$PWD/qtrlocale.h  \
  $$PWD/class/datalanguageprovider.h \
  $$PWD/oasiglobal.h
  
SOURCES += $$PWD/class/qtrlocale.cpp  \
   $$PWD/class/datalanguageprovider.cpp 
   
   
include($$PWD/oasi/third_parti/cld2.pri)x