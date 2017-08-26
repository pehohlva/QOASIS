#include <QCoreApplication>

#include "sys/kernel_document.h"
#include "sys/docformat/epub/econverter.h"


static void usagethisapp(const char *name) {
    printf("Usage: %s (Options)  \n", name);
    printf("Tell the file to index Options ->  file.xx \n");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList in = a.arguments();
    Epub::Converter *w = new Epub::Converter();
    qDebug()  << in << " arri";

     if (in.size() == 1) {
     usagethisapp(argv[0]);
     return 0;
     }

    if (in.size() !=2 || in.size() !=3) {
                 QString html;
                int tablesum;
        QTextDocument *dd = w->convert(in.at(1),html,tablesum);
          qDebug()  << dd->isEmpty() << " -> isfile";
    } else {
      usagethisapp(argv[0]);
    }
    return 1; /// a.exec();
}
