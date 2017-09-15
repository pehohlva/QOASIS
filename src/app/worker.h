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
#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include "doc_session.h"
#include <QByteArray>
#include <QDebug>
#include <QElapsedTimer>
#include <QProcess>
#include <QString>
#include <QTextStream>
#include <QThread>
#include <QTimer>
#include <QtCore/QCoreApplication>

#if 0 //// 1 or 0
#define WDEBUG qDebug
#define WORKERT 1
#define _wtdebuglogfile_                                                       \
  QString("/Volumes/dati/sandbox/Tiny_Edit/src/worker_log.txt")
#else
#define WDEBUG                                                                 \
  if (0)                                                                       \
  QNoDebug
#define WORKERT 0
#define _wtdebuglogfile_ QString("")
#endif

class ToWorker : public QObject {
  Q_OBJECT

public:
  enum workerstate { pause, running, killing, ending, timeoutrun, cleanend };
  explicit ToWorker(QObject *parent = nullptr);
  void blabering(const QString cmd, const QStringList args);
  void stop();
  QByteArray results();
  QString lastAction();
signals:
  void ElapsedTimew(float);
  void JobWorkerEnd();
public slots:
  void ready(int);
  void status();
  void cleanEndAction();

private:
  workerstate cursor;
  void wakeup();
  QProcess *process;
  qint64 timegos; /// = 0;
  qint64 timeafter;
  QElapsedTimer timer;
  qint64 loopcheks;
  QByteArray result;
  QByteArray notice;
  QString complete;
};

/*  usage:
Gloader *singing = new VLoader();
singing->Setting(this,cmd,argument);
singing->start(QThread::LowPriority);
on slot incomming
ToWorker *ht = qobject_cast<ToWorker *>(sender());
read data..
*/

class VLoader : public QThread {
  Q_OBJECT

public:
  void Setting(QObject *parent, const QString bcmd, QStringList barg);

protected:
  void run();
signals:
private:
  QString xbcmd;
  ToWorker *voijob;
  QStringList xbarg;
  QObject *receiver;
};

#endif // WORKER_H
