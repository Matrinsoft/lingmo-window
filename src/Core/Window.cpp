#include "private/Window_p.h"
#include "private/WindowManager_p.h"

#include <QResizeEvent>
#include <QMoveEvent>
#include <QExposeEvent>
#include <QScreen>
#include <QGuiApplication>

namespace Lingmo {

WindowPrivate::WindowPrivate(Window *qq)
    : q(qq)
{
}

WindowPrivate::~WindowPrivate() = default;

void WindowPrivate::init()
{
    manager.reset(WindowManager::create());
}

void WindowPrivate::updateExtraMargins()
{
    extraMargins = manager ? manager->extraMargins(q) : QMargins();
}

void WindowPrivate::applyWindowState(Lingmo::WindowState s)
{
    state = s;
    if (manager) {
        manager->setWindowState(q, s);
    }
}

Window::Window(QWindow *parent)
    : QWindow(parent)
    , d(std::make_unique<WindowPrivate>(this))
{
    d->init();
}

Window::~Window() = default;

QString Window::title() const { return d->title; }

void Window::setTitle(const QString &title)
{
    if (d->title == title) return;
    d->title = title;
    if (d->manager) d->manager->setTitle(this, title);
    QWindow::setTitle(title);
    emit titleChanged();
}

QIcon Window::icon() const { return d->icon; }

void Window::setIcon(const QIcon &icon)
{
    if (d->icon.cacheKey() == icon.cacheKey()) return;
    d->icon = icon;
    if (d->manager) d->manager->setIcon(this, icon);
    emit iconChanged();
}

QSize Window::minimumSize() const { return d->minSize; }

void Window::setMinimumSize(const QSize &size)
{
    if (d->minSize == size) return;
    d->minSize = size;
    QWindow::setMinimumSize(size);
    emit minimumSizeChanged();
}

QSize Window::maximumSize() const { return d->maxSize; }

void Window::setMaximumSize(const QSize &size)
{
    if (d->maxSize == size) return;
    d->maxSize = size;
    QWindow::setMaximumSize(size);
    emit maximumSizeChanged();
}

bool Window::isResizable() const { return d->resizable; }

void Window::setResizable(bool resizable)
{
    if (d->resizable == resizable) return;
    d->resizable = resizable;
    if (d->manager) d->manager->setResizable(this, resizable);
    emit resizableChanged();
}

bool Window::isClosable() const { return d->closable; }

void Window::setClosable(bool closable)
{
    if (d->closable == closable) return;
    d->closable = closable;
    emit closableChanged();
}

Lingmo::WindowState Window::windowState() const
{
    return d->manager ? d->manager->windowState(this) : d->state;
}

void Window::setWindowState(Lingmo::WindowState state)
{
    if (d->state == state) return;
    d->applyWindowState(state);
    emit windowStateChanged(d->state);
}

void Window::minimize() { setWindowState(Lingmo::WindowState::Minimized); }

void Window::maximize() { setWindowState(Lingmo::WindowState::Maximized); }

void Window::fullscreen() { setWindowState(Lingmo::WindowState::FullScreen); }

void Window::restore() { setWindowState(Lingmo::WindowState::Normal); }

void Window::show()
{
    QWindow::show();
}

void Window::hide()
{
    QWindow::hide();
    d->state = Lingmo::WindowState::Hidden;
    emit windowStateChanged(d->state);
}

void Window::close()
{
    QWindow::close();
    emit closed();
}

void Window::centerOnScreen(QScreen *screen)
{
    if (!screen) screen = QGuiApplication::primaryScreen();
    if (!screen) return;
    const QRect geo = screen->availableGeometry();
    const QSize sz = geometry().size().expandedTo(minimumSize());
    const int x = geo.x() + (geo.width() - sz.width()) / 2;
    const int y = geo.y() + (geo.height() - sz.height()) / 2;
    setGeometry(x, y, sz.width(), sz.height());
}

QMargins Window::extraMargins() const
{
    return d->extraMargins;
}

void Window::resizeEvent(QResizeEvent *event)
{
    QWindow::resizeEvent(event);
    emit geometryChanged();
}

void Window::moveEvent(QMoveEvent *event)
{
    QWindow::moveEvent(event);
    emit geometryChanged();
}

void Window::exposeEvent(QExposeEvent *event)
{
    QWindow::exposeEvent(event);
    if (isExposed()) {
        emit activeChanged();
    }
}

bool Window::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::WindowActivate:
        emit activeChanged();
        break;
    case QEvent::WindowDeactivate:
        emit activeChanged();
        break;
    case QEvent::Close:
        emit closed();
        break;
    default:
        break;
    }
    return QWindow::event(event);
}

} // namespace Lingmo
