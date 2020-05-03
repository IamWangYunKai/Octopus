#include "utils.h"
#include <QJsonObject>
#include <QJsonDocument>

QByteArray toMessage(QString data, QString robot_id, QString mtype, int pri){
    QJsonObject object;
    object.insert("Mtype",mtype);
    object.insert("Pri",pri);
    object.insert("Id",robot_id);
    object.insert("Data",data);
    QJsonDocument doc;
    doc.setObject(object);
    QByteArray bytes = doc.toJson(QJsonDocument::Compact);
    return bytes;
}
