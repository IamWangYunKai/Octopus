#ifndef CMDRECEIVER_H
#define CMDRECEIVER_H

#include "singleton.hpp"
#include "udpreceiver.h"

class CmdReceiver : public UDPReceiver{
public:
    CmdReceiver();
private:
    virtual void parseData(QByteArray receivedData);
};

typedef Singleton<CmdReceiver> CommandReceiver;
#endif // CMDRECEIVER_H
