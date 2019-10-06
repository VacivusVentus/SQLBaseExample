#ifndef CLIENTCLASS_H
#define CLIENTCLASS_H

#include <QObject>

class ClientClass : public QObject
{
    Q_OBJECT
public:
    explicit ClientClass(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CLIENTCLASS_H
