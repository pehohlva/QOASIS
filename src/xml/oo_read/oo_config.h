#ifndef OO_CONFIG_H
#define OO_CONFIG_H


#include <stdio.h>
#include <QTextStream>
#include <QCoreApplication>
#include <qbytearray.h>
#include <qstring.h>
#include <qchar.h>
#include <iostream>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QScrollBar>
#include <QXmlQuery>
#include <QAbstractScrollArea>
#include <QSystemTrayIcon>
#include <QAbstractScrollArea>
#include <QSystemTrayIcon>
#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QScrollBar>
#include <QDomDocument>
#include <QAbstractScrollArea>
#include <QPainter>
#include <QBuffer>
#include <QTextDocument>
#include <QBuffer>
#include <QDebug>
#include <QTextFrameFormat>
#include <QTextFrame>
#include <QBuffer>
#include <QAbstractTextDocumentLayout>
#include <QMarginsF>
#include <QGraphicsDropShadowEffect>
#include <QPlainTextDocumentLayout>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsEffect>
#include <QPlainTextDocumentLayout>
#include <QCoreApplication>
#include <QApplication>
#include <QMainWindow>
#include <QTabletEvent>
#include <QNativeGestureEvent>
#include <QInputEvent>
#include <QNativeGestureEvent>
#include <QMimeDatabase>
#include <QMimeType>
#include <QIODevice>

#include <QtCore/QAtomicPointer>
#include <sys/types.h>
#include <QtCore/QObject>



#include <QtCore/qglobal.h>

#if defined(KOSTORE_EXPORT)
#  define KOSTORE_EXPORT Q_DECL_EXPORT
#else
#  define KOSTORE_EXPORT Q_DECL_IMPORT
#endif



static inline QString i18n( const QString txt ) {
    QString translate = txt;
    translate.prepend("Transalte i18n:");
    qFatal("Translate Message in lib...");
    return translate;
}












#endif // OO_CONFIG_H
