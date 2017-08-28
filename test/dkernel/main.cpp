#include "core_application.h"
#include <QCoreApplication>



/*
static void usagethisapp(const char *name) {
    printf("Usage: %s (Options)  \n", name);
    printf("Tell the file to index Options ->  file.xx \n");
}
*/

int main(int argc, char *argv[]) {
  Core_Application api(argc, argv);
  /////QStringList in = a.arguments();
  /*
  qDebug()  << in << " arri";

   if (in.size() == 1) {
   usagethisapp(argv[0]);
   return 0;
   }

  if (in.size() !=2 || in.size() !=3) {

  } else {
    usagethisapp(argv[0]);
  }
  return 1; /// */
  api.exec();
}

/*
 * Epub::Converter *w = new Epub::Converter();
 * const QList<EpubToc> listing = w->convert(in.at(1));
        if (listing.size() > 0) {
          EpubToc fox = listing.at(0);
           qDebug()  <<  fox.jumpurl << " -> isfile";
        }
        qDebug()  <<  listing.size() << " -> isfile";
  */
