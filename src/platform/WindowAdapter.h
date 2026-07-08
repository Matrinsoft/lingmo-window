#pragma once

#include <LingmoWindow/Types.h>

class QWindow;

namespace Lingmo {

// Abstract interface for platform-specific window operations.
// Platform adapters handle differences between Wayland, X11, and generic
// window systems (e.g., setting window type, fullscreen handling, CSD negotiation).
//
// Concrete implementations live in platform/Wayland/, platform/X11/, and
// platform/Generic/ respectively.
class WindowAdapter
{
public:
    static WindowAdapter *create(QWindow *window);

    virtual ~WindowAdapter() = default;

    virtual void setWindowGeometry(QWindow *window, const QRect &geometry);
    virtual QRect windowGeometry(const QWindow *window) const;

    virtual void setWindowState(QWindow *window, Qt::WindowState state);
    virtual Qt::WindowState windowState(const QWindow *window) const;

protected:
    WindowAdapter() = default;
};

} // namespace Lingmo
