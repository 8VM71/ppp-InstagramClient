import QtQuick 2.0

import "service.js" as Service

Item {
    property string title: qsTr("Поиск")

    signal next
    signal back


    Component.onCompleted: {
        var service = new Service.Service()
        service.setToken(appSettings.vkToken)
//        service.searchUsers("inst", function(reply) {
//            console.debug("Success:", reply.success)
//            if(reply.success) {
//                console.debug("Data:", JSON.stringify(reply.data))
//            } else {
//                console.debug(reply.errorString)
//            }
//        })
//        service.getUserInfo("117812625", function(reply) {
//            console.debug("Success:", reply.success)
//            if(reply.success) {
//                console.debug("User Data:", JSON.stringify(reply.data))
//            } else {
//                console.debug(reply.errorString)
//            }
//        })
//        service.getAppPermissions("117812625", function(reply) {
//            console.debug("Success:", reply.success)
//            if(reply.success) {
//                console.debug("App permissions:", JSON.stringify(reply.data))
//            } else {
//                console.debug(reply.errorString)
//            }
//        })
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
