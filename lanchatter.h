#ifndef LANChatter_H
#define LANChatter_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>


class LANChatter : public QObject{

    Q_OBJECT

public:
    LANChatter(QObject *parent = 0);
    QTcpSocket tcpSocket;
    ~LANChatter();


signals:
    void error(QString error);
    void out(QString data);
    void dead();

private:
    QDataStream in;

public slots:
    void connect(QString adress, qint16 port);
    void send(QString data);
    void read();

private slots:


};

#endif // LANChatter_H
