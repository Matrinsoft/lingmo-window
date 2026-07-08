#include "GenericAdapter.h"

#include <QWindow>

namespace Lingmo {

Lingmo::Platform GenericAdapter::platform() const
{
    return Lingmo::Platform::Unknown;
}

void GenericAdapter::setWindowState(QWindow *window, Qt::WindowState state)
{
    if (!window) return;
    window->setWindowState(state);
}

Qt::WindowState GenericAdapter::windowState(const QWindow *window) const
{
    if (!window) return Qt::WindowNoState;
    return window->windowState();
}

void GenericAdapter::setWindowGeometry(QWindow *window, const QRect &geometry)
{
    if (!window) return;
    window->setGeometry(geometry);
}

QRect GenericAdapter::windowGeometry(const QWindow *window) const
{
    if (!window) return {};
    return window->geometry();
}

void GenericAdapter::configureWindowFlags(QWindow *window)
{
    Q_UNUSED(window);
}

} // namespace Lingmo
