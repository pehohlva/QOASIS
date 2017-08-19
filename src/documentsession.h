#ifndef DOCUMENTSESSIONPHPIDNUMC23765H
#define DOCUMENTSESSIONPHPIDNUMC23765H

#include <QAbstractSocket>
#include <QApplication>
#include <QDebug>
#include <QDomElement>
#include <QFileInfo>
#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QtCore>
#include <QtGui>
//// #include <stdio.h>

#ifdef LOADPDFIUMYES
#include <QPdfium>
#include <QPdfiumPage>
#endif

/// a pointer to write history epup odt docx
/// pdf go to html each page a image is faster.
/// only to display and speack text from pdfium
class DocumentRam {

public:
  enum { MAGICNUMBER = 0xFFAAFFAA, VERSION = 2 };
  DocumentRam();
  ~DocumentRam();
  QByteArray idx(QString file);
  QByteArray hashmodel();
  bool operator!=(DocumentRam &d);
  DocumentRam &operator=(const DocumentRam &d);
  operator QVariant() const;
  int page;
  QSizeF RealSize;
  QString ext;      /// mime type
  QString filename; // & path full
  uint created;
};

Q_DECLARE_METATYPE(DocumentRam);

/* not export if is a lib! this is only a bridge from app to documnts  */
/// RTF & RTFD- Rich Text Format

static inline QString FileFilterHaving() {
  QString filter;
  filter = "";
  /// filter += QString( "FOP file" ) + " (*.fop *.fop.gz *.fo *.fo.gz
  /// *.xml);;";
  //// filter+= QString( "MiniScribus binary stream file" ) + " (*.page);;";
  //// filter+= QString( "OpenOffice 1.1 file format" ) + " (*.sxw *.stw);;";
  /////museum
  filter += QString("RichtText Format") + " (*.rtf);;";
  filter +=
      QString("Plain Text Format") + " (*.txt *.tmp *.dat *.c *.h *.cpp);;";
  filter += QString("OpenOffice 2.4 file format") + " (*.odt *.ott);;";
  filter += QString("RichText Format ") + " (*.rtf *.rtfd);;";
  filter += QString("XHTML file Format") + " (*.htm *.html);;";
  filter += QString("PDF  Format") + " (*.pdf);;";
  filter += QString("Epub Book all Book Format") + " (*.epub *.* );;";
  //////filter += ")";
  return filter;
}

#define _BG_CHAR_ALPHA_ 425
#define _TXT_CHAR_ALPHA_ 424

#define POINT_TO_CM(cm) ((cm) / 28.3465058)
#define POINT_TO_MM(mm) ((mm) / 2.83465058) ////////  0.352777778
#define POINT_TO_DM(dm) ((dm) / 283.465058)
#define POINT_TO_INCH(inch) ((inch) / 72.0)
#define POINT_TO_PI(pi) ((pi) / 12)
#define POINT_TO_DD(dd) ((dd) / 154.08124)
#define POINT_TO_CC(cc) ((cc) / 12.840103)
////------------------------------------
#define MM_TO_POINT(mm) ((mm)*2.83465058)
#define CM_TO_POINT(cm) ((cm)*28.3465058) ///// 28.346456693
#define DM_TO_POINT(dm) ((dm)*283.465058)
#define INCH_TO_POINT(inch) ((inch)*72.0)
#define PI_TO_POINT(pi) ((pi)*12)
#define DD_TO_POINT(dd) ((dd)*154.08124)
#define CC_TO_POINT(cc) ((cc)*12.840103)

#define _PAGE_NUMERATION_ QString("#Page#")

class DocSession : public QObject {
  Q_OBJECT

public:
  DocSession(QObject *parent = nullptr);
  ~DocSession();
  int Doc_Open(const QString file);
  QMap<int, DocumentRam> DocumentList() { return history_page_norms; }
  bool is_OnChain(DocumentRam e);

signals:
  void wait_loading(qint64);
public slots:
  void on_loading();

private:
  QMap<int, DocumentRam> history_page_norms;
  bool Processing;
  int render;
};

class DocBuffer {
public:
  DocBuffer() : d(new QBuffer()) { d->open(QIODevice::ReadWrite); }
  ~DocBuffer() { d->close(); }
  bool clear() {
    d->write(QByteArray());
    return d->bytesAvailable() == 0 ? true : false;
  }

  bool LoadFile(const QString file) {
    if (clear()) {
      QFile f(file);
      if (f.exists()) {
        if (f.open(QFile::ReadOnly)) {
          d->write(f.readAll());
          d->seek(0);
          return true;
        }
      }
    }
    return false;
  }

  bool PutOnFile(const QString file) {
    QFile f(file);
    d->seek(0);
    if (f.open(QFile::WriteOnly)) {
      uint bi = f.write(stream());
      f.close();
      return bi > 0 ? true : false;
    }
    return false;
  }

  QIODevice *device() { return d; }
  QByteArray stream() { return d->data(); }
  /* <?xml version="1.0" encoding="utf-8"?> */
  QString data() { return QString::fromUtf8(stream()); }
  QString tohtmlsimulate() {
    QStringList lines = data().split(QRegExp("[\n]"), QString::KeepEmptyParts);
    QString str = lines.join("<br/>");
    str.prepend(QString("<p>"));
    str.append(QString("<p/>"));
    return str;
  }

  QBuffer *d;
  QDomDocument Dom() { return doc; }
  bool isValid() { return doc.setContent(stream(), false, 0, 0, 0); }
  QDomDocument doc;
};

#endif // DOCUMENTSESSION_H
