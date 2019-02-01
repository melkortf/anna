#ifndef SERVERS_H
#define SERVERS_H

#include <Cutelyst/Controller>

class Servers : public Cutelyst::Controller {
    Q_OBJECT

public:
    explicit Servers(QObject *parent = nullptr);
    ~Servers();

    C_ATTR(index, :Chained("/") :PathPart("servers") :AutoArgs :ActionClass(REST))
    void index(Cutelyst::Context *c);

    C_ATTR(index_GET, :Private)
    void index_GET(Cutelyst::Context* c);

    C_ATTR(server_name, :Chained("/") :PathPart("servers") :AutoArgs :ActionClass(REST))
    void server_name(Cutelyst::Context* c, const QString& serverName);

    C_ATTR(server_name_GET, :Private)
    void server_name_GET(Cutelyst::Context* c, const QString& serverName);

};

#endif //SERVERS_H

