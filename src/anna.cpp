#include "anna.h"
#include "daemon.h"
#include "servers.h"
#include <Cutelyst/Plugins/CSRFProtection/CSRFProtection>
#include <QtCore>

using namespace Cutelyst;

Anna::Anna(QObject* parent) :
    Application(parent)
{
    // cors
    defaultHeaders().setHeader("Access-Control-Allow-Origin", "*");
}

Anna::~Anna()
{

}

bool Anna::init()
{
    // endpoints
    new Daemon(this);
    new Servers(this);

    // plugins
    new CSRFProtection(this);

    return true;
}

QDBusConnection Anna::dbusConnection()
{
    // TODO Discover DBus connection
    return QDBusConnection::sessionBus();
}
