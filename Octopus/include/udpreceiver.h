#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <thread>
#include <QUdpSocket>

class UDPReceiver {
public:
    UDPReceiver();
    UDPReceiver(const int port, const QString address);
    bool setup(const int port, const QString address);
    void readData();
    void start();
    QHostAddress getHostAddress(){return hostAddress;}
private:
    virtual void parseData(QByteArray receivedData){}
    QUdpSocket receiveSocket;
    std::thread* receiveThread = nullptr;
    QHostAddress hostAddress;
};

#endif // UDPRECEIVER_H
