#include "interaction.h"
#include "globaldata.h"

Interaction::Interaction(QObject *parent) : QObject(parent) {
}

int Interaction::getLantency(){
    return GlobalData::instance()->getLantency();
}

void Interaction::setStop(bool stopFlag){
    GlobalData::instance()->setStop(stopFlag);
}

int Interaction::getFPS(){
    return GlobalData::instance()->getFPS();
}
