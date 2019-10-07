#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include "basereader.h"
#include "clientclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QTranslator translator;
    auto s =translator.load(":/locale/taskbase_" + QLocale::system().name());
    app.installTranslator(&translator);

    QQmlApplicationEngine engine;
    //if (argc > 1)
    {
        //if (QString(argv[1]) == "--server") //запускаем сервер
        {
            const QUrl url(QStringLiteral("qrc:/qml/serverSetup.qml"));
            QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                             &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
            qmlRegisterType<BaseReader>("com.taskdb.server", 1, 0, "BaseReader");
            engine.load(url);

           // return app.exec();
        }
    } //иначе запускаем клиентскую прграмму
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qmlRegisterType<ClientClass>("com.taskdb.client", 1, 0, "ClientInterface");
    engine.load(url);

    return app.exec();
}
