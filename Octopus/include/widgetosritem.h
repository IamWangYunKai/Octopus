#ifndef WIDGETOSRITEM_H
#define WIDGETOSRITEM_H

#include <QQuickPaintedItem>

class WidgetOSRItem : public QQuickPaintedItem{
    Q_OBJECT
    Q_PROPERTY(QVariant osrWidget WRITE setOSRWidget)
public:
    WidgetOSRItem();

    void setOSRWidget(QVariant w);

    virtual void paint(QPainter *painter) override;

protected:
    virtual bool eventFilter(QObject* obj, QEvent* e) override;
    virtual void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry) override;

    virtual void	hoverEnterEvent(QHoverEvent * e) override;
    virtual void	hoverLeaveEvent(QHoverEvent * e) override;
    virtual void	hoverMoveEvent(QHoverEvent * e) override;
    virtual bool    event(QEvent *e) override;

private:
    QWidget* mOSRWidget;
};

#endif // WIDGETOSRITEM_H
