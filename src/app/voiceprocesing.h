#ifndef VOICEPROCESING_H
#define VOICEPROCESING_H

#include <QDialog>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QTextEdit>
#include <QtWidgets/QProgressBar>
#include <QTextEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QPushButton>
#include <QTextEdit>

#include <QProgressBar>
#include <QSettings>
#include <QTextDocument>
#include <QWidget>
#include <QProcess>
#include <QObject>
#include <QDialog>
#include "worker.h"

int genkeyname(const QString name);

class VoiceProcesing : public QDialog
{
    Q_OBJECT

public:
    explicit VoiceProcesing(QWidget *parent = 0);
    ~VoiceProcesing();

private:
private:
    QTextEdit *textEdit;
    QPushButton *closeButton;
    QProgressBar *progreso;

};

#endif // VOICEPROCESING_H
