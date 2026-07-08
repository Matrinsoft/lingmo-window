#pragma once

#include <LingmoWindow/Types.h>

class QWindow;

namespace Lingmo {

class Window;

class WindowManager
{
public:
    static WindowManager *create();

    virtual ~WindowManager() = default;

    virtual void setWindowState(Window *window, Lingmo::WindowState state);
    virtual Lingmo::WindowState windowState(const Window *window) const;
    virtual void setTitle(Window *window, const QString &title);
    virtual void setIcon(Window *window, const QIcon &icon);
    virtual void setResizable(Window *window, bool resizable);
    virtual void setGeometry(const Window *window, QRect geometry);
    virtual QMargins extraMargins(const Window *window) const;

protected:
    WindowManager() = default;
};

} // namespace Lingmo
