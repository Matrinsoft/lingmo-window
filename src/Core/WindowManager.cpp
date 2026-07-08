#include "private/WindowManager_p.h"

#include <LingmoWindow/Window.h>
#include <LingmoWindow/WindowHelper.h>

#include <QGuiApplication>
#include <QWindow>
#include <QScreen>
#include <QWidget>

namespace Lingmo {

// --- Generic WindowManager (cross-platform fallback) ---

class GenericWindowManager : public WindowManager
{
public:
    void setWindowState(Window *window, Lingmo::WindowState state) override
    {
        Qt::WindowState qtState = Qt::WindowNoState;
        switch (state) {
        case Lingmo::WindowState::Normal:     qtState = Qt::WindowNoState; break;
        case Lingmo::WindowState::Minimized:  qtState = Qt::WindowMinimized; break;
        case Lingmo::WindowState::Maximized:  qtState = Qt::WindowMaximized; break;
        case Lingmo::WindowState::FullScreen: qtState = Qt::WindowFullScreen; break;
        case Lingmo::WindowState::Hidden:
            window->hide();
            return;
        }
        window->QWindow::setWindowState(qtState);
    }

    Lingmo::WindowState windowState(const Window *window) const override
    {
        const auto qtState = const_cast<QWindow *>(static_cast<const QWindow *>(window))->windowState();
        switch (qtState) {
        case Qt::WindowMinimized:  return Lingmo::WindowState::Minimized;
        case Qt::WindowMaximized:  return Lingmo::WindowState::Maximized;
        case Qt::WindowFullScreen: return Lingmo::WindowState::FullScreen;
        default:                   return Lingmo::WindowState::Normal;
        }
    }

    void setTitle(Window *window, const QString &title) override
    {
        window->QWindow::setTitle(title);
    }

    void setIcon(Window *window, const QIcon &icon) override
    {
        window->QWindow::setIcon(icon);
    }

    void setResizable(Window *window, bool resizable) override
    {
        Q_UNUSED(window);
        Q_UNUSED(resizable);
    }

    QMargins extraMargins(const Window *window) const override
    {
        Q_UNUSED(window);
        return {};
    }
};

// --- Windows WindowManager ---

#ifdef Q_OS_WIN
class WindowsWindowManager : public WindowManager
{
public:
    void setWindowState(Window *window, Lingmo::WindowState state) override
    {
        GenericWindowManager().setWindowState(window, state);
    }

    Lingmo::WindowState windowState(const Window *window) const override
    {
        return GenericWindowManager().windowState(window);
    }

    void setResizable(Window *window, bool resizable) override
    {
        Q_UNUSED(window);
        Q_UNUSED(resizable);
    }
};
#endif

// --- Factory ---

WindowManager *WindowManager::create()
{
    const auto platform = WindowHelper::currentPlatform();
    switch (platform) {
#ifdef Q_OS_WIN
    case Platform::Windows:
        return new WindowsWindowManager();
#endif
    default:
        return new GenericWindowManager();
    }
}

} // namespace Lingmo
