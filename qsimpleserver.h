#ifndef QSIMPLESERVER_H
#define QSIMPLESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>
#include "qsocketthread.h"

class QSimpleServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QSimpleServer(QObject *parent = 0);

signals:

public slots:
    void incomingConnection (qintptr handle);
};

#endif // QSIMPLESERVER_H
