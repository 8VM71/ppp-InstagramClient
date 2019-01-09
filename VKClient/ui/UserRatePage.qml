import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item {
    id: root
    property string title: qsTr("Рейтинг")

    property var userObject

    signal back

    property var photos: calculator.photosData
    property var posts: calculator.postsData
    property real userRate: calculator.userRate

    QtObject {
        id: internal

        function getUserInfo(userId) {
            calculator.calcRate(userId, appSettings.vkToken)
        }
    }

    Pane {
        anchors.fill: parent
        anchors.margins: 20

        Material.elevation: 9

        Pane {
            id: userPicPane
            anchors {
                top: parent.top
                left: parent.left
                margins: 10
            }
            Material.elevation: 3

            Image {
                width: 250
                height: width
                fillMode: Image.PreserveAspectCrop
                source: root.userObject.image
                sourceSize: Qt.size(width,height)
            }      
        }

        Column {
            id: metricsColumn
            anchors {
                top: parent.top
                left: userPicPane.right
                margins: 10
            }

            spacing: 20

            Text {
                text: "Количество всего фото (TPhc): %1".arg(photos.totalCount)
                font.bold: true
            }
            Text {
                text: "Количество оцениваемых фото (Phc): %1".arg(photos.shownCount)
            }
            Text {
                text: "Количество лайков для оцениваемых фото (Phl): %1".arg(photos.likes)
            }
            Text {
                text: "Количество репостов для оцениваемых фото (Phr): %1".arg(photos.reposts)
            }
            Text {
                text: "Количество всего постов (TPc): %1".arg(posts.totalCount)
                font.bold: true
            }
            Text {
                text: "Количество оцениваемых постов (Pc): %1".arg(posts.shownCount)
            }
            Text {
                text: "Количество лайков для оцениваемых постов (Pl): %1".arg(posts.likes)
            }
            Text {
                text: "Количество комментариев для оцениваемых постов (Pcom): %1".arg(posts.comments)
            }
            Text {
                text: "Количество репостов для оцениваемых постов (Pr): %1".arg(posts.reposts)
            }
        }

        Row {
            id: formulaRow
            anchors {
                top: userPicPane.bottom
                topMargin: 40
                left: parent.left
                leftMargin: 20
            }

            Text {
                anchors {
                    verticalCenter: parent.verticalCenter
                }

                text: "Формула расчета индекса популярности: "
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Image {
                id: formula
                anchors {
                    verticalCenter: parent.verticalCenter
                }
                source: "qrc:/images/formula.svg"
                width: 291 * 1.3
                height: 27 * 1.3
                fillMode: Image.PreserveAspectFit
                sourceSize: Qt.size(width, height)
                antialiasing: true
            }
        }

        Text {
            anchors {
                top: formulaRow.bottom
                left: parent.left
                margins: 20
            }

            text: "Индекс популярности: %1".arg(root.userRate)
        }
    }


    Component.onCompleted: {
        internal.getUserInfo(root.userObject.user_id)
    }

}
