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
#include "../kzip.h"
#include "converter.h"
#include "document.h"
#include "formatproperty.h"
#include "styleinformation.h"
#include <QPixmap>
#include <QtCore/QObject>
#include <QtCore/QQueue>
#include <QtCore/QUrl>
#include <QtGui/QTextCharFormat>
#include <QtGui/QTextCursor>
#include <QtGui/QTextDocument>
#include <QtGui/QTextFrame>
#include <QtGui/QTextList>
#include <QtGui/QTextTableCell>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>
#include <QtXml/QXmlSimpleReader>

using namespace OOO;

class Style {
public:
  Style(const QTextBlockFormat &blockFormat, const QTextCharFormat &textFormat);

  QTextBlockFormat blockFormat() const;
  QTextCharFormat textFormat() const;

private:
  QTextBlockFormat mBlockFormat;
  QTextCharFormat mTextFormat;
};

Style::Style(const QTextBlockFormat &blockFormat,
             const QTextCharFormat &textFormat)
    : mBlockFormat(blockFormat), mTextFormat(textFormat) {}

QTextBlockFormat Style::blockFormat() const { return mBlockFormat; }

QTextCharFormat Style::textFormat() const { return mTextFormat; }

Converter::Converter() : mTextDocument(0), mCursor(0), mStyleInformation(0) {}

QTextDocument *Converter::convert(const QString &fileName , QString &html) {
  Document oooDocument(fileName);
  if (!oooDocument.open()) {
    return 0;
  }
  mTextDocument = new QTextDocument;
  mCursor = new QTextCursor(mTextDocument);

  /**
   * Create the dom of the content
   */
  QXmlSimpleReader reader;

  QXmlInputSource source;
  source.setData(oooDocument.content());

  QString errorMsg;
  QDomDocument document;
  if (!document.setContent(&source, &reader, &errorMsg)) {
    if (!oooDocument.anyFileEncrypted())

      delete mCursor;
    return new QTextDocument;
  }

  mStyleInformation = new StyleInformation();

  /**
   * Read the style properties, so the are available when
   * parsing the content.
   */
  StyleParser styleParser(&oooDocument, document, mStyleInformation);
  if (!styleParser.parse()) {
    if (!oooDocument.anyFileEncrypted())
      delete mCursor;
    return new QTextDocument;
  }

  /**
   * Add all images of the document to resource framework
   */
  const QMap<QString, QByteArray> images = oooDocument.images();
  QMapIterator<QString, QByteArray> it(images);
  while (it.hasNext()) {
    it.next();
    mTextDocument->addResource(QTextDocument::ImageResource, QUrl(it.key()),
                               QImage::fromData(it.value()));
  }

  /**
   * Set the correct page size
   */
  const QString masterLayout = mStyleInformation->masterPageName();
  const PageFormatProperty property =
      mStyleInformation->pageProperty(masterLayout);

  int pageWidth = qRound(CM_TO_POINT(18));
  int pageHeight = qRound(CM_TO_POINT(24));

  if (pageWidth == 0)
    pageWidth = 600;
  if (pageHeight == 0)
    pageHeight = 800;

  mTextDocument->setPageSize(QSize(pageWidth, pageHeight));

  QTextFrameFormat frameFormat;
  frameFormat.setMargin(qRound(property.margin()));

  QTextFrame *rootFrame = mTextDocument->rootFrame();
  rootFrame->setFrameFormat(frameFormat);

  /**
   * Parse the content of the document
   */
  const QDomElement documentElement = document.documentElement();

  QDomElement element = documentElement.firstChildElement();
  while (!element.isNull()) {
    if (element.tagName() == QLatin1String("body")) {
      if (!convertBody(element)) {
        if (!oooDocument.anyFileEncrypted())
            delete mCursor;


        return new QTextDocument;
      }
    }

    element = element.nextSiblingElement();
  }

  MetaInformation::List metaInformation = mStyleInformation->metaInformation();
  for (int i = 0; i < metaInformation.count(); ++i) {
    ///// emit addMetaData(metaInformation[i].key(), metaInformation[i].value(), metaInformation[i].title());
  }

  QString HTMLFORCE = mTextDocument->toHtml("utf_8");
  html = handle_html(HTMLFORCE); /*  inline image here.. if need.. */

  delete mCursor;
  delete mStyleInformation;
  mStyleInformation = 0;
  return mTextDocument;
}

