#include "cmdsender.h"
#include "parammanager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

namespace {
    int PORT_SEND = 23338;
    QString BOARDCAST_ADDRESS = "233.233.233.233";
}

CmdSender::CmdSender(){
    ParamManager::instance()->loadParam(BOARDCAST_ADDRESS, "Network/multicast_address", "233.233.233.233");
    ParamManager::instance()->loadParam(PORT_SEND, "Network/cmd_send", 23338);
}

void CmdSender::sendCmd(){
    QJsonObject object;
    mutex.lock();
    object.insert("v",v);
    object.insert("w",w);
    object.insert("b",brake);
    mutex.unlock();
    QJsonDocument doc;
    doc.setObject(object);
    QByteArray bytes = doc.toJson(QJsonDocument::Compact);
    sendSocket.writeDatagram(bytes, QHostAddress(BOARDCAST_ADDRESS), PORT_SEND);
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
