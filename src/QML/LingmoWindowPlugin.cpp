#include <LingmoWindow/Window.h>
#include <LingmoWindow/WindowController.h>
#include <LingmoWindow/WindowChrome.h>
#include <LingmoWindow/WindowEffects.h>
#include <LingmoWindow/HeaderBar.h>
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
        qmlRegisterUncreatableType<Lingmo::WindowController>(uri, 1, 0, "WindowController",
            QStringLiteral("WindowController is provided by the C++ layer"));
        qmlRegisterUncreatableType<Lingmo::WindowChrome>(uri, 1, 0, "WindowChrome",
            QStringLiteral("WindowChrome is provided by the C++ layer"));
        qmlRegisterUncreatableType<Lingmo::WindowEffects>(uri, 1, 0, "WindowEffects",
            QStringLiteral("WindowEffects is provided by the C++ layer"));
        qmlRegisterUncreatableType<Lingmo::HeaderBar>(uri, 1, 0, "HeaderBar",
            QStringLiteral("HeaderBar is provided by the QML layer"));
    }
};

#include "LingmoWindowPlugin.moc"
