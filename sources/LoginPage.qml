import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item {
    id: root

    property Scale uiScale: Scale {}

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
                "url_regexp": "^https://(www\\.)*instagram\\.com/(oauth|accounts/login|integrity/checkpoint/|challenge).+",
                        "finish_regexp": "^https://client\\.loc/admin/instagram/redirect.+",
                        "url": "https://instagram.com/oauth/authorize",
                        "logout_url": "https://instagram.com/accounts/logout",
                        "params": {
                    "client_id": "89f5ac8066054a15ac7cc50e701b2803",
                    "response_type": "token",
                    "redirect_uri": "https://client.loc/admin/instagram/redirect"
                }
            }
        }
    }

}
