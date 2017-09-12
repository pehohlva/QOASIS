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
#include "editorkernel.h"
#include "oasimain.h"
#include <QImage>
#include <QTextBrowser>
#include <Qfile>

#include "doc_session.h"
#include "editortable_setting.h"
#include "imageedit.h"
#include "ui_forms.h"


EditorKernel::EditorKernel() : QTextBrowser(), scaleFaktor(1.367) {
  edit_yes = true;
  active_or_not = 10;
  modus_edit(edit_yes);
  this->setContentsMargins(0, 0, 0, 0);
  screenprint = new QShortcut(QKeySequence(tr("Ctrl+W", "Print Screen")), this);
  connect(screenprint, SIGNAL(activated()), this, SLOT(MakePrintScreen()));
  this->setFont(QFont(_WORKDEFAULTFONT_));
}

void EditorKernel::switchEditModus() {
  if (edit_yes) {
    edit_yes = false;
    modus_edit(false);
  } else {
    edit_yes = true;
    modus_edit(false);
  }
}

void EditorKernel::modus_edit(bool e) {
  if (e) {
    //// edit...
    setOpenExternalLinks(false);
    setOpenLinks(false);
    setOverwriteMode(true);
    setReadOnly(false);
  } else {
    /// view
    setOpenExternalLinks(true);
    setOpenLinks(true);
    setOverwriteMode(false);
    setReadOnly(true);
  }
}

void EditorKernel::insertImage(const QString filenew) {
  QImage xpic;
  xpic.load(filenew);
  if (!xpic.isNull()) {
    QDateTime timer1(QDateTime::currentDateTime());
    const qint64 sec1970 = timer1.currentMSecsSinceEpoch();
    QString randomname = QString::number(sec1970) + QString(".png");
    QTextImageFormat format;
    format.setWidth(xpic.width());
    format.setHeight(xpic.height());
    format.setName(randomname);
    this->textCursor().insertImage(format);
    this->document()->addResource(QTextDocument::ImageResource,
                                  QUrl(randomname), xpic);

    QFile fips(TMPIMAGE);
    if (fips.exists()) {
      ///// fips.remove();
    }

  } else {
    qDebug() << "### pic xpic.isNull()-> " << xpic.isNull();
  }
}

void EditorKernel::Image_mod_Setting() {
  QFile fips(TMPIMAGE);
  if (fips.exists()) {
    fips.remove();
  }
  const QString picname = nowimage.name();
  if (picname.isEmpty()) {
    return;
  }
  QDateTime timer1(QDateTime::currentDateTime());
  ///// const qint64 sec1970 = timer1.currentMSecsSinceEpoch();
  QVariant img = this->document()->resource(QTextDocument::ImageResource,
                                            picname); //// get image
  QImage imgxx = img.value<QImage>();
  qDebug() << "### picnamepicnamepicnamepicnamepicnamepicname origin  "
           << imgxx.width();
  imgxx.save(TMPIMAGE, "PNG", 9);
  if (nowimage.isValid()) {
    Interface::self(this)->SetFormat(nowimage);
    Interface::self(this)->SetPic(TMPIMAGE);
    Interface::self(this)->exec();

    QImage imgswap;
    imgswap.load(TMPIMAGE, "PNG");
    qDebug() << "### picnamepicnamepicnamepicnamepicnamepicname swap  "
             << imgswap.width();
    QTextImageFormat newforminepic = Interface::self(this)->GetFormat();
    if (newforminepic.isValid()) {
      if (!imgswap.isNull()) {
        const qint64 sec1970 = timer1.currentMSecsSinceEpoch();
        QString randomname = QString::number(sec1970) + QString(".png");
        QTextImageFormat format;
        format.setWidth(imgswap.width());
        format.setHeight(imgswap.height());
        format.setName(randomname);
        QTextDocumentFragment fragment =
            QTextDocumentFragment::fromHtml(QString("<p></br></p>"));
        this->textCursor().insertFragment(fragment);
        this->textCursor().insertImage(format);
        this->document()->addResource(QTextDocument::ImageResource,
                                      QUrl(randomname), imgswap);

      } else {
        qDebug() << "###  image is null ";
      }
      /////// insertImage(TMPIMAGE); //// become new name..
      ///// QTimer::singleShot(200, this, SLOT(RepaintScreen()));
    }
  }
}

