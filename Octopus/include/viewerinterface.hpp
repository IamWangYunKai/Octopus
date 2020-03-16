#ifndef VIEWERINTERFACE_H
#define VIEWERINTERFACE_H

#include <QObject>
#include <QAbstractListModel>
#include "globaldata.h"
#include <cstdlib>
#include "sensorreceiver.h"
#include <QTimer>

class ViewerInterface : public QAbstractListModel{
    Q_OBJECT
public:
    explicit ViewerInterface(QObject *parent = Q_NULLPTR){
        timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(changeRobotInfo()));
        timer->start(17);
    }
    enum Roles {
        robotID = Qt::UserRole + 1,
        robotTeam,
        robotBattery,
        robotCapacitance,
        robotInfrared
    };
    Q_ENUM(Roles)
    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> result = QAbstractListModel::roleNames();
        result.insert(robotID, ("mID"));
        result.insert(robotTeam,("mTeam"));
        result.insert(robotBattery, ("mBattery"));
        result.insert(robotCapacitance, ("mCapacitance"));
        result.insert(robotInfrared, ("mInfrared"));
        return result;
    }
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return 1;
    }
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 5;
    }
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
        if(index.isValid()){
            int team = index.row()%2;
            int id = index.row()/2;
            switch(role){
            case robotID:
                return id;
            case robotTeam:
                return team;
            case robotBattery:
                return SensorInterface::instance()->getV();
            case robotCapacitance:
                return (SensorInterface::instance()->getW()+1)/2;
            case robotInfrared:
                return SensorInterface::instance()->getC();
            }
            return 0;
        }
    }
public slots:
    void changeRobotInfo(){
        emit dataChanged(createIndex(0, 0),createIndex(0, 0));
    }
private:
    QTimer *timer;
};

#endif // VIEWERINTERFACE_H
