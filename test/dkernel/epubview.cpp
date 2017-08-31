#include "epubview.h"
#include "core_application.h"

#include <QEventLoop>
#include <QWebEnginePage>
#include <QTimer>
#include <QPushButton>

#include <qtrlocale.h>




EpubView::EpubView(QWidget *parent) : QWebEngineView(parent) {
  modusNow = 1;
  this->setMinimumWidth(400);
  this->setMinimumHeight(400);
  this->setContentsMargins(0, 0, 0, 0);
  connect(QWebEngineView::page(), SIGNAL(loadFinished(bool)), this, SLOT(startHtmlGrab(bool)));
}

void EpubView::startHtmlGrab( bool ok) {
     if (ok) {
         QUrl uri = this->page()->url();
         if (uri.isLocalFile()) {
            connect(this, SIGNAL(incomHtml(QString)), this, SLOT(handleHTML(QString)));
            this->page()->toHtml([this](const QString& result) mutable { emit (void)incomHtml(result);});
         }
     }
}

void EpubView::handleHTML(QString sHTML)
{
    QUrl uri = this->page()->url();
    if (!uri.isLocalFile()) {
        return;
    }

    /*  QString htmlsource;
  QString text2voice;
  QSet<QString> uniqueVdoc;
  QList<VoiceDocument> VoiceHistory; /// back forward
  */
    htmlsource = sHTML;
    QTextDocument  *d = new QTextDocument();
    d->setHtml(htmlsource);
    text2voice = d->toPlainText();
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    uint unixtime = currentDateTime.toTime_t();
    doctitle = this->page()->title();
    if (doctitle.isEmpty()) {
        doctitle = QString("Unknow Title Document.");
    }
  QTrlocale Vtr;
  QLocale reclang = Vtr.getQlocaleFromText(text2voice);
  VoiceDocument vdoc;
  vdoc.unixtime = unixtime;
  vdoc.title = doctitle;
  vdoc.jumpurl = uri.toString(QUrl::RemoveFragment);
  vdoc.text = text2voice;
  vdoc.lang = reclang.bcp47Name();
  vdoc.readok = 0;
  vdoc.local = true;
  if (uniqueVdoc.contains(vdoc.jumpurl)) {
     uniqueVdoc.insert(vdoc.jumpurl);
     VoiceHistory.append(vdoc);
  }
  vcurrent = vdoc;
  //// qDebug()<< "Rec The HTML is :" << htmlsource.size();
  //// qDebug()<< "Rec The Plaintext is :" << text2voice.size();
  //// qDebug()<< "Rec The vdoc.jumpurl is :" << vdoc.jumpurl;
  emit VdocReady();
}

void EpubView::contextMenuEvent(QContextMenuEvent *event) {
  QMenu *menu = page()->createStandardContextMenu();

  /*
  const QList<QAction*> actions = menu->actions();
  auto it = std::find(actions.cbegin(), actions.cend(),
  page()->action(QWebEnginePage::OpenLinkInThisWindow)); if (it !=
  actions.cend()) {
      (*it)->setText(tr("Open Link in This Tab"));
      ++it;
      QAction *before(it == actions.cend() ? nullptr : *it);
      menu->insertAction(before,
  page()->action(QWebEnginePage::OpenLinkInNewWindow));
      menu->insertAction(before,
  page()->action(QWebEnginePage::OpenLinkInNewTab));
  }   */
  qDebug() << "### contextMenuEvent   " << event->globalPos();
  menu->popup(event->globalPos());
}


/*  ///// this->page()->SelectAll();
  ////CCDEBUG() << op << "tt slect"; */
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
void EpubView::JumpEpub(const QUrl urie) { this->setUrl(urie); }
