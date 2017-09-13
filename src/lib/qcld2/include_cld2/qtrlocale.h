#ifndef QTRLOCALE_H
#define QTRLOCALE_H

#include "datalanguageprovider.h"
#include <QBuffer>
#include <QChar>
#include <QCryptographicHash>
#include <QDate>
#include <QDir>
#include <QElapsedTimer>
#include <QLocale>
#include <QMimeDatabase>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTextCodec>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <qbytearray.h>
#include <qchar.h>
#include <qdebug.h>
#include <qfile.h>
#include <qhash.h>
#include <qlist.h>
#include <qstring.h>
#include <qvector.h>
#include <stdio.h>

QString html_encode(const QString &string);
bool file_put_contents(const QString fullFileName, QString &xml,
                       int modus = 0); /// 0 normal 1 append
QString toXexsumm(QString put);
/// return the qchar script max from text...
int hit_Script_found(QString text);
/// avaiable script in qchar
static int sumscritpsLang = 131;

class DataLocaleProvider;
class QTrlocale  {


public:
  explicit QTrlocale(const int modus = 1 );
  /// from class QLocale get all info...
  QLocale getQlocaleFromText(const QString txt);
  bool isLatinLang(QString txt);
  QString CodingCld(QString txt);
  QString CodingChar(QString txt);
  void ReadFile(const QString file);
  QString getnameScriptQChar(const ushort unicode) const;
  QSet<QString> qlocaleList();
  void wr_47854g76b64(); /// generator.. table

signals:

public slots:

private:
  QHash<QByteArray, QChar::Script> scriptMap;
  void initScriptMap();
  int d;
  DataLocaleProvider *data;
};

#endif // QTRLOCALE_H
