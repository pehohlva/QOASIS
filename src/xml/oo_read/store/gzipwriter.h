#ifndef GZIPWRITER_H
#define GZIPWRITER_H


//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QLibrary class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qstring.h>
#include <QtCore/qfile.h>

class GZipWriterPrivate;


namespace CZIP {




class  QZipWriter
{
public:
    QZipWriter(const QString &fileName, QIODevice::OpenMode mode = (QIODevice::WriteOnly | QIODevice::Truncate) );

    explicit QZipWriter(QIODevice *device);

    bool isWritable() const;
    bool exists() const;

    enum Status {
        NoError,
        FileWriteError,
        FileOpenError,
        FilePermissionsError,
        FileError
    };

    Status status() const;

    enum CompressionPolicy {
        AlwaysCompress,
        NeverCompress,
        AutoCompress
    };

    void setCompressionPolicy(CompressionPolicy policy);
    CompressionPolicy compressionPolicy() const;

    void setCreationPermissions(QFile::Permissions permissions);
    QFile::Permissions creationPermissions() const;

    void addFile(const QString &fileName, const QByteArray &data);

    void addFile(const QString &fileName, QIODevice *device);

    void addDirectory(const QString &dirName);

    void addSymLink(const QString &fileName, const QString &destination);

    void close();
private:
    GZipWriterPrivate *d;
    Q_DISABLE_COPY(QZipWriter)
};

}


#endif // QZIPWRITER_H
