#include "core_mainwindow.h"

#include <QAction>
#include <QComboBox>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QStatusBar>

#include "epubview.h"

Core_MainWindow::Core_MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setObjectName(QString("maincreen"));
  QMenuBar *menubarre = new QMenuBar(this);
  VoiceDocument newone;
  newone.local = false;
  newone.lang = QString();
  vdoc = newone;
  QStatusBar *sta = new QStatusBar(this);
  ///// sta->setStyleSheet("background-color: #baeee9;");
  statusbar = new QLabel("Application Loading...");
  statusbar->setFixedWidth(255);
  statusbar2 = new QLabel("");
  statusbar2->setFixedWidth(255);

  svoice = new QPushButton(this);
  svoice->setFlat(true);
  svoice->setStyleSheet("font-family: \"Icons South St\"");
  svoice->setText(QString("p"));
  svoice->setDisabled(true);
  ///// svoice->setToolTip(QString("Speack"));

  bprev = new QPushButton(this);
  bprev->setFlat(true);
  bprev->setStyleSheet("font-family: \"Icons South St\"");
  bprev->setText(QString("T")); /// TS
  ///// bprev->setToolTip(QString("Back"));
  bprev->show();
  bprev->setDisabled(true);
  bnext = new QPushButton(this);
  bnext->setFlat(true);
  bnext->setStyleSheet("font-family: \"Icons South St\"");
  bnext->setText(QString("S")); /// TS
  //// bnext->setToolTip(QString("Forward"));
  bnext->show();
  bnext->setDisabled(true);
  epub_pages = new QComboBox(this);
  epub_pages->setFixedWidth(180);
  epub_pages->hide();
  voice_person = new QComboBox(this);
  voice_person->setFixedWidth(180);
  voice_person->hide();
  sta->addWidget(statusbar); /// append progressbar from load
  sta->addWidget(epub_pages);
  sta->addWidget(bprev);
  sta->addWidget(bnext);
  sta->addWidget(statusbar2);
  sta->addWidget(svoice);
  sta->addWidget(voice_person);

  this->setMenuBar(menubarre);
  this->setStatusBar(sta);

  progress = 0;

  fileMenu = menubarre->addMenu(tr("&File"));
  QAction *act_file_open = new QAction(tr("Open Fake File"), this);
  act_file_open->setShortcut(QKeySequence(QKeySequence::Open));
  connect(act_file_open, SIGNAL(triggered()), this, SLOT(SetBookorFile()));
  ///// connect(act_file_open, SIGNAL(triggered()), this,
  ///SLOT(SetBookorFile()));
  fileMenu->addAction(act_file_open);
  /* ---------------------------------------- */
  emainw = new EpubView(this);
  setCentralWidget(emainw);
  emainw->hide(); /// load all before...
  /* ---------------------------------------- */
  connect(emainw, SIGNAL(PaintMenuEpub(bool)), this, SLOT(ComboEpubWake(bool)));
  connect(emainw, SIGNAL(titleChanged(QString)), this,SLOT(updateTit(QString)));
  connect(emainw, SIGNAL(urlChanged(QUrl)), this, SLOT(updateUrl(QUrl)));
  connect(bnext, SIGNAL(clicked()), emainw, SLOT(forward()));
  connect(bprev, SIGNAL(clicked()), emainw, SLOT(back()));
  connect(svoice, SIGNAL(clicked()), this, SLOT(afterWaitSpeack()));
  connect(emainw, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
  connect(emainw, SIGNAL(VdocReady()), SLOT(WaitText()));
  connect(epub_pages, SIGNAL(currentIndexChanged(int)), this,SLOT(NavitoepubPage(int)));


  ///// connect(emainw->page(), SIGNAL(urlChanged(QUrl)), this,
  ///SLOT(updateUrl(QString)));
  SetStatusText(QString("End .. Loading... "));
  setWindowTitle(_FIRSTWINDOWTITLESHOW_);
  _qvoice = new QTextToSpeech("osx",this);
  vloc = QLocale::system();
  languageID = (int)vloc.language();
  _qvoice->setLocale(vloc);
  active_voice_Group(false);
  ReadVoiceProgress =0;
  this->show();
}

void Core_MainWindow::updateTit(QString tit) {
  CCDEBUG() << "signal in here->: " << __FUNCTION__ << "-" << tit;
  if (!tit.isEmpty()) {
    setWindowTitle(QString("%1 - %2").arg(_FIRSTWINDOWTITLESHOW_).arg(tit));
  } else {
    setWindowTitle(QString("%1 - No Document Name.").arg(_FIRSTWINDOWTITLESHOW_));
  }
}

void Core_MainWindow::updateUrl(QUrl uri) {
  CCDEBUG() << "signal in here->: " << __FUNCTION__ << "-" << uri;
  updateButton();
}

