#include <LingmoWindow/HeaderBar.h>

#include <QTest>
#include <QSignalSpy>

class tst_HeaderBar : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testDefaultConstruction()
    {
        Lingmo::HeaderBar bar;
        QCOMPARE(bar.title(), QString());
        QCOMPARE(bar.subtitle(), QString());
        QVERIFY(bar.icon().isNull());
        QVERIFY(bar.showMinimize());
        QVERIFY(bar.showMaximize());
        QVERIFY(bar.showClose());
        QVERIFY(bar.showTitle());
        QVERIFY(!bar.showIcon());
        QVERIFY(bar.height() > 0);
        QVERIFY(bar.titleBarHeight() > 0);
    }

    void testTitle()
    {
        Lingmo::HeaderBar bar;
        QSignalSpy spy(&bar, &Lingmo::HeaderBar::titleChanged);

        bar.setTitle("My App");
        QCOMPARE(bar.title(), "My App");
        QCOMPARE(spy.count(), 1);

        bar.setTitle("My App");
        QCOMPARE(spy.count(), 1);
    }

    void testSubtitle()
    {
        Lingmo::HeaderBar bar;
        QSignalSpy spy(&bar, &Lingmo::HeaderBar::subtitleChanged);

        bar.setSubtitle("Version 1.0");
        QCOMPARE(bar.subtitle(), "Version 1.0");
        QCOMPARE(spy.count(), 1);
    }

    void testShowButtons()
    {
        Lingmo::HeaderBar bar;
        QSignalSpy spyMin(&bar, &Lingmo::HeaderBar::showMinimizeChanged);
        QSignalSpy spyMax(&bar, &Lingmo::HeaderBar::showMaximizeChanged);
        QSignalSpy spyClose(&bar, &Lingmo::HeaderBar::showCloseChanged);

        bar.setShowMinimize(false);
        QVERIFY(!bar.showMinimize());
        QCOMPARE(spyMin.count(), 1);

        bar.setShowMaximize(false);
        QVERIFY(!bar.showMaximize());
        QCOMPARE(spyMax.count(), 1);

        bar.setShowClose(false);
        QVERIFY(!bar.showClose());
        QCOMPARE(spyClose.count(), 1);
    }

    void testShowTitle()
    {
        Lingmo::HeaderBar bar;
        QSignalSpy spy(&bar, &Lingmo::HeaderBar::showTitleChanged);

        bar.setShowTitle(false);
        QVERIFY(!bar.showTitle());
        QCOMPARE(spy.count(), 1);

        bar.setShowTitle(true);
        QVERIFY(bar.showTitle());
        QCOMPARE(spy.count(), 2);
    }

    void testShowIcon()
    {
        Lingmo::HeaderBar bar;
        QSignalSpy spy(&bar, &Lingmo::HeaderBar::showIconChanged);
        QSignalSpy spySrc(&bar, &Lingmo::HeaderBar::iconSourceChanged);

        bar.setShowIcon(true);
        QVERIFY(bar.showIcon());
        QCOMPARE(spy.count(), 1);

        QUrl url("qrc:/icon.png");
        bar.setIconSource(url);
        QCOMPARE(bar.iconSource(), url);
        QCOMPARE(spySrc.count(), 1);
    }

    void testIconSourceNoChange()
    {
        Lingmo::HeaderBar bar;
        QSignalSpy spy(&bar, &Lingmo::HeaderBar::iconSourceChanged);

        QUrl url("qrc:/icon.png");
        bar.setIconSource(url);
        QCOMPARE(spy.count(), 1);

        bar.setIconSource(url);
        QCOMPARE(spy.count(), 1);
    }

    void testSignals()
    {
        Lingmo::HeaderBar bar;
        QSignalSpy spyMinClk(&bar, &Lingmo::HeaderBar::minimizeClicked);
        QSignalSpy spyMaxClk(&bar, &Lingmo::HeaderBar::maximizeClicked);
        QSignalSpy spyCloseClk(&bar, &Lingmo::HeaderBar::closeClicked);

        bar.minimize();
        bar.maximize();
        bar.close();
    }
};

QTEST_MAIN(tst_HeaderBar)
#include "tst_HeaderBar.moc"
