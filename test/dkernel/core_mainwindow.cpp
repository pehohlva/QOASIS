#include "core_mainwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QStatusBar>

#include "epubview.h"

Core_MainWindow::Core_MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setObjectName(QString("maincreen"));
  QMenuBar *menubarre = new QMenuBar(this);
  QStatusBar *sta = new QStatusBar(this);
  statusbar = new QLabel("Application Loading...");
  sta->addWidget(statusbar); /// append progressbar from load
  this->setMenuBar(menubarre);
  this->setStatusBar(sta);

  fileMenu = menubarre->addMenu(tr("&File"));
  QAction *act_file_open = new QAction(tr("Open Fake File"), this);
  act_file_open->setShortcut(QKeySequence(QKeySequence::Open));
  connect(act_file_open, SIGNAL(triggered()), this, SLOT(SetBookorFile()));
  fileMenu->addAction(act_file_open);
  /* ---------------------------------------- */
  emainw = new EpubView(this);
  setCentralWidget(emainw);
  /* ---------------------------------------- */
  SetStatusText(QString("End .. Loading... "));
  this->show();
  Make_Test_File();
}


void Core_MainWindow::Make_Test_File() {
    QDir dira(_TESTBOOKS_);
    if ( dira.mkpath(_TESTBOOKS_) ) { } else {
    return;
    }
   const QString itemplay= QString("qt4cc.epub");
   QFile fister("://qt4cc.epub");
   QString destination = _TESTBOOKS_ + itemplay;
   QByteArray xchunk;
    if (fister.open(QFile::ReadOnly)) {
       xchunk = fister.readAll();
       fister.close();
    }
    CCDEBUG() << "xchunk.size() : " << xchunk.size();
    if (xchunk.size() > 1) {
        QFile f( destination );
          if ( f.open(  QIODevice::WriteOnly ) ) {
            f.write(xchunk);
            f.close();
          }
     }
     QFileInfo  fi(destination);
     if (fi.exists()) {
       CCDEBUG() << "incomming : " << fi.absoluteFilePath();
       const QUrl lluri = QUrl::fromLocalFile(fi.absoluteFilePath());
       CCDEBUG() << "QUrl : " << lluri;
       emainw->OpenEpub(lluri);
     }
}


void Core_MainWindow::RequestPutFile(const QString file) {

  CCDEBUG() << "incomming : " << file << ":" << __LINE__;
}

void Core_MainWindow::SetBookorFile() {
  const QString homeuser = QDir::homePath();
  CCDEBUG() << "Run: " << __FUNCTION__ << "-" << __FILE__ << ":" << __LINE__;
  QString file =
      QFileDialog::getOpenFileName(this, tr("Choose File..."), homeuser, "*",
                                   Q_NULLPTR, QFileDialog::DontUseNativeDialog);

  if (file.isEmpty()) {
    return;
  } else {
      QUrl fixifile = QUrl::fromLocalFile(file);
      emainw->PlayFile(fixifile);

  }
}

void Core_MainWindow::closeEvent(QCloseEvent *event) {
  emit Request_To_Close();
  event->ignore();
}

void Core_MainWindow::SetStatusText(const QString text) {
  CCDEBUG() << "Run: " << __FUNCTION__ << "-" << __FILE__ << ":" << __LINE__;
  statusbar->setText(text);
  emit Set_Tmp_File(QString("Stay cool please..."));
}

void Core_MainWindow::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);
  CCDEBUG() << "Run: " << __FUNCTION__ << "-" << __FILE__ << ":" << __LINE__;
  QRect screens = this->geometry();
  QSettings settings(_ORGANIZATION_NAME_, _PROGRAM_NAME_);
  settings.setValue("editor/width", screens.width());
  settings.setValue("editor/height", screens.height());
}
