/*
    Copyright (C)  2017 Piter K. <pehohlva@gmail.com>

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    History This file was a part from my own projects
    https://sourceforge.net/projects/wysiwyg-edit/
    https://code.google.com/archive/p/fop-miniscribus/
    old Link https://de.wikipedia.org/wiki/Extensible_Stylesheet_Language_%E2%80%93_Formatting_Objects
    XSL-FO Wysiwyg MiniScribus / XHTML Qeditor
    in 2008 - 2013 adapted from QT4.8 to QT5.9
*/

#ifndef IMAGEEDIT_H
#define IMAGEEDIT_H

#include "oasimain.h"
#include "ui_forms.h"
#include <QObject>

class ImageEdit {
public:
  ImageEdit();
};

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
      Q_UNUSED(e);
    QPainter painter;
    QBrush nowis(QColor(Qt::transparent), Qt::SolidPattern);
    painter.setBrush(nowis);
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
  QImage GetImage() { return display.toImage(); }

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

#endif // IMAGEEDIT_H
