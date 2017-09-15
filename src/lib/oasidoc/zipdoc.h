#ifndef ZIPDOC_H
#define ZIPDOC_H
#include <QObject>
#include "gzipreader.h"
#include "gzipwriter.h"
#include <QCoreApplication>
#include <QObject>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QDir>
#include <QDate>
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QDirIterator>
#include <QStorageInfo>
#include <QCryptographicHash>
#include <QFileInfo>
#include <QBuffer>


/*  open document odt docx or other zip format   */
QMap<QString,QByteArray> unzipstream( const QString file );

/*  usage
QString txtlog;
QMap<QString,QByteArray>  filist = unzipstream("giallo.odt");
QMapIterator<QString,QByteArray> i(filist);
    while (i.hasNext()) {
        i.next();
        qDebug() << "### name---------- " << i.key();
        txtlog.append(i.key());
    }
QByteArray base = filist["content.xml"];
if (base.size() > 0) {
   txtlog.append(QString(base));
}
*/


#endif // ZIPDOC_H