void EditorKernel::contextMenuEvent(QContextMenuEvent *event) {
  QMenu *menu = this->createStandardContextMenu();
  menu->addAction(QIcon(QString::fromUtf8(":/images/mac/filenew.png")),
                  tr("Remove Format Font size all.."), this,
                  SLOT(removeFormat()));
  menu->addSeparator();

  QPixmap pix(22, 22);
  pix.fill(Qt::black);
  bool Eimage = false;
  QTextCursor c = this->textCursor();
  lastcursor = this->textCursor();

  QTextBlock textblocc = lastcursor.block();

  Eframe = lastcursor.currentFrame();
  nowimage = lastcursor.charFormat().toImageFormat();
  nowtable = lastcursor.currentTable();
  Eimage = nowimage.isValid();
  Etable = lastcursor.currentTable();
  isqtextblok = textblocc.isValid();
  //// QAction *addAction(const QIcon &icon, const QString &text, const QObject
  ///*receiver, const char* member, const QKeySequence &shortcut = 0);

  if (nowimage.isValid()) {
    QString picname = nowimage.name();
    QFileInfo locinfo(picname);
    menu->addAction(
        QIcon(QString::fromUtf8(":/images/pictures.png")),
        tr("Image edit \"%1\" width - height").arg(locinfo.fileName()), this,
        SLOT(Image_mod_Setting()));
  }

  menu->addAction(QIcon(QString::fromUtf8(":/images/pictures.png")),
                  tr("Insert new image/images Multiselect"), this,
                  SLOT(CreateanewImage()));
  menu->addAction(QIcon(QString::fromUtf8(":/images/pictures.png")),
                  tr("Grab Print Screen"), this, SLOT(MakePrintScreen()),
                  QKeySequence(tr("Ctrl+W")));

  tableContext = new QMenu(tr("Table Option"), this);
  tableContext->setIcon(QIcon(QString::fromUtf8(":/images/table.png")));
  tableContext->addAction(tr("Insert Table here"), this,
                          SLOT(CreateanewTable()));

  menu->addMenu(tableContext);
  //// menu->addMenu(imageContext);

  if (lastcursor.currentTable()) {
    tableContext->addAction(
        QIcon(QString::fromUtf8(":/images/table.png")),
        tr("Table (this) Propriety BackgroundColor, Padding, Spacing"), this,
        SLOT(TableSetting()));
    tableContext->addAction(QIcon(QString::fromUtf8(":/images/row_table.png")),
                            tr("Merge selected cell (if select)"), this,
                            SLOT(MergeCellByCursorPosition()));
    tableContext->addAction(tr("Append Row on this table"), this,
                            SLOT(AppendTableRows()));
    tableContext->addAction(tr("Append Cools on this table"), this,
                            SLOT(AppendTableCools()));
    tableContext->addAction(tr("Remove this row"), this,
                            SLOT(RemoveRowByCursorPosition()));
    tableContext->addAction(tr("Remove this cool"), this,
                            SLOT(RemoveCoolByCursorPosition()));
    tableContext->addAction(tr("Set Cell backgroundColor"), this,
                            SLOT(SetTableCellColor()));
    tableContext->addAction(tr("Set Cell Width"), this, SLOT(SetColumLarge()));
  }
  qDebug() << "### xxxx  " << event->globalPos();
  menu->popup(event->globalPos());
}

void EditorKernel::CreateanewImage() {
  QStringList pics = QFileDialog::getOpenFileNames(
      this, tr("Choose Image"),
      QString(DOC::self(this)->value("LastDirImage").toString()),
      tr("Image Files supported (*)"));
  if (pics.size() < 1) {
    return;
  }
  bool oki = true;
  for (int x = 0; x < pics.size(); x++) {
    QFileInfo fox(pics.at(x));
    QImage base;
    base.load(fox.absoluteFilePath());
    if (!base.isNull()) {
      DOC::self(this)->setValue("LastDirImage", QVariant(fox.absolutePath()));
      insertImage(fox.absoluteFilePath());
    } else {
      oki = false;
    }
  }
  if (!oki) {
    QMessageBox::warning(
        this, tr("Image Plugin"),
        tr("Pleas install the plugin for this format.. or select other..\nOr "
           "copy and paste image from your images application. \nTo convert on "
           "web image. png jpg gif"));
    return;
  }
}

void EditorKernel::SetColumLarge() {
  /* QTextTable  *nowtable; */
  QTextCursor findercursor(this->textCursor());
  Etable = findercursor.currentTable();
  if (Etable) {
    QTextTableCell existingcell = nowtable->cellAt(findercursor);

    QTextTableFormat tbforms = nowtable->format();

    int cellcoolcursoris =
        existingcell.column(); /* int value start from zero */
    /* get lengh % to set on cell .... */
    bool ok;
    int LargeSet =
        QInputDialog::getInt(this, tr("Set Cell Width"),
                             tr("Percentage Length:"), 10, 1, 100, 1, &ok);
    if (ok && LargeSet > 0) {
      QVector<QTextLength> constraints = tbforms.columnWidthConstraints();
      for (int i = 0; i < constraints.size(); ++i) {
        if (i == cellcoolcursoris) {
          constraints.replace(
              i, QTextLength(QTextLength::PercentageLength, LargeSet));
        }
      }
      tbforms.setColumnWidthConstraints(constraints);

      nowtable->setFormat(tbforms);
    }
  }
}

