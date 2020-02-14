#include "debugger.h"

Debugger::Debugger(){
}

void Debugger::line(QPainter &painter, const QLine &line){
    painter.drawLine(line);
}

void Debugger::line(QPainter &painter, const QPoint &p1, const QPoint &p2){
    painter.drawLine(p1, p2);
}
