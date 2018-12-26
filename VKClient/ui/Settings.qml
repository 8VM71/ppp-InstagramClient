import QtQuick 2.10
import Qt.labs.settings 1.0

Item {
    id: root
    property string vkToken: ""


    Settings {
        id: auth
        category: "Autorization"
        property alias vkToken: root.vkToken
    }

}
