#include "cmdreceiver.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "parammanager.h"

namespace {
    int PORT_RECEIVE = 23334;
    QString BOARDCAST_ADDRESS = "233.233.233.233";
    double MAX_V = 9999;
    double MAX_W = 9999;
}

CmdReceiver::CmdReceiver(){
    ParamManager::instance()->loadParam(MAX_V, "Motion/max_v", 5.0);
    ParamManager::instance()->loadParam(MAX_W, "Motion/max_w", 5.0);
    ParamManager::instance()->loadParam(PORT_RECEIVE, "Network/cmd_port", 23334);
    ParamManager::instance()->loadParam(BOARDCAST_ADDRESS, "Network/multicast_address", "233.233.233.233");
    bool ret = setup(PORT_RECEIVE, BOARDCAST_ADDRESS);
    if (ret) start();
    else qDebug() << "Bind Error in CmdReceiver !";
}

void CmdReceiver::parseData(const QByteArray &receivedData){
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
