#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    log = new Logger();
    ui->setupUi(this);
    lanThread = new QThread();
    lan = new LANChatter();
    lan->moveToThread(lanThread);
    lan->tcpSocket.moveToThread(lanThread);
    ui->stopButton->setEnabled(false);
    QObject::connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopButton);
    QObject::connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectButton);
    QObject::connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendButton);
    QObject::connect(lan, SIGNAL(dead()), lanThread, SLOT(quit()));
    QObject::connect(lanThread, SIGNAL(finished()), lan, SLOT(deleteLater()));
    QObject::connect(lan, SIGNAL(dead()), lanThread, SLOT(deleteLater()));
    QObject::connect(this, SIGNAL(connect(QString, qint16)), lan, SLOT(connect(QString, qint16)));
    QObject::connect(this, SIGNAL(send(QString)), lan, SLOT(send(QString)));
    QObject::connect(lan, SIGNAL(error(QString)), this, SLOT(in(QString)));
    QObject::connect(lan, SIGNAL(out(QString)), this, SLOT(in(QString)));
    QObject::connect(this, SIGNAL(send(QString)), log, SLOT(sending(QString)));
    QObject::connect(lan, SIGNAL(error(QString)), log, SLOT(error(QString)));
    QObject::connect(lan, SIGNAL(out(QString)), log, SLOT(received(QString)));
    lanThread->start();
}

MainWindow::~MainWindow()
{
    delete lan;
    lanThread->quit();
    lanThread->requestInterruption();
    log->print("QThread dead : ");
        if(lanThread->wait()){
            log->print("True");
        }else{
            log->print("False");
        }
    delete lanThread;
    delete ui;
    delete log;
}

void MainWindow::connectButton(){
    emit connect(adress, port);
    ui->stopButton->setEnabled(false);
}

void MainWindow::sendButton(){
    ui->connectButton->setEnabled(false);
    ui->sendButton->setEnabled(false);
    timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->start(1000);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerIn()));
    //emit send("request");
    ui->stopButton->setEnabled(true);
}

void MainWindow::stopButton(){
    ui->connectButton->setEnabled(true);
    ui->sendButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    timer->stop();
   //emit end();
}

void MainWindow::in(QString data){
    //do something with data
}

void MainWindow::timerIn(){
    emit send("request");
}
