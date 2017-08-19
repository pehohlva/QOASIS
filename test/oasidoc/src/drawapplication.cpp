#include "drawapplication.h"

DrawApplication::DrawApplication(int &argc, char **argv)
    : QApplication(argc, argv), strak(0.034) {
  DrawDocument *xx = new DrawDocument();
  xx->show();
  QApplication::setWheelScrollLines(4);
  //// QApplication::setKeypadNavigationEnabled(true);
}

bool DrawApplication::event(QEvent *event) {
  strak = strak + 0.11;
  if (event->type() == QEvent::TabletEnterProximity ||
      event->type() == QEvent::TabletLeaveProximity) {
    /// qDebug() << strak <<  "### TabletEnterProximity >>  " <<
    /// (int)event->type();
  } else {
    //// qDebug() << strak <<  "### TabletEnterProximity >>  " <<
    ///(int)event->type();
  }
  return QApplication::event(event);
}

void DrawApplication::prepare_to_close() {
  qDebug() << "### prepare_to_close";
  QMessageBox::StandardButton resBtn = QMessageBox::question(
      0, tr("Speacker"), tr("Are you sure to quit?\n"),
      QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
      QMessageBox::Yes);
  const int permission = (int)resBtn;
  if (permission == 16384) {
    QApplication::quit();
    return;
  }
  emit internal_L(tr("Continue to Speack..."));
}
