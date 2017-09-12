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
#include "doc_session.h"

#include "zipdoc.h"  /// simple..
#include "kzip.h" ///  best?
#include "editorkernel.h"
#include "core_htmldriver.h"
#include "oasimain.h"
#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QSettings>
#include <QToolBar>

QPointer<DOC> DOC::_self = 0L;

DOC *DOC::self(QObject *parent) {
  if (!_self)
    _self = new DOC(parent);
  return _self;
}

DOC::DOC(QObject *parent) : QObject(parent) {
  d = new QTextDocument(parent);
  QDir dirsystem;
  if (!dirsystem.mkpath(CACHEBUFFERDISKTMP)) {
    qWarning() << "Failed to mkdir cache  " << CACHEBUFFERDISKTMP;
  }
  action = -1;
  QTimer::singleShot(1000, this, SLOT(observerDoc()));
  loading = false;
}

#include "ui_forms.h"
#include <QCloseEvent>

#include <OdtFormat>
#include <RTFFormat>

#ifndef _NOSVGMODULE_
#include <QtSvg>
#endif

#include <QMimeDatabase>
#include <QMimeType>

#ifndef _NO_PDFIUM_MODULE_
#include <QtPdfium/QPdfium>
#endif

#define IPNG QString("png")
#define IJPG QString("jpg")
#define ITIFF QString("tiff")
#define IRTF QString("rtf")
#define IRTFD QString("rtfd")
#define IDOC QString("doc")
#define IDOCX QString("docx")
#define IHTML QString("html")
#define IODT QString("odt")
#define IOTT QString("ott")
#define IPDF QString("pdf")
#define IZIP QString("zip")
#define MODTM QString("application/vnd.oasis.opendocument.text")
#define MACTEST QString("_osx_yes")

static inline QByteArray picencode(QImage im) {
  int w = im.width();
  int h = im.height();
  QByteArray bytes;
  QBuffer buffer(&bytes);
  buffer.open(QIODevice::WriteOnly);
  im.save(&buffer, "PNG");
  if (bytes.size() > 0) {
    QByteArray blueimag = bytes.toBase64();
    QByteArray orderpic("data:image/png;base64,");
    orderpic.append(blueimag);
    return orderpic;
  } else {
    return QByteArray("data:image/"
                      "gif;base64,"
                      "R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==");
  }
}

static inline QString Bytes(const qint64 size) {
  if (size < 0)
    return QString();
  if (size < 1024)
    return QObject::tr("%1 B").arg(QString::number(((double)size), 'f', 0));
  if ((size >= 1024) && (size < 1048576))
    return QObject::tr("%1 KB").arg(
        QString::number(((double)size) / 1024, 'f', 0));
  if ((size >= 1048576) && (size < 1073741824))
    return QObject::tr("%1 MB").arg(
        QString::number(((double)size) / 1048576, 'f', 2));
  if (size >= 1073741824)
    return QObject::tr("%1 GB").arg(
        QString::number(((double)size) / 1073741824, 'f', 2));
  return QString();
}

