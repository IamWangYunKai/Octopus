#include "widgetosritem.h"
#include <QWidget>
#include <QPainter>
#include <QDebug>

WidgetOSRItem::WidgetOSRItem()
    :mOSRWidget(0){
    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);
    setFlag(ItemIsFocusScope, true);
    setFlag(ItemHasContents, true);
}

void WidgetOSRItem::setOSRWidget(QVariant w){
    mOSRWidget = w.value<QWidget*>();
    if(mOSRWidget){
        mOSRWidget->installEventFilter(this);
        this->update();
    }
}

void WidgetOSRItem::paint(QPainter *painter){
    painter->save();
    if(mOSRWidget == NULL){
        painter->drawText(this->boundingRect(), Qt::AlignCenter, "Hello World !");
        QPainterPath path;
        path.moveTo(200+20*5, 80*5);
        path.lineTo(200+20*5, 30*5);
        path.cubicTo(200+80*5, 0, 200+50*5, 50*5, 200+80*5, 80*5);
        painter->drawPath(path);
    }
    else{
        mOSRWidget->render(painter);
    }

    painter->restore();
}

bool WidgetOSRItem::eventFilter(QObject *obj, QEvent *e){
    bool res = QQuickPaintedItem::eventFilter(obj, e);
    if(obj == mOSRWidget){
        switch(e->type()){
        case QEvent::Paint:{
            this->update();
        }
            break;
        }
    }
    return res;
}

void WidgetOSRItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry){
    QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);

    if(mOSRWidget){
        mOSRWidget->setGeometry(newGeometry.toRect());
    }
}

void WidgetOSRItem::hoverEnterEvent(QHoverEvent *e){
   if(!mOSRWidget)
       return;
   QEnterEvent enterEvent(e->posF(), mapToScene(e->posF()), QCursor::pos());
   qApp->sendEvent(mOSRWidget, &enterEvent);
}

void WidgetOSRItem::hoverLeaveEvent(QHoverEvent *e){
    if(!mOSRWidget)
        return;
    qApp->sendEvent(mOSRWidget, e);
}

void WidgetOSRItem::hoverMoveEvent(QHoverEvent *e){
    if(!mOSRWidget)
        return;
    QMouseEvent me(QEvent::MouseMove, e->posF(), mapToScene(e->posF()), QCursor::pos(), Qt::NoButton, Qt::NoButton, 0);
    qApp->sendEvent(mOSRWidget, &me);
}

bool WidgetOSRItem::event(QEvent *e){
    if(!mOSRWidget){
        e->ignore();
        return false;
    }

    switch(e->type()){
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
    case QEvent::HoverMove:{
        return QQuickPaintedItem::event(e);
    }
        break;
    default:
        return qApp->sendEvent(mOSRWidget, e);
    }
}
