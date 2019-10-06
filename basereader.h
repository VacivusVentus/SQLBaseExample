#ifndef BASEREADER_H
#define BASEREADER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTcpServer>

class BaseReader : public QObject
{
    Q_OBJECT
public:
    explicit BaseReader();
    virtual ~BaseReader();
    Q_INVOKABLE
    void initServer(QString adminpass, QString portlisten);
private:
    QSqlDatabase database;
    QSqlQuery query;
    QTcpServer *server;
    QString adminPasswd;
    QString login;
signals:
    void initdb(bool isInit);
    void qmlLog(QString msg);
private slots:
    void newClient();
    void readSocket();
    void disconnectSocket();
};

#endif // BASEREADER_H
