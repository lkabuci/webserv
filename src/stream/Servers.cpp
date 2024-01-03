#include "Servers.hpp"

Servers::Servers() {}

void Servers::add(Server* server) {
    _servers.push_back(server);
}

std::vector<Server*> Servers::get() {
    return _servers;
}

size_t Servers::size() const {
    return _servers.size();
}

Server* Servers::operator[](size_t i) {
    return _servers[i];
}

Servers::~Servers() {
    for (std::vector<Server*>::iterator it = _servers.begin();
         it != _servers.end(); ++it) {
        delete *it;
    }
}
