#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QPainter>
#include <QMutex>
#include <QJsonObject>
#include <QJsonDocument>
#include "singleton.hpp"
#include "udpreceiver.h"

class Debugger : public UDPReceiver{
public:
    Debugger();
    static void line(QPainter &painter, const QLine &line, const QColor &color=Qt::color0);
    static void line(QPainter &painter, const QPoint &p1, const QPoint &p2, const QColor &color=Qt::color0);
    static void rect(QPainter &painter, const QRectF &rect, const QColor &color=Qt::color0);
    static void box(QPainter &painter, const QRectF &rect, const QString &message=QString(""), const QColor &color=Qt::color0);
    static void centerBox(QPainter &painter, const QPointF &center, const double &width, const double &height, const QString &message=QString(""), const QColor &color=Qt::color0);
    static QColor adaptColor(const QColor &color);
    void drawAll(QPainter &painter);
    void clearAll();
private:
    bool needClear = false;
    bool needDraw = false;
    QMutex mutex;
    virtual void parseData(QByteArray receivedData);
    QVector<QJsonObject> jsonObjects;
};
typedef Singleton<Debugger> DebugEngine;
#endif // DEBUGGER_H
