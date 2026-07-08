#pragma once

#include <LingmoWindow/WindowChrome.h>

#include <QMargins>

class QWindow;

namespace Lingmo {

class WindowChromePrivate
{
public:
    explicit WindowChromePrivate(WindowChrome *qq);
    ~WindowChromePrivate();

    WindowChrome *q;

    QWindow *window = nullptr;
    qreal cornerRadius = 0.0;
    QMargins resizeMargins{8, 8, 8, 8};
    QMargins dragMargins{0, 0, 0, 0};
};

} // namespace Lingmo
