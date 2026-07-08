import QtQuick
import Lingmo.Theme

QtObject {
    id: effect

    property Item target: null
    property bool blurEnabled: false
    property real cornerRadius: 0
    property bool darkMode: false

    onBlurEnabledChanged: updateEffect()
    onCornerRadiusChanged: updateEffect()
    onDarkModeChanged: updateEffect()

    function updateEffect() {
        var settings = {
            "blur": effect.blurEnabled,
            "cornerRadius": effect.cornerRadius,
            "darkMode": effect.darkMode
        };
        console.log("[WindowEffects] Applying:", JSON.stringify(settings));
    }
}
