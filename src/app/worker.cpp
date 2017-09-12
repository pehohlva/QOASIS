#include "worker.h"


ToWorker::ToWorker(QObject *parent) : QObject(parent) {
   loopcheks = 1000;
   cursor = pause;
   timer.start();
   process = new QProcess();
   status(); /// controll process.
}
/// enum workerstate { pause, running, killing, ending , timeoutrun  };
void ToWorker::blabering(const QString cmd , const QStringList args ) {
    timegos = 1;
    timer.start();
    cursor = running;
    complete = cmd + QString(" ") + args.join(" ");
    process = new QProcess();
    process->setReadChannel(QProcess::StandardOutput);
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->setProgram(cmd);
    process->setArguments(args);
    QObject::connect(process, SIGNAL(finished(int)), this, SLOT(ready(int)));
    process->open(QIODevice::ReadOnly);
    const int maxtimeset = (120 * 1000);
    if (!process->waitForFinished(maxtimeset)) {
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
  if (cursor != pause ) {
  emit ElapsedTimew(sec);
  WDEBUG() <<  loopcheks << " emitet time";
  }
  wakeup();
}

///    enum workerstate { pause, running, killing, ending };
void ToWorker::wakeup() {
    const int timeintervall = 500;
    if (cursor != pause ) {
    WDEBUG() <<  loopcheks << "workerstate -" << cursor << " time:" << timer.elapsed();
    }
    switch (cursor) {
    case pause: /// 0
        QTimer::singleShot(timeintervall, this, SLOT(status()));
        break;
    case running: //// 1
        QTimer::singleShot(timeintervall, this, SLOT(status()));
        break;
    case killing: //// 2
       if (  process->isOpen() ) {
           process->kill();
       }
       notice =result;
       result.clear();
        cleanEndAction();
        break;
    case timeoutrun: /// 4
        break;
    case ending: /// 3s
            notice =result;
            result.clear();
        /////WDEBUG() << fox <<   loopcheks << " wakeup end result - fix:" << (int)fox.unicode() << " time:" << timer.elapsed();
        cleanEndAction();
        break;
    default:
        qFatal("Fatal error on ToWorker::wakeup() file worker.cpp, report you usage here bevore, crash.");
        break;
    }

}

void ToWorker::cleanEndAction() {
     if (result.size() > 0) {
        QTextStream qout(stdout);
        qout <<  result;
     }
     emit JobWorkerEnd();
}


void ToWorker::ready(int id ) {
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
void VLoader::Setting( QObject *parent , const QString bcmd , QStringList barg )
{
    receiver = parent;
    xbcmd = bcmd;
    xbarg = barg;
    setTerminationEnabled(true);
}

void VLoader::run()
{
     WDEBUG() << "QThread run";
     voijob = new ToWorker();
     connect(voijob, SIGNAL(JobWorkerEnd()), receiver , SLOT(speechEnd()));
     connect(voijob, SIGNAL(ElapsedTimew(float)), receiver , SLOT(reportTime(float)));
     voijob->blabering(xbcmd,xbarg);
     exec();
}



