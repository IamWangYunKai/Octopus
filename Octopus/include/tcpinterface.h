#ifndef TCPINTERFACE_H
#define TCPINTERFACE_H

#include <thread>
#include <QObject>
#include <QTcpSocket>

class TCPInterface : public QObject {
    Q_OBJECT
public:
    explicit TCPInterface(const QString &regInfo = QString(""), const int &_port=0, QObject *parent = Q_NULLPTR);
    virtual ~TCPInterface() {}
    bool setup(const int &port, const QString &address);
    void register2pub(const QString& regInfo);
//    void readData();
//    void start();
    void startTempThread();
    void waitForConnect();
    QTcpSocket *socket = nullptr;
    QString ip;
    int port;
    QString publicIP;
    QString robot_id;
    int publicPort;
    bool connected = false;
    std::thread* tempThread = nullptr;
//private:
//    virtual void parseData(const QByteArray &receivedData){}
//    void register2pub(const QString& regInfo);
//    void startTempThread();
public slots:
//    void parseData();
    virtual void parseData(){}
};

#endif // TCPINTERFACE_H
