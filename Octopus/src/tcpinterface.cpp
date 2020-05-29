#include "tcpinterface.h"
#include "parammanager.h"
#include "utils.h"
#include <QDebug>

TCPInterface::TCPInterface(const QString &regInfo, const int &_port, QObject *parent): QObject(parent) {
    ParamManager::instance()->loadParam(publicIP, "Network/public_ip", "127.0.0.1");
    ParamManager::instance()->loadParam(robot_id, "Robot/robot_id", "123456");
    publicPort = _port;
    socket = new QTcpSocket();
//    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(parseData()));
    setup(publicPort, publicIP);
    register2pub(regInfo);
    startTempThread();
}

void TCPInterface::register2pub(const QString& regInfo){
    QByteArray bytes = toMessage(regInfo, robot_id, QString("register"));
    socket->write(bytes);
    socket->waitForBytesWritten(100);
}

bool TCPInterface::setup(const int &port, const QString &address){
    socket->connectToHost(publicIP, publicPort);
    if(!socket->waitForConnected(1000)){
        qDebug() << "Connection time out!";
        return false;
    } else {
        qDebug() << "Successfully connected !";
        return true;
    }
}

void TCPInterface::startTempThread(){
    tempThread = new std::thread([ = ] {waitForConnect();});
    tempThread->detach();
}

void TCPInterface::waitForConnect(){
    while(true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        QByteArray receivedData = socket->readAll();
        if (receivedData.size() == 0) continue;
        else{
            qDebug() <<"TCP Connected ....";
            break;
        }
    }
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(parseData()));
}
