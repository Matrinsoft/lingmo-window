#pragma once

#include <platform/WindowAdapter.h>

namespace Lingmo {

// Wayland platform adapter.
// Handles Wayland-specific window state management:
// - State transitions use QWindow::show*() methods (Wayland doesn't support
//   direct setWindowState() for minimize/maximize).
// - Geometry changes are validated before application.
// - CSD (Client-Side Decoration) is the default on Wayland.
class WaylandAdapter : public WindowAdapter
{
public:
    WaylandAdapter() = default;
    ~WaylandAdapter() override = default;

    Lingmo::Platform platform() const override;

    void setWindowState(QWindow *window, Qt::WindowState state) override;
    Qt::WindowState windowState(const QWindow *window) const override;

    void setWindowGeometry(QWindow *window, const QRect &geometry) override;
    QRect windowGeometry(const QWindow *window) const override;

    void configureWindowFlags(QWindow *window) override;
};

} // namespace Lingmo