void Core_MainWindow::RequestPutFile(QUrl uri) {
  CCDEBUG() << "signal in here->: " << __FUNCTION__ << "-" << uri << ":"
            << __LINE__;
  active_voice_Group(false);
  QFileInfo xfi(uri.toLocalFile());
  if (xfi.exists()) {
    this->CheckeOpenFile(xfi.absoluteFilePath());
  } else {
    Check_Visible_Engine(true);
    emainw->JumpEpub(uri); /// www
  }
}

void Core_MainWindow::SetBookorFile() {

  QSettings settings(_ORGANIZATION_NAME_, _PROGRAM_NAME_);
  QString dirlast = settings.value("books/lastdir_open").toString();
  QVariantList lastfiles = settings.value("books/files/db").toList();
  if (dirlast.size() == 0) {
    dirlast = QDir::homePath();
    ///// QFileDialog::DontUseNativeDialog
  }
  QString file = QFileDialog::getOpenFileName(
      Q_NULLPTR, QString("Choose File..."), dirlast, "*", Q_NULLPTR,
      QFileDialog::HideNameFilterDetails);

  if (file.isEmpty()) {
    return;
  } else {
    active_voice_Group(false);
    QFileInfo iox(file);
    lastfiles.append(QVariant(iox.absoluteFilePath()));
    settings.setValue("books/files/db", lastfiles);
    settings.setValue("books/lastdir_open", QVariant(iox.absolutePath()));
    this->CheckeOpenFile(iox.absoluteFilePath());
  }
}

void Core_MainWindow::CheckeOpenFile(const QString file) {
    active_voice_Group(false);
  QString text = QString("Open: %1").arg(file);
  QFileInfo fix(file);
  QUrl fixifile = QUrl::fromLocalFile(file);
  CCDEBUG() << " fix.completeSuffix() " << fix.completeSuffix();
  if (fix.completeSuffix() == QString("epub")) {
    emainw->OpenEpub(fixifile);
    statusbar->setText(text);
    return;
  } else {

    if (fix.completeSuffix() == QString("xhtml") ||
        fix.completeSuffix() == QString("html") ||
        fix.completeSuffix() == QString("xml")) {
      epub_pages->clear();
      epub_pages->hide();
      emainw->JumpEpub(fixifile);
      return;
    }

    QByteArray chunk;
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    uint unixtime = currentDateTime.toTime_t();
    QString newfile = _TESTBOOKS_ + QString("%1.html").arg(unixtime);
    QUrl fixifileA = QUrl::fromLocalFile(newfile);
    // can write in _TESTBOOKS_
    Kernel_Document *doc = new Kernel_Document();
    if (doc->Load(file)) {
      chunk = doc->to_Html();
      if (chunk.size() > 1) {
        if (file_put_contents(newfile, QString(chunk.constData()))) {
          epub_pages->clear();
          epub_pages->hide();
          emainw->JumpEpub(fixifileA);
          return;
        }
      }
    }
  }
}

/*    QByteArray to_html_compressd();
    QByteArray to_html_utf8();  */

void Core_MainWindow::closeEvent(QCloseEvent *event) {
  active_voice_Group(false);
  emit Request_To_Close();
  event->ignore();
}

void Core_MainWindow::SetStatusText(const QString text) {
  statusbar->setText(text);
}

void Core_MainWindow::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);
  ///// CCDEBUG() << "Run: " << __FUNCTION__ << "-" << __FILE__ << ":" <<
  ///__LINE__;
  QRect screens = this->geometry();
  QSettings settings(_ORGANIZATION_NAME_, _PROGRAM_NAME_);
  settings.setValue("editor/width", screens.width());
  settings.setValue("editor/height", screens.height());
  QMainWindow::resizeEvent(event);
}

void Core_MainWindow::NavitoepubPage(int x) {
  active_voice_Group(false);
  Check_Visible_Engine(true);
  QVariant urijump = epub_pages->itemData(x);
  QString gofile = urijump.toString();
  if (!gofile.isEmpty()) {
    QUrl openuri;
    QFileInfo xfi(gofile);
    if (xfi.exists()) {
      openuri = QUrl::fromLocalFile(gofile);
    } else {
      openuri = QUrl(gofile);
    }
    emainw->JumpEpub(openuri);
    SetStatusText(QString("Render Page: %1").arg(epub_pages->currentText()));
  }
}

void Core_MainWindow::Check_Visible_Engine(bool e) {
  Q_UNUSED(e); /// if must play other widged...
  if (emainw->isHidden()) {
    emainw->show();
  }
}

