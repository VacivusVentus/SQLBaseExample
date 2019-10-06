#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTcpServer>

class ServerThread: public QThread
{
    Q_OBJECT
public:
    ServerThread(QObject *parent = nullptr);
protected:
    void run() override;
};

#endif // SERVERTHREAD_H
