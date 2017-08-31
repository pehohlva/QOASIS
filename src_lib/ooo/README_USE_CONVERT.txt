
# OASIS Open Document Format for Office Applications

Use of this dir:
Here i all to convert odt document to;
#include "converter.h" /// only this && its self have #include "../kzip.h" to open this file
QString html;
OOO::Converter *odt = new OOO::Converter(); // .odt odf or so...  OpenDocument Format.
QTextDocument *qtdoc = odt->convert(HandleNow,html);

if you like qtdoc go to QTextEdit or other... image i inside QTextDocument table ecc.
other way QString html; have now all html + image inline as base64

QByteArray("data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==");
After file i portable to use in other app...

and browser or other also QTextEdit can display limit is 6-7 MB and all is overloaded...



