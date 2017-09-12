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
#include <QMainWindow>
#include <QCoreApplication>
#include <QApplication>
#include <QtGui>
#include <QFontDatabase>
#include "oasimain.h"
#include "oasi_application.h"
#include "doc_session.h"

#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QByteArray>
#include <QString>
#include <QProcess>
#include <QElapsedTimer>

#include "worker.h"




/*
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream qout(stdout);
    QStringList lc;
    QStringList note;
    lc << "-v";
    lc << "Anna";
    lc << "-f";
    lc << "text.txt";
    lc << "--progress";
    ToWorker wt;
    wt.run("say",lc);
    return a.exec();
}
 */


/////#include "allconfig.h"#include "mainwindow.h"*#include "core_application.h" #ifndef QT_NO_PRINTER QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
 ///// * Q_OS_MAC  Q_OS_WIN  Q_OS_LINUX  Q_OS_MAC*/

int main(int argc, char *argv[]) {
    Oasi a(argc, argv);
    return a.exec();
}
