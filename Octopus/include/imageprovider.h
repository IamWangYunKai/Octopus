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
    virtual void parseData();
    QImage image;
    QByteArray image_data;
    int expect_data_len = 0;
    QMutex mutex;
    qint64 timestamp;
};

#endif // IMAGEPROVIDER_H
