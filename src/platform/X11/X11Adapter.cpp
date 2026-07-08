#include "X11Adapter.h"

#include <LingmoWindow/Types.h>
#include <QWindow>

namespace Lingmo {

Lingmo::Platform X11Adapter::platform() const
{
    return Lingmo::Platform::X11;
}

void X11Adapter::setWindowState(QWindow *window, Qt::WindowState state)
{
    if (!window) return;

    // On X11, setWindowState() works directly via _NET_WM_STATE.
    // Qt's X11 platform plugin translates Qt::WindowState to the
    // appropriate EWMH atoms.
    window->setWindowState(state);
}

Qt::WindowState X11Adapter::windowState(const QWindow *window) const
{
    if (!window) return Qt::WindowNoState;
    return window->windowState();
}

void X11Adapter::setWindowGeometry(QWindow *window, const QRect &geometry)
{
    if (!window) return;

    // On X11, setGeometry() is fully effective — both size and position
    // are honored by the window manager.
    window->setGeometry(geometry);
}

QRect X11Adapter::windowGeometry(const QWindow *window) const
{
    if (!window) return {};
    return window->geometry();
}

void X11Adapter::configureWindowFlags(QWindow *window)
{
    if (!window) return;

    // On X11, SSD (Server-Side Decoration) is the default.
    // Applications that provide their own title bar should set
    // FramelessWindowHint. The window manager will stop decorating
    // the window.
    window->setFlags(window->flags() | Qt::FramelessWindowHint);
}

} // namespace Lingmo
