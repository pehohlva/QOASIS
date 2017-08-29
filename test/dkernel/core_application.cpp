#include "core_application.h"
#include <QDesktopWidget>
#include <QFile>
#include <QFileInfo>

#include "core_mainwindow.h"

Core_Application::Core_Application(int &argc, char **argv)
    : QApplication(argc, argv), modus_run(2) {
  log_intern = 100;
  QSettings settings(_ORGANIZATION_NAME_, _PROGRAM_NAME_);
  DownDir_RM(_ZIPCACHEBOOK_); //// remove chunk in test sandbox!
  mainw = new Core_MainWindow();
  mainw->setWindowTitle(_FIRSTWINDOWTITLESHOW_);
  mainw->activateWindow();
  QRect rall = QApplication::desktop()->availableGeometry();
  const qreal _wi = rall.width();
  const qreal _hi = rall.height();
  const qreal mawi_ = _wi - 300;
  const qreal mahi_ = _hi - 300;
  mainw->setMinimumWidth(mawi_);
  mainw->setMinimumHeight(mahi_);
  const qreal TopLeftisnow = (_wi / 2) - (mawi_ / 2);
  mainw->move(QPoint(TopLeftisnow, 0));
  Make_Test_File();
  connect(mainw, SIGNAL(Request_To_Close()), this, SLOT(Bevore_Quit()));
  connect(this, SIGNAL(FileOpenOrSet(QUrl)), mainw, SLOT(RequestPutFile(QUrl)));
  connect(this, SIGNAL(PlayMessage(QString)), mainw,
          SLOT(SetStatusText(QString)));
  connect(mainw, SIGNAL(Set_Tmp_File(QString)), this,
          SLOT(ParkingFile(QString)));

  QStringList in = this->arguments();
  for (int x = 0; x < in.count(); x++) {
    if (x > 1) {
      QFileInfo dig(in.at(x));
      if (dig.isFile()) {
        wait_filetoOpen << dig.absoluteFilePath();
      }
    }
  }
  /// give time to paint all gui... after launch file...
  QTimer::singleShot(2000, this, SLOT(CheksEventApp()));
}

void Core_Application::CheksEventApp() {
  CCDEBUG() << "Run: " << __FUNCTION__ << "-" << __FILE__ << ":" << __LINE__;
  log_intern++;
  if (wait_filetoOpen.size() > 0) {
    for (int x = 0; x < wait_filetoOpen.count(); x++) {
      ////// emit FileOpenOrSet(wait_filetoOpen.at(x));
    }
    wait_filetoOpen.clear();
  }
  if (modus_run == 2) {
    QDateTime Tloac = QDateTime::currentDateTime().toLocalTime();
    ///// CCDEBUG() << "Emit call: " << __FUNCTION__ << " - ";
    QString xday = Tloac.toString(Qt::SystemLocaleLongDate);
    mainw->SetStatusText(QString("Load: %1").arg(xday));
    QTimer::singleShot(1000, this, SLOT(CheksEventApp()));
  }
}

void Core_Application::Bevore_Quit() {
  QApplication::quit();
  return;
  CCDEBUG() << "Run: " << __FUNCTION__ << "-" << __FILE__ << ":" << __LINE__;
  QMessageBox::StandardButton resBtn = QMessageBox::question(
      mainw, _PROGRAM_NAME_, tr("Are you sure to quit?\n"),
      QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
      QMessageBox::Yes);
  const int permission = (int)resBtn;
  if (permission == 16384) {
    QApplication::quit();
    return;
  }
  emit PlayMessage(tr("Continue to work..."));
}

void Core_Application::ParkingFile(QString file) {
  CCDEBUG() << "Run: " << __FUNCTION__ << "-" << file << ":" << __LINE__;
  QFileInfo dig(file);
  if (dig.isFile()) {
    wait_filetoOpen << file;
  }
}

void Core_Application::closeEvent(QCloseEvent *event) {
  CCDEBUG() << "Run: " << __FUNCTION__ << "-" << __FILE__ << ":" << __LINE__;
  event->ignore();
  this->Bevore_Quit();
}

bool Core_Application::event(QEvent *event) {

  if (event->type() == QEvent::FileOpen) {
    // Get the path of the file that we want to open
    const QString file_path = static_cast<QFileOpenEvent *>(event)->file();
    const QUrl maconly_incomming = QUrl::fromLocalFile(file_path);
    mainw->RequestPutFile(maconly_incomming); //// QUrl
  } else {
    // The system requested us to do another thing, so we just follow the rules
    return QApplication::event(event);
  }
  return true;
}

void Core_Application::Make_Test_File() {
  QDir dira(_TESTBOOKS_);
  if (dira.mkpath(_TESTBOOKS_)) {
  } else {
    return;
  }
  const QString itemplay = QString("QtQuickApplicationGuide4Desktop.epub");
  QFile fister("://QtQuickApplicationGuide4Desktop.epub");
  QString destination = _TESTBOOKS_ + itemplay;
  QByteArray xchunk;
  if (fister.open(QFile::ReadOnly)) {
    xchunk = fister.readAll();
    fister.close();
  }
  CCDEBUG() << "xchunk.size() : " << xchunk.size();
  if (xchunk.size() > 1) {
    QFile f(destination);
    if (f.open(QIODevice::WriteOnly)) {
      f.write(xchunk);
      f.close();
    }
  }
  QFileInfo fi(destination);
  if (fi.exists()) {
    CCDEBUG() << " source give file : " << fi.absoluteFilePath();
    const QUrl lluri = QUrl::fromLocalFile(fi.absoluteFilePath());
    CCDEBUG() << " emit now QUrl : " << lluri;
    mainw->RequestPutFile(lluri); //// QUrl
  }
}
