import QtQuick
import QtQuick.Controls as T
import QtQuick.Window as QWindow
import Lingmo.Theme

QWindow.Window {
    id: window

    default property alias contentData: contentItem.data
    property alias contentItem: contentItem
    property var headerBar

    color: Theme.palette.surface

    Item {
        id: contentItem
        anchors {
            top: headerBarItem.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    Item {
        id: headerBarItem
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: headerBar ? headerBar.height : 0
        visible: headerBar !== null
    }
}
