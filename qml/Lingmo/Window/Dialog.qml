import QtQuick
import QtQuick.Controls as T
import Lingmo.Theme

T.Dialog {
    id: dialog

    property alias headerBar: headerBarItem

    x: Math.max(0, Math.round((parent ? parent.width : 0) - width) / 2)
    y: Math.max(0, Math.round((parent ? parent.height : 0) - height) / 3)

    margins: 0
    spacing: 0
    topPadding: 0

    background: Rectangle {
        color: Theme.palette.surface
        radius: Theme.metrics.radiusMedium
        border.color: Theme.palette.border
        border.width: 1
    }

    header: Item {
        id: headerBarItem
        height: 0
    }

    footer: DialogButtonBox {
        background: Rectangle {
            color: "transparent"
        }
    }

    T.Overlay.modal: Rectangle {
        color: Theme.palette.overlay
    }

    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0.0
            to: 1.0
            duration: Theme.animation("fast").duration
        }
    }

    exit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1.0
            to: 0.0
            duration: Theme.animation("fast").duration
        }
    }
}
