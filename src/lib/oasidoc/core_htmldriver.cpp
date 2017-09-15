#include "core_htmldriver.h"

HtmlDriver::HtmlDriver() {
  cacheop = -1;
  clean_cache();
}

HtmlDriver::~HtmlDriver() {
  qDebug() << "### clean " << __FUNCTION__ << CACHEBUFFERDISKTMP;
  clean_cache();
}

void HtmlDriver::clean_cache() {
  DownDir_RM(CACHEBUFFERDISKTMP);
  QDir dirsystem;
  if (dirsystem.mkpath(CACHEBUFFERDISKTMP)) {
    cacheop = 1;
  }
  qDebug() << "### clean " << __FUNCTION__ << CACHEBUFFERDISKTMP;
}

/*  Readutf8File file_put_utf8contents */
/* read the contenet of a local file as qstring */
QString readfile(const QString fullFileName) {
  QString inside = "";
  QFile file(fullFileName);
  if (file.exists()) {
    if (file.open(QFile::ReadOnly | QFile::Text)) {
      inside = QString(file.readAll().constData());
      file.close();
    }
  }
  return inside;
}

/* remove dir recursive */
void DownDir_RM(const QString d) {
  QDir dir(d);
  QDir enddir(d);
  if (dir.exists()) {
    const QFileInfoList list = dir.entryInfoList();
    QFileInfo fi;
    for (int l = 0; l < list.size(); l++) {
      fi = list.at(l);
      if (fi.isDir() && fi.fileName() != "." && fi.fileName() != "..")
        DownDir_RM(fi.absoluteFilePath());
      else if (fi.isFile()) {
        unlink(fi.absoluteFilePath());
      }
    }
    dir.rmdir(d);
  }

  //// return enddir.exists();
}

/* remove a file */
bool unlink(const QString fullFileName) {
  if (fullFileName.size() > 0) {
    QFile f(fullFileName);
    if (f.exists(fullFileName)) {
      if (f.remove()) {
        return true;
      }
    }
  }
  return false;
}

/* check if a int or float nummer */
bool is_numeric(QString incomming) {
  incomming.replace(QString(" "), QString("")); /* trimm */
  QString str2 = incomming;
  bool ok;
  str2.toFloat(&ok);
  return ok;
}

/* encode to name */
QString encodeBase64(QString xml) {
  QByteArray text;
  text.append(xml);
  return text.toBase64();
}

/* decode to name */
QString decodeBase64(QString xml) {
  QByteArray xcode("");
  ;
  xcode.append(xml);
  QByteArray precode(QByteArray::fromBase64(xcode));
  QString notetxt = precode.data();
  return notetxt;
}

/* encode to name */
QString encodeBase64(QByteArray chunk) { return chunk.toBase64(); }

/* decode to name */
QString decodeBase64(QByteArray chunk) {
  QByteArray precode(QByteArray::fromBase64(chunk));
  QString notetxt = precode.data();
  return notetxt;
}

/* copy file from a to b ... if dir not exist make it ...*/
bool copy(const QString inputfile, const QString outfile) {
  bool actioncpy = false;
  QString ultimacartellaaperta = outfile.left(outfile.lastIndexOf("/")) + "/";
  QDir dira(ultimacartellaaperta);
  if (dira.mkpath(ultimacartellaaperta)) {
  } else {
    return actioncpy;
  }
  if (is_file(inputfile)) {
    unlink(outfile);
    QFile Imaged(inputfile);
    if (Imaged.copy(outfile)) {
      actioncpy = true;
    }
  }
  return actioncpy;
}

bool is_file(const QString fullFileName) {
  QFile f(fullFileName);
  if (f.exists(fullFileName)) {
    return true;
  } else {
    return false;
  }
}

bool file_put_contents(const QString fullFileName, QString xml, int modus) {
  if (modus == 10) {
    return true; /// no debug!!
  }

  QFileInfo fix(fullFileName);

  QDir dira(fix.absolutePath());
  if (dira.mkpath(fix.absolutePath())) {
  } else {
    return false;
  }

  if (modus == 1) {
    unlink(fullFileName); /// if is one make place..
  }
  QFile f(fullFileName);
  if (modus == 1) {
    if (f.open(QIODevice::WriteOnly)) {
      QTextStream sw(&f);
      sw.setCodec("UTF-8");
      sw << xml;
      f.close();
      if (f.bytesAvailable() > 0) {
        return true;
      } else {
        return false;
      }
    }
  } else {
    if (f.open(QFile::Append | QFile::Text)) {
      QTextStream sw(&f);
      sw.setCodec("UTF-8");
      sw << xml;
      f.close();
      if (f.bytesAvailable() > 0) {
        return true;
      } else {
        return false;
      }
    }
  }
    return false;
}
