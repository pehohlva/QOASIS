#ifndef CORE_MAINWINDOW_H
#define CORE_MAINWINDOW_H

#include "core_application.h"
#include <QObject>
#include <QWidget>
#include "epubview.h"



class QMainWindow;

class Core_MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit Core_MainWindow(QWidget *parent = nullptr);
  void resizeEvent(QResizeEvent *event);
  void closeEvent(QCloseEvent *event);
signals:
  void Request_To_Close();
  void Set_Tmp_File(QString);
public slots:
  void ComboEpubWake(bool e);
  void RequestPutFile(QUrl uri);
  void SetStatusText(const QString text);
  void SetBookorFile();
  void NavitoepubPage(int x);
  void updateTit(QString tit);
  void updateUrl(QUrl uri);
  void setProgress(int p);
  void prepareVoice();
  void WaitText();
  void swapVoice(int x);
  void afterWaitSpeack();

protected:
  void populate_Speacker();
  bool voice_exist( const int idspeacker );
  void active_voice_Group( const bool e);
  void updateButton();
  void Check_Visible_Engine( bool e);
  void CheckeOpenFile(const QString file);
  QMenu *fileMenu;
  QLabel *statusbar; /// to write in
  QLabel *statusbar2; /// to write in
  EpubView *emainw;
  QComboBox *epub_pages; /// list toc
  QComboBox *voice_person;
  QPushButton *bnext;
  QPushButton *bprev;
  QPushButton *svoice;  //// start e stop voice//
  int progress;
  QTextToSpeech *_qvoice;
  int VoiceLanguageBirthday;
  QLocale vloc;
  VoiceDocument vdoc;
  int languageID;
  uint ReadVoiceProgress;
};

#endif // CORE_MAINWINDOW_H
