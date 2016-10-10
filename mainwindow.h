#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logger.h"
#include <QThread>
#include "lanchatter.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void in(QString data);

signals:
    void connect(QString adress, qint16 port);
    void send(QString data);


private:
    Ui::MainWindow *ui;
    Logger *log;
    QThread *lanThread;
    LANChatter *lan;
    QString adress = "172.16.13.21";
    qint16 port = 1;
    QTimer* timer;

private slots:
    void sendButton();
    void connectButton();
    void stopButton();
    void timerIn();


};

#endif // MAINWINDOW_H
