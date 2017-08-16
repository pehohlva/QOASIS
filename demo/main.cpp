#include "rtfdemo.h"

#include <Qt/qapplication.h>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  RtfDemo demo;
  demo.resize(800, 600);
  demo.show();
  return app.exec();
 }
 
 