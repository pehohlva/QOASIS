#include "epubview.h"
#include "core_application.h"

EpubView::EpubView(QWidget *parent) : QWebEngineView(parent) {
  modusNow = 1;
  this->setMinimumWidth(400);
  this->setMinimumHeight(400);
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  this->setContentsMargins(0,0,0,0);
  //// this->setBackgroundRole();
}

///// all file here...
void EpubView::PlayFile(const QUrl localremote) {
  CCDEBUG() << localremote << " -> open... this ";
  this->OpenEpub(localremote); /// if epub
}

/* only epub file here down!  */

void EpubView::OpenEpub(const QUrl urie) {
  playepub = new Epub::Converter();
  const QString ebookfile = urie.toLocalFile();
  qDebug() << ebookfile << " -> !!!!! ebookfile";
  active_epub = playepub->convert(ebookfile, _ZIPCACHEBOOK_);
  //// list full Table of Contenent toc..   first file cover...
  qDebug() << active_epub.size() << " -> size  EpubToc file ... this ";
  if (active_epub.size() > 0) {
    EpubToc fox = active_epub.at(0);
    QFileInfo eefile(fox.jumpurl);
    this->JumpEpub(QUrl::fromLocalFile(eefile.absoluteFilePath()));
    qDebug() << fox.jumpurl << " -> open first url ... this ";
    emit PaintMenuEpub(true);
  }
}

//// move page from combobox
void EpubView::JumpEpub(const QUrl urie) {
  this->setUrl(urie);
}
