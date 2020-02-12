#include "interaction.h"
#include "globaldata.h"

Interaction::Interaction(QObject *parent) : QObject(parent) {
}

int Interaction::getLatency(){
    return GlobalData::instance()->getLatency();
}

void Interaction::setStop(bool stopFlag){
    GlobalData::instance()->setStop(stopFlag);
}

int Interaction::getFPS(){
    return GlobalData::instance()->getFPS();
}


