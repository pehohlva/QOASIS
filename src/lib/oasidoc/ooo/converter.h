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

#ifndef CONVERTER_H
#define CONVERTER_H

#include "../kzip.h"
#include "document.h"
#include "converter.h"
#include "styleinformation.h"
#include "styleparser.h"


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

class QDomElement;
class QDomText;

namespace OOO {

class Document;
class Converter : public QObject {

   Q_OBJECT

public:
  Converter();
  ~Converter();
  virtual QTextDocument *convert(const QString &fileName, QString &html);
  QByteArray image_encode( QImage im );
  QString handle_html( QString & html );
  bool exist_image( const QString & name );
signals:
    void setMetaMessage(QString);
   ///// key,value,title.
   //// void addMetaData(QString,QString,QString);

private:
  QTextTableFormat defaultTableStyle();
  void setError(const QString msg, const int vars = 0);

  bool convertBody(const QDomElement &element);
  bool convertText(const QDomElement &element);
  bool convertHeader(QTextCursor *cursor, const QDomElement &element);
  bool convertParagraph(QTextCursor *cursor, const QDomElement &element,
                        const QTextBlockFormat &format = QTextBlockFormat(),
                        bool merge = false);
  bool convertTextNode(QTextCursor *cursor, const QDomText &element,
                       const QTextCharFormat &format);
  bool convertSpan(QTextCursor *cursor, const QDomElement &element,
                   const QTextCharFormat &format);
  bool convertLink(QTextCursor *cursor, const QDomElement &element,
                   const QTextCharFormat &format);
  bool convertList(QTextCursor *cursor, const QDomElement &element);
  bool convertTable(const QDomElement &element);
  bool convertFrame(const QDomElement &element);
  bool convertAnnotation(QTextCursor *cursor, const QDomElement &element);

  QTextDocument *mTextDocument;
  QTextCursor *mCursor;
  QMap<QString, QByteArray> images;

  StyleInformation *mStyleInformation;
};
} // namespace OOO

#endif /* CONVERTER_H */
