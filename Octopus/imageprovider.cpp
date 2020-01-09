#include "imageprovider.h"
#include <qDebug>
#include <QImageReader>

namespace {
    const int WIDTH = 640;
    const int HEIGHT = 480;
}

ImageProvider::ImageProvider():QQuickImageProvider(QQuickImageProvider::Pixmap){
}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
    qDebug() << "Get id in qml:" << id ;

   if (size) *size = QSize(WIDTH, HEIGHT);
   QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : WIDTH,
                  requestedSize.height() > 0 ? requestedSize.height() : HEIGHT);
   pixmap.fill(QColor(255, 127, 0).rgba());
   pixmap = test_read();
   return pixmap;
}

QPixmap ImageProvider::test_read(){
    QImageReader reader("test.png");
    QImage img = reader.read();
    if (img.isNull()){
        qDebug() << reader.errorString();
        return nullptr;
    }
    else{
        auto pixmap = QPixmap::fromImage(img);
        return pixmap;
    }

}
