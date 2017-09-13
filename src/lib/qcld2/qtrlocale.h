#ifndef QTRLOCALE_H
#define QTRLOCALE_H

#include <QObject>
#include <QObject>
#include <QString>
#include <QBuffer>
#include <QMimeDatabase>
#include <QTextCodec>
#include <QDir>
#include <QLocale>
#include <QTextStream>
#include <QLocale>
#include <QDate>
#include <QChar>
#include <qlist.h>
#include <qhash.h>
#include <qfile.h>
#include <qbytearray.h>
#include <qstring.h>
#include <qchar.h>
#include <qvector.h>
#include <qdebug.h>
#include <QStringList>
#include <QElapsedTimer>
#include <QCryptographicHash>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include "datalanguageprovider.h"

QString html_encode(const QString &string);
bool file_put_contents(const QString fullFileName, QString &xml , int modus = 0 ); /// 0 normal 1 append
QString toXexsumm( QString put );
/// return the qchar script max from text...
int  hit_Script_found( QString text );
/// avaiable script in qchar
static int sumscritpsLang =131;

class DataLocaleProvider;

class QTrlocale : public QObject
{

  Q_OBJECT

public:
  explicit QTrlocale(const int modus = 1 , QObject *parent = nullptr);
  /// from class QLocale get all info...
  QLocale getQlocaleFromText( const QString txt );
  bool isLatinLang( QString txt );
  QString CodingCld( QString txt );
  QString CodingChar( QString txt );
  void ReadFile( const QString file );
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
