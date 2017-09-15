/*
    Copyright (C)  2017 Piter K. <pehohlva@gmail.com>

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
