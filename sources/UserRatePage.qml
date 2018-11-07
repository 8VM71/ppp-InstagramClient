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

        function getUserInfo(userId) {
            internal.service.getUserPhotos(userId, function(result) {
//                console.debug("result:", JSON.stringify(result))
                if(result.success) {
                    var data = result.data;
                    console.debug("getUserPhotos success")
                    var response = data.response;
                    console.debug("photos count = ", response.count)

                    console.debug("items count = ", response.items.length)

                    var likes = response.items.reduce(function(sum, current) {
                        return sum + current.likes.count;
                    }, 0);
                    console.debug("total 100 photos likes = ", likes)
                    var reposts = response.items.reduce(function(sum, current) {
                        return sum + current.reposts.count;
                    }, 0);
                    console.debug("total 100 photos reposts = ", reposts)
                }
            });

            internal.service.getUserPosts(userId, function(result) {
//                console.debug("result:", JSON.stringify(result))
                if(result.success) {
                    var data = result.data;
                    console.debug("getUserPosts success")
                    var response = data.response;
                    console.debug("posts count = ", response.count)

                    console.debug("items count = ", response.items.length)

                    var comments = response.items.reduce(function(sum, current) {
                        return sum + current.comments.count;
                    }, 0);
                    console.debug("total 100 posts comments = ", comments)
                    var likes = response.items.reduce(function(sum, current) {
                        return sum + current.likes.count;
                    }, 0);
                    console.debug("total 100 posts likes = ", likes)
                    var reposts = response.items.reduce(function(sum, current) {
                        return sum + current.reposts.count;
                    }, 0);
                    console.debug("total 100 posts reposts = ", reposts)
                }
            });
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
