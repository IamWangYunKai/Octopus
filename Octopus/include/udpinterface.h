#ifndef UDPINTERFACE_H
#define UDPINTERFACE_H

#include <thread>
#include <QUdpSocket>

class UDPInterface {
public:
    UDPInterface(const QString &regInfo = QString(""), const int &_port=0);
    bool setup(const int &port, const QString &address);
    void readData();
    void start();
    QHostAddress getHostAddress(){return hostAddress;}
    void waitForConnect();
    QUdpSocket socket;
    QString ip;
    int port;
    QString publicIP;
    int publicPort;
    bool connected = false;
private:
    virtual void parseData(const QByteArray &receivedData){}
    void register2pub(const QString& regInfo);
    void startTempThread();
    std::thread* receiveThread = nullptr;
    std::thread* tempThread = nullptr;
    QHostAddress hostAddress;
};

#endif // UDPINTERFACE_H
