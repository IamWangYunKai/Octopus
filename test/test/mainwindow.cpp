#include "mainwindow.h"
#include "ui_mainwindow.h"


TCPInterface::TCPInterface(QObject *parent): QObject(parent){
    socket = new QTcpSocket();
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readyReadData()));
    qDebug() << "connect .....";
    socket->connectToHost(QString("127.0.0.1"),33334);
    if(!socket->waitForConnected(100)){
        qDebug() << "Error: " << socket->errorString();
    } else {
        qDebug() << "successfully connect!";
    }
//    readData();
}

void TCPInterface::readData(){
    while(true) {
        qDebug() << socket->isReadable();
        while (socket->waitForReadyRead(500)) {
            QByteArray receivedData = socket->readAll();
            qDebug() << receivedData.length() << receivedData;
        }
    }
}

void TCPInterface::readyReadData(){
    qDebug() << socket->isReadable();
    QByteArray receivedData = socket->readAll();
    qDebug() << receivedData.length() << receivedData;
    if(socket->state() == QAbstractSocket::ConnectedState){
        socket->write("OK");
        socket->waitForBytesWritten(100);
    } else{
        qDebug() << "Not connected";
    }
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
//    TCPInterface tcp;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

