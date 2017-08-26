
#include "interface.h"

typedef enum {
  DRAW_SELECTION,
  SCALE_SELECTION,
  DRAW_LINE,
  DRAW_START,
  WORK_CONTEX_MENU,
  DRAW_OUTSIDE_IMAGE,
  MOVE_RECTANGLE,
  MOVE_RECTANGLE_END,
  NO_EFFECT
} DRAG_MODE;

class Foto_DD : public QWidget {
  Q_OBJECT
  //
public:
  Foto_DD(QWidget * = 0) { rotatari = 0; }
  void paint(QPixmap e) {
    base = e;
    repaint();
  }
  void paintEvent(QPaintEvent *e) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(0, 0, base);
    painter.end();
  }

protected:
  void mousePressEvent(QMouseEvent *e) { emit PrMouse(e); }
  void mouseMoveEvent(QMouseEvent *e) { emit MoMouse(e); }

private:
  QPixmap base;
  int rotatari;
signals:
  void PrMouse(QMouseEvent *e);
  void MoMouse(QMouseEvent *e);
public slots:
  void setRotate(int i) {
    rotatari = i;
    repaint();
  }
};

class Interface : public QDialog, public Ui::Interface {
  Q_OBJECT
public:
  static Interface *self(QWidget * = 0);
  void SetPic(const QString pic);
  void SetFormat(QTextImageFormat e);
  QTextImageFormat GetFormat();

protected:
  void resizeEvent(QResizeEvent *);
  void closeEvent(QCloseEvent *);
  void wheelEvent(QWheelEvent *event);
  void mouseReleaseEvent(QMouseEvent *e);
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  QScrollBar *sx1;
  QScrollBar *sx2;

private:
  Interface(QWidget * = 0);
  static QPointer<Interface> _self;
  QVariant currentItemData(QComboBox *comboBox);
  Foto_DD *wrapper;
  void UpdateNow();
  QFileInfo fi;
  int Top_startX;
  int Top_startY;
  bool airotato;
  bool moverecci;
  bool CTRL_Pressed;
  int nrpic;
  /* image attribute */
  QTextImageFormat nowimage; /* qtextedit html image */
  QRect TagliaPoi;
  QPoint Dstart;
  QPoint Dstop;
  QPoint Dmove;

  QByteArray extension;
  int rotazione;
  ///// int  HighteResult;
  /////int  LargeResult;
  int LargeReal;
  int HighteReal;
  qreal ratio;
  qreal cento;
  QColor color1;
  bool onwi;
  QString origImageFilename;
  QPixmap display;
  QPixmap original2;
  QPixmap original;
  QPoint ScalePoint(QPoint p);
  void populateWithColors(QComboBox *comboBox);
  void populateFilter(QComboBox *comboBox);
  int QMIN(int x, int y);
  int QMAX(int x, int y);
  int QRAPORT(int n, qreal r);
  void DisegnaRect(QPoint topLeft, QPoint bottomRight);
signals:

public slots:
  void SetColor();
  void SetZoom(int percentual);
  void Mousepress(QMouseEvent *e);
  void Mousemove(QMouseEvent *e);
  void setMesure(int w, int mode);
  void setRotate(int r);
  void BaseReset();
  void BaseSave();
  void TmpSave();
  void CropNow();
  void misurecambiaA();
  void misurecambiaL();
  void PrintScreen();
  void MakePrintScreen();
  void applyFilter(QString filtername);
};

QPointer<Interface> Interface::_self = 0L;

Interface *Interface::self(QWidget *parent) {
  if (!_self)
    _self = new Interface(parent);
  return _self;
}

void Interface::PrintScreen() {
  QDesktopWidget *desk = qApp->desktop();
  QPixmap desktopscreen = QPixmap::grabWindow(desk->screen()->winId());
  desktopscreen.save(origImageFilename, extension.data(), qualvalue->value());
  BaseReset();
  showMaximized();
}

void Interface::MakePrintScreen() {
  bool ok;
  int i = QInputDialog::getInt(
      this, tr("Wait Sec. to PrintScreen...."),
      tr("Wait Sec. to PrintScreen....<br>Sec: from 1/10"), 1, 1, 10, 1, &ok);
  if (ok && i > 0 && i < 11) {
    QTimer::singleShot(i * 1000, this, SLOT(PrintScreen()));
  }
}

