#include <LingmoWindow/WindowController.h>
#include <LingmoWindow/Types.h>
#include <platform/WindowAdapter.h>

#include <QTest>
#include <QWindow>
#include <QGuiApplication>
#include <QScreen>

class tst_WindowAdapter : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testCreateReturnsNonNull()
    {
        // create() must return a valid adapter for any QWindow
        QWindow window;
        auto *adapter = Lingmo::WindowAdapter::create(&window);
        QVERIFY(adapter != nullptr);
        delete adapter;
    }

    void testPlatformEnum()
    {
        // The adapter must report a valid platform
        QWindow window;
        auto *adapter = Lingmo::WindowAdapter::create(&window);
        QVERIFY(adapter != nullptr);

        const auto p = adapter->platform();
        QVERIFY(p == Lingmo::Platform::Unknown
             || p == Lingmo::Platform::X11
             || p == Lingmo::Platform::Wayland
             || p == Lingmo::Platform::macOS);
        delete adapter;
    }

    void testWindowStateRoundTrip()
    {
        QWindow window;
        auto *adapter = Lingmo::WindowAdapter::create(&window);
        QVERIFY(adapter != nullptr);

        // Read initial state — should be NoState for a fresh window
        const auto initial = adapter->windowState(&window);
        QCOMPARE(initial, Qt::WindowNoState);

        // Set Normal (no-op for already-normal window, but should not crash)
        adapter->setWindowState(&window, Qt::WindowNoState);
        QCOMPARE(adapter->windowState(&window), Qt::WindowNoState);

        delete adapter;
    }

    void testWindowGeometryRoundTrip()
    {
        QWindow window;
        auto *adapter = Lingmo::WindowAdapter::create(&window);
        QVERIFY(adapter != nullptr);

        const QRect testGeo(100, 200, 640, 480);
        adapter->setWindowGeometry(&window, testGeo);

        // On some platforms, position may be adjusted, but size should be honored
        const QRect result = adapter->windowGeometry(&window);
        QCOMPARE(result.width(), testGeo.width());
        QCOMPARE(result.height(), testGeo.height());

        delete adapter;
    }

    void testConfigureWindowFlagsDoesNotCrash()
    {
        QWindow window;
        auto *adapter = Lingmo::WindowAdapter::create(&window);
        QVERIFY(adapter != nullptr);

        // Should not crash — just configures flags
        adapter->configureWindowFlags(&window);

        delete adapter;
    }

    void testNullWindowHandling()
    {
        // All methods must handle nullptr gracefully
        auto *adapter = Lingmo::WindowAdapter::create(nullptr);
        QVERIFY(adapter != nullptr);

        // Should not crash
        adapter->setWindowState(nullptr, Qt::WindowNoState);
        QCOMPARE(adapter->windowState(nullptr), Qt::WindowNoState);

        adapter->setWindowGeometry(nullptr, QRect(0, 0, 100, 100));
        QCOMPARE(adapter->windowGeometry(nullptr), QRect());

        adapter->configureWindowFlags(nullptr);

        delete adapter;
    }

    void testAdapterViaWindowController()
    {
        // WindowController should create and use the adapter
        Lingmo::WindowController controller;
        QWindow window;
        controller.setWindow(&window);

        // State changes through controller should work
        controller.setWindowState(Lingmo::WindowState::Normal);
        QCOMPARE(controller.windowState(), Lingmo::WindowState::Normal);
    }
};

QTEST_MAIN(tst_WindowAdapter)
#include "tst_WindowAdapter.moc"
