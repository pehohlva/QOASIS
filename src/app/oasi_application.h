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
#ifndef OASI_APPLICATION_H
#define OASI_APPLICATION_H

#include "doc_session.h"
#include "editorkernel.h"
#include "oasimain.h"
#include <QApplication>
#include <QCoreApplication>

#define oasi (static_cast<Oasi *>(QCoreApplication::instance()))

class Oasi : public QApplication {
  Q_OBJECT
public:
  explicit Oasi(int &argc, char **argv);
  bool event(QEvent *event);

signals:
  void eventLog(QString);
  void signalFileOpen(QString);

public slots:
  void prepare_to_close();
  void loginternal(QString log);

private:
  OasiMain *mainwin;
  QString current_dir;
};

#endif // OASI_APPLICATION_H
