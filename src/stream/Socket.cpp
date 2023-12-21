#include "Socket.hpp"
#include <cstdlib>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Socket::Socket(const char* ip, const char* port)
    : _addresses(ip, port), _sockfd(-1), _ip(ip), _port(port) {
    initializeSocket();
    std::cout << "Successfully listening on " << _ip << ":" << _port << "\n";
}

void Socket::initializeSocket() {
    int i = 0;
    for (; i < _addresses.getAddresses().size(); ++i) {
        const struct addrinfo currentAddress = _addresses.getAddresses()[i];
        if ((_sockfd =
                 socket(currentAddress.ai_family, currentAddress.ai_socktype,
                        currentAddress.ai_protocol)) == -1)
            continue;
        try {
            configureSocket();
            bindSocket(i);
        } catch (const std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            close(_sockfd);
            continue;
        }
        break;
    }
    if (i == _addresses.getAddresses().size()) {
        std::cerr << "Error: could not bind address for "
                  << std::string(_ip) + ":" << std::string(_port) << ".\n";
        std::exit(EXIT_FAILURE);
    }
}

Socket::~Socket() { close(_sockfd); }

int Socket::getSocketfd() const { return _sockfd; }

void Socket::configureSocket() {
    if (fcntl(_sockfd, F_SETFL, O_NONBLOCK, FD_CLOEXEC) < 0) {
        throw std::runtime_error("Failed to configure socket");
        ;
    }
    int option = 1;
    if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, (void*)&option,
                   (socklen_t)sizeof(option)) < 0) {
        throw std::runtime_error("Failed to set socket option");
    }
}

void Socket::bindSocket(int index) {
    const struct sockaddr* address =
        (struct sockaddr*)_addresses.getAddresses()[index].ai_addr;
    const socklen_t addressLen =
        (socklen_t)_addresses.getAddresses()[index].ai_addrlen;
    const int bret = bind(_sockfd, address, addressLen);
    if (bret < 0) {
        throw std::runtime_error("Failed to bind on socket");
    }
    const int lret = listen(_sockfd, BACKLOG);
    if (lret < 0) {
        throw std::runtime_error("Failed to listen on socket");
    }
}
