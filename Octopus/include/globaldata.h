#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "singleton.hpp"
#include <QMutex>

class CGlobalData{
public:
    CGlobalData();
    void setLantency(qint64 latency);
    qint64 getLantency();
private:
    QMutex mutex;
    qint64 latency = -9999;
};
typedef Singleton<CGlobalData> GlobalData;
#endif // GLOBALDATA_H
