#include "globaldata.h"

CGlobalData::CGlobalData(){
}

void CGlobalData::setLatency(const qint64 &latency){
    mutex.lock();
    this->latency = latency;
    mutex.unlock();
}

qint64 CGlobalData::getLatency(){
    mutex.lock();
    auto latency = this->latency;
    mutex.unlock();
    return latency;
}

int CGlobalData::getFPS(){
    mutex.lock();
    auto _fps = this->fps;
    this->fps = 0;
    mutex.unlock();
    return _fps;
}

void CGlobalData::countFPS(){
    mutex.lock();
    this->fps ++;
    mutex.unlock();
}

void CGlobalData::setStop(const bool &flag){
    mutex.lock();
    this->stopFlag = flag;
    mutex.unlock();
}

bool CGlobalData::getStop(){
    mutex.lock();
    auto flag = this->stopFlag;
    mutex.unlock();
    return flag;
}

void CGlobalData::setSyncBias(const qint64 &timeBias){
    mutex.lock();
    syncBias = timeBias;
    mutex.unlock();
}

qint64 CGlobalData::getSyncBias(){
    mutex.lock();
    auto timeBias = syncBias;
    mutex.unlock();
    return timeBias;
}
