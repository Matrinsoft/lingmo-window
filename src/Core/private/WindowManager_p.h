#pragma once

#include <LingmoWindow/Types.h>

class QWindow;

namespace Lingmo {

class Window;

// WindowManager is deprecated. WindowController handles window state
// directly via QWindow. This class is retained as a stub.
class WindowManager
{
public:
    static WindowManager *create();

    virtual ~WindowManager() = default;

protected:
    WindowManager() = default;
};

} // namespace Lingmo