Interface::Interface(QWidget *parent) : QDialog(parent) {
  setWindowFlags(Qt::Window);
  setWindowModality(Qt::ApplicationModal);
  setupUi(this);
  setWindowTitle(tr("Image minimal editor"));
  pushButton->setText(tr("Save and Exit"));
  pushButton->setToolTip(tr("Only save CTRL+S"));
  airotato = false;
  cento = 100.0;
  onwi = false;
  rotazione = 0;
  ratio = cento;
  CTRL_Pressed = false;
  moverecci = false;
  Dstart = QPoint(0, 0);
  wrapper = new Foto_DD(this);
  scrolla->setWidget(wrapper);
  scrolla->setBackgroundRole(QPalette::Dark);
  QRect areaplace(QPoint(0, 0), QPoint(0, 0));
  TagliaPoi = areaplace;
  sx1 = scrolla->verticalScrollBar();
  sx2 = scrolla->horizontalScrollBar();
  connect(wrapper, SIGNAL(PrMouse(QMouseEvent *)), this,
          SLOT(Mousepress(QMouseEvent *)));
  connect(wrapper, SIGNAL(MoMouse(QMouseEvent *)), this,
          SLOT(Mousemove(QMouseEvent *)));
  populateWithColors(comboBox);
  color1 = qvariant_cast<QColor>(currentItemData(comboBox));
  connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SetColor()));
  connect(horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(SetZoom(int)));
  connect(horizontalSlider_2, SIGNAL(sliderReleased()), this,
          SLOT(misurecambiaA()));
  connect(horizontalSlider_3, SIGNAL(sliderReleased()), this,
          SLOT(misurecambiaL()));
  connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(misurecambiaA()));
  connect(spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(misurecambiaL()));
  connect(spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(setRotate(int)));
  connect(pushButton, SIGNAL(clicked()), this, SLOT(BaseSave()));
  connect(pushButton_2, SIGNAL(clicked()), this, SLOT(CropNow()));
  connect(comboBox_2, SIGNAL(currentIndexChanged(QString)), this,
          SLOT(applyFilter(QString)));
  populateFilter(comboBox_2);
}

void Interface::SetFormat(QTextImageFormat e) {
  nowimage = e;
  SetPic(e.name());
}

QTextImageFormat Interface::GetFormat() {
  nowimage.setHeight(HighteReal);
  nowimage.setWidth(LargeReal);
  return nowimage;
}

void Interface::SetPic(const QString pic) {
  origImageFilename = pic;
  QFileInfo ImageInfo(pic);
  fi = ImageInfo;
  QString ext = ImageInfo.completeSuffix();
  ext.toUpper();
  extension = ext.toLocal8Bit();
  display = QPixmap(pic);
  original = QPixmap(pic);
  original2 = original;
  wrapper->paint(display);
  spinBox_3->setValue(ratio);
  LargeReal = original.width();
  HighteReal = original.height();
  cento = 100.0;
  rotazione = 0;
  ratio = cento;
  CTRL_Pressed = false;
  moverecci = false;
  Top_startX = 0;
  QRect areaplace(QPoint(0, 0), QPoint(0, 0));
  TagliaPoi = areaplace;
  UpdateNow();
  // qDebug() << "####### size().width()  " << size().width();
  int nuovadim;
  if (LargeReal > size().width()) {
    nuovadim = ratio = (size().width() * cento) / LargeReal;
    ////////////qDebug() << "####### ratio sp   " << nuovadim;
    spinBox_3->setValue(ratio);
    SetZoom(nuovadim);
    return;
  }
}

void Interface::misurecambiaA() {
  if (!onwi) {
    setMesure(spinBox->value(), 0);
  }
}

void Interface::misurecambiaL() {
  if (!onwi) {
    setMesure(spinBox_2->value(), 1);
  }
}

void Interface::setMesure(int w, int mode) {
  onwi = true;
  QPixmap resized;
  QPixmap picsa(origImageFilename);
  if (mode == 0) {
    resized = picsa.scaledToWidth(w);
  } else {
    resized = picsa.scaledToHeight(w);
  }
  ratio = 100.0;
  display = resized;
  original = resized;
  original2 = resized;
  SetZoom(100);
}

