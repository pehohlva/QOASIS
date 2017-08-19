#include "documentsession.h"
#include <QCloseEvent>
#include <QPointer>

DocumentRam &DocumentRam::operator=(const DocumentRam &d) {
  filename = d.filename;
  ext = d.ext;
  RealSize = d.RealSize;
  created = d.created;
  page = d.page;
  return *this;
}

/*
QDebug &DocumentRam::operator<<(QDebug debug, DocumentRam &udoc) {
  debug.nospace() << "DocumentRam(Enable." << udoc.filename << ",filename(),"
                  << udoc.ext << ",ext()," << udoc.RealSize << ",RealSize(),"
                  << udoc.created << ",created()," << udoc.page << ",page()"
                  << ")";
  return debug.space();
}
*/

QByteArray DocumentRam::hashmodel() {
  QString position, tmp;
  tmp.append(filename);
  tmp.append(ext);
  tmp.append(QString::number(created));
  QCryptographicHash enmd5(QCryptographicHash::Sha1);
  enmd5.addData(tmp.toLocal8Bit());
  const QByteArray chunkha = enmd5.result();
  return chunkha.toHex();
}

QByteArray DocumentRam::idx(QString file) {
  QFileInfo fi(file);
  if (!fi.exists()) {
    return QByteArray();
  }
  filename = file;
  QDateTime filestamp(fi.created());
  created = filestamp.currentSecsSinceEpoch();
  ext = QString(fi.completeSuffix()).toLower();

  QString position, tmp;
  tmp.append(filename);
  tmp.append(ext);
  tmp.append(QString::number(created));
  QCryptographicHash enmd5(QCryptographicHash::Sha1);
  enmd5.addData(tmp.toLocal8Bit());
  const QByteArray chunkha = enmd5.result();
  return chunkha.toHex();
}

DocumentRam::DocumentRam() {
  filename = QString("none");
  ext = QString("none");
  RealSize = QSizeF(50, 50);
  created = QDateTime::currentSecsSinceEpoch();
  page = 0;
}

DocumentRam::operator QVariant() const { return QVariant::fromValue(*this); }
DocumentRam::~DocumentRam() { filename = QString(); }

DocSession::DocSession(QObject *parent) : QObject(parent), Processing(false) {
  render = 0;
}

DocSession::~DocSession() {
  /// save doc list...
  this->deleteLater();
}

bool DocSession::is_OnChain(DocumentRam e) {
  bool iifound = false;
  QMapIterator<int, DocumentRam> i(DocumentList());
  while (i.hasNext()) {
    i.next();
    DocumentRam current = i.value();
    if (e.hashmodel() == current.hashmodel()) {
      iifound = true;
    }
  }
  if (!iifound) {
    const int tot = history_page_norms.size();
    history_page_norms.insert(tot, e);
  }
  return iifound;
}

int DocSession::Doc_Open(const QString file) {

  QFileInfo fi(file);
  DocumentRam now;
  QByteArray way = now.idx(file);
  if (this->is_OnChain(now)) {
    ////reopen
    return -1;
  }

  DocBuffer *buf = new DocBuffer();
  QMimeDatabase mimeDatabase;
  QMimeType mimeType = mimeDatabase.mimeTypeForFile(file);
  QStringList typs = mimeType.aliases();
  typs << mimeType.filterString().toLower(); // if upper case
  typs.append(mimeType.filterString());
  typs.append(mimeType.suffixes());
  typs.append(mimeType.aliases());
  typs.append(mimeType.parentMimeTypes());
  buf->~DocBuffer();
  emit wait_loading(fi.size());
  QTimer::singleShot(250, this, SLOT(on_loading()));
  Processing = true;
  return 1;
}

void DocSession::on_loading() {
  if (Processing) {
    ++render;
    if (render > 100) {
      render = 1;
    }
    emit wait_loading(render);
    const int wait = 1000;
    qDebug() << __FUNCTION__ << " sender .. " << render << " .. ";
    QTimer::singleShot(200, this, SLOT(on_loading()));
  }
}
