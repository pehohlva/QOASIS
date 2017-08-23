#include <QCoreApplication>

#include "sys/kernel_document.h"


static void usagethisapp(const char *name) {
    printf("Usage: %s (Options)  \n", name);
    printf("Tell the file to index Options ->  file.xx \n");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList in = a.arguments();
    Kernel_Document *w = new Kernel_Document();
    qDebug()  << in << " arri";

     if (in.size() == 1) {
     usagethisapp(argv[0]);
     return 0;
     }

    if (in.size() !=2 || in.size() !=3) {
         bool isfile = w->Load(in.at(1));
          qDebug()  << isfile << " -> isfile";
    } else {
      usagethisapp(argv[0]);
    }


    w->deleteLater();
    return 1; /// a.exec();
}
