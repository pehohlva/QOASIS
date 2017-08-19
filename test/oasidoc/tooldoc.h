#ifndef TOOLDOC_H
#define TOOLDOC_H

#include "documentsession.h"
#include <QAbstractScrollArea>
#include <QAbstractTextDocumentLayout>
#include <QAction>
#include <QApplication>
#include <QBuffer>
#include <QCoreApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QDomDocument>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImageWriter>
#include <QInputEvent>
#include <QMainWindow>
#include <QMarginsF>
#include <QMenu>
#include <QMessageBox>
#include <QMimeDatabase>
#include <QMimeType>
#include <QNativeGestureEvent>
#include <QObject>
#include <QPainter>
#include <QPlainTextDocumentLayout>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QScrollBar>
#include <QSystemTrayIcon>
#include <QTabletEvent>
#include <QTextDocument>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QTimer>
#include <QWidget>
#include <QXmlQuery>

#include <QTextCursor>

#include <cmath>
#include <typeinfo>

#ifdef LOADPDFIUMYES
#include <QPdfium>
#include <QPdfiumPage>
#endif


static inline bool file_put_contents(const QString fullFileName,  const QString &xml , int modus = 0) {
    if (fullFileName.contains("/", Qt::CaseInsensitive)) {
    QString ultimacartellaaperta = fullFileName.left(fullFileName.lastIndexOf("/"))+"/";
    QDir dira(ultimacartellaaperta);
    if ( dira.mkpath(ultimacartellaaperta) ) { } else {
    return false;
    }
    }
        QTextCodec *codecx;
        codecx = QTextCodec::codecForLocale();
        QFile f( fullFileName );
            if (modus == 0) {  //// not append!
                if (f.exists()) {
                    f.remove();
                  }
                if ( f.open(  QFile::WriteOnly | QIODevice::Text  ) ) {
                    QTextStream sw( &f );
                    sw.setCodec(codecx);
                    sw << xml;
                    f.close();
                     if (f.bytesAvailable() > 0) {
                        return true;
                      } else {
                        return false;
                      }
                }
             } else {
                if ( f.open( QFile::Append | QFile::Text ) ) {
                        QTextStream sw( &f );
                        sw.setCodec(codecx);
                        sw << xml;
                        f.close();
                        if (f.bytesAvailable() > 0) {
                           return true;
                         } else {
                           return false;
                         }
                 }
              }
     return false;
}



/*  all tool to QAbstractScrollArea drawdocument.h */
static const qreal PAGEFAKTOR = 1.2;
static const qreal SCALING_STEEP = 0.85555555;
static const qreal TRACKPADSTEEPS = 0.013555555;
static const qreal SLIDERMARGIN_TICK = 25.0;
static const qreal SLIDERSPACER = 2.5;
static const qreal SLIDERCURSORWI = 6.0;
static const qreal PAPERSPACE = 5;
static const int MaximumPages = 99;
static const qreal BorderShadow = 5.2;
static const int DefaultFonzSize = 32;
static const int DiffborderDocument = 20;
static const int Waitblockwwi = 5;
static const int Waitblockwhi = 100;
static const qreal SLIDERMARGIN_TICK_LEFT = SLIDERMARGIN_TICK + SLIDERSPACER;
static const qreal SLIDERMARGIN_TICK_TOTAL =
    SLIDERMARGIN_TICK + SLIDERSPACER + SLIDERSPACER;
typedef QPair<qreal, qreal> bodyMargins;
typedef QPair<qreal, qreal> bodyMargins;
#define POINT_TO_CM(cm) ((cm) / 28.3465058)
#define POINT_TO_MM(mm) ((mm) / 2.83465058)
#define MM_TO_POINT(mm) ((mm)*2.83465058)
#define CM_TO_POINT(cm) ((cm)*28.3465058)

#define _SLIDERBGCOLOR_ QColor("#ebe9ed")
#define _EDITORBGCOLOR_ QColor("#ebe9ed")
#define _SHADOWCOLOR_ QColor("#D3D3D3")

static QIcon createColorIcon(QColor color) {
  QPixmap pixmap(50, 50);
  pixmap.fill(color);
  return QIcon(pixmap);
}


