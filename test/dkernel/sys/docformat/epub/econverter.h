#ifndef EBUPPYCONVERTER_H
#define EBUPPYCONVERTER_H

#include <QObject>

#include "edocument.h"
#include <QtGui/QTextCharFormat>
#include <QtXml/QDomDocument>

namespace Epub {

class Document;

class Converter {
public:
  Converter();
  ~Converter();
  virtual const QList<EpubToc> convert(const QString &fileName);
private:
};

} // namespace Epub

#endif // CONVERTER_H
