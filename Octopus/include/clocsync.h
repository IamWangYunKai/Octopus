#ifndef CLOCSYNC_H
#define CLOCSYNC_H

#include <QMutex>
#include <QUdpSocket>
#include "singleton.hpp"
#include "udpreceiver.h"

class ClocSync : public UDPReceiver{
public:
    ClocSync();
    void sendPackage(const int &n);
private:
    virtual void parseData(const QByteArray &receivedData);
    QMutex mutex;
    QUdpSocket sendSocket;
};
typedef Singleton<ClocSync> Sync;
#endif // CLOCSYNC_H
