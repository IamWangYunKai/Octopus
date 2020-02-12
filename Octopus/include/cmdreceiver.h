#ifndef CMDRECEIVER_H
#define CMDRECEIVER_H

#include <QMutex>
#include "singleton.hpp"
#include "udpreceiver.h"

class CmdReceiver : public UDPReceiver{
public:
    CmdReceiver();
    double getV(){return v;}
    double getW(){return w;}
    bool getC(){return c;}
private:
    virtual void parseData(QByteArray receivedData);
    QMutex mutex;
    double v = 0;
    double w = 0;
    bool c = false;
};
typedef Singleton<CmdReceiver> CommandReceiver;
#endif // CMDRECEIVER_H