QString DOC::GetHtml(const QString file) {
  f = file;
  loading = true;
  QString main;
  QMimeDatabase mimeDatabase;
  QMimeType mimeType;
  mimeType = mimeDatabase.mimeTypeForFile(file);
  QStringList alii = mimeType.aliases();
  const QString MIMENAME = mimeType.name();
  QFileInfo fi(file);
  QString namef = file;
  namef.prepend(fi.fileName() + QString(" - "));
  namef.append("/");
  namef.append(Bytes(fi.size()));
  QString logx = QString("{%1} - ").arg(MIMENAME) + QString(alii.join(",")) +
                 QString(" - ") + namef;
  log_documents(logx); /// know exact type.
  const QString EXT = fi.completeSuffix().toLower();
  if (!fi.exists()) {
    return QString("File not exist:%1").arg(file);
  }
  //// textutils can run on mac or linux a tool to doc convert hidden...

  if (EXT == IRTFD || EXT == IDOCX || EXT == IDOC ||
      EXT == QString("webarchive")) {
     run_textutils(file); /// go to html
    if (d->toHtml().size() > 33) {
      return QString(); /// pass doc fill..
    } else {
      main = QString("Unable to handle your file:%1").arg(file);
      return main;
    }
  } else if (MIMENAME == MODTM) {
    //// qDebug() << "load odt session section...";
    QString html;
    OOO::Converter *odt =
        new OOO::Converter(); // .odt odf or so...  OpenDocument Format.
    odt->convert(file, html);
    connect(odt, SIGNAL(setMetaMessage(QString)), this,
            SLOT(incommingText(QString)));
    if (haveBase64pics(html)) {
      HtmlDecode(html, d);
    } else {
      d->setHtml(html);
    }
    if (d->toHtml().size() < 33) {
      main = QString("Unable to handle your odt file:%1").arg(file);
      return main;
    } else {
      return QString(); /// pass doc fill..
    }
  } else if (EXT == IRTF) {
   ////  qDebug() << "load rtf section...";
    RtfReader::Reader *reader = new RtfReader::Reader();
    bool result = reader->open(f);
    if (!result) {
      main = QString("RtfReader can not handle file:%1").arg(file);
    } else {
      d->clear();
      RtfReader::TextDocumentRtfOutput *output =
          new RtfReader::TextDocumentRtfOutput(d);
      reader->parseTo(output);
      action = 1;
      main.clear();
    }
    /// textutilgo....
    main.clear();
    if (d->toHtml().size() > 22) {
      //// ok not need here by
    } else {
      qDebug() << "Run textutils section...";
      run_textutils(file); /// last option..
    }
  } else if (MIMENAME.contains(QString("image"))) { //// check as image? to display..
    QImage img;
    QImage pics;
    img = QIcon(file).pixmap(QSize(400, 400)).toImage();
#ifndef _NOSVGMODULE_
//// QSvgRenderer renderer(file);
//// renderer.isValid();
#endif
    if (!img.isNull()) {
      pics = img;
    } else {
      pics.load(file);
    }
    if (pics.isNull()) {
      main = tr("Unable to open/diplay your image file: %1").arg(file);
      return main;
    } else {
      QByteArray imgscroll = this->picxencode(pics);
      imgscroll.prepend("<p><img src=\"");
      imgscroll.append("\" /></p>");
      QString htmlx = QString(imgscroll.constData());
      ///// haveBase64pics(htmlx);
      HtmlDecode(htmlx, d);
      return QString();
    }
  } else {
    //// QMap<QString,QByteArray> liting = unzipstream(f);
    KZipStream *Kzip = new KZipStream(f);
    if (Kzip->canread()) {
      const QStringList entries = Kzip->filelist();
      QString streams = QString("You like to read zip File? name:%1\n").arg(f);
      for (int x = 0; x < entries.size(); x++) {
        QString line = entries.at(x) + QString("\n");
        streams.append(line);
      }
      d->setPlainText(streams);
      return main;
    }

    if (MIMENAME.contains(QString("/pdf"))) {
#ifndef _NO_PDFIUM_MODULE_
      QPdfium pdf(f);
      QString grep;
      const int sumpage = pdf.pageCount();
      const int last = sumpage - 1;
      for (int i = 0; i <= sumpage; i++) {
        if (i <= last) {
          QPdfiumPage page = pdf.page(i);
          grep.append(page.text());
        }
      }
      d->setPlainText(grep);
      return main;
#endif
/*   try popplerqt5 here  */



    }

    QFile file(f);
    if (!file.open(QFile::ReadOnly)) {
      main.clear();
      main = QString("Unable to open/diplay your image or document file.");
      return main;
    }
    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
      if (haveBase64pics(str)) {
        HtmlDecode(str, d);
      } else {
        d->setHtml(str);
      }
    } else {
      str = QString::fromLocal8Bit(data);
      d->setPlainText(str);
    }
  }

  return QString();
}

void DOC::wakeUpContenent(QString plaintext, const QFileInfo file) {
  if (loading)
    return;

  QLocale docl = LanguageDoc(plaintext);
  const int idlanguage = (int)docl.language();
  this->setValue(QString("DoumentCurrentLanguage"), QVariant(idlanguage));
  QMimeDatabase mimeDatabase;
  QString namef;
  const QString MIMENAME =
      mimeDatabase.mimeTypeForFile(file.absoluteFilePath()).name();
  if (file.exists()) {
    namef.prepend(file.fileName() + QString(" -%1 ").arg(idlanguage));
    namef.append(" ");
    namef.append(Bytes(file.size()));
  }
  DOC_INFONOW = namef;
  const QString lang = docl.nativeLanguageName();
  const int bhsize = plaintext.size();
  QString tlean = plaintext.trimmed();
  ALLWORD.clear();
  ALLWORD = tlean.split(" ");
  const int totalwords = ALLWORD.size();
  if (totalwords < 2) {
    DOC_INFONOW = _NONAMEFILE_;
  }
  if (file.exists()) {
    QString rec = DOC_INFONOW +
                  QString(" Word:%1/Char:%2").arg(totalwords).arg(bhsize) +
                  QString("-Lang:%1-%2").arg(lang).arg(idlanguage);
    emit setMessage(rec);
  } else {
    if (bhsize < 33) {
      QString rec =
          _NONAMEFILE_ + QString(" / ") + QString("-Lang:%1-%2").arg(lang).arg(idlanguage);
      emit setMessage(rec);
    } else {
      QString rec = _NONAMEFILE_ + QString(" / Save your work..") +
                    QString("-Lang:%1-%2").arg(lang).arg(idlanguage);
      emit setMessage(rec);
    }
  }
}

