#include "Webserver.hpp"
#include "../../include/webserv.h"
#include <cstring>
#include <iostream>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Webserver::Webserver(std::vector<int>& serverSockets)
    : _pollfds(), _nbrOfServers(serverSockets.size()) {
    for (size_t i = 0; i < _nbrOfServers; i++) {
        pollfd pfd = {serverSockets[i], POLLIN, 0};
        _pollfds.push_back(pfd);
    }
}

void Webserver::start() {
    while (isServerRunning) {
        int ret = poll(_pollfds.data(), _pollfds.size(), -1);
        if (ret == -1) {
            std::cerr << "poll failed" << std::endl;
            continue;
            // std::exit(EXIT_FAILURE);
        }
        // we are on the server side of the connection
        for (size_t i = 0; i < _nbrOfServers; i++) {
            if (_pollfds[i].revents & POLLIN) {
                // accept connection
                sockaddr_storage clientAddr;
                socklen_t        clientAddrLen = sizeof clientAddr;
                int              clientSocket = accept(
                    _pollfds[i].fd, (sockaddr*)&clientAddr, &clientAddrLen);
                if (clientSocket == -1) {
                    std::cerr << "failed to connect" << std::endl;
                    continue;
                }
                Client* client = new Client(clientAddr, clientSocket);
                _clients.push_back(client);
                _pollfds.push_back(client->getPfd());
            }
        }
        // we are on the client side of the connection
        for (size_t i = _nbrOfServers; i < _pollfds.size(); i++) {
            if (_pollfds[i].revents & POLLHUP) {
                removeClient(i - _nbrOfServers);
                continue;
            }
            if (_pollfds[i].revents & POLLIN) {
                // read data from a client
                char _buffer[BUFFER_SIZE];
                std::memset(_buffer, 0, BUFFER_SIZE);
                int ret = recv(_pollfds[i].fd, _buffer, BUFFER_SIZE - 1, 0);
                if (ret == -1) {
                    std::cerr << "failed to read data from client" << std::endl;
                    removeClient(i - _nbrOfServers);
                    continue;
                }
                if (ret == 0) {
                    // client closed connection
                    removeClient(i - _nbrOfServers);
                    continue;
                }
                std::cout << "client (" << _pollfds[i].fd << ")\""
                          << "sent: " << _buffer << std::endl;
            }
        }
    }
}

void Webserver::removeClient(size_t ClientIndex) {
    delete _clients[ClientIndex];
    _clients.erase(_clients.begin() + ClientIndex);
    _pollfds.erase(_pollfds.begin() + _nbrOfServers + ClientIndex);
}

Webserver::~Webserver() {
    // close servers
    for (size_t i = 0; i < _nbrOfServers; i++) {
        close(_pollfds[i].fd);
    }
    // close clients
    for (size_t i = 0; i < _clients.size(); i++) {
        delete _clients[i]; // this one will call
                            // close(_clients[i]->getSockFd())
    }
    _clients.clear();
    _pollfds.clear();
}
