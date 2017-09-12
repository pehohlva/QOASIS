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
#include "editvoiceblock.h"
#include <QProgressDialog>
#include "core_htmldriver.h"
#include "voiceprocesing.h"
#include <QObject>



static const int speedchaine = 1500;

VoiceBlock::VoiceBlock(QObject *parent) : QObject(parent) {
    smisound = shutdown;
    vcursor = notrun;
    stateB =0;
}
/*  DocumentCursor vcursor; /// cursor read for sound. { notrun, waitrespone, parseblock, errorparse }
  SoundStatus smisound; /// stautus of voice. { shutdown , waitsound, sendsound  } */
void VoiceBlock::killVoice() {

    if (vcursor != notrun) {
       stopfast();
    }
    smisound = shutdown;
}
/*  DocumentCursor vcursor; /// cursor read for sound. { notrun, waitrespone, parseblock, errorparse }
  SoundStatus smisound; /// stautus of voice. { shutdown , waitsound, sendsound  } */
void VoiceBlock::say(const QString text , int e ) {
    if (text.size() == 0 ) {
        SESSDEBUG() << __FUNCTION__ << " - NULLTEXT I INCOMMING GO ASSERT!";
        return;
    }

    if (smisound !=shutdown) {
        SESSDEBUG() << __FUNCTION__ << " - sound is not shutdown GO ASSERT!";
        return;
    }


   SESSDEBUG() << __FUNCTION__ << " - job go voice name " << currentVoice.voicename;
   SESSDEBUG() << __FUNCTION__ << " - job go voice id" << currentVoice.IDVoice;
   SESSDEBUG() << __FUNCTION__ << " - job txt" << text;
  smisound = sendsound;
  if (currentVoice.IDVoice > 0 ) {
    QStringList cmd;
    cmd << "-v";
    cmd << currentVoice.voicename;
    cmd << text;
    smisound = waitsound;
#ifdef Q_WS_MAC
    singing = new VLoader(); //// vjob old obj
    singing->setObjectName(QString("Singformac_voice_"));
    singing->Setting(this,"say",cmd);
    singing->start(QThread::LowPriority);
#else
    smisound = shutdown;
    stopfast();
    vcursor = notrun;
#endif
  } else {
    if ( vcursor ==  waitrespone && e !=0 ) {
      stopfast();
    } else {
    //// SESSDEBUG() << __FUNCTION__ << " - STOP XXXXXXXX -" << currentVoice.debug();
    emit setVoicePriorMessage(QString("Unable to write inside Cache dir... disk is full?"));
    }
  }
}


void VoiceBlock::sayDemoVoice() {
  emit switschStatus(false);
  const int uservoice = DOC::self(this)->value("MyVoicePref").toInt();
  Voice person = TakeVoiceId(uservoice);
  if (!person.voicename.isEmpty() || !person.demotext.isEmpty() ) {
    currentVoice = person;
    QString text = person.demotext.replace(QString("#"), QString());
    say(text,0);
  } else {
    SESSDEBUG() << __FUNCTION__ << " - Assert null person!!!!!!XXXXXXXXXX";
  }
}

Voice VoiceBlock::TakeVoiceId(const int pref) {
  ////  -f file.txt -v voicename -i, --interactive    ... say -f read.dat -v
  ///Federica
  QList<Voice>::const_iterator x;
  for (x = voices.constBegin(); x != voices.constEnd(); ++x) {
    Voice fox = *x;
    if (pref == fox.IDVoice) {
      return fox;
    }
  }
  Voice nullio;
  //// SESSDEBUG() << __FUNCTION__ << " grrrr not found id go assert!";
  return nullio;
}

void VoiceBlock::FillvaiableVoice() {
  voices.clear();
  QStringList cmd; //// mac comand ( say -v "?" )
  cmd << QString("-v");
  cmd << QString("?");
  const QString litflat = say_comand_sdout(cmd);
  if (litflat.size() > 0) {
    QStringList linebyline = litflat.split(QString("\n"));
    for (int x = 0; x < linebyline.size(); x++) {
      QString liner = linebyline.at(x);
      QString name = liner.left(20).trimmed();
      int su = liner.indexOf(QString("#"));
      QString country = liner.mid(20, 12).trimmed();
      if (country.contains(QString("#")) != -1) {
        country = liner.mid(20, 6).trimmed();
      }
      QLocale st(country);
      Voice one;
      one.voicename = name;
      one.language = st.nativeLanguageName();
      one.languageID = (int)st.language();
      one.countryname = st.countryToString(st.country());
      QString comment = liner.mid(su - 1, liner.size() - su).trimmed();
      int xid = genkeyname(name + one.language + one.countryname);
      one.IDVoice = xid;
      one.demotext = comment;
      if (!name.isEmpty()) {
        voices.append(one);
        ///// SESSDEBUG() << __FUNCTION__ << " refill " << one.debug();
      }
    }
  }
}

