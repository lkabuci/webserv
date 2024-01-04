#include "Webserver.hpp"
#include "reactor/Reactor.hpp"
#include "reactor/ServerEventHandler.hpp"

Webserver::Webserver(Servers& servers) : _servers(servers) {
    _setup();
}

void Webserver::_setup() {
    Reactor& reactor = Reactor::getInstance();
    for (size_t i = 0; i < _servers.size(); ++i) {
        ServerEventHandler* serverHandler =
            new ServerEventHandler(_servers[i]->getSocket());
        reactor.registerHandler(serverHandler, _servers[i]->getSocket());
    }
    reactor.run();
}

void Webserver::run() {
    Reactor::getInstance().run();
}
