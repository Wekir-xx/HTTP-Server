#include "qsocketthread.h"

QSocketThread::QSocketThread(int descriptor, QObject *parent):
    QThread(parent), socketDescriptor(descriptor)
{}

QSocketThread::~QSocketThread()
{
    delete socket;
}

void QSocketThread::run()
{
    socket = new QTcpSocket();
    socket->setSocketDescriptor (socketDescriptor);

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()),Qt::DirectConnection);

    exec();
}

void QSocketThread::onReadyRead()
{
    qDebug() << socket->readAll ();

    QString response = "HTTP/1.1 200 OK\r\n\r\n%1";
    socket->write(response.arg(QTime::currentTime().toString()).toUtf8());
    socket->disconnectFromHost ();
}

void QSocketThread::onDisconnected()
{
    socket->close();
    quit();
}
