#include "private/WindowEffects_p.h"

namespace Lingmo {

WindowEffectsPrivate::WindowEffectsPrivate(WindowEffects *qq)
    : q(qq)
{
}

WindowEffectsPrivate::~WindowEffectsPrivate() = default;

WindowEffects::WindowEffects(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<WindowEffectsPrivate>(this))
{
}

WindowEffects::~WindowEffects() = default;

bool WindowEffects::isBlurEnabled() const { return d->blurEnabled; }

void WindowEffects::setBlurEnabled(bool enabled)
{
    if (d->blurEnabled == enabled) return;
    d->blurEnabled = enabled;
    emit blurEnabledChanged();
}

qreal WindowEffects::cornerRadius() const { return d->cornerRadius; }

void WindowEffects::setCornerRadius(qreal radius)
{
    if (qFuzzyCompare(d->cornerRadius, radius)) return;
    d->cornerRadius = radius;
    emit cornerRadiusChanged();
}

bool WindowEffects::isDarkModeEnabled() const { return d->darkMode; }

void WindowEffects::setDarkModeEnabled(bool enabled)
{
    if (d->darkMode == enabled) return;
    d->darkMode = enabled;
    emit darkModeEnabledChanged();
}

} // namespace Lingmo