QTextDocument *DOC::GetQdoc(const QString file) {
  QMimeDatabase mimeDatabase;
  QMimeType mimeType;
  mimeType = mimeDatabase.mimeTypeForFile(file);
  QStringList alii = mimeType.aliases();
  QString namef = mimeType.name();
  QFileInfo fo(file);
  if (fo.exists()) {
    namef.prepend(fo.fileName() + QString(" - "));
    namef.append(" ");
    namef.append(Bytes(fo.size()));
  }
  DOC_INFONOW = namef;
  if (!DOC_INFONOW.isEmpty()) {
    emit setMessage(DOC_INFONOW);
  }

  if (file == f) {
    loading = false;
    return d;
  } else {
    const QString x = GetHtml(file);
    if (x.size() < 5) {
      d->setPlainText(
          QString("Unable to open your file %1 - %2.").arg(file).arg(namef));
    }
    loading = false;
    return d;
  }
  loading = false;
  return d;
}

/* here only osx mac wo have install textutils by default */
void DOC::run_textutils(const QString file) {
  QFile fix(CACHEFILETMP);
  if (fix.exists()) {
    fix.remove();
  }

  const QString txtutils = unixwhich(QString("textutil"));

  if (txtutils.size() < 4) {
    msg = QString(
        "<h1>Your System not support 'textutil' or is not Install!.<h1/>");
    d->setHtml(msg);
    msg.clear();
    return;
  }
  QString htmltext;
  QProcess *process = new QProcess(NULL);
  process->setReadChannelMode(QProcess::MergedChannels);
  QStringList cmd_rock;
  cmd_rock << "-convert"
           << "html" << file << "-output" << CACHEFILETMP;
  //// qDebug() << "### handler use-> | textutil " <<  cmd_rock.join(" ") <<"
  ///|";
  process->start(txtutils, cmd_rock, QIODevice::ReadOnly);
  if (!process->waitForFinished()) {
    msg = QString("QProcess fail..");
  } else {
    QString htmlimage;
    htmltext = readcfile(CACHEFILETMP);
    image_grep(htmltext, htmlimage);
    if (htmlimage.size() > 0) {
      if (haveBase64pics(htmlimage)) {
        HtmlDecode(htmlimage, d);
      } else {
        d->setHtml(htmlimage);
      }
    } else {
      d->setHtml(
          QString("<h1>Textutils not convert your file: %1</h1>").arg(f));
    }
  }
}

QByteArray DOC::picxencode(QImage im) {
  int w = im.width();
  int h = im.height();
  QByteArray bytes;
  if (w > 550) {
    im.scaled(550, 550, Qt::KeepAspectRatio);
  }
  QBuffer buffer(&bytes);
  buffer.open(QIODevice::WriteOnly);
  im.save(&buffer, "PNG");
  if (bytes.size() > 0) {
    QByteArray blueimag = bytes.toBase64();
    QByteArray orderpic("data:image/png;base64,");
    orderpic.append(blueimag);
    return orderpic;
  } else {
    return QByteArray("data:image/"
                      "gif;base64,"
                      "R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==");
  }
}

