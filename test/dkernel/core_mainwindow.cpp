#include "core_mainwindow.h"

#include <QAction>
#include <QComboBox>
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
  statusbar->setFixedWidth(255);
  epub_pages = new QComboBox(this);
  epub_pages->hide();
  sta->addWidget(statusbar); /// append progressbar from load
  sta->addWidget(epub_pages);
  this->setMenuBar(menubarre);
  this->setStatusBar(sta);
  //// epub_pages
  //// void	highlighted(int index)
  connect(epub_pages, SIGNAL(currentIndexChanged(int)), this,
          SLOT(NavitoepubPage(int)));
  fileMenu = menubarre->addMenu(tr("&File"));
  QAction *act_file_open = new QAction(tr("Open Fake File"), this);
  act_file_open->setShortcut(QKeySequence(QKeySequence::Open));
  connect(act_file_open, SIGNAL(triggered()), this, SLOT(SetBookorFile()));
  ///// connect(act_file_open, SIGNAL(triggered()), this, SLOT(SetBookorFile()));
  fileMenu->addAction(act_file_open);
  /* ---------------------------------------- */
  emainw = new EpubView(this);
  setCentralWidget(emainw);
  emainw->hide(); /// load all before...
  /* ---------------------------------------- */
  connect(emainw, SIGNAL(PaintMenuEpub(bool)), this, SLOT(ComboEpubWake(bool)));
  SetStatusText(QString("End .. Loading... "));
  this->show();
}

void Core_MainWindow::RequestPutFile(QUrl uri) {
  CCDEBUG() << "signal in here->: " << __FUNCTION__ << "-" << uri << ":"
            << __LINE__;
  QFileInfo xfi(uri.toLocalFile());
  if (xfi.exists()) {
    this->CheckeOpenFile(xfi.absoluteFilePath());
  } else {
    Check_Visible_Engine(true);
    emainw->JumpEpub(uri); /// www
  }
}

void Core_MainWindow::SetBookorFile() {

    QSettings settings(_ORGANIZATION_NAME_, _PROGRAM_NAME_);
    QString dirlast = settings.value("books/lastdir_open").toString();
    QVariantList lastfiles = settings.value("books/files/db").toList();
        if (dirlast.size() ==0) {
              dirlast = QDir::homePath();
              ///// QFileDialog::DontUseNativeDialog
        }
  QString file = QFileDialog::getOpenFileName(Q_NULLPTR, QString("Choose File..."),dirlast,
                                              "*",Q_NULLPTR, QFileDialog::HideNameFilterDetails);

  if (file.isEmpty()) {
    return;
  } else {
     QFileInfo iox(file);
     lastfiles.append(QVariant(iox.absoluteFilePath()));
     settings.setValue("books/files/db",lastfiles);
     settings.setValue("books/lastdir_open",QVariant(iox.absolutePath()));
     this->CheckeOpenFile(iox.absoluteFilePath());
  }
}


void Core_MainWindow::CheckeOpenFile(const QString file) {
  QString text = QString("Open: %1").arg(file);
  QFileInfo fix(file);
  QUrl fixifile = QUrl::fromLocalFile(file);
  CCDEBUG() << " fix.completeSuffix() " << fix.completeSuffix();
  if (fix.completeSuffix() == QString("epub") ) {
      emainw->OpenEpub(fixifile);
      statusbar->setText(text);
      return;
  } else {

     if (fix.completeSuffix() == QString("xhtml") ||
               fix.completeSuffix() == QString("html") ||
                   fix.completeSuffix() == QString("xml")) {
         epub_pages->clear();
         epub_pages->hide();
         emainw->JumpEpub(fixifile);
         return;
     }

      QByteArray chunk;
      QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
      uint unixtime = currentDateTime.toTime_t();
      QString newfile = _TESTBOOKS_ + QString("%1.html").arg(unixtime);
      QUrl fixifileA = QUrl::fromLocalFile(newfile);
      // can write in _TESTBOOKS_
      Kernel_Document *doc = new Kernel_Document();
           if (doc->Load(file)) {
             chunk=doc->to_Html();
             if (chunk.size() > 1 ) {
                  if (file_put_contents(newfile,QString(chunk.constData()))) {
                     epub_pages->clear();
                     epub_pages->hide();
                     emainw->JumpEpub(fixifileA);
                     return;
                  }
             }
           }
  }
}

/*    QByteArray to_html_compressd();
    QByteArray to_html_utf8();  */


void Core_MainWindow::closeEvent(QCloseEvent *event) {
  emit Request_To_Close();
  event->ignore();
}

void Core_MainWindow::SetStatusText(const QString text) {
  statusbar->setText(text);
}

void Core_MainWindow::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);
  ///// CCDEBUG() << "Run: " << __FUNCTION__ << "-" << __FILE__ << ":" << __LINE__;
  QRect screens = this->geometry();
  QSettings settings(_ORGANIZATION_NAME_, _PROGRAM_NAME_);
  settings.setValue("editor/width", screens.width());
  settings.setValue("editor/height", screens.height());
  QMainWindow::resizeEvent(event);
}

void Core_MainWindow::NavitoepubPage(int x) {
  Check_Visible_Engine(true);
  QVariant urijump = epub_pages->itemData(x);
  QString gofile = urijump.toString();
  if (!gofile.isEmpty()) {
      QUrl openuri;
      QFileInfo xfi(gofile);
      if (xfi.exists()) {
        openuri = QUrl::fromLocalFile(gofile);
      } else {
        openuri = QUrl(gofile);
      }
    emainw->JumpEpub(openuri);
    SetStatusText(QString("Render Page: %1").arg(epub_pages->currentText()));
  }
}

void Core_MainWindow::Check_Visible_Engine( bool e) {
    Q_UNUSED(e); /// if must play other widged...
    if (emainw->isHidden() ) {
        emainw->show();
    }
}

void Core_MainWindow::ComboEpubWake(bool e) {
  if (e) {
    epub_pages->clear();
    this->Check_Visible_Engine(true);
    QList<EpubToc> tocep = emainw->RenderMenu();
    if (tocep.size() > 0) {
      for (int x = 0; x < tocep.size(); x++) {
        EpubToc fox = tocep.at(x);
        ///// CCDEBUG() << "combo in " << fox.title << ":" << fox.jumpurl;
        QFileInfo foxa(fox.jumpurl);
        if (foxa.exists()) {
          int homeorder = 1 + fox.orderid;
          epub_pages->addItem(QString("%1) Local Book: - %2").arg(homeorder).arg(fox.title),
                              QVariant(foxa.absoluteFilePath()));
        }
      }

    }
    epub_pages->addItem(QString("Online: - Google.com"),QVariant(QString("https://www.google.ch/")));
    epub_pages->show();
  } else {
    epub_pages->hide();
  }
}
