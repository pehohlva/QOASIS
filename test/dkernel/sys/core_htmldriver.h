#ifndef CORE_HTMLDRIVER_H
#define CORE_HTMLDRIVER_H

#include "kernel_load.h"
#include "fastrambuffer.h"

//// like on php
bool file_put_contents(const QString fullFileName, QString xml , int modus = 1);
QString readfile(const QString fullFileName );
bool is_text_tool();
bool is_file(const QString fullFileName);
bool unlink(const QString fullFileName);
bool copy(const QString inputfile, const  QString outfile);
void DownDir_RM(const QString d);
/* encode to name pics file ... */
QString encodeBase64( QString xml );
QString encodeBase64( QByteArray chunk );
/* decode to name pics file ...  */
QString decodeBase64( QString xml );
QString decodeBase64( QByteArray chunk );
/* check if a int or float nummer */
bool is_numeric(QString incomming);

// by error no image insert pix image transparent
#define __ONEPIXELGIF__ \
              QString("data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==")

#define CACHEBUFFERDISKTMP\
               QString( "%1/.kernelversion" ).arg(QDir::homePath())

#define CACHEFILETMP\
               QString( "%1/index.html" ).arg(CACHEBUFFERDISKTMP)

class HtmlDriver
{
public:
    HtmlDriver();
    ~HtmlDriver();
    bool is_text_tool();
    void clean_cache();
    void rtfd_to_html( const QString file );
    void disk_textutils( const QString file );
    /*  qCompress qUncompress  */
    QByteArray results_htmlgz() {
        return HTMLCOMPRESSED;
    }

private:
    void image_find( QString html ); /// resolve image!
    QByteArray pic_encode( QImage im );
    QString fullhtmlnow;
    QString txtutils;
    int cacheop;
    QByteArray HTMLCOMPRESSED;
};

#endif // CORE_HTMLDRIVER_H
