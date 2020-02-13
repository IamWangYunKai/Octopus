#include "interaction.h"
#include "globaldata.h"
#include "cmdreceiver.h"

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

double Interaction::getV(){
    return CommandReceiver::instance()->getV();
}

double Interaction::getW(){
    return CommandReceiver::instance()->getW();
}

