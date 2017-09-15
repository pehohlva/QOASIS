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

#include "voiceprocesing.h"
#include "doc_session.h"
#include <QPointer>
#include <QDesktopServices>

/* 
terminal:   say --file-format ?
3gp2  3GPP-2 Audio         (.3g2) [Qclp,aac,aace,aacf,aach,aacl,aacp]
3gpp  3GP Audio            (.3gp) [Qclp,aac,aace,aacf,aach,aacl,aacp]
AIFC  AIFC                 (.aifc,.aiff,.aif) [lpcm,ulaw,alaw,ima4,Qclp]
AIFF  AIFF                 (.aiff,.aif) [lpcm]
NeXT  NeXT/Sun             (.snd,.au) [lpcm,ulaw]
Sd2f  Sound Designer II    (.sd2) [lpcm]
WAVE  WAVE                 (.wav) [lpcm,ulaw,alaw]
adts  AAC ADTS             (.aac,.adts) [aac,aach,aacp]
caff  CAF                  (.caf)
[Qclp,aac,aace,aacf,aach,aacl,aacp,alac,alaw,ilbc,ima4,lpcm,ulaw] m4af  Apple
MPEG-4 Audio   (.m4a,.m4r) [aac,aace,aacf,aach,aacl,aacp,alac] m4bf  Apple
MPEG-4 AudioBooks (.m4b) [aac,aace,aacf,aach,aacl,aacp] mp4f  MPEG-4 Audio
(.mp4) [aac,aace,aacf,aach,aacl,aacp] */

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

QPointer<VoiceProcesing> VoiceProcesing::_self = 0L;

VoiceProcesing *VoiceProcesing::self(QWidget *parent) {
  if (!_self)
    _self = new VoiceProcesing(parent);
  return _self;
}

VoiceProcesing::VoiceProcesing(QWidget *parent) : QDialog(parent) {
  cursorp = 0;
  cnow = idle;
  setObjectName(QStringLiteral("VoiceProcesing"));
  setMinimumSize(QSize(680, 180));
  setMaximumSize(QSize(700, 180));
  QWidget::setWindowFlags(Qt::WindowSystemMenuHint | Qt::CustomizeWindowHint |
                          Qt::Sheet);
  QWidget::setWindowModality(Qt::ApplicationModal);

  gridLayout = new QGridLayout(this);
  gridLayout->setObjectName(QStringLiteral("gridLayout"));
  label_2 = new QLabel(this);
  label_2->setObjectName(QStringLiteral("label_2"));

  gridLayout->addWidget(label_2, 0, 0, 1, 1);

  voiceformat = new QComboBox(this);
  voiceformat->setObjectName(QStringLiteral("voiceformat"));

  voicenames = new QComboBox(this);
  voicenames->setObjectName(QStringLiteral("voicenames"));

  gridLayout->addWidget(voicenames, 0, 1, 1, 3);
  this->setVoices(); /// fill data here

  progreso = new QProgressBar(this);
  progreso->setValue(0);
  progreso->setMaximum(100);
  progreso->setMinimum(0);

  gridLayout->addWidget(progreso, 1, 0, 1, 4);

  label = new QLabel(this);
  label->setText(QStringLiteral("Audio Format:"));
  label->setObjectName(QStringLiteral("label"));

  gridLayout->addWidget(label, 2, 0, 1, 1);
  gridLayout->addWidget(voiceformat, 2, 1, 1, 1);
  startaction = new QPushButton(tr("&Start...."));
  gridLayout->addWidget(startaction, 2, 2, 1, 1);
  abortation = new QPushButton(tr("&Abort - Close"));
  gridLayout->addWidget(abortation, 2, 3, 1, 1);
  label_3 = new QLabel(this);
  label_3->setObjectName(QStringLiteral("label_3"));
  QString settime = QString("%1").arg(QTime(0, 0).addMSecs(1).toString());
  label_3->setText(settime);
  label_3->setFixedWidth(77);
  gridLayout->addWidget(label_3, 2, 4, 1, 1);
  this->setLayout(gridLayout);
  setWindowTitle(tr("VoiceProcesing"));
  QObject::connect(startaction, SIGNAL(clicked()), this, SLOT(startAction()));
  QObject::connect(abortation, SIGNAL(clicked()), this, SLOT(closeallcyle()));
  QObject::connect(this, SIGNAL(setValuePros(int)), progreso,
                   SLOT(setValue(int)));
  QObject::connect(voicenames, SIGNAL(activated(int)), this,
                   SLOT(setVoiceatd(int)));
  QObject::connect(voiceformat, SIGNAL(activated(int)), this,
                   SLOT(setFormatdAudioOut(int)));
}

