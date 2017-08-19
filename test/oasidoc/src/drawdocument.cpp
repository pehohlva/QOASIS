#include "drawdocument.h"

void DrawDocument::updateDocument() {
  htmlformat.setLeftMargin(MM_TO_POINT(30));
  htmlformat.setRightMargin(MM_TO_POINT(25));
  htmlformat.setBottomMargin(MM_TO_POINT(35)); /// paint cut 30
  htmlformat.setTopMargin(MM_TO_POINT(18));
  doc->rootFrame()->setFrameFormat(htmlformat);
}

DrawDocument::DrawDocument(QWidget *parent)
    : QAbstractScrollArea(0), lineTimer(0), scaleFaktor(1.367),
      Beeboncontroll(false), doc(new QTextDocument()), RUNPDF(false),
      portrait_mode(true) {

#ifdef LOADPDFIUMYES
  m_pdf = new QPdfium();
#endif

  lastkeyMETA = false;
  CursorPosition = -1;
  doc->setPageSize(QSizeF(MM_TO_POINT(210), MM_TO_POINT(297)));
  htmlformat = doc->rootFrame()->frameFormat();
  this->setMinimumHeight(480);
  this->setMinimumWidth(460);
  this->resize(900, 499);
  if (htmlformat.leftMargin() < 10) {
    this->updateDocument();
  }
  strak = -1;
  this->setContentsMargins(0, 0, 0, 0);
  this->setAcceptDrops(true);
  this->grabGesture(Qt::SwipeGesture, Qt::ReceivePartialGestures);
  this->grabMouse();
  QTimer::singleShot(700, this, SLOT(LoadFile()));
  connect(doc->documentLayout(), SIGNAL(update(QRectF)), this,
          SLOT(updatedoc(QRectF)));
  connect(this, SIGNAL(newdata()), this, SLOT(updateslow())); /// slow paint..
  updateslow();
}
///  mac  trackpad https://support.apple.com/en-us/HT204895
bool DrawDocument::gestureNative(QNativeGestureEvent *e) {
  if (e->type() == QEvent::NativeGesture) {
    if (e->value() < 0) {
      distanceswip = distanceswip - e->value();
      setZoom(scaleFaktor - TRACKPADSTEEPS);
    } else {
      distanceswip = distanceswip + e->value();
      setZoom(scaleFaktor + TRACKPADSTEEPS);
    }
  }
  return true;
}


/* TouchBegin = 194,
      TouchUpdate = 195,
      TouchEnd = 196, spontaneous()

QTextStream xcout(stdout, QIODevice::WriteOnly);
 QString dir;
 xcout << "spontaneous(): " <<  e->spontaneous() <<  " tipe()->" << (int)e->type() << " evalue()->" <<  e->value() << "\n";
 xcout << " move mm:" << POINT_TO_MM(distanceswip) << "\n";
 e->accept();

 */


bool DrawDocument::event(QEvent *e) {
  if (e->type() == QEvent::NativeGesture) {
    return gestureNative(static_cast<QNativeGestureEvent *>(e));
  } else if (e->type() == QEvent::ContextMenu) {
    contextMenuEvent(static_cast<QContextMenuEvent *>(e));
    e->accept();
  }
  //// QString foo;
  ////foo.fill(QChar('-'), 33);
  /// strak = strak + 0.11; /// visual sleep? event 82 ontext menu
  //// const int xmac = e->type();
  return QAbstractScrollArea::event(e);
}

void DrawDocument::updatedoc(QRectF area) {
  /// qDebug() << __FUNCTION__ << " Area new date ->" << area.center().x() <<
  //// emit newdata();
}

