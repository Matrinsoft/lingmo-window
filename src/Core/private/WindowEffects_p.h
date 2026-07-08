#pragma once

#include <LingmoWindow/WindowEffects.h>

namespace Lingmo {

class WindowEffectsPrivate
{
public:
    explicit WindowEffectsPrivate(WindowEffects *qq);
    ~WindowEffectsPrivate();

    WindowEffects *q;

    bool blurEnabled = false;
    qreal cornerRadius = 0.0;
    bool darkMode = false;
};

} // namespace Lingmo
