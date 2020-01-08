#include "imageprovider.h"
#include <qDebug>

namespace {
    const int width = 600;
    const int height = 400;
}

ImageProvider::ImageProvider():QQuickImageProvider(QQuickImageProvider::Pixmap){
}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
    qDebug() << "get id in qml:" << id ;

   if (size) *size = QSize(width, height);
   QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                  requestedSize.height() > 0 ? requestedSize.height() : height);
   pixmap.fill(QColor(255, 127, 0).rgba());
   return pixmap;
}