void DrawDocument::paintEvent(QPaintEvent *ev) {
  const QRectF viewAreaRect(0, 0, viewport()->width(), viewport()->height());
  htmlformat = doc->rootFrame()->frameFormat();
  QTransform matrix; ///* zero matrix
  QPainter *p = new QPainter(viewport());
  p->setRenderHint(QPainter::Antialiasing, true);
  paintArea(p, ev->rect(), _EDITORBGCOLOR_);
  const int y = yOffset();
  const int x = xOffset();
  p->translate(-x, -y);
  p->setWorldTransform(mcurrent, true);
  int pdf = -1;
#ifdef LOADPDFIUMYES
  pdf = (m_pdf->isValid() && RUNPDF) ? m_pdf->pageCount() : 0;
#endif
  if (pdf > 0) {
    PageSumm = pdf;
  } else {
    PageSumm = qBound(1, doc->pageCount(), MaximumPages);
  }
  for (int o = 0; o < PageSumm; ++o) {
    paintEditPage(o, p);
  }
  p->end();
  p = 0;
}
void DrawDocument::mouseDoubleClickEvent(QMouseEvent *e) {
  /// qDebug() << "->" << __FUNCTION__ << " - " << e->type();
}
void DrawDocument::mousePressEvent(QMouseEvent *e) {
  //// qDebug() << "->" << __FUNCTION__ << " - " << e->type();
}

void DrawDocument::adjustScrollbars() {
  ////  portrait - landscape
  qreal lmax = 10 + qMax(doc->pageSize().width(), doc->pageSize().height());
  qreal lmin = 10 + qMin(doc->pageSize().width(), doc->pageSize().height());
  if (portrait_mode) {
    page = QRectF(0, 0, lmin, lmax);
  } else {
    page = QRectF(0, 0, lmax, lmin);
  }
  const qreal left_slide = SLIDERMARGIN_TICK_TOTAL;
  const int PageSumm = qBound(1, doc->pageCount(), MaximumPages);
  workArea = QSize(page.width() * scaleFaktor,
                   (page.height() * scaleFaktor) * PageSumm);
  bool stayinwi = workArea.width() < viewport()->width() ? true : false;
  bool stayinhi = workArea.height() < viewport()->height() ? true : false;
  qreal border_wi = left_slide;
  qreal border_hi = 0.1;
  if (stayinwi) {
    border_wi = qMax(left_slide, qAbs((qreal)(workArea.width() / 2) -
                                      (viewport()->width() / 2)));
  } else {
    border_hi = left_slide;
  }
  mcurrent =
      QTransform(scaleFaktor, 0., 0., scaleFaktor, border_wi + PAPERSPACE,
                 SLIDERMARGIN_TICK_TOTAL + PAPERSPACE);
  ////// ultimo da sopra penultimo da sinistra
  QSize viewPanelSize = viewport()->size();
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  verticalScrollBar()->setPageStep(workArea.height());  ////* zoom state
  horizontalScrollBar()->setPageStep(workArea.width()); ////* zoom state
  verticalScrollBar()->setRange(0, workArea.height() - viewPanelSize.height() +
                                       SLIDERMARGIN_TICK_TOTAL * 3);
  horizontalScrollBar()->setRange(0, (page.width() * scaleFaktor) -
                                         viewPanelSize.width() +
                                         SLIDERMARGIN_TICK_TOTAL * 3);
}

void DrawDocument::paintgopen(QPainter *painter, int wi, QColor co) {
  QPen fora(co);
  fora.setWidth(wi);
  if (wi < 2) {
    painter->setPen(Qt::NoPen);
  } else {
    painter->setPen(fora);
  }
}

void DrawDocument::wheelEvent(QWheelEvent *e) {
  if (e->phase() != Qt::ScrollEnd) {
    if (static_cast<QWheelEvent *>(e)->orientation() == Qt::Horizontal) {
      QApplication::sendEvent(horizontalScrollBar(), e);
    } else {
      QApplication::sendEvent(verticalScrollBar(), e);
    }
  }
}

