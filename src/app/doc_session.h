/*
    Copyright (C)  2017 Piter K. <pehohlva@gmail.com>

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DOC_SESSION_H
#define DOC_SESSION_H

#include "editorkernel.h"
#include <QObject>
#include <QSettings>
#include <QTextDocument>
#include <QWidget>
#include <QProcess>
#include <QObject>



#define _BASICORG_ QString("QTClub")
#define _BASICDOMAINE_ QString("org.freeroad.ch")
#define _BASICTITLE_EDITOR_ QString("OasisEdit - Document Tiny Editor")
#define _CVERSION_ QString("Vr. 1.2")
#define _WORKDEFAULTFONT_ QString("Ubuntu-C")
#define Q_WS_MAC  Q_OS_MAC


// by error no image insert pix image transparent
#define __ONEPIXELGIF__                                                        \
  QString("data:image/"                                                        \
          "gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==")

#define CACHEBUFFERDISKTMP QString("%1/.kernelversion").arg(QDir::homePath())

#define CACHEFILETMP QString("%1/index.html").arg(CACHEBUFFERDISKTMP)

#define CACHESPEECHFILE QString("%1/read.dat").arg(CACHEBUFFERDISKTMP)

#define _NONAMEFILE_ QString("Untitled.txt")

#if 0 //// 1 or 0
#define SESSDEBUG qDebug
#define STAGE 1
#define _debuglogfile_                                                         \
  QString("/Volumes/dati/sandbox/Tiny_Edit/src/mim_log.txt")
#else
#define SESSDEBUG                                                              \
  if (0)                                                                       \
  qDebug
#define STAGE 0
#define _debuglogfile_ QString("")
#endif

static inline QString unixwhich(QString apps = QString("gs")) {
#ifdef Q_OS_WIN
  return QString();
#endif
  QStringList potential_paths;
  potential_paths.append("/usr/bin");
  potential_paths.append("/usr/local/bin");
  potential_paths.append("/sw/bin"); /* to use on mac as same */
  potential_paths.append("/opt/bin");
  QProcess *process = new QProcess(NULL);
  process->setReadChannelMode(QProcess::MergedChannels);
  QStringList env = process->systemEnvironment();
  env.replaceInStrings(QRegExp("^PATH=(.*)", Qt::CaseInsensitive),
                       "PATH=\\1;" + potential_paths.join(";"));
  process->setEnvironment(env);
  process->start(QString("which"), QStringList() << apps, QIODevice::ReadOnly);
  if (!process->waitForFinished()) {
    return QString();
  } else {
    QString finder = process->readAll().trimmed();
    if (finder.endsWith(apps, Qt::CaseInsensitive)) {
      return finder;
    } else {
      return QString();
    }
  }
}

#ifndef _QCLD2NO_
#include <qtrlocale.h>
static inline QLocale LanguageDoc(const QString txt) {
  QTrlocale Vtr;
  return Vtr.getQlocaleFromText(txt);
}
#else
static inline QLocale LanguageDoc(const QString txt) {
  return QLocale::system();
}
#endif

class DOC : public QObject {
  Q_OBJECT

public:
  static DOC *self(QObject *parent = nullptr);
  QString
  GetHtml(const QString file); //// null if QTextDocument is ok or html no image
  QTextDocument *GetQdoc(const QString file);

  QVariant value(const QString name);               /// qsetting
  void setValue(const QString name, QVariant data); /// qsetting

  bool haveBase64pics(const QString html);
  //// html + base64 encodet image go normal to QTextDocument back
  void HtmlDecode(QString &html, QTextDocument *d);
  /// portable images inside. & read ok.. browser & here.
  void DecodeHtml(QString &html, QTextDocument *d);
  ///// void setDoc(QTextDocument *indoc) { picsdoc = indoc->clone(); }
  QByteArray picxencode(QImage im);
  QString readcfile(const QString fullFileName);
signals:
  void setMessage(QString);
  void setPriorMessage(QString);
  void setMessageBase(QString);
public slots:
  void incommingText(QString txt);
  void log_documents(QString xtcr);
  void wakeUpContenent(QString plaintext, const QFileInfo file);
  void save();
  void setDir(const QString workdir);
  void installfont(bool inout);
private slots:
  void observerDoc();

private:
  DOC(QObject *parent = nullptr);
  static QPointer<DOC> _self;
  void run_textutils(const QString file);
  void image_grep(QString &html, QString &newhtml);
  QTextDocument *d;
  int action;
  QString workdirectory;
  QString txtutils;
  QString DOC_INFONOW;
  QString msg;
  QStringList ALLWORD;
  QString f;
  bool loading;
};

#endif // DOC_SESSION_H
