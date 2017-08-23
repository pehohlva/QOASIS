#ifndef KERNEL_LOAD_H
#define KERNEL_LOAD_H

#include <QAbstractTextDocumentLayout>
#include <QBuffer>
#include <QDebug>
#include <QDomDocument>
#include <QMarginsF>
#include <QMimeDatabase>
#include <QMimeType>
#include <QObject>
#include <QPainter>
#include <QTextDocument>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QXmlQuery>
#include <cmath>
#include <typeinfo>
#include <QDir>
#include <QtDebug>
#include <QDebug>
#include <QProcess>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QMap>




static qint64 megalimit = 4 * 1048576; /// as doument

#define POINT_TO_CM(cm) ((cm) / 28.3465058)
#define POINT_TO_MM(mm) ((mm) / 2.83465058)
#define MM_TO_POINT(mm) ((mm)*2.83465058)
#define CM_TO_POINT(cm) ((cm)*28.3465058)

#define volumega(x) ((x) / 1048576)

#define _SLIDERBGCOLOR_ QColor("#ebe9ed")
#define _EDITORBGCOLOR_ QColor("#ebe9ed")
#define _SHADOWCOLOR_ QColor("#D3D3D3")



static inline QString BytesRead(const qint64 size)
{
        if (size < 0)
            return QString();
        if (size < 1024)
            return QObject::tr("%1 B").arg(QString::number(((double) size), 'f', 0));
        if ((size >= 1024) && (size < 1048576))
            return QObject::tr("%1 KB").arg(QString::number(((double) size) / 1024, 'f', 0));
        if ((size >= 1048576) && (size < 1073741824))
            return QObject::tr("%1 MB").arg(QString::number(((double) size) / 1048576, 'f', 2));
        if (size >= 1073741824)
            return QObject::tr("%1 GB").arg(QString::number(((double) size) / 1073741824, 'f', 2));
        return QString();

 }






#endif // KERNEL_LOAD_H
