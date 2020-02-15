#include "debugger.h"

Debugger::Debugger(){
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
