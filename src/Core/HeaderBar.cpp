#include "private/HeaderBar_p.h"

#include <QWindow>
#include <LingmoTheme/Theme.h>
#include <LingmoTheme/Metrics.h>

namespace Lingmo {

HeaderBarPrivate::HeaderBarPrivate(HeaderBar *qq)
    : q(qq)
{
}

HeaderBarPrivate::~HeaderBarPrivate() = default;

void HeaderBarPrivate::updateHeight()
{
    const auto *theme = Theme::instance();
    if (theme) {
        const auto &metrics = theme->metrics();
        heightValue = metrics.spacingXLarge() * 2.0
                    + metrics.spacingMedium();
    } else {
        heightValue = 48.0;
    }
    emit q->heightChanged();
}

HeaderBar::HeaderBar(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<HeaderBarPrivate>(this))
{
}

HeaderBar::~HeaderBar() = default;

QString HeaderBar::title() const { return d->title; }

void HeaderBar::setTitle(const QString &title)
{
    if (d->title == title) return;
    d->title = title;
    emit titleChanged();
}

QString HeaderBar::subtitle() const { return d->subtitle; }

void HeaderBar::setSubtitle(const QString &subtitle)
{
    if (d->subtitle == subtitle) return;
    d->subtitle = subtitle;
    emit subtitleChanged();
}

QIcon HeaderBar::icon() const { return d->icon; }

void HeaderBar::setIcon(const QIcon &icon)
{
    d->icon = icon;
    emit iconChanged();
}

QUrl HeaderBar::iconSource() const { return d->iconSource; }

void HeaderBar::setIconSource(const QUrl &url)
{
    if (d->iconSource == url) return;
    d->iconSource = url;
    emit iconSourceChanged();
}

bool HeaderBar::showMinimize() const { return d->showMinimize; }

void HeaderBar::setShowMinimize(bool visible)
{
    if (d->showMinimize == visible) return;
    d->showMinimize = visible;
    emit showMinimizeChanged();
}

bool HeaderBar::showMaximize() const { return d->showMaximize; }

void HeaderBar::setShowMaximize(bool visible)
{
    if (d->showMaximize == visible) return;
    d->showMaximize = visible;
    emit showMaximizeChanged();
}

bool HeaderBar::showClose() const { return d->showClose; }

void HeaderBar::setShowClose(bool visible)
{
    if (d->showClose == visible) return;
    d->showClose = visible;
    emit showCloseChanged();
}

bool HeaderBar::showTitle() const { return d->showTitle; }

void HeaderBar::setShowTitle(bool visible)
{
    if (d->showTitle == visible) return;
    d->showTitle = visible;
    emit showTitleChanged();
}

bool HeaderBar::showIcon() const { return d->showIcon; }

void HeaderBar::setShowIcon(bool visible)
{
    if (d->showIcon == visible) return;
    d->showIcon = visible;
    emit showIconChanged();
}

qreal HeaderBar::height() const
{
    return d->heightValue;
}

QWindow *HeaderBar::window() const { return d->targetWindow; }

void HeaderBar::setWindow(QWindow *window)
{
    if (d->targetWindow == window) return;
    d->targetWindow = window;
    emit windowChanged();
}

int HeaderBar::titleBarHeight() const
{
    return static_cast<int>(d->heightValue);
}

void HeaderBar::minimize()
{
    if (d->targetWindow) d->targetWindow->setWindowState(Qt::WindowMinimized);
    emit minimizeClicked();
}

void HeaderBar::maximize()
{
    if (d->targetWindow) {
        if (d->targetWindow->windowStates() & Qt::WindowMaximized) {
            d->targetWindow->setWindowState(Qt::WindowNoState);
        } else {
            d->targetWindow->setWindowState(Qt::WindowMaximized);
        }
    }
    emit maximizeClicked();
}

void HeaderBar::close()
{
    if (d->targetWindow) d->targetWindow->close();
    emit closeClicked();
}

} // namespace Lingmo
