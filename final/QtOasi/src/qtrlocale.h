#ifndef QTRLOCALE_H
#define QTRLOCALE_H
#include <QObject>
#include <QLocale>
#include <QtCore/qobject.h>
#include <QtCore/qvariant.h>
#include <QtCore/qhash.h>
#include "oasiglobal.h"

OASI_EXPORT QString html_encode(const QString &string);
OASI_EXPORT bool file_put_contents(const QString fullFileName, QString &xml , int modus = 0 ); /// 0 normal 1 append
OASI_EXPORT QString toXexsumm( QString put );
/// return the qchar script max from text...
OASI_EXPORT int  hit_Script_found( QString text );
/// avaiable script in qchar
static int sumscritpsLang =131;

QT_BEGIN_NAMESPACE

class DataLocaleProvider;
class OASI_EXPORT QTrlocale : public QObject
{
  Q_OBJECT

public:
  explicit QTrlocale(const int modus = 1 , QObject *parent = nullptr);
  /*  from class QLocale get all info.  */
  QLocale getQlocaleFromText( const QString txt );
  Q_INVOKABLE bool isLatinLang( QString txt );
  Q_INVOKABLE QString CodingCld( QString txt );
  Q_INVOKABLE QString CodingChar( QString txt );
  void ReadFile( const QString file );
  QString getnameScriptQChar(const ushort unicode) const;
  QSet<QString> qlocaleList();
  void wr_47854g76b64();
private:
  QHash<QByteArray, QChar::Script> scriptMap;
  void initScriptMap();
  int d;
  DataLocaleProvider *data;
};

QT_END_NAMESPACE

#endif




