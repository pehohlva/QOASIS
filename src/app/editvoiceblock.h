#ifndef EDITVOICEBLOCK_H
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
#define EDITVOICEBLOCK_H

#include "doc_session.h"
#include "oasimain.h"
#include <QObject>
#include "worker.h"


struct Voice {
  QString debug() {
    QString x = QString("|voicename:%1").arg(voicename);
     x += QString("|IDVoice:%1").arg(IDVoice);
    x += QString("|countryname:%1").arg(countryname);
    x += QString("|language:%1").arg(language);
    x += QString("|demotext:%1").arg(demotext.size());
    x += QString("|languageID:%1").arg(languageID);
    return x;
  }
  QString voicename;
  QString countryname;
  QString language;
  QString demotext;
  int languageID;
  int IDVoice;
};

class ToWorker;
class VLoader;

class VoiceBlock : public QObject {
  Q_OBJECT
public:
  static VoiceBlock *self(QObject *parent = nullptr);
  enum DocumentCursor { notrun, waitrespone, parseblock, errorparse };
  enum SoundStatus { shutdown , waitsound, sendsound  };
  enum Action_Cycle { start , chance, stop , idle  };
  void init_on(QTextEdit *e);
  void formatBlok(const int blokid, bool highlight);
  void FillvaiableVoice();
  QList<Voice> avaiableVoices() { return voices; }
  Voice TakeVoiceId(const int pref);

signals:
  void servicerunvoice(int);
  void endreadPage();
  void switschStatus(bool);
  void setVoicePriorMessage(QString);
  ///// void setDumpMessage(QString);
public slots:
  void killVoice();
  void say(const QString text , int e );
  void sayDemoVoice();
  void stopfast();
  void jump_and_Speeach(int blocknr);
  void reportTime( float qtime );
  void speechEnd();

private:
  VoiceBlock(QObject *parent = nullptr);
  static QPointer<VoiceBlock> _self;
  QSet<QString> comanddebug;
  Voice currentVoice;
  Voice systemVoice;
  QString say_comand_sdout(QStringList comandlist);
  QList<Voice> voices;
  void sendursorTo(const int blocknr);
  QTextEdit *edit;
  VLoader *singing;
  int summtotblock;
  DocumentCursor vcursor; /// cursor read for sound. { notrun, waitrespone, parseblock, errorparse }
  SoundStatus smisound; /// stautus of voice. { shutdown , waitsound, sendsound  }
  int stateB;
};

#endif // EDITVOICEBLOCK_H
