#include "anna.h"
#include "daemon.h"

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
    return true;
}

QDBusConnection Anna::dbusConnection()
{
    // TODO Discover DBus connection
    return QDBusConnection::sessionBus();
}
