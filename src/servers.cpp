#include "servers.h"
#include "anna.h"
#include "servercoordinatorinterface.h"
#include "servermanagerinterface.h"
#include "serverinterface.h"
#include "serverstatusinterface.h"

using namespace Cutelyst;

namespace {

QString stateToString(morgoth::ServerCoordinator::State state)
{
    switch (state) {
        case morgoth::ServerCoordinator::State::Offline:
            return "offline";

        case morgoth::ServerCoordinator::State::Starting:
            return "starting";

        case morgoth::ServerCoordinator::State::Running:
            return "running";

        case morgoth::ServerCoordinator::State::ShuttingDown:
            return "shutting down";

        case morgoth::ServerCoordinator::State::Crashed:
            return "crashed";
    }
}

QJsonObject fetchServer(const org::morgoth::Server& server)
{
    org::morgoth::ServerCoordinator coordinator("org.morgoth", server.coordinatorPath().path(), Anna::dbusConnection());

    auto ret = QJsonObject{
        { QStringLiteral("name"), server.name() },
        { QStringLiteral("state"), stateToString(coordinator.state()) }
    };

    if (coordinator.state() == morgoth::ServerCoordinator::Running) {
        QJsonObject statusJson;
        org::morgoth::ServerStatus status("org.morgoth", server.statusPath().path(), Anna::dbusConnection());
        statusJson["hostname"] = status.hostname();
        statusJson["map"] = status.map();
        statusJson["maxPlayers"] = status.maxPlayers();
        statusJson["playerCount"] = status.playerCount();
        statusJson["address"] = status.address();
        statusJson["passwordProtected"] = !status.password().isEmpty();
        statusJson["sourceTv"] = QJsonObject{
            { "port", status.stvPort() },
            { "password", status.stvPassword() }
        };

        QJsonArray playersJson;
        auto players = status.players();
        for (const morgoth::PlayerInfo& player: qAsConst(players)) {
            playersJson.append(QJsonObject{
                { QStringLiteral("name"), player.name() },
                { QStringLiteral("steamId"), QString::number(player.steamId().toSteamId64()) }
            });
        }

        statusJson["players"] = playersJson;
        ret["status"] = statusJson;
    }

    return ret;
}

}

Servers::Servers(QObject *parent) :
    Controller(parent)
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
            array.append(fetchServer(server));
        }

        c->response()->setJsonArrayBody(array);
    } else {
        c->response()->setJsonObjectBody({{"message", "daemon unavailable"}});
        c->response()->setStatus(Response::InternalServerError);
    }
}

void Servers::server_name(Context* c, const QString& serverName)
{
    Q_UNUSED(c);
    Q_UNUSED(serverName);
}

void Servers::server_name_GET(Context* c, const QString& serverName)
{
    org::morgoth::ServerManager serverManager("org.morgoth", "/servers", Anna::dbusConnection(), this);
    if (serverManager.isValid()) {
        if (serverManager.servers().contains(serverName)) {
            QDBusObjectPath path = serverManager.serverPath(serverName);
            org::morgoth::Server server("org.morgoth", path.path(), Anna::dbusConnection(), this);
            c->response()->setJsonObjectBody(fetchServer(server));
        } else {
            c->response()->setJsonObjectBody({{"message", "server not found"}});
            c->response()->setStatus(Response::NotFound);
        }
    } else {
        c->response()->setJsonObjectBody({{"message", "daemon unavailable"}});
        c->response()->setStatus(Response::InternalServerError);
    }
}

