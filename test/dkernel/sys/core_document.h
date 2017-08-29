#ifndef CORE_DOCUMENT_H
#define CORE_DOCUMENT_H

#include <QObject>
#include "kernel_load.h"
#include "fastrambuffer.h"


class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(QObject *parent = nullptr);
    void updateDocument( QSizeF size = QSizeF(0,0) , qreal top =0 , qreal bottom =0 , qreal left=0 , qreal right=0 );
    QTextCursor cursor_doc();
    bool d_save_toFilehtml( const QString file );
    bool d_save_toFileodt( const QString file );
    QTextDocument * qt_doc() {
        return d;
    }
    void set_Html_compressed( const QByteArray html );
    QByteArray to_html_compressd();
    QByteArray to_html_utf8();
signals:

public slots:
private:
    QTextDocument *d;
    QByteArray HTMLCHUNK;
};

#endif // CORE_DOCUMENT_H
