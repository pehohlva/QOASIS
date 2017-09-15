
#include <stdio.h>
#include <iostream>

#include <QString>
#include <qtrlocale.h>
#include <QTextStream>


int main(int argc, char **argv) {
	
	
     QTrlocale *lang = new QTrlocale();
     QString tmp_text("Io parlo un po di questa lingua ma per favore non dirlo a nesun altro, ti rigrazio della tolleranza.");
     QLocale dis =  lang->getQlocaleFromText(tmp_text);
     QTextStream out(stdout);
       out <<  tmp_text << "\n";
	   out <<  "Language detect is:" << dis.language() <<  "\n";
       out <<  QString::fromLocal8Bit(__DATE__) << "\n";
       out.flush();
	   

       std::cout << "-------------------------------------------------------\n";
       
       std::cout << "---- Hi This is a Hook install on app to build other .--\n";
       
       std::cout << "-------------------------------------------------------\n";

}
