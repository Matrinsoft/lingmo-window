#include <LingmoWindow/Window.h>
#include <LingmoWindow/WindowController.h>
#include <LingmoWindow/WindowChrome.h>
#include <LingmoWindow/WindowEffects.h>

#include <QResizeEvent>
#include <QMoveEvent>
#include <QExposeEvent>
#include <QScreen>
#include <QGuiApplication>

namespace Lingmo {

Window::Window(QWindow *parent)
    : QWindow(parent)
    , m_controller(new WindowController(this))
{
    m_controller->setWindow(this);
}

Window::~Window() = default;

QString Window::title() const { return m_controller->title(); }

void Window::setTitle(const QString &title)
{
    m_controller->setTitle(title);
}

QIcon Window::icon() const { return m_controller->icon(); }

void Window::setIcon(const QIcon &icon)
{
    m_controller->setIcon(icon);
}

QSize Window::minimumSize() const { return m_controller->minimumSize(); }

void Window::setMinimumSize(const QSize &size)
{
    m_controller->setMinimumSize(size);
}

QSize Window::maximumSize() const { return m_controller->maximumSize(); }

void Window::setMaximumSize(const QSize &size)
{
    m_controller->setMaximumSize(size);
}

bool Window::isResizable() const { return m_controller->isResizable(); }

void Window::setResizable(bool resizable)
{
    m_controller->setResizable(resizable);
}

bool Window::isClosable() const { return m_controller->isClosable(); }

void Window::setClosable(bool closable)
{
    m_controller->setClosable(closable);
}

Lingmo::WindowState Window::windowState() const
{
    return m_controller->windowState();
}

void Window::setWindowState(Lingmo::WindowState state)
{
    m_controller->setWindowState(state);
}

void Window::centerOnScreen(QScreen *screen)
{
    m_controller->centerOnScreen(screen);
}

QMargins Window::extraMargins() const
{
    return m_controller->extraMargins();
}

WindowController *Window::controller() const { return m_controller; }

WindowChrome *Window::chrome() const { return m_controller->chrome(); }

WindowEffects *Window::effects() const { return m_controller->effects(); }

void Window::minimize() { m_controller->minimize(); }

void Window::maximize() { m_controller->maximize(); }

void Window::fullscreen() { m_controller->fullscreen(); }

void Window::restore() { m_controller->restore(); }

void Window::show() { QWindow::show(); }

void Window::hide() { QWindow::hide(); }

void Window::close() { QWindow::close(); }

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
