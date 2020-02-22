#include "clocsync.h"
#include <QDebug>
#include <QTime>
#include "globaldata.h"

namespace {
    const int PORT_RECEIVE = 23336;
    const int PORT_SEND = 23337;
    const QString BOARDCAST_ADDRESS = "233.233.233.233";
    const int SYNC_PACKAGE_NUM = 10;
    qint64 last_remote_tsp = 0;
    qint64 last_local_tsp = 0;
    const double UPDATE_RATE = 0.2;
}

ClocSync::ClocSync(){
    bool ret = setup(PORT_RECEIVE, BOARDCAST_ADDRESS);
    if (ret) start();
    else qDebug() << "Bind Error in ClocSync !";
    sendPackage(SYNC_PACKAGE_NUM);
}

void ClocSync::sendPackage(const int &n){
    QByteArray bytes = QString::number(n).toUtf8();
    sendSocket.writeDatagram(bytes, QHostAddress(BOARDCAST_ADDRESS), PORT_SEND);
}

void ClocSync::parseData(const QByteArray &receivedData){
    qint64 remote_timestamp = static_cast<qint64>(receivedData.mid(16, 16).toLongLong());
    QByteArray data = receivedData.mid(32);
    qint64 local_timestamp = QDateTime::currentMSecsSinceEpoch()*1000;
    int number = data.toInt();
    if (number == SYNC_PACKAGE_NUM - 1){
        last_remote_tsp = remote_timestamp;
        last_local_tsp = local_timestamp;
    }
    else{
        qint64 timeBias = (2*last_local_tsp - last_remote_tsp - remote_timestamp)/2;
        last_remote_tsp = remote_timestamp;
        last_local_tsp = local_timestamp;

        qint64 old_tb = GlobalData::instance()->getSyncBias();
        if (old_tb == 0) GlobalData::instance()->setSyncBias(timeBias);
        else{
            qint64 new_tb = static_cast<qint64>(old_tb*(1 - UPDATE_RATE) + timeBias*UPDATE_RATE);
//            qDebug() << "timeBias" << timeBias << new_tb;
            GlobalData::instance()->setSyncBias(new_tb);
        }
    }
    if (number > 0){
        sendPackage(number--);
    }
}
