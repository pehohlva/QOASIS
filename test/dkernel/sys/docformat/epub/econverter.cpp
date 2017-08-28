

#include "../kzip.h"
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

#include "econverter.h"
#include "edocument.h"

using namespace Epub;

Converter::Converter() { /* init class */ }

Converter::~Converter() { }

const QList<EpubToc> Converter::convert(const QString &fileName , const QString dir ) {
  Document oooDocument(fileName,dir);
  if (!oooDocument.open()) {
      QList<EpubToc> dummy;
    return dummy;
  } else {
    return oooDocument.MenuList();
  }
}
