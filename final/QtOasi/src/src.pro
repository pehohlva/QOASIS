
QT = core-private
CONFIG += c++11

DEFINES += OASI_LIBRARY
MODULE = QtOasi
load(qt_module)


DEFINES += QT_NO_FOREACH


HEADERS += $$PWD/qtrlocale.h  \
  $$PWD/class/datalanguageprovider.h \
  $$PWD/oasiglobal.h
  
SOURCES += $$PWD/class/qtrlocale.cpp  \
   $$PWD/class/datalanguageprovider.cpp 
   
   
include($$PWD/oasi/third_party/cld2.pri)