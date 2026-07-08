#include "private/WindowEffect_p.h"
#include "private/WindowEffectManager_p.h"

#include <QWindow>

namespace Lingmo {

WindowEffectPrivate::WindowEffectPrivate(WindowEffect *qq)
    : q(qq)
{
    manager.reset(WindowEffectManager::create());
}

WindowEffectPrivate::~WindowEffectPrivate() = default;

void WindowEffectPrivate::updateEffect()
{
    if (!window || !manager) return;
    if (blurEnabled) manager->enableBlur(window);
    else manager->disableBlur(window);
    if (micaEnabled) manager->enableMica(window);
    else manager->disableMica(window);
    if (acrylicEnabled) manager->enableAcrylic(window);
    else manager->disableAcrylic(window);
    if (cornerRadius > 0.0) manager->setCornerRadius(window, cornerRadius);
    manager->setDarkMode(window, darkMode);
}

WindowEffect::WindowEffect(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<WindowEffectPrivate>(this))
{
}

WindowEffect::~WindowEffect() = default;

void WindowEffect::setWindow(QWindow *window)
{
    d->window = window;
}

bool WindowEffect::isBlurEnabled() const { return d->blurEnabled; }

bool WindowEffect::isMicaEnabled() const { return d->micaEnabled; }

bool WindowEffect::isAcrylicEnabled() const { return d->acrylicEnabled; }

qreal WindowEffect::cornerRadius() const { return d->cornerRadius; }

void WindowEffect::setCornerRadius(qreal radius)
{
    if (qFuzzyCompare(d->cornerRadius, radius)) return;
    d->cornerRadius = radius;
    if (d->manager) d->manager->setCornerRadius(d->window, radius);
    emit cornerRadiusChanged();
}

bool WindowEffect::isDarkModeEnabled() const { return d->darkMode; }

void WindowEffect::setDarkModeEnabled(bool enabled)
{
    if (d->darkMode == enabled) return;
    d->darkMode = enabled;
    if (d->manager) d->manager->setDarkMode(d->window, enabled);
    emit darkModeEnabledChanged();
}

bool WindowEffect::isSupported() const
{
    return d->manager ? d->manager->isSupported() : false;
}

void WindowEffect::enableBlur()
{
    if (d->blurEnabled) return;
    d->blurEnabled = true;
    if (d->manager) d->manager->enableBlur(d->window);
    emit blurEnabledChanged();
}

void WindowEffect::disableBlur()
{
    if (!d->blurEnabled) return;
    d->blurEnabled = false;
    if (d->manager) d->manager->disableBlur(d->window);
    emit blurEnabledChanged();
}

void WindowEffect::enableMica()
{
    if (d->micaEnabled) return;
    d->micaEnabled = true;
    if (d->manager) d->manager->enableMica(d->window);
    emit micaEnabledChanged();
}

void WindowEffect::disableMica()
{
    if (!d->micaEnabled) return;
    d->micaEnabled = false;
    if (d->manager) d->manager->disableMica(d->window);
    emit micaEnabledChanged();
}

void WindowEffect::enableAcrylic()
{
    if (d->acrylicEnabled) return;
    d->acrylicEnabled = true;
    if (d->manager) d->manager->enableAcrylic(d->window);
    emit acrylicEnabledChanged();
}

void WindowEffect::disableAcrylic()
{
    if (!d->acrylicEnabled) return;
    d->acrylicEnabled = false;
    if (d->manager) d->manager->disableAcrylic(d->window);
    emit acrylicEnabledChanged();
}

} // namespace Lingmo