bool Converter::convertBody(const QDomElement &element) {
  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if (child.tagName() == QLatin1String("text")) {
      if (!convertText(child))
        return false;
    }

    child = child.nextSiblingElement();
  }

  return true;
}

bool Converter::convertText(const QDomElement &element) {
  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if (child.tagName() == QLatin1String("p")) {
      mCursor->insertBlock();
      if (!convertParagraph(mCursor, child))
        return false;
    } else if (child.tagName() == QLatin1String("h")) {
      mCursor->insertBlock();
      if (!convertHeader(mCursor, child))
        return false;
    } else if (child.tagName() == QLatin1String("list")) {
      if (!convertList(mCursor, child))
        return false;
    } else if (child.tagName() == QLatin1String("table")) {
      if (!convertTable(child))
        return false;
    }

    child = child.nextSiblingElement();
  }

  return true;
}

bool Converter::convertHeader(QTextCursor *cursor, const QDomElement &element) {
  const QString styleName = element.attribute(QStringLiteral("style-name"));
  const StyleFormatProperty property =
      mStyleInformation->styleProperty(styleName);

  QTextBlockFormat blockFormat;
  QTextCharFormat textFormat;
  property.applyBlock(&blockFormat);
  property.applyText(&textFormat);

  cursor->setBlockFormat(blockFormat);

  QDomNode child = element.firstChild();
  while (!child.isNull()) {
    if (child.isElement()) {
      const QDomElement childElement = child.toElement();
      if (childElement.tagName() == QLatin1String("span")) {
        if (!convertSpan(cursor, childElement, textFormat))
          return false;
      }
    } else if (child.isText()) {
      const QDomText childText = child.toText();
      if (!convertTextNode(cursor, childText, textFormat))
        return false;
    }

    child = child.nextSibling();
  }

  return true;
}

bool Converter::convertParagraph(QTextCursor *cursor,
                                 const QDomElement &element,
                                 const QTextBlockFormat &parentFormat,
                                 bool merge) {
  const QString styleName = element.attribute(QStringLiteral("style-name"));
  const StyleFormatProperty property =
      mStyleInformation->styleProperty(styleName);

  QTextBlockFormat blockFormat(parentFormat);
  QTextCharFormat textFormat;
  property.applyBlock(&blockFormat);
  property.applyText(&textFormat);

  if (merge)
    cursor->mergeBlockFormat(blockFormat);
  else
    cursor->setBlockFormat(blockFormat);

  QDomNode child = element.firstChild();
  while (!child.isNull()) {
    if (child.isElement()) {
      const QDomElement childElement = child.toElement();
      if (childElement.tagName() == QLatin1String("span")) {
        if (!convertSpan(cursor, childElement, textFormat))
          return false;
      } else if (childElement.tagName() == QLatin1String("tab")) {
        mCursor->insertText(QStringLiteral("    "));
      } else if (childElement.tagName() == QLatin1String("s")) {
        QString spaces;
        spaces.fill(QLatin1Char(' '),
                    childElement.attribute(QStringLiteral("c")).toInt());
        mCursor->insertText(spaces);
      } else if (childElement.tagName() == QLatin1String("frame")) {
        if (!convertFrame(childElement))
          return false;
      } else if (childElement.tagName() == QLatin1String("a")) {
        if (!convertLink(cursor, childElement, textFormat))
          return false;
      } else if (childElement.tagName() == QLatin1String("annotation")) {
        if (!convertAnnotation(cursor, childElement))
          return false;
      }
    } else if (child.isText()) {
      const QDomText childText = child.toText();
      if (!convertTextNode(cursor, childText, textFormat))
        return false;
    }

    child = child.nextSibling();
  }

  return true;
}

bool Converter::convertTextNode(QTextCursor *cursor, const QDomText &element,
                                const QTextCharFormat &format) {
  cursor->insertText(element.data(), format);

  return true;
}

bool Converter::convertSpan(QTextCursor *cursor, const QDomElement &element,
                            const QTextCharFormat &format) {
  const QString styleName = element.attribute(QStringLiteral("style-name"));
  const StyleFormatProperty property =
      mStyleInformation->styleProperty(styleName);

  QTextCharFormat textFormat(format);
  property.applyText(&textFormat);

  QDomNode child = element.firstChild();
  while (!child.isNull()) {
    if (child.isText()) {
      const QDomText childText = child.toText();
      if (!convertTextNode(cursor, childText, textFormat))
        return false;
    }

    child = child.nextSibling();
  }

  return true;
}

