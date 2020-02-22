#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "singleton.hpp"
#include <QMutex>

class CGlobalData{
public:
    CGlobalData();
    void setLatency(const qint64 &latency);
    qint64 getLatency();
    int getFPS(); //get FPS every second, and clear it
    void countFPS();
    void setStop(const bool &flag);
    bool getStop();
    void setSyncBias(const qint64 &timeBias); // nanoseconds
    qint64 getSyncBias(); // nanoseconds
private:
    QMutex mutex;
    int fps = 0;
    qint64 latency = -9999;
    bool stopFlag = false;
    qint64 syncBias = 0;
};
typedef Singleton<CGlobalData> GlobalData;
#endif // GLOBALDATA_H
