import QtQuick
import QtTest
import Lingmo.Window
import Lingmo.Theme

TestCase {
    name: "QmlImportTest"

    function test_createWindow() {
        var window = createTemporaryObject(Window, {}, {});
        verify(window !== null, "Window should be creatable");
    }

    function test_createHeaderBar() {
        var bar = createTemporaryObject(HeaderBar, {}, {
            title: "Test",
            subtitle: "Sub",
            showMinimize: true,
            showMaximize: true,
            showClose: true
        });
        verify(bar !== null, "HeaderBar should be creatable");
        compare(bar.title, "Test");
        compare(bar.subtitle, "Sub");
    }

    function test_createDialog() {
        var dialog = createTemporaryObject(Dialog, {}, {});
        verify(dialog !== null, "Dialog should be creatable");
    }

    function test_createWindowEffects() {
        var effect = createTemporaryObject(WindowEffects, {}, {});
        verify(effect !== null, "WindowEffects should be creatable");
    }

    function test_themeImport() {
        verify(Theme.palette !== undefined, "Lingmo.Theme should be importable");
        verify(Theme.metrics !== undefined);
        verify(Theme.typography !== undefined);
    }
}