bool Converter::convertList(QTextCursor *cursor, const QDomElement &element) {
  const QString styleName = element.attribute(QStringLiteral("style-name"));
  const ListFormatProperty property =
      mStyleInformation->listProperty(styleName);

  QTextListFormat format;

  if (cursor->currentList()) { // we are in a nested list
    format = cursor->currentList()->format();
    format.setIndent(format.indent() + 1);
  }

  property.apply(&format, 0);

  QTextList *list = cursor->insertList(format);

  QDomElement itemChild = element.firstChildElement();
  int loop = 0;
  while (!itemChild.isNull()) {
    if (itemChild.tagName() == QLatin1String("list-item")) {
      loop++;

      QDomElement childElement = itemChild.firstChildElement();
      while (!childElement.isNull()) {

        QTextBlock prevBlock;

        if (childElement.tagName() == QLatin1String("p")) {
          if (loop > 1)
            cursor->insertBlock();

          prevBlock = cursor->block();

          if (!convertParagraph(cursor, childElement, QTextBlockFormat(), true))
            return false;

        } else if (childElement.tagName() == QLatin1String("list")) {
          prevBlock = cursor->block();

          if (!convertList(cursor, childElement))
            return false;
        }

        if (prevBlock.isValid())
          list->add(prevBlock);

        childElement = childElement.nextSiblingElement();
      }
    }

    itemChild = itemChild.nextSiblingElement();
  }

  return true;
}

static void enqueueNodeList(QQueue<QDomNode> &queue, const QDomNodeList &list) {
  for (int i = 0; i < list.count(); ++i) {
    queue.enqueue(list.at(i));
  }
}

bool Converter::convertTable(const QDomElement &element) {
  /**
   * Find out dimension of the table
   */
  int rowCounter = 0;
  int columnCounter = 0;

  QQueue<QDomNode> nodeQueue;
  enqueueNodeList(nodeQueue, element.childNodes());
  while (!nodeQueue.isEmpty()) {
    QDomElement el = nodeQueue.dequeue().toElement();
    if (el.isNull())
      continue;

    if (el.tagName() == QLatin1String("table-row")) {
      rowCounter++;

      int counter = 0;
      QDomElement columnElement = el.firstChildElement();
      while (!columnElement.isNull()) {
        if (columnElement.tagName() == QLatin1String("table-cell")) {
          counter++;
        }
        columnElement = columnElement.nextSiblingElement();
      }

      columnCounter = qMax(columnCounter, counter);
    } else if (el.tagName() == QLatin1String("table-header-rows")) {
      enqueueNodeList(nodeQueue, el.childNodes());
    }
  }

  /**
   * Create table
   */
  QTextTable *table = mCursor->insertTable(rowCounter, columnCounter);
  mCursor->movePosition(QTextCursor::End);

  /**
   * Fill table
   */
  nodeQueue.clear();
  enqueueNodeList(nodeQueue, element.childNodes());

  QTextTableFormat tableFormat;

  rowCounter = 0;
  while (!nodeQueue.isEmpty()) {
    QDomElement el = nodeQueue.dequeue().toElement();
    if (el.isNull())
      continue;

    if (el.tagName() == QLatin1String("table-row")) {

      int columnCounter = 0;
      QDomElement columnElement = el.firstChildElement();
      while (!columnElement.isNull()) {
        if (columnElement.tagName() == QLatin1String("table-cell")) {
          const StyleFormatProperty property = mStyleInformation->styleProperty(
              columnElement.attribute(QStringLiteral("style-name")));

          QTextBlockFormat format;
          property.applyTableCell(&format);

          QDomElement paragraphElement = columnElement.firstChildElement();
          while (!paragraphElement.isNull()) {
            if (paragraphElement.tagName() == QLatin1String("p")) {
              QTextTableCell cell = table->cellAt(rowCounter, columnCounter);
              // Insert a frame into the cell and work on that, so we can handle
              // different parts of the cell having different block formatting
              QTextCursor cellCursor = cell.lastCursorPosition();
              QTextFrameFormat frameFormat;
              frameFormat.setMargin(1); // TODO: this shouldn't be hard coded
              QTextFrame *frame = cellCursor.insertFrame(frameFormat);
              QTextCursor frameCursor = frame->firstCursorPosition();
              frameCursor.setBlockFormat(format);

              if (!convertParagraph(&frameCursor, paragraphElement, format))
                return false;
            } else if (paragraphElement.tagName() == QLatin1String("list")) {
              QTextTableCell cell = table->cellAt(rowCounter, columnCounter);
              // insert a list into the cell
              QTextCursor cellCursor = cell.lastCursorPosition();
              if (!convertList(&cellCursor, paragraphElement)) {
                return false;
              }
            }

            paragraphElement = paragraphElement.nextSiblingElement();
          }
          columnCounter++;
        }
        columnElement = columnElement.nextSiblingElement();
      }

      rowCounter++;
    } else if (el.tagName() == QLatin1String("table-column")) {
      const StyleFormatProperty property = mStyleInformation->styleProperty(
          el.attribute(QStringLiteral("style-name")));
      const QString tableColumnNumColumnsRepeated = el.attribute(
          QStringLiteral("number-columns-repeated"), QStringLiteral("1"));
      int numColumnsToApplyTo = tableColumnNumColumnsRepeated.toInt();
      for (int i = 0; i < numColumnsToApplyTo; ++i) {
        property.applyTableColumn(&tableFormat);
      }
    }
  }

  table->setFormat(tableFormat);

  return true;
}

