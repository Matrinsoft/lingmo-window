#pragma once

#include <LingmoWindow/LingmoWindowExport.h>

#include <QObject>

namespace Lingmo {

enum class WindowState {
    Normal     = 0,
    Minimized  = 1,
    Maximized  = 2,
    FullScreen = 3,
    Hidden     = 4
};

enum class WindowType {
    Normal       = 0,
    Dialog       = 1,
    Utility      = 2,
    SplashScreen = 3
};

enum class Platform {
    Unknown = 0,
    X11     = 1,
    Wayland = 2,
    macOS   = 3
};

} // namespace Lingmo
