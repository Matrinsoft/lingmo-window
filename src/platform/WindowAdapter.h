#pragma once

#include <QRect>
#include <Qt>

class QWindow;

namespace Lingmo {

// Forward declaration — concrete definition is in LingmoWindow/Types.h.
// This avoids pulling the export macro and Qt dependencies into adapter headers.
enum class Platform : int;

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

    virtual Lingmo::Platform platform() const = 0;

    virtual void setWindowState(QWindow *window, Qt::WindowState state) = 0;
    virtual Qt::WindowState windowState(const QWindow *window) const = 0;

    virtual void setWindowGeometry(QWindow *window, const QRect &geometry) = 0;
    virtual QRect windowGeometry(const QWindow *window) const = 0;

    virtual void configureWindowFlags(QWindow *window) = 0;

protected:
    WindowAdapter() = default;
};

} // namespace Lingmo
