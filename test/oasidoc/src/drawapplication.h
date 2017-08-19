#ifndef DRAWAPPLICATION_H
#define DRAWAPPLICATION_H

#include "drawdocument.h"
#include "tooldoc.h"

#define drawapplication (static_cast<RDoc *>(QCoreApplication::instance()))

class DrawApplication : public QApplication {
  Q_OBJECT
public:
  DrawApplication(int &argc, char **argv);
  bool event(QEvent *event);
signals:
  void internal_L(QString);
public slots:
  void prepare_to_close();

private:
  qreal strak;
};

#endif // DRAWAPPLICATION_H
