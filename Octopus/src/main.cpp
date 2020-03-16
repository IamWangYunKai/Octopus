#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include "imageprovider.h"
#include "parammanager.h"
#include "paraminterface.h"
#include "globaldata.h"
#include "interaction.h"
#include "viewerinterface.hpp"
#include "sensorreceiver.h"
#include "cmdsender.h"
#include "debugger.h"
#include "clocsync.h"

namespace  {
    void initSetup(){
        GlobalData::instance();
        ParamManager::instance();
        SensorInterface::instance();
        CommandSender::instance();
        DebugEngine::instance();
        SyncCloc::instance();
        qmlRegisterType<Interaction>("BackEndInterface", 1, 0, "Interaction");
        qmlRegisterType<ParamInterface>("BackEndInterface", 1, 0, "ParamModel");
        qmlRegisterType<ViewerInterface>("BackEndInterface", 1, 0, "ViewerInterface");
    }
}

int main(int argc, char *argv[]){
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setFont(QFont("Consolas", 14, QFont::Bold));

    initSetup();

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("image_provider"), new ImageProvider);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
