#include <QCoreApplication>
#include <qsimpleserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSimpleServer server;

    return a.exec();
}
