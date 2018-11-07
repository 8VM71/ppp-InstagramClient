import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import "service.js" as Service

Item {
    id: root
    property string title: qsTr("Поиск")

    signal next(var user)
    signal back


    QtObject {
        id: internal

        property var service: new Service.Service(appSettings.vkToken)

        function search(query) {
            internal.service.searchUsers(query, function(result) {
                if(result.success) {
                    resultsModel.clear();

                    var data = result.data.response.items;
                    //console.debug("data:", JSON.stringify(data))
                    for(var i in data) {
                        var item = data[i]
                        resultsModel.append({
                                                user_id: item.id,
                                                last_name: item.last_name,
                                                first_name: item.first_name,
                                                image: item.photo_big,
                                                followers: item.followers_count
                                            })
                    }
                }
            })
        }
    }

    ListView {
        id: searchResultsView

        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            topMargin: 10
            bottom: parent.bottom
        }

        model: ListModel {
            id: resultsModel
        }
        header: Item {
            height: 80
            width: parent.width

            Pane {
                width: parent.width
                height: 60
                Material.elevation: 5
                TextField {
                    id: inputTextField
                    width: parent.width

                    onTextChanged: {
                        internal.search(text)
                    }
                }
            }
        }

        spacing: 10

        width: 700

        delegate: Pane {
            width: parent.width
            height: 80

            Material.elevation: 5

            Image {
                id: imageItem
                anchors {
                    top: parent.top
                    left: parent.left
                }

                width: parent.height
                height: width

                fillMode: Image.PreserveAspectFit

                sourceSize: Qt.size(width, height)

                source: model.image
                asynchronous: true
            }

            Column {
                anchors {
                    left: imageItem.right
                    leftMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                spacing: 15

                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: model.first_name + " " + model.last_name
                }

                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: model.followers
                }

            }

            Button {
                anchors {
                    right: parent.right
                    rightMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                text: "Выбрать"
                onClicked: {
                    console.debug("onClicked",model.user_id)
                    var user = {
                        user_id: model.user_id.toString(),
                        last_name: model.last_name.toString(),
                        first_name: model.first_name.toString(),
                        image: model.image.toString(),
                        followers: model.followers.toString()
                    }
                    root.next(user)
                }
            }
        }
    }

    Component.onCompleted: {
    }

}
