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
#ifndef EBUPPYCONVERTER_H
#define EBUPPYCONVERTER_H

#include <QObject>

#include "edocument.h"
#include <QtGui/QTextCharFormat>
#include <QtXml/QDomDocument>

namespace Epub {

class Document;

class Converter : public QObject
{

Q_OBJECT

public:
  Converter();
  ~Converter();
   virtual const QList<EpubToc> convert(const QString &fileName, const QString dir );
private:
};

} // namespace Epub


#endif // CONVERTER_H