void VoiceProcesing::updateProgress() {

  if (cnow == stop) {
    return; /// end transform
  }
  cursorp++;
  if (cursorp == 101) {
    cursorp = 0;
  }
  qint64 tt = timer.elapsed();
  QString settime = QString("%1").arg(QTime(0, 0).addMSecs(tt).toString());
  label_3->setText(settime);
  const int timeintervall = 20;
  QTimer::singleShot(timeintervall, this, SLOT(updateProgress()));
  emit setValuePros(cursorp);
}

void VoiceProcesing::closeallcyle() {
  cnow = stop;
  timer.restart();
  progreso->setValue(0);
  voicenames->setEnabled(true);
  startaction->setDisabled(false);
  this->close();
}

void VoiceProcesing::setVoiceatd(int voiceid) {
  voicenames->setEnabled(false);
  const int myvoice = voicenames->itemData(voiceid).toInt();
  Voicecurrent = VoiceBlock::self(this)->TakeVoiceId(myvoice);
  voicenames->setEnabled(true);
}

void VoiceProcesing::setVoices() {
  QList<Voice> vitem = VoiceBlock::self(this)->avaiableVoices();
  QList<Voice>::const_iterator x;
  voicenames->clear();
  const int localvoi = DOC::self(this)
                           ->value("SYSTEMLOCALEVOICE")
                           .toInt();
  int uservoice = DOC::self(this)->value("MyVoicePref").toInt();
  if (uservoice < 10) {
    uservoice = localvoi;
  }
  for (x = vitem.constBegin(); x != vitem.constEnd(); ++x) {
    Voice fox = *x;
    QString name = QString("%1/%2 - %3")
                       .arg(fox.voicename)
                       .arg(fox.countryname)
                       .arg(fox.language);
    name.append(QString("-%1").arg(fox.languageID));
    voicenames->addItem(name, QVariant(fox.IDVoice));
    if (uservoice == fox.IDVoice) {
      voicenames->setCurrentIndex(voicenames->count() - 1);
    }
  }
  voiceformat->clear();
  QString aa;
  aa = QString(
      "m4bf  Apple MPEG-4 AudioBooks / (.m4b) [aac,aace,aacf,aach,aacl,aacp]");
  voiceformat->addItem(aa, QVariant("m4b"));

  aa = QString("m4af  Apple MPEG-4 Audio / (.m4a,.m4r) "
               "[aac,aace,aacf,aach,aacl,aacp,alac]");
  voiceformat->addItem(aa, QVariant("m4a"));

  aa = QString("mp4f  MPEG-4 Audio / (.mp4) [aac,aace,aacf,aach,aacl,aacp]");
  voiceformat->addItem(aa, QVariant("mp4"));

  aa = QString(
      "3gp2  3GPP-2 Audio / (.3gp) [Qclp,aac,aace,aacf,aach,aacl,aacp]");
  voiceformat->addItem(aa, QVariant("3gp"));

  aa = QString(
      "AIFC  AIFC Audio / (.aifc,.aiff,.aif) [lpcm,ulaw,alaw,ima4,Qclp]");
  voiceformat->addItem(aa, QVariant("aifc"));

  aa = QString("AIFF  AIFF Audio / (.aiff,.aif) [lpcm]");
  voiceformat->addItem(aa, QVariant("aiff"));

  aa = QString("NeXT  NeXT/Sun Audio / (.snd,.au) [lpcm,ulaw]");
  voiceformat->addItem(aa, QVariant("snd"));

  aa = QString("Sd2f  Sound Designer II Audio / (.sd2) [lpcm]");
  voiceformat->addItem(aa, QVariant("sd2"));

  aa = QString("WAVE  WAVE Audio / (.wav) [lpcm,ulaw,alaw]");
  voiceformat->addItem(aa, QVariant("wav"));

  aa = QString("adts  AAC ADTS Audio / (.aac,.adts) [aac,aach,aacp]");
  voiceformat->addItem(aa, QVariant("aac"));

  aa = QString("caff  CAF Audio / (.caf) "
               "[Qclp,aac,aace,aacf,aach,aacl,aacp,alac,alaw,ilbc,ima4,lpcm,"
               "ulaw]");
  voiceformat->addItem(aa, QVariant("caf"));
}

