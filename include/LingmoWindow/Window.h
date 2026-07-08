#pragma once

#include <LingmoWindow/LingmoWindowExport.h>
#include <LingmoWindow/Types.h>

#include <QWindow>
#include <QMargins>
#include <QSize>
#include <QString>
#include <QIcon>
#include <QRect>
#include <memory>

class QScreen;

namespace Lingmo {

class WindowPrivate;

class LINGMOWINDOW_EXPORT Window : public QWindow
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)
    Q_PROPERTY(QSize minimumSize READ minimumSize WRITE setMinimumSize NOTIFY minimumSizeChanged)
    Q_PROPERTY(QSize maximumSize READ maximumSize WRITE setMaximumSize NOTIFY maximumSizeChanged)
    Q_PROPERTY(bool resizable READ isResizable WRITE setResizable NOTIFY resizableChanged)
    Q_PROPERTY(bool closable READ isClosable WRITE setClosable NOTIFY closableChanged)
    Q_PROPERTY(Lingmo::WindowState windowState READ windowState WRITE setWindowState NOTIFY windowStateChanged)

public:
    explicit Window(QWindow *parent = nullptr);
    ~Window() override;

    QString title() const;
    void setTitle(const QString &title);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    QSize minimumSize() const;
    void setMinimumSize(const QSize &size);

    QSize maximumSize() const;
    void setMaximumSize(const QSize &size);

    bool isResizable() const;
    void setResizable(bool resizable);

    bool isClosable() const;
    void setClosable(bool closable);

    Lingmo::WindowState windowState() const;

    void centerOnScreen(QScreen *screen = nullptr);

    QMargins extraMargins() const;

public Q_SLOTS:
    void setWindowState(Lingmo::WindowState state);
    void minimize();
    void maximize();
    void fullscreen();
    void restore();
    void show();
    void hide();
    void close();

Q_SIGNALS:
    void titleChanged();
    void iconChanged();
    void geometryChanged();
    void minimumSizeChanged();
    void maximumSizeChanged();
    void resizableChanged();
    void closableChanged();
    void windowStateChanged(Lingmo::WindowState state);
    void closed();
    void activeChanged();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;
    bool event(QEvent *event) override;

private:
    std::unique_ptr<WindowPrivate> d;
};

} // namespace Lingmo
