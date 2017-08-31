#include "fastrambuffer.h"
#include "kernel_load.h"

#include <QtDebug>












Fastrambuffer::Fastrambuffer() {
  x = new QBuffer();
  x->open(QIODevice::ReadWrite);
}

bool Fastrambuffer::load_file(const QString file) {
  QMimeDatabase db;
  mime = db.mimeTypeForFile(file).name();
  qDebug()  << mime << " mime incomming ram -----   " << __LINE__;
  QFileInfo fix(file);
  absolutepathfromfile = fix.absolutePath();
  filename = fix.fileName();
  FcurrentSize = fix.size();
  if (fix.completeSuffix() == QStringLiteral("rtfd")) {
      QByteArray xdax(absolutepathfromfile.toUtf8());
      this->device()->write(xdax);
      x->seek(0);
      return true;
  }
  qDebug()  << mime << " size:" <<  BytesRead(FcurrentSize) <<  "-limit" << BytesRead(megalimit) << ",     mime incomming ram -----   " << __LINE__;
  if (FcurrentSize > megalimit) {
      return false;
  }
  qDebug()  << mime << " mime incomming ram -----   " << __LINE__;
  if (mime.contains(".oasis.") ) {
      QByteArray signature(absolutepathfromfile.toUtf8());
      signature.prepend(QByteArray("opendocument,calligra,okular,openoffice"));
      this->device()->write(signature);
      x->seek(0);
      return true;
  }
  qDebug()  << mime << " mime incomming ram -----   " << __LINE__;

  QFile f(file);
  if (f.exists()) {
    if (f.open(QFile::ReadOnly)) {
      x->write(f.readAll());
      x->seek(0);
      ScurrentSize = x->bytesAvailable();
      return true;
    }
  }

  return false;
}

bool Fastrambuffer::PutOnFile(const QString file) {
       /// mkdir if not exist
      if (file.contains("/", Qt::CaseInsensitive)) {
        QString lastdir = file.left(file.lastIndexOf("/")) + "/";
        QDir dira(lastdir);
        if (dira.mkpath(lastdir)) {
        } else {
          return false;
        }

        QFile f(file);
        x->seek(0);
        if (f.open(QFile::WriteOnly)) {
          uint bi = f.write(stream());
          f.close();
          return bi > 0 ? true : false;
        }
        return false;
      }
}

  bool Fastrambuffer::clear() {
    x->close();
    x->seek(0);
    x->write(QByteArray());
    return x->bytesAvailable() == 0 ? true : false;
  }

  QString Fastrambuffer::data() {

      return QString::fromUtf8(stream());
  }

  QIODevice *Fastrambuffer::device() {
      return x;
  }

  QByteArray Fastrambuffer::stream() {
      return x->data();
  }

  QString Fastrambuffer::strip_tag(QString txt) {

    if (txt.size() < 3) {
      return QString();
    }
    QString tmp;
    for (int i = 0; i < txt.size(); i++) {
      QChar vox(txt.at(i));
      int letter = vox.unicode(); /// <60 62>
      if (letter == 60 || letter == 62 || letter > 250) {
        tmp += QString("&#") + QString::number(letter) + QString(";");
      } else {
        tmp.append(QString(vox));
      }
    }
    return tmp;
  }

  QString Fastrambuffer::tohtmlsimulate() {
    QStringList lines =
        strip_tag(data()).split(QRegExp("[\n]"), QString::KeepEmptyParts);
    QString str = lines.join("<br/>");
    str.prepend(QString("<p>"));
    str.append(QString("<p/>"));
    return str;
  }
