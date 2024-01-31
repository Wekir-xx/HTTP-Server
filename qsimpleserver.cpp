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
    QTcpSocket* socket = new QTcpSocket();
    socket->setSocketDescriptor (handle);

    connect (socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect (socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void QSimpleServer::onReadyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender ());
    qDebug() << socket->readAll ();

    QString response = "HTTP/1.1 200 OK\r\n\r\n%1";
    socket->write(response.arg(QTime::currentTime().toString()).toUtf8());
    socket->disconnectFromHost ();
}

void QSimpleServer::onDisconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender ());
    socket->close ();
    socket->deleteLater ();
}
