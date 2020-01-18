#include "globaldata.h"

CGlobalData::CGlobalData(){

}


void CGlobalData::setLantency(qint64 latency){
    mutex.lock();
    this->latency = latency;
    mutex.unlock();
}

qint64 CGlobalData::getLantency(){
    mutex.lock();
    auto latency = this->latency;
    mutex.unlock();
    return latency;
}