void Interface::setRotate(int r) {
  if (r < 360) { /* -360   - 360  */
    rotazione = r;
    /////QPixmap base(origImageFilename);
    QImage base(origImageFilename);
    int massimo =
        QMAX(base.width(), base.height()); /* find  max cube from image */
    int fotox = (massimo / 2) - (base.width() / 2);
    int fotoy = (massimo / 2) - (base.height() / 2);
    QPixmap nuovo(massimo, massimo);
    QPainter painter;
    painter.begin(&nuovo);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate((massimo / 2), (massimo / 2));
    painter.rotate(r);
    painter.translate(-(massimo / 2), -(massimo / 2));
    /////painter.drawPixmap(fotox,fotoy,base);
    painter.drawImage(fotox, fotoy, base, Qt::MonoOnly);
    painter.end();
    int newlarge = (massimo / cento) * ratio;
    display = nuovo.scaledToWidth(newlarge, Qt::FastTransformation);
    original = nuovo;

    wrapper->paint(display);
    ////////SetZoom( ratio );
    airotato = true;
  }
}

void Interface::resizeEvent(QResizeEvent *) {
  wrapper->setMinimumSize(original.width(), original.height());
}

void Interface::BaseReset() {
  if (origImageFilename.size() > 0) {
    SetPic(origImageFilename);
    SetZoom(ratio);
  }
  sx1->setValue(0);
  sx2->setValue(0);
  Top_startX = 0;
  QApplication::restoreOverrideCursor();
}

void Interface::TmpSave() {
  if (TagliaPoi.width() > 10) {
    SetZoom(ratio);
  }
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  Top_startX = 0;

  QRect areaplace(QPoint(0, 0), QPoint(0, 0));
  TagliaPoi = areaplace;

  if (origImageFilename.size() > 0) {
    ratio = 100.0;
    original.save(origImageFilename, extension.data(), qualvalue->value());
    rotazione = 0;
    spinBox_4->setValue(rotazione);
    BaseReset();
  }
  QApplication::restoreOverrideCursor();
}

void Interface::BaseSave() {
  if (TagliaPoi.width() > 10) {
    SetZoom(ratio);
  }

  Top_startX = 0;

  QRect areaplace(QPoint(0, 0), QPoint(0, 0));
  TagliaPoi = areaplace;

  if (origImageFilename.size() > 0) {
    ratio = 100.0;
    original.save(origImageFilename, extension.data(), qualvalue->value());
    rotazione = 0;
    spinBox_4->setValue(rotazione);
    BaseReset();
  }
  accept();
}

void Interface::CropNow() {
  if (TagliaPoi.width() > 5) {
    original = original2.copy(TagliaPoi);
    TmpSave();
  }
  sx1->setValue(0);
  sx2->setValue(0);
  Top_startX = 0;
}

//

void Interface::UpdateNow() {

  QDateTime lastm = fi.lastModified();
  spinBox_3->setValue(ratio);
  LargeReal = original2.width();
  HighteReal = original2.height();
  spinBox->setValue(LargeReal);
  spinBox_2->setValue(HighteReal);
  horizontalSlider_2->setValue(LargeReal);
  horizontalSlider_3->setValue(HighteReal);
  spinBox_4->setValue(rotazione);

  if (Top_startX > 0) {
    pushButton_2->setEnabled(true);
    imgcoo->setText(
        tr("Init crop on X=%1 Y=%2  px %3x%4 CTRL + mouse to move crop area.")
            .arg(Top_startX)
            .arg(Top_startY)
            .arg(TagliaPoi.width())
            .arg(TagliaPoi.height()));
  } else {
    imgcoo->setText(tr("No crop action"));
    pushButton_2->setEnabled(false);
  }

  QString help = "";

  if (rotazione != 0) {
    help = tr("Save image after rotation!");
  }

  imginfo->setText(tr("Name: %1 %2x%3 / Size %4 / lastModified %5 %6")
                       .arg(fi.fileName())
                       .arg(LargeReal)
                       .arg(HighteReal)
                       .arg(BiteorMega(fi.size()))
                       .arg(lastm.toString(Qt::ISODate))
                       .arg(help));

  QResource xmlres(":/img/tip.html");
  QString sale = "";
  QFile file(xmlres.absoluteFilePath());
  if (file.exists()) {
    if (file.open(QFile::ReadOnly | QFile::Text)) {
      sale = QString::fromUtf8(file.readAll());
      file.close();
    }
  }
  imginfo->setToolTip(QString(sale));

  onwi = false;
}

