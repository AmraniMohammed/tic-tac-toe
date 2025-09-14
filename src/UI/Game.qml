import QtQuick
import QtQuick.Controls

Page {
    id: gamePage
    visible: true
    title: qsTr("Tic Tac Toe Game")

    property string gameOverText: ""

    Rectangle {
        width: parent.width
        height: parent.height

        anchors {
            fill: parent
        }

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#374151" }
            GradientStop { position: 0.33; color: "#475569" }
            GradientStop { position: 1.0; color: "#1d4ed8" }
            orientation : Gradient.Horizontal
        }

        Rectangle {
            id: gameContainerBg

            width: gameManager ? ((gameManager.getBoardSize() < 5) ? parent.width * 0.8 : parent.width * 0.95) : parent.width * 0.8
            height: gameManager ? ((gameManager.getBoardSize() < 5) ? parent.height * 0.8 : parent.height * 0.95) : parent.height * 0.8

            color: "#1Affffff"

            anchors {
                centerIn: parent
            }

            border {
                color: "#33c2c2c2"
                width: 2
            }

            radius : 10

            Rectangle {
                id: gridContainer
                width: gridBoard.implicitWidth + 40
                height: gridBoard.implicitHeight + 40

                color: "#1Affffff"

                anchors {
                    centerIn: parent
                }

                border {
                    color: "#33c2c2c2"
                    width: 2
                }

                radius : 10

                Grid {
                    id: gridBoard
                    anchors {
                        centerIn: parent
                    }

                    rows: gameManager ? gameManager.getBoardSize() : 3
                    columns: gameManager ? gameManager.getBoardSize() : 3
                    spacing: 10

                    Repeater {
                        model: gameManager ? gameManager.getBoardSize() * gameManager.getBoardSize() : 3

                        Rectangle {
                            width: gameManager ? ((gameManager.getBoardSize() < 5) ? 90 : 65) : 90
                            height: gameManager ? ((gameManager.getBoardSize() < 5) ? 90 : 65) : 90

                            color: "#1Affffff"

                            border {
                                color: "#33c2c2c2"
                                width: 2
                            }

                            radius : 10

                            Text {
                                id: squareText
                                font.pixelSize: 40
                                font.bold: true

                                color: "white"

                                anchors {
                                    fill: parent
                                    margins: 10
                                }
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter

                                text: gameManager ? gameManager.board_table[index] : ""
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    gameManager.update(index)
                                }
                            }
                        }
                    }
                }

            }

            Rectangle {
                id: backBtn


                width: 150
                height: 50

                anchors {
                    top: parent.top
                    left: parent.left
                    margins: 10
                }

                color: "#1Affffff"

                border {
                    color: "#33c2c2c2"
                    width: 2
                }
                radius: 10

                Row {
                    spacing: 8

                    anchors {
                        centerIn: parent
                    }

                    Image {
                        source: "qrc:/Resources/icons/back.png"
                        width: 24
                        height: 24
                        fillMode: Image.PreserveAspectFit
                    }

                    Text {
                        id: backBtnText
                        text: qsTr("Back")
                        color: "white"

                        font.pixelSize: 15

                        // anchors {
                        //     fill: parent
                        //     margins: 10
                        // }

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Back to main window")
                        gameManager.reset()
                        pagesContainer.pop()
                    }
                }
            }


            Rectangle {
                id: gameModeContainer
                width: 200
                height: 50

                anchors {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    margins: 10
                }

                color: "transparent"


                Row {
                    spacing: 8
                    anchors {
                        centerIn: parent
                    }

                    Image {
                        source: "qrc:/Resources/icons/people.png"
                        width: 24
                        height: 24
                        fillMode: Image.PreserveAspectFit
                    }

                    Text {
                        id: gameModeText
                        text: gameManager ? gameManager.getGame_mode() : "Player vs Player"
                        color: "white"

                        font.pixelSize: 15

                        // anchors {
                        //     fill: parent
                        //     margins: 10
                        // }

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            Rectangle {
                id: resetBtn

                width: 150
                height: 50

                anchors {
                    top: parent.top
                    right: parent.right
                    margins: 10
                }

                color: "#1Affffff"

                border {
                    color: "#33c2c2c2"
                    width: 2
                }
                radius: 10

                Row {
                    spacing: 8

                    anchors {
                        centerIn: parent
                    }

                    Image {
                        source: "qrc:/Resources/icons/restart.png"
                        width: 24
                        height: 24
                        fillMode: Image.PreserveAspectFit
                    }

                    Text {
                        id: resetBtnText
                        text: qsTr("Reset")
                        color: "white"

                        font.pixelSize: 15

                        // anchors {
                        //     fill: parent
                        //     margins: 10
                        // }

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Reset Board")

                        gameManager.reset()
                    }
                }
            }

            Rectangle {
                id: playerAndResult
                anchors {
                    bottom: gridContainer.top
                    horizontalCenter: parent.horizontalCenter
                    bottomMargin: 30
                }

                Row {
                    spacing: 8

                    anchors {
                        centerIn: parent
                    }

                    Image {
                        source: "qrc:/Resources/icons/trophy.png"
                        width: 24
                        height: 24
                        fillMode: Image.PreserveAspectFit
                        visible: (gameManager && ((gameManager.game_state == 3) || (gameManager.game_state == 2))) ? false : true
                    }

                    Text {
                        // text: (gameManager.game_state() == "Continue") ? ("Current player: " + gameManager.getCurrent_player()) : gameManager.game_state()
                        text: gameManager && gameManager.game_state == 3 ? ("Current Player: " + gameManager.getCurrent_player()) : (gameManager.game_state == 2 ? "Draw" : (gameManager.game_state == 1 ? "Player O Wins" : "Player X Wins"))
                        color: "white"

                        font.pixelSize: 15

                        // anchors {
                        //     fill: parent
                        //     margins: 10
                        // }

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }




        }


    }

    Dialog {
        id: gameOverDialog
        title: "Game Over"
        width: 250
        parent: Overlay.overlay

        anchors {
            centerIn: parent
        }

        modal: true
        standardButtons: Dialog.Close

        Label {
            text: gameOverText
            font.pixelSize: 15
        }
    }

    Connections {
        target: gameManager
        function onGameOver(message) {
            gameOverText = message
            gameOverDialog.open()
        }
    }
}
