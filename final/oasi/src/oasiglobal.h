#ifndef QCLD2GLOBAL_H
#define QCLD2GLOBAL_H


#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_OASI_LIB)
#      define OASI_EXPORT Q_DECL_EXPORT
#    else
#      define OASI_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define OASI_EXPORT
#endif

QT_END_NAMESPACE


#endif // QCLD2GLOBAL_H
