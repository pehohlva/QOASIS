#include "kernel_document.h"
#include "kernel_load.h"
#include "fastrambuffer.h"
#include "core_htmldriver.h"
#include <QDebug>
#include "core_document.h"

Kernel_Document::Kernel_Document(QObject *parent)
    : QObject(parent), d(new Document), ram(new Fastrambuffer)
{
    FOUNDDOC =0;
    namemd5 = QStringLiteral("dummy");
    /// start here
}

bool Kernel_Document::Load(const QString file)
{
   if (ram->load_file(file)) {
    fullpathfile = ram->FullPath();
    filename = ram->FileName();
    HandleNow = fullpathfile + QString("/") +  file;
    d->qt_doc()->setBaseUrl(QUrl(fullpathfile));
    qDebug()  << HandleNow << "=file doc size";
     const QByteArray chunk = ram->stream();
     const qint64 kbs =  ram->size_chunk();
     qDebug()  << BytesRead(kbs) << " -> doc size" << filename << " - ";
     if ( kbs < 20) {
        return false;
     } else {

         if ( kbs > 20 &&  kbs < megalimit ) {
             QString Mime = ram->mimeType();
             this->rtf_test(Mime);
             this->html_test(Mime);
             this->bindoc_test(Mime);
             this->xmlall_test(Mime);
             this->rtfd_test(Mime);
             this->zipdoc_test(Mime); /// zip at end
             //// now fill doument if you can..s
             return true;
             emit wait_loop(1);
         }
     }
   }
  qDebug()  << file << " -> end check..";
  return false;
}


bool Kernel_Document::xmlall_test(const QString mime ) {
    if (FOUNDDOC !=0) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
   if (mime.contains("application/x") && ram->isValidXml() ) {
    qDebug()  << __FUNCTION__ << " found.";
    FOUNDDOC =1;
    return true;
    }
    return false;
}


bool Kernel_Document::zipdoc_test(const QString mime ) {
    if (FOUNDDOC !=0) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
   QByteArray dwoline = ram->stream().mid(0,2);
   if (mime.contains("application/") && dwoline == QByteArray("PK")) {
    ///// qDebug()  << dwoline << " -> dwoline zip";
    qDebug()  << __FUNCTION__ << " found.";
    if (HandleNow.endsWith(".odt") ) {

    }

    return true;
    }
    return false;
}

bool Kernel_Document::rtf_test(const QString mime ) {
    if (FOUNDDOC !=0) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
    QByteArray firstline = ram->stream().mid(0,11);
   if (mime.contains("/rtf") && firstline.contains("rtf1")) {
       HtmlDriver *xhtml = new HtmlDriver();
        xhtml->rtfd_to_html(HandleNow); /// convert e send back ...
        const QByteArray recHTML = xhtml->results_htmlgz(); /// compressed...
        xhtml->~HtmlDriver();
        if (recHTML.size() > 1 ) {
        d->set_Html_compressed(recHTML);
        d->d_save_toFilehtml("xxrtf.html");
        }
        //// insert rtf lib rtf to html
    /// qDebug()  << dwoline << " -> dwoline";
    qDebug()  << __FUNCTION__ << " found.";
    FOUNDDOC =1;
    return true;
   }
    return false;
}

/* only a mac format! is a dir inode and data... */
bool Kernel_Document::rtfd_test(const QString mime ) {
    if (FOUNDDOC !=0) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
    /// only textutil open this file !
   if (mime.contains("inode/") ) {  //// like a dir or stream rtfd format
       HtmlDriver *xhtml = new HtmlDriver();
        xhtml->rtfd_to_html(HandleNow); /// convert e send back ...
        const QByteArray recHTML = xhtml->results_htmlgz(); /// compressed...
        xhtml->~HtmlDriver();
        d->set_Html_compressed(recHTML);
        d->d_save_toFilehtml("xxrtfd.html");
    qDebug()  << __FUNCTION__ << " found. size->"   <<  recHTML.size();
    FOUNDDOC =1;
    return true;
   }
    return false;
}





bool Kernel_Document::bindoc_test(const QString mime ) {
    if (FOUNDDOC !=0) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
   //// 0M8R4A==
   //// QByteArray dwoline = ram->stream().mid(0,4);
   /// QByteArray first = dwoline.toBase64();
   if (mime.contains("/msword") && filename.contains(".doc") && !filename.contains(".docx")) {
     qDebug()  << __FUNCTION__ << " found.";
     FOUNDDOC =1;
    return true;
   }
    return false;
}

bool Kernel_Document::html_test(const QString mime ) {
    if (FOUNDDOC !=0) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
   QByteArray dwoline = ram->stream().mid(0,30);
   if (mime.contains("/html") && dwoline.contains("/W3C")) {
    qDebug()  << __FUNCTION__ << " found.";
    //// d->setHtml(ram->data()); /// take image if load or check..
    FOUNDDOC =1;
    return true;
   }
    return false;
}







