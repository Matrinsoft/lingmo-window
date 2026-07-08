#include "WaylandAdapter.h"

#include <LingmoWindow/Types.h>
#include <QWindow>
#include <QScreen>
#include <QGuiApplication>

namespace Lingmo {

Lingmo::Platform WaylandAdapter::platform() const
{
    return Lingmo::Platform::Wayland;
}

void WaylandAdapter::setWindowState(QWindow *window, Qt::WindowState state)
{
    if (!window) return;

    // On Wayland, direct setWindowState() doesn't work for minimize/maximize.
    // Use the show*() methods which the Qt Wayland platform plugin handles
    // through the appropriate protocol (xdg_toplevel for maximize/minimize,
    // ext_idle_notification or protocol-specific for minimize).
    switch (state) {
    case Qt::WindowNoState:
        window->showNormal();
        break;
    case Qt::WindowMinimized:
        window->showMinimized();
        break;
    case Qt::WindowMaximized:
        window->showMaximized();
        break;
    case Qt::WindowFullScreen:
        window->showFullScreen();
        break;
    case Qt::WindowActive:
        window->show();
        window->raise();
        window->requestActivate();
        break;
    }
}

Qt::WindowState WaylandAdapter::windowState(const QWindow *window) const
{
    if (!window) return Qt::WindowNoState;
    return window->windowState();
}

void WaylandAdapter::setWindowGeometry(QWindow *window, const QRect &geometry)
{
    if (!window) return;

    // On Wayland, the compositor controls window placement.
    // setGeometry() is partially supported — size is honored but position
    // may be ignored. We clamp to screen bounds as a best-effort.
    QRect clamped = geometry;

    if (QScreen *screen = window->screen()) {
        const QRect screenGeo = screen->availableGeometry();
        // Ensure window is at least partially visible
        if (clamped.right() < screenGeo.left())
            clamped.moveLeft(screenGeo.left());
        if (clamped.bottom() < screenGeo.top())
            clamped.moveTop(screenGeo.top());
        if (clamped.left() > screenGeo.right())
            clamped.moveRight(screenGeo.right());
        if (clamped.top() > screenGeo.bottom())
            clamped.moveBottom(screenGeo.bottom());
    }

    window->setGeometry(clamped);
}

QRect WaylandAdapter::windowGeometry(const QWindow *window) const
{
    if (!window) return {};
    return window->geometry();
}

void WaylandAdapter::configureWindowFlags(QWindow *window)
{
    if (!window) return;

    // On Wayland, CSD (Client-Side Decoration) is the default.
    // Applications that provide their own title bar should use
    // FramelessWindowHint. The xdg-decoration protocol will negotiate
    // CSD vs SSD with the compositor.
    window->setFlags(window->flags() | Qt::FramelessWindowHint);
}

} // namespace Lingmo
