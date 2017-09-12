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
#ifndef EDITORTABLE_SETTING_H
#define EDITORTABLE_SETTING_H

#include <QObject>
#include <QWidget>

#include <QActionGroup>
#include <QByteArray>
#include <QColorDialog>
#include <QDebug>
#include <QErrorMessage>
#include <QFile>
#include <QFileDialog>
#include <QFontDatabase>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QProcess>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QTextBlockFormat>
#include <QTextCodec>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QTextFormat>
#include <QTextLength>
#include <QTextList>
#include <QTextListFormat>
#include <QTextStream>
#include <QTextTable>
#include <QTextTableCell>
#include <QTextTableFormat>

#include "ui_forms.h"

/*  Save file as table_setting.h  */
/*  Class Table_Setting Created on Tue Sep 12 13:46:10 CEST 2006  */
//
#include <QPointer>
//
class Table_Setting : public QDialog, public Ui::Table_Setting {
  Q_OBJECT
  //
public:
  static Table_Setting *self(QWidget * = 0);
  void SetFormat(QTextTable *existingtable);
  QTextTableFormat GetNewFormats();
  //
protected:
  void closeEvent(QCloseEvent *);
  //
private:
  Table_Setting(QWidget * = 0);
  static QPointer<Table_Setting> _self;
  QTextTable *format_table;
  QTextTableFormat formtab;
  QTextLength trolengh;
  qreal xpadding;
  qreal xspacing;
  QBrush xbgcolor;
  int setfoundalign;
  int allineaesistente;
  qreal intborder;
  QColor normalcolor;
  QAction *TableColor;
  QPixmap pix;
  //
public slots:
  void ChoisColor();
  void UpdateFormats();
};

#endif // EDITORTABLE_SETTING_H
