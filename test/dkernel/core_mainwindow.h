#ifndef CORE_MAINWINDOW_H
#define CORE_MAINWINDOW_H

#include "core_application.h"
#include <QObject>
#include <QWidget>

#include "epubview.h"

class QMainWindow;

class Core_MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit Core_MainWindow(QWidget *parent = nullptr);
  void resizeEvent(QResizeEvent *event);
  void closeEvent(QCloseEvent *event);
signals:
  void Request_To_Close();
  void Set_Tmp_File(QString);
public slots:
  void ComboEpubWake(bool e);
  void RequestPutFile(QUrl uri);
  void SetStatusText(const QString text);
  void SetBookorFile();
  void NavitoepubPage(int x);

protected:
  void Check_Visible_Engine( bool e);
  void CheckeOpenFile(const QString file);
  QMenu *fileMenu;
  QLabel *statusbar; /// to write in
  EpubView *emainw;
  QComboBox *epub_pages; /// list toc
};

#endif // CORE_MAINWINDOW_H
