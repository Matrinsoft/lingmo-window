# Lingmo Window

Application window SDK for the Lingmo Desktop — frameless window helpers, CSD, titlebar, and window state management.

## Architecture

`lingmo-window` is a **client-side SDK library** (Layer 3 in the LingmoUI stack). It provides application-facing window abstractions with **no** dependency on KWin, KDE Frameworks, or any compositor internals.

```
lingmo-controls  ←  lingmo-window  →  lingmo-style
                      ↓
                 lingmo-theme (colors, metrics, typography)
```

### Components

| Class / QML Type | Role |
|---|---|
| `WindowController` (C++) | Decoupled window control abstraction — works with `QWindow`, `QQuickWindow`, or `QWidget` |
| `Window` (C++ / QML) | Thin `QWindow` convenience subclass; delegates to `WindowController` |
| `WindowChrome` (C++) | CSD hit-testing, drag regions, resize margins, corner radius |
| `WindowEffects` (C++) | Pure state holder for blur, corner radius, dark mode — **no platform impl** |
| `HeaderBar` (C++ / QML) | Custom titlebar with title, subtitle, icon, and min/max/close buttons |
| `Dialog` (QML) | Modal dialog with Lingmo theme styling |

### Platform Layer (`src/platform/`)

- `Wayland/` — xdg-shell protocol adapters (stub)
- `X11/` — Xlib/XCB window property adapters (stub)
- `Generic/` — fallback using basic Qt APIs

Compositor-side effect integration is handled by `kwin-integration` (separate repo), not by this library.

## Build

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

### Dependencies

- Qt 6.5+ (Core, Gui, Widgets, Qml, Quick)
- [lingmo-theme](https://github.com/Matrinsoft/lingmo-theme)

### Install

```bash
cmake --install build --prefix /usr
```

Consume from CMake:

```cmake
find_package(LingmoWindow REQUIRED)
target_link_libraries(myapp PRIVATE Lingmo::Window)
```

Or from QML:

```qml
import Lingmo.Window
```

## Quick Start (C++)

```cpp
#include <LingmoWindow/WindowController.h>

Lingmo::WindowController ctrl;
ctrl.setWindow(someQWindow);
ctrl.setTitle("My App");
ctrl.show();
```

## Quick Start (QML)

```qml
import Lingmo.Window

Window {
    width: 800
    height: 600
    visible: true
    title: "My App"
}
```

## Packaging

| Distro | Package |
|---|---|
| Debian | `liblingmowindow1`, `liblingmowindow-dev`, `qml6-module-lingmowindow` |
| Fedora / RPM | `liblingmowindow1`, `liblingmowindow-devel`, `qml6-lingmowindow` |

## License

GPL-2.0-or-later
