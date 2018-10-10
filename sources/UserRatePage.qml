import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import "service.js" as Service

Item {
    id: root
    property string title: qsTr("Рейтинг")

    property var userObject

    signal back


    QtObject {
        id: internal

        property var service: new Service.Service(appSettings.vkToken)

        function getUserInfo(query) {
            internal.service.getUserPhotos(query, function(result) {
                console.debug("result:", JSON.stringify(result))
                if(result.success) {
                    var data = result.data/*.response.items*/;
                    console.debug("data:", JSON.stringify(data))
                }
            })
        }
    }

    Pane {
        anchors.fill: parent
        anchors.margins: 20

        Material.elevation: 9

        Pane {
            anchors {
                top: parent.top
                left: parent.left
                margins: 10
            }
            Material.elevation: 3

            Image {
                width: 250
                height: width
                fillMode: Image.PreserveAspectFit
                source: root.userObject.image
                sourceSize: Qt.size(width,height)
            }
        }
    }


    Component.onCompleted: {
        internal.getUserInfo(root.userObject.user_id)
    }

}
