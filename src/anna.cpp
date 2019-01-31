#include "anna.h"
#include "daemon.h"
#include "servers.h"

using namespace Cutelyst;

Anna::Anna(QObject* parent) :
    Application(parent)
{

}

Anna::~Anna()
{

}

bool Anna::init()
{
    new Daemon(this);
    new Servers(this);
    return true;
}

QDBusConnection Anna::dbusConnection()
{
    // TODO Discover DBus connection
    return QDBusConnection::sessionBus();
}
