#ifndef KERNEL_DOCUMENT_H
#define KERNEL_DOCUMENT_H

#include "kernel_load.h"
#include <QObject>

/*  Status 24.8.2017 can read & convert to html: rtf, rtfd , doc (theold binary) , webarchive safari odt,
    note odt direct to html is a better way not qtexdocument...
    todo epub in the next 2-3 day..
*/


class Document;
class Fastrambuffer;

class Kernel_Document : public QObject {
  Q_OBJECT
public:
  explicit Kernel_Document(QObject *parent = nullptr);
  bool Load(const QString file);
  bool rtf_test(const QString mime );
  bool rtfd_test(const QString mime ); /// super format on mac
  bool html_test(const QString mime );
  bool bindoc_test(const QString mime ); //// before docx xml!
  bool zipdoc_test(const QString mime ); /// to many format
  bool xmlall_test(const QString mime );

signals:
  void wait_loop(qreal);
public slots:
private:
  Document *d;
  Fastrambuffer *ram;
  QString namemd5;
  QString fullpathfile;
  QString filename;
  QString HandleNow;
  int FOUNDDOC;
};





#endif // KERNEL_DOCUMENT_H
