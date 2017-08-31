/* 
 * File:   converter.cpp
 * Author: pro
 * Struzzo bello in fare le cose
 * Created on 24. Oktober 2013, 14:26
 */
#include <QtGui/QTextCharFormat>
#include <QtXml/QDomDocument>
#include "document.h"
#include "styleinformation.h"
#include "converter.h"
#include "formatproperty.h"
#include <QtCore/QQueue>
#include <QtCore/QUrl>
#include <QtGui/QTextCursor>
#include <QtGui/QTextDocument>
#include <QtGui/QTextFrame>
#include <QtGui/QTextList>
#include <QtGui/QTextTableCell>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>
#include <QtXml/QXmlSimpleReader>
#include <QtCore/QObject>
#include <QPixmap>
#include "../kzip.h"

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

Style::Style(const QTextBlockFormat &blockFormat, const QTextCharFormat &textFormat)
: mBlockFormat(blockFormat), mTextFormat(textFormat) {
}

QTextBlockFormat Style::blockFormat() const {
    return mBlockFormat;
}

QTextCharFormat Style::textFormat() const {
    return mTextFormat;
}

Converter::Converter()
: mTextDocument(0), mCursor(0),
mStyleInformation(0) {
}

QTextDocument* Converter::convert(const QString &fileName , QString & html , int & tablesum) {
    Document oooDocument(fileName);
    if (!oooDocument.open()) {
        //// emit error(oooDocument.lastErrorString(), -1);
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
        setError(QString("Invalid XML document: %1").arg(errorMsg), -1);
        delete mCursor;
        return mTextDocument;
    }

    mStyleInformation = new StyleInformation();

    if (oooDocument.styles().size() > 0) {
        ///// ODTDEBUG() << "ST:" << oooDocument.styles();
        StyleParser styleParser(&oooDocument, document, mStyleInformation);
        if (!styleParser.parse()) {
            setError(QString("Unable to read style information"), -1);
            delete mCursor;
            return 0;
        }
    }
    if (oooDocument.content().size() > 0) {
        //// ODTDEBUG() << "CO:" << oooDocument.content();
    }

    /**
     * Read the style properties, so the are available when
     * parsing the content.
     */



    /**
     * Add all images of the document to resource framework
     */

    imageLIST = oooDocument.images();
    QMapIterator<QString, QByteArray> it(imageLIST);
    while (it.hasNext()) {
        it.next();
        ODTDEBUG() << " in pic  " << it.key();
        mTextDocument->addResource(QTextDocument::ImageResource, QUrl(it.key()), QImage::fromData(it.value()));
    }


    /**
     * Set the correct page size
     */
    const int DPX = 231; /// im.logicalDpiX(); // 231
    const int DPY = 231; // im.logicalDpiY(); // 231
    const int A4Width = MM_TO_POINT(210); /// A4 210 x297 mm 
    const int A4Height = MM_TO_POINT(297);
    const QString masterLayout = mStyleInformation->masterPageName();
    const PageFormatProperty property = mStyleInformation->pageProperty(masterLayout);
    int pageWidth = qRound(property.width() / 72.0 * DPX);
    if (pageWidth < 1) {
        pageWidth = A4Width;
    }
    int pageHeight = qRound(property.height() / 72.0 * DPY);
    if (pageHeight < 1) {
        pageHeight = A4Height;
    }
    ODTDEBUG() << "pageWidth:" << pageWidth;
    ODTDEBUG() << "pageHeight:" << pageHeight;
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
                /// setError(QString
                setError(i18n("Unable to convert document content"), -1);
                delete mCursor;
                return 0;
            }
        }

        element = element.nextSiblingElement();
    }

    //// handle this now! as normal html.. not 4 qtexedit! browser or so..
    /// e book...
    QString htmlooo = mTextDocument->toHtml("utf_8");
    html = handle_html(htmlooo);

    QRegExp rx("\\b(table)\\b"); // write table in doc... haha..:-)
    int pos = 0;    // where we are
    int count = 0;  // how many count...
    while (pos >= 0) {
        pos = rx.indexIn(htmlooo, pos);
        if (pos >= 0) {
            ++pos;
            const QString resx= htmlooo.mid(pos - 3,110);
            QChar fox(resx.at(0));
            const int chari = (int)fox.unicode();
            if (chari == 60) {
            ++count;
            //// qDebug() << chari << ":close->" << htmlooo.mid(pos - 3,8)  << "-";
            } else if (chari == 10) {
             ++count;
             /// qDebug() << chari << ":open->" << resx  << "-";
            }
        }
    }
    if (!count / 2)  {
        qFatal("Summ of table is not corret!");
    }
    tablesum = count / 2;
    qDebug() << tablesum << " - summoftable";
    ODTDEBUG() << "##################### converter .... " << __LINE__;
    if (STAGE == 1) {
    qDebug() <<  STAGE << ":work" << __FILE__ << ":" << __LINE__;
    }
    return mTextDocument;
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

