#include "Demultiplexer.hpp"

// Add server socket to poll list
Demultiplexer::Demultiplexer(int serverSocket) : _serverSocket(serverSocket) {
    struct pollfd serverFd = {_serverSocket, POLLIN, 0};
    _fds.push_back(serverFd);
}

// Poll for events indefinitely
int Demultiplexer::pollEvents() {
    return poll(_fds.data(), _fds.size(), -1);
}

std::vector<pollfd>& Demultiplexer::getDescriptors() {
    return _fds;
}
