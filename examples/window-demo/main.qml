import QtQuick
import QtQuick.Controls as T
import Lingmo.Theme
import Lingmo.Window

Window {
    id: window
    width: 800
    height: 600
    visible: true
    title: "Window Demo"

    headerBar: HeaderBar {
        title: "Lingmo Window Demo"
        subtitle: "A demonstration of the windowing system"
        iconSource: "qrc:/icon.png"
        showMinimize: true
        showMaximize: true
        showClose: true

        onMinimizeClicked: window.showMinimized()
        onMaximizeClicked: window.showMaximized()
        onCloseClicked: window.close()
    }

    contentItem: Rectangle {
        color: Theme.palette.background

        T.Label {
            anchors.centerIn: parent
            text: "Welcome to Lingmo Desktop"
            font: Theme.typography.fontByRole(FontRole.Heading)
            color: Theme.palette.foreground
        }
    }
}
