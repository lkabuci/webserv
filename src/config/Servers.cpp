#include "Servers.hpp"

Servers::Servers() {}

void    Servers::add(const Server& server) {
    _servers.push_back(server);
}

std::vector<Server> Servers::get() { return _servers; }

Server& Servers::get(size_t i) {
    return _servers[i];
}
