#include "private/WindowManager_p.h"

#include <LingmoWindow/WindowHelper.h>

#include <QGuiApplication>
#include <QWindow>

namespace Lingmo {

// WindowManager is no longer used. Window delegates directly to
// WindowController which operates on QWindow without a strategy class.
// This file is retained as a stub for backward compatibility.

WindowManager *WindowManager::create()
{
    return nullptr;
}

} // namespace Lingmo
