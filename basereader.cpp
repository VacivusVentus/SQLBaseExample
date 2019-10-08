#include "basereader.h"
#include <QTcpSocket>
#include <QSqlError>
#include "header.h"

BaseReader::BaseReader()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("tasks.db");
    server = new  QTcpServer(this);
    emit qmlLog("Init server");
}

BaseReader::~BaseReader()
{

}

void BaseReader::initServer(QString adminpass, QString portlisten)
{

    adminPasswd = adminpass;
    unsigned short port = portlisten.toUInt() & 0xFFFF;
    bool init = server->listen(QHostAddress::LocalHost, port);
    if (init) connect(server, &QTcpServer::newConnection, this, &BaseReader::newClient);
    init &= database.open();
    emit initdb(init);
    if (init)
    {
        query = QSqlQuery(database);
        bool ret = query.exec("create table if not exists Tasks(int id not null, char task varchar(1024) not null,"
                   "about varchar(4096) not null, timework varchar(32), progress int)"
        );
        if (!ret) {
            emit qmlLog(query.lastError().text());
            return;
        }
        ret = query.exec("create table if not exists Users(login varchar(32) not null, password varchar(64),"
                         "fio varchar(128))"
        );
        if (!ret) {
            emit qmlLog(query.lastError().text());
            return;
        }

        ret = query.exec("create table if not exists TU(int id not null, login varchar(32)"
                         "persontask varchar(4096), report varchar(4096))"
        );
        if (!ret) {
            emit qmlLog(query.lastError().text());
            return;
        }
    }
    emit initdb(init);
}

void BaseReader::newClient()
{
    QTcpSocket *sock = server->nextPendingConnection();
    connect(sock, &QTcpSocket::readyRead, this, &BaseReader::readSocket);
    connect(sock, &QTcpSocket::disconnected, this, &BaseReader::disconnectSocket);
    emit qmlLog("New connect");
}

void BaseReader::readSocket()
{
    QTcpSocket *sock = static_cast<QTcpSocket*>(sender());
    for (;sock->bytesAvailable() > 0;)  {
        QByteArray ba = sock->readAll();
        DBOperation operation = testPackege(ba);
        emit qmlLog("datagram from client");
        if (operation == DBOperation::NORE)
        {
            DBDisconnect disconnect;
            disconnect.dbcause = DBCause::BAD_PACKAGE;
            QByteArray berr;
            disconnect.toBytes(berr);
            sock->write(berr);
        }
        else if (operation == DBOperation::CONNECT)
        {
            DBConnect dbCon(ba);
            bool ret = query.exec("select count(*) from Users where login=" + dbCon.login +
                       "and password=" + dbCon.password);
        }
    }
}

void BaseReader::disconnectSocket()
{
    QTcpSocket *sock = static_cast<QTcpSocket*>(sender());
    sock->close();
    emit qmlLog("close socket");
}
