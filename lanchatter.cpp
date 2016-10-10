#include "LANChatter.h"

LANChatter::LANChatter(QObject *parent) : QObject(parent){
    QObject::connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(read()));
}

LANChatter::~LANChatter(){
    emit dead();
}

void LANChatter::connect(QString adress, qint16 port){
    tcpSocket.close();
    tcpSocket.connectToHost(adress, port);
    tcpSocket.waitForConnected(1000);
    tcpSocket.write("ping\n");
}


void LANChatter::send(QString data){
    tcpSocket.write(data.toLocal8Bit() + "\n");
}

void LANChatter::read(){
    emit out(tcpSocket.readAll());
}
