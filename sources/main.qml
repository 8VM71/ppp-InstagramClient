import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

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

    LoginPage {
        uiScale: uiScale
        anchors.fill: parent
    }

}
