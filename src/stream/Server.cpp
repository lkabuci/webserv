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

const std::string& Server::ip() const {
    return _svconf.ip();
}

const std::string& Server::port() const {
    return _svconf.port();
}

const std::set<std::string>& Server::server_name() const {
    return _svconf.server_name();
}

const size_t& Server::client_max_body_size() const {
    return _svconf.client_max_body_size();
}

const std::set<std::string>& Server::index() const {
    return _svconf.index();
}

const std::set<std::string>& Server::root() const {
    return _svconf.root();
}

const std::map<size_t, std::string>& Server::error_page() const {
    return _svconf.error_page();
}

const std::map<size_t, std::string>& Server::return_page() const {
    return _svconf.return_page();
}

const std::set<std::string>& Server::allow_methods() const {
    return _svconf.allow_methods();
}

const bool& Server::autoindex() const {
    return _svconf.autoindex();
}
