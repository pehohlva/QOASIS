#ifndef DRAWAPPLICATION_H
#define DRAWAPPLICATION_H

#include "drawdocument.h"
#include "tooldoc.h"

#define drawapplication (static_cast<RDoc *>(QCoreApplication::instance()))

class DrawApplication : public QApplication {
  Q_OBJECT
public:
  DrawApplication(int &argc, char **argv);
  DocSession *Sessions() { return cookie; }
  bool event(QEvent *event);
  void closeEvent(QCloseEvent *event);
signals:
  void internal_L(QString);
public slots:
  void prepare_to_close();

private:
  qreal strak;
  DrawDocument *paintdoc;
  DocSession *cookie;
};

#endif // DRAWAPPLICATION_H
