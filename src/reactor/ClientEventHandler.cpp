#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include "../stream/Client.hpp"
#include "ClientEventHandler.hpp"
#include "Reactor.hpp"

#define BUFFER_SIZE 4096

ClientEventHandler::ClientEventHandler(sockaddr_storage& addr, int clientSocket)
    : _socket(clientSocket), _client(addr, clientSocket) {}

ClientEventHandler::~ClientEventHandler() {}

void ClientEventHandler::handleEvent() {
    // Implement client-related event handling
    char buffer[BUFFER_SIZE];
    std::memset(buffer, 0, BUFFER_SIZE);
    ssize_t ret = recv(_socket, buffer, BUFFER_SIZE - 1, 0);

    if (ret == -1) {
        std::cerr << "failed to read data from client" << std::endl;
        Reactor::getInstance().unregisterHandler(this);
        return;
    }
    // Client closed connection
    if (ret == 0) {
        std::cout << "Client " << _client.getSockFd()
                  << " closed connection"
                     "."
                  << std::endl;
        Reactor::getInstance().unregisterHandler(this);
        return;
    }
    std::cout << "Client " << _client.getSockFd() << " sent: " << buffer
              << std::endl;
    // Process incoming data or respond to the client
    // note that if the connection should be kept alive or not
    // Other necessary methods for client events
}
