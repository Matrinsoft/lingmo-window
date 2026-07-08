#include <LingmoWindow/Window.h>
#include <LingmoWindow/WindowHelper.h>

#include <QTest>
#include <QSignalSpy>
#include <QGuiApplication>
#include <QScreen>

class tst_Window : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase()
    {
    }

    void testDefaultConstruction()
    {
        Lingmo::Window window;
        QCOMPARE(window.title(), QString());
        QVERIFY(window.icon().isNull());
        QCOMPARE(window.minimumSize(), QSize(0, 0));
        QCOMPARE(window.maximumSize(), QSize(16777215, 16777215));
        QVERIFY(window.isResizable());
        QVERIFY(window.isClosable());
        QCOMPARE(window.windowState(), Lingmo::WindowState::Normal);
    }

    void testTitle()
    {
        Lingmo::Window window;
        QSignalSpy spy(&window, &Lingmo::Window::titleChanged);

        window.setTitle("Test Window");
        QCOMPARE(window.title(), "Test Window");
        QCOMPARE(spy.count(), 1);

        window.setTitle("Test Window");
        QCOMPARE(spy.count(), 1);
    }

    void testResizable()
    {
        Lingmo::Window window;
        QSignalSpy spy(&window, &Lingmo::Window::resizableChanged);

        window.setResizable(false);
        QVERIFY(!window.isResizable());
        QCOMPARE(spy.count(), 1);

        window.setResizable(false);
        QCOMPARE(spy.count(), 1);

        window.setResizable(true);
        QVERIFY(window.isResizable());
        QCOMPARE(spy.count(), 2);
    }

    void testWindowState()
    {
        Lingmo::Window window;
        QSignalSpy spy(&window, &Lingmo::Window::windowStateChanged);

        window.setWindowState(Lingmo::WindowState::Minimized);
        QCOMPARE(window.windowState(), Lingmo::WindowState::Minimized);

        window.setWindowState(Lingmo::WindowState::Normal);
        QCOMPARE(window.windowState(), Lingmo::WindowState::Normal);
    }

    void testCenterOnScreen()
    {
        Lingmo::Window window;
        window.setGeometry(0, 0, 400, 300);
        window.centerOnScreen();

        auto *screen = QGuiApplication::primaryScreen();
        QVERIFY(screen != nullptr);
        const QRect geo = window.geometry();
        const QRect avail = screen->availableGeometry();
        const int expectedX = avail.x() + (avail.width() - 400) / 2;
        const int expectedY = avail.y() + (avail.height() - 300) / 2;
        QCOMPARE(geo.x(), expectedX);
        QCOMPARE(geo.y(), expectedY);
    }

    void testMinimumSize()
    {
        Lingmo::Window window;
        QSignalSpy spy(&window, &Lingmo::Window::minimumSizeChanged);

        window.setMinimumSize(QSize(320, 240));
        QCOMPARE(window.minimumSize(), QSize(320, 240));
        QCOMPARE(spy.count(), 1);
    }

    void testMaximumSize()
    {
        Lingmo::Window window;
        QSignalSpy spy(&window, &Lingmo::Window::maximumSizeChanged);

        window.setMaximumSize(QSize(1920, 1080));
        QCOMPARE(window.maximumSize(), QSize(1920, 1080));
        QCOMPARE(spy.count(), 1);
    }

    void testHelperFunctions()
    {
        QVERIFY(!Lingmo::WindowHelper::platformName().isEmpty());
        QVERIFY(!Lingmo::WindowHelper::isWayland()
                || !Lingmo::WindowHelper::isX11());
    }

    void testExtraMargins()
    {
        Lingmo::Window window;
        QCOMPARE(window.extraMargins(), QMargins());
    }
};

QTEST_MAIN(tst_Window)
#include "tst_Window.moc"
