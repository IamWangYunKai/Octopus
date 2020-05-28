#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QUdpSocket>
#include <QMutex>
#include "tcpinterface.h"

class ImageProvider : public QQuickImageProvider, public TCPInterface{
public:
    ImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
    QPixmap getDefaultImg();

private:
    virtual void parseData(const QByteArray &receivedData);
    QImage image;
    QByteArray image_data;
    int expect_package_num = -1;
    QMutex mutex;
};

#endif // IMAGEPROVIDER_H