void Core_MainWindow::ComboEpubWake(bool e) {
  if (e) {
    epub_pages->clear();
    this->Check_Visible_Engine(true);
    QList<EpubToc> tocep = emainw->RenderMenu();
    if (tocep.size() > 0) {
      for (int x = 0; x < tocep.size(); x++) {
        EpubToc fox = tocep.at(x);
        ///// CCDEBUG() << "combo in " << fox.title << ":" << fox.jumpurl;
        QFileInfo foxa(fox.jumpurl);
        if (foxa.exists()) {
          int homeorder = 1 + fox.orderid;
          epub_pages->addItem(
              QString("%1) Local Book: - %2").arg(homeorder).arg(fox.title),
              QVariant(foxa.absoluteFilePath()));
        }
      }
    }
    epub_pages->addItem(QString("Online: - Google.com"),
                        QVariant(QString("https://www.google.ch/")));
    epub_pages->show();
  } else {
     active_voice_Group(false);
    epub_pages->hide();
  }
}

void Core_MainWindow::setProgress(int p) {
  progress = p;
  if (progress <= 0 || progress >= 99) {
    progress = 101;
    statusbar2->setText(QString());
  } else {
    active_voice_Group(false);
    statusbar2->setText(QString("Loading.... (%1%)").arg(progress));
  }
}

void Core_MainWindow::updateButton() {
  QWebEngineHistory *history = emainw->page()->history();
  bnext->setDisabled(!history->canGoForward());
  bprev->setDisabled(!history->canGoBack());
}


void Core_MainWindow::WaitText() {
    if (progress == 101 ) {
      QTimer::singleShot(250, this, SLOT(prepareVoice()));
    }
}


void Core_MainWindow::populate_Speacker()
{

    if (vdoc.lang.isEmpty()) {
     qDebug() << "snd return:" << __FUNCTION__;
     return;
    }
    if (languageID == 0) {
     return;
    }

    QSettings settings(_ORGANIZATION_NAME_, _PROGRAM_NAME_);
    const int myspeaker = settings.value("books/speaker_pref").toInt();
    if (myspeaker < 1) {
        //// first time
        qDebug() << " first runn QSettings myspeaker->"<< myspeaker  << __FUNCTION__;
    }
     voice_person->clear();
     QVector<QVoice> m_voices = _qvoice->availableVoices();
               foreach (const QVoice &voice, m_voices) {
                          const int idbirth =  voicebirthay(voice,languageID);
                          QString wtext =QString::number(idbirth) + QString("Voc:%1 - %2 - %3").arg(voice.name())
                               .arg(QVoice::genderName(voice.gender()))
                               .arg(QVoice::ageName(voice.age()));
                          voice_person->addItem(wtext);
                   if (idbirth == myspeaker ) {
                       voice_person->setCurrentIndex(voice_person->count() - 1);
                   }
               }
}
 void Core_MainWindow::afterWaitSpeack() {

     if (languageID == 0) {
      return;
     }
     if (vdoc.lang.isEmpty()) {
       qDebug() << " snd return:" << __FUNCTION__;
      return;
     }
     qDebug() << "languageID"  << languageID << "  byspeack:" << __FUNCTION__;
     QLocale rloc = QLocale::system();
     qDebug() << "languageID sistem->"  << (int)rloc.language() << "  byspeack:" << __FUNCTION__;
     if (ReadVoiceProgress > 0) {
       _qvoice->stop();
       ///// _qvoice->objectName()
       ReadVoiceProgress =0;
     } else {
         _qvoice->say(vdoc.text);
         _qvoice->startTimer(1000);
        ReadVoiceProgress = 100;
     }
 }

void Core_MainWindow::swapVoice(int x) {

   QSettings settings(_ORGANIZATION_NAME_, _PROGRAM_NAME_);
   const int myspeaker = settings.value("books/speaker_pref").toInt();
   if (myspeaker < 1) {
       //// first time
   }
     //// vdoc = emainw->CurrentDoc();
     if (vdoc.lang.isEmpty()) {
         return;
     }
     if ( voice_person->isHidden() ) {
        return;
     }
      if (languageID == 0) {
       return;
      }
     QVector<QVoice> m_voices = _qvoice->availableVoices();
     const int totvoiceNow= m_voices.size();
     if (x > totvoiceNow) {
         qWarning("No voice in current language!!");
         return;
     }
     QVoice OldVoice = _qvoice->voice();  //// or default voice new lang
     const int oldvoieIDX = voicebirthay(OldVoice,languageID);
      _qvoice->setVoice(m_voices.at(x));  /////  save pref here!!!!
      QVoice _currentVoice = _qvoice->voice();
      VoiceLanguageBirthday = voicebirthay(_currentVoice,languageID);
      settings.setValue("books/speaker_pref",VoiceLanguageBirthday);
      if (VoiceLanguageBirthday != oldvoieIDX) {
       qDebug() << VoiceLanguageBirthday <<  " chance ok name:" << _currentVoice.name() << " voice -" << languageID;
      } else {
       qDebug() << VoiceLanguageBirthday <<  " no chance!!!! XXXXXXXX :" << oldvoieIDX;
      }
      const QString LANGUAGENAME=QLocale(vdoc.lang).nativeLanguageName();
      const QString nameV = _qvoice->voice().name();
      QString casem = LANGUAGENAME + QString("/") + nameV;
      statusbar2->setText(QString("Text %2 / Read size:  %1").arg(BytesRead(vdoc.text.size())).arg(casem));
     if ( vdoc.local ) {
      active_voice_Group(true);
     statusbar2->setText(QString("Text %2 / Read size:  %1").arg(BytesRead(vdoc.text.size())).arg(casem));
     } else {
         active_voice_Group(false);
         statusbar2->setText(QString("Online: not need voice."));
     }

     qDebug() << VoiceLanguageBirthday << "/VoiceLanguageBirthday - " << vdoc.debug() <<  __FUNCTION__;
}



