#include "daemon.h"
#include "anna.h"
#include "daemoninterface.h"
#include <QtCore>

using namespace Cutelyst;

Daemon::Daemon(QObject* parent) : Controller(parent)
{

}

void Daemon::index(Context* c)
{
    Q_UNUSED(c);
}

void Daemon::index_GET(Context* c)
{
    org::morgoth::Daemon daemon("org.morgoth", "/daemon", Anna::dbusConnection(), this);
    if (!daemon.isValid()) {
        c->response()->setJsonObjectBody({{"message", "daemon unavailable"}});
        c->response()->setStatus(Response::InternalServerError);
    } else {
        c->response()->setJsonObjectBody({{ "version", daemon.version() }});
    }
}
