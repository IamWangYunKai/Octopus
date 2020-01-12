#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include "imageprovider.h"
#include "parammanager.h"
#include "paraminterface.h"

int main(int argc, char *argv[]){
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ParamInterface>("BackEndInterface", 1, 0, "ParamModel");
    app.setFont(QFont("Consolas", 14, QFont::Bold));

    QQmlApplicationEngine engine;

    engine.addImageProvider(QLatin1String("image_provider"), new ImageProvider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
