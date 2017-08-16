#ifndef RTFEXPORT_EXTERN_TO_LIB_762134
#define RTFEXPORT_EXTERN_TO_LIB_762134

#include <QMainWindow>
#include <QXmlQuery>
#include <QSystemTrayIcon>
#include <QAction>
#include <QDomDocument>
#include <QAbstractScrollArea>
#include <QPainter>
#include <QTextDocument>
#include <QDebug>
#include <QTextFrameFormat>
#include <QTextFrame>
#include <QBuffer>

#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE


#ifndef QT_STATIC
#    if defined(QT_BUILD_DOC_OASI_LIB)
#      define DOC_OASI_EXPORT Q_DECL_EXPORT
#    else
#      define DOC_OASI_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define DOC_OASI_EXPORT
#endif


QT_END_NAMESPACE






#endif
