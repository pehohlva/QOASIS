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
#include "document.h"
#include "../kzip.h"
#include <QtCore/QString>

using namespace OOO;

Document::Document(const QString &fileName) : mFileName(fileName) {
  /// password protected file search ManifestEntry::ManifestEntry( const QString
  /// &fileName ) : on okular
}

bool Document::open() {
  mContent.clear();
  mStyles.clear();
  KZipStream *Kzip = new KZipStream(mFileName);
  if (Kzip->canread()) {
    const QStringList entries = Kzip->filelist();
    ODTDEBUG() << "entry list:" << entries;

    if (!entries.contains("META-INF")) {
      setError(
          i18n("Invalid document structure (META-INF directory is missing)"));
      return false;
    }

    if (!entries.contains("content.xml")) {
      setError(i18n("Invalid document structure (content.xml is missing)"));
      return false;
    }

    if (!entries.contains("styles.xml")) {
      /// nokia qt odt export dont write
      setError(i18n("Invalid document structure (styles.xml is missing)"));
      ////  return false;
    }

    if (!entries.contains("meta.xml")) {
      /// nokia qt odt export dont write
      setError(i18n("Invalid document structure (meta.xml is missing)"));
      //// return false;
    }

    QMap<QString, QByteArray> allfiles = Kzip->listData();
    QMapIterator<QString, QByteArray> i(allfiles);
    while (i.hasNext()) {
      i.next();
      QByteArray xdata(i.value());
      QImage pic; /// i.value() /// i.key();
      const QString namex = QString(i.key());
      pic.loadFromData(xdata);
      if (!pic.isNull()) {
        mImages.insert(namex, xdata);
        //// ODTDEBUG() << "New name pics len:" << namex << " s:" <<
        ///xdata.size();
      } else {
        //// ODTDEBUG() << "New name xml len:" << namex << " s:" <<
        ///xdata.size();
        if (namex == "styles.xml") {
          mStyles = xdata;
        }
        if (namex == "content.xml") {
          mContent = xdata;
        }
        if (namex == "META-INF/manifest.xml") {
          mMeta = xdata;
        }
        if (namex == "mimetype") {
          mMimetype = xdata;
        }
        if (namex == "settings.xml") {
          mSetting = xdata;
        }
      }
    }
    if (QByteArray("application/vnd.oasis.opendocument.text") != mMimetype) {
      ///// setError(i18n("Invalid MimeType found:
      ///%1!").arg(QString::fromUtf8(mMimetype)));
      return false;
    }
    //// ODTDEBUG() << "heja :" << content();
    return true;
  }
  return false;
}

void Document::setError(const QString &error) {
  ODTDEBUG() << "New error:" << error;
  mErrorString = error;
}

QString Document::lastErrorString() const { return mErrorString; }

Document::~Document() {
  //// delete mManifest;
}

QByteArray Document::content() const { return mContent; }

QByteArray Document::meta() const { return mMeta; }

QByteArray Document::styles() const { return mStyles; }

QMap<QString, QByteArray> Document::images() const { return mImages; }

bool Document::anyFileEncrypted() const { return mAnyEncrypted; }
