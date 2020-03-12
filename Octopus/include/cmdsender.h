#ifndef CMDSENDER_H
#define CMDSENDER_H

#include <QMutex>
#include <QUdpSocket>
#include "singleton.hpp"

class CmdSender{
public:
    CmdSender();
    void sendCmd();
    void setV(double _v);
    void setW(double _w);
    void setBrake(double _brake);
    void setGear(int _gear);
    void setHandBrake(bool _handbrake);
private:
    QMutex mutex;
    QUdpSocket sendSocket;
    double v = 0;
    double w = 0;
    double brake = 0;
    int gear = 1;
    bool handbrake = false;
};
typedef Singleton<CmdSender> CommandSender;
#endif // CMDSENDER_H