QString VoiceBlock::say_comand_sdout(QStringList comandlist) {
 #ifdef Q_WS_MAC
  QString lstr;
  QString cmd = QString("say");
  QProcess *process = new QProcess(this);
  process->setReadChannelMode(QProcess::MergedChannels);
  process->start(cmd, comandlist, QIODevice::ReadOnly);
  if (!process->waitForFinished()) {
    lstr = QString();
  } else {
    lstr = QString(process->readAll().constData());
  }
  return lstr;
#else
     return QString();
#endif
}

/*
take voice cmd:
say -v "?"
say -o out22.aiff -v Federica "Buongiorno a tutti come state, avete iniziato
bene la giornata?"


*/



/*
void VoiceBlock::say() {
  if (now == speeach) {
    SESSDEBUG() << __FUNCTION__ << " - on speeach- ";
    QTimer::singleShot(speedchaine, this, SLOT(next()));
  } else {
    SESSDEBUG() << __FUNCTION__ << " - on pause or stop - ";
  }
}
 */

/*  DocumentCursor vcursor; /// cursor read for sound. { notrun, waitrespone, parseblock, errorparse }
  SoundStatus smisound; /// stautus of voice. { shutdown , waitsound, sendsound  } */
void VoiceBlock::stopfast() {
  if (vcursor != notrun) {
    vcursor = notrun;
    smisound = shutdown;
    summtotblock = edit->document()->blockCount();
    for (int x = 0; x < summtotblock; x++) {
      formatBlok(x, false); //// clean my format if have..
    }
     sendursorTo(0);
     vcursor = notrun;
     stateB = 0;
     emit switschStatus(true);
     emit endreadPage();
     emit setVoicePriorMessage(QString("Stop/End Read Document.."));
     if (singing) {
         singing->terminate();
         singing->deleteLater();
     }
  }

  smisound = shutdown;
  return;
  ////  typedef QList<QObject*> QObjectList;
  //// SESSDEBUG() << __FUNCTION__ << " - find item to kill ";
  QObjectList mx = this->children();
  QList<QObject*>::const_iterator x;
  for (x = mx.constBegin(); x != mx.constEnd(); ++x) {
    QObject *fox = *x;
    //// SESSDEBUG() << fox->objectName() << " <->  find one or moore...";
  }


  ////
}

void VoiceBlock::reportTime( float qtime ) {
     QString tmp = QString("hope");
    ToWorker *voicework = qobject_cast<ToWorker *>(sender());
    if (voicework) {
        tmp = QString("suncastok...... ");
    }
    SESSDEBUG() << tmp << " Voice report state" << qtime;
}

/*  DocumentCursor vcursor; /// cursor read for sound. { notrun, waitrespone, parseblock, errorparse }
  SoundStatus smisound; /// stautus of voice. { shutdown , waitsound, sendsound  } */
void VoiceBlock::speechEnd() {
#ifdef Q_WS_MAC
    QString tmp;
    ToWorker *voicework = qobject_cast<ToWorker *>(sender());
    if (voicework) {
        tmp = voicework->lastAction();
        if (tmp.isEmpty()) {
          return;
        }
        comanddebug.insert(tmp);
    } else {
        return;
    }
    SESSDEBUG() << __FUNCTION__ << "Voice ready-from   " << tmp  << ":state" << stateB;
    smisound = shutdown;
     if ( stateB > 1000 && vcursor == waitrespone ) {
         vcursor = parseblock;
         jump_and_Speeach(stateB);
     } else {
        emit switschStatus(true);
     }

#else
//// use qspeech module normal
emit switschStatus(true); /// button enable
#endif
}

/*  DocumentCursor vcursor; /// cursor read for sound. { notrun, waitrespone, parseblock, errorparse }
  SoundStatus smisound; /// stautus of voice. { shutdown , waitsound, sendsound  } */
