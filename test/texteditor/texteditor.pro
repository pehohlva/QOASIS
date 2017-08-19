TEMPLATE = app
TARGET = texteditor
QT += quick quickcontrols2
qtHaveModule(widgets): QT += widgets

cross_compile: DEFINES += QT_EXTRA_FILE_SELECTOR=\\\"touch\\\"


CONFIG += c++11
MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build

CONFIG += qt release warn_off silence
DESTDIR	+= ./


HEADERS += \
    documenthandler.h

SOURCES += \
    texteditor.cpp \
    documenthandler.cpp

OTHER_FILES += \
    qml/*.qml

RESOURCES += \
    texteditor.qrc

