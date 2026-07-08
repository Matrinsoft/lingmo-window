#include <LingmoWindow/WindowChrome.h>

#include <QTest>
#include <QSignalSpy>

class tst_WindowChrome : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testDefaultConstruction()
    {
        Lingmo::WindowChrome chrome;
        QCOMPARE(chrome.cornerRadius(), 0.0);
        QCOMPARE(chrome.resizeMargins(), QMargins(8, 8, 8, 8));
        QCOMPARE(chrome.dragMargins(), QMargins(0, 0, 0, 0));
        QVERIFY(chrome.window() == nullptr);
    }

    void testCornerRadius()
    {
        Lingmo::WindowChrome chrome;
        QSignalSpy spy(&chrome, &Lingmo::WindowChrome::cornerRadiusChanged);

        chrome.setCornerRadius(10.0);
        QCOMPARE(chrome.cornerRadius(), 10.0);
        QCOMPARE(spy.count(), 1);

        chrome.setCornerRadius(10.0);
        QCOMPARE(spy.count(), 1);
    }

    void testResizeMargins()
    {
        Lingmo::WindowChrome chrome;
        QSignalSpy spy(&chrome, &Lingmo::WindowChrome::resizeMarginsChanged);

        QMargins margins(4, 4, 4, 4);
        chrome.setResizeMargins(margins);
        QCOMPARE(chrome.resizeMargins(), margins);
        QCOMPARE(spy.count(), 1);

        chrome.setResizeMargins(margins);
        QCOMPARE(spy.count(), 1);
    }

    void testDragMargins()
    {
        Lingmo::WindowChrome chrome;
        QSignalSpy spy(&chrome, &Lingmo::WindowChrome::dragMarginsChanged);

        QMargins margins(10, 0, 10, 0);
        chrome.setDragMargins(margins);
        QCOMPARE(chrome.dragMargins(), margins);
        QCOMPARE(spy.count(), 1);
    }

    void testResizeEdgeDetection()
    {
        Lingmo::WindowChrome chrome;
        // Without a window, resizeEdgeAt should return no edges
        QCOMPARE(chrome.resizeEdgeAt(QPoint(0, 0)), Qt::Edges{});
    }

    void testDragRegion()
    {
        Lingmo::WindowChrome chrome;
        QSize size(800, 600);

        // Default drag margins (0,0,0,0) - full window is drag area
        QRegion region = chrome.dragRegion(size);
        QCOMPARE(region, QRegion(0, 0, 800, 600));

        // With drag margins, excluded from top
        chrome.setDragMargins(QMargins(0, 48, 0, 0));
        region = chrome.dragRegion(size);
        QCOMPARE(region, QRegion(0, 48, 800, 552));
    }

    void testResizeRegion()
    {
        Lingmo::WindowChrome chrome;
        QSize size(800, 600);

        QRegion region = chrome.resizeRegion(size);
        QVERIFY(!region.isEmpty());
    }
};

QTEST_MAIN(tst_WindowChrome)
#include "tst_WindowChrome.moc"
