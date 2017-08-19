#ifndef CORE_ZIP_H
#define CORE_ZIP_H


#include <QMap>
#include <QByteArray>

#include "oo_config.h"
#include "Odf2Debug.h"


/// step by step replace Kzip if faster...
QMap<QString,QByteArray> unzipstream( const QString file );




#endif // CORE_ZIP_H
