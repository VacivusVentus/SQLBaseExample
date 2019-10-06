#ifndef CLIENTCLASS_H
#define CLIENTCLASS_H

#include <QObject>
#include <QTcpSocket>

class ClientClass : public QObject
{
    Q_OBJECT
public:
    explicit ClientClass(QObject *parent = nullptr);

signals:

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
};

#endif // CLIENTCLASS_H
