#ifndef DOCHANDLER_H
#define DOCHANDLER_H

#include <QObject>

class DocHandler : public QObject
{
    Q_OBJECT
public:
    explicit DocHandler(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DOCHANDLER_H