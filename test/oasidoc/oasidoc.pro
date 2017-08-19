TEMPLATE = app
TARGET = oasidoc
DEPENDPATH += . ../../src/ ../src/xml
INCLUDEPATH += . ./../../src/ ../src/xml
CONFIG += qt release warn_off silence
DESTDIR	+= ./
TEMPLATE = app
CONFIG -= app_bundle

CONFIG += c++11
MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build

QT += gui xml
QT += widgets core
QT += xmlpatterns
QT += printsupport



# set not 1 to build whitout pdfium module ApiSession *sx = ApiSession::instance();
USEPDFPLAY = 1
contains( USEPDFPLAY , [l1] ):QT += pdfium
contains( USEPDFPLAY , [l1] ):message(..ok load pdfium tool... )
contains( USEPDFPLAY , [l1] ):DEFINES += LOADPDFIUMYES=$(USEPDFPLAY)

SOURCES += main.cpp \
    drawdocument.cpp \
    drawapplication.cpp  \
    ../../src/documentsession.cpp

HEADERS += \
    tooldoc.h \
    drawdocument.h \
    drawapplication.h \
    ../../src/documentsession.h

DISTFILES += \
    codetmp.txt \
    main_blob.txt \
    collo.txt \
    index.html \
    save-base.txt \
    noteappunti.txt



CURLONBOARD = $$system(which curl)

UNAME = $$system(uname -s)
contains( UNAME, [lD]arwin ):message( This looks like Linux ($$UNAME) to me )

message(..ok qt version. on  ($$UNAME))
message(..ok qt version. on  ($$DNSPOP))








