#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QPainter>
#include <QLine>

class Debugger {
public:
    Debugger();
    static void line(QPainter &painter, const QLine &line);
    static void line(QPainter &painter, const QPoint &p1, const QPoint &p2);
};
#endif // DEBUGGER_H
