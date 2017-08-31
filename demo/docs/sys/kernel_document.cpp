#include "kernel_document.h"
#include "kernel_load.h"
#include "fastrambuffer.h"
#include "core_htmldriver.h"
#include <QDebug>
#include "core_document.h"
#include "docformat/ooo/converter.h"


Kernel_Document::Kernel_Document(QObject *parent)
    : QObject(parent), d(new Document), ram(new Fastrambuffer)
{
    FOUNDDOC =0;
    namemd5 = QStringLiteral("dummy");
    /// start here
}

QByteArray Kernel_Document::to_Html() {
    return d->to_html_utf8();
}

bool Kernel_Document::Load(const QString file)
{
    FILEFULLNOTTOUCH = file;
   if (ram->load_file(file)) {
    fullpathfile = ram->FullPath();
    filename = ram->FileName();
    HandleNow = FILEFULLNOTTOUCH;
    d->qt_doc()->setBaseUrl(QUrl(file));
     const QByteArray chunk = ram->stream();
     QString Mime = ram->mimeType();
     const qint64 kbs =  ram->size_chunk();
     qDebug()  << Mime << "-kb." << BytesRead(kbs) << " -> doc size" << file << " - ";
     if ( kbs < 1) {
        return false;
     } else {

         this->rtfd_test(Mime);

         if ( kbs > 20 &&  kbs < megalimit ) {

             this->rtfd_test(Mime);
             this->rtf_test(Mime);
             this->html_test(Mime);
             this->bindoc_test(Mime);
             this->xmlall_test(Mime);
             this->zipdoc_test(Mime); /// zip at end
         }
     }
   }
  qDebug()  << file << " -> end if html size > ok...";
  return true;
}


bool Kernel_Document::xmlall_test(const QString mime ) {
    if (FOUNDDOC == 1) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
    //// only xml douments a long work...
   if (mime.contains("application/x") && ram->isValidXml() ) {
    qDebug()  << __FUNCTION__ << " found.";
    FOUNDDOC =0;
    }
    return false;
}


bool Kernel_Document::zipdoc_test(const QString mime ) {

     QByteArray dwoline = ram->stream().mid(0,11);
     qDebug()  << dwoline << " ->  zip" << __FUNCTION__;

     if (FOUNDDOC == 1) {
         return false;
     }

    if (ram->size_chunk() < 3) {
       return false;
    }
    HtmlDriver *xhtml = new HtmlDriver();
   if (mime.contains(".oasis.") ) {
    //// qDebug()  << dwoline << " -> dwoline zip";
    qDebug()  << __FUNCTION__ << " found.";
              if (HandleNow.endsWith(".odt") || HandleNow.endsWith(".ott")  ) {
                OOO::Converter *doc_odt = new OOO::Converter();
                QString htmlchunk; /// fill variable ...
                int summoftableinside = 0; /// fill variable ...
                doc_odt->convert(HandleNow,htmlchunk,summoftableinside); /// bugs if to many table!!!
                doc_odt->~Converter();
                if (htmlchunk.size() > 11 && summoftableinside < 3) {
                    d->qt_doc()->setHtml(htmlchunk);
                    if ( d->to_html_utf8().size() > 3 ) {
                        FOUNDDOC = 1;
                        return true;
                    }
                    ///// return file_put_contents("xxodt1.html",htmlchunk,1);
                } else {
                    //// to many table inside document... use other lib!!
                     if ( xhtml->is_text_tool() ) {
                         xhtml->rtfd_to_html(HandleNow); /// if is not rtfd it lost images!!!
                         d->set_Html_compressed(xhtml->results_htmlgz());
                         xhtml->~HtmlDriver();
                         //// return d->d_save_toFilehtml("xxodt2.html");
                         if ( d->to_html_utf8().size() > 3 ) {
                             FOUNDDOC = 1;
                             return true;
                         }
                      }
                }

    }

    return false;
    }
    return false;
}

bool Kernel_Document::rtf_test(const QString mime ) {
    if (FOUNDDOC == 1) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
    ///// QByteArray firstline = ram->stream().mid(0,11);
   if (mime.contains("rtf")) {
       HtmlDriver *xhtml = new HtmlDriver();
        xhtml->rtfd_to_html(HandleNow); /// convert e send back ...
        const QByteArray recHTML = xhtml->results_htmlgz(); /// compressed...
        xhtml->~HtmlDriver();
        if (recHTML.size() > 1 ) {
        d->set_Html_compressed(recHTML);
        qDebug()  << __FUNCTION__ << " !!!!!!!!!  found.";
            if ( d->to_html_utf8().size() > 3 ) {
                FOUNDDOC = 1;
                return true;
            }
        }
   }
    return false;
}

/* only a mac format! is a dir inode and data... */
bool Kernel_Document::rtfd_test(const QString mime ) {
    if (FOUNDDOC == 1) {
        return false;
    }
    if (ram->size_chunk() < 1) {
       return false;
    }
    qDebug()  << __FUNCTION__ << " go up ";
    /// only textutil open this file !
   if (mime.contains("inod") ) {  //// like a dir or stream rtfd format
       HtmlDriver *xhtml = new HtmlDriver();
        xhtml->rtfd_to_html(HandleNow); /// convert e send back ...
        const QByteArray recHTML = xhtml->results_htmlgz(); /// compressed...
        qDebug()  << recHTML.size() << " size end!!! 170";
        xhtml->~HtmlDriver();
        d->set_Html_compressed(recHTML);
        if ( d->to_html_utf8().size() > 3 ) {
            FOUNDDOC = 1;
            return true;
        }
   }
    qDebug()  << __FUNCTION__ << " go end!!!!! ";
    return false;
}





bool Kernel_Document::bindoc_test(const QString mime ) {
    if (FOUNDDOC == 1) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
   if (mime.contains("/msword") && filename.contains(".doc") && !filename.contains(".docx")) {
     qDebug()  << __FUNCTION__ << " found.";
     HtmlDriver *xhtml = new HtmlDriver();
      xhtml->rtfd_to_html(HandleNow); /// convert e send back ...
      const QByteArray recHTML = xhtml->results_htmlgz(); /// compressed...
      xhtml->~HtmlDriver();
      d->set_Html_compressed(recHTML);
      ///// d->d_save_toFilehtml("xxrtfd.html");
     if ( d->to_html_utf8().size() > 3 ) {
          FOUNDDOC = 1;
          return true;
      }
   }
    return false;
}

bool Kernel_Document::html_test(const QString mime ) {
    if (FOUNDDOC == 1) {
        return false;
    }
    if (ram->size_chunk() < 3) {
       return false;
    }
   QByteArray dwoline = ram->stream().mid(0,30);
   if (mime.contains("/html") && dwoline.contains("/W3C")) {
    qDebug()  << __FUNCTION__ << " found.";
    d->qt_doc()->setHtml(ram->data()); /// take image if load or check..
    FOUNDDOC =1;
    return true;
   }
    return false;
}







