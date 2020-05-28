#ifndef TCPINTERFACE_H
#define TCPINTERFACE_H

#include <thread>
#include <QTcpSocket>

class TCPInterface {
public:
    TCPInterface(const QString &regInfo = QString(""), const int &_port=0);
    bool setup(const int &port, const QString &address);
    void readData();
    void start();
    void waitForConnect();
    QTcpSocket socket;
    QString ip;
    int port;
    QString publicIP;
    QString robot_id;
    int publicPort;
    bool connected = false;
private:
    virtual void parseData(const QByteArray &receivedData){}
    void register2pub(const QString& regInfo);
    void startTempThread();
    std::thread* receiveThread = nullptr;
    std::thread* tempThread = nullptr;
};

#endif // TCPINTERFACE_H
