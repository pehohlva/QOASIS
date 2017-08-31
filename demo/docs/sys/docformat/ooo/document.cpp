/***************************************************************************
 *   Copyright (C) 2006 by Tobias Koenig <tokoe@kde.org>                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "document.h"


#include "../kzip.h"

using namespace OOO;

Document::Document( const QString &fileName )
  : mFileName( fileName ), mManifest( 0 ), mAnyEncrypted( false )
{
}

bool Document::open( )
{
  mContent.clear();
  mStyles.clear();

  KZip zip( mFileName );
  if ( !zip.open( QIODevice::ReadOnly ) ) {
    setError( i18n( "Document is not a valid ZIP archive" ) );
    return false;
  }



  if (!entries.contains("manifest.xml")) {
       setError(i18n("Invalid document structure (manifest.xml directory is missing)"));
       return false;
   }

         if (!entries.contains("META-INF")) {
              setError(i18n("Invalid document structure (META-INF directory is missing)"));
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
                          //// ODTDEBUG() << "New name pics len:" << namex << " s:" << xdata.size();
                      } else {
                          //// ODTDEBUG() << "New name xml len:" << namex << " s:" << xdata.size();
                          if (namex == QStringLiteral("styles.xml")) {
                              mStyles = xdata;
                          }
                          if (namex == QStringLiteral("content.xml")) {
                              mContent = xdata;
                          }
                          if (namex == QStringLiteral("META-INF/manifest.xml")) {
                              mMeta = xdata;
                          }
                          if (namex == QStringLiteral("mimetype")) {
                              mMimetype = xdata;
                          }
                          if (namex == QStringLiteral("settings.xml")) {
                              mSetting = xdata;
                          }
                          if (namex == QStringLiteral("manifest.xml")) {
                              QString password;
                              mManifest = new Manifest( mFileName,xdata, password );
                          }



                      }

                  }


          if (QByteArray("application/vnd.oasis.opendocument.text") != mMimetype) {
                      setError(i18n("Invalid MimeType found: %1!").arg(QString::fromUtf8(mMimetype)));
                      return false;
                  }


  zip.close();

  return true;
}

Document::~Document()
{
  delete mManifest;
}

QString Document::lastErrorString() const
{
  return mErrorString;
}

QByteArray Document::content() const
{
  return mContent;
}

QByteArray Document::meta() const
{
  return mMeta;
}

QByteArray Document::styles() const
{
  return mStyles;
}

QMap<QString, QByteArray> Document::images() const
{
  return mImages;
}

bool Document::anyFileEncrypted() const
{
  return mAnyEncrypted;
}

void Document::setError( const QString &error )
{
  mErrorString = error;
}
