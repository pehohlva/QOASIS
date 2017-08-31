#include "core_document.h"
#include "core_htmldriver.h"
#include <QTextDocumentWriter>


Document::Document(QObject *parent) : QObject(parent), d(new QTextDocument())
{

}

void Document::updateDocument( QSizeF sizex , qreal top , qreal bottom , qreal left , qreal right ) {

     QTextFrameFormat htmlformat = d->rootFrame()->frameFormat();
     if (sizex.width() < 3) {
        d->setPageSize(QSizeF(MM_TO_POINT(210), MM_TO_POINT(297)));
     } else {
        d->setPageSize(sizex);
     }
     const int fromtop = htmlformat.topMargin();
     if (top < 2 ) {
       htmlformat.setTopMargin(MM_TO_POINT(18));
     } else {
       htmlformat.setTopMargin(top);
     }
     if (bottom < 2 ) {
        htmlformat.setBottomMargin(MM_TO_POINT(35)); /// paint cut 30
     } else {
        htmlformat.setBottomMargin(bottom);
     }
     if (left < 2 ) {
         htmlformat.setLeftMargin(MM_TO_POINT(30));
     } else {
        htmlformat.setLeftMargin(left);
     }
     if (right < 2 ) {
         htmlformat.setRightMargin(MM_TO_POINT(25));
     } else {
        htmlformat.setRightMargin(right);
     }
     d->rootFrame()->setFrameFormat(htmlformat);
}

bool Document::d_save_toFilehtml( const QString file ) {
    const QString html = d->toHtml("UTF_8");
    return file_put_contents(file,html,1);
}

bool Document::d_save_toFileodt( const QString file ) {
    //// const QString html = d->toHtml("UTF_8");
    QTextDocumentWriter writer(file);
    return writer.write(d);
}

QTextCursor Document::cursor_doc() {
    QTextCursor curornow(d);
    curornow.setPosition(0,QTextCursor::MoveAnchor);
    return curornow;
}

QByteArray Document::to_html_compressd() {
    QByteArray xstream = QString(d->toHtml("UTF_8")).toUtf8();
    return qCompress(xstream,9);
}

QByteArray Document::to_html_utf8() {
    QByteArray xstream = QString(d->toHtml("UTF_8")).toUtf8();
    if (xstream.size() < 5) {
        return HTMLCHUNK;
    } else {
       return xstream;  //// only after 2Mb d-> is fanny!!!
    }
}

void Document::set_Html_compressed( const QByteArray html ) {
    HTMLCHUNK = html;
    qDebug()  << html.size() << " in Document::set_Html_compressed size!!!";
    QByteArray x = qUncompress(html);
    qDebug()  << x.size() << " in compressed size Document::set_Html_compressed !!!";
    d->setHtml(QString(x.constData()));
    QTextFrameFormat htmlformat = d->rootFrame()->frameFormat();
    if ( htmlformat.topMargin() < 4) {
        this->updateDocument();
    }
}
