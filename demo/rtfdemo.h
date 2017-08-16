
#ifndef RTFDEMO_H
#define RTFDEMO_H

#include "rtfreader.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QScrollBar>
#include <QXmlQuery>
#include <QAbstractScrollArea>
#include <QSystemTrayIcon>
#include <QAbstractScrollArea>
#include <QSystemTrayIcon>
#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QScrollBar>
#include <QDomDocument>
#include <QAbstractScrollArea>
#include <QPainter>
#include <QBuffer>
#include <QTextDocument>
#include <QBuffer>
#include <QDebug>
#include <QTextFrameFormat>
#include <QTextFrame>
#include <QBuffer>
#include <QMainWindow>

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
