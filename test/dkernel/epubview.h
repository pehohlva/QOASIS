#ifndef EPUBVIEW_H
#define EPUBVIEW_H

#include "core_application.h"
#include <QTextBrowser>
#include <QTextEdit>
#include <QWidget>

class EpubView : public QTextBrowser {
  Q_OBJECT
public:
  explicit EpubView(QWidget *parent = nullptr);

signals:

public slots:
  void PlayFile(const QUrl localremote);
  void OpenEpub(const QUrl localremote);
  void ModusPlay();

private:
  int modusNow;
  Epub::Converter *playepub;
};

#endif // EPUBVIEW_H