void VoiceProcesing::setTextProcess(const QString txt) {
  proessingtxt = txt;
  const int localvoi = DOC::self(this)
                           ->value("SYSTEMLOCALEVOICE")
                           .toInt();
  int uservoice = DOC::self(this)->value("MyVoicePref").toInt();
  if (uservoice < 10) {
    uservoice = localvoi;
  }
  if (Voicecurrent.voicename.isEmpty()) {
    Voicecurrent = VoiceBlock::self(this)->TakeVoiceId(uservoice);
  }
  QString settime = QString("%1").arg(QTime(0, 0).addMSecs(1).toString());
  label_3->setText(settime);
  formatextenion = QString("m4b");
  formatcmd = QString("m4bf");
}

void VoiceProcesing::startAction() {
  //// #ifdef Q_WS_MAC

  //// #else
  timer.start();
  progreso->setValue(0);
  voicenames->setEnabled(false);
  startaction->setDisabled(true);
  cnow = start;
  const QString docsave = CACHEBUFFERDISKTMP + QString("/recf.txt");
  file_put_contents(docsave, proessingtxt);
  filetargetout = CACHEBUFFERDISKTMP + QString("/rec.%1").arg(formatextenion);
  QFile f(filetargetout);
  if (f.exists()) {
    f.remove();
  }
  QStringList cmd;
  cmd << "-v";
  cmd << Voicecurrent.voicename;
  cmd << "-f";
  cmd << docsave;
  cmd << "--file-format";
  cmd << formatcmd;
  cmd << "-o";
  cmd << filetargetout;
  cnow = chance;
  timer.restart();
  updateProgress();
  VLoader *singing = new VLoader(); //// vjob old obj
  singing->setObjectName(QString("Singformac_voice_2"));
  singing->Setting(this, "say", cmd);
  singing->start(QThread::NormalPriority);
}

void VoiceProcesing::speechEnd() {
  QString tmp;
  ToWorker *voicework = qobject_cast<ToWorker *>(sender());
  if (voicework) {
    tmp = voicework->lastAction();
    if (tmp.isEmpty()) {
      return;
    }
  }
  emit setValuePros(100);
  cnow = stop;
  const QString resultfile = filetargetout;
  QFileInfo fi(filetargetout);
  QString exteni = fi.completeSuffix();
  const QString musicdir =
      QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
  progreso->setValue(100);
  voicenames->setEnabled(true);
  startaction->setDisabled(false);
  QDateTime timer1(QDateTime::currentDateTime());
  const qint64 sec1970 = timer1.currentMSecsSinceEpoch();
  QString outmove = QString("%1/rec_%2_%3_audio.")
                        .arg(musicdir)
                        .arg(Voicecurrent.voicename)
                        .arg(sec1970);
  outmove.append(formatextenion);
  const QString userhome = QDir::homePath();
  QUrl dfile = QUrl::fromLocalFile(outmove);
  QUrl homex = QUrl::fromLocalFile(musicdir);
  QFile fr(resultfile);
  if (fr.exists()) {
    bool sucess = QFile::copy(resultfile, outmove);
    if (sucess) {
      QDesktopServices::openUrl(homex);
      QDesktopServices::openUrl(dfile);
    }
  }
  fr.remove(resultfile);
  cnow = idle;
}

void VoiceProcesing::reportTime(float tms) {
   Q_UNUSED(tms);
   cnow = stop;
}

void VoiceProcesing::setFormatdAudioOut(int index) {
  formatextenion = voiceformat->itemData(index).toString();
  const QString txte = voiceformat->itemText(index);
  formatcmd = txte.trimmed().left(4).trimmed();
}

VoiceProcesing::~VoiceProcesing() {}
