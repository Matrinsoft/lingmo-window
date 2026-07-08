import QtQuick
import QtQuick.Controls as T
import QtQuick.Layouts
import Lingmo.Theme

T.Control {
    id: control

    property string title: ""
    property string subtitle: ""
    property url iconSource: ""
    property bool showMinimize: true
    property bool showMaximize: true
    property bool showClose: true
    property bool showTitle: true
    property bool showIcon: false
    property bool isFullScreen: false

    signal minimizeClicked()
    signal maximizeClicked()
    signal closeClicked()
    signal doubleClicked()

    implicitHeight: Math.max(Theme.metrics.spacingXLarge * 2 + Theme.metrics.spacingMedium,
                             48)

    padding: 0
    spacing: Theme.metrics.spacingSmall

    background: Rectangle {
        color: Theme.palette.surface
        T.Label {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: Theme.palette.border
        }
    }

    contentItem: Row {
        height: parent.height
        spacing: control.spacing
        leftPadding: control.leftPadding
        rightPadding: control.rightPadding

        Item {
            width: iconArea.visible ? iconArea.width + control.spacing : 0
            height: parent.height
            visible: control.showIcon

            Rectangle {
                id: iconArea
                anchors.centerIn: parent
                width: 24
                height: 24
                radius: 4
                color: "transparent"
                visible: control.iconSource.toString() !== ""

                Image {
                    anchors.fill: parent
                    source: control.iconSource
                    fillMode: Image.PreserveAspectFit
                }
            }
        }

        Item {
            width: titleColumn.width
            height: parent.height
            visible: control.showTitle && (control.title !== "" || control.subtitle !== "")

            Column {
                id: titleColumn
                anchors.verticalCenter: parent.verticalCenter
                spacing: 0

                T.Label {
                    text: control.title
                    font: Theme.typography.fontByRole(FontRole.UI)
                    color: Theme.palette.foreground
                    visible: control.title !== ""
                }

                T.Label {
                    text: control.subtitle
                    font: Theme.typography.fontByRole(FontRole.Caption)
                    color: Theme.palette.foregroundSecondary
                    visible: control.subtitle !== ""
                }
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Row {
            spacing: 0
            visible: !control.isFullScreen

            T.Button {
                id: minimizeBtn
                width: 46
                height: control.height
                flat: true
                visible: control.showMinimize
                icon.name: "window-minimize-symbolic"
                onClicked: control.minimizeClicked()
            }

            T.Button {
                id: maximizeBtn
                width: 46
                height: control.height
                flat: true
                visible: control.showMaximize
                icon.name: "window-maximize-symbolic"
                onClicked: control.maximizeClicked()
            }

            T.Button {
                id: closeBtn
                width: 46
                height: control.height
                flat: true
                visible: control.showClose
                icon.name: "window-close-symbolic"
                onClicked: control.closeClicked()
            }
        }
    }

    // Drag handling uses WindowChrome logic
    // For QML, this provides simple header bar dragging
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"

        onPressed: function(mouse) {
            clickPos = Qt.point(mouse.x, mouse.y);
        }

        onPositionChanged: function(mouse) {
            if (mouse.buttons & Qt.LeftButton) {
                var win = control.Window.window;
                if (win) {
                    win.x += mouse.x - clickPos.x;
                    win.y += mouse.y - clickPos.y;
                }
            }
        }

        onDoubleClicked: {
            control.doubleClicked();
        }
    }
}
