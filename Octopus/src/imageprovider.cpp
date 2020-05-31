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

ImageProvider::ImageProvider():QQuickImageProvider(QQuickImageProvider::Pixmap), TCPInterface(QString("client:vision"), PORT){
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

void ImageProvider::parseData(){
    QByteArray receivedData = socket->readAll();
    auto length = receivedData.length();
//    qDebug() << "length" << length << receivedData;
    if(length < 30){
        expect_data_len = receivedData.mid(0, 8).toInt();
        timestamp = static_cast<qint64>(receivedData.mid(8).toLongLong());
        mutex.lock();
        image_data.clear();
        mutex.unlock();

        socket->write("OK");
        socket->waitForBytesWritten(100);
    }
    else{
        mutex.lock();
        image_data.append(receivedData);
        mutex.unlock();
//        qDebug() << "left" << expect_data_len;
        expect_data_len -= length;
        if(expect_data_len <= 0){
            mutex.lock();
            image = QImage::fromData(image_data);
            mutex.unlock();

            qint64 current = QDateTime::currentMSecsSinceEpoch();
            qint64 timeBias = GlobalData::instance()->getSyncBias();
            qint64 latency = current - (timeBias + timestamp)/1000;
            GlobalData::instance()->setLatency(latency);
            GlobalData::instance()->countFPS();

            socket->write("OK");
            socket->waitForBytesWritten(100);
        }
    }
}
