#ifndef ANNA_H
#define ANNA_H

#include <Cutelyst/Application>
#include <QtDBus/QDBusConnection>

class Anna : public Cutelyst::Application {
    Q_OBJECT
    CUTELYST_APPLICATION(IID "org.morgoth.anna.Anna")

public:
    Q_INVOKABLE explicit Anna(QObject* parent = nullptr);
    virtual ~Anna() override;

    bool init() override final;

    static QDBusConnection dbusConnection();

};

#endif // ANNA_H
