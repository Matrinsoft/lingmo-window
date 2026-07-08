#include <platform/WindowAdapter.h>

#include <QGuiApplication>
#include <QString>

// Platform-specific adapter includes are provided by the linked OBJECT library.
// The factory creates the correct adapter based on the runtime platform.
#if defined(Q_OS_LINUX)
#include <platform/Generic/GenericAdapter.h>
#include <platform/Wayland/WaylandAdapter.h>
#include <platform/X11/X11Adapter.h>
#endif

namespace Lingmo {

WindowAdapter *WindowAdapter::create(QWindow *window)
{
    Q_UNUSED(window);

#if defined(Q_OS_LINUX)
    const QString platformName = QGuiApplication::platformName();

    if (platformName.contains(QLatin1String("wayland"), Qt::CaseInsensitive)) {
        return new WaylandAdapter();
    }

    if (platformName.contains(QLatin1String("xcb"), Qt::CaseInsensitive)) {
        return new X11Adapter();
    }

    return new GenericAdapter();
#else
    return new GenericAdapter();
#endif
}

} // namespace Lingmo