/*

 int fotox = (massimo / 2) - (base.width() / 2);
                int fotoy = (massimo / 2) - (base.height() / 2);

*/
/* ##################################################################################
 */
/* ###################################event
 * mouse############################################### */
/* ##################################################################################
 */

void Interface::keyPressEvent(QKeyEvent *e) {
  qDebug() << "### " << __FILE__ << "-" << __FUNCTION__ << "line:" << __LINE__;

  if (e->key() == Qt::Key_Control && TagliaPoi.width() > 0) {
    moverecci = true;
    CTRL_Pressed = true;
    setCursor(Qt::OpenHandCursor);
    return;
  }

  if (e->key() == Qt::Key_Escape) {
    BaseReset();
    return;
  }

  if (e->key() == Qt::Key_D && e->modifiers()) {
    MakePrintScreen();
    return;
  }

  if (e->key() == Qt::Key_S && e->modifiers()) {
    TmpSave();
    return;
  }

  if (e->key() == Qt::Key_V && e->modifiers()) {
    const QMimeData *data = QApplication::clipboard()->mimeData();
    if (data->hasImage()) {
      nrpic++;
      QImage images = qvariant_cast<QImage>(data->imageData());
      bool saved = images.save(origImageFilename, extension, 100);
      if (saved) {
        BaseReset();
      }
    }
    return;
  }

  ////////////////if( e->key() ==  Qt::Key_C)

  if (e->key() == Qt::Key_C && e->modifiers()) {
    QApplication::clipboard()->setImage(display.toImage(),
                                        QClipboard::Clipboard);
    return;
  }

  if (e->key() == Qt::Key_Plus) {
    int pluspuls = ratio + 1;
    SetZoom(pluspuls);
    return;
  }

  if (e->key() == Qt::Key_Minus) {
    int minuspuls = ratio - 1;
    SetZoom(minuspuls);
    return;
  }
}
void Interface::keyReleaseEvent(QKeyEvent *e) {
  setCursor(Qt::ArrowCursor);
  moverecci = false;
  CTRL_Pressed = false;
}

void Interface::Mousepress(QMouseEvent *e) /* mouse start */
{
  if (CTRL_Pressed) {
    setCursor(Qt::OpenHandCursor);
    return;
  }

  Dstart = QPoint(0, 0);
  if (e->button() == Qt::LeftButton && !CTRL_Pressed) {
    Dstart = ScalePoint(e->pos());
    setCursor(Qt::CrossCursor);
    moverecci = false;
    CTRL_Pressed = false;
  }
}

void Interface::Mousemove(QMouseEvent *e) /* mouse start */
{

  if (CTRL_Pressed && moverecci && TagliaPoi.width() > 10) {
    moverecci = true;
    CTRL_Pressed = true;

    setCursor(Qt::ClosedHandCursor);

    QRect TMPrect = TagliaPoi;

    Dmove = ScalePoint(e->pos());

    Dmove.setX(Dmove.x() - (TMPrect.width() / 2));
    Dmove.setY(Dmove.y() - (TMPrect.height() / 2));
    TMPrect.moveTo(Dmove);
    DisegnaRect(TMPrect.topLeft(), TMPrect.bottomRight());
    //////////////qDebug() << "####### TMPrect.width()  " << TMPrect.height() <<
    ///" TMPrect.width() " << TMPrect.width();
    //////////////////qDebug() << "####### TagliaPoi  " << TagliaPoi;
    return;
  }

  if (Dstart.x() > 0) {
    Dstop = ScalePoint(e->pos());
    DisegnaRect(Dstart, Dstop);
    setCursor(Qt::CrossCursor);
    moverecci = false;
    CTRL_Pressed = false;
  }
}

void Interface::mouseReleaseEvent(QMouseEvent *e) /* mouse start */
{
  setCursor(Qt::ArrowCursor);
  moverecci = false;
  CTRL_Pressed = false;
}

QPoint Interface::ScalePoint(QPoint p) {
  if (ratio == 100) {
    return p;
  } else {
    int ReX = (p.x() / ratio) * cento;
    int ReY = (p.y() / ratio) * cento;
    return QPoint(ReX, ReY);
  }
}

/* ##################################################################################
 */
/* ###################################event
 * mouse############################################### */
