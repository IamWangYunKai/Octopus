#ifndef CLOCSYNC_H
#define CLOCSYNC_H

#include <QMutex>
#include <QUdpSocket>
#include "singleton.hpp"
#include "udpinterface.h"

class ClocSync : public UDPInterface{
public:
    ClocSync();
    void sendPackage(const int &n);
private:
    virtual void parseData(const QByteArray &receivedData);
    QMutex mutex;
};
typedef Singleton<ClocSync> SyncCloc;
#endif // CLOCSYNC_H
