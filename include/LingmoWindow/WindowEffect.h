#pragma once

#include <LingmoWindow/LingmoWindowExport.h>
#include <LingmoWindow/Types.h>

#include <QObject>
#include <memory>

class QWindow;

namespace Lingmo {

class WindowEffectPrivate;

class LINGMOWINDOW_EXPORT WindowEffect : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool blurEnabled READ isBlurEnabled NOTIFY blurEnabledChanged)
    Q_PROPERTY(bool micaEnabled READ isMicaEnabled NOTIFY micaEnabledChanged)
    Q_PROPERTY(bool acrylicEnabled READ isAcrylicEnabled NOTIFY acrylicEnabledChanged)
    Q_PROPERTY(qreal cornerRadius READ cornerRadius WRITE setCornerRadius NOTIFY cornerRadiusChanged)
    Q_PROPERTY(bool darkModeEnabled READ isDarkModeEnabled WRITE setDarkModeEnabled NOTIFY darkModeEnabledChanged)

public:
    explicit WindowEffect(QObject *parent = nullptr);
    ~WindowEffect() override;

    void setWindow(QWindow *window);

    bool isBlurEnabled() const;
    bool isMicaEnabled() const;
    bool isAcrylicEnabled() const;

    qreal cornerRadius() const;
    void setCornerRadius(qreal radius);

    bool isDarkModeEnabled() const;
    void setDarkModeEnabled(bool enabled);

    bool isSupported() const;

public Q_SLOTS:
    void enableBlur();
    void disableBlur();
    void enableMica();
    void disableMica();
    void enableAcrylic();
    void disableAcrylic();

Q_SIGNALS:
    void blurEnabledChanged();
    void micaEnabledChanged();
    void acrylicEnabledChanged();
    void cornerRadiusChanged();
    void darkModeEnabledChanged();

private:
    std::unique_ptr<WindowEffectPrivate> d;
};

} // namespace Lingmo
