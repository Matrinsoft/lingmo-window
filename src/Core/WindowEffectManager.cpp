#include "private/WindowEffectManager_p.h"

#include <LingmoWindow/WindowHelper.h>

#include <QWindow>

#if defined(Q_OS_WIN)
#  include <QtGui/private/qwindow_p.h>
#  include <dwmapi.h>
#  include <windows.h>
#  pragma comment(lib, "dwmapi.lib")
#  pragma comment(lib, "user32.lib")
#endif

namespace Lingmo {

// --- Generic WindowEffectManager (cross-platform fallback) ---

class GenericWindowEffectManager : public WindowEffectManager
{
public:
    void enableBlur(QWindow *window) override
    {
        Q_UNUSED(window);
    }

    void disableBlur(QWindow *window) override
    {
        Q_UNUSED(window);
    }

    void enableMica(QWindow *window) override
    {
        Q_UNUSED(window);
    }

    void disableMica(QWindow *window) override
    {
        Q_UNUSED(window);
    }

    void enableAcrylic(QWindow *window) override
    {
        Q_UNUSED(window);
    }

    void disableAcrylic(QWindow *window) override
    {
        Q_UNUSED(window);
    }

    void setCornerRadius(QWindow *window, qreal radius) override
    {
        Q_UNUSED(window);
        Q_UNUSED(radius);
    }

    void setDarkMode(QWindow *window, bool enabled) override
    {
        Q_UNUSED(window);
        Q_UNUSED(enabled);
    }

    bool isSupported() const override
    {
        return false;
    }
};

// --- Windows WindowEffectManager ---

#if defined(Q_OS_WIN)

class WindowsWindowEffectManager : public WindowEffectManager
{
public:
    void enableBlur(QWindow *window) override
    {
        if (!window) return;
        HWND hwnd = reinterpret_cast<HWND>(window->winId());
        if (!hwnd) return;

        DWM_BLURBEHIND bb = {};
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = TRUE;
        bb.hRgnBlur = nullptr;
        DwmEnableBlurBehindWindow(hwnd, &bb);
    }

    void disableBlur(QWindow *window) override
    {
        if (!window) return;
        HWND hwnd = reinterpret_cast<HWND>(window->winId());
        if (!hwnd) return;

        DWM_BLURBEHIND bb = {};
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = FALSE;
        DwmEnableBlurBehindWindow(hwnd, &bb);
    }

    void enableMica(QWindow *window) override
    {
        if (!window) return;
        HWND hwnd = reinterpret_cast<HWND>(window->winId());
        if (!hwnd) return;

        static const DWM_SYSTEMBACKDROP_TYPE mica = DWMSBT_MAINWINDOW;
        DwmSetWindowAttribute(hwnd, DWMWA_SYSTEMBACKDROP_TYPE, &mica, sizeof(mica));
    }

    void disableMica(QWindow *window) override
    {
        if (!window) return;
        HWND hwnd = reinterpret_cast<HWND>(window->winId());
        if (!hwnd) return;

        static const DWM_SYSTEMBACKDROP_TYPE none = DWMSBT_NONE;
        DwmSetWindowAttribute(hwnd, DWMWA_SYSTEMBACKDROP_TYPE, &none, sizeof(none));
    }

    void enableAcrylic(QWindow *window) override
    {
        if (!window) return;
        HWND hwnd = reinterpret_cast<HWND>(window->winId());
        if (!hwnd) return;

        static const DWM_SYSTEMBACKDROP_TYPE acrylic = DWMSBT_ACRYLICBLUR;
        DwmSetWindowAttribute(hwnd, DWMWA_SYSTEMBACKDROP_TYPE, &acrylic, sizeof(acrylic));
    }

    void disableAcrylic(QWindow *window) override
    {
        disableMica(window);
    }

    void setCornerRadius(QWindow *window, qreal radius) override
    {
        if (!window) return;
        HWND hwnd = reinterpret_cast<HWND>(window->winId());
        if (!hwnd) return;

        DWM_WINDOW_CORNER_PREFERENCE pref;
        if (qFuzzyIsNull(radius)) {
            pref = DWMWCP_DONOTROUND;
        } else {
            pref = DWMWCP_ROUND;
        }
        DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &pref, sizeof(pref));
    }

    void setDarkMode(QWindow *window, bool enabled) override
    {
        if (!window) return;
        HWND hwnd = reinterpret_cast<HWND>(window->winId());
        if (!hwnd) return;

        BOOL dark = enabled ? TRUE : FALSE;
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
    }

    bool isSupported() const override
    {
        return true;
    }
};

#endif

WindowEffectManager *WindowEffectManager::create()
{
    const auto platform = WindowHelper::currentPlatform();
    switch (platform) {
#if defined(Q_OS_WIN)
    case Platform::Windows:
        return new WindowsWindowEffectManager();
#endif
    default:
        return new GenericWindowEffectManager();
    }
}

} // namespace Lingmo
