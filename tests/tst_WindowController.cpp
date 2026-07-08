#include <LingmoWindow/WindowController.h>
#include <LingmoWindow/WindowChrome.h>
#include <LingmoWindow/WindowEffects.h>

#include <QTest>
#include <QSignalSpy>

class tst_WindowController : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testCreate()
    {
        Lingmo::WindowController ctrl;
        QVERIFY(!ctrl.hasWindow());
        QVERIFY(ctrl.chrome() != nullptr);
        QVERIFY(ctrl.effects() != nullptr);
    }

    void testDefaultProperties()
    {
        Lingmo::WindowController ctrl;
        QCOMPARE(ctrl.title(), QString());
        QVERIFY(ctrl.icon().isNull());
        QCOMPARE(ctrl.minimumSize(), QSize(0, 0));
        QCOMPARE(ctrl.maximumSize(), QSize(16777215, 16777215));
        QVERIFY(ctrl.isResizable());
        QVERIFY(ctrl.isClosable());
        QCOMPARE(ctrl.windowState(), Lingmo::WindowState::Normal);
    }

    void testTitle()
    {
        Lingmo::WindowController ctrl;
        QSignalSpy spy(&ctrl, &Lingmo::WindowController::titleChanged);

        ctrl.setTitle("Test");
        QCOMPARE(ctrl.title(), "Test");
        QCOMPARE(spy.count(), 1);

        ctrl.setTitle("Test");
        QCOMPARE(spy.count(), 1);
    }

    void testResizable()
    {
        Lingmo::WindowController ctrl;
        QSignalSpy spy(&ctrl, &Lingmo::WindowController::resizableChanged);

        ctrl.setResizable(false);
        QVERIFY(!ctrl.isResizable());
        QCOMPARE(spy.count(), 1);

        ctrl.setResizable(true);
        QVERIFY(ctrl.isResizable());
        QCOMPARE(spy.count(), 2);
    }

    void testClosable()
    {
        Lingmo::WindowController ctrl;
        QSignalSpy spy(&ctrl, &Lingmo::WindowController::closableChanged);

        ctrl.setClosable(false);
        QVERIFY(!ctrl.isClosable());
        QCOMPARE(spy.count(), 1);

        ctrl.setClosable(true);
        QVERIFY(ctrl.isClosable());
        QCOMPARE(spy.count(), 2);
    }

    void testWindowState()
    {
        Lingmo::WindowController ctrl;
        QSignalSpy spy(&ctrl, &Lingmo::WindowController::windowStateChanged);

        ctrl.setWindowState(Lingmo::WindowState::Minimized);
        QCOMPARE(ctrl.windowState(), Lingmo::WindowState::Minimized);

        ctrl.setWindowState(Lingmo::WindowState::Normal);
        QCOMPARE(ctrl.windowState(), Lingmo::WindowState::Normal);
    }

    void testChrome()
    {
        Lingmo::WindowController ctrl;
        auto *chrome = ctrl.chrome();
        QVERIFY(chrome != nullptr);

        chrome->setCornerRadius(12.0);
        QCOMPARE(chrome->cornerRadius(), 12.0);

        chrome->setResizeMargins(QMargins(5, 5, 5, 5));
        QCOMPARE(chrome->resizeMargins(), QMargins(5, 5, 5, 5));
    }

    void testEffects()
    {
        Lingmo::WindowController ctrl;
        auto *effects = ctrl.effects();
        QVERIFY(effects != nullptr);

        QVERIFY(!effects->isBlurEnabled());
        effects->setBlurEnabled(true);
        QVERIFY(effects->isBlurEnabled());

        QVERIFY(!effects->isDarkModeEnabled());
        effects->setDarkModeEnabled(true);
        QVERIFY(effects->isDarkModeEnabled());
    }

    void testExtraMargins()
    {
        Lingmo::WindowController ctrl;
        QCOMPARE(ctrl.extraMargins(), QMargins());
    }
};

QTEST_MAIN(tst_WindowController)
#include "tst_WindowController.moc"
