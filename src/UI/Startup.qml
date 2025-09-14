import QtQuick 2.15
import QtQuick.Controls

Page {
    id: startupPage
    title: "Tic Tac Toe Game"
    visible: true


    property int board_size_value: 3
    property int ai_depth_value: 10
    property bool is_two_player: true
    property bool is_x: true
    property bool is_easy: true

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
            width: parent.width * 0.55
            height: parent.height * 0.8

            color: "#1Affffff"

            anchors {
                centerIn: parent
            }

            border {
                color: "#66c2c2c2"
                width: 2
            }

            radius : 20

            Column {
                id: container
                width: parent.width
                spacing: 20
                anchors.centerIn: parent

                Column {
                    id: title
                    width: parent.width
                    spacing: 1
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        font.pixelSize: 35
                        font.bold : true
                        anchors {
                            horizontalCenter: parent.horizontalCenter
                        }
                        text: "Tic Tac Toe"
                        color: "white"
                    }

                    Text {
                        font.pixelSize: 12
                        anchors {
                            horizontalCenter: parent.horizontalCenter
                            topMargin: 20
                        }
                        text: "Configure your game settings"
                        color: "white"
                    }
                }

                Column {
                    width: parent.width
                    spacing: 10
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }

                    Row {
                        spacing: 8

                        anchors {
                            left: parent.left
                            leftMargin: 20
                        }

                        Image {
                            source: "qrc:/Resources/icons/setting.png"
                            width: 24
                            height: 24
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            font.pixelSize: 16
                            font.bold : true
                            text: "Game Mode"
                            color: "white"
                        }
                    }



                    Row {
                        width: parent.width
                        spacing: 50
                        anchors {
                            left: parent.left
                            right: parent.right
                            leftMargin: 20
                            rightMargin: 20
                        }

                        Rectangle {
                            width: (parent.width / 2) - 25
                            height: 80
                            color: is_two_player ? "#3b82f6" : "#66ffffff"
                            radius : 10


                            Column {
                                spacing: 8

                                anchors {
                                    centerIn: parent
                                }

                                Image {
                                    source: "qrc:/Resources/icons/people.png"
                                    width: 24
                                    height: 24
                                    fillMode: Image.PreserveAspectFit
                                    anchors {
                                        horizontalCenter: parent.horizontalCenter
                                    }
                                }

                                Text {
                                    font.pixelSize: 14
                                    font.bold : true
                                    text: "Player vs Player"
                                    color: "white"
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    is_two_player = true
                                }
                            }
                        }

                        Rectangle {
                            width: (parent.width / 2) - 25
                            height: 80
                            color: is_two_player ? "#66ffffff" : "#3b82f6"
                            radius : 10

                            Column {
                                spacing: 8

                                anchors {
                                    centerIn: parent
                                }

                                Image {
                                    source: "qrc:/Resources/icons/agents.png"
                                    width: 24
                                    height: 24
                                    fillMode: Image.PreserveAspectFit
                                    anchors {
                                        horizontalCenter: parent.horizontalCenter
                                    }
                                }

                                Text {
                                    font.pixelSize: 14
                                    font.bold : true
                                    text: "Player vs AI"
                                    color: "white"
                                }
                            }



                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    is_two_player = false
                                }
                            }
                        }
                    }

                }

                Column {
                    width: parent.width
                    spacing: 10
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        font.pixelSize: 16
                        font.bold : true
                        anchors {
                            left: parent.left
                            leftMargin: 20
                        }
                        text: "Board Size: " + Math.round(boardSizeSlider.value) + "x" + Math.round(boardSizeSlider.value)
                        color: "white"
                    }

                    Slider {
                        id: boardSizeSlider
                        width: parent.width * 0.8
                        from: 3
                        to: 8
                        value: 3
                        stepSize: 1
                        anchors.horizontalCenter: parent.horizontalCenter

                        onValueChanged:
                        {
                            // console.log("Slider Value : " , value);
                            board_size_value = value
                        }

                        background: Rectangle {
                                x: boardSizeSlider.leftPadding
                                y: boardSizeSlider.topPadding + boardSizeSlider.availableHeight / 2 - height / 2
                                implicitWidth: 200
                                implicitHeight: 4
                                width: boardSizeSlider.availableWidth
                                height: implicitHeight
                                radius: 2
                                color: "#bdbebf"

                                Rectangle {
                                    width: boardSizeSlider.visualPosition * parent.width
                                    height: parent.height
                                    color: "#989a9c"
                                    radius: 2
                                }
                            }

                            handle: Rectangle {
                                x: boardSizeSlider.leftPadding + boardSizeSlider.visualPosition * (boardSizeSlider.availableWidth - width)
                                y: boardSizeSlider.topPadding + boardSizeSlider.availableHeight / 2 - height / 2
                                implicitWidth: 20
                                implicitHeight: 20
                                radius: 13
                                color: boardSizeSlider.pressed ? "#989a9c" : "#989a9c"
                                border.color: "#989a9c"
                            }
                    }

                }

                Column {
                    width: parent.width
                    spacing: 10
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        font.pixelSize: 16
                        font.bold : true
                        anchors {
                            left: parent.left
                            leftMargin: 20
                        }
                        text: "Starting Player"
                        color: "white"
                    }

                    Row {
                        width: parent.width
                        spacing: 50
                        anchors {
                            left: parent.left
                            right: parent.right
                            leftMargin: 20
                            rightMargin: 20
                        }

                        Rectangle {
                            width: (parent.width / 2) - 25
                            height: 60
                            color: is_x? "#3b82f6" : "#66ffffff"
                            radius : 10

                            Text {
                                font.pixelSize: 14
                                font.bold : true
                                anchors {
                                    centerIn: parent
                                }
                                text: "X"
                                color: "white"
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    is_x = true
                                }
                            }
                        }

                        Rectangle {
                            width: (parent.width / 2) - 25
                            height: 60
                            color: is_x? "#66ffffff" : "#3b82f6"
                            radius : 10

                            Text {
                                font.pixelSize: 14
                                font.bold : true
                                anchors {
                                    centerIn: parent
                                }
                                text: "O"
                                color: "white"
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    is_x = false
                                }
                            }
                        }
                    }

                }

                Column {
                    id: difficultySection
                    width: parent.width
                    spacing: 10
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }
                    visible: !(is_two_player)

                    Text {
                        font.pixelSize: 16
                        font.bold : true
                        anchors {
                            left: parent.left
                            leftMargin: 20
                        }
                        text: "AI Difficulty"
                        color: "white"
                    }

                    Row {
                        width: parent.width
                        spacing: 50
                        anchors {
                            left: parent.left
                            right: parent.right
                            leftMargin: 20
                            rightMargin: 20
                        }

                        Rectangle {
                            width: (parent.width / 2) - 25
                            height: 60
                            color: is_easy? "#3b82f6" : "#66ffffff"
                            radius : 10

                            Text {
                                font.pixelSize: 14
                                font.bold : true
                                anchors {
                                    centerIn: parent
                                }
                                text: "Easy"
                                color: "white"
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    is_easy = true
                                }
                            }
                        }

                        Rectangle {
                            width: (parent.width / 2) - 25
                            height: 60
                            color: is_easy? "#66ffffff" : "#3b82f6"
                            radius : 10

                            Text {
                                font.pixelSize: 14
                                font.bold : true
                                anchors {
                                    centerIn: parent
                                }
                                text: "Hard"
                                color: "white"
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    is_easy = false
                                }
                            }
                        }
                    }

                }

                Column {
                    width: parent.width
                    spacing: 10
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }
                    visible: !(is_two_player)

                    Text {
                        font.pixelSize: 16
                        font.bold : true
                        anchors {
                            left: parent.left
                            leftMargin: 20
                        }
                        text: "AI Search Depth: " + Math.round(aiDepthSlider.value)
                        color: "white"
                    }

                    Slider {
                        id: aiDepthSlider
                        width: parent.width * 0.8
                        from: 5
                        to: 50
                        value: 10
                        stepSize: 1
                        anchors.horizontalCenter: parent.horizontalCenter

                        onValueChanged:
                        {
                            ai_depth_value = value
                        }

                        background: Rectangle {
                                x: aiDepthSlider.leftPadding
                                y: aiDepthSlider.topPadding + aiDepthSlider.availableHeight / 2 - height / 2
                                implicitWidth: 200
                                implicitHeight: 4
                                width: aiDepthSlider.availableWidth
                                height: implicitHeight
                                radius: 2
                                color: "#bdbebf"

                                Rectangle {
                                    width: aiDepthSlider.visualPosition * parent.width
                                    height: parent.height
                                    color: "#989a9c"
                                    radius: 2
                                }
                            }

                            handle: Rectangle {
                                x: aiDepthSlider.leftPadding + aiDepthSlider.visualPosition * (aiDepthSlider.availableWidth - width)
                                y: aiDepthSlider.topPadding + aiDepthSlider.availableHeight / 2 - height / 2
                                implicitWidth: 20
                                implicitHeight: 20
                                radius: 13
                                color: aiDepthSlider.pressed ? "#989a9c" : "#989a9c"
                                border.color: "#989a9c"
                            }
                    }

                }

                Rectangle {
                    width: parent.width * 0.8
                    height: 60
                    color: hovered ? "#E63b82f6" : "#3b82f6"
                    radius : 10

                    property bool hovered: false

                    anchors {
                        left: parent.left
                        right: parent.right
                        leftMargin: 20
                        rightMargin: 20
                    }

                    Row {
                        spacing: 8

                        anchors {
                            centerIn: parent
                        }

                        Image {
                            source: "qrc:/Resources/icons/play-button.png"
                            width: 24
                            height: 24
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            font.pixelSize: 14
                            font.bold : true
                            // anchors {
                            //     centerIn: parent
                            // }
                            text: "Start Game"
                            color: "white"
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor

                        onEntered: parent.hovered = true
                        onExited: parent.hovered = false
                        onClicked: {
                            gameManager.setup(board_size_value, ai_depth_value, is_two_player, is_x, is_easy)

                            pagesContainer.push("qrc:/UI/Game.qml", StackView.PushTransition)
                        }
                    }
                }
            }



        }
    }
}
