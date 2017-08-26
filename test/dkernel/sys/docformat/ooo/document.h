/* 
 * File:   document.h
 * Author: pro
 *
 * Created on 24. Oktober 2013, 11:36
 */

#ifndef DOCUMENT_H
#define	DOCUMENT_H

#include <QtCore/qfile.h>
#include <QtCore/qstring.h>
#include <QtCore/QMap>
#include <QtCore/QDebug>
#include <QtCore/QBuffer>
#include <QtCore/qiodevice.h>
#include <QtCore/qbytearray.h>
#include <QtXml/QDomDocument>
#include <QtGui/QTextDocument>
#include <qstringlist.h>
#include <QtCore/QByteArray>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QImage>
#include <QtCore/QObject>
#include <QtGui/QTextCharFormat>
#include <QtXml/QDomDocument>
#include "document.h"
#include "styleparser.h"
#include "styleinformation.h"
#include "converter.h"
#include "formatproperty.h"
#include "../kzip.h"
#define i18n QObject::tr

#if 0 //// 1 or 0
#define ODTDEBUG qDebug
#define STAGE 1
#else
#define ODTDEBUG if (0) qDebug
#define STAGE 0
#endif



namespace OOO {
    
    
    


    class Document {
    public:
        Document(const QString &fileName);
        ~Document();

        bool open();

        QString lastErrorString() const;

        QByteArray content() const;
        QByteArray meta() const;
        QByteArray styles() const;
        QMap<QString, QByteArray> images() const;

    private:
        void setError(const QString&);

        QString mFileName;
        QByteArray mContent;
        QByteArray mMimetype;
        QByteArray mSetting;
        QByteArray mMeta;
        QByteArray mStyles;
        QMap<QString,QByteArray> mImages;
        //// Manifest *mManifest; mimetype
        QString mErrorString;
    };

}

#endif	/* DOCUMENT_H */

