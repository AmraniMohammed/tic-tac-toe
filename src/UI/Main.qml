import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    visible: true
    width: 1000
    height: 900

    minimumWidth: 800
    minimumHeight: 850

    title: "Tic Tac Toe Game"

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
    }


    StackView {
        id: pagesContainer
        anchors.fill: parent
        initialItem: Qt.resolvedUrl("qrc:/UI/Startup.qml")

        pushEnter: Transition {
            PropertyAnimation {
                property: "x"
                from: pagesContainer.width
                to: 0
                duration: 300
                easing.type: Easing.InOutQuad
            }
        }
        pushExit: Transition {
            PropertyAnimation {
                property: "x"
                from: 0
                to: -pagesContainer.width
                duration: 300
                easing.type: Easing.InOutQuad
            }
        }
        popEnter: Transition {
            PropertyAnimation {
                property: "x"
                from: -pagesContainer.width
                to: 0
                duration: 300
                easing.type: Easing.InOutQuad
            }
        }
        popExit: Transition {
            PropertyAnimation {
                property: "x"
                from: 0
                to: pagesContainer.width
                duration: 300
                easing.type: Easing.InOutQuad
            }
        }

        Component.onCompleted: {
            pagesContainer.push("qrc:/UI/Startup.qml", StackView.PushTransition)
        }
    }
}
