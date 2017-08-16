
#include "rtfdemo.h"
#include "rtfreader.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QTextDocumentWriter>
#include <QTextEdit>

#include "TextDocumentRtfOutput.h"

RtfDemo::RtfDemo() {
  QMenu *fileMenu = new QMenu("&File", this);

  QAction *openAction = fileMenu->addAction("&Open");
  openAction->setShortcut(QKeySequence::Open);

  m_saveTextAction = fileMenu->addAction("Save as Text");
  m_saveTextAction->setDisabled(true);

  m_saveHtmlAction = fileMenu->addAction("Save as HTML");
  m_saveHtmlAction->setDisabled(true);

  m_saveOdfAction = fileMenu->addAction("Save as ODF");
  m_saveOdfAction->setDisabled(true);

  QAction *closeAction = fileMenu->addAction("&Quit");
  closeAction->setShortcut(QKeySequence::Close);

  menuBar()->addMenu(fileMenu);

  connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
  connect(m_saveTextAction, SIGNAL(triggered()), this, SLOT(saveTextFile()));
  connect(m_saveHtmlAction, SIGNAL(triggered()), this, SLOT(saveHtmlFile()));
  connect(m_saveOdfAction, SIGNAL(triggered()), this, SLOT(saveOdfFile()));
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
}

RtfDemo::~RtfDemo() {
  // delete m_rtfDocument;
}

void RtfDemo::openFile() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "Open RTF file", QString(), "*.rtf");

  if (fileName.isEmpty()) {
    return;
  }

  RtfReader::Reader *reader = new RtfReader::Reader(this);

  bool result = reader->open(fileName);

  if (!result) {
    qDebug() << "failed to open file: " << fileName;
    return;
  }

  // delete m_rtfDocument;
  m_rtfDocument = new QTextDocument(this);
  RtfReader::TextDocumentRtfOutput *output =
      new RtfReader::TextDocumentRtfOutput(m_rtfDocument);

  reader->parseTo(output);

  QTextEdit *textEdit = new QTextEdit(this);
  setCentralWidget(textEdit);

  textEdit->setDocument(m_rtfDocument);

  m_saveTextAction->setEnabled(true);
  m_saveHtmlAction->setEnabled(true);
  m_saveOdfAction->setEnabled(true);
}

void RtfDemo::saveTextFile() {
  QString saveFileName =
      QFileDialog::getSaveFileName(this, "Save as Text", QString(), "*.txt");

  if (saveFileName.isEmpty()) {
    return;
  }

  QFile saveFile(saveFileName, this);

  bool openOk = saveFile.open(QIODevice::WriteOnly | QIODevice::Text);
  if (!openOk) {
    qDebug() << "failed to open for writing text:" << saveFileName;
  }

  QByteArray text = m_rtfDocument->toPlainText().toUtf8();

  saveFile.write(text);

  saveFile.close();
}

void RtfDemo::saveHtmlFile() {
  QString saveFileName =
      QFileDialog::getSaveFileName(this, "Save as HTML", QString(), "*.html");

  if (saveFileName.isEmpty()) {
    return;
  }

  QFile saveFile(saveFileName, this);

  bool openOk = saveFile.open(QIODevice::WriteOnly | QIODevice::Text);
  if (!openOk) {
    qDebug() << "failed to open for writing HTML:" << saveFileName;
  }

  QByteArray html = m_rtfDocument->toHtml("utf8").toUtf8();

  saveFile.write(html);

  saveFile.close();
}

void RtfDemo::saveOdfFile() {
  QString saveFileName =
      QFileDialog::getSaveFileName(this, "Save as ODF", QString(), "*.odt");

  if (saveFileName.isEmpty()) {
    return;
  }

  QFile saveFile(saveFileName, this);

  bool openOk = saveFile.open(QIODevice::WriteOnly | QIODevice::Text);
  if (!openOk) {
    qDebug() << "failed to open for writing ODF:" << saveFileName;
  }

  QTextDocumentWriter writer(&saveFile, "odf");
  writer.write(m_rtfDocument);

  saveFile.close();
}

