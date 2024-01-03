#include "Server.hpp"
#include <unistd.h>

Server::Server(const ServerConfig& svconf) {
    setServer(svconf);
}

Server::Server(const Server& server)
    : _svconf(server._svconf), _sockfd(server._sockfd) {}

Server::~Server() {
    close(_sockfd);
}

Server& Server::operator=(const Server& server) {
    if (this == &server)
        return *this;
    _svconf = server._svconf;
    _sockfd = server._sockfd;
    return *this;
}

ServerConfig& Server::getServerConfig() {
    return _svconf;
}

const int& Server::getSocket() const {
    return _sockfd;
}

void Server::setServer(const ServerConfig& svconf) {
    _svconf = svconf;
    Socket sock(_svconf.ip().c_str(), _svconf.port().c_str());
    _sockfd = sock.getSocketfd();
}
