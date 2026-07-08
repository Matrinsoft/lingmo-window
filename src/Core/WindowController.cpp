#include "private/WindowController_p.h"
#include "private/WindowChrome_p.h"
#include "private/WindowEffects_p.h"
#include <platform/WindowAdapter.h>

#include <QWindow>
#include <QScreen>
#include <QGuiApplication>

namespace Lingmo {

WindowControllerPrivate::WindowControllerPrivate(WindowController *qq)
    : q(qq)
    , chrome(new WindowChrome(qq))
    , effects(new WindowEffects(qq))
{
}

WindowControllerPrivate::~WindowControllerPrivate() = default;

void WindowControllerPrivate::applyWindowState(Lingmo::WindowState s)
{
    state = s;
    if (!window || !adapter) return;

    switch (s) {
    case Lingmo::WindowState::Normal:
        adapter->setWindowState(window, Qt::WindowNoState);
        break;
    case Lingmo::WindowState::Minimized:
        adapter->setWindowState(window, Qt::WindowMinimized);
        break;
    case Lingmo::WindowState::Maximized:
        adapter->setWindowState(window, Qt::WindowMaximized);
        break;
    case Lingmo::WindowState::FullScreen:
        adapter->setWindowState(window, Qt::WindowFullScreen);
        break;
    case Lingmo::WindowState::Hidden:
        window->hide();
        break;
    }
}

void WindowControllerPrivate::applyWindowFlags()
{
    if (!window || !adapter) return;
    adapter->configureWindowFlags(window);
}

WindowController::WindowController(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<WindowControllerPrivate>(this))
{
}

WindowController::~WindowController() = default;

void WindowController::setWindow(QWindow *w)
{
    d->window = w;
    d->adapter.reset(WindowAdapter::create(w));
    d->chrome->setWindow(w);
}

QWindow *WindowController::window() const { return d->window; }

bool WindowController::hasWindow() const { return d->window != nullptr; }

QString WindowController::title() const { return d->title; }

void WindowController::setTitle(const QString &title)
{
    if (d->title == title) return;
    d->title = title;
    if (d->window) d->window->setTitle(title);
    emit titleChanged();
}

QIcon WindowController::icon() const { return d->icon; }

void WindowController::setIcon(const QIcon &icon)
{
    d->icon = icon;
    if (d->window) d->window->setIcon(icon);
    emit iconChanged();
}

QSize WindowController::minimumSize() const { return d->minSize; }

void WindowController::setMinimumSize(const QSize &size)
{
    if (d->minSize == size) return;
    d->minSize = size;
    if (d->window) d->window->setMinimumSize(size);
    emit minimumSizeChanged();
}

QSize WindowController::maximumSize() const { return d->maxSize; }

void WindowController::setMaximumSize(const QSize &size)
{
    if (d->maxSize == size) return;
    d->maxSize = size;
    if (d->window) d->window->setMaximumSize(size);
    emit maximumSizeChanged();
}

bool WindowController::isResizable() const { return d->resizable; }

void WindowController::setResizable(bool resizable)
{
    if (d->resizable == resizable) return;
    d->resizable = resizable;
    if (d->window) {
        d->window->setFlag(Qt::WindowMinimizeButtonHint, resizable);
        d->window->setFlag(Qt::WindowMaximizeButtonHint, resizable);
        d->applyWindowFlags();
    }
    emit resizableChanged();
}

bool WindowController::isClosable() const { return d->closable; }

void WindowController::setClosable(bool closable)
{
    if (d->closable == closable) return;
    d->closable = closable;
    if (d->window) {
        d->window->setFlag(Qt::WindowCloseButtonHint, closable);
        d->applyWindowFlags();
    }
    emit closableChanged();
}

Lingmo::WindowState WindowController::windowState() const
{
    if (d->window) {
        const auto qtState = d->window->windowState();
        switch (qtState) {
        case Qt::WindowMinimized:  return Lingmo::WindowState::Minimized;
        case Qt::WindowMaximized:  return Lingmo::WindowState::Maximized;
        case Qt::WindowFullScreen: return Lingmo::WindowState::FullScreen;
        default:                   return Lingmo::WindowState::Normal;
        }
    }
    return d->state;
}

void WindowController::setWindowState(Lingmo::WindowState state)
{
    if (d->state == state) return;
    d->applyWindowState(state);
    emit windowStateChanged(d->state);
}

QMargins WindowController::extraMargins() const
{
    return d->extraMargins;
}

WindowChrome *WindowController::chrome() const { return d->chrome; }

WindowEffects *WindowController::effects() const { return d->effects; }

void WindowController::show()
{
    if (d->window) d->window->show();
}

void WindowController::hide()
{
    if (d->window) {
        d->window->hide();
        d->state = Lingmo::WindowState::Hidden;
        emit windowStateChanged(d->state);
    }
}

void WindowController::close()
{
    if (d->window) d->window->close();
    emit closed();
}

void WindowController::minimize() { setWindowState(Lingmo::WindowState::Minimized); }

void WindowController::maximize() { setWindowState(Lingmo::WindowState::Maximized); }

void WindowController::fullscreen() { setWindowState(Lingmo::WindowState::FullScreen); }

void WindowController::restore() { setWindowState(Lingmo::WindowState::Normal); }

void WindowController::centerOnScreen(QScreen *screen)
{
    if (!d->window) return;
    if (!screen) screen = QGuiApplication::primaryScreen();
    if (!screen) return;
    const QRect geo = screen->availableGeometry();
    const QSize sz = d->window->geometry().size().expandedTo(d->minSize);
    const int x = geo.x() + (geo.width() - sz.width()) / 2;
    const int y = geo.y() + (geo.height() - sz.height()) / 2;
    d->window->setGeometry(x, y, sz.width(), sz.height());
}

} // namespace Lingmo
