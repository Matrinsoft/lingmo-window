import QtQuick
import QtQuick.Controls as T
import Lingmo.Theme

QtObject {
    id: effect

    property Item target: null
    property bool blurEnabled: false
    property bool micaEnabled: false
    property bool acrylicEnabled: false
    property real cornerRadius: 0
    property bool darkMode: false

    onBlurEnabledChanged: updateEffect()
    onMicaEnabledChanged: updateEffect()
    onAcrylicEnabledChanged: updateEffect()
    onCornerRadiusChanged: updateEffect()
    onDarkModeChanged: updateEffect()

    function updateEffect() {
        var settings = {
            "blur": effect.blurEnabled,
            "mica": effect.micaEnabled,
            "acrylic": effect.acrylicEnabled,
            "cornerRadius": effect.cornerRadius,
            "darkMode": effect.darkMode
        };
        console.log("[WindowEffect] Applying:", JSON.stringify(settings));
    }
}
