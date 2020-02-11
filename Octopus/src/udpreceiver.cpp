#include "udpreceiver.h"
#include <QDebug>

UDPReceiver::UDPReceiver(){
}

UDPReceiver::UDPReceiver(const int port, const QString address){
    if(setup(port, address)){
        start();
    }
    else{
        qDebug() << "Bind Error in UDPReceiver !";
    }
}

bool UDPReceiver::setup(const int port, const QString address){
    return receiveSocket.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)
           && receiveSocket.joinMulticastGroup(QHostAddress(address));
}

void UDPReceiver::start(){
    receiveThread = new std::thread([ = ] {readData();});
    receiveThread->detach();
}

void UDPReceiver::readData(){
    while(true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        while (receiveSocket.state() == QUdpSocket::BoundState && receiveSocket.hasPendingDatagrams()) {
            QByteArray receivedData;
            receivedData.resize(receiveSocket.pendingDatagramSize());
            receiveSocket.readDatagram(receivedData.data(), receivedData.size(), &hostAddress);
            parseData(receivedData);
        }
    }
}