void EditorKernel::SetTableCellColor() {
  /* QTextTable  *nowtable; */
  QTextCursor findercursor(this->textCursor());
  Etable = findercursor.currentTable();
  if (Etable) {
    bool ok;
    QTextTableCell existingcell = nowtable->cellAt(findercursor);
    /* reformat this -> existingcell */
    QTextCharFormat existformat = existingcell.format();
    /* get color */
    QColor opop(Qt::transparent);
    QColor col = QColorDialog::getRgba(000000, &ok, this);
    if (!col.isValid()) {
      return;
    }
    QBrush stylesin(col);
    existformat.setBackground(stylesin);
    existingcell.setFormat(existformat);
  }
}

void EditorKernel::MakePrintScreen() {
  bool ok;
  int i = QInputDialog::getInt(
      0, tr("Wait Sec. to PrintScreen...."),
      tr("Wait Sec. to PrintScreen....<br>Sec: from 1/10"), 1, 1, 10, 1, &ok);
  if (ok && i > 0 && i < 11) {
    QTimer::singleShot(i * 1000, this, SLOT(PrintScreen()));
  }
}

void EditorKernel::insertFromMimeData(const QMimeData *source) {
  if (source->hasImage()) {
    active_or_not++;
    QDateTime timer1(QDateTime::currentDateTime());
    const qint64 secsince70 = timer1.currentMSecsSinceEpoch();
    const QString localimage =
        QString("%2/image_%1.png").arg(secsince70).arg(QDir::homePath());
    QImage image = qvariant_cast<QImage>(source->imageData());
    bool salvato = image.save(localimage, "PNG", 100);
    if (salvato) {
      emit TakeImage(localimage);
      QUrl urlpics = QUrl::fromLocalFile(localimage);
      document()->addResource(QTextDocument::ImageResource, urlpics,
                              QVariant(image));
    }
  } else if (source->formats().contains("text/html")) {
    QString draghtml = source->html();
    QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(draghtml);
    textCursor().insertFragment(fragment);
    emit IncommingHTML(); //// tell to parent...
    return;
  } else {
    QTextEdit::insertFromMimeData(source);
  }
}

void EditorKernel::PrintScreen() {
  QFile fips(TMPIMAGE);
  if (fips.exists()) {
    fips.remove();
  }
  QDesktopWidget *dw = QApplication::desktop();
  QPixmap desktopscreen =
      QPixmap::grabWindow(dw->winId(), 0, 0, dw->width(), dw->height());
  desktopscreen.save(TMPIMAGE, "PNG", 100);
  insertImage(TMPIMAGE);
}

void EditorKernel::insertHtml(QString html) {
  QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(html);
  this->textCursor().insertFragment(fragment);
}

void EditorKernel::mouseDoubleClickEvent(QMouseEvent *e) {
  emit DoubleClick_is_now();

  if (lastcursor.currentTable()) {
    TableSetting();
    return;
  }

  QTextEdit::mouseDoubleClickEvent(e);
}

void EditorKernel::keyPressEvent(QKeyEvent *e) {

  QTextBrowser::keyPressEvent(e);
}

