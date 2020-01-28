#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "singleton.hpp"
#include <QMutex>

class CGlobalData{
public:
    CGlobalData();
    void setLatency(qint64 latency);
    qint64 getLatency();
    int getFPS(); //get FPS every second, and clear it
    void countFPS();
    void setStop(bool flag);
    bool getStop();
private:
    QMutex mutex;
    int fps = 0;
    qint64 latency = -9999;
    bool stopFlag = false;
};
typedef Singleton<CGlobalData> GlobalData;
#endif // GLOBALDATA_H
