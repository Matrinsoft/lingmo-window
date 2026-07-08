#include <LingmoWindow/WindowHelper.h>

#include <QGuiApplication>
#include <QScreen>
#include <QWindow>
#include <QPoint>

namespace Lingmo {
namespace WindowHelper {

void centerOnScreen(QWindow *window, QScreen *screen)
{
    if (!window) return;
    if (!screen) screen = QGuiApplication::primaryScreen();
    if (!screen) return;
    const QRect geo = screen->availableGeometry();
    const QSize sz = window->geometry().size();
    const int x = geo.x() + (geo.width() - sz.width()) / 2;
    const int y = geo.y() + (geo.height() - sz.height()) / 2;
    window->setGeometry(x, y, sz.width(), sz.height());
}

QRect availableGeometry(QScreen *screen)
{
    if (!screen) screen = QGuiApplication::primaryScreen();
    return screen ? screen->availableGeometry() : QRect();
}

QScreen *screenAt(const QPoint &point)
{
    return QGuiApplication::screenAt(point);
}

bool isWayland()
{
    return QGuiApplication::platformName().contains("wayland", Qt::CaseInsensitive);
}

bool isX11()
{
    return QGuiApplication::platformName().contains("xcb", Qt::CaseInsensitive);
}

Lingmo::Platform currentPlatform()
{
    const QString name = QGuiApplication::platformName();
    if (name.contains("wayland", Qt::CaseInsensitive)) return Platform::Wayland;
    if (name.contains("xcb", Qt::CaseInsensitive)) return Platform::X11;
    if (name.contains("cocoa", Qt::CaseInsensitive)) return Platform::macOS;
    return Platform::Unknown;
}

QString platformName()
{
    return QGuiApplication::platformName();
}

QWindow *transientParent(QWindow *window)
{
    return window ? window->transientParent() : nullptr;
}

void setTransientParent(QWindow *window, QWindow *parent)
{
    if (window) window->setTransientParent(parent);
}

} // namespace WindowHelper
} // namespace Lingmo