class StreamBuf {
public:
  StreamBuf() : d(new QBuffer()) { d->open(QIODevice::ReadWrite); }
  ~StreamBuf() { d->close(); }
  bool clear() {
    d->write(QByteArray());
    return d->bytesAvailable() == 0 ? true : false;
  }

  bool LoadFile(const QString file) {
    if (clear()) {
      QFile f(file);
      if (f.exists()) {
        if (f.open(QFile::ReadOnly)) {
          d->write(f.readAll());
          d->seek(0);
          return true;
        }
      }
    }
    return false;
  }

  bool PutOnFile(const QString file) {
    QFile f(file);
    d->seek(0);
    if (f.open(QFile::WriteOnly | QIODevice::Text )) {
      uint bi = f.write(stream());
      f.close();
      return bi > 0 ? true : false;
    }
    return false;
  }

  QIODevice *device() { return d; }
  QByteArray stream() { return d->data(); }
  /* <?xml version="1.0" encoding="utf-8"?> */
  QString data() { return QString::fromUtf8(stream()); }
  QString tohtmlsimulate() {
    QStringList lines = data().split(QRegExp("[\n]"), QString::KeepEmptyParts);
    QString str = lines.join("<br/>");
    str.prepend(QString("<p>"));
    str.append(QString("<p/>"));
    return str;
  }

  QBuffer *d;
  QDomDocument Dom() { return doc; }
  bool isValid() { return doc.setContent(stream(), false, 0, 0, 0); }
  QDomDocument doc;
};

static inline void caca() {
    StreamBuf *rami = new StreamBuf();
    rami->device()->write(QByteArray("hi"));
    rami->device()->seek(0);

    rami->clear();
    rami->~StreamBuf();

}


/// same game to odt format image if load faster
static inline QByteArray html_image(QImage x, const QSize area) {
  if (x.isNull()) {
    return QByteArray();
  }
  QByteArray ba;
  QBuffer bu(&ba);
  //bu.open(QBuffer::ReadWrite);
  bu.open(QIODevice::WriteOnly);
  x.save(&bu,"JPG",5);
  bu.close();
  QString head0 =  QString("<img style='max-width:90vw' src='data:image/png;base64,");
  QString head1 = QString("\'  width=\'");
  head1 += QString::number(area.width());
  head1 += QString("\' height=\'");
  head1 += QString::number(area.height());
  head1 += QString("' />");
  head0.replace(QChar(39), QChar(34));
  head1.replace(QChar(39), QChar(34));
  /// base 64 sign ..
  QByteArray endchunk = ba.toBase64(); ///  = /// tra_chunk.toBase64();
  x.~QImage();
  //// qDebug() << __FUNCTION__ << "- size-> " << endchunk.size();
  endchunk.prepend(head0.toLatin1());
  endchunk.append(head1.toLatin1());
   //// qDebug() << __FUNCTION__ << "- " << endchunk;
  return endchunk;
}

