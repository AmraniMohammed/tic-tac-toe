#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include "Board.h"
#include "GameManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Board* board = new Board();

    GameManager wrapper(board);
    engine.rootContext()->setContextProperty("gameManager", &wrapper);

    // GameManager* wrapper = new GameManager(board);
    // qmlRegisterSingletonInstance("Game", 1, 0, "GameManager", wrapper);

    app.setWindowIcon(QIcon(":/Resources/icons/game_icon.png"));


    const QUrl url(QStringLiteral("qrc:/UI/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
       engine.load(url);

    return app.exec();
   delete board;
   board = NULL;
}
