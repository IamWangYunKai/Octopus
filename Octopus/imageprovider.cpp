#include "imageprovider.h"
#include <qDebug>
#include <QImageReader>
#include <chrono>
#include <thread>

namespace {
    const int WIDTH = 640;
    const int HEIGHT = 480;
    const int PORT_RECEIVE = 8080;
    std::thread* receiveThread = nullptr;
}

ImageProvider::ImageProvider():QQuickImageProvider(QQuickImageProvider::Pixmap){
    if(receiveSocket.bind(QHostAddress::AnyIPv4, PORT_RECEIVE, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qDebug() << "****** start receive ! ******";
        receiveThread = new std::thread([ = ] {readData();});
        receiveThread->detach();
    } else {
        qDebug() << "Bind Error in action module !";
    }
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

void ImageProvider::readData(){
    static QHostAddress address;
    static bool first = true;
    while(true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        while (receiveSocket.state() == QUdpSocket::BoundState && receiveSocket.hasPendingDatagrams()) {
            qDebug() << "receive data !!!";
            rx.resize(receiveSocket.pendingDatagramSize());
            receiveSocket.readDatagram(rx.data(), rx.size(), &address);
            auto img = QImage::fromData(rx);
            qDebug() << img.width() << img.height();
            if(first){
                img.save("save.png");
                first = false;
            }
        }
    }
}