/* ##################################################################################
 */

void Interface::DisegnaRect(QPoint topLeft, QPoint bottomRight) {
  Top_startX = QMIN(topLeft.x(), bottomRight.x());
  Top_startY = QMIN(topLeft.y(), bottomRight.y());

  int Bot_endX = QMAX(topLeft.x(), bottomRight.x());
  int Bot_endY = QMAX(topLeft.y(), bottomRight.y());

  QPoint topLefta(Top_startX, Top_startY);
  QPoint bottomRighta(Bot_endX, Bot_endY);
  QRect areaplace(topLefta, bottomRighta);

  /*

  */

  TagliaPoi = areaplace;

  /////////////////qDebug() << "####### TagliaPoi.width()  " <<
  /// TagliaPoi.height();

  if (areaplace.width() > 9) {
    TagliaPoi = areaplace;
    QPen pen;
    pen.setStyle(Qt::SolidLine);

    pen.setWidth(2);
    if (ratio > 80 && ratio < 110) {
      pen.setWidth(2);
    }
    if (ratio < 81) {
      pen.setWidth(4);
    }
    if (ratio < 50) {
      pen.setWidth(6);
    }
    if (ratio > 130) {
      pen.setWidth(1);
    }

    pen.setColor(color1);
    QPixmap nuovo(original2.width(), original2.height());
    QPainter painter;
    painter.begin(&nuovo);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0, 0, original2);
    painter.setPen(pen);         /* penna */
    painter.drawRect(areaplace); /* disegna */
    painter.end();
    display = nuovo;
    int newlarge = (original2.width() / cento) * ratio;
    wrapper->paint(
        QPixmap(display.scaledToWidth(newlarge, Qt::FastTransformation)));
    setCursor(Qt::CrossCursor);
    UpdateNow();
  }
}

void Interface::wheelEvent(QWheelEvent *event) {
  int numDegrees = event->delta() / 8;
  int numTicks = numDegrees / 15;
  /////////////qDebug() << "###  wheelEvent numTicks " << numTicks;
  if (numTicks == 1) {
    int pluspuls = ratio + 1;
    SetZoom(pluspuls);
  } else {
    int minuspuls = ratio - 1;
    SetZoom(minuspuls);
  }
  QApplication::restoreOverrideCursor();
  return;
}

/* ##################################################################################
 */
/* ###################################event
 * mouse############################################### */
/* ##################################################################################
 */

void Interface::SetZoom(int percentual) {

  //////////////qDebug() << "####### percentual  " << percentual;
  if (original.isNull()) {
    return;
  }
  ////////////qDebug() << "####### percentual  " << percentual;
  ratio = percentual;
  QRect screenSize = qApp->desktop()->availableGeometry();
  int newlarge = (original.width() / cento) * percentual;
  display = original2.scaledToWidth(newlarge, Qt::FastTransformation);
  wrapper->paint(display);
  UpdateNow();
}

void Interface::closeEvent(QCloseEvent *e) { e->accept(); }

void Interface::SetColor() {
  color1 = qvariant_cast<QColor>(currentItemData(comboBox));
  wrapper->paint(display);
}

void Interface::populateWithColors(QComboBox *comboBox) {
  QPixmap pix(22, 22);

  QStringList colorNames = QColor::colorNames();
  foreach (QString name, colorNames) {
    pix.fill(QColor(name));
    comboBox->addItem(pix, name, QColor(name));
  }
}

QVariant Interface::currentItemData(QComboBox *comboBox) {
  return comboBox->itemData(comboBox->currentIndex());
}

int Interface::QMIN(int x, int y) {
  if (x < y) {
    return x;
  } else {
    return y;
  }
}

int Interface::QMAX(int x, int y) {
  if (x > y) {
    return x;
  } else {
    return y;
  }
}

int Interface::QRAPORT(int n, qreal r) {
  int x = (n / r) * cento;
  if (x < 1) {
    x = 0;
  }
  return x;
}

