#ifndef INTERACTION_H
#define INTERACTION_H

#include <QObject>
#include <QMutex>

class Interaction : public QObject {
    Q_OBJECT
public:
    explicit Interaction(QObject *parent = nullptr);
    Q_INVOKABLE int getLatency();
    Q_INVOKABLE void setStop(const bool &stopFlag);
    Q_INVOKABLE int getFPS();
    Q_INVOKABLE double getV();
    Q_INVOKABLE double getW();
    Q_INVOKABLE void syncCloc(const int &n);
private:
    QMutex mutex;
};

#endif // INTERACTION_H
