#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Board.h"
#include "GameManager.h"
#include "GameManagerWrapper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    Board board;
    GameManager game_manager(board);

    GameManagerWrapper wrapper(&game_manager);
    engine.rootContext()->setContextProperty("gameManager", &wrapper);


    const QUrl url(QStringLiteral("qrc:/UI/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
       engine.load(url);

    return app.exec();
}
