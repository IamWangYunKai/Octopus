#include "clocsync.h"
#include <QDebug>
#include <QTime>

namespace {
    const int PORT_RECEIVE = 23336;
    const QString BOARDCAST_ADDRESS = "233.233.233.233";
}

ClocSync::ClocSync(){
    bool ret = setup(PORT_RECEIVE, BOARDCAST_ADDRESS);
    if (ret) start();
    else qDebug() << "Bind Error in ClocSync !";
}

void ClocSync::parseData(const QByteArray &receivedData){
    auto package_remain = receivedData.mid(0, 8).toInt();
    qint64 remote_timestamp = static_cast<qint64>(receivedData.mid(8, 16).toLongLong());
    QByteArray data = receivedData.mid(8+16);
    qint64 local_timestamp = QDateTime::currentMSecsSinceEpoch();
    qint64 latency = local_timestamp - remote_timestamp/1000;
}