void Interface::populateFilter(QComboBox *comboBox) {
  QPixmap pix(22, 22);

  QStringList colorNames = QColor::colorNames();
  comboBox->addItem(tr("Select a filter.."));
  pix.fill(QColor("grey"));
  comboBox->addItem(pix, tr("GreyScale"));
  comboBox->addItem(tr("RGB Swapped"));
  comboBox->addItem(tr("InvertPixels color"));
  pix.fill(QColor(162, 128, 101));
  comboBox->addItem(pix, tr("Colorize") + QString(" color=\"sepia\""));
  comboBox->addItem(tr("Colorize") + QString(" color=\"mycolor\""));

  foreach (QString name, colorNames) {

    pix.fill(QColor(name));
    comboBox->addItem(pix, tr("Colorize") + QString(" color=\"%1\"").arg(name));
  }
}

void Interface::applyFilter(QString filtername) {
  QImage income(origImageFilename);
  QImage base = income.convertToFormat(QImage::Format_RGB32);
  int newlarge = (original.width() / cento) * ratio;
  int largeful = base.width();
  QPixmap result;
  if (base.isNull()) {
    return;
  }
  if (filtername == tr("Select a filter..")) {
    //////qDebug() << "### return " << filtername;
    return;
  }
  QColor gtr;
  comboBox_2->setCurrentIndex(0);
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  qDebug() << "### filtername " << filtername;
  /* start to pray filter */
  if (filtername.contains(tr("Colorize"))) {
    const QString colorn = BraketName(filtername);

    if (colorn == "sepia") {
      gtr = QColor(162, 128, 101);
    } else if (colorn == "mycolor") {
      QApplication::restoreOverrideCursor();
      QColor col = QColorDialog::getColor(QColor("red"), this);
      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
      gtr = col;
    } else {
      gtr = QColor(colorn);
    }
    ///////////qDebug() << "### colorn " << colorn;
    int sepiaH, sepiaS, sepiaL;
    ///////QColor(162,128,101).getHsv( &sepiaH, &sepiaS, &sepiaL );
    gtr.getHsv(&sepiaH, &sepiaS, &sepiaL);
    // iterate over each selected scanline
    int x, y, pixelLuminance;
    QRgb *rgb;
    QColor sepiaColor;
    uchar *scanLine;

    for (y = 0; y < base.height(); y++) {
      scanLine = base.scanLine(y);
      for (x = 0; x < base.width(); x++) {
        rgb = ((QRgb *)scanLine + x);
        pixelLuminance = (int)(0.2125 * qRed(*rgb) + 0.7154 * qGreen(*rgb) +
                               0.0721 * qBlue(*rgb));
        sepiaColor.setHsv(sepiaH, sepiaS, pixelLuminance);
        *rgb = sepiaColor.rgb();
      }
    }
    qDebug() << "### base.isNull() 1111  must see false!  " << base.isNull();
    result = QPixmap::fromImage(base);

  } else if (filtername == tr("GreyScale")) {

    result = QPixmap::fromImage(GreyScale(base));

  } else if (filtername == tr("RGB Swapped")) {

    base.rgbSwapped();
    result = QPixmap::fromImage(base);

  } else if (filtername == tr("InvertPixels color")) {

    base.invertPixels();
    result = QPixmap::fromImage(base);

  } else {

    return;
  }

  original = result;

  qDebug() << "### base.isNull() 333  must see false!  " << result.isNull();

  display = result.scaledToWidth(newlarge, Qt::FastTransformation);
  wrapper->paint(display);
  UpdateNow();

  QApplication::restoreOverrideCursor();
}

/*  Text edit & hyperlink if need  start  */

class QTextEdit;

class EditText : public QTextBrowser {
  Q_OBJECT
  //
public:
  EditText(QWidget *parent = 0);
  ~EditText();
  //// bool canInsertFromMimeData(const QMimeData *source);
  void insertFromMimeData(const QMimeData *source);

protected:
  void keyPressEvent(QKeyEvent *e);
  void mouseDoubleClickEvent(QMouseEvent *e);
signals:
  void DoubleClick_is_now();
  void CloseAllApp();
  void TakeImage(QString nuovaimagine);
public slots:
  void PrintScreen();
  void OpenNewDoc();
  void MakePrintScreen(); // 1
  void MakeBasicText();
  void PicsFromCopy(const QString filenew);
  void EditContext(const QPoint &pos);
  void Image_mod_Setting();
  void Request_Quit();
  void SaveCurrentDoc();
  void RepaintScreen();
  void printPreview(QPrinter *printer);
  void filePrintPreview();

private:
  int active_or_not; /// eine fortlaufende nummer..
  QShortcut *kurzeltastatur_0;
  QShortcut *kurzeltastatur_1;
  QTextImageFormat nowimage;
  QTextCursor lastcursor;
};

