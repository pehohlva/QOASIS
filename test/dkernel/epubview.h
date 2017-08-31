#ifndef EPUBVIEW_H
#define EPUBVIEW_H

#include "core_application.h"
#include <QWebEngineView>
#include <QWidget>

struct VoiceDocument {

  QString print() {
        QString result = QString("<div><a href='#%1'>").arg(jumpurl) +
                     QString("<h1>") + title + QString("</h1>") +
                     QString("</a></div>\n<!-- Unixtime/OrderId = (%1) ,%2, -->").arg(unixtime).arg(orderid);
    return result;
  }
  QString qurl() {
      return jumpurl;
  }

  QString debug() {
      QString x = QString("|text:%1").arg(text.size());
               x+=QString("|jumpurl:%1").arg(jumpurl);
               x+=QString("|title:%1").arg(title);
               x+=QString("|lang:%1").arg(lang);
               x+=QString("|unixtime:%1").arg(unixtime);
               x+=QString("|orderid:%1").arg(orderid);
      return x;
  }

  QString text;
  QString jumpurl;
  QString title;
  QString lang;
  uint unixtime;
  int readok;
  int readstop;
  int orderid;
  bool local;
};




//// QTextBrowser 2 QWebEngineView
class EpubView : public QWebEngineView {
  Q_OBJECT
public:
  explicit EpubView(QWidget *parent = nullptr);
  void toPlainTextLambda();
  QList<EpubToc> RenderMenu() { return active_epub; }
  QString PlainTextcc() { return text2voice; }
  VoiceDocument CurrentDoc() {
      return vcurrent;
  }
   void WeneedTxt();
signals:
  void PaintMenuEpub(bool);
  void htmlReady();
  void VdocReady();
  void incomHtml(QString);
public slots:
  void PlayFile(const QUrl localremote);
  void OpenEpub(const QUrl urie);
  void JumpEpub(const QUrl urie);
  void startHtmlGrab(bool ok);
  void handleHTML(QString sHTML);

protected:
  QString htmlsource;
  QString text2voice;
  QString doctitle;
  void RollContext(const QPoint &pos);
  void contextMenuEvent(QContextMenuEvent *event);

private:
  int modusNow;
  QSet<QString> uniqueVdoc;
  QList<VoiceDocument> VoiceHistory; /// back forward
  QList<EpubToc> active_epub;
  Epub::Converter *playepub;
  VoiceDocument vcurrent;
};

#endif // EPUBVIEW_H
