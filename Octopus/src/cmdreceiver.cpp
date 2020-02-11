#include "cmdreceiver.h"
#include<QJsonObject>
#include<QJsonDocument>

namespace {
    const int PORT_RECEIVE = 23334;
    const QString BOARDCAST_ADDRESS = "233.233.233.233";
}

CmdReceiver::CmdReceiver(){
    bool ret = setup(PORT_RECEIVE, BOARDCAST_ADDRESS);
    if (ret) start();
    else qDebug() << "Bind Error in CmdReceiver !";
}

void CmdReceiver::parseData(QByteArray receivedData){
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(receivedData, &jsonError);
//    qDebug() << receivedData << jsonError.errorString();
    QJsonObject jsonObject = jsonDoc.object();
//    qDebug() << jsonObject.value("v").toDouble();
//    qDebug() << jsonObject.value("w").toDouble();
//    qDebug() << jsonObject.value("c").toBool();
}
