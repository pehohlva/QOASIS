#include "core_application.h"
#include <QCoreApplication>



/*
static void usagethisapp(const char *name) {
    printf("Usage: %s (Options)  \n", name);
    printf("Tell the file to index Options ->  file.xx \n");
}
*/

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
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
ic/compact_lang_det.h /usr/local/include/compact_lang_det.h
/Users/dev/Applications/qt5.9.1/bin/qmake -install qinstall /Volumes/dati/var/QCLD2/google_bridge/cld2/public/encodings.h /usr/local/include/encodings.h
/Users/dev/Applications/qt5.9.1/bin/qmake -install qinstall /Volumes/dati/var/QCLD2/google_bridge/datalanguageprovider.h /usr/local/include/datalanguageprovider.h
/Users/dev/Applications/qt5.9.1/bin/qmake -install qinstall /Volumes/dati/var/QCLD2/google_bridge/qtrlocale.h /usr/local/include/qtrlocale.h
/Users/dev/Applications/qt5.9.1/bin/qmake -install qinstall libqcld2.a /usr/local/lib/libqcld2.a
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib -s /usr/local/lib/libqcld2.a



  */
