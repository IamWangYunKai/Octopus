#include "imageprovider.h"
#include <qDebug>
#include <QImageReader>
#include <chrono>
#include <thread>

namespace {
    const int WIDTH = 640;
    const int HEIGHT = 480;
    const int PORT_RECEIVE = 23333;
    const QString BOARDCAST_ADDRESS = "233.233.233.233";
    std::thread* receiveThread = nullptr;
    QHostAddress address;
}

ImageProvider::ImageProvider():QQuickImageProvider(QQuickImageProvider::Pixmap){
//    if(receiveSocket.bind(QHostAddress::AnyIPv4, PORT_RECEIVE, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)
//            && receiveSocket.joinMulticastGroup(QHostAddress(BOARDCAST_ADDRESS))) {
//        qDebug() << "****** start receive ! ******";
//        receiveThread = new std::thread([ = ] {readData();});
//        receiveThread->detach();
//    }
//    else {
//        qDebug() << "Bind Error in action module !";
//    }
    auto res = receiveSocket.bind(QHostAddress::AnyIPv4, PORT_RECEIVE, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    auto res2 = receiveSocket.joinMulticastGroup(QHostAddress(BOARDCAST_ADDRESS));
    qDebug() << res << res2;
    receiveThread = new std::thread([ = ] {readData();});
    receiveThread->detach();
}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
//    qDebug() << "Get id in qml:" << id ;
//    if (size) *size = QSize(WIDTH, HEIGHT);
//    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : WIDTH,
//                  requestedSize.height() > 0 ? requestedSize.height() : HEIGHT);
//    pixmap.fill(QColor(127, 127, 0).rgba());
    auto pixmap = QPixmap::fromImage(image);
    return pixmap;
}

void ImageProvider::readData(){
    while(true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        while (receiveSocket.state() == QUdpSocket::BoundState && receiveSocket.hasPendingDatagrams()) {
            rx.resize(receiveSocket.pendingDatagramSize());
            receiveSocket.readDatagram(rx.data(), rx.size(), &address);
            image = QImage::fromData(rx);
        }
    }
}
