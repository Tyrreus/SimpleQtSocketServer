#include "socketserver.h"
#include <QTcpSocket>
#include <QtDebug>

SocketServer::SocketServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any, 2000)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
}

void SocketServer::newConnection() {
    QTcpSocket *socket = server->nextPendingConnection();
    qDebug() << "Got new connection!";
    socket->write("Response from server!\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);
    socket->close();
}