void DrawDocument::paintEditPage(const int index, QPainter *painter) {
  const qreal hip = doc->pageSize().height();
  int pdf = -1; ///  (m_pdf->isValid() && RUNPDF)? m_pdf->pageCount()  : 0;
#ifdef LOADPDFIUMYES
  pdf = (m_pdf->isValid() && RUNPDF) ? m_pdf->pageCount() : 0;
#endif
  const qreal fromtop = index * hip;
  const qreal diff = 5 * 4; /// shadow page white hight
  QRectF viewarea(QPointF(0, fromtop), doc->pageSize());
  const QRectF body = QRectF(viewarea.topLeft(), viewarea.size());
  if (index == 0) {
    /// paint image page ground only 1 time e class save.
    xpage = onepageimage(
        QRectF(0, 0, body.size().width(), body.size().height()), diff);
  }
  //// qDebug() <<  __FUNCTION__ << " ->" << index << "-" << fromtop;
  QAbstractTextDocumentLayout::PaintContext CTX;
  CTX.palette.setColor(QPalette::Text, Qt::black);
  //// const QRectF body = QRectF(viewarea.topLeft(),viewarea.size()); /* on
  ///view */
  QRectF view(viewarea.topLeft(), viewarea.size()); /* on doc */
  painter->setClipRect(view);
  painter->drawImage(view, xpage);
  if (pdf < 1) {
    CTX.clip = view;
    CTX.cursorPosition = CursorPosition;
    paintgopen(painter, 0);
    doc->documentLayout()->setProperty(
        "basic_point",
        QVariant(index)); /// register if is paint or not! page nr.x
    doc->documentLayout()->draw(painter, CTX);
  } else {
    const QSize pagepdf(body.size().width(), body.size().height());
    QSize incommingsize(body.size().width(), body.size().height());
    QImage pdfshow = this->req_ImagePdf(index, &incommingsize, pagepdf);
    painter->drawImage(view, pdfshow);
  }
  /// painter->restore();
  QPointF center = view.center();
  QTextStream xcout(stdout, QIODevice::WriteOnly);
  ////xcout << "------------Paint Page:" << index << " center ->" << center.x()
  ///<< " \r";
}

void DrawDocument::triggerFormat() {
  portrait_mode = portrait_mode == true ? false : true;
  if (portrait_mode) {
    doc->setPageSize(QSizeF(MM_TO_POINT(210), MM_TO_POINT(297)));
  } else {
    doc->setPageSize(QSizeF(MM_TO_POINT(297), MM_TO_POINT(210)));
  }
  emit newdata();
}

void DrawDocument::fitToNormal() { setZoom(1.7); }

void DrawDocument::resizeEvent(QResizeEvent *e) { this->updateslow(); }

void DrawDocument::fastupdate() {
  updateDocument();
  viewport()->update();
  adjustScrollbars();
}

void DrawDocument::updateslow() {
//// Eyes do not see fast but resource ...
#ifdef LOADPDFIUMYES
  if (m_pdf->isValid()) {
    RUNPDF = true;
    QTimer::singleShot(460, this, SLOT(fastupdate()));
    return;
  }
#endif
  QTimer::singleShot(90, this, SLOT(fastupdate()));
}

void DrawDocument::keyReleaseEvent(QKeyEvent *event) {
  if (lastkeyMETA) {
    if (Beeboncontroll) {
      QApplication::beep();
    }
    lastkeyMETA = false;
  }
}

void DrawDocument::keyPressEvent(QKeyEvent *e) {

  if (Qt::Key_Meta == e->key() || Qt::Key_Control == e->key()) {
    lastkeyMETA = true;
    if (Beeboncontroll) {
      QApplication::beep();
    }
  }

  if (lastkeyMETA || e->isAutoRepeat()) {
    if (Qt::Key_PageUp == e->key()) {
      e->accept();
      emit newdata();
      return;
    } else if (Qt::Key_PageDown == e->key()) {
      e->accept();
      emit newdata();
      return;
    } else if (Qt::Key_Up == e->key()) {
      scaleFaktor = scaleFaktor + 0.05;
      if (scaleFaktor < 0.22 || scaleFaktor > 10) {
        scaleFaktor = 9.9;
      }
      emit newdata();
      e->accept();
      return;
    } else if (Qt::Key_Down == e->key()) {
      scaleFaktor = scaleFaktor - 0.05;
      if (scaleFaktor < 0.22 || scaleFaktor > 10) {
        scaleFaktor = 0.23;
      }
      emit newdata();
      e->accept();
      return;
    }
  }
  e->accept();
}

