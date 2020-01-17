#include "imageprovider.h"
#include <qDebug>
#include <QImageReader>
#include <chrono>
#include <thread>
#include <QTime>
#include "parammanager.h"

namespace {
//    const int WIDTH = 640;
//    const int HEIGHT = 480;
    const int PORT_RECEIVE = 23333;
    const QString BOARDCAST_ADDRESS = "233.233.233.233";
    std::thread* receiveThread = nullptr;
    QHostAddress address;
    bool isTest = false;
}

ImageProvider::ImageProvider():QQuickImageProvider(QQuickImageProvider::Pixmap){
    if(receiveSocket.bind(QHostAddress::AnyIPv4, PORT_RECEIVE, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)
            && receiveSocket.joinMulticastGroup(QHostAddress(BOARDCAST_ADDRESS))) {
        qDebug() << "****** start receive ! ******";
        receiveThread = new std::thread([ = ] {readData();});
        receiveThread->detach();
    }
    else {
        qDebug() << "Bind Error in action module !";
    }
    Global::ZParamManager::instance()->loadParam(isTest, "Test/isTest", false);
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
            QByteArray receive_data;
            receive_data.resize(receiveSocket.pendingDatagramSize());
            receiveSocket.readDatagram(receive_data.data(), receive_data.size(), &address);

            auto package_remain = receive_data.mid(0, 8).toInt();
            auto data_length = receive_data.mid(8, 8).toInt();
            qint64 timestamp = static_cast<qint64>(receive_data.mid(16, 16).toLongLong());
            QByteArray data = receive_data.mid(32);

            // receiving packages, but get wrong package number
            if(expect_package_num > -1 && package_remain != expect_package_num){
                image_data = QByteArray("");// lost package, start over
            }
            expect_package_num = package_remain - 1;

            image_data = image_data.append(data);
//            qDebug() << package_remain << data_length << rx.length();
            if(package_remain == 0){
                // match data length
                if(data_length == image_data.length()){
                    qint64 current = QDateTime::currentMSecsSinceEpoch();
                    qint64 latency = current - timestamp/1000;
//                    qDebug() << "latency:" << latency << "ms";
                    mutex.lock();
                    image = QImage::fromData(image_data);
                    mutex.unlock();
                }
                image_data = QByteArray("");
                expect_package_num = -1;
            }
        }
    }
}
