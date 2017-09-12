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
 */
#ifndef EDITORKERNEL_H
#define EDITORKERNEL_H

#include "doc_session.h"
#include "oasimain.h"
#include "ui_forms.h"
#include <QObject>
#include <QTextBrowser>

#define TMPIMAGE QString("%1/zz_oasi_tmp_image.png").arg(QDir::homePath())

///// QTextBrowser or QTextEdit ?? big question
class EditorKernel : public QTextBrowser {
  Q_OBJECT
public:
  EditorKernel();
signals:
  void DoubleClick_is_now();
  void IncommingHTML();
  void TakeImage(QString); /// remove image source
public slots:
  void RepaintScreen();
  void Image_mod_Setting();
  void PrintScreen();

  void MakePrintScreen();
  void CreateanewTable();
  void insertImage(const QString filenew);
  void insertHtml(QString html);

  void MergeCellByCursorPosition();
  void RemoveRowByCursorPosition();
  void RemoveCoolByCursorPosition();
  void AppendTableRows();
  void AppendTableCools();
  void TableSetting();
  void SetTableCellColor();
  void SetColumLarge();

  void switchEditModus();
  void modus_edit(bool e);

  void CreateanewImage();
  void removeFormat();

public:
  QMenu *contenentContext;
  QMenu *tableContext;
  QMenu *imageContext;

  QTextImageFormat nowimage;
  QTextTable *nowtable;
  bool Eframe;
  bool Eimage;
  bool Etable;
  bool isqtextblok;
  QTextCursor lastcursor;
  int active_or_not;
  bool edit_yes;
  QShortcut *screenprint;
  ///// QShortcut *kurzeltastatur_1;

protected:
  void wheelEvent(QWheelEvent *event);
  void keyPressEvent(QKeyEvent *e);
  void mouseDoubleClickEvent(QMouseEvent *e);
  void contextMenuEvent(QContextMenuEvent *event);
  void insertFromMimeData(const QMimeData *source);
  bool gestureNative(QNativeGestureEvent *e);
  bool event(QEvent *e);
  qreal scaleFaktor;
  bool portrait_mode;
  qint64 lineTimer;
  qreal distanceswip;
};

#endif // EDITORKERNEL_H