bool Converter::convertFrame(const QDomElement &element) {
  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if (child.tagName() == QLatin1String("image")) {
      const QString href = child.attribute(QStringLiteral("href"));
      QTextImageFormat format;
      format.setWidth(
          StyleParser::convertUnit(element.attribute(QStringLiteral("width"))));
      format.setHeight(StyleParser::convertUnit(
          element.attribute(QStringLiteral("height"))));
      format.setName(href);

      mCursor->insertImage(format);
    }

    child = child.nextSiblingElement();
  }

  return true;
}

bool Converter::convertLink(QTextCursor *cursor, const QDomElement &element,
                            const QTextCharFormat &format) {
  int startPosition = cursor->position();

  QDomNode child = element.firstChild();
  while (!child.isNull()) {
    if (child.isElement()) {
      const QDomElement childElement = child.toElement();
      if (childElement.tagName() == QLatin1String("span")) {
        if (!convertSpan(cursor, childElement, format))
          return false;
      }
    } else if (child.isText()) {
      const QDomText childText = child.toText();
      if (!convertTextNode(cursor, childText, format))
        return false;
    }

    child = child.nextSibling();
  }

  int endPosition = cursor->position();
  return true;
}

bool Converter::convertAnnotation(QTextCursor *cursor,
                                  const QDomElement &element) {
  QStringList contents;
  QString creator;
  QDateTime dateTime;

  int position = cursor->position();

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if (child.tagName() == QLatin1String("creator")) {
      creator = child.text();
    } else if (child.tagName() == QLatin1String("date")) {
      dateTime = QDateTime::fromString(child.text(), Qt::ISODate);
    } else if (child.tagName() == QLatin1String("p")) {
      contents.append(child.text());
    }

    child = child.nextSiblingElement();
  }

  /*
  Okular::TextAnnotation *annotation = new Okular::TextAnnotation;
  annotation->setAuthor(creator);
  annotation->setContents(contents.join("\n"));
  annotation->setCreationDate(dateTime);
  annotation->style().setColor(QColor("#ffff00"));
  annotation->style().setOpacity(0.5);
   * */
  return true;
}

Converter::~Converter() {}


QByteArray Converter::image_encode( QImage im )  {
    int w=im.width();
    int h=im.height();
    QByteArray bytes;
    if (w > 700 ) {
        im.scaled(700,700, Qt::KeepAspectRatio);
    }
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    im.save(&buffer, "PNG");
    if (bytes.size() > 0) {
    QByteArray blueimag = bytes.toBase64();
    QByteArray orderpic("data:image/png;base64,");
    orderpic.append(blueimag);
    return orderpic;
    } else {
        return QByteArray("data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==");
    }
}

QString Converter::handle_html( QString & html ) {
    QMapIterator<QString, QByteArray> it(imageLIST);
    while (it.hasNext()) {
                 it.next();
                 ODTDEBUG() << "html replace-> in pic  " << it.key();
                 QByteArray picsbase64 = image_encode(QImage::fromData(it.value()));
                 html.replace(it.key(),picsbase64);
    }
    return html;
}
