/* 
 * File:   converter.h
 * Author: pro
 *
 * Created on 24. Oktober 2013, 14:26
 */

#ifndef CONVERTER_H
#define	CONVERTER_H


#include <QtGui/QTextCharFormat>
#include <QtXml/QDomDocument>
#include "document.h"
#include "styleparser.h"
#include "styleinformation.h"
#include "converter.h"
#include "formatproperty.h"

class QDomElement;
class QDomText;

namespace OOO {


    class Document;

    class Converter {
    public:
        Converter();
        ~Converter();

        virtual QTextDocument *convert(const QString &fileName, QString &html, int &tablesum );

    private:
        QTextTableFormat defaultTableStyle();
        QString handle_html( QString & html );
        QByteArray image_encode( QImage im );
        void setError(const QString msg, const int vars = 0);

        bool convertBody(const QDomElement &element);
        bool convertText(const QDomElement &element);
        bool convertHeader(QTextCursor *cursor, const QDomElement &element);
        bool convertParagraph(QTextCursor *cursor, const QDomElement &element, const QTextBlockFormat &format = QTextBlockFormat(), bool merge = false);
        bool convertTextNode(QTextCursor *cursor, const QDomText &element, const QTextCharFormat &format);
        bool convertSpan(QTextCursor *cursor, const QDomElement &element, const QTextCharFormat &format);
        bool convertLink(QTextCursor *cursor, const QDomElement &element, const QTextCharFormat &format);
        bool convertList(QTextCursor *cursor, const QDomElement &element);
        bool convertTable(const QDomElement &element);
        bool convertFrame(const QDomElement &element);
        bool convertAnnotation(QTextCursor *cursor, const QDomElement &element);
       
        QTextDocument *mTextDocument;
        QTextCursor *mCursor;
        QMap<QString, QByteArray> imageLIST;

        StyleInformation *mStyleInformation;
    };
}






#endif	/* CONVERTER_H */

