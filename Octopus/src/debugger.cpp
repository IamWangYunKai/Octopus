#include "debugger.h"
#include <QDebug>
#include "parammanager.h"

namespace {
    const int PORT_RECEIVE = 23335;
    const QString BOARDCAST_ADDRESS = "233.233.233.233";
}

Debugger::Debugger(){
    bool ret = setup(PORT_RECEIVE, BOARDCAST_ADDRESS);
    if (ret) start();
    else qDebug() << "Bind Error in CmdReceiver !";
}

void Debugger::parseData(QByteArray receivedData){
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(receivedData, &jsonError);
//    qDebug() << receivedData << jsonError.errorString();
    QJsonObject jsonObject = jsonDoc.object();
    mutex.lock();
    jsonObjects.clear();
    foreach(const QJsonValue &value, jsonObject) {
        QJsonDocument doc = QJsonDocument::fromJson(value.toString().toUtf8());
        QJsonObject obj = doc.object();
        jsonObjects.push_back(obj);
    }
    mutex.unlock();
}

void Debugger::drawAll(QPainter &painter){
    mutex.lock();
    foreach(const QJsonObject &jsonObject, jsonObjects) {
        QString dtype = jsonObject.value("dtype").toString();
        if(dtype == QString("box")){
            double lt_x = jsonObject.value("lt_x").toDouble();
            double lt_y = jsonObject.value("lt_y").toDouble();
            double width = jsonObject.value("width").toDouble();
            double height = jsonObject.value("height").toDouble();
            QString message = jsonObject.value("message").toString();
            QString color = jsonObject.value("color").toString();
            box(painter, QRectF(lt_x, lt_y, width, height), message, Qt::magenta);
        }
        else if(dtype == QString("center_box")){
            qDebug() << "center_box";
        }
        else if(dtype == QString("line")){
            qDebug() << "line";
        }
        else{
            qDebug() << "Unknow debug message type" << dtype;
        }
    }
    mutex.unlock();
}

void Debugger::clearAll(){
    mutex.lock();
    jsonObjects.clear();
    mutex.unlock();
}

void Debugger::line(QPainter &painter, const QLine &line, const QColor &color){
    if(color != Qt::color0){
        painter.setPen(QPen(color, 1));
    }
    else{
        painter.setPen(QPen(Qt::red, 1));
    }
    painter.drawLine(line);
}

void Debugger::line(QPainter &painter, const QPoint &p1, const QPoint &p2, const QColor &color){
    if(color != Qt::color0){
        painter.setPen(QPen(color, 1));
    }
    else{
        painter.setPen(QPen(Qt::red, 1));
    }
    painter.drawLine(p1, p2);
}

void Debugger::rect(QPainter &painter, const QRectF &rect, const QColor &color){
    if(color != Qt::color0){
        painter.setPen(QPen(color, 1));
    }
    else{
        painter.setPen(QPen(Qt::red, 1));
    }
    painter.drawRect(rect);
}

void Debugger::box(QPainter &painter, const QRectF &rect, const QString &message, const QColor &color){
    if(color != Qt::color0){
        painter.setPen(QPen(color, 1));
    }
    else{
        painter.setPen(QPen(Qt::red, 1));
    }
    painter.drawRect(rect);
    QRectF lableRect = QRectF(rect.x(), rect.y()-20, message.size()*11, 20);
    painter.fillRect(lableRect, color);
    painter.setPen(QPen(adaptColor(color), 1));
    painter.drawText(lableRect, Qt::AlignLeft, message);
}

void Debugger::centerBox(QPainter &painter, const QPointF &center, const double &width, const double &height, const QString &message, const QColor &color){
    QRectF rect(center.x()-width/2, center.y()-height/2, width, height);
    box(painter, rect, message, color);
}

QColor Debugger::adaptColor(const QColor &color){
    if(color == Qt::black || color == Qt::red || color == Qt::blue || color == Qt::magenta
            || color == Qt::darkGray || color == Qt::darkRed|| color == Qt::darkGreen || color == Qt::darkBlue
            || color == Qt::darkCyan || color == Qt::darkMagenta || color == Qt::darkYellow)
        return Qt::white;
    else return Qt::black;
}

