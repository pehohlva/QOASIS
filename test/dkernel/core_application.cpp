#include "core_application.h"
#include <QDesktopWidget>
#include <QFile>
#include <QFileInfo>

#include "core_mainwindow.h"

Core_Application::Core_Application(int &argc, char **argv)
    : QApplication(argc, argv), modus_run(2) {
  log_intern = 100;
  DownDir_RM(_ZIPCACHEBOOK_); //// remove chunk in test sandbox!
  mainw = new Core_MainWindow();
  mainw->setWindowTitle(_FIRSTWINDOWTITLESHOW_);
  mainw->activateWindow();
  QRect rall = QApplication::desktop()->availableGeometry();
  const qreal _wi = rall.width();
  const qreal _hi = rall.height();
  const qreal mawi_ = _wi - 150;
  const qreal mahi_ = _hi - 50;
  mainw->setMinimumWidth(mawi_);
  mainw->setMinimumHeight(mahi_);
  const qreal TopLeftisnow = (_wi / 2) - (mawi_ / 2);
  //// CCDEBUG() << "width: " << mawi_;
  //// CCDEBUG() << "height: " << mahi_;
  mainw->move(QPoint(TopLeftisnow,0));
  connect(mainw, SIGNAL(Request_To_Close()), this, SLOT(Bevore_Quit()));
  connect(this, SIGNAL(FileOpenOrSet(QString)),mainw,SLOT(RequestPutFile(QString)));
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
      emit FileOpenOrSet(wait_filetoOpen.at(x));
    }
    wait_filetoOpen.clear();
  }
  if (modus_run == 2) {
    CCDEBUG() << "Emit call: " << __FUNCTION__ << " - ";
    mainw->SetStatusText(QString("Run sequence .. Wait %1.. ").arg(log_intern));
    QTimer::singleShot(1000 * 180, this, SLOT(CheksEventApp()));
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
    mainw->RequestPutFile(file_path);
  } else {
    // The system requested us to do another thing, so we just follow the rules
    return QApplication::event(event);
  }
  return true;
}