/* read the contenet of a local file as qstring */
QString DOC::readcfile(const QString fullFileName) {
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

void DOC::DecodeHtml(QString &html, QTextDocument *d) {
  if (d->isEmpty()) {
    QString msg = QString("Is not possibel to decode a Empty Document.");
    emit setPriorMessage(msg);
    return;
  }

  QDateTime UTC(QDateTime::currentDateTimeUtc());
  QDateTime local(UTC.toLocalTime());
  d->setMetaInformation(
      QTextDocument::DocumentTitle,
      QString("Oasis Document Encode/created Portable-Images - %1")
          .arg(local.toString()));

  QMap<QString, QImage> images; //// meganame
  QString xhtml = d->toHtml("utf_8");

  QMap<QString, QImage> imgname; //// meganame
  QRegExp expression("src=[\"\'](.*)[\"\']", Qt::CaseInsensitive);
  expression.setMinimal(true);
  int iPosition = 0;
  int tot = 0;
  while ((iPosition = expression.indexIn(xhtml, iPosition)) != -1) {
    const QString picname = expression.cap(1);
    QVariant img =
        d->resource(QTextDocument::ImageResource, picname); //// get image
    QImage imgxx = img.value<QImage>();
    images.insert(picname, imgxx);
    iPosition += expression.matchedLength();
  }
  QMapIterator<QString, QImage> it(images);
  while (it.hasNext()) {
    it.next();
    QByteArray ddpic = picencode(it.value());
    xhtml.replace(it.key(), ddpic);
  }

  html = xhtml;
}

void DOC::HtmlDecode(QString &html, QTextDocument *d) {
  if (!haveBase64pics(html)) {
    return;
  }
  if (html.size() < 3) {
    return;
  }
  QMap<QString, QImage> images;  //// meganame
  QMap<QString, QImage> imgname; //// meganame
  QRegExp expression("src=[\"\'](.*)[\"\']", Qt::CaseInsensitive);
  expression.setMinimal(true);
  d->clear();
  int iPosition = 0;
  int tot = 0;
  while ((iPosition = expression.indexIn(html, iPosition)) != -1) {
    const QString imagesrcx = expression.cap(1);
    int loengh = imagesrcx.length();
    QString first = imagesrcx.left(22);
    const int xf = first.indexOf(QString("base64,"), 0); /// 7 subs
    QByteArray yourpicencoded =
        QByteArray(imagesrcx.toLatin1())
            .remove(0, xf + 7); /// in png/jpg 7 base64, is 7char
    QByteArray xpii(QByteArray::fromBase64(yourpicencoded));
    QImage secv;
    secv.loadFromData(xpii);
    if (!secv.isNull()) {
      images.insert(imagesrcx, secv);
      tot++;
    }
    iPosition += expression.matchedLength();
  }

  QDateTime timer1(QDateTime::currentDateTime());
  const qint64 sec1970 = timer1.currentMSecsSinceEpoch();
  int counts = 0;
  QMapIterator<QString, QImage> it(images);
  while (it.hasNext()) {
    it.next();
    counts++;
    const QString newnamepic =
        QString("pic_") + QString::number(counts + sec1970) + QString(".png");
    QByteArray iofi = newnamepic.toLatin1();
    const QString imagex = it.key(); /// make name
    html.replace(imagex, iofi, Qt::CaseSensitive);
    imgname.insert(newnamepic, it.value());
    qDebug() << counts << "### new name on HtmlDecode " << newnamepic << " -";
  }
  d->clear();
  d->setHtml(html);
  QMapIterator<QString, QImage> xo(imgname);
  while (xo.hasNext()) {
    xo.next();
    qDebug() << "### fill resource HtmlDecode " << Bytes(xo.key().size())
             << " -" << xo.value().size();
    d->addResource(QTextDocument::ImageResource, QUrl(xo.key()), xo.value());
  }
  QDateTime UTC(QDateTime::currentDateTimeUtc());
  QDateTime local(UTC.toLocalTime());
  d->setMetaInformation(
      QTextDocument::DocumentTitle,
      QString("Oasis Document decoded on - %1").arg(local.toString()));
  imgname.clear();
  images.clear(); /// free ram
}

bool DOC::haveBase64pics(const QString html) {
  QRegExp expression("src=[\"data:\'data:](.*)[\"\']", Qt::CaseInsensitive);
  expression.setMinimal(true);
  int iPosition = 0;
  int tot = 0;
  while ((iPosition = expression.indexIn(html, iPosition)) != -1) {
    const QString imagesrcx = expression.cap(1);
    int loengh = imagesrcx.length();
    QString first = imagesrcx.left(100);
    const int xf = first.indexOf(QString("base64,"), 0); /// 7 subs
    if (first.size() > 0) {
      bool validim = false;
      if (xf > 0) {
        QByteArray xall = QByteArray(imagesrcx.toLatin1()).remove(0, xf + 7);
        QByteArray xpii(QByteArray::fromBase64(xall));
        QImage secv;
        secv.loadFromData(xpii);
        validim = (secv.isNull()) ? false : true;
        if (validim) {
          tot++;
        }
      }
    }
    iPosition += expression.matchedLength();
  }
  return (tot > 0) ? true : false;
}

/*
textutil  -convert html /Volumes/dati/sandbox/dkernelbellotrffoto.rtfd -output
/Users/dev/.kernelversion/index.html
*/
void DOC::image_grep(QString &html, QString &newhtml) {
  QMap<QString, QImage> mappic;
  QRegExp expression("src=[\"\'](.*)[\"\']", Qt::CaseInsensitive);
  expression.setMinimal(true);
  int iPosition = 0;
  int goway = -1;
  while ((iPosition = expression.indexIn(html, iPosition)) != -1) {
    const QString imagesrcx = expression.cap(1); /// this must replaced
    int loengh = imagesrcx.length();
    int repos = imagesrcx.indexOf("=");
    QUrl inserter(imagesrcx);
    if (repos < 1) {
      if (inserter.isLocalFile()) {
        QString filen = CACHEBUFFERDISKTMP + inserter.toLocalFile();
        QImage pio = QImage(filen);
        //// pio.load(filen)
        if (!pio.isNull()) {
          mappic.insert(imagesrcx, pio);
        }
      } else {
        QImage aufi;
        mappic.insert(imagesrcx, aufi); /// nullpic!!
      }
    }

    iPosition += expression.matchedLength();
  }
  QMapIterator<QString, QImage> i(mappic);
  while (i.hasNext()) {
    i.next();
    QImage ox = i.value();
    const QString htmlimage = QString(picxencode(ox).constData());
    html.replace(i.key(), htmlimage);
  }
  newhtml = html;
}

void DOC::incommingText(QString txt) {
  if (!txt.isEmpty()) {
    //// emit setPriorMessage(txt);
  }
  qDebug() << "###  message odt " << txt << " |";
}
void DOC::observerDoc() {
  QDateTime Tloac = QDateTime::currentDateTime().toLocalTime();
  QString xday = Tloac.toString(Qt::SystemLocaleLongDate);
  ///// mainw->SetStatusText(QString("Load: %1").arg(xday));
  QTimer::singleShot(1000, this, SLOT(observerDoc()));
  emit setMessageBase(QString("Dc. %1").arg(xday));
}

void DOC::setValue(const QString name, QVariant data) {
  QSettings session_s(QString("OasiClub"), QString("OasiEditor"));
  session_s.setValue(name, data);
}

QVariant DOC::value(const QString name) {
  QSettings session_s(QString("OasiClub"), QString("OasiEditor"));
  return session_s.value(name);
}

void DOC::log_documents(QString xtcr) {
  //// log mime to have exact association on open file...
  QString line = xtcr + QString("\n");

  QString logdd = readcfile(_debuglogfile_);
  logdd.prepend(xtcr);
  SESSDEBUG() << "### wake " << __FUNCTION__;
  QFile f(_debuglogfile_);
  if (f.open(QFile::Truncate | QFile::Text | QFile::ReadWrite)) {
    QTextStream sw(&f);
    sw.setCodec(QTextCodec::codecForName("UTF-8"));
    sw << logdd;
    f.close();
    if (f.bytesAvailable() > 0) {
      SESSDEBUG() << workdirectory << "### log ok " << __FUNCTION__;
    }
  }
}

void DOC::save() {
  //////  DownDir_RM(CACHEBUFFERDISKTMP);
  QDir trash(CACHEBUFFERDISKTMP);
  SESSDEBUG() << "###  trash.exists() " << trash.exists() << " by by wake "
              << __FUNCTION__;
}
void DOC::setDir(const QString workdir) { workdirectory = workdir; }
void DOC::installfont(bool inout) {
  QFontDatabase fontDatabase;
  QStringList pushfont;
  pushfont << QStringLiteral("Ubuntu-B.ttf");
  pushfont << QStringLiteral("Ubuntu-L.ttf");
  pushfont << QStringLiteral("Ubuntu-MI.ttf");
  pushfont << QStringLiteral("UbuntuMono-B.ttf");
  pushfont << QStringLiteral("UbuntuMono-RI.ttf");
  pushfont << QStringLiteral("Ubuntu-BI.ttf");
  pushfont << QStringLiteral("Ubuntu-LI.ttf");
  pushfont << QStringLiteral("Ubuntu-R.ttf");
  pushfont << QStringLiteral("UbuntuMono-BI.ttf");
  pushfont << QStringLiteral("Ubuntu-C.ttf");
  pushfont << QStringLiteral("Ubuntu-RI.ttf");
  pushfont << QStringLiteral("Ubuntu-M.ttf");
  pushfont << QStringLiteral("Ubuntu-R.ttf");
  if (inout) {
    for (int x = 0; x < pushfont.size(); x++) {
      const QString fox = QString(":/font/%1").arg(pushfont.at(x));
      if (fontDatabase.addApplicationFont(fox) == -1) {
        qWarning() << "Failed to load " << fox;
      } else {
        //// SESSDEBUG() << "Install success " << fox;
      }
    }
  } else {
    if (fontDatabase.removeAllApplicationFonts()) {
      //// SESSDEBUG() << "Remove fonts success " << pushfont;
    } else {
      qWarning() << "Failed to remove font ";
    }
  }
}
