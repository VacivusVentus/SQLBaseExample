#include "clientclass.h"
#include <QHostAddress>

ClientClass::ClientClass(QObject *parent) : QObject(parent)
{
    taskInfList.clear();
}

void ClientClass::connectToBase(QString ip, QString port, QString login, QString password)
{
    this->ip = ip;
    this->port = port.toUInt() & 0xFFFF;
    this->login = login;
    this->passwrd = password;

    clientsocket = new QTcpSocket(this);
    clientsocket->connectToHost(QHostAddress(ip), this->port);
    connect(clientsocket, &QTcpSocket::readyRead, this, &ClientClass::fillSocket);
    connect(clientsocket, &QTcpSocket::connected, this, &ClientClass::sendToSocket);
    sendBytes.clear();
    DBConnect db;
    db.login = login;
    db.password = passwrd;
    db.toBytes(sendBytes);
    emit initTaskField();
}

void ClientClass::fillSocket()
{
    for (;clientsocket->bytesAvailable() > 0;)
    {
        QByteArray ba = clientsocket->readAll();
        DBOperation operation = testPackege(ba);
        if (operation == DBOperation::CLOSECONNECT)
        {
            clientsocket->close();
            delete  clientsocket;
            clientsocket = nullptr;
        } else if (operation == DBOperation::TASK_LINE)
        {
            TaskInformation taskInform(ba);
            taskInfList.append(ba);
        }
    }
}

void ClientClass::sendToSocket()
{
     if (sendBytes.size()) clientsocket->write(sendBytes);
     else {
         clientsocket->close();
         delete clientsocket;
         clientsocket = nullptr;
     }
     sendBytes.clear();
}
