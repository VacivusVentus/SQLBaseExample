#ifndef CLIENTCLASS_H
#define CLIENTCLASS_H

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include "header.h"

class ClientClass : public QObject
{
    Q_OBJECT
public:
    explicit ClientClass(QObject *parent = nullptr);

signals:
    void addTaskTofield(quint32 idtask, QString task, QString describe, QString bdate, QString edate, quint8 progrss);
    void addUserToField(QString fio, QString login, QString usertask, QString report);
    void hasInfoTaskUser(quint32 idtask, QString login, bool isActive);
    void initTaskField();
    void addTaskInformation(quint32 idtask, QString task, QString describe, QString date, quint8 progress);
public slots:
    void connectToBase(QString ip, QString port, QString login, QString password);
    void fillSocket();
    void sendToSocket();

private:
    QTcpSocket *clientsocket;
    quint16 port;
    QString ip;
    QString login, passwrd;
    QByteArray sendBytes;
    QList<TaskInformation>taskInfList;
};

#endif // CLIENTCLASS_H
