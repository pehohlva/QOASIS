#ifndef EPUBVIEW_H
#define EPUBVIEW_H

#include "core_application.h"
#include <QWebEngineView>
#include <QWidget>
//// QTextBrowser 2 QWebEngineView
class EpubView : public QWebEngineView {
  Q_OBJECT
public:
  explicit EpubView(QWidget *parent = nullptr);
  QList<EpubToc> RenderMenu() { return active_epub; }

signals:
  void PaintMenuEpub(bool);
public slots:
  void PlayFile(const QUrl localremote);
  void OpenEpub(const QUrl urie);
  void JumpEpub(const QUrl urie);

private:
  int modusNow;
  QList<EpubToc> active_epub;
  Epub::Converter *playepub;
};

#endif // EPUBVIEW_H