/* MM_TO_POINT  A4  210 mm × 297 mm */
static inline QByteArray html_pdf_file(const QString file) {  //// pdf file ...
  const qreal pixelscreenscale = 2;
   QSize _A4( MM_TO_POINT(210) / pixelscreenscale , MM_TO_POINT(297) / pixelscreenscale  ); /// screen .. to print get full...
   QByteArray body,tmp,line;
   body += QByteArray("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"> ");
   body += QByteArray("<html><head><meta name=\"qrichtext\" content=\"1\" /><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />" );
   body += QByteArray("</head><body>" );

#ifdef LOADPDFIUMYES
  qreal scale = MM_TO_POINT(210) / _A4.width(); /// must give pixelscreenscale!!!
  QPdfium *m_pdf = new QPdfium();     /// destroy old!
  m_pdf->loadFile(file);
  if (!m_pdf->isValid()) {
      return QByteArray();
  }
  const int pagex = m_pdf->pageCount();
  if (pagex > 0) {
      int dd=-1;
      do {
         dd++;
         qDebug() << __FUNCTION__ << " - " << scale << "- page  " << dd;
         QPdfiumPage page = m_pdf->page(dd);
         QImage image = page.image(scale);
         if (image.isNull()) {
           return QByteArray();
         }
         QByteArray img64 = html_image(image,_A4);  /// .toLatin1();
         image.~QImage();
         line += QByteArray("<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  ");
         line += img64;
         line += QByteArray("</p>");
         body.append(line);
      } while( dd < (pagex -1) );
  }
#endif
  QByteArray footer = QByteArray("</body></html>");
  body.append(footer);
  return body;
}

/// Background image for 1 html page in subclass QAbstractScrollArea A4 or other
static inline QImage onepageimage(const QRectF big, qreal substract) {
  QImage qImage(big.size().width(), big.size().height(), QImage::Format_RGB32);
  qImage.fill(_EDITORBGCOLOR_);
  int angle = substract / 4;
  QRectF inside(0, 0, big.size().width() - substract,
                big.size().height() - substract);
  QPainter *p = new QPainter();
  p->begin(&qImage);
  p->setPen(Qt::NoPen);
  p->setBrush(Qt::white);
  p->drawRect(inside);
  p->setBrush(Qt::black);
  /// p->setBrush(Qt::red);
  p->setPen(Qt::NoPen);
  /// QRectF(qreal left, qreal top, qreal width, qreal height)
  p->drawRect(
      QRectF(angle, inside.size().height(), inside.size().width(), angle));
  p->drawRect(
      QRectF(inside.size().width(), angle, angle, inside.size().height()));
  bool bEnd = p->end();
  if (bEnd) {
    return qImage;
  } else {
    return QImage();
  }
}

static void paintWidged(QPainter *p, const QRectF rect, const QTransform trax) {
  p->save();
  p->setPen(QPen(Qt::black, 0.8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  p->setBrush(_SLIDERBGCOLOR_);

  p->drawRect(rect);
  p->restore();
}

static void paintArea(QPainter *p, const QRectF rect, QColor col) {
  p->save();
  p->setBrush(col);
  p->setPen(Qt::NoPen);
  p->drawRect(rect);
  p->restore();
}

static void paintCursor(QPainter *p, const QRectF rect) {
  bool horrizontal = rect.width() == SLIDERCURSORWI ? true : false;
  qreal midiline = SLIDERCURSORWI / 2;
  QPointF soco(QPointF(midiline, 0) + rect.topLeft());
  QPointF socoend(QPointF(midiline, 0) + rect.bottomLeft());

  if (!horrizontal) {
    soco = rect.bottomLeft() - QPointF(0, midiline);
    socoend = soco + QPointF(rect.width(), 0);
  }

  p->save();
  p->setOpacity(0.4);
  p->setBrush(QColor(Qt::green));
  p->setPen(Qt::NoPen);
  p->drawRect(rect);
  p->setOpacity(1.0);
  p->setBrush(Qt::red);
  p->setPen(QPen(Qt::red, 1.5));
  if (horrizontal) {
    p->drawLine(soco, socoend);
  } else {
    p->drawLine(soco, socoend);
  }
  p->restore();
}

static void paintScale(QPainter *p, const QRectF rect,
                       QPair<qreal, qreal> bodyMargins, const QTransform trax) {
  bool horrizontal =
      qMax(rect.height(), rect.width()) == rect.width() ? true : false;
  const qreal one_unit = CM_TO_POINT(1);
  const qreal one_unit_dec = MM_TO_POINT(1) * trax.m11();
  const QPointF init = rect.topLeft();
  qreal linemid = qMin(rect.height(), rect.width()) / 5;
  qreal wi = qMax(rect.height(), rect.width());
  const qreal marginLeftX = init.x() + (bodyMargins.first * trax.m11());
  const qreal marginRightX =
      init.x() + rect.width() - (bodyMargins.second * trax.m11());
  const qreal marginTopY = init.y() + (bodyMargins.first * trax.m11());
  const qreal marginToptX =
      init.y() + rect.height() - (bodyMargins.second * trax.m11());
  int fontsizetxt = 6;
  int sline = wi / one_unit;
  int slines = wi / one_unit_dec;
  p->save();
  p->setBrush(QColor(Qt::white));
  p->setPen(Qt::NoPen);
  p->drawRect(rect);
  QFont valFont("Arial", fontsizetxt, QFont::Normal);
  p->setFont(valFont);
  p->setPen(QPen(Qt::black, 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  if (horrizontal) {
    p->drawLine(init.x(), linemid + init.y(), init.x() + wi,
                linemid + init.y());
    p->setPen(
        QPen(Qt::black, 0.25, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    int PressUnit = -1;
    int numsUnit = 0;
    for (int x = 0; x <= slines; x++) {
      PressUnit++;
      const int LeftPointer2 = (x * one_unit_dec) + init.x();
      if (PressUnit == 0) {
        p->drawLine(LeftPointer2, linemid + init.y(), LeftPointer2,
                    linemid * 3.5 + init.y());
      } else if (PressUnit == 5) {
        p->drawLine(LeftPointer2, linemid + init.y(), LeftPointer2,
                    linemid * 3 + init.y());
      } else {
        p->drawLine(LeftPointer2, linemid + init.y(), LeftPointer2,
                    linemid * 2 + init.y());
      }

      if (PressUnit == 0 && numsUnit > 0) {
        const QString strnum = QString("%1").arg(numsUnit);
        QRectF valR(LeftPointer2 - fontsizetxt, linemid * 3 + init.y(),
                    fontsizetxt * 2, fontsizetxt + 2);
        p->drawText(valR, Qt::AlignCenter, strnum);
      }

      if (PressUnit == 9) {
        PressUnit = -1;
        numsUnit++;
      }
    }
    const QRectF cursor_1(marginLeftX - (SLIDERCURSORWI / 2), init.y(),
                          SLIDERCURSORWI, rect.height());
    const QRectF cursor_2(marginRightX - (SLIDERCURSORWI / 2), init.y(),
                          SLIDERCURSORWI, rect.height());
    paintCursor(p, cursor_1);
    paintCursor(p, cursor_2);

  } else {
    p->setPen(QPen(Qt::black, 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p->drawLine(init.x() + linemid, init.y(), init.x() + linemid,
                init.y() + wi);
    p->setPen(
        QPen(Qt::black, 0.25, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    int PressUnit = -1;
    int numsUnit = 0;

    for (int x = 0; x <= slines; x++) {
      PressUnit++;

      const int TopPointer = (x * one_unit_dec) + init.y();
      if (PressUnit == 0) {
        p->drawLine(init.x() + linemid, TopPointer, init.x() + (linemid * 3.5),
                    TopPointer);
      } else if (PressUnit == 5) {
        p->drawLine(init.x() + linemid, TopPointer, init.x() + (linemid * 3),
                    TopPointer);
      } else {
        p->drawLine(init.x() + linemid, TopPointer, init.x() + (linemid * 2),
                    TopPointer);
      }

      if (PressUnit == 0 && numsUnit > 0) {
        const QString strnum = QString("%1").arg(numsUnit);
        QRectF valR(init.x() + (linemid * 2), TopPointer - fontsizetxt,
                    fontsizetxt * 2, fontsizetxt + 2);
        //////////////p->rotate ( 90 );
        p->drawText(valR, Qt::AlignCenter, strnum);
      }

      if (PressUnit == 9) {
        PressUnit = -1;
        numsUnit++;
      }
    }

    //////const QRectF cursor_1(marginLeftX - (SLIDERCURSORWI /
    /// 2),init.y(),SLIDERCURSORWI,rect.height());
    const QRectF cursor_3(init.x(), marginTopY - (SLIDERCURSORWI / 2),
                          rect.width(), SLIDERCURSORWI);
    const QRectF cursor_4(init.x(), marginToptX - (SLIDERCURSORWI / 2),
                          rect.width(), SLIDERCURSORWI);
    paintCursor(p, cursor_3);
    paintCursor(p, cursor_4);
  }

  p->setBrush(Qt::NoBrush);
  p->setPen(QPen(Qt::black, 0.8));
  p->drawRect(rect);
  p->restore();
}

#endif // TOOLDOC_H
