#pragma once

#include <LingmoWindow/HeaderBar.h>

#include <QString>
#include <QIcon>
#include <QUrl>

class QWindow;

namespace Lingmo {

class HeaderBarPrivate
{
public:
    explicit HeaderBarPrivate(HeaderBar *qq);
    ~HeaderBarPrivate();

    void updateHeight();

    HeaderBar *q;

    QString title;
    QString subtitle;
    QIcon icon;
    QUrl iconSource;
    bool showMinimize = true;
    bool showMaximize = true;
    bool showClose = true;
    bool showTitle = true;
    bool showIcon = false;
    qreal heightValue = 48.0;
    QWindow *targetWindow = nullptr;
};

} // namespace Lingmo
