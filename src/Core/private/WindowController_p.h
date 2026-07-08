#pragma once

#include <LingmoWindow/WindowController.h>

#include <QIcon>
#include <QString>
#include <QSize>
#include <QMargins>
#include <memory>

class QWindow;

namespace Lingmo {

class WindowAdapter;
class WindowChrome;
class WindowEffects;

class WindowControllerPrivate
{
public:
    explicit WindowControllerPrivate(WindowController *qq);
    ~WindowControllerPrivate();

    void applyWindowState(Lingmo::WindowState state);
    void applyWindowFlags();

    WindowController *q;

    QWindow *window = nullptr;
    std::unique_ptr<WindowAdapter> adapter;
    WindowChrome *chrome = nullptr;
    WindowEffects *effects = nullptr;

    QString title;
    QIcon icon;
    QSize minSize;
    QSize maxSize;
    bool resizable = true;
    bool closable = true;
    Lingmo::WindowState state = Lingmo::WindowState::Normal;
    QMargins extraMargins;
};

} // namespace Lingmo
