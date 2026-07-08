#pragma once

#include <platform/WindowAdapter.h>

namespace Lingmo {

// X11 platform adapter.
// Handles X11-specific window operations:
// - Full window state control via Qt (X11 supports _NET_WM_STATE).
// - Geometry changes are fully effective on X11.
// - SSD (Server-Side Decoration) is the default; CSD requires explicit opt-in.
class X11Adapter : public WindowAdapter
{
public:
    X11Adapter() = default;
    ~X11Adapter() override = default;

    Lingmo::Platform platform() const override;

    void setWindowState(QWindow *window, Qt::WindowState state) override;
    Qt::WindowState windowState(const QWindow *window) const override;

    void setWindowGeometry(QWindow *window, const QRect &geometry) override;
    QRect windowGeometry(const QWindow *window) const override;

    void configureWindowFlags(QWindow *window) override;
};

} // namespace Lingmo
