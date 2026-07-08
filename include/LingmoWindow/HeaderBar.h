#pragma once

#include <LingmoWindow/LingmoWindowExport.h>
#include <LingmoWindow/Types.h>

#include <QObject>
#include <QString>
#include <QIcon>
#include <QUrl>
#include <memory>

class QWindow;

namespace Lingmo {

class HeaderBarPrivate;

class LINGMOWINDOW_EXPORT HeaderBar : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle NOTIFY subtitleChanged)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QUrl iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged)
    Q_PROPERTY(bool showMinimize READ showMinimize WRITE setShowMinimize NOTIFY showMinimizeChanged)
    Q_PROPERTY(bool showMaximize READ showMaximize WRITE setShowMaximize NOTIFY showMaximizeChanged)
    Q_PROPERTY(bool showClose READ showClose WRITE setShowClose NOTIFY showCloseChanged)
    Q_PROPERTY(bool showTitle READ showTitle WRITE setShowTitle NOTIFY showTitleChanged)
    Q_PROPERTY(bool showIcon READ showIcon WRITE setShowIcon NOTIFY showIconChanged)
    Q_PROPERTY(qreal height READ height NOTIFY heightChanged)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow NOTIFY windowChanged)

public:
    explicit HeaderBar(QObject *parent = nullptr);
    ~HeaderBar() override;

    QString title() const;
    void setTitle(const QString &title);

    QString subtitle() const;
    void setSubtitle(const QString &subtitle);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    QUrl iconSource() const;
    void setIconSource(const QUrl &url);

    bool showMinimize() const;
    void setShowMinimize(bool visible);

    bool showMaximize() const;
    void setShowMaximize(bool visible);

    bool showClose() const;
    void setShowClose(bool visible);

    bool showTitle() const;
    void setShowTitle(bool visible);

    bool showIcon() const;
    void setShowIcon(bool visible);

    qreal height() const;

    QWindow *window() const;
    void setWindow(QWindow *window);

    int titleBarHeight() const;

public Q_SLOTS:
    void minimize();
    void maximize();
    void close();

Q_SIGNALS:
    void titleChanged();
    void subtitleChanged();
    void iconChanged();
    void iconSourceChanged();
    void showMinimizeChanged();
    void showMaximizeChanged();
    void showCloseChanged();
    void showTitleChanged();
    void showIconChanged();
    void heightChanged();
    void windowChanged();
    void minimizeClicked();
    void maximizeClicked();
    void closeClicked();
    void doubleClicked();

private:
    std::unique_ptr<HeaderBarPrivate> d;
};

} // namespace Lingmo
