#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "imageprovider.h"


int main(int argc, char *argv[]){
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.addImageProvider(QLatin1String("image_provider"), new ImageProvider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
