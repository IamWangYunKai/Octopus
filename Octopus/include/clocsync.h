#ifndef CLOCSYNC_H
#define CLOCSYNC_H

#include <QMutex>
#include "singleton.hpp"
#include "udpreceiver.h"

class ClocSync : public UDPReceiver{
public:
    ClocSync();
private:
    virtual void parseData(const QByteArray &receivedData);
    QMutex mutex;
};
typedef Singleton<ClocSync> Sync;
#endif // CLOCSYNC_H
