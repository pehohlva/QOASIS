
#include <stdio.h>
#include <QTextStream>
#include <QCoreApplication>
#include <qbytearray.h>
#include <qstring.h>
#include <qchar.h>
#include <iostream>


using namespace std;

  std::ostream& operator<<(std::ostream& str, const QString& string) {
    return str << string.toStdString();
}



int main(int argc, char **argv) {

    QTextStream out(stdout);
    QString sayplease("QT is active .. ok ...  ");
    out <<  sayplease << "\n";
    out <<  QString::fromLocal8Bit(__DATE__) << "\n";
    out.flush();

       std::cout << "-------------------------------------------------------\n";
       
       std::cout << "---- Hi This is a Hook install on app to build other .--\n";
       
       std::cout << "-------------------------------------------------------\n";


}