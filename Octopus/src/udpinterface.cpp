#include "udpinterface.h"
#include "parammanager.h"
#include "utils.h"
#include <QDebug>

UDPInterface::UDPInterface(const QString &regInfo, const int &_port){
    ParamManager::instance()->loadParam(publicIP, "Network/public_ip", "127.0.0.1");
    ParamManager::instance()->loadParam(robot_id, "Robot/robot_id", "123456");
    publicPort = _port;
    register2pub(regInfo);
    startTempThread();
}
void UDPInterface::register2pub(const QString& regInfo){
    QByteArray bytes = toMessage(regInfo, robot_id, QString("register"));
//    qDebug() << "regInfo" << bytes;
//    QByteArray bytes = regInfo.toUtf8();
    socket.writeDatagram(bytes, QHostAddress(publicIP), publicPort);
}

bool UDPInterface::setup(const int &port, const QString &address){
    return socket.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)
           && socket.joinMulticastGroup(QHostAddress(address));
}

void UDPInterface::startTempThread(){
    tempThread = new std::thread([ = ] {waitForConnect();});
    tempThread->detach();
}

void UDPInterface::start(){
    receiveThread = new std::thread([ = ] {readData();});
    receiveThread->detach();
}

void UDPInterface::readData(){
    while(true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        while (socket.state() == QUdpSocket::BoundState && socket.hasPendingDatagrams()) {
            QByteArray receivedData;
            receivedData.resize(socket.pendingDatagramSize());
            socket.readDatagram(receivedData.data(), receivedData.size(), &hostAddress);
            parseData(receivedData);
        }
    }
}

void UDPInterface::waitForConnect(){
    while(!connected) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        while (socket.state() == QUdpSocket::BoundState && socket.hasPendingDatagrams()) {
            QByteArray receivedData;
            receivedData.resize(socket.pendingDatagramSize());
            socket.readDatagram(receivedData.data(), receivedData.size());
            if (receivedData.size() == 0) continue; // nothing
//            QString address = QString::fromUtf8(receivedData);
//            QStringList addressList = address.split(':', QString::SkipEmptyParts);
//            ip = QString(addressList.at(0));
//            port = addressList.at(1).toInt();
            qDebug() <<"Connected ....";
            connected = true;
        }
    }
    start();
}
