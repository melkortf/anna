#ifndef DAEMON_H
#define DAEMON_H

#include <Cutelyst/Controller>

class Daemon : public Cutelyst::Controller {
    Q_OBJECT

public:
    Daemon(QObject* parent = nullptr);

    C_ATTR(index, :Chained("/") :PathPart("daemon") :AutoArgs :ActionClass(REST))
    void index(Cutelyst::Context* c);

    C_ATTR(index_GET, :Private)
    void index_GET(Cutelyst::Context* c);

};

#endif // DAEMON_H
