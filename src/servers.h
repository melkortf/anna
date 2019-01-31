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

};

#endif //SERVERS_H

