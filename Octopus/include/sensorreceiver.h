#ifndef SENSORRECEIVER_H
#define SENSORRECEIVER_H

#include <QMutex>
#include "singleton.hpp"
#include "udpinterface.h"

class SensorReceiver : public UDPInterface{
public:
    SensorReceiver();
    double getV(){return v;}
    double getW(){return w;}
    bool getC(){return c;}
private:
    virtual void parseData(const QByteArray &receivedData);
    QMutex mutex;
    double v = 0;
    double w = 0;
    bool c = false;
};
typedef Singleton<SensorReceiver> SensorInterface;
#endif // SENSORRECEIVER_H
