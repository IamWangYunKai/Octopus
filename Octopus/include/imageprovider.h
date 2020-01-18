#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QUdpSocket>
#include <QMutex>

class ImageProvider : public QQuickImageProvider{
public:
    ImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
    void readData();
    QPixmap getDefaultImg();

private:
    QImage image;
    QByteArray image_data;
    int expect_package_num = -1;
    QMutex mutex;
    QUdpSocket receiveSocket;
};

#endif // IMAGEPROVIDER_H
