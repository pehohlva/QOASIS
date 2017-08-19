#include "drawdocument.h"

void DrawDocument::updateDocument() {
  htmlformat.setLeftMargin(MM_TO_POINT(30));
  htmlformat.setRightMargin(MM_TO_POINT(25));
  htmlformat.setBottomMargin(MM_TO_POINT(35)); /// paint cut 30
  htmlformat.setTopMargin(MM_TO_POINT(18));
  doc->rootFrame()->setFrameFormat(htmlformat);
}

DrawDocument::DrawDocument(QWidget *parent)
    : QAbstractScrollArea(0), lineTimer(0), waitprocess(false),
      scaleFaktor(1.367), Beeboncontroll(false), doc(new QTextDocument()),
      RUNPDF(false), portrait_mode(true) {
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
  this->setContentsMargins(0, 0, 0, 0);
  this->setAcceptDrops(true);
  this->grabGesture(Qt::SwipeGesture, Qt::ReceivePartialGestures);
  this->grabMouse();
  connect(doc->documentLayout(), SIGNAL(update(QRectF)), this,
          SLOT(updatedoc(QRectF)));
  connect(this, SIGNAL(newdata()), this, SLOT(updateslow()));
  strak = 0;
  updateslow();
  QTimer::singleShot(50, this, SLOT(LoadInitDoc()));
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

bool DrawDocument::event(QEvent *e) {
  if (e->type() == QEvent::NativeGesture) {
    return gestureNative(static_cast<QNativeGestureEvent *>(e));
  } else if (e->type() == QEvent::ContextMenu) {
    contextMenuEvent(static_cast<QContextMenuEvent *>(e));
    e->accept();
  }
  return QAbstractScrollArea::event(e);
}

void DrawDocument::updatedoc(QRectF area) {
  //// emit newdata();
}

static void xxcrisi(qreal &tac, int v) {

  int x = 0;
  do {
    ++x;
    tac++;
  } while (x < v);
}

void DrawDocument::wait_time(qint64 byte) {
  if (byte == 0 || byte < 1) {
    waitprocess = false;
    progressbar = 0;
    return;
  } else {
    const int wi = doc->pageSize().width() - Waitblockwwi;
    waitprocess = true;
    const int diffspaint = (DiffborderDocument * 3);
    if (progressbar > wi) {
      progressbar = 1 - diffspaint;
    }

    strak++;

    if (doc->pageCount() == 1) {
    }

    if (byte == 1) {
      progressbar = -44;
      doc->setPageSize(QSizeF(MM_TO_POINT(210), MM_TO_POINT(297)));
    }
    if (byte > 0 || byte == 1) {
      xxcrisi(progressbar, 44);
      qDebug() << byte << "-" << progressbar << " wait .. " << diffspaint
               << " .. ";
      QApplication::processEvents();
      updateslow();
    }
  }
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

  PageSumm = qBound(1, doc->pageCount(), MaximumPages);
  for (int o = 0; o < PageSumm; ++o) {
    paintEditPage(o, p);
  }
  if (waitprocess) {
    QRectF viewbar(progressbar, 0, Waitblockwwi, doc->size().height());
    ////if (strak%2 == 0 ) {
    paintArea(p, viewbar, QColor(Qt::red));
    ///} else {
    //// paintArea(p,viewbar, QColor(Qt::blue));
    /// }
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
  const qreal fromtop = index * hip;
  const qreal diff = DiffborderDocument; /// shadow page white hight
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
  /// view */
  QRectF view(viewarea.topLeft(), viewarea.size()); /* on doc */
  painter->setClipRect(view);
  painter->drawImage(view, xpage);

  CTX.clip = view;
  CTX.cursorPosition = CursorPosition;
  paintgopen(painter, 0);
  doc->documentLayout()->setProperty(
      "basic_point",
      QVariant(index)); /// register if is paint or not! page nr.x
  doc->documentLayout()->draw(painter, CTX);

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
  QTimer::singleShot(240, this, SLOT(fastupdate()));
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

void DrawDocument::show_meta_doc(DocumentRam &file) {

  qDebug() << __FUNCTION__ << " Area entra ->" << file << " - ";
}

void DrawDocument::ShowFile(const QString file) {
  /// test if a pdf!
  if (file.size() < 3) {
    return;
  }

  QFileInfo fix(file);
  //// emit wait_loading( fix.size() );
  //// QApplication::processEvents(QEventLoop::WaitForMoreEvents,5*1000);
  const int sak = session->Doc_Open(file);
  connect(session, SIGNAL(new_document(DocumentRam)), this,
          SLOT(show_meta_doc(DocumentRam)));
  connect(session, SIGNAL(wait_loading(qint64)), this, SLOT(wait_time(qint64)));
  updateslow();
}

void DrawDocument::OpenFile() {
  const QString file =
      QFileDialog::getOpenFileName(this, tr("Open File to read"),
                                   qApp->applicationDirPath(), tr("Files (*)"));
  if (!file.isEmpty()) {
    this->ShowFile(file);
  }
}

void DrawDocument::LoadInitDoc() {
  QByteArray  htmlhunk = html_pdf_file("./aa.pdf");
  StreamBuf *rami = new StreamBuf();
  rami->device()->write(htmlhunk);
  if (!rami->isValid()) {
      //// qDebug() << __FUNCTION__ << " valid dom - " << htmlhunk.size();
      return;
  }
  const QString xmlo = rami->data();
  rami->~StreamBuf();
  doc->setHtml(xmlo);
}

/// here is perfect on mac osx dont touch..
void DrawDocument::setZoom(const qreal value) {
  if (value < 0.22) {
    scaleFaktor = 0.23;
    return;
  }
  if (value > 10) {
    scaleFaktor = 9.9;
    return;
  }
  if (value != scaleFaktor) {
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
/*
QString DrawDocument::pageTextpdf(int index) {
#ifdef LOADPDFIUMYES
  return m_pdf && m_pdf->isValid() ? m_pdf->page(index).text() : "";
#endif
  return QString();
}
*/