void EditText::filePrintPreview() {
  QPrinter printer(QPrinter::HighResolution);
  QPrintPreviewDialog preview(&printer, this);
  preview.setWindowFlags(Qt::Window);
  connect(&preview, SIGNAL(paintRequested(QPrinter *)),
          SLOT(printPreview(QPrinter *)));
  preview.exec();
}

void EditText::printPreview(QPrinter *printer) {
  this->document()->print(printer);
}

void EditText::SaveCurrentDoc() { qDebug() << "### SaveCurrentDoc ...   "; }

void EditText::RepaintScreen() {
  QTextDocument *xdoc = new QTextDocument();
  const QString html = this->document()->toHtml("utf_8");
  QTextDocument *d = this->document();
  this->setDocument(xdoc);
  this->document()->setHtml(html);
  qDebug() << "### RepaintScreen ..text.   ";
  this->document()->adjustSize();
  QTextCursor c(this->document());
  c.beginEditBlock();
}

void EditText::Request_Quit() {
  qDebug() << "### Request_Quit check file open`?  ";
  emit CloseAllApp();
}

EditText::EditText(QWidget *parent) : QTextBrowser(parent) {
  active_or_not = 0;
  setContextMenuPolicy(Qt::CustomContextMenu); //// auskommentiren wenn eine
                                               /// andere class zugreifen will.
  kurzeltastatur_0 =
      new QShortcut(QKeySequence(tr("Ctrl+W", "Print Screen")), this);
  connect(kurzeltastatur_0, SIGNAL(activated()), this, SLOT(MakePrintScreen()));
  kurzeltastatur_1 = new QShortcut((QKeySequence::Save), this);
  connect(kurzeltastatur_0, SIGNAL(activated()), this, SLOT(SaveCurrentDoc()));
  connect(this, SIGNAL(TakeImage(QString)), this, SLOT(PicsFromCopy(QString)));
  connect(this, SIGNAL(DoubleClick_is_now()), this, SLOT(Image_mod_Setting()));
  setContentsMargins(20, 20, 20, 20);
  this->resize(600, 500);
  this->setReadOnly(false); //// schreiben und lesen ..
  setMinimumWidth(400);
  setMinimumHeight(400);
  resize(500, 500);
  setWindowTitle(tr("Basic Editor Text & Image"));
  QTimer::singleShot(400, this, SLOT(MakeBasicText()));
  connect(this, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(EditContext(QPoint)));
}

void EditText::OpenNewDoc() { qDebug() << "### new doc open  "; }

void EditText::Image_mod_Setting() {
  //// qDebug() << "### open image here ";
  QString picname = nowimage.name();
  QFileInfo locinfo(picname);
  ///// qDebug() << "### imagexx ---" << nowimage.name();
  if (nowimage.isValid()) {
    Interface::self(this)->SetFormat(nowimage);
    Interface::self(this)->exec();
    QTextImageFormat newforminepic = Interface::self(this)->GetFormat();
    if (newforminepic.isValid()) {
      lastcursor.setCharFormat(newforminepic);
      QTimer::singleShot(20, this, SLOT(RepaintScreen()));
    }
  }
}

/* context menu */
void EditText::EditContext(const QPoint &pos) {
  qDebug() << "### contextMenuEvent   " << pos;
  QPixmap pix(22, 22);
  pix.fill(Qt::black);
  bool Eimage = false;
  QTextCursor c = this->textCursor();
  lastcursor = this->textCursor();
  int starta = c.selectionStart();
  int startb = c.selectionEnd();
  nowimage = c.charFormat().toImageFormat();
  qDebug() << "### valid image by cursor?   " << nowimage.isValid();
  QMenu *tt = new QMenu(this);
  tt->addAction(tr("Open other xhtml or html file"), this, SLOT(OpenNewDoc()));
  QAction *acopy = new QAction(tr("&Copy"), this);
  acopy->setShortcut(tr("Ctrl+C"));
  connect(acopy, SIGNAL(triggered()), this, SLOT(copy()));
  tt->addAction(acopy);
  QAction *apaste = new QAction(tr("&Paste"), this);
  apaste->setShortcut(tr("Ctrl+V"));
  connect(apaste, SIGNAL(triggered()), this, SLOT(paste()));
  tt->addAction(apaste);
  tt->addSeparator();

  if (nowimage.isValid()) {
    QString picname = nowimage.name();
    QFileInfo locinfo(picname);
    tt->addAction(
        tr("Image edit \"%1\" width - height").arg(locinfo.fileName()), this,
        SLOT(Image_mod_Setting()));
  }

  tt->addAction(tr("Print Preview"), this, SLOT(filePrintPreview()));
  tt->addSeparator();
  tt->addAction(tr("Close quit"), this, SLOT(Request_Quit()));
  tt->exec(QCursor::pos());
}

