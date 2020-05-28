#include "tcpinterface.h"
#include "parammanager.h"
#include "utils.h"
#include <QDebug>

TCPInterface::TCPInterface(const QString &regInfo, const int &_port, QObject *parent): QObject(parent) {
    ParamManager::instance()->loadParam(publicIP, "Network/public_ip", "127.0.0.1");
    ParamManager::instance()->loadParam(robot_id, "Robot/robot_id", "123456");
    publicPort = _port;
    socket = new QTcpSocket();
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(parseData()));
    setup(publicPort, publicIP);
}

//void TCPInterface::register2pub(const QString& regInfo){
//    QByteArray bytes = toMessage(regInfo, robot_id, QString("register"));
////    qDebug() << "regInfo" << bytes;
////    QByteArray bytes = regInfo.toUtf8();
////    socket.writeDatagram(bytes, QHostAddress(publicIP), publicPort);
//}

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

//void TCPInterface::parseData(){
//    qDebug() << socket->isReadable();
//    QByteArray receivedData = socket->readAll();
//    qDebug() << receivedData.length() << receivedData;
//    if(socket->state() == QAbstractSocket::ConnectedState){
//        socket->write("OK");
//        socket->waitForBytesWritten(100);
//    } else{
//        qDebug() << "Not connected";
//    }
//}

//void TCPInterface::startTempThread(){
//    tempThread = new std::thread([ = ] {waitForConnect();});
//    tempThread->detach();
//}

//void TCPInterface::start(){
//    receiveThread = new std::thread([ = ] {readData();});
//    receiveThread->detach();
//}

//void TCPInterface::readData(){
//    while(true) {
//        std::this_thread::sleep_for(std::chrono::microseconds(500));
//        while (socket->bytesAvailable()) {
//            QByteArray receivedData = socket->readAll();
//            qDebug() << receivedData.length();
////            socket.readDatagram(receivedData.data(), receivedData.size(), &hostAddress);
////            parseData(receivedData);
//        }
//    }
//}

void TCPInterface::waitForConnect(){
    while(!connected) {
//        std::this_thread::sleep_for(std::chrono::microseconds(500));
        connected = socket->waitForConnected(500);
//        while (socket.state() == QUdpSocket::BoundState && socket.hasPendingDatagrams()) {
//            QByteArray receivedData;
//            receivedData.resize(socket.pendingDatagramSize());
//            socket.readDatagram(receivedData.data(), receivedData.size());
//            if (receivedData.size() == 0) continue; // nothing
//            qDebug() <<"Connected ....";
//            connected = true;
//        }
    }
}
