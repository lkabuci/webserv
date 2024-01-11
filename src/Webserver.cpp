#include "Webserver.hpp"
#include "reactor/Reactor.hpp"
#include "reactor/ServerEventHandler.hpp"

Webserver::Webserver(Servers& servers) : _servers(servers) {
    _setup();
}

void Webserver::_setup() {
    Reactor& reactor = Reactor::getInstance();
    size_t   size = _servers.size();
    for (size_t i = 0; i < size; ++i) {
        ServerEventHandler* serverHandler =
            new ServerEventHandler(*_servers[i]);
        reactor.registerHandler(serverHandler, _servers[i]->getSocket());
    }
    reactor.run();
}

void Webserver::run() {
    Reactor::getInstance().run();
}
