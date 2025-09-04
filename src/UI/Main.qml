import QtQuick

Window {
    id: root
    width: 640
    height: 640
    visible: true
    title: qsTr("Tic Tac Toe Game")

    property int board_size: 3
    property bool isPlayerX: true

    Grid {
        anchors {
            centerIn: parent
        }

        rows: root.board_size
        columns: root.board_size
        spacing: 0

        Repeater {
            model: root.board_size * root.board_size

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
                        console.log("clicked in rectangle index : ", index)
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
            }
        }
    }

}
