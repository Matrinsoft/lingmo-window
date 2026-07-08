#pragma once

#include <LingmoWindow/LingmoWindowExport.h>

#include <QObject>
#include <QMargins>
#include <QPoint>
#include <QSize>
#include <QRegion>
#include <memory>

class QWindow;

namespace Lingmo {

class WindowChromePrivate;

class LINGMOWINDOW_EXPORT WindowChrome : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal cornerRadius READ cornerRadius WRITE setCornerRadius NOTIFY cornerRadiusChanged)
    Q_PROPERTY(QMargins resizeMargins READ resizeMargins WRITE setResizeMargins NOTIFY resizeMarginsChanged)
    Q_PROPERTY(QMargins dragMargins READ dragMargins WRITE setDragMargins NOTIFY dragMarginsChanged)

public:
    explicit WindowChrome(QObject *parent = nullptr);
    ~WindowChrome() override;

    void setWindow(QWindow *window);
    QWindow *window() const;

    qreal cornerRadius() const;
    void setCornerRadius(qreal radius);

    QMargins resizeMargins() const;
    void setResizeMargins(const QMargins &margins);

    QMargins dragMargins() const;
    void setDragMargins(const QMargins &margins);

    Q_INVOKABLE bool isInDragArea(const QPoint &localPos) const;
    Q_INVOKABLE Qt::Edges resizeEdgeAt(const QPoint &localPos) const;

    QRegion dragRegion(const QSize &windowSize) const;
    QRegion resizeRegion(const QSize &windowSize) const;

Q_SIGNALS:
    void cornerRadiusChanged();
    void resizeMarginsChanged();
    void dragMarginsChanged();

private:
    std::unique_ptr<WindowChromePrivate> d;
};

} // namespace Lingmo