void EditorKernel::CreateanewTable() {

  QString subtext, collx, rowx;
  bool ok;
  int colonne = QInputDialog::getInt(this, tr("New Table cool"), tr("Cool:"), 3,
                                     1, 10, 1, &ok);
  int righe = QInputDialog::getInt(this, tr("New Table row"), tr("Row:"), 3, 1,
                                   100, 1, &ok);
  int largo = QInputDialog::getInt(this, tr("New Table percent on page"),
                                   tr("Percent \%:"), 100, 10, 100, 1, &ok);
  if (colonne > 0 and righe > 0 and largo > 0) {
    QStringList tables;
    tables.clear();
    tables.append(
        QString("<table border=\"1\" align=\"center\" width=\"%1%\" "
                "cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"#ffffff\">")
            .arg(largo));
    for (int i = 0; i < righe; i++) {
      tables.append(QString("<tr>"));
      for (int o = 0; o < colonne; o++) {
        tables.append(QString("<td><p></p></td>"));
      }
      tables.append(QString("</tr>"));
    }
    tables.append(QString("</table>"));

    subtext = tables.join("\n");
    QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(subtext);
    this->textCursor().insertFragment(fragment);
  }
}

void EditorKernel::MergeCellByCursorPosition() {
  QTextCursor findercursor(this->textCursor());
  Etable = findercursor.currentTable();
  if (Etable) {
    nowtable->mergeCells(findercursor);
  }
}

void EditorKernel::RemoveRowByCursorPosition() {
  QTextCursor findercursor(this->textCursor());
  Etable = findercursor.currentTable();
  if (Etable) {
    QTextTableCell existingcell = nowtable->cellAt(findercursor);
    ///// int cellcoolcursoris = existingcell.column();                /* int value start from zero */
    int cellrowcursoris = existingcell.row(); /* int value start from zero */
    nowtable->removeRows(cellrowcursoris, 1);
  }
}

void EditorKernel::RemoveCoolByCursorPosition() {
  QTextCursor findercursor(this->textCursor());
  Etable = findercursor.currentTable();
  if (Etable) {
    QTextTableCell existingcell = nowtable->cellAt(findercursor);
    int cellcoolcursoris =
        existingcell.column();                /* int value start from zero */
    /// int cellrowcursoris = existingcell.row(); /* int value start from zero */
    nowtable->removeColumns(cellcoolcursoris, 1);
  }
}

void EditorKernel::AppendTableRows() {
  bool ok = false;
  QTextCursor findercursor(this->textCursor());
  Etable = findercursor.currentTable();
  if (Etable) {
    QTextTableCell existingcell = nowtable->cellAt(findercursor);
    int cellcoolcursoris =
        existingcell.column();                /* int value start from zero */
    Q_UNUSED(cellcoolcursoris);
    int cellrowcursoris = existingcell.row(); /* int value start from zero */
    int approwtot = QInputDialog::getInt(this, tr("Append  line row"),
                                         tr("Row:"), 1, 1, 100, 1, &ok);
    if (ok and approwtot > 0) {
      nowtable->insertRows(cellrowcursoris + 1, approwtot);
    }
  }
}

void EditorKernel::AppendTableCools() {
  bool ok = false;
  QTextCursor findercursor(this->textCursor());
  Etable = findercursor.currentTable();
  if (Etable) {
    QTextTableCell existingcell = nowtable->cellAt(findercursor);
    int cellcoolcursoris =
        existingcell.column();                /* int value start from zero */
    int cellrowcursoris = existingcell.row(); /* int value start from zero */
    Q_UNUSED(cellrowcursoris);
    int appcooltot = QInputDialog::getInt(this, tr("Table Column nr."),
                                          tr("Cool:"), 1, 1, 10, 1, &ok);
    if (ok and appcooltot > 0) {
      nowtable->insertColumns(cellcoolcursoris + 1, appcooltot);
    }
  }
}

void EditorKernel::TableSetting() {
  QTextCursor currentable = this->textCursor();
  Etable = currentable.currentTable();
  if (Etable) {
    Table_Setting::self(this)->SetFormat(nowtable);
    Table_Setting::self(this)->exec();
    QTextTableFormat newformine = Table_Setting::self(this)->GetNewFormats();
    if (newformine.isValid()) {
      nowtable->setFormat(newformine);
    }
  }
}

/*  fast & effektfull */
void EditorKernel::RepaintScreen() {
  QTextDocument *xdoc = new QTextDocument();
  const QString html = this->document()->toHtml("utf_8");
  QTextDocument *d = this->document();
  this->setDocument(xdoc);
  this->document()->setHtml(html);
  this->document()->adjustSize();
  this->setDocument(d);
  QTextCursor c(this->document());
  c.beginEditBlock();
  switchEditModus(); /// reset to last modus..
}

bool EditorKernel::event(QEvent *e) {
  if (e->type() == QEvent::NativeGesture) {
    return gestureNative(static_cast<QNativeGestureEvent *>(e));
  } else if (e->type() == QEvent::ContextMenu) {
    contextMenuEvent(static_cast<QContextMenuEvent *>(e));
    e->accept();
  }
  return QTextEdit::event(e);
}

void EditorKernel::removeFormat() {
  QString txt = this->document()->toPlainText();
  QChar doti('.');
  txt.replace(doti,QLatin1String(". \n"));
  this->document()->clear();
  this->document()->setPlainText(txt);
}

void EditorKernel::wheelEvent(QWheelEvent *event) {
  if (Qt::ControlModifier & event->modifiers()) {
    if (event->delta() > 0)
      zoomIn();
    else
      zoomOut();
  } else
    QTextBrowser::wheelEvent(event);
}

bool EditorKernel::gestureNative(QNativeGestureEvent *e) {

  if (e->type() == QEvent::NativeGesture) {
    if (e->value() < 0) {
      zoomIn();
    } else {
      zoomOut();
    }
  }
  SESSDEBUG() << "events-" << e->value();
  e->accept();
  return true;
}
