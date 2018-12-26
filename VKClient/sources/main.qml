import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 750
    height: 600
    title: Application.name

    property Scale uiScale: Scale {
        xScale: window.width / 800
        yScale: window.height / 800
    }

    Material.theme: Material.Light
    Material.accent: Material.Purple

    Settings {
        id: appSettings
    }

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
        width: window.width * 0.30
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Авторизация")
                width: parent.width
                onClicked: {
                    stackView.push(loginPage)
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Поиск")
                width: parent.width
                onClicked: {
                    stackView.push(searchPage)
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Рейтинг")
                width: parent.width
                onClicked: {
                    stackView.push(ratePage)
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: searchPage
        anchors.fill: parent
    }


    Component {
        id: loginPage
        LoginPage {
            logined: appSettings.vkToken != ""
            onNext: {
                console.debug("Push search page")
                stackView.push(searchPage)
            }
        }
    }

    Component {
        id: searchPage
        SearchPage {
            onNext: {
                console.debug("Push rate page")
                stackView.push(ratePage, {userObject : user})
            }
        }
    }

    Component {
        id: ratePage
        UserRatePage {

        }
    }
    Component.onCompleted: {
        sender.start();
    }

}
