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
            GradientStop { position: 0.0; color: "#3867d6" }
            GradientStop { position: 0.33; color: "#4b7bec" }
            GradientStop { position: 1.0; color: "#45aaf2" }
            orientation : Gradient.Horizontal
        }

        Grid {
            anchors {
                centerIn: parent
            }

            rows: gameManager ? gameManager.getBoardSize() : 3
            columns: gameManager ? gameManager.getBoardSize() : 3
            spacing: 0

            Repeater {
                model: gameManager ? gameManager.getBoardSize() * gameManager.getBoardSize() : 3

                Rectangle {
                    width: 100
                    height: 100

                    color: "transparent"

                    border {
                        color: "black"
                        width: 2
                    }
                    Text {
                        id: squareText
                        font.pixelSize: 50
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

        Rectangle {
            id: backBtn

            anchors {
                bottom: parent.bottom
                left: parent.left
                margins: 10
            }

            width: 70
            height: width/2

            color: "transparent"
            radius: 20

            border {
                color: "black"
                width: 2
            }

            Text {
                id: backBtnText
                text: qsTr("Back")

                font.pixelSize: 15

                anchors {
                    fill: parent
                    margins: 10
                }

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
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
            id: resetBtn

            anchors {
                bottom: parent.bottom
                right: parent.right
                margins: 10
            }

            width: 70
            height: width/2

            color: "transparent"
            radius: 20

            border {
                color: "black"
                width: 2
            }

            Text {
                id: resetBtnText
                text: qsTr("Reset")

                font.pixelSize: 15

                anchors {
                    fill: parent
                    margins: 10
                }

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Reset Board")

                    gameManager.reset()
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
