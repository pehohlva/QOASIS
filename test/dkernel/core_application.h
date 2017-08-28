#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include <QApplication>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QCursor>
#include <QDebug>
#include <QDesktopWidget>
#include <QDialog>
#include <QDir>
#include <QEvent>
#include <QFileDialog>
#include <QFileinfo>
#include <QIcon>
#include <QKeySequence>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QObject>
#include <QPlainTextEdit>
#include <QPoint>
#include <QProgressBar>
#include <QPushButton>
#include <QResizeEvent>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QStyle>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QTimer>
#include <QWidget>
#include <QWidgetAction>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

#include "sys/kernel_document.h"


#if 1 //// 1 or 0
#define CCDEBUG qDebug
#define STAGE 1
#else
#define CCDEBUG                                                                \
  if (0)                                                                       \
  qDebug
#define STAGE 0
#endif

#define WEBAGENTNAME "Google"
#define _PROGRAM_NAME_ QString("KernelApp")
#define _PROGRAM_NAME_DOMAINE_ QString("qt.io")
#define _ORGANIZATION_NAME_ QString("Avasoft")
#define _PROGRAM_VERSION_ QString("version 0.2.1 / go git")
#define _PROGRAM_OWNER_ QString("version 0.2.1")
#define _PROGRAM_TITLE_ QString("TestApp")
#define _PROGRAM_SHORT_NAME QString("docsrc_test")
#define TUMBNAIL_SIZE 120
#define ICONSW_SIZE 50
#define _ZIPCACHEBOOK_ QString("%1/ebooks/fromlocal/").arg(QDir::homePath())
#define _FIRSTWINDOWTITLESHOW_ QString("Test epub File in QTextBrowser")
#define _TESTBOOKS_ QString("%1/tmp/").arg(_ZIPCACHEBOOK_)


#define core_application (static_cast<RDoc *>(QCoreApplication::instance()))

class Core_MainWindow;

class Core_Application : public QApplication {
  Q_OBJECT

public:
  explicit Core_Application(int &argc, char **argv);

signals:
  /// emit to mac user app drag e drop to app icon action!
  void PlayMessage(QString); //// SetStatusText
  void FileOpenOrSet(QString);
public slots:
  void ParkingFile(QString file);
  void CheksEventApp();
  void Bevore_Quit();

private:
  bool event(QEvent *event);
  void closeEvent(QCloseEvent *event);
  QString wait_onefile;
  QStringList wait_filetoOpen;
  QRect screens;
  int modus_run;
  int log_intern;
  QRect screen;
  Core_MainWindow *mainw;
};

#endif // CORE_APPLICATION_H
