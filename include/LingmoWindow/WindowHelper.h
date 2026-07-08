#pragma once

#include <LingmoWindow/LingmoWindowExport.h>
#include <LingmoWindow/Types.h>

#include <QRect>
#include <QString>

class QScreen;
class QWindow;

namespace Lingmo {

namespace WindowHelper {

LINGMOWINDOW_EXPORT void centerOnScreen(QWindow *window, QScreen *screen = nullptr);

LINGMOWINDOW_EXPORT QRect availableGeometry(QScreen *screen = nullptr);

LINGMOWINDOW_EXPORT QScreen *screenAt(const QPoint &point);

LINGMOWINDOW_EXPORT bool isWayland();

LINGMOWINDOW_EXPORT bool isX11();

LINGMOWINDOW_EXPORT Lingmo::Platform currentPlatform();

LINGMOWINDOW_EXPORT QString platformName();

LINGMOWINDOW_EXPORT QWindow *transientParent(QWindow *window);

LINGMOWINDOW_EXPORT void setTransientParent(QWindow *window, QWindow *parent);

LINGMOWINDOW_EXPORT bool supportsWindowEffects();

} // namespace WindowHelper

} // namespace Lingmo
