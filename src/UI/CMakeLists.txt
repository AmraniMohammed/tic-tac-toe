
# add_executable(appTicTacToe UI/Main.qml)

qt_add_qml_module(UIModule
    URI TicTacToe
    VERSION 1.0
    QML_FILES Game.qml Startup.qml
    QML_FILES
    QML_FILES Main.qml
)
