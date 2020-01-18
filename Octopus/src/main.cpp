#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include "imageprovider.h"
#include "parammanager.h"
#include "paraminterface.h"
#include "WidgetOSRItem.h"
#include "globaldata.h"
#include "interaction.h"

void initSetup(){
    GlobalData::instance();
    ParamManager::instance();
    qmlRegisterType<Interaction>("BackEndInterface", 1, 0, "Interaction");
    qmlRegisterType<ParamInterface>("BackEndInterface", 1, 0, "ParamModel");
    qmlRegisterType<WidgetOSRItem>("BackEndInterface",1,0, "WidgetOSRItem");
}

int main(int argc, char *argv[]){
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setFont(QFont("Consolas", 14, QFont::Bold));

    initSetup();

    QQmlApplicationEngine engine;

    engine.addImageProvider(QLatin1String("image_provider"), new ImageProvider);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
