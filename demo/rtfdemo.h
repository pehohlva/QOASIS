
#ifndef RTFDEMO_H
#define RTFDEMO_H

#include "rtfreader.h"

#include "Qt/qmainwindow.h"

class RtfDemo : public QMainWindow {
  Q_OBJECT

public:
  RtfDemo();
  ~RtfDemo();

private slots:
  void openFile();
  void saveTextFile();
  void saveHtmlFile();
  void saveOdfFile();

private:
  QTextDocument *m_rtfDocument;

  QAction *m_saveTextAction;
  QAction *m_saveHtmlAction;
  QAction *m_saveOdfAction;
};

#endif
