#pragma once

#include <LingmoWindow/WindowEffect.h>

class QWindow;

namespace Lingmo {

class WindowEffectManager;

class WindowEffectPrivate
{
public:
    explicit WindowEffectPrivate(WindowEffect *qq);
    ~WindowEffectPrivate();

    void updateEffect();

    WindowEffect *q;

    QWindow *window = nullptr;
    WindowEffectManager *manager = nullptr;

    bool blurEnabled = false;
    bool micaEnabled = false;
    bool acrylicEnabled = false;
    qreal cornerRadius = 0.0;
    bool darkMode = false;
};

} // namespace Lingmo
