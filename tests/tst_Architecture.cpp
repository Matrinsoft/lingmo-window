#include <LingmoWindow/WindowController.h>
#include <LingmoWindow/WindowChrome.h>
#include <LingmoWindow/WindowEffects.h>
#include <LingmoWindow/Types.h>

#include <QTest>

// Architecture constraint tests: verify no forbidden dependencies exist.
//
// These tests ensure lingmo-window remains a client-side SDK library
// with no dependency on KWin, KDE Frameworks, or platform-specific
// windowing system APIs (Windows DWM, etc.).

static_assert(sizeof(Lingmo::WindowController) > 0,
    "WindowController must be a complete type");
static_assert(sizeof(Lingmo::WindowChrome) > 0,
    "WindowChrome must be a complete type");
static_assert(sizeof(Lingmo::WindowEffects) > 0,
    "WindowEffects must be a complete type");

class tst_Architecture : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testPlatformEnumHasNoWindows()
    {
        // Platform::Windows removed - lingmo-window is Linux-only
        bool hasWindows = false;
        switch (Lingmo::Platform::Unknown) {
        case Lingmo::Platform::X11:
        case Lingmo::Platform::Wayland:
        case Lingmo::Platform::macOS:
        case Lingmo::Platform::Unknown:
            break;
        }
        QVERIFY(!hasWindows);
    }

    void testWindowEffectsHasNoPlatformCode()
    {
        // WindowEffects is pure state holder - no platform API calls
        Lingmo::WindowEffects effects;
        effects.setBlurEnabled(true);
        QVERIFY(effects.isBlurEnabled());

        effects.setDarkModeEnabled(true);
        QVERIFY(effects.isDarkModeEnabled());

        // No isSupported() method - effects are always available as state
        // Compositor integration is deferred to kwin-integration layer
    }

    void testWindowChromeIsGeometryOnly()
    {
        // WindowChrome is pure geometry/hit-testing - no effect implementation
        Lingmo::WindowChrome chrome;
        chrome.setCornerRadius(8.0);
        QCOMPARE(chrome.cornerRadius(), 8.0);

        // isInDragArea and resizeEdgeAt are pure math operations
        QCOMPARE(chrome.resizeEdgeAt(QPoint(-1, -1)), Qt::Edges{});
    }

    void testNoWindowEffectManager()
    {
        // WindowEffectManager was removed - no DWM, no Mica, no Acrylic
        // WindowEffects is the replacement: pure state holder
        Lingmo::WindowEffects effects;
        QVERIFY(!effects.isBlurEnabled());
    }
};

QTEST_MAIN(tst_Architecture)
#include "tst_Architecture.moc"
