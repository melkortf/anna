#include "servers.h"
#include "anna.h"
#include "servermanagerinterface.h"
#include "serverinterface.h"

using namespace Cutelyst;

Servers::Servers(QObject *parent) : Controller(parent)
{
}

Servers::~Servers()
{
}

void Servers::index(Context *c)
{
    Q_UNUSED(c);
}

void Servers::index_GET(Context* c)
{
    org::morgoth::ServerManager serverManager("org.morgoth", "/servers", Anna::dbusConnection(), this);
    if (serverManager.isValid()) {
        QStringList servers = serverManager.servers();
        QJsonArray array;

        for (const QString& s: qAsConst(servers)) {
            QDBusObjectPath path = serverManager.serverPath(s);
            org::morgoth::Server server("org.morgoth", path.path(), Anna::dbusConnection(), this);
            array.append(QJsonObject{
                { QStringLiteral("name"), server.name() },
                { QStringLiteral("state"), QStringLiteral("offline") }
            });
        }

        c->response()->setJsonArrayBody(array);
    } else {
        c->response()->setJsonObjectBody({{"message", "daemon unavailable"}});
        c->response()->setStatus(Response::InternalServerError);
    }
}

