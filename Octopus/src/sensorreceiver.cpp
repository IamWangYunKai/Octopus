#include "sensorreceiver.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "parammanager.h"

namespace {
    double MAX_V = 9999;
    double MAX_W = 9999;
}

SensorReceiver::SensorReceiver() : UDPInterface(QString("client:sensor")){
    ParamManager::instance()->loadParam(MAX_V, "Motion/max_v", 5.0);
    ParamManager::instance()->loadParam(MAX_W, "Motion/max_w", 5.0);
}

void SensorReceiver::parseData(const QByteArray &receivedData){
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(receivedData, &jsonError);
//    qDebug() << receivedData << jsonError.errorString();
    QJsonObject jsonObject = jsonDoc.object();
    mutex.lock();
    v = jsonObject.value("v").toDouble()/MAX_V;
    w = jsonObject.value("w").toDouble()/MAX_W;
    c = jsonObject.value("c").toBool();
    mutex.unlock();
}
