import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item {
    id: root

    property Scale uiScale: Scale {}
    property string title: qsTr("Авторизация")

    signal next

    Pane {
        Material.elevation: 6

        anchors.centerIn: parent

        width: parent.width - 60 * root.uiScale.xScale
        height: parent.height - 60 * root.uiScale.yScale

        LoginDialog {
            anchors.fill: parent
            uiScale: root.uiScale

            serviceInfo: {
                    "url_regexp": "^https://(oauth|login)\\.vk\\.com/.+",
                    "finish_regexp": "^https://oauth\\.vk\\.com/blank/\\.html.+",
                    "url": "https://oauth.vk.com/authorize",
                    "logout_url": "https://login.vk.com/?act=logout&hash=9e6b7189913e10fd8f&_origin=https://vk.com",
                    "params": {
                        "client_id": "6703476",
                        "response_type": "token",
                        "redirect_uri": "https://oauth.vk.com/blank.html",
                        "scope": "offline,photos",
                        "v": "5.52",
                        "display": "page",
                }
            }
        }
    }

}
