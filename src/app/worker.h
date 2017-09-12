#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QByteArray>
#include <QString>
#include <QProcess>
#include <QElapsedTimer>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include "doc_session.h"

#if 0 //// 1 or 0
#define WDEBUG qDebug
#define WORKERT 1
#define _wtdebuglogfile_                                                         \
  QString("/Volumes/dati/sandbox/Tiny_Edit/src/worker_log.txt")
#else
#define WDEBUG                                                              \
  if (0)                                                                       \
  QNoDebug
#define WORKERT 0
#define _wtdebuglogfile_   QString("")
#endif


class ToWorker : public QObject
{
    Q_OBJECT

public:
    enum workerstate { pause, running, killing, ending , timeoutrun, cleanend  };
    explicit ToWorker(QObject *parent = nullptr);
    void blabering(const QString cmd, const QStringList args );
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

class VLoader : public QThread
{
    Q_OBJECT

public:
  void Setting( QObject *parent , const QString bcmd , QStringList barg );
protected:
  void run();
  signals:
private:
    QString xbcmd;
    ToWorker *voijob;
    QStringList xbarg;
    QObject* receiver;
};














#endif // WORKER_H
