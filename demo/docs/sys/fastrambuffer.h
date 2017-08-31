#ifndef FASTRAMBUFFER_H
#define FASTRAMBUFFER_H

#include "kernel_load.h"



extern inline QString run_which( QString apps = QString("gs") )
{
    QStringList potential_paths;
    potential_paths.append("/usr/bin");
    potential_paths.append("/usr/local/bin");
    potential_paths.append("/sw/bin");   /* to use on mac as same */
    potential_paths.append("/opt/bin");
    QProcess *process = new QProcess(NULL);
    process->setReadChannelMode(QProcess::MergedChannels);
    QStringList env = process->systemEnvironment();
    env.replaceInStrings(QRegExp("^PATH=(.*)", Qt::CaseInsensitive), "PATH=\\1;"+potential_paths.join(";"));
    process->setEnvironment(env);

        process->start( QString("which") ,  QStringList() << apps , QIODevice::ReadOnly );
          if (!process->waitForFinished()) {
          return QString();
          } else {
              QString finder = process->readAll().trimmed();
              if (finder.endsWith(apps,Qt::CaseInsensitive)) {
                 ///// qDebug() << "### finder which............................ " <<  finder;
                return finder;
              } else {
                return QString();
              }
          }
}





/* limit 5mb file for sped max superram todo? */
class Fastrambuffer {
public:
  Fastrambuffer();
    ~Fastrambuffer() {
      x->close(); // close buffer! or clear() to take other file
    }
  bool load_file(const QString file);
  bool PutOnFile(const QString file);
  qint64 size_chunk() { return x->bytesAvailable(); }
  QString tohtmlsimulate();
  QString mimeType() { return mime; }
  bool isValidXml() { return doc.setContent(stream(),false,0,0,0);  }
  QString FullPath() { return absolutepathfromfile; }
  QString FileName() { return filename; }
  QString strip_tag(QString txt);
  bool clear();
  QIODevice *device();
  QByteArray stream();
  QString data();
  QBuffer *x;
  QDomDocument doc;
  QString mime;
  qint64 FcurrentSize; /// file size =!
  qint64 ScurrentSize; /// size_chunk()
  QString absolutepathfromfile;
  QString filename;
};
















#endif // FASTRAMBUFFER_H
