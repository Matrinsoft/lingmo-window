#pragma once

#include <platform/WindowAdapter.h>

namespace Lingmo {

// Generic/fallback platform adapter.
// Uses standard Qt APIs with no platform-specific behavior.
class GenericAdapter : public WindowAdapter
{
public:
    GenericAdapter() = default;
    ~GenericAdapter() override = default;

    Lingmo::Platform platform() const override;

    void setWindowState(QWindow *window, Qt::WindowState state) override;
    Qt::WindowState windowState(const QWindow *window) const override;

    void setWindowGeometry(QWindow *window, const QRect &geometry) override;
    QRect windowGeometry(const QWindow *window) const override;

    void configureWindowFlags(QWindow *window) override;
};

} // namespace Lingmo
