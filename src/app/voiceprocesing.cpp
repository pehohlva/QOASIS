#include "voiceprocesing.h"

/*  make numeric a QString summ from unicode used plus year code..
 its faster to find in html code e pages.. */
 int genkeyname(const QString name) {
  int base = 0;
  int xsize = name.size();
  if (xsize > 55) {
    xsize = 54;
  }
  for (int o = 0; o < xsize; o++) {
    const QChar vox(name.at(o));
    const int unico = (int)vox.unicode();
    base += unico;
  }
  base += 2017;
  return base;
}

VoiceProcesing::VoiceProcesing(QWidget *parent)
    : QDialog(parent)
{
    setObjectName(QStringLiteral("VoiceProcesing"));
    resize(509, 120);
    setMinimumSize(QSize(509, 140));
    setMaximumSize(QSize(800,444));
    QWidget::setWindowFlags( Qt::WindowSystemMenuHint | Qt::CustomizeWindowHint | Qt::Sheet);
    QWidget::setWindowModality(Qt::ApplicationModal);
    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    textEdit->setLineWrapMode(QTextEdit::NoWrap);

    progreso = new QProgressBar;
    progreso->setObjectName(QStringLiteral("processo"));
    progreso->setValue(0);
    progreso->setMaximum(100);
    progreso->setMinimum(0);
    closeButton = new QPushButton(tr("&Abort - Cancell"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(progreso);
    layout->addWidget(closeButton);
    setLayout(layout);
    setWindowTitle(tr("VoiceProcesing"));

}

VoiceProcesing::~VoiceProcesing()
{

}