void Core_MainWindow::prepareVoice() {

    if (progress !=101 ) {
        return;
    }
    vdoc = emainw->CurrentDoc();
    if (vdoc.lang.isEmpty()) {
        return;
    }
    progress = 0;


    ///// QLocale now_locale = QLocale(vdoc.lang);
    ////// languageID = (int)now_locale.language();

    ///// CCDEBUG() << "old id: "  <<  languageID << "signal in here-> init.. : " << __FUNCTION__;
    QLocale now_locale = QLocale(vdoc.lang);
    active_voice_Group(true);
    _qvoice->setLocale(now_locale); //// need to build speacker person list!!!!
    bool realwap = false;
    if (!voice_exist(VoiceLanguageBirthday)) { //// the selected type from user before
        //// real chance of language!!!
        realwap =true;
        qDebug() << " swap language old speacker is out!!!!" << __FUNCTION__;
        QVector<QVoice> m_voices = _qvoice->availableVoices();
        if (m_voices.size() == 0) {
            active_voice_Group(false);
            VoiceLanguageBirthday = 0;
            return; /// not supported language!
        }
    } else {
        //// not swap default voice to loast
    }
    languageID != (int)now_locale.language();
    populate_Speacker(); /// select a new one... or old stay!
    if (realwap) {
     QVector<QVoice> m_voices = _qvoice->availableVoices();
    swapVoice(m_voices.size() - 1); /// default here one new default
    return;
    }
    VoiceLanguageBirthday = voicebirthay(_qvoice->voice(),languageID);  //// default iis set..
    const QString LANGUAGENAME=now_locale.nativeLanguageName();
    const QString nameV = _qvoice->voice().name();
    QString casem = LANGUAGENAME + QString("/") + nameV;
    if ( vdoc.local ) {
     active_voice_Group(true);
    statusbar2->setText(QString("Text %2 / Read size:  %1").arg(BytesRead(vdoc.text.size())).arg(casem));
    } else {
        active_voice_Group(false);
        statusbar2->setText(QString("Online: not need voice."));
    }

    qDebug() << VoiceLanguageBirthday << "/VoiceLanguageBirthday - " << vdoc.debug() <<   __FUNCTION__;
}




bool Core_MainWindow::voice_exist( const int idspeacker ) {
    bool _exist =false;
    if (_qvoice->availableVoices().size() > 0) {
    QVector<QVoice> m_voices = _qvoice->availableVoices();
              foreach (const QVoice &voice, m_voices) {
                         const int idbirth =  voicebirthay(voice,languageID);
                         if (idbirth == idspeacker) {
                            _exist =true;
                         }
              }
    }
    return _exist;
}

void Core_MainWindow::active_voice_Group( const bool e) {
    if (!e) {
        qDebug() << e << "/active_voice_Group";
        languageID = 0;
        svoice->setDisabled(true);
        voice_person->clear();
        voice_person->hide();
        /////// disconnect(svoice, SIGNAL(clicked()), this,SLOT(init_Speack()));
        disconnect(voice_person, SIGNAL(currentIndexChanged(int)), this,SLOT(swapVoice(int)));
    } else {
        if (!vdoc.lang.isEmpty()) {
            QLocale now_locale = QLocale(vdoc.lang);
            languageID = (int)now_locale.language();
        }
         qDebug() << e << "/active_voice_Group cccc ";
        svoice->setDisabled(false);
        ////// connect(svoice, SIGNAL(clicked()), this,SLOT(init_Speack()));
        connect(voice_person, SIGNAL(currentIndexChanged(int)), this,SLOT(swapVoice(int)));
        voice_person->show();
    }
}
