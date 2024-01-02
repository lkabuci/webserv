#include <cstring>
#include <iostream>
#include <sys/socket.h>

#include "../stream/Client.hpp"
#include "ClientEventHandler.hpp"

#define BUFFER_SIZE 4096

ClientEventHandler::ClientEventHandler(sockaddr_storage &addr, int
clientSocket)
: _socket(clientSocket), _client(addr, clientSocket) {
}

ClientEventHandler::~ClientEventHandler() {}

void ClientEventHandler::handleEvent() {
    // Implement client-related event handling
    char buffer[BUFFER_SIZE];
    std::memset(buffer, 0, BUFFER_SIZE);
    ssize_t ret = recv(_socket, buffer, BUFFER_SIZE - 1, 0);

    if (ret == -1) {
        std::cerr << "failed to read data from client" << std::endl;
        // Handle error or remove client handler
        return;
    }
    if (ret == 0) {
        // Client closed connection
        // Handle closure or remove client handler
        return;
    }
    std::cout << "Client sent: " << buffer << std::endl;
    // Process incoming data or respond to the client
    // Other necessary methods for client events
}

