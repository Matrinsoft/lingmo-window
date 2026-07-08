#pragma once

#include <LingmoWindow/Types.h>

class QWindow;

namespace Lingmo {

class WindowEffect;

class WindowEffectManager
{
public:
    static WindowEffectManager *create();

    virtual ~WindowEffectManager() = default;

    virtual void enableBlur(QWindow *window);
    virtual void disableBlur(QWindow *window);
    virtual void enableMica(QWindow *window);
    virtual void disableMica(QWindow *window);
    virtual void enableAcrylic(QWindow *window);
    virtual void disableAcrylic(QWindow *window);
    virtual void setCornerRadius(QWindow *window, qreal radius);
    virtual void setDarkMode(QWindow *window, bool enabled);
    virtual bool isSupported() const;

protected:
    WindowEffectManager() = default;
};

} // namespace Lingmo
