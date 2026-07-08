#include <LingmoWindow/Window.h>
#include <LingmoWindow/HeaderBar.h>
#include <LingmoWindow/WindowEffect.h>
#include <LingmoWindow/Types.h>

#include <QtQml/qqml.h>
#include <QtQml/qqmlextensionplugin.h>

class LingmoWindowPlugin : public QQmlEngineExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void initializeEngine(QQmlEngine *engine, const char *uri) override
    {
        Q_UNUSED(engine);
        Q_UNUSED(uri);
    }

    void registerTypes(const char *uri) override
    {
        qmlRegisterUncreatableType<Lingmo::Window>(uri, 1, 0, "Window",
            QStringLiteral("Window is provided by the QML layer"));
        qmlRegisterUncreatableType<Lingmo::HeaderBar>(uri, 1, 0, "HeaderBar",
            QStringLiteral("HeaderBar is provided by the QML layer"));
        qmlRegisterUncreatableType<Lingmo::WindowEffect>(uri, 1, 0, "WindowEffect",
            QStringLiteral("WindowEffect is provided by the QML layer"));
    }
};

#include "LingmoWindowPlugin.moc"