void EditText::MakeBasicText() {
  QString subtext = QString(
      "<h1>Hallo have a nice day...</h1> "
      "<p>press CTRL + W to hav a image printscreen..</p></br></br></br>");
  QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(subtext);
  this->textCursor().insertFragment(fragment);
}

EditText::~EditText() { active_or_not = 0; }

void EditText::PrintScreen() {
  QDesktopWidget *dw = QApplication::desktop();
  QPixmap desktopscreen =
      QPixmap::grabWindow(dw->winId(), 0, 0, dw->width(), dw->height());
  active_or_not++;
  const QString neuesbildsave =
      QString("%2/image_%1.png").arg(active_or_not).arg(QDir::homePath());
  /// speichere das bild und sag das ein bild da ist
  desktopscreen.save(neuesbildsave, "PNG", 100);
  emit TakeImage(neuesbildsave); /* and remove nuovaim  */
}

void EditText::PicsFromCopy(const QString filenew) {
  qDebug() << "### " << __FILE__ << "-" << __FUNCTION__ << "line:" << __LINE__;
  QString subtext = QString("<p><img src=\"%1\" />").arg(filenew);
  QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(subtext);
  this->textCursor().insertFragment(fragment);
}

void EditText::MakePrintScreen() {
  bool ok;
  int i = QInputDialog::getInt(
      0, tr("Wait Sec. to PrintScreen...."),
      tr("Wait Sec. to PrintScreen....<br>Sec: from 1/10"), 1, 1, 10, 1, &ok);
  if (ok && i > 0 && i < 11) {
    QTimer::singleShot(i * 1000, this, SLOT(PrintScreen()));
  }
}

/*
bool EditText::canInsertFromMimeData(const QMimeData *source) {
  qDebug() << "### " << __FILE__ << "-" << __FUNCTION__ << "line:" << __LINE__;
  return QTextEdit::canInsertFromMimeData(source);
}
*/

void EditText::keyPressEvent(QKeyEvent *e) { QTextBrowser::keyPressEvent(e); }

void EditText::mouseDoubleClickEvent(QMouseEvent *e) {
  qDebug() << "### mouseDoubleClickEvent ";
  emit DoubleClick_is_now();
  QTextEdit::mouseDoubleClickEvent(e);
}

void EditText::insertFromMimeData(const QMimeData *source) {
  qDebug() << "### " << __FILE__ << "-" << __FUNCTION__ << "line:" << __LINE__;
  //// in bild einfügen via ctrl + V
  if (source->hasImage()) {
    active_or_not++;
    QDateTime timer1(QDateTime::currentDateTime());
    const qint64 secsince70 = timer1.currentMSecsSinceEpoch();
    const QString neuesbildsave =
        QString("%2/image_%1.png").arg(secsince70).arg(QDir::homePath());
    QImage images = qvariant_cast<QImage>(source->imageData());
    bool salvato = images.save(neuesbildsave, "PNG", 100);
    if (salvato) {
      emit TakeImage(neuesbildsave); //// externes main holt bild und löschst..
                                     /// oder vrschieben
    }
  } else if (source->formats().contains("text/html")) {
    ////////qDebug() << "### incomming paste text/html  ";
    QString draghtml = source->html();
    QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(draghtml);
    textCursor().insertFragment(fragment);
    //// emit IncommingHTML(); //// tell to parent...
    return;
  } else {
    /// text plain einfügen macht dieser von natur aus ..
    QTextEdit::insertFromMimeData(source);
  }
}

/*  Text edit & hyperlink if need  stop  */

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  EditText w;
  w.show();
  w.connect(&w, SIGNAL(CloseAllApp()), &a, SLOT(quit()));
  w.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
  return a.exec();
}

#include "main.moc"
