import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5

import "utils.js" as Utils

Item {
    id: root

    property Scale uiScale: Scale {}
    property var serviceInfo: ({})
    property bool logined: false

    signal autorized(var token)

    function updateLogin(logined, token) {
        root.logined = logined;
        if(token)
            root.autorized(token);
    }

    QtObject {
        id: internal
        property string loginURL: root.serviceInfo != undefined ? Utils.combineUrl(root.serviceInfo.url, root.serviceInfo.params) : ""
        property string logoutURL: root.serviceInfo != undefined ? root.serviceInfo.logoutUrl : ""

        function testWhiteList(urlString) {
            var urlRegExp = new RegExp(root.serviceInfo.allowedURLRegexp);
            var finishRegExp = new RegExp(root.serviceInfo.loginCompleteRegexp);

            if (urlRegExp.test(urlString) || finishRegExp.test(urlString)) {
                return true;
            } else {
                return false;
            }
        }

//        function getFullLoginUrl() {
//            var url = root.serviceInfo.url + '?'
//            var params = root.serviceInfo.params
//            for (var param in params) {
//                url += '&%1=%2'.arg(param).arg(params[param])
//            }
//            console.debug(url)
//            return url
//        }

        function testLoginFinished(urlString) {
            var finishRegExp = new RegExp(root.serviceInfo.loginCompleteRegexp);
            return finishRegExp.test(urlString);
        }

        function parseParams(url) {
            if (typeof url !== 'string') {
                return null
            }

            var result = {}
            var queries = url.replace(/[?#]/g, '&').replace(/^[^&]*?&/, '').replace(/[+]/g, '%20').split(/[&;]/)
            for (var i = 0; i < queries.length; i++) {
                var params = queries[i].split('=')
                result[decodeURIComponent(params[0])] = decodeURIComponent(params[1])
            }

            return result
        }
    }

    Label {
        id: titleText
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            topMargin: 10 * root.uiScale.yScale
        }

        width: parent.width
        height: 100 * root.uiScale.yScale

        font {
            //family: root.uiStyle.font.boldFamily
            pixelSize: 32 * root.uiScale.yScale
            weight: Font.DemiBold
            bold: true
        }
        fontSizeMode: Text.HorizontalFit
        lineHeight: 1.13
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
//        color: "#343434"
        wrapMode: Text.WordWrap

        maximumLineCount: 2

        text: (root.logined ? qsTr("Вход выполнен")
                            : qsTr("Войдите в свой аккаунт,\n чтобы открыть доступ к VK"))
    }


    Button {
        id: logoutButton
        anchors {
            bottom: root.bottom
            bottomMargin: 50 * root.uiScale.yScale
            horizontalCenter: parent.horizontalCenter
        }
        width: 200 * root.uiScale.xScale
        height: 75 * root.uiScale.yScale
        text: qsTr("Выход")

         Material.foreground: Material.LightBlue

        font {
            //family: root.uiStyle.font.boldFamily
            pixelSize: 24 *root.uiScale.yScale
            //weight: Font.DemiBold
            letterSpacing: 0.8
            capitalization: Font.AllUppercase
        }
        visible: root.logined
        onClicked: {
            root.updateLogin(false)
            webEngine.url = internal.logoutURL
        }
    }

    WebEngineView {
        id: webEngine

        visible: !root.logined
        enabled: visible

        anchors {
            top: titleText.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            topMargin: 15 * root.uiScale.yScale
            bottomMargin: 15 * root.uiScale.yScale
            margins: 30 * root.uiScale.xScale
        }

        url: root.logined ? "" : internal.loginURL

        profile: WebEngineProfile {
            persistentCookiesPolicy: WebEngineProfile.NoPersistentCookies
            //storageName: "4"
            //httpUserAgent: "Mobile"
        }

        settings {
            autoLoadImages: true
            javascriptEnabled: true
            javascriptCanAccessClipboard: true
            showScrollBars: false
            focusOnNavigationEnabled: true
        }

        onCertificateError: {
            error.defer();
        }

        onLoadingChanged: {
            if (loadRequest.status === WebEngineView.LoadStartedStatus) {
                return;
            }

            if(loadRequest.url.toString() == internal.logoutURL) {
                //root.clearAllCookies(webEngine.profile);
                root.updateLogin(false)
                webEngine.url = internal.loginURL;
                return;
            } else if(!internal.testLoginFinished(loadRequest.url.toString())) {
                return;
            }

            var result = internal.parseParams(loadRequest.url.toString())
            if (!result) {
                console.error("Wrong responce from server", loadRequest.url.toString());
                return;
            }
            if (result.error) {
                console.error("Error", result.error, result.error_description);
                return;
            }
            if (!result.access_token) {
                console.error("Access token absent", loadRequest.url.toString());
                return;
            }

            console.debug("VK access token:",result.access_token);
            root.updateLogin(true, result.access_token)
        }

        onJavaScriptConsoleMessage: {
            console.debug("WebEngine(%1 - %2): %3"
                          .arg(level)
                          .arg(lineNumber)
                          .arg(message));
        }

        onNavigationRequested: {
            console.debug("Instagram::onNavigationRequested:", request.url.toString())
            if( !internal.testWhiteList(request.url.toString()) ) {
                request.action = WebEngineView.IgnoreRequest;
                return;
            }
            request.action = WebEngineView.AcceptRequest;
        }

        BusyIndicator {
            anchors.centerIn: parent
            width: 60 * root.uiScale.xScale
            height: width
            running: webEngine.loading
        }
    }
}
