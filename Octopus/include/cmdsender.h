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
    void setBrake(double brake);
private:
    QMutex mutex;
    QUdpSocket sendSocket;
    double v = 0;
    double w = 0;
    double brake = 0;
};
typedef Singleton<CmdSender> CommandSender;
#endif // CMDSENDER_H
