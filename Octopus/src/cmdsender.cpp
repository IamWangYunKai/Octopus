#include "cmdsender.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <thread>
namespace  {
    const int PORT = 10003;
}
CmdSender::CmdSender() : UDPInterface(QString("client:cmd"), PORT){
}

void CmdSender::sendCmd(){
    if(!connected) return;
    QJsonObject object;
    mutex.lock();
    object.insert("v",v);
    object.insert("w",w);
    object.insert("b",brake);
    object.insert("g",gear);
    object.insert("h",handbrake);
    mutex.unlock();
    QJsonDocument doc;
    doc.setObject(object);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    socket.writeDatagram(data, QHostAddress(publicIP), publicPort);
}

void CmdSender::setV(double _v){
    mutex.lock();
    v = _v;
    mutex.unlock();
}

void CmdSender::setW(double _w){
    mutex.lock();
    w = _w;
    mutex.unlock();
}

void CmdSender::setBrake(double _brake){
    mutex.lock();
    brake = _brake;
    mutex.unlock();
}

void CmdSender::setGear(int _gear){
    mutex.lock();
    gear = _gear;
    mutex.unlock();
}

void CmdSender::setHandBrake(bool _handbrake){
    mutex.lock();
    handbrake = _handbrake;
    mutex.unlock();
}
