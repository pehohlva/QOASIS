/*
    Copyright (C)  2017 Piter K. <pehohlva@gmail.com>

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "oasi_application.h"
#include "doc_session.h"
#include "oasimain.h"

Oasi::Oasi(int &argc, char **argv) : QApplication(argc, argv) {
  QStringList path;
  const QString resfilewinunix = this->applicationDirPath();
  path << resfilewinunix;
#if defined Q_OS_MAC
  path.append(QApplication::applicationDirPath());
  QDir dir(QApplication::applicationDirPath());
  dir.cdUp();
  path.append(dir.absolutePath());
  dir.cd("plugins");
  path.append(dir.absolutePath());
  dir.cdUp();
  path.append(dir.absolutePath());
  dir.cd("Resources");
  const QString resfilemac = dir.absolutePath();
  path.append(dir.absolutePath());
  dir.cdUp();
  path.append(dir.absolutePath());
  dir.cdUp();
  path.append(dir.absolutePath());
  QApplication::setLibraryPaths(path);
  path << dir.absolutePath();
  QDir::setCurrent(dir.absolutePath()); /* here down -> Frameworks */
#endif
  const QString current_dir = QDir::currentPath();
  DOC::self(this)->setDir(current_dir); //// document session
  //// SESSDEBUG() << "### wake " << path;
  /// file list in linux here
  QCoreApplication::setOrganizationName(_BASICORG_);
  QCoreApplication::setOrganizationDomain(_BASICDOMAINE_);
  QCoreApplication::setApplicationName(_BASICTITLE_EDITOR_);
  mainwin = new OasiMain();
  mainwin->show();
  connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));
  connect(this, SIGNAL(signalFileOpen(QString)), mainwin,
          SLOT(appsOpen(QString))); //// mac
  connect(mainwin, SIGNAL(request_to_close()), this, SLOT(prepare_to_close()));

  QRect rall = QApplication::desktop()->availableGeometry();
  const qreal _wi = rall.width();
  const qreal _hi = rall.height();
  const qreal mawi_ = _wi - 300;
  const qreal mahi_ = _hi - 300;
  mainwin->setMinimumWidth(mawi_);
  mainwin->setMinimumHeight(mahi_);
  const qreal TopLeftisnow = (_wi / 2) - (mawi_ / 2);
  mainwin->move(QPoint(TopLeftisnow, 0));
  //// for linux & Window mac go fileevent
  QStringList filelist = this->arguments();
  for (int x = 0; x < filelist.size(); x++) {
    if (x != 0) {
      QFileInfo infi(filelist.at(x));
      if (infi.exists())
        mainwin->appsOpen(infi.absoluteFilePath());
    }
  }

  DOC::self(this)->installfont(true);
  const int uservoice = DOC::self(this)->value("MyVoicePref").toInt();
  qDebug() << "### init have voice " << uservoice;

}

void Oasi::prepare_to_close() {
  qDebug() << "### prepare_to_close";
  QMessageBox::StandardButton resBtn = QMessageBox::question(
      mainwin, _BASICTITLE_EDITOR_, tr("Are you sure to quit?\n"),
      QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
      QMessageBox::Yes);
  const int permission = (int)resBtn;
  if (permission == 16384) {
    DOC::self(this)->save();
    DOC::self(this)->installfont(false);
    QApplication::quit();
    return;
  }
}

/* only this class for mac drag file to icon in app status Dock  */
bool Oasi::event(QEvent *event) {
  if (event->type() == QEvent::FileOpen) {
    const QString file_path = static_cast<QFileOpenEvent *>(event)->file();
    emit signalFileOpen(file_path);
  } else {
    return QApplication::event(event);
  }
}

void Oasi::loginternal(QString log) {
  qDebug() << "### Oasi::loginternal >>" << log;
}
