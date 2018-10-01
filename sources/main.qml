import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import "service.js" as Service

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
        width: window.width * 0.66
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
                    stackView.push("SearchPage.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
//        initialItem: "LoginPage.qml"
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

            }
        }
    }
    Component.onCompleted: {
        var service = new Service.Service()
        service.setToken = appSettings.vkToken
        service.searchUsers("inst", function(reply) {
            console.debug("Success:", reply.success)
            if(reply.success) {
                console.debug("Data:", JSON.stringify(reply.data))
            } else {
                console.debug(reply.errorString)
            }
        })
        service.getUserInfo("117812625", function(reply) {
            console.debug("Success:", reply.success)
            if(reply.success) {
                console.debug("User Data:", JSON.stringify(reply.data))
            } else {
                console.debug(reply.errorString)
            }
        })
        service.getAppPermissions("117812625", function(reply) {
            console.debug("Success:", reply.success)
            if(reply.success) {
                console.debug("App permissions:", JSON.stringify(reply.data))
            } else {
                console.debug(reply.errorString)
            }
        })
        service.getUserPhotos("117812625", function(reply) {
            console.debug("Success:", reply.success)
            if(reply.success) {
                console.debug("User Photos:", JSON.stringify(reply.data))
            } else {
                console.debug(reply.errorString)
            }
        })

    }

}
