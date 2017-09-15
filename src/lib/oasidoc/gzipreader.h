#ifndef GZIPREADER_H
#define GZIPREADER_H



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
#include <qdebug.h>
#include <QtCore/qfile.h>
#include <QtCore/qstring.h>
#include <QBuffer>
#include <QDomDocument>
#include <QIODevice>
#include <QByteArray>
#include <QFile>
#include <QProcess>


class RamStream
{
  public:
  RamStream()
  :d(new QBuffer())
  {
  d->open(QIODevice::ReadWrite);
  start();
  }
  ~RamStream()
  {
   d->close();
  }
  bool clear()
  {
    d->write(QByteArray());
    return d->bytesAvailable() == 0 ? true : false;
  }
  qint64 ramwrite( QByteArray x ) {
    d->write(x);
    start();
    return d->bytesAvailable();
  }

  void start() {
    d->seek(0);
  }

  bool LoadFile( const QString file ) {
    if (clear()) {
     QFile f(file);
        if (f.exists()) {
          if (f.open(QFile::ReadOnly)) {
           d->write(f.readAll());
           f.close();
           start();
           return true;
          }
        }
    }
    return false;
  }
  bool PutOnFile( const QString file ) {
      QFile f(file);
      start();
      if (f.open(QFile::WriteOnly)) {
        uint bi = f.write(d->readAll());
        f.close();
        start();
        return bi > 0 ? true : false;
      }
   return false;
  }
  QDomDocument Dom() { return doc; }
  QBuffer *device() { return d; }
  bool isValid() { return doc.setContent(stream(),false,0,0,0);  }
  QByteArray stream() { return d->data(); }
  QDomDocument doc;
  QBuffer *d;
};





class GZipReaderPrivate;

namespace CZIP {

class QZipReader
{
public:
    QZipReader(const QString &fileName, QIODevice::OpenMode mode = QIODevice::ReadOnly );

    explicit QZipReader(QIODevice *device);
    ~QZipReader();

    bool isReadable() const;
    bool exists() const;

    struct Q_AUTOTEST_EXPORT FileInfo
    {
        FileInfo();
        FileInfo(const FileInfo &other);
        ~FileInfo();
        FileInfo &operator=(const FileInfo &other);
        QString filePath;
        uint isDir : 1;
        uint isFile : 1;
        uint isSymLink : 1;
        QFile::Permissions permissions;
        uint z_crc32;
        qint64 size;
        void *d;
    };

    QList<FileInfo> fileInfoList() const;
    int count() const;

    FileInfo entryInfoAt(int index) const;
    QByteArray fileData(const QString &fileName) const;
    bool extractAll(const QString &destinationDir) const;

    enum Status {
        NoError,
        FileReadError,
        FileOpenError,
        FilePermissionsError,
        FileError
    };

    Status status() const;

    void close();

private:
    GZipReaderPrivate *d;
    Q_DISABLE_COPY(QZipReader)
};

}

#endif // QZIPREADER_H
