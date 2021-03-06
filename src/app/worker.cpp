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
#include "worker.h"

ToWorker::ToWorker(QObject *parent) : QObject(parent) {
  loopcheks = 1000;
  cursor = pause;
  timer.start();
  process = new QProcess();
  status(); /// controll process.
}


void ToWorker::killFastnow() {
    WDEBUG() << __FUNCTION__;
    if (process) {
        WDEBUG() << __FUNCTION__ << "kill2";
        process->waitForFinished(10);
        this->deleteLater();
    }
}
/// enum workerstate { pause, running, killing, ending , timeoutrun  };
void ToWorker::blabering(const QString cmd, const QStringList args) {
  timegos = 1;
  timer.start();
  cursor = running;
  complete = cmd + QString(" ") + args.join(" ");
  process = new QProcess();
  process->setReadChannel(QProcess::StandardOutput);
  process->setProcessChannelMode(QProcess::MergedChannels);
  process->setProgram(cmd);
  process->setArguments(args);
  QObject::connect(VoiceBlock::self(this), SIGNAL(detroyVoice()), this, SLOT(deleteLater()));
  QObject::connect(process, SIGNAL(finished(int)), this, SLOT(ready(int)));
  process->open(QIODevice::ReadOnly);
  //// const int maxtimeset = (60 * 60  * 1000); no time out
  if (!process->waitForFinished(-1)) {
    result = process->readAll();
    result.prepend("-");
    cursor = ending;
  } else {
    result = process->readAll();
    result.prepend("|");
    cursor = ending;
  }
}

void ToWorker::status() {
  loopcheks++;
  const float sec = timer.elapsed() / 1000;
  if (cursor != pause) {
    emit ElapsedTimew(sec);
    WDEBUG() << loopcheks << " emitet time";
  }
  wakeup();
}

///    enum workerstate { pause, running, killing, ending };
void ToWorker::wakeup() {
  const int timeintervall = 500;
  if (cursor != pause) {
    WDEBUG() << loopcheks << "workerstate -" << cursor
             << " time:" << timer.elapsed();
  }
  switch (cursor) {
  case pause: /// 0
    QTimer::singleShot(timeintervall, this, SLOT(status()));
    break;
  case running: //// 1
    QTimer::singleShot(timeintervall, this, SLOT(status()));
    break;
  case killing: //// 2
    if (process->isOpen()) {
      process->kill();
    }
    notice = result;
    result.clear();
    cleanEndAction();
    break;
  case timeoutrun: /// 4
    break;
  case ending: /// 3s
    notice = result;
    result.clear();
    /////WDEBUG() << fox <<   loopcheks << " wakeup end result - fix:" <<
    ///(int)fox.unicode() << " time:" << timer.elapsed();
    cleanEndAction();
    break;
  default:
    qFatal("Fatal error on ToWorker::wakeup() file worker.cpp, report you "
           "usage here bevore, crash.");
    break;
  }
}

void ToWorker::cleanEndAction() {
  if (result.size() > 0) {
    QTextStream qout(stdout);
    qout << result;
  }
  emit JobWorkerEnd();
}

void ToWorker::ready(int id) {
  Q_UNUSED(id);
  if (cursor != cleanend) {
    wakeup();
    return;
  }
}
void ToWorker::stop() {
  cursor = killing;
  wakeup();
}

QByteArray ToWorker::results() {
  QByteArray tmp = notice;
  notice.clear();
  return tmp;
}
QString ToWorker::lastAction() {
  QString tmp = complete;
  complete.clear();
  return tmp;
}

////  QThread here
void VLoader::Setting(QObject *parent, const QString bcmd, QStringList barg) {
  receiver = parent;
  xbcmd = bcmd;
  xbarg = barg;
  setTerminationEnabled(true);
}

void VLoader::run() {
  WDEBUG() << "QThread run";
  voijob = new ToWorker();
  connect(voijob, SIGNAL(JobWorkerEnd()), receiver, SLOT(speechEnd()));
  connect(voijob, SIGNAL(ElapsedTimew(float)), receiver, SLOT(reportTime(float)));
  QObject::connect(VoiceBlock::self(this), SIGNAL(detroyVoice()), voijob, SLOT(killFastnow()));
  voijob->blabering(xbcmd, xbarg);
  exec();
}
