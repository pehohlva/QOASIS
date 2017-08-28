QT += core xml network gui
QT += concurrent pdfium
QT += xmlpatterns
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11
TARGET = EpubRead
#CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lz
INCLUDEPATH += $$[QT_INSTALL_PREFIX]/src/3rdparty/zlib
INCLUDEPATH += . sys/docformat

MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build


SOURCES += main.cpp \
    core_application.cpp \
    core_mainwindow.cpp \
    epubview.cpp

# The following define makes your compiler emit warnings if you use
# any feature of dokument schliessen Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS



# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    core_application.h \
    core_mainwindow.h \
    epubview.h

RESOURCES += \
    app_resource.qrc



!include(file_format.pri) {
message( "file_format.pri not found" )
}