void Converter::setError(const QString msg, const int vars) {
    /// emit error here 
    ODTDEBUG() << msg << " ERRORPLAY!!!!! level:" << vars;
}

bool Converter::convertBody(const QDomElement &element) {

    ODTDEBUG() << "Converter::" << __FUNCTION__ << " .... " << __LINE__;

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
    ODTDEBUG() << "Converter::" << __FUNCTION__ << " .... " << __LINE__;

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
    ODTDEBUG() << "Converter::" << __FUNCTION__ << " .... " << __LINE__;

    const QString styleName = element.attribute("style-name");
    const StyleFormatProperty property = mStyleInformation->styleProperty(styleName);

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

    //// emit addTitle(element.attribute("outline-level", 0).toInt(), element.text(), cursor->block());

    return true;
}

bool Converter::convertParagraph(QTextCursor *cursor, const QDomElement &element, const QTextBlockFormat &parentFormat, bool merge) {
    //// ODTDEBUG() << "Converter::" << __FUNCTION__ << " .... " << __LINE__;
    const QString styleName = element.attribute("style-name");
    const StyleFormatProperty property = mStyleInformation->styleProperty(styleName);

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
                mCursor->insertText("    ");
            } else if (childElement.tagName() == QLatin1String("s")) {
                QString spaces;
                spaces.fill(' ', childElement.attribute("c").toInt());
                mCursor->insertText(spaces);
            } else if (childElement.tagName() == QLatin1String("frame")) {
                const int xpos = cursor->position();
                mCursor->setPosition(xpos, QTextCursor::MoveAnchor);
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

bool Converter::convertTextNode(QTextCursor *cursor, const QDomText &element, const QTextCharFormat &format) {
    //// ODTDEBUG() << "Converter::" << __FUNCTION__ << " .... " << __LINE__;
    cursor->insertText(element.data(), format);

    return true;
}

bool Converter::convertSpan(QTextCursor *cursor, const QDomElement &element, const QTextCharFormat &format) {
    ///// ODTDEBUG() << "Converter::" << __FUNCTION__ << " .... " << __LINE__;

    const QString styleName = element.attribute("style-name");
    const StyleFormatProperty property = mStyleInformation->styleProperty(styleName);

    QTextCharFormat textFormat(format);
    property.applyText(&textFormat);

    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        //// search <text:s/> 
        if (child.isText()) {
            const QDomText childText = child.toText();
            if (!convertTextNode(cursor, childText, textFormat))
                return false;
        } else if (child.isElement()) {
            const QDomElement childElement = child.toElement();
            if (childElement.tagName() == QLatin1String("tab")) {
                cursor->insertText("    ");
            } else if (childElement.tagName() == QLatin1String("s")) {
                QString spaces;
                spaces.fill(' ', childElement.attribute("c").toInt());
                cursor->insertText(spaces);
            } else if (childElement.tagName() == QLatin1String("frame")) {
                const int xpos = cursor->position();
                mCursor->setPosition(xpos, QTextCursor::MoveAnchor);
                if (!convertFrame(childElement))
                    return false;
            }

        }
        child = child.nextSibling();
    }

    return true;
}

