#include "epubview.h"
#include "core_application.h"

EpubView::EpubView(QWidget *parent) : QTextBrowser(parent) {
  modusNow = 1;
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  ModusPlay();
}
void EpubView::ModusPlay() {
  this->setContentsMargins(22, 11, 22, 11);
  this->setReadOnly(true); ////  lesen ..kopieren
  this->setMinimumWidth(400);
  this->setMinimumHeight(400);
  this->resize(600, 500);
  this->setOpenExternalLinks(true);
  this->setOpenLinks(true);
  this->document()->setDocumentMargin(100);
  this->document()->setPageSize(QSizeF(800, 500));
}
void EpubView::PlayFile(const QUrl localremote) {
  CCDEBUG() << localremote << " -> open... this ";
  this->OpenEpub(localremote);
}
void EpubView::OpenEpub(const QUrl localremote) {
  playepub = new Epub::Converter();
  const QString ebookfile = localremote.toLocalFile();
  CCDEBUG() << ebookfile << " -> !!!!! ebookfile";
  QList<EpubToc> listing = playepub->convert(ebookfile, _ZIPCACHEBOOK_);
  //// list full Table of Contenent toc..   first file cover... 
  CCDEBUG() << listing.size() << " -> size  EpubToc file ... this ";
  if (listing.size() > 2) {
    EpubToc fox = listing.at(3);
    QFileInfo eefile(fox.jumpurl);
    this->setSource(QUrl::fromLocalFile(eefile.absoluteFilePath()));
    ///this->document()->setBaseUrl(QUrl::fromLocalFile(eefile.absolutePath()));
    CCDEBUG() << fox.jumpurl << " -> open first url ... this ";
  }
  ModusPlay();
}
