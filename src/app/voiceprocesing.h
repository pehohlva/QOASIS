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
#ifndef VOICEPROCESING_H
#define VOICEPROCESING_H

#include "editvoiceblock.h"
#include "worker.h"
#include <QDialog>
#include <QObject>
#include <QPointer>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QSettings>
#include <QTextDocument>
#include <QTextEdit>
#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>

int genkeyname(const QString name);

class VoiceProcesing : public QDialog {
  Q_OBJECT

public:
  static VoiceProcesing *self(QWidget * = 0);
  ~VoiceProcesing();
  void setTextProcess(const QString txt); /// bevor init

  enum Action_Cycle { start, chance, stop, idle };

signals:
  void setValuePros(int);

public slots:
  void updateProgress();
  void speechEnd();
  void startAction();
  void closeallcyle();
  void setVoiceatd(int voiceid);
  void setFormatdAudioOut(int index);
  void reportTime(float tms);

private:
  VoiceProcesing(QWidget * = 0);
  static QPointer<VoiceProcesing> _self;
  void setVoices();
  QGridLayout *gridLayout;
  QLabel *label_2;
  QComboBox *voicenames;
  QComboBox *voiceformat;
  QProgressBar *progressBar;
  QLabel *label;
  //// QLineEdit *lineEdit;
  QPushButton *startaction;
  QPushButton *abortation;
  QLabel *label_3;
  QProgressBar *progreso;
  int cursorp;
  Action_Cycle cnow; ///
  QElapsedTimer timer;
  QString proessingtxt;
  QString filetargetout;
  QString formatcmd;
  QString formatextenion;
  Voice Voicecurrent;
};

#endif // VOICEPROCESING_H
