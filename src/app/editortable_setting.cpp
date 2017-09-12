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
#include "editortable_setting.h"
#include "ui_forms.h"
#include <QCloseEvent>
//
QPointer<Table_Setting> Table_Setting::_self = 0L;
//
Table_Setting *Table_Setting::self(QWidget *parent) {
  if (!_self)
    _self = new Table_Setting(parent);
  return _self;
}
//
Table_Setting::Table_Setting(QWidget *parent) : QDialog(parent) {
  setupUi(this);
  setWindowFlags(Qt::Sheet);
}

void Table_Setting::SetFormat(QTextTable *existingtable) {
  /*  QTextTableFormat  */

  format_table = existingtable;     /* QTextTable */
  formtab = format_table->format(); /* QTextTableFormat  */
  xpadding = formtab.cellPadding();
  xspacing = formtab.cellSpacing();

  intborder = formtab.border();
  int bordert = intborder;
  tapadding->setValue(xpadding);
  taspacing->setValue(xspacing);
  vborder->setValue(bordert);
  trolengh = formtab.width();
  int tablelargo = trolengh.rawValue();
  largotable->setValue(tablelargo);

  xbgcolor = formtab.background();
  normalcolor = xbgcolor.color();
  setfoundalign = 0;
  allineaesistente = formtab.alignment();
  QStringList palign;
  palign << "[1] AlignLeft"
         << "[2] AlignRight"
         << "[4] AlignHCenter";
  xalign->clear();
  xalign->addItems(palign);

  if (allineaesistente > 0) {
    if (allineaesistente == 1) {
      setfoundalign = 0;
    } else if (allineaesistente == 2) {
      setfoundalign = 1;
    } else if (allineaesistente == 4) {
      setfoundalign = 2;
    }
  }
  if (setfoundalign > 0) {
    xalign->setCurrentIndex(setfoundalign);
  }

  QPixmap pix(22, 22);
  pix.fill(normalcolor);

  TableColor = new QAction(pix, tr("Table Background Color"), this);
  connect(TableColor, SIGNAL(triggered()), this, SLOT(ChoisColor()));
  tablecolor->setDefaultAction(TableColor);
  connect(xalign, SIGNAL(currentIndexChanged(int)), this,
          SLOT(UpdateFormats()));
  connect(largotable, SIGNAL(valueChanged(int)), this, SLOT(UpdateFormats()));
  connect(tapadding, SIGNAL(valueChanged(double)), this, SLOT(UpdateFormats()));
  connect(taspacing, SIGNAL(valueChanged(double)), this, SLOT(UpdateFormats()));
  connect(vborder, SIGNAL(valueChanged(int)), this, SLOT(UpdateFormats()));
}

void Table_Setting::ChoisColor() {
  QColor bcol = QColorDialog::getColor(normalcolor, this);
  if (bcol.isValid()) {
    normalcolor = bcol;
    QPixmap pix(22, 22);
    pix.fill(bcol);
    TableColor->setIcon(pix);
    UpdateFormats();
  }
}

void Table_Setting::UpdateFormats() {
  /* header QTextTableFormat formtab; */
  QBrush newcolorsett(normalcolor, Qt::SolidPattern);
  formtab.setBackground(newcolorsett);
  formtab.setCellPadding(tapadding->value());
  formtab.setCellSpacing(taspacing->value());
  /////int newalign = BraketNummer(xalign->currentText());
  QTextLength newlargos(QTextLength::PercentageLength, largotable->value());
  formtab.setWidth(newlargos);
  formtab.setBorder(vborder->value());

  /*
  qDebug() << "### newalign " << newalign;
  qDebug() << "### newpadding " << tapadding->value();
  qDebug() << "### newspacing " << taspacing->value();

  if (newalign == 1) {
    formtab.setAlignment(Qt::AlignLeft);
  } else if (newalign == 2) {
    formtab.setAlignment(Qt::AlignRight);
  } else if (newalign == 4) {
    formtab.setAlignment(Qt::AlignHCenter);
  }
  */
}

QTextTableFormat Table_Setting::GetNewFormats() { return formtab; }

void Table_Setting::closeEvent(QCloseEvent *e) {
  UpdateFormats();
  e->accept();
}
