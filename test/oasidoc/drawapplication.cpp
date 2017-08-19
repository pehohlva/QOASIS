#include "drawapplication.h"

DrawApplication::DrawApplication(int &argc, char **argv)
    : QApplication(argc, argv), strak(0.034), paintdoc(new DrawDocument()) {
  paintdoc->show();
  QApplication::setWheelScrollLines(4);

  cookie = new DocSession(this);
  paintdoc->setSession(cookie);
}

/// osx  mac drag file to icon here to open file..
bool DrawApplication::event(QEvent *event) {
  qDebug() << "### Application event... " << event->type();
  return QApplication::event(event);
  //// this->grabGesture(Qt::SwipeGesture, Qt::ReceivePartialGestures);
}

void DrawApplication::closeEvent(QCloseEvent *event) {
  event->ignore();
  prepare_to_close();
}

void DrawApplication::prepare_to_close() {
  QMessageBox::StandardButton resBtn = QMessageBox::question(
      0, tr("Speacker"), tr("Are you sure to quit?\n"),
      QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
      QMessageBox::Yes);
  const int permission = (int)resBtn;
  if (permission == 16384) {
    /// remove all tmp item ///
    QApplication::quit();
    return;
  }
  /// emit internal_L(tr("Continue to Speack..."));
}
