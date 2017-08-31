/***************************************************************************
 *   Copyright (C) 2006 by Tobias Koenig <tokoe@kde.org>                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

/* Setting from PH pehohlva@gmail.com 2017 to enable build inide QT5.9.1 check
 * ok. */
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../kzip.h"
#include "converter.h"
#include "document.h"
#include "formatproperty.h"
#include "styleinformation.h"
#include "styleparser.h"
#include <QImage>
#include <QtCore/QBuffer>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/qbytearray.h>
#include <QtCore/qfile.h>
#include <QtCore/qiodevice.h>
#include <QtCore/qstring.h>
#include <QtGui/QTextCharFormat>
#include <QtGui/QTextDocument>
#include <QtXml/QDomDocument>
#include <qstringlist.h>

#include <QTextTableFormat>
#include <QTextCursor>
#include <QTextTableFormat>
#include <QTextCharFormat>
#include <QTextTableFormat>
#include <QDomElement>
#include <QTextBlockFormat>



#define i18n QObject::tr

#include "manifest.h"

#if 1 //// 1 or 0
#define ODTDEBUG qDebug
#define STAGE 1
#else
#define ODTDEBUG                                                               \
  if (0)                                                                       \
  qDebug
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
  bool anyFileEncrypted() const;

private:
  void setError(const QString &);

  QString mFileName;
  QByteArray mContent;
  QByteArray mMeta;
  QByteArray mStyles;
  QMap<QString, QByteArray> mImages;
  Manifest *mManifest;
  QString mMimetype;
  QString mSetting;
  QString mErrorString;
  bool mAnyEncrypted;
};

/*   QString mFileName;
QByteArray mContent;
QByteArray mMeta;
QByteArray mStyles;
QMap<QString, QByteArray> mImages;
Manifest *mManifest;
QString mErrorString;
bool mAnyEncrypted; */

} // namespace OOO

#endif /* DOCUMENT_H */
