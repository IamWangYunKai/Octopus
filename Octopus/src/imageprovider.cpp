#include "imageprovider.h"
#include <QDebug>
#include <QImageReader>
#include <chrono>
#include <thread>
#include <QTime>
#include "parammanager.h"
#include "globaldata.h"
#include <QPainter>
#include "debugger.h"

namespace {
    int width = 1280;
    int height = 720;
    bool isTest = false;
    const int PORT = 10001;
}

ImageProvider::ImageProvider():QQuickImageProvider(QQuickImageProvider::Pixmap), UDPInterface(QString("client:vision"), PORT){
    ParamManager::instance()->loadParam(isTest, "Test/isTest", false);
    ParamManager::instance()->loadParam(width, "Camera/width", 1280);
    ParamManager::instance()->loadParam(height, "Camera/height", 720);

    QPixmap pixmap(width, height);
    pixmap.fill(QColor(255, 255, 255).rgba());
    image = pixmap.toImage().convertToFormat(QImage::Format_RGB32);
}

QPixmap ImageProvider::getDefaultImg(){
    QPixmap pixmap(width, height);
    pixmap.fill(QColor(255, 255, 255).rgba());
    return pixmap;
}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
//    qDebug() << "Get id in qml:" << id ;
//    if (size) *size = QSize(WIDTH, HEIGHT);
//    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : WIDTH,
//                  requestedSize.height() > 0 ? requestedSize.height() : HEIGHT);
//    pixmap.fill(QColor(127, 127, 0).rgba());
    if (GlobalData::instance()->getStop()){
        return this->getDefaultImg();
    }
    else{
        auto pixmap = QPixmap::fromImage(image);
        QPainter painter(&pixmap);
        DebugEngine::instance()->drawAll(painter);
        return pixmap;
    }
}

void ImageProvider::parseData(const QByteArray &receivedData){
    auto package_remain = receivedData.mid(0, 8).toInt();
    auto data_length = receivedData.mid(8, 8).toInt();
    qint64 timestamp = static_cast<qint64>(receivedData.mid(16, 16).toLongLong());
    QByteArray data = receivedData.mid(32);

    // receiving packages, but get wrong package number
    if(expect_package_num > -1 && package_remain != expect_package_num){
        image_data = QByteArray("");// lost package, start over
    }
    expect_package_num = package_remain - 1;

    image_data = image_data.append(data);
//    qDebug() << package_remain << data_length << rx.length();
    if(package_remain == 0){
        // match data length
        if(data_length == image_data.length()){
            qint64 current = QDateTime::currentMSecsSinceEpoch();
            qint64 timeBias = GlobalData::instance()->getSyncBias();
            qint64 latency = current - (timeBias + timestamp)/1000;
            GlobalData::instance()->setLatency(latency);
            GlobalData::instance()->countFPS();
//            qDebug() << "latency:" << latency << "ms";
            mutex.lock();
            image = QImage::fromData(image_data);
            mutex.unlock();
        }
        image_data = QByteArray("");
        expect_package_num = -1;
    }
}
