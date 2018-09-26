import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 800
    title: Application.name

    property Scale uiScale: Scale {
        xScale: window.width / 800
        yScale: window.height / 800
    }

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Авторизация")
                width: parent.width
                onClicked: {
                    stackView.push("LoginPage.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Поиск")
                width: parent.width
                onClicked: {
                    stackView.push("SearchPage.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "LoginPage.qml"
        anchors.fill: parent
    }
}