void DrawDocument::contextMenuEvent(QContextMenuEvent *event) {
  QMenu *menu = new QMenu(this);
  menu->addAction(tr("Open File html"), this, SLOT(OpenFile()));
  menu->addAction(tr("Swap page format"), this, SLOT(triggerFormat()));
  menu->addAction(tr("Fit size to Page"), this, SLOT(fitToLarge()));
  menu->exec(event->globalPos());
  delete menu;
}

void DrawDocument::ShowFile(const QString file) {
/// test if a pdf!
#ifdef LOADPDFIUMYES
  if (RUNPDF) {
    RUNPDF = false;
    m_pdf->loadFile(
        "../notexist.pdf"); /// make not valid..to clas not repaint..
  }
#endif
  int casego = 0;
  StreamBuf *buf = new StreamBuf();
  QMimeDatabase mimeDatabase;
  QMimeType mimeType = mimeDatabase.mimeTypeForFile(file);
  QStringList typs = mimeType.aliases();
  typs << mimeType.filterString().toLower(); // if upper case
  typs.append(mimeType.filterString());
  typs.append(mimeType.suffixes());
  typs.append(mimeType.aliases());
  typs.append(mimeType.parentMimeTypes());
  QString flat = typs.join(",");
  bool ok = false;
  buf->LoadFile(file);
  if (flat.indexOf(".html", 0) > 0) {
    casego = 1;
    if (buf->isValid()) {
      doc->setHtml(buf->data());
    } else {
      doc->setHtml(buf->tohtmlsimulate());
    }
  } else if (mimeType.inherits("text/plain")) { //// rtf is here handler todo
    casego = 2;
    doc->setHtml(buf->tohtmlsimulate());
  } else if ((flat.indexOf(".pdf", 0) > 0) ||
             (flat.indexOf("acrobat", 0) > 0)) {
    casego = 3;
#ifdef LOADPDFIUMYES
    m_pdf = new QPdfium(); /// destroy old!
    m_pdf->loadFile(file);
    buf->clear();
    RUNPDF = true;
#endif
    doc->setHtml(" <h1> Sorry pdf is not valid...<h1/>   ");
  }
  buf->~StreamBuf();
  if (!RUNPDF) {
    emit newdata();
  }
}

void DrawDocument::OpenFile() {
  const QString file =
      QFileDialog::getOpenFileName(this, tr("Open File to read"),
                                   qApp->applicationDirPath(), tr("Files (*)"));
  if (!file.isEmpty()) {
    this->ShowFile(file);
  }
}

void DrawDocument::LoadFile() {
  ShowFile("./index.html");
  QString textplain = doc->toPlainText();
  if (textplain.size() < 10) {
    this->OpenFile();
    return;
  }
}

/// here is perfect on mac osx dont touch..
void DrawDocument::setZoom(const qreal value) {
      if (value < 0.22 ) {
          scaleFaktor = 0.23;
          return;
      }
      if ( value > 10 ) {
          scaleFaktor = 9.9;
          return;
      }
      if ( value != scaleFaktor) {
        scaleFaktor = value;
        QTimer::singleShot(10, this, SLOT(updateslow()));
        return;
      }
      /// message turn back..
}

void DrawDocument::fitToLarge() {
  qreal scaleFaktor = 3.3;
  QSizeF vdocument = doc->pageSize();
  qreal posibel = viewport()->width();
  QRect screens = QApplication::desktop()->availableGeometry();
  int largox = screens.width() / 2;
  int altox = screens.height() / 2;
  setZoom((posibel / vdocument.width() * 2));
}

QString DrawDocument::pageTextpdf(int index) {
#ifdef LOADPDFIUMYES
  return m_pdf && m_pdf->isValid() ? m_pdf->page(index).text() : "";
#endif
  return QString();
}

QImage DrawDocument::req_ImagePdf(const int id, QSize *size,
                                  const QSize &requestedSize) {
#ifdef LOADPDFIUMYES
  if (!m_pdf || !m_pdf->isValid()) {
    return QImage();
  }
  auto page = m_pdf->page(id);
  qreal scale =
      requestedSize.isValid() ? requestedSize.width() / (qreal)page.width() : 2;
  auto image = page.image(scale);
  size->setWidth(image.width());
  size->setHeight(image.height());
  return image;
#endif
  return QImage();
}
