#include "interaction.h"
#include "globaldata.h"
#include "cmdreceiver.h"
#include "cmdsender.h"
#include "clocsync.h"
#include <cmath>

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

void Interaction::vel(double x, double y){
    double v = - sin(atan2(y, x)); //y-axis facing down
    CommandSender::instance()->setV(v);
}

void Interaction::dir(double x, double y){
    double w = cos(atan2(y, x));
    CommandSender::instance()->setW(w);
}

void Interaction::setBrake(double brake){
    CommandSender::instance()->setBrake(brake);
}

void Interaction::sendCmd(){
    CommandSender::instance()->sendCmd();
}

void Interaction::setGear(int gear){
    CommandSender::instance()->setGear(gear);
}

void Interaction::setHandBrake(bool handbrake){
    CommandSender::instance()->setHandBrake(handbrake);
}
