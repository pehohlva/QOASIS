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
  void RequestPutFile(const QString file);
  void SetStatusText(const QString text);
  void SetBookorFile();

protected:
  void Make_Test_File(); /// to test all ...
  QMenu *fileMenu;
  QLabel *statusbar; /// to write in
  EpubView *emainw;
};

#endif // CORE_MAINWINDOW_H
