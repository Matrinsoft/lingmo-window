#pragma once

#include <LingmoWindow/Window.h>

#include <QIcon>
#include <QString>
#include <QSize>
#include <QMargins>
#include <QTimer>

namespace Lingmo {

class WindowManager;

class WindowPrivate
{
public:
    explicit WindowPrivate(Window *qq);
    ~WindowPrivate();

    void init();
    void updateExtraMargins();
    void applyWindowState(Lingmo::WindowState state);
    Lingmo::WindowState qtToLingmoState(Qt::WindowState state) const;

    Window *q;

    QString title;
    QIcon icon;
    QSize minSize;
    QSize maxSize;
    bool resizable = true;
    bool closable = true;
    Lingmo::WindowState state = Lingmo::WindowState::Normal;
    Lingmo::WindowType type = Lingmo::WindowType::Normal;

    QMargins extraMargins;
    WindowManager *manager = nullptr;
};

} // namespace Lingmo
