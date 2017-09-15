

Use of this dir:
Here i all to convert odt document to;
#include "converter.h" /// only this && its self have #include "../kzip.h" to open this file
QString html;
OOO::Converter *odt = new OOO::Converter(); // .odt odf or so...  OpenDocument Format.
QTextDocument *qtdoc = odt->convert(HandleNow,html);

if you like qtdoc go to QTextEdit or other... image i inside QTextDocument table ecc.
other way QString html; have now all html + image inline as base64

QByteArray("data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==");

and browser or other also QTextEdit can display limit is 6-7 MB and all is overloaded...



QFile f( fullFileName );
       f.open(  QIODevice::WriteOnly );
            f.write()
            f.close();

            sw << xml;
            f.close();
             if (f.bytesAvailable() > 0) {
                return true;
              } else {
                return false;
              }



QDomElement ee = child.toElement();
if (!ee.isNull() && ee.tagName() == QLatin1String("frame") ) {
   ODTDEBUG() << "XXXXXXXXXXXXXXX  tag el:" << ee.tagName();
   if (!convertFrame(ee)) {
     return false;
   }
} else


ODTDEBUG() << "XXXXXXXXXXXXXXX  init:" << __FUNCTION__;
bool nameA = false;
bool nameB = false;
QString namesec;
if (element.tagName() == QLatin1String("frame") ) {
     namesec = element.attribute(QStringLiteral("name"));
     nameB = exist_image(namesec);
}
