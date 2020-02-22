#include "interaction.h"
#include "globaldata.h"
#include "cmdreceiver.h"
#include "clocsync.h"

Interaction::Interaction(QObject *parent) : QObject(parent) {
}

int Interaction::getLatency(){
    return GlobalData::instance()->getLatency();
}

void Interaction::setStop(const bool &stopFlag){
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

void Interaction::syncCloc(const int &n){
    SyncCloc::instance()->sendPackage(n);
}
