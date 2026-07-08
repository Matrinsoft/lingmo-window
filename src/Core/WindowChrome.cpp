#include "private/WindowChrome_p.h"

#include <QWindow>

namespace Lingmo {

WindowChromePrivate::WindowChromePrivate(WindowChrome *qq)
    : q(qq)
{
}

WindowChromePrivate::~WindowChromePrivate() = default;

WindowChrome::WindowChrome(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<WindowChromePrivate>(this))
{
}

WindowChrome::~WindowChrome() = default;

void WindowChrome::setWindow(QWindow *w) { d->window = w; }

QWindow *WindowChrome::window() const { return d->window; }

qreal WindowChrome::cornerRadius() const { return d->cornerRadius; }

void WindowChrome::setCornerRadius(qreal radius)
{
    if (qFuzzyCompare(d->cornerRadius, radius)) return;
    d->cornerRadius = radius;
    emit cornerRadiusChanged();
}

QMargins WindowChrome::resizeMargins() const { return d->resizeMargins; }

void WindowChrome::setResizeMargins(const QMargins &margins)
{
    if (d->resizeMargins == margins) return;
    d->resizeMargins = margins;
    emit resizeMarginsChanged();
}

QMargins WindowChrome::dragMargins() const { return d->dragMargins; }

void WindowChrome::setDragMargins(const QMargins &margins)
{
    if (d->dragMargins == margins) return;
    d->dragMargins = margins;
    emit dragMarginsChanged();
}

bool WindowChrome::isInDragArea(const QPoint &localPos) const
{
    if (resizeEdgeAt(localPos) != Qt::Edges{}) return false;

    const auto rect = d->window ? d->window->geometry() : QRect();
    const QRect dragRect(
        d->dragMargins.left(),
        d->dragMargins.top(),
        rect.width() - d->dragMargins.left() - d->dragMargins.right(),
        rect.height() - d->dragMargins.top() - d->dragMargins.bottom()
    );
    return dragRect.contains(localPos);
}

Qt::Edges WindowChrome::resizeEdgeAt(const QPoint &localPos) const
{
    if (!d->window) return {};
    const auto sz = d->window->geometry().size();
    Qt::Edges edges;

    if (localPos.x() <= d->resizeMargins.left())
        edges |= Qt::LeftEdge;
    if (localPos.x() >= sz.width() - d->resizeMargins.right())
        edges |= Qt::RightEdge;
    if (localPos.y() <= d->resizeMargins.top())
        edges |= Qt::TopEdge;
    if (localPos.y() >= sz.height() - d->resizeMargins.bottom())
        edges |= Qt::BottomEdge;

    return edges;
}

QRegion WindowChrome::dragRegion(const QSize &windowSize) const
{
    const int x = d->dragMargins.left();
    const int y = d->dragMargins.top();
    const int w = windowSize.width() - d->dragMargins.left() - d->dragMargins.right();
    const int h = windowSize.height() - d->dragMargins.top() - d->dragMargins.bottom();
    if (w <= 0 || h <= 0) return {};
    return QRegion(x, y, w, h);
}

QRegion WindowChrome::resizeRegion(const QSize &windowSize) const
{
    QRegion region;
    const int w = windowSize.width();
    const int h = windowSize.height();

    // Top edge
    if (d->resizeMargins.top() > 0)
        region += QRegion(0, 0, w, d->resizeMargins.top());
    // Bottom edge
    if (d->resizeMargins.bottom() > 0)
        region += QRegion(0, h - d->resizeMargins.bottom(), w, d->resizeMargins.bottom());
    // Left edge
    if (d->resizeMargins.left() > 0)
        region += QRegion(0, d->resizeMargins.top(), d->resizeMargins.left(), h - d->resizeMargins.top() - d->resizeMargins.bottom());
    // Right edge
    if (d->resizeMargins.right() > 0)
        region += QRegion(w - d->resizeMargins.right(), d->resizeMargins.top(), d->resizeMargins.right(), h - d->resizeMargins.top() - d->resizeMargins.bottom());

    return region;
}

} // namespace Lingmo
