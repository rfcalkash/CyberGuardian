#include "noiseprovider.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    NoiseProvider* m_provider = new NoiseProvider();
    engine.rootContext()->setContextProperty("terrain", m_provider);
    engine.addImageProvider(QLatin1String("maps"), m_provider);
    const QUrl url(QStringLiteral("qrc:/CyberGuardian/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