void VoiceBlock::jump_and_Speeach(int blocknr) {
   SESSDEBUG() << __FUNCTION__ << " - pos -> " << blocknr;
  if (vcursor != parseblock) {
    return;
  }
  vcursor = parseblock;
  const int textbloknummer = blocknr - 1000; //// work on null no..
  QTextBlock dd = edit->document()->findBlockByNumber(textbloknummer);
  stateB = blocknr;
  stateB++;
  QString tmp;
  if (!dd.isValid()) {
      vcursor = errorparse;
      tmp = QString("error");
  } else {
     tmp = QString("valid");
  }

  SESSDEBUG() << "Block parse on:" << textbloknummer << " - StateB" << stateB << " blockValid:" << tmp;

  if (!dd.isValid()) {
      stopfast(); //// end document..
      return;
  }


  if (dd.isValid()) {
    const QString txt = dd.text();
    QString dummytext = txt.trimmed();
            if (dummytext.size() > 0) {
              formatBlok(textbloknummer, true);
            } else {
              formatBlok(textbloknummer, false);
            }
    formatBlok(textbloknummer - 1, false);
    //// send cursor next block...to view text ok...
    sendursorTo(textbloknummer + 2);
            if (dummytext.isEmpty()) {
              SESSDEBUG() << __FUNCTION__ << ": go next";
              vcursor = parseblock;
              jump_and_Speeach(stateB);
              return;
            } else {
              SESSDEBUG() << __FUNCTION__ << ": go say";
              vcursor = waitrespone;
              say(txt,stateB);
              return;
            }
  }
}

/*  DocumentCursor vcursor; /// cursor read for sound. { notrun, waitrespone, parseblock, errorparse }
  SoundStatus smisound; /// stautus of voice. { shutdown , waitsound, sendsound  } */
void VoiceBlock::init_on(QTextEdit *e) {
  if (vcursor != notrun) {
    return;
  }
  const int uservoice = DOC::self(this)->value("MyVoicePref").toInt();
  Voice person = TakeVoiceId(uservoice);
  if (!person.voicename.isEmpty() || !person.demotext.isEmpty() ) {
    currentVoice = person;
  }
  vcursor = parseblock;
  edit = e;
  QString fillt = e->document()->toPlainText();
  if (fillt.size() < 10) {
    emit endreadPage();
    emit setVoicePriorMessage(QString("No Text found to Speeck or no Documents, maybe too small."));
    vcursor = notrun;
    return;
  }
  if (currentVoice.voicename.isEmpty()) {
      vcursor = notrun;
      emit endreadPage();
      emit setVoicePriorMessage(QString("Error Voice Name not exist, we need a Name from list."));
      return;
  }
  //// enum DocumentCursor { notrun, waitrespone, parseblock, errorparse };
  stateB = 1000; /// to init on block 0;

  const int gg = DOC::self(this)->value(QString("DoumentCurrentLanguage")).toInt();
  if (currentVoice.languageID != gg) {
     emit setVoicePriorMessage(QString("Voice Name %1 have other language as document.").arg(currentVoice.voicename));
  }
  emit switschStatus(false);
  summtotblock = edit->document()->blockCount();
  vcursor = parseblock;
  jump_and_Speeach(stateB); /// to init on block 0;
}

void VoiceBlock::formatBlok(const int blokid, bool highlight) {

  QTextBlock block = edit->document()->findBlockByNumber(blokid);
  if (!block.isValid()) {
    return;
  }
  QTextBlockFormat sfo = block.blockFormat();
  QTextCursor cu(block);
  QColor baks(110, 218, 230, 50);
  if (highlight) {
    sfo.setBackground(QBrush(baks, Qt::SolidPattern));
    cu.setBlockFormat(sfo);
  } else {
    QBrush tt(Qt::transparent, Qt::SolidPattern);
    QBrush xx = sfo.brushProperty(QTextBlockFormat::BackgroundBrush);
    if (xx != tt) {
      sfo.setBackground(tt);
      cu.setBlockFormat(sfo);
    }
  }
}

void VoiceBlock::sendursorTo(const int blocknr) {
  QTextBlock dd = edit->document()->findBlockByNumber(blocknr);
  if (dd.isValid()) {
    QTextCursor c(dd);
    const int xxdd = c.positionInBlock();
    c.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    edit->setTextCursor(c);
  }
}