bool Converter::convertList(QTextCursor *cursor, const QDomElement &element) {

    //// ODTDEBUG() << "Converter::" << __FUNCTION__ << " .... " << __LINE__;

    const QString styleName = element.attribute("style-name");
    const ListFormatProperty property = mStyleInformation->listProperty(styleName);

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
    ODTDEBUG() << "Converter::" << __FUNCTION__ << " .... " << __LINE__;

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
    //// QBrush(const QColor &color, Qt::BrushStyle bs=Qt::SolidPattern);
    QTextTableFormat table_oasi_c = defaultTableStyle();
    QTextTable *table = mCursor->insertTable(rowCounter, columnCounter , table_oasi_c );
    mCursor->movePosition(QTextCursor::End);

    /**
     * Fill table
     */
    nodeQueue.clear();
    enqueueNodeList(nodeQueue, element.childNodes());



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
                    const StyleFormatProperty property = mStyleInformation->styleProperty(columnElement.attribute("style-name"));

                     QTextBlockFormat tcellfor; /// defaultTableStyle();
                     tcellfor.setRightMargin(2);
                     tcellfor.setLeftMargin(2);
                     tcellfor.setTopMargin(2);
                     tcellfor.setBottomMargin(2);
                     property.applyTableCell(&tcellfor);

                    QDomElement paragraphElement = columnElement.firstChildElement();
                    while (!paragraphElement.isNull()) {
                        if (paragraphElement.tagName() == QLatin1String("p")) {
                            QTextTableCell cell = table->cellAt(rowCounter, columnCounter);
                            // Insert a frame into the cell and work on that, so we can handle
                            // different parts of the cell having different block formatting
                            QTextCursor cellCursor = cell.lastCursorPosition();
                            QTextFrameFormat frameFormat;
                            frameFormat.setMargin(0); // TODO: this shouldn't be hard coded
                            QTextFrame *frame = cellCursor.insertFrame(frameFormat);
                            QTextCursor frameCursor = frame->firstCursorPosition();
                            frameCursor.setBlockFormat(tcellfor);

                            if (!convertParagraph(&frameCursor, paragraphElement, tcellfor))
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
            const StyleFormatProperty property = mStyleInformation->styleProperty(el.attribute("style-name"));
            const QString tableColumnNumColumnsRepeated = el.attribute("number-columns-repeated", "1");
            int numColumnsToApplyTo = tableColumnNumColumnsRepeated.toInt();
            for (int i = 0; i < numColumnsToApplyTo; ++i) {
                property.applyTableColumn(&table_oasi_c);
            }
        }
    }

    table->setFormat(table_oasi_c);

    return true;
}


/*   fake long table !!! debug or not! */
QTextTableFormat Converter::defaultTableStyle() {
    QTextTableFormat tfo;
    QTextLength valwi(QTextLength::PercentageLength,100);
    tfo.setWidth(valwi);
    tfo.setBorder(0);
    if (STAGE == 1) {
        qWarning("SET STAGE=0 on document.h to see normal table!!");
        tfo.setBackground(QBrush(QColor(Qt::red),Qt::SolidPattern));
    } else {
        tfo.setBackground(QBrush(QColor(Qt::white),Qt::SolidPattern));
    }
    return tfo;
}




bool Converter::convertFrame(const QDomElement &element) {

    ODTDEBUG() << "Converter::" << __FUNCTION__ << " .... " << __LINE__;
    QDomElement child = element.firstChildElement();
    QDomElement suchild = element.lastChildElement("title");
    /// svg:title alt && title 
    while (!child.isNull()) {
        if (child.tagName() == QLatin1String("image")) {
            const QString href = child.attribute("href");
            const QString xname = element.attribute("name");
            QString alttitle = QString("Name:%1 - Ref:%2").arg(xname).arg(href);
            if (suchild.tagName() == QLatin1String("title")) {
                alttitle.append(QString(" - Title:%1").arg(suchild.text()));
            }
            QTextImageFormat format;
            format.setToolTip(alttitle);
            format.setWidth(StyleParser::convertUnit(element.attribute("width")));
            format.setHeight(StyleParser::convertUnit(element.attribute("height")));
            format.setName(href);
            mCursor->insertImage(format);
        }

        child = child.nextSiblingElement();
    }

    return true;
}

bool Converter::convertLink(QTextCursor *cursor, const QDomElement &element, const QTextCharFormat &format) {
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
    USETODONEXT(endPosition);
    USETODONEXT(startPosition);
    ////Okular::Action *action = new Okular::BrowseAction(element.attribute("href"));
    //// emit addAction(action, startPosition, endPosition);

    return true;
}

bool Converter::convertAnnotation(QTextCursor *cursor, const QDomElement &element) {
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

    USETODONEXT(position);

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

Converter::~Converter() {
}






