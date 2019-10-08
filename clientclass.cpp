#include "clientclass.h"
#include <QHostAddress>

ClientClass::ClientClass(QObject *parent) : QObject(parent)
{
    taskInfList.clear();
    timer = nullptr;
    clientsocket = nullptr;
}


void ClientClass::connectToBase(QString ip, QString port, QString login, QString password)
{
    this->ip = ip;
    this->port = port.toUInt() & 0xFFFF;
    this->login = login;
    this->passwrd = password;

    if (login.length() == 0 || password.length() == 0)
    {
        emit showNtifiy(tr("Input login and password"));
        return;
    }

    sendBytes.clear();
    DBConnect db;
    db.login = login;
    db.password = passwrd;
    db.toBytes(sendBytes);
    if (clientsocket)
    {
        clientsocket->close();
        delete clientsocket;
        clientsocket = nullptr;
    }
    clientsocket = new QTcpSocket(this);
    clientsocket->connectToHost(QHostAddress(ip), this->port);
    connect(clientsocket, &QTcpSocket::readyRead, this, &ClientClass::fillSocket);
    connect(clientsocket, &QTcpSocket::connected, this, &ClientClass::sendToSocket);

    if (timer)
    {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    timer = new QTimer(this);

    emit printLog("Send to server");
    connect(timer, &QTimer::timeout, this, &ClientClass::timeoutDetect);
    timer->setInterval(1000);
    timer->start();
}

void ClientClass::fillSocket()
{
    for (;clientsocket->bytesAvailable() > 0;)
    {
        QByteArray ba = clientsocket->readAll();
        DBOperation operation = testPackege(ba);
        if (operation == DBOperation::CLOSECONNECT)
        {
            DBDisconnect dis(ba);
            if (dis.dbcause == DBCause::COMPLETE_CONNECT)
            {
                 emit initTaskField();
            } else if  (dis.dbcause == DBCause::BAD_DB || dis.dbcause == DBCause::LOGIN_PASSWORD || dis.dbcause == DBCause::BAD_PACKAGE)
            {
                emit showNtifiy(dis.getCauseToClose());
            } else emit showNtifiy(QString::number(dis.dbcause));
            timer->stop();
            delete timer;
            timer = nullptr;
            clientsocket->close();
        } else if (operation == DBOperation::TASK_LINE)
        {
            TaskInformation taskInform(ba);
            taskInfList.append(ba);
            emit addTaskTofield(taskInform.idtask, taskInform.task, taskInform.descibe,
                                taskInform.startDate, taskInform.endDate, taskInform.progress);
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
void ClientClass::openTask(quint32 idtask)
{
}

void ClientClass::getTaskList()
{
    TaskInformation tinf;
    tinf.toBytes(sendBytes);
    if (clientsocket)
    {
        clientsocket->close();
        delete clientsocket;
        clientsocket = nullptr;
    }
    clientsocket = new QTcpSocket(this);
    clientsocket->connectToHost(QHostAddress(ip), this->port);
    connect(clientsocket, &QTcpSocket::readyRead, this, &ClientClass::fillSocket);
    connect(clientsocket, &QTcpSocket::connected, this, &ClientClass::sendToSocket);
    emit printLog("Send: get tasks");
}

void ClientClass::timeoutDetect()
{
    if (timer)
    {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    if (clientsocket)
    {
        clientsocket->close();
        delete clientsocket;
        clientsocket = nullptr;
    }
    emit showNtifiy(tr("Timeout. There is not answer from server"));
}
