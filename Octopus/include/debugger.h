#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QPainter>

class Debugger {
public:
    Debugger();
    static void line(QPainter &painter, const QLine &line, const QColor &color=Qt::color0);
    static void line(QPainter &painter, const QPoint &p1, const QPoint &p2, const QColor &color=Qt::color0);
    static void rect(QPainter &painter, const QRectF &rect, const QColor &color=Qt::color0);
    static void box(QPainter &painter, const QRectF &rect, const QString &message=QString(""), const QColor &color=Qt::color0);
    static void centerBox(QPainter &painter, const QPointF &center, const double &width, const double &height, const QString &message=QString(""), const QColor &color=Qt::color0);
    static QColor adaptColor(const QColor &color);
};
#endif // DEBUGGER_H
