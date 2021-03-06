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
#ifndef OASIMAIN_H
#define OASIMAIN_H

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QColorDialog>
#include <QComboBox>
#include <QCoreApplication>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontComboBox>
#include <QFontDatabase>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QObject>
#include <QPointer>
#include <QSettings>
#include <QStatusBar>
#include <QSystemTrayIcon>
#include <QTextCodec>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QTextEdit>
#include <QTextList>
#include <QToolBar>
#include <QWidget>
#include <QtDebug>
#include <QtGui/QTextCharFormat>
#include <QtGui>

#ifdef QTPRINTSUPPORT_OK
#include <QPrinterInfo>
#include <QTextDocumentWriter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/qprintdialog.h>
#include <QtPrintSupport/qprinter.h>
#endif


#include "qdom.h"
#include "qtxmlglobal.h"
#include "qtxmlversion.h"
#include "qxml.h"
#include <QtCore/qstring.h>
#include <QtXml/QtXmlDepends>
#include <QtXml/qtxmlglobal.h>


#ifdef QT5SPEEHLOAD_OK
#include "editvoiceblock.h" /// compiler read block by block text
#include <QTextToSpeech>
#define SAYENABLE QString("console_or_module")
#endif

#ifdef UNIXCONSOLE_OPEN
#include "editvoiceblock.h" /// mac not need module go on console man say.
#ifndef SAYENABLE
#define SAYENABLE QString("console_or_module")
#endif
#endif

#ifndef UNIXCONSOLE_OPEN
/// access to speech no console && no module
#define SAYENABLE QString()
#endif


/// init to open file if exist
#define INITFILEPLAY QString("%1/loadme.htm").arg(QDir::homePath())


class VoiceBlock;
class EditorKernel;

class OasiMain : public QMainWindow {
  Q_OBJECT
public:
  explicit OasiMain(QWidget *parent = nullptr);
  ~OasiMain(void);

signals:
  void request_to_close();
public slots:
  void appsOpen(QString file);
  bool load(const QString &f);
  bool maybeSave();
  void setCurrentFileName(const QString &fileName);
  void fileNew();
  void fileOpen();
  bool fileSave();
  bool fileSaveAs();
  
  void textBold();
  void textUnderline();
  void textItalic();
  void textFamily(const QString &f);
  void textSize(const QString &p);
  void textStyle(int styleIndex);
  void textColor();
  void textAlign(QAction *a);
  void currentCharFormatChanged(const QTextCharFormat &format);
  void cursorPositionChanged();
  void clipboardDataChanged();
  void about();
  void showFront();
  //// if printer module:
#ifdef QTPRINTSUPPORT_OK
  void filePrint();
  void filePrintPreview();
  void filePrintPdf();
  void printPreview(QPrinter *);
#endif
  
  void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
  void fontChanged(const QFont &f);
  void colorChanged(const QColor &c);
  void alignmentChanged(Qt::Alignment a);
  void DocumentChanged();

  ////
  void setTextStatus2(const QString txt);
  void setTextMsg(const QString txt);
  void TextOnlyTray(const QString txt);
  //// voice read block by block
  void runReadBlocks();
  void stopReadBlocks();
  void enableVoiceged( bool e); /// enable or disable combo voice

  void setVoiceat(int voiceid);
  void convertTextMp3();

protected:
  QSystemTrayIcon *traytop;
  void drawall();
  void setupTextActions();
  void closeEvent(QCloseEvent *event);

  QAction *actionSave, *actionTextBold, *actionTextUnderline, *actionTextItalic,
      *actionTextColor, *actionAlignLeft, *actionAlignCenter, *actionAlignRight,
      *actionAlignJustify, *actionUndo, *actionRedo, *actionCut, *actionCopy,
      *actionPaste, *actionVoiceBlocks, *actionStopVoice, *actionDocTextmp3;

  QStatusBar *statusbar;
  QFontComboBox *comboFont;
  QComboBox *comboSize, *comboStyle, *combovoice;
  QLabel *statustxt2, *statustxt;

  QToolBar *tb;
  QFileInfo currentin;
  QString fileName;
  EditorKernel *base_edit;
  QGridLayout *gridLayout;
  bool enableedit;
  int currdocsize;
  int firstdocsize;
};

#endif // OASIMAIN_H
