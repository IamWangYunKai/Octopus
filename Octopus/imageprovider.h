#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QUdpSocket>

class ImageProvider : public QQuickImageProvider{
public:
    ImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
    QPixmap test_read();
    void readData();
private:
    QByteArray rx;
    QUdpSocket receiveSocket;
};

#endif // IMAGEPROVIDER_H
