#pragma once

#include <LingmoWindow/LingmoWindowExport.h>

#include <QObject>
#include <memory>

namespace Lingmo {

class WindowEffectsPrivate;

class LINGMOWINDOW_EXPORT WindowEffects : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool blurEnabled READ isBlurEnabled WRITE setBlurEnabled NOTIFY blurEnabledChanged)
    Q_PROPERTY(qreal cornerRadius READ cornerRadius WRITE setCornerRadius NOTIFY cornerRadiusChanged)
    Q_PROPERTY(bool darkModeEnabled READ isDarkModeEnabled WRITE setDarkModeEnabled NOTIFY darkModeEnabledChanged)

public:
    explicit WindowEffects(QObject *parent = nullptr);
    ~WindowEffects() override;

    bool isBlurEnabled() const;
    void setBlurEnabled(bool enabled);

    qreal cornerRadius() const;
    void setCornerRadius(qreal radius);

    bool isDarkModeEnabled() const;
    void setDarkModeEnabled(bool enabled);

Q_SIGNALS:
    void blurEnabledChanged();
    void cornerRadiusChanged();
    void darkModeEnabledChanged();

private:
    std::unique_ptr<WindowEffectsPrivate> d;
};

} // namespace Lingmo
