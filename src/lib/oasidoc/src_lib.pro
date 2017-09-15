

TEMPLATE = lib
TARGET = oasidoc

QT   += core
CONFIG += c++11

CONFIG += warn_on staticlib silence
#CONFIG += staticlib warn_off
CONFIG += release


CONFIG += staticlib

!include( docformat/odt.pri ) {
message( "odt.pri not found" )
}

!include( docformat/rtfsrc.pri ) {
message( "rtfsrc.pri not found" )
}

!include( zlib.pri ) {
message( "zlib.pri not found" )
}


DESTDIR	+= ../

MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build


qtHaveModule(xml) {
DEFINES += _HAVEXMLPARSE_
QT += xml
message("Oh you have intall xml, confirm/bundle.")
}
qtHaveModule(network) {
QT += network
DEFINES += _HAVENETWORK_
message("Oh you have intall network, confirm/bundle.")
}