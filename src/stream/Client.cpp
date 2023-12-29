#include "Client.hpp"

Client::Client(struct sockaddr_storage& addr, int sockfd)
    : _sockAddr(addr), _sockfd(sockfd), _pfd(), _ip(), _port() {
    initClient();
    fillIpPort();
}

const char* Client::getClientAddress() const {
    static char address[PORT_LEN + INET6_ADDRSTRLEN + 2];
    std::memset(address, 0, sizeof(address));
    snprintf(address, sizeof(address), "%s:%s", _ip, _port);
    return address;
}

int Client::getSockFd() const {
    return _pfd.fd;
}

short Client::getEvent() const {
    return _pfd.events;
}

short Client::getRevent() const {
    return _pfd.revents;
}

void Client::setRevent(short revents) {
    _pfd.revents = revents;
}

void Client::setEvent(short event) {
    _pfd.events = event;
}

void Client::initClient() {
    std::memset(&_pfd, 0, sizeof _pfd);
    _pfd.fd = _sockfd;
    _pfd.events = POLLIN;
    _pfd.revents = 0;
}

void Client::fillIpPort() {
    struct sockaddr_in*  ipv4 = NULL;
    struct sockaddr_in6* ipv6 = NULL;

    std::memset(_ip, 0, sizeof _ip);
    std::memset(_port, 0, sizeof _port);

    switch (_sockAddr.ss_family) {
    case AF_INET:
        ipv4 = reinterpret_cast<struct sockaddr_in*>(&_sockAddr);
        inet_ntop(AF_INET, &(ipv4->sin_addr), _ip, sizeof _ip);
        snprintf(_port, sizeof(_port), "%d", ntohs(ipv4->sin_port));
        break;
    case AF_INET6:
        ipv6 = reinterpret_cast<struct sockaddr_in6*>(&_sockAddr);
        inet_ntop(AF_INET6, &(ipv6->sin6_addr), _ip, sizeof _ip);
        snprintf(_port, sizeof(_port), "%d", ntohs(ipv6->sin6_port));
        break;
    default:
        // here I should probably return a -1 or throw an error so the poll
        // multiplexing ignore it
        std::cerr << "Unknown address family\n";
        break;
    }
}
