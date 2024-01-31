#include "qsimpleserver.h"

QSimpleServer::QSimpleServer(QObject *parent):
    QTcpServer{parent}
{
    if(listen (QHostAddress::Any, 5500))
        qDebug() << "Listening...";
    else
        qDebug() << "Error while starting: " << errorString ();
}

void QSimpleServer::incomingConnection(qintptr handle)
{
    QSocketThread* thread = new QSocketThread(handle);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start ();
}
