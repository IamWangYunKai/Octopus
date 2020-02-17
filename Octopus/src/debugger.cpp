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

void Debugger::parseData(const QByteArray &receivedData){
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
            QString colorString = jsonObject.value("color").toString();
            QColor color = getColor(colorString);
            box(painter, QRectF(lt_x, lt_y, width, height), message, color);
        }
        else if(dtype == QString("center_box")){
            double ct_x = jsonObject.value("ct_x").toDouble();
            double ct_y = jsonObject.value("ct_y").toDouble();
            double width = jsonObject.value("width").toDouble();
            double height = jsonObject.value("height").toDouble();
            QString message = jsonObject.value("message").toString();
            QString colorString = jsonObject.value("color").toString();
            QColor color = getColor(colorString);
            centerBox(painter, QPointF(ct_x, ct_y), width, height, message, color);
        }
        else if(dtype == QString("line")){
            double s_x = jsonObject.value("s_x").toDouble();
            double s_y = jsonObject.value("s_y").toDouble();
            double e_x = jsonObject.value("e_x").toDouble();
            double e_y = jsonObject.value("e_y").toDouble();
            QString colorString = jsonObject.value("color").toString();
            QColor color = getColor(colorString);
            line(painter, QPointF(s_x, s_y), QPointF(e_x, e_y), color);
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

void Debugger::line(QPainter &painter, const QLineF &line, const QColor &color){
    if(color != Qt::color0){
        painter.setPen(QPen(color, 1));
    }
    else{
        painter.setPen(QPen(Qt::red, 1));
    }
    painter.drawLine(line);
}

void Debugger::line(QPainter &painter, const QPointF &p1, const QPointF &p2, const QColor &color){
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

QColor Debugger::getColor(const QString &colorString){
    if (colorString == QString("black")) return Qt::black;
    else if (colorString == QString("white")) return Qt::white;
    else if (colorString == QString("darkGray")) return Qt::darkGray;
    else if (colorString == QString("gray")) return Qt::gray;
    else if (colorString == QString("lightGray")) return Qt::lightGray;
    else if (colorString == QString("red")) return Qt::red;
    else if (colorString == QString("green")) return Qt::green;
    else if (colorString == QString("blue")) return Qt::blue;
    else if (colorString == QString("cyan")) return Qt::cyan;
    else if (colorString == QString("magenta")) return Qt::magenta;
    else if (colorString == QString("yellow")) return Qt::yellow;
    else if (colorString == QString("darkRed")) return Qt::darkRed;
    else if (colorString == QString("darkGreen")) return Qt::darkGreen;
    else if (colorString == QString("darkBlue")) return Qt::darkBlue;
    else if (colorString == QString("darkCyan")) return Qt::darkCyan;
    else if (colorString == QString("darkMagenta")) return Qt::darkMagenta;
    else if (colorString == QString("darkYellow")) return Qt::darkYellow;
    else return Qt::red;
}